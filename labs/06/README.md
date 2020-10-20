# Lab 06 instructions

## Objective

Make the students familiar with mutual exclusion objects (mutex). A mutex is a program object that allows
multiple program threads to share the same resource, such as file access, but not simultaneously. 

# Requirements

* Linux machine, either a VM or a bare-metal host
* git send mail server installed and configured on your Linux machine

## Instructions

* Create a program that handles the coordination of 5 milk sellers. 
* Each seller can sell a random number of bottles ( from 1 to 200 )
* Each seller can sell to 5 costumers 
* The factory only can produce daily 1000 bottles
* Headquarter need to take care that sellers do not sell more than 1000 bottles

## Expected result:

Please send the patch with your code in C using MUTEX or SEMAPHORES ( op to you ) 

## Please send the mail as git send mail:

    ```
        $ git add round-robin.py
        $ git commit -s -m <STUDENT-ID>-homework-06
        $ git send-email -1

    ```
Do some tests sending the mail to your personal account, if you get the mail,
then you can be sure I will get the mail

# Time to do the homework:

One week from the moment the mail is sent to students
