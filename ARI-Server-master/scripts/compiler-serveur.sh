#!/bin/sh
clear
if [ "$EUID" -ne 0 ]
  then echo "Ce script doit être executé en tant que root"
  exit
fi

cd ../build
cmake --build .
cp ARI-Server ../Exec_env
cd ../Exec_env
./ARI-Server
rm ARI-Server