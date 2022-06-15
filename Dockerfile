# syntax=docker/dockerfile:1
# Created by June Knauth (VMware) <june.knauth@gmail.com>, 2022-06-15
# Adapted from install.sh on github.com/knauth/trace-cruncher (branch debian)

FROM debian
# Install APT and pip dependencies
RUN apt update
RUN apt install build-essential git cmake libjson-c-dev libpython3-dev cython3 python3-numpy python3-pip flex valgrind binutils-dev pkg-config swig -y
RUN pip3 install --system pkgconfig GitPython
# Download trace-cruncher itself
RUN git clone https://github.com/vmware/trace-cruncher.git
WORKDIR trace-cruncher
# Build kernel tracing libs
RUN git clone https://git.kernel.org/pub/scm/libs/libtrace/libtraceevent.git &&\
cd libtraceevent && make && make install
RUN git clone https://git.kernel.org/pub/scm/libs/libtrace/libtracefs.git &&\
cd libtracefs && make && make install
RUN git clone https://git.kernel.org/pub/scm/utils/trace-cmd/trace-cmd.git &&\
cd trace-cmd && make && make install_libs
RUN git clone https://github.com/yordan-karadzhov/kernel-shark-v2.beta.git kernel-shark &&\
cd kernel-shark/build && cmake .. && make && make install
# Install trace-cruncher
RUN make && make install
# Run the unit tests
# RUN cd tests && python3 -m unittest discover .
