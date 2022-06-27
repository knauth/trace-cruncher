# syntax=docker/dockerfile:1
# SPDX-License-Identifier: LGPL-2.1
# Copyright (C) 2022, VMware Inc, June Knauth <june.knauth@gmail.com>

FROM debian
# Install APT and pip dependencies
RUN apt update && apt install build-essential git cmake libjson-c-dev libpython3-dev cython3 python3-numpy python3-pip flex valgrind binutils-dev pkg-config swig -y && pip3 install --system pkgconfig GitPython
# Download trace-cruncher itself
RUN git clone -b fix-ci-script https://github.com/knauth/trace-cruncher.git
WORKDIR trace-cruncher
# Build kernel tracing libs
RUN scripts/date-snapshot/date-snapshot.sh -f scripts/date-snapshot/repos
RUN cd libtraceevent && make && make install
RUN cd libtracefs && make && make install
RUN cd trace-cmd && make && make install_libs
RUN cd kernel-shark/build && cmake .. && make && make install
# Install trace-cruncher
RUN make && make install
