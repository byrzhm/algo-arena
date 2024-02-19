# use docker build: docker build -t algo-arena .
FROM ubuntu:latest

# dev-tools
RUN apt-get update && \
    apt-get install -y build-essential git llvm clang lldb cmake

# openssh
RUN apt-get install -y openssh-server

# google benchmark
RUN echo "************************ google benchmark ************************"
RUN git clone https://github.com:google/benchmark
RUN mkdir -p  /tmp/benchmark/build && cd /tmp/benchmark/build
WORKDIR "/tmp/benchmark/build"
RUN cmake -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ..\
    && cmake --build . --parallel && cmake --install .
WORKDIR "/"
RUN rm -rf /tmp/benchmark

# googletest
RUN echo "************************ googletest ************************"
RUN git clone https://github.com:google/googletest
RUN mkdir -p  /tmp/googletest/build && cd /tmp/googletest/build
WORKDIR "/tmp/googletest/build"
RUN cmake -DBUILD_SHARED_LIBS=ON .. && cmake --build . --parallel && cmake --install .
WORKDIR "/"
RUN rm -rf /tmp/googletest
