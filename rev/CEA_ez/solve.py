from pwn import *
import struct
import ctypes
# https://gist.github.com/twheys/4e83567942172f8ba85058fae6bfeef5
def _vec2str(vector, l=4):
    """
    Decodes a vector to a binary string.  The string is composed by chunks of size l for every two elements in the 
    vector.
    
    Compliment of _str2vec.
        
    :param vector:
        An even-length vector.
    :param l:
        The length of the chunks to compose the returned string.  This should match the value for l used by _str2vec.
        If the value used is smaller, than characters will be lost.
    :return:
    """
    return bytes((element >> 8 * i) & 0xff
                 for element in vector
                 for i in range(l)).replace(b'\x00', b'')
def _decipher(v, k):
    """
    TEA decipher algorithm.  Decodes a length-2 vector using a length-4 vector as a length-2 vector.
    
    Compliment of _encipher.
    :param v:
        A vector representing the information to be deciphered.  *Must* have a length of 2.
    :param k:
        A vector representing the encryption key.  *Must* have a length of 4.
    :return:
        The original message.
    """

    y, z = [ctypes.c_uint32(x)
            for x in v]
    sum = ctypes.c_uint32(3585596896)
    delta = 0xdeadbeef

    for n in range(32, 0, -1):
        z.value -= (y.value << 4) + k[2] ^ y.value + sum.value ^ (y.value >> 5) + k[3]
        y.value -= (z.value << 4) + k[0] ^ z.value + sum.value ^ (z.value >> 5) + k[1]
        sum.value -= delta

    return [y.value, z.value]


# output_raw is just the `xxd -r output > output_raw` product...
with open('output_raw', 'rb') as f:
    enc = f.read()
    # Get only the bytes that matter, minus the last newline
    enc = enc.split(b': ')[1][:-1]
    print(hexdump(enc))
    print(len(enc))
    l = []
    k = [0x1337beef, 0xfa11b33d, 0xcafebabe, 0x99669966];
    for t in range(0, 32, 8):
        l.append([struct.unpack_from('<I', enc[t:])[0], struct.unpack_from('<I', enc[t+4:])[0]])

    dec = []
    for touple in l:
        dec.append(_vec2str(_decipher(touple,k)))
    print(b''.join(dec))