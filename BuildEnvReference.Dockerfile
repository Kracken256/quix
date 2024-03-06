# Known good build environment for the project

FROM ubuntu:22.04

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Install dependencies
RUN apt update
RUN apt install -y cmake g++ llvm-15 llvm-14 libssl-dev
RUN cd /usr/include && ln -s llvm-15/llvm llvm && ln -s llvm-c-15/llvm-c llvm-c

# Build the project
RUN cd /app
RUN rm -rf build bin
RUN python3 ./build.py