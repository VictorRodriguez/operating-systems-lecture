all: download build-kernel

download:
	git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/torvalds/linux.git

build-kernel:
	cd linux
	make -j4	
