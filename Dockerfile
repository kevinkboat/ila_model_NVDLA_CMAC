##
## Build ILA models and their SystemC simulator (from 3la-integrate)
##
FROM ubuntu:bionic as ilabuilder

# var
ENV WORK_ROOT /root
ENV VIRTUAL_ENV 3laEnv
ENV BUILD_PREF $WORK_ROOT/$VIRTUAL_ENV
RUN mkdir -p $BUILD_PREF

# need to make this if no virtualenv
RUN mkdir -p $BUILD_PREF/bin

# required packages
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install --yes --no-install-recommends \
    bison \
    build-essential \
    ca-certificates \
    flex \
    gcc-5 \
    g++-5 \
    git \
    libz3-dev \
    openssh-client \
    python3 \
    python3-pip \
    wget \
    z3 \
    && rm -rf /var/lib/apt/lists/*

# setup local build via virtualenv
#WORKDIR $WORK_ROOT
#RUN pip3 install virtualenv
#RUN virtualenv $VIRTUAL_ENV

# cmake
ENV CMAKE_DIR $WORK_ROOT/cmake-3.19.2-Linux-x86_64
WORKDIR $WORK_ROOT
RUN wget https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.tar.gz
RUN tar zxvf cmake-3.19.2-Linux-x86_64.tar.gz

# SystemC
ENV SYSC_DIR $WORK_ROOT/systemc-2.3.3
WORKDIR $WORK_ROOT
RUN wget https://accellera.org/images/downloads/standards/systemc/systemc-2.3.3.tar.gz
RUN tar zxvf systemc-2.3.3.tar.gz
WORKDIR $SYSC_DIR
RUN mkdir -p build
WORKDIR $SYSC_DIR/build
RUN $CMAKE_DIR/bin/cmake $SYSC_DIR -DCMAKE_INSTALL_PREFIX=$BUILD_PREF -DCMAKE_CXX_STANDARD=11 && \
    make -j"$(nproc)" && \
    make install 

# boost
ENV BOOST_DIR $WORK_ROOT/boost_1_75_0
WORKDIR $WORK_ROOT
RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.75.0/source/boost_1_75_0.tar.gz
RUN tar zxvf boost_1_75_0.tar.gz
WORKDIR $BOOST_DIR
RUN ./bootstrap.sh --prefix=$BUILD_PREF
RUN ./b2 --with-chrono --with-math --with-system install -j"$(nproc)" || :

# ILAng
ENV ILANG_DIR $WORK_ROOT/ILAng
WORKDIR $WORK_ROOT
RUN git clone --depth=1 https://github.com/PrincetonUniversity/ILAng.git $ILANG_DIR
WORKDIR $ILANG_DIR
# Branch: ilator_opt
RUN git fetch origin ilator_opt && git checkout 7de6fd9f78999845644326e462bcb723daf60b6f
RUN mkdir -p build 
WORKDIR $ILANG_DIR/build
# RUN $CMAKE_DIR/bin/cmake $ILANG_DIR -DCMAKE_INSTALL_PREFIX=$BUILD_PREF && \
RUN $CMAKE_DIR/bin/cmake $ILANG_DIR && \
    make -j"$(nproc)" && \
    make install 
