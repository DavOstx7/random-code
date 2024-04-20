#!/usr/bin/env python3


def RecHex(string, index):
	if(index == -1):
		return '1' + string
	if(string[index] == 'F'):
		arr = list(string)
		arr[index] = '0'
		string = "".join(arr)
		return RecHex(string, index - 1)

	arr = list(string)
	arr[index] = chr(ord(arr[index])+1)
	string = "".join(arr)
	return string

def NextHex(string):
	if(string[0] == '0' and string[1] == 'x'):
		string = string[2:]
		string = RecHex(string, len(string) - 1)
		return '0x' + string
	return RecHex(string, len(string) - 1)

print(NextHex('0x11'))