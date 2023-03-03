FROM ubuntu:20.04

WORKDIR /ari-dev
RUN echo installation des dépendances

RUN cd /ari-dev
RUN apt update &&\
    apt install -y g++ wget unzip build-essential iputils-ping
RUN wget https://github.com/Kitware/CMake/releases/download/v3.26.0-rc5/cmake-3.26.0-rc5-linux-x86_64.sh -O cmake-build.sh

RUN ls

RUN chmod +x /ari-dev/cmake-build.sh &&\
    mkdir /opt/cmake &&\
    /ari-dev/cmake-build.sh --prefix=/opt/cmake --skip-license &&\
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake &&\
    cmake --version
# RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip &&\
#    unzip opencv.zip &&\
#    mkdir -p build &&\ 
#    cd build &&\
#    cmake  ../opencv-4.x &&\
#    cmake --build .
#RUN cd ../

RUN echo Compilation du logiciel

ADD ./CMakeLists.txt /ari-dev
COPY ./src /ari-dev/src
RUN mkdir /ari-dev/build &&\
    cd /ari-dev/build &&\
    echo "Dossier actuel" &&\
    ls /ari-dev/&&\
    echo "dossier src" &&\
    ls /ari-dev/src/ &&\
    cmake /ari-dev/ &&\
    cmake --build /ari-dev/build

CMD ["/ari-dev/build/ARI-Server"]

