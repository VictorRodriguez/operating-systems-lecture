/*
 * Create a program that open a file like 
 *
 * gcc cat.c -o cat
 *
 * ./cat 
 *
 * You might find some help here: 
 *
 *  http://man7.org/linux/man-pages/man2/open.2.html
 *
 * https://www.ibm.com/developerworks/community/blogs/\
 *  58e72888-6340-46ac-b488-d31aa4058e9c/entry/understanding_linux_open_system_call?lang=en
 *
 * 
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/stat.h>
#define STDOUT 1

typedef int File;

int main(int argc, char const *argv[]) {
	File fileOrigin;
	ssize_t readSize;
	const int bufSize = 512;
	char buffer[bufSize]; //Buffer of 512 character
	 //open(const char* path, int flags)
	if ((fileOrigin = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "file open failed, error = %s\n", errno);
		exit(1);
	}

	while ((readSize = read(fileOrigin, &buffer, bufSize)) > 0) {
		if (write(STDOUT, &buffer, readSize) < 0) {
			fprintf(stderr, "write to stdout failed, error = %s\n", errno);
			exit(1);
		}
	}

	close(fileOrigin);
	return 0;
}