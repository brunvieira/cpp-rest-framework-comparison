FROM alpine:3.7

RUN apk add --no-cache clang alpine-sdk git bash cmake
RUN apk add boost-dev=1.62.0-r5

ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++
ENV PORT=18001