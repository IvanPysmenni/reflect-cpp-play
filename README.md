# reflect-cpp-play

This project was created for practise with reflect-cpp library.
Inspired by this issue https://github.com/maxsharabayko/srt-xtransmit/issues/6

## Build
```
sudo apt install cmake gcc g++ libyaml-cpp0.8 libyaml-cpp-dev
mkdir -p build
cd build
cmake ..
make
```

## Run
```
build/bin/reflec-cpp-play
```

## Docker
### Build
```
docker build --rm -t reflect-cpp-play .
```

### Run
```
docker run --rm -it -v ${PWD}/test_files:/app/test_files reflect-cpp-play
```
