# Lab 05 instructions

## Objective

Make the students familiar with Round-robin scheduling 

# Requirements

* Linux machine, either a VM or a baremetal host
* git send mail server installed and configured on your Linux machine

## Instructions

Round-robin (RR) is one of the algorithms employed by process and network schedulers in computing.
As the term is generally used, time slices (also known as time quanta) are assigned to each process 
in equal portions and in circular order, handling all processes without priority (also known as cyclic executive). 
Round-robin scheduling is simple, easy to implement, and starvation-free. 

In this lab we will create a tool that graph quantum time vs average turn around time ( every context switch will cost 2 ut)
of a RR algorithm. You can use as a reference the example created by the profesor and create your own RR algorithm 

## Expected result:

Please send the patch with your own code in python and a link to the graph on the top comments
Despite teh fact that I provide a reference of the RR algorithm is necesary that you create your own

## Please send the mail as git send mail:

    ```
        $ git add round-robin.py
        $ git commit -s -m <STUDENT-ID>-homework-04
        $ git send-email -1

    ```
Do some tests sending the mail to your personal account, if you get the mail,
then you can be sure I will get the mail

# Time to do the homework:

One week from the moment the mail is sent to students

