#!/bin/bash

# Function to install packages on Debian-based systems
install_debian() {
    sudo apt-get update
    sudo apt-get install -y libpugixml-dev libprotobuf-dev libprotoc-dev protobuf-compiler libopencv-dev libzmq3-dev cmake g++ git

    # Install libtoml11 from source
    git clone https://github.com/marzer/tomlplusplus.git
    cd tomlplusplus
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
    sudo cmake --build build --target install
    cd ..
    rm -rf tomlplusplus

    # Install darknet from source
    git clone https://github.com/AlexeyAB/darknet
    cd darknet
    make
    sudo cp darknet /usr/local/bin
    sudo chmod +x /usr/local/bin/darknet
    cd ..
    rm -rf darknet

    # Install Cuda from source (ONLY IF GPU PRESENT)
    if command -v nvcc &> /dev/null; then
        echo "CUDA already installed!"
    else
        # Check if NVIDIA GPU is present
        if lspci | grep -i nvidia; then
            # Check if NVIDIA driver is installed
            if nvidia-smi &> /dev/null; then
                # Add GPG Key for Ubuntu
                sudo apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/3bf863cc.pub

                # Add Cuda toolkit repo (doesn't live in Ubuntu main repo)
                wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/cuda-ubuntu2004.pin
                sudo mv cuda-ubuntu2004.pin /etc/apt/preferences.d/cuda-repository-pin-600
                sudo add-apt-repository "deb https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/ /"

                # Update and install cuda using new cuda repo
                sudo apt-get update
                sudo apt install cuda

                # Move path to bashrc and source 
                echo 'export PATH=/usr/local/cuda/bin${PATH:+:${PATH}}' >> ~/.bashrc
                source ~/.bashrc

                # Check and print cuda version
                echo 'Installed CUDA!'
                echo '----------------------'
                echo 'nvcc --version'
            else
                echo "NVIDIA driver not found! Skipping CUDA installation..."
            fi
        else
            echo "NVIDIA driver/GPU not found! Skipping CUDA installation..."
        fi

    fi
    
    # Ask if user wants to install darknet weights
    echo "Would you like to wget yolov4 model?"
    read -p "Enter 'yes' or 'no': " answer

    if [[ $answer == "yes" ]] || [[ $answer == "y" ]]; then
         wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v3_optimal/yolov4.weights
	 wget https://raw.githubusercontent.com/AlexeyAB/darknet/master/cfg/yolov4.cfg

	 mkdir -p ../Models && cp yolov4.* ../Models
	 rm yolov4.*
    fi    
    
    # Ask if user wants to install pre-trained car model (trained on COCO dataset)
    echo "Would you like to get pre-trained car model (yolov3)?"
    read -p "Enter 'yes' or 'no': " answer

    if [[ $answer == "yes" ]] || [[ $answer == "y" ]]; then
         wget https://pjreddie.com/media/files/yolov3.weights
	 wget https://github.com/pjreddie/darknet/blob/master/cfg/yolov3.cfg

         mkdir -p ../Models && cp yolov3.* ../Models
         rm yolov3.*
    fi

}

# Function to install packages on Red Hat-based systems
install_redhat() {
    sudo yum install -y epel-release
    sudo yum install -y pugixml-devel protobuf-devel protobuf-compiler opencv-devel cppzmq-devel cmake gcc-c++ git

    # Install libtoml11 from source
    git clone https://github.com/ToruNiina/toml11.git
    cd toml11
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
    sudo cmake --build build --target install
    cd ..
    rm -rf toml11

    # Install darknet from source
    git clone https://github.com/AlexeyAB/darknet 
    cd darknet
    make
    sudo cp darknet /usr/local/bin
    sudo chmod +x /usr/local/bin/darknet
    cd ..
    rm -rf darknet 

    # Install Cuda from source (TODO) 
}

# Function to check if packages are installed
check_installation() {
    echo "Checking installation..."

    pkg_config_status=0
    for pkg in pugixml protobuf opencv4 libzmq; do
        if ! pkg-config --exists $pkg; then
            echo "Error: $pkg not found."
            pkg_config_status=1
        fi
    done

    # Check libtoml11
    if [ ! -f /usr/include/toml++/toml.h ]; then
        echo "Error: libtomlplusplus not found."
        pkg_config_status=1
    fi

    if [ $pkg_config_status -eq 0 ]; then
        echo "All packages installed successfully."
    else
        echo "Some packages are missing. Please check the installation logs."
        exit 1
    fi
}

# Detect the operating system
if [ -f /etc/os-release ]; then
    . /etc/os-release
else
    echo "Error: Unable to detect operating system."
    exit 1
fi

# Install packages based on the operating system
case $ID in
    debian|ubuntu|kali)
        echo "Detected Debian-based system."
        install_debian
        ;;
    fedora|rhel|centos)
        echo "Detected Red Hat-based system."
        install_redhat
        ;;
    *)
        echo "Error: Unsupported operating system."
        exit 1
        ;;
esac

# Check if all packages are installed
check_installation
