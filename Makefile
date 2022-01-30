asm_src := $(shell find src -name *.asm)
asm_obj := $(patsubst src/%.asm, build/%.o, $(asm_src))

c_src := $(shell find src -name *.c)
c_obj := $(patsubst src/%.c, build/%.o, $(c_src))

kernel_src := $(shell find src/kernel -name *.c)
kernel_obj := $(patsubst src/kernel/%.c, build/%.o, $(kernel_c_src))

obj_files := $(c_obj) $(asm_obj)

$(kernel_obj): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/interface -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(c_obj): build/%.o : src/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/interface -ffreestanding $(patsubst build/%.o, src/%.c, $@) -o $@	

$(asm_obj): build/%.o : src/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/%.o, src/%.asm, $@) -o $@

.PHONY: build
build: $(obj_files) $(kernel_obj)
	mkdir -p dist && \
	x86_64-elf-ld -n -o dist/kernel.bin -T targets/linker.ld $(kernel_obj) $(obj_files) && \
	cp dist/kernel.bin targets/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/kernel.iso targets/iso/
