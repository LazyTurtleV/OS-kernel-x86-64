int main(struct multiboot *_mboot_ptr) {
    kernel_main();
    return 0xDEADBABA;
}