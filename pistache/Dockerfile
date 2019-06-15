FROM debian:latest

RUN apt-get update -qq && apt-get install -qq clang git cmake libssl-dev openssl

RUN mkdir /tmp/build
WORKDIR /tmp/build

ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

RUN git clone https://github.com/oktal/pistache.git pistache && cd pistache \
&& git submodule update --init  && mkdir build && cd build \
&& cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release .. \
&& make && make install

RUN git clone https://github.com/Tencent/rapidjson.git rapidjson && cd rapidjson \
&& git submodule update --init  && mkdir build && cd build && cmake .. && make && make install

WORKDIR /usr/src/pistache
COPY ./pistache/src ./src
COPY ./pistache/CMakeLists.txt .
COPY ./cpputils src/cpputils

WORKDIR /usr/src/pistache/build
RUN cmake .. && make

ENV PORT=18004
CMD ["cpp-comparison-pistache"]

