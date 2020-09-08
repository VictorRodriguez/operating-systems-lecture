# Lab 02 instructions

## Objective

Make the students get familiar with the system calls using C as main programing
language. At the end of the practice students will understand

* How to use a system call from C code
* How to use a generic syscall and SYSNO from C code
* How to create a useful binary such as chmod/cat

# Requirements

* Linux machine, either a VM or a baremetal host
* GCC compiler (at least version 4.8)
* shell scripting
* git send mail server installed and configured on your Linux machine

## Instructions

* Clone the repository
* Go to operating-systems-lecture/labs/02
* Reading the examples from operating-systems-lecture/labs/02/cat/ directory
and chmod seeing in class please create one for chown. chown() changes the
ownership of the file specified by path.
* git commit -s -m 'ITESMID-homework-02'
* git send-mail -1

## Expected result:

Create a code that does this:

```
./chown file.txt <usr>
```

## Please send the mail as git send mail:

```
$ git add hello.c
$ git commit -s -m <STUDENT-ID>-homework-01
$ git send-email -1

```
Do some tests sending the mail to your personal account, if you get the mail,
then you can be sure I will get the mail

# Time to do the homework:

One week from the moment the mail is sent to students

