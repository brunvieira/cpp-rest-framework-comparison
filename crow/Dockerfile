FROM debian:latest

RUN apt-get -qq update && apt-get -qq upgrade
RUN apt-get -qq install cmake libboost-all-dev=1.62.0.1 libtcmalloc-minimal4 clang && \
    ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so

ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++
ENV PORT=18001

WORKDIR  /usr/src/crow
COPY . .
RUN rm -rf ./build/*

WORKDIR /usr/src/crow/build
RUN cmake .. && make

CMD ["cpp_comparison_crow"]