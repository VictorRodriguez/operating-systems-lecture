all:
	gcc cat_sys_call.c -o cat_sys_call
	gcc homework_cat.c -o homework_cat

download:
	git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/torvalds/linux.git

build-kernel:
	cd linux
	make -j4

clean:
	rm -rf cat_sys_call
	rm -rf homework_cat
