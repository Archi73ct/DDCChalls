# baby bof

This folder contains the easy_bof pwn challenge.

# Flag(s) 
`DDC{Smashing_The_Stack_For_Fun_And_Profit}`

# Domain name (OR) Link to challenge on nextcloud
`babyheap.hkn:1024`

# Description(s) (THIS IS WHAT THE USER WILL SEE, YOU CAN USE MARKDOWN HERE)
1. baby_heap
- Proposed difficulty: hard
- Stack exploits are out of fashion, let's be honest, the future is dynamic memory.

# Prerequisites and Outcome

Prerequisites
- Knowledge about libc's dynamic memory allocator
- Knowledge about networking and communicating with a remote server

Outcome
- This will teach tchache poisoning

# Solutions (FULL WRITEUP FOR EACH FLAG.)
The user is presented with a menu allowing for 4 options.
Malloc, free, read, write.
By abusing the lack of checking on the tchache, the user can cause ptmalloc2
to return an arbitrary pointer.

This can be done through the following sequence of allocations:
```
a = malloc
b = malloc
free a
free b
// now the tcache freelist looks like the following
// b -> a
// use the uaf to change b's forward pointer to a
write b 0x41414141
// b -> [0x41414141]
malloc a
malloc b
// b is now the pointer 0x41414141
```
By controlling the pointer returned by malloc, one can point it to the flag
loaded into memory at 0x4040c0.

Because of the way ptmalloc2 works when you malloc the second last element in the tcache
the bk ptr will be set to 0x0.
Essentially this will allow for only leaking 8 bytes of the flag.
By just wrapping the previous operations in a loop one can leak the flag 8
bytes at a time.

Solution in `POC.py`.
