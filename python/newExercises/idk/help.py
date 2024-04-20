#!/usr/bin/env python3
from pwn import *
import binascii
import curses
from pwn import *
import sys
import pyperclip

x = p32(int("0x89", 16))

sys.stdout.buffer.write(b'\x89\n')
print('\x89')
