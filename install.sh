#!/bin/bash
# trace-cruncher install script
# created by June Knauth (VMware) <june.knauth@gmail.com>, 2022-06-14
# Debian version for docker testing

# Install Dependencies
echo "---Installing APT Deps---"
apt update
apt install build-essential git cmake libjson-c-dev libpython3-dev cython3 python3-numpy python3-pip flex valgrind binutils-dev pkg-config swig -y
pip3 install --system pkgconfig GitPython

echo "---Building Other Deps---"
git clone https://git.kernel.org/pub/scm/libs/libtrace/libtraceevent.git/
cd libtraceevent
make
make install
cd ..
git clone https://git.kernel.org/pub/scm/libs/libtrace/libtracefs.git/
cd libtracefs
make
make install
cd ..
git clone https://git.kernel.org/pub/scm/utils/trace-cmd/trace-cmd.git
cd trace-cmd
make
make install_libs
cd ..
git clone https://github.com/yordan-karadzhov/kernel-shark-v2.beta.git kernel-shark
cd kernel-shark/build
cmake ..
make
make install
cd ../..

echo "---Installing trace-cruncher---"
make
make install

echo "---Running Unit Tests---"
cd tests
python3 -m unittest discover .
