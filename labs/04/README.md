# Lab 04

## Objective:
Develop the skills to program an application that solves a problem using threads

# Requirements

* Linux machine, either a VM or a baremetal host
* GCC compiler (at least version 4.8)
* shell scripting
* git send mail server installed and configured on your Linux machine

## Instructions

* Clone the repository
* Go to operating-systems-lecture/labs/04
* Read examples from operating-systems-lecture/labs/04
* Calculate the value of Pi ( 3.141596 ) using this algorithm:

```

npoints = 10000
circle_count = 0

do j = 1,npoints
  generate 2 random numbers between 0 and 1
  xcoordinate = random1
  ycoordinate = random2
  if (xcoordinate, ycoordinate) inside circle
  then circle_count = circle_count + 1
end do

PI = 4.0*circle_count/npoints

```

more info: https://computing.llnl.gov/tutorials/parallel_comp/ )

Please send the code as a patch and include in the comments of the code (at
the top), the results in terms of a link to a graph that shows the speed
improvements, how much time does it take to calculate pi with 1 thread, 2
threads 4 threads 8 threads and 16 threads?

In order to measure the time you can use the time command from Linux

https://www.lifewire.com/command-return-time-command-4054237

or you can code it:

http://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/

the link could be to a google documents pdf. please create good graphs:

	* X axis = number of threads
	* Y axis = speed in time (make the scale start in 0)
	* Title

* git commit -s -m 'ITESMID-homework-03'
* git send-mail -1

## Expected result:


```
./pi_calculation <number of threads>
3.151596...
```

## Please send the mail as git send mail:

```
$ git add my_terminal.c
$ git commit -s -m <STUDENT-ID>-homework-04
$ git send-email -1

```
Do some tests sending the mail to your personal account, if you get the mail,
then you can be sure I will get the mail

# Time to do the homework:

One week from the moment the mail is sent to students

