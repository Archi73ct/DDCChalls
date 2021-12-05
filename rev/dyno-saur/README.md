# Dyno-saurus

This folder contains the dyno-saurus reversing challenge.

# Flag(s) 
`DDC{78e8ba6134adc7e824239ebde29}`

# Domain name (OR) Link to challenge on nextcloud
`coolchallenge.hkn`

# Description(s) (THIS IS WHAT THE USER WILL SEE, YOU CAN USE MARKDOWN HERE)
1. (CHALLENGE NAME,REMEMBER TO ADD LINK OR DOMAIN)
- Proposed difficulty: Easy-medium
- Static analysis is not always the way.

# Prerequisites and Outcome

Prerequisites
- None

Outcome
- Learning that you can tell a good bit by analyzing the output of a black box.

# Solutions (FULL WRITEUP FOR EACH FLAG.)
The user has flag_out containing the "encrypted" flag.
This is actually just a scrambled string, using a substitution table like the
following:
```
let sbox = [17, 13, 20, 14, 3, 23, 28, 30, 21, 4, 18, 12, 0, 25, 10, 27, 22, 16, 8, 6, 19, 7, 11, 24, 29, 31, 9, 5, 26, 1, 2, 15];
```

The user is able to run the program to their liking, with whatever input they want.
As long as the input is 32-bytes long, the input will get scrambled.

Because the binary is a stripped rust binary, this will be very hard to reverse engineer.
The idea is that the smartest way is just to analyze the output and realize that it is a sbox.
Then by supplying it input in the form of 32 different chars, figuring out the internal sbox.

