### Build
You can build an image in two ways: manually or automated.

Run a shell script ci.sh in order to start automated build. 

In order to manually build iso image of OS execute the following commands: 
>1. docker build buildenv -t osbuildenv - build an environment image 
>2. docker run --rm -it -v "${pwd}:/root/env" osbuildenv - run build environment
>3. make build - build an OS image inside build environment

### Execution
A built image can be run with qemu using command:
qemu-system-x86_64 -cdrom dist/kernel.iso