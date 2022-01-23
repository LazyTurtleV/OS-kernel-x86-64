#!bin/bash

#setup an image for build env
docker build buildenv -t osbuildenv

#build an OS image in build env
docker run --rm -it -v "${pwd}:/root/env" osbuildenv
make build
exit

"H:\ProgrammingSoft\qemu-system-x86_64" -cdrom dist/x86_64/kernel.iso