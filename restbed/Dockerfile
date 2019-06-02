FROM debian:latest

RUN apt-get update -qq && apt-get install -qq clang git cmake libssl-dev openssl

ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

RUN mkdir /tmp/build
WORKDIR /tmp/build

RUN git clone --recursive https://github.com/corvusoft/restbed.git restbed \
&& cd restbed && mkdir build && cd build && cmake -DBUILD_SSL=NO -DBUILD_TESTS=NO -DCMAKE_INSTALL_PREFIX=/usr/local .. \
&& make -j 5 && make install

RUN git clone https://github.com/Tencent/rapidjson.git rapidjson && cd rapidjson \
&& git submodule update --init  && mkdir build && cd build && cmake .. && make && make install

WORKDIR /usr/src/restbed
COPY . .
RUN rm -rf ./build/*

WORKDIR /usr/src/restbed/build
RUN cmake .. && make

ENV PORT=18005
CMD ["cpp_comparison_restbed"]