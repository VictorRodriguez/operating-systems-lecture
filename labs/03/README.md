# Lab 03 instructions

## Objective

Make the students get familiar with the forks using C as main programing
language. At the end of the practice students will understand

* How to use forks to create new processes in C code

# Requirements

* Linux machine, either a VM or a baremetal host
* GCC compiler (at least version 4.8)
* shell scripting
* git send mail server installed and configured on your Linux machine

## Instructions

* Clone the repository
* Go to operating-systems-lecture/labs/03
* Reading the examples from operating-systems-lecture/labs/03 create a terminal
* git commit -s -m 'ITESMID-homework-03'
* git send-mail -1

## Expected result:

Create a code that does this:

```
./my_terminal
osh> ls
failing    multiple-forks.c  shm_server    simple-fork.c       simple-shared	simple-shell.c	waitp-example.c
failing.c  shm_client	     shm_server.c  simple-fork-exec    simple-shared.c	test
Makefile   shm_client.c      simple-fork   simple-fork-exec.c  simple-shell	waitp-example
osh> pwd
/home/vrodri3/operating-systems-lecture/labs/03

```

## Please send the mail as git send mail:

```
$ git add my_terminal.c
$ git commit -s -m <STUDENT-ID>-homework-03
$ git send-email -1

```
Do some tests sending the mail to your personal account, if you get the mail,
then you can be sure I will get the mail

# Time to do the homework:

One week from the moment the mail is sent to students

