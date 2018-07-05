#!/usr/bin/env bash

# Make the script fail if any command in it fail
set -e

python3.5 -m venv env --without-pip
source env/bin/activate
python --version
wget https://bootstrap.pypa.io/get-pip.py
python get-pip.py
pip install cvra-packager~=1.0.0
pip install msgpack-python==0.4.8 PyYAML==3.11

echo "Installing protobuf..."
pushd /
wget https://github.com/google/protobuf/releases/download/v3.5.1/protoc-3.5.1-linux-x86_64.zip
unzip protoc*.zip
popd
pip install --upgrade protobuf

pushd lib/uavcan/libuavcan/dsdl_compiler/pyuavcan/
python setup.py install
popd

pushd lib/uavcan/libuavcan/dsdl_compiler/
python setup.py install
popd

if [ "$BUILD_TYPE" == "build" ]
then
    wget https://launchpad.net/gcc-arm-embedded/4.9/4.9-2014-q4-major/+download/gcc-arm-none-eabi-4_9-2014q4-20141203-linux.tar.bz2
    tar -xf gcc-arm-none-eabi-4_9-2014q4-20141203-linux.tar.bz2
fi

if [ "$BUILD_TYPE" == "tests" ]
then
    # Install cpputest
    pushd ..
    wget "https://github.com/cpputest/cpputest/releases/download/v3.8/cpputest-3.8.tar.gz" -O cpputest.tar.gz
    tar -xzf cpputest.tar.gz
    cd cpputest-3.8/
    ./configure --prefix=$HOME/cpputest
    make
    make install
    popd
fi
