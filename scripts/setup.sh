#!/bin/bash

# Function to install packages on Debian-based systems
install_debian() {
    sudo apt-get update
    sudo apt-get install -y libpugixml-dev libprotobuf-dev libopencv-dev libzmq3-dev cmake g++ git

    # Install libtoml11 from source
    git clone https://github.com/marzer/tomlplusplus.git
    cd tomlplusplus
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
    sudo cmake --build build --target install
    cd ..
    rm -rf tomlplusplus
}

# Function to install packages on Red Hat-based systems
install_redhat() {
    sudo yum install -y epel-release
    sudo yum install -y pugixml-devel protobuf-devel opencv-devel cppzmq-devel cmake gcc-c++ git

    # Install libtoml11 from source
    git clone https://github.com/ToruNiina/toml11.git
    cd toml11
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
    sudo cmake --build build --target install
    cd ..
    rm -rf toml11
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
