box = [17, 13, 20, 14, 3, 23, 28, 30, 21, 4, 18, 12, 0, 25, 10, 27, 22, 16, 8, 6, 19, 7, 11, 24, 29, 31, 9, 5, 26, 1, 2, 15]
flag = []

with open("flag_out", "r") as f:
    enc = f.read()
    for t in range(len(enc)):
        flag.append(enc[box.index(t)])
print(''.join(flag))

