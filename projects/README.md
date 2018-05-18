# Operating System Projects

## Kernel optimiation 

The idea of this project is to make a kernel change on scheduler/memory
managment and measure the performance impact using the phoronix benchmark tools 

More information of this can be found at: 

* operating-systems-lecture/projects/scheduler.md

At the end you will find information of where to change kernel scheduler
information or memory vm size , ie: 

* /proc/sys/kernel/sched_rt_period_us

Defines the time period to be considered one hundred percent of CPU bandwidth,
in microseconds ('us' being the closest equivalent to 'µs' in plain text). The
default value is 1000000µs, or 1 second.

* /proc/sys/kernel/sched_rt_runtime_us

Defines the time period to be devoted to running realtime threads, in
microseconds ('us' being the closest equivalent to 'µs' in plain text). The
default value is 950000µs, or 0.95 seconds.

## Kernel Driver

This project means to create a linux kernel driver to turn on a led on a
raspberry pi system. More information abotu kernel drivers can be found at : 

* https://github.com/VictorRodriguez/linux_device_drivers_tutorial

The idea is to make a drive that could reseive a syscall from usser space with: 

    * echo "on" > /dev/myled
    * echo "off" > /dev/myled


## Alan Turin Challange

The Turing test, developed by Alan Turing in 1950, is a test of a machine's
ability to exhibit intelligent behavior equivalent to, or indistinguishable
from, that of a human. Turing proposed that a human evaluator would judge
natural language conversations between a human and a machine designed to
generate human-like responses. 

The evaluator would be aware that one of the two partners in conversation is a
machine, and all participants would be separated from one another. The
conversation would be limited to a text-only channel such as a computer
keyboard and screen so the result would not depend on the machine's ability to
render words as speech.

If the evaluator cannot reliably tell the machine from the human, the machine
is said to have passed the test. The test does not check the ability to give
correct answers to questions, only how closely answers resemble those a human
would give.

The students should do this with a server-client application in C ussing the
inter process communication techiniques that we learn on the semester.

## Report and presentation 

Presentation shoudl be done in front of the team with a writen report made in
latex. The template for it is: 

* https://github.com/VictorRodriguez/operating-systems-lecture/blob/master/projects/report.tex

You have to send the mail with latex code and pdf generated. 


