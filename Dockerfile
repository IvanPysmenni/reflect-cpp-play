FROM ubuntu:24.04 AS builder

WORKDIR /usr/src

ENV DEBIAN_FRONTEND=noninteractive

COPY . .

RUN apt update -y && apt install -y cmake gcc g++ libyaml-cpp0.8 libyaml-cpp-dev
RUN mkdir -p build && cd build && cmake .. && make

FROM ubuntu:24.04 AS runner

WORKDIR /app

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update -y && apt install -y libyaml-cpp0.8

COPY --from=builder /usr/src/build/bin/reflect-cpp-play .

ENTRYPOINT [ "./reflect-cpp-play" ]
