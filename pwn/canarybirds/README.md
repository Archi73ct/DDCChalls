# Canarybirds

This folder contains the canarybirds challenge

# Flag(s) 
`DDC{canarybirds_g0_brrrrrrrrrrrrr}`

# Domain name (OR) Link to challenge on nextcloud
`canaries.hkn:1024`

# Description(s) (THIS IS WHAT THE USER WILL SEE, YOU CAN USE MARKDOWN HERE)
1. Canarybirds <3
- Proposed difficulty: Easy-medium
- Canarybirds, they sing when bad stuff is brewing
- `nc canarybirds.hkn 1024`

# Prerequisites and Outcome

Prerequisites
- Knowledge about buffer overflows
- Knowledge about stack canaries
- Knowledge about networking and communicating with a remote server

Outcome
- Knowledge about stack canaries

# Solutions (FULL WRITEUP FOR EACH FLAG.)
By reversing the challenge one can find the `getflag()` function.
This function will open and print the flag, so the goal is to redirect execution to this function.
The program asks for the lenth of the name of the user, as well as the name itself.
This is then printed. But one can realize that the length entered can be way longer than the buffer
containing the username. By using this leak, the user can leak the stack cookie, and gain IP control
using the buffer overflow in the following message.

POC.py is the solution.