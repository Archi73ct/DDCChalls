# CEA
This repo contains a challenge meant for more experienced reverse-engineers.
The challenge is a shared library file, and a output file.
The player must reverse-engineer the shared library file.

# Flag(s) 
`DDC{Wanna_drink_som_custom_tea?}`

# Domain name (OR) Link to challenge on nextcloud
`https://nextcloud.ntp-event.dk:8443/s/aamFtgG9dbiWeF5/download/cea_ez.zip`

# Description(s) (THIS IS WHAT THE USER WILL SEE, YOU CAN USE MARKDOWN HERE)
## CEA
This is a custom library recovered from a device.
It only implements the encryption function, we need you to create the decryption function.
The `output` file contains a hexdump of the secret message we intercepted from the device.
The algorithm seems to be quite _tiny_.
https://nextcloud.ntp-event.dk:8443/s/aamFtgG9dbiWeF5/download/cea_ez.zip

# Prerequisites and Outcome
A good understanding of x86 assembly.


# Solutions (FULL WRITEUP FOR EACH FLAG.)

## Flag 1
This challenge is a classic reversing challenge.
The original C file contains a modified version of TEA, https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm

One needs to realize the TEA algorithm by getting the name hint, and examining the assembly using a reverse engineering tool.

The decompilation of the `encrypt` function looks like this:
```c
void encrypt(char *__block,int __edflag)

{
  int *piVar1;
  undefined4 in_register_00000034;
  uint local_18;
  int local_14;
  uint local_10;
  uint local_c;
  
  piVar1 = (int *)CONCAT44(in_register_00000034,__edflag);
  local_c = *(uint *)__block;
  local_10 = *(uint *)(__block + 4);
  local_14 = 0;
  for (local_18 = 0; local_18 < 0x20; local_18 = local_18 + 1) {
    local_14 = local_14 + -0x21524111;
    local_c = local_c + (piVar1[1] + (local_10 >> 5) ^
                        local_10 * 0x10 + *piVar1 ^ local_14 + local_10);
    local_10 = local_10 +
               (piVar1[3] + (local_c >> 5) ^ local_c * 0x10 + piVar1[2] ^ local_14 + local_c);
  }
  *(uint *)__block = local_c;
  *(uint *)(__block + 4) = local_10;
  return;
}
```
The original function from the wiki page of TEA looks like the following:
```c
void encrypt (uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0xdeadbeef;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}
```
With the exeption of the `delta` variable having been changed.

This is the only editing one needs to do to the decryption function to adapt it.
With the addition of editing sum to match `(0xdeadbeef<<5)&0xffffffff`.
```c
void decrypt (uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=3585596896, i;  /* set up; sum is (delta << 5) & 0xFFFFFFFF */
    uint32_t delta=0xdeadbeef;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}
```

The key used for TEA can be easily spotted in `main` as the following assignment used for the encryption function:

```
  local_38 = 0x1337beef;
  local_34 = 0xfa11b33d;
  local_30 = 0xcafebabe;
  local_2c = 0x99669966;
```

You can then implement decryption as such:
```
for (int i = 0; i <= 4; i++) {
        decrypt(&p[i], k);
}
```
where p is a pointer to the encrypted string as a uint64_t *.

