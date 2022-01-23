x86_64_asm_src := $(shell find src -name *.asm)
x86_64_asm_obj := $(patsubst src/%.asm, build/%.o, $(x86_64_asm_src))

$(x86_64_asm_obj): build/%.o : src/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/%.o, src/%.asm, $@) -o $@

.PHONY: build
build-x86_64: $(x86_64_asm_obj)
	mkdir -p dist && .
	x86_64-elf-ld -n -o dist/kernel.bin -T targets/linker.ld $(x86_64_asm_obj) && \
	cp dist/kernel.bin targets/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/kernel.iso targets/iso/
