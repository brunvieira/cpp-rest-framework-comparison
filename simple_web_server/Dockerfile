FROM debian:latest

RUN apt-get update -qq && apt-get install -qq clang git cmake libssl-dev openssl \
libboost-system-dev libboost-filesystem-dev libboost-thread-dev

ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

RUN mkdir /tmp/build
WORKDIR /tmp/build

RUN git clone https://gitlab.com/eidheim/Simple-Web-Server.git simple-web-server \
&& cd simple-web-server && mkdir build && cd build && cmake .. && make && make install

RUN git clone https://github.com/Tencent/rapidjson.git rapidjson && cd rapidjson \
&& git submodule update --init  && mkdir build && cd build && cmake .. && make && make install

WORKDIR /usr/src/simple_web_server
COPY . .
RUN rm -rf ./build/*

WORKDIR /usr/src/simple_web_server/build
RUN cmake .. && make

ENV PORT=18003
CMD ["cpp-comparison-simple-web-server"]