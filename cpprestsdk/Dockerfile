FROM debian:latest

RUN apt-get update && apt-get install -qq g++ git libboost-atomic-dev \
libboost-thread-dev libboost-system-dev libboost-date-time-dev libboost-regex-dev \
libboost-filesystem-dev libboost-random-dev libboost-chrono-dev cmake zlib1g-dev \
libboost-serialization-dev libwebsocketpp-dev openssl libssl-dev ninja-build

RUN mkdir /tmp/build
WORKDIR /tmp/build

RUN  git clone https://github.com/Microsoft/cpprestsdk.git casablanca && cd casablanca \
&& mkdir build && cd build \
&& cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Release && ninja && ninja install

WORKDIR /usr/src/cpprestsdk
COPY . .
RUN rm -rf ./build/*

WORKDIR /usr/src/cpprestsdk/build
RUN cmake .. && make

ENV PORT=18002