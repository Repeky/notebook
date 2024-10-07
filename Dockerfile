FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \
    qt5-default \
    qtbase5-dev \
    qtbase5-dev-tools \
    qtchooser \
    qtscript5-dev \
    git \
    cmake \
    g++

RUN apt-get install -y libx11-dev

WORKDIR /usr/src/app

COPY . .

RUN qmake && make

CMD ["./my_qt_app"]
