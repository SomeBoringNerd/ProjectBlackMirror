FROM ubuntu:20.04

WORKDIR /ari-dev
RUN echo installation des dépendances
RUN export TERM=xterm # <- sensé résoudre un problème mais ça marche pas
RUN cd /ari-dev
RUN apt update &&\
    apt install -y g++ wget unzip build-essential iputils-ping
# installation de cmake    
RUN wget https://github.com/Kitware/CMake/releases/download/v3.26.0-rc5/cmake-3.26.0-rc5-linux-x86_64.sh -O cmake-build.sh &&\
    chmod +x cmake-build.sh &&\
    mkdir /opt/cmake &&\
    /bin/bash cmake-build.sh --prefix=/opt/cmake --skip-license &&\
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake

# compilation de opencv
#RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip &&\
#    unzip opencv.zip &&\
#    mkdir -p build &&\ 
#    cd build &&\
#    cmake  ../opencv-4.x &&\
#    cmake --build .
#RUN cd ../

RUN echo Compilation du logiciel serveur

ADD ./CMakeLists.txt /ari-dev

COPY ./src /ari-dev/src

RUN mkdir /ari-dev/build &&\
    cd /ari-dev/build &&\
    echo "Dossier actuel" &&\
    ls /ari-dev/&&\
    echo "dossier src" &&\
    ls /ari-dev/src/ &&\
    cmake /ari-dev/ &&\
    cmake --build /ari-dev/build &&\
    chmod +x /ari-dev/build/ARI-Server

CMD ["/ari-dev/build/ARI-Server"]
