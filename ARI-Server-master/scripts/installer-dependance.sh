if [ "$EUID" -ne 0 ]
  then echo "Ce script doit être executé en tant que root"
  exit
fi

# met a jour les repos APT et installe des dependances de build
apt update
apt install -y g++ wget unzip build-essential iputils-ping xterm ffmpeg libtesseract-dev libblis-pthread-dev

# compile cmake 3.26 car la version APT est la 3.7
wget https://github.com/Kitware/CMake/releases/download/v3.26.0-rc5/cmake-3.26.0-rc5-linux-x86_64.sh -O cmake-build.sh

chmod +x /cmake-build.sh
mkdir /opt/cmake
/bin/bash cmake-build.sh --prefix=/opt/cmake --skip-license
ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake

# compile OpenCV 4 (prend une heure sur mon vieux laptop, prendra surement plus longtemps en prod)

wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip
mkdir -p build

cd build
cmake  ../opencv-4.x
cmake --build .

echo "Le logiciel est prêt a être compilé !"
echo "Lancez le script \"compiler_serveur\""