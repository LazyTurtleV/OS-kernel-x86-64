#!bin/bash

echo -e "\n----------------------------------------------------"
echo -e "Docker img build\n"
docker build buildenv -t osbuildenv

echo -e "\n----------------------------------------------------"
echo -e "An OS img build\n"
docker run --rm -it -v "$(pwd)":/root/env osbuildenv make build