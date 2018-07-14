# Valgrin training 

Although C is a very useful and powerful language, it can be hard to debug. A
particular problem that you have probably encountered at some point is memory
errors. We have already talked about gdb, which can be a helpful resource if
your program consistently crashes or outputs a wrong result. However, sometimes
you suspect that the problem you are having is due to a memory error, but it
does not cause a segfault and you do not want to set a lot of breakpoints and
step through in gdb. Another common problem you might encounter is a program
with a memory leak: somewhere, you call malloc but never call free. Valgrind is
a program that will help you fix both problems.


Training examples from http://pages.cs.wisc.edu/~bart/537/valgrind.html
