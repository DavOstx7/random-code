#!/usr/bin/env python3

import string
import codecs
import enchant

# to encrypt we add <key>, to decrypt we sub <key> OR to encrypt we sub (26 - <key>), to decrypt we add (<26 - <key>)
# since the key of 13 is equal to 26//2, to encrypt or decrypt we use the same method.

def ROT13A(s):
	new = ""
	for char in s:
		if(char in string.ascii_lowercase):
			c = ord(char)
			c+=13
			c-=ord('a')
			c = c % 26
			c += ord('a')
			new+=chr(c)

		elif(char in string.ascii_uppercase):
			c = ord(char)
			c+=13
			c-=ord('A')
			c = c % 26
			c += ord('A')
			new+=chr(c)

		else:
			new+=char

	print(new)

#print("ROT13A: ")
#ROT13A("Hello World")

def ROT13B(s):
	new = ""
	for char in s:
		if(char not in string.ascii_lowercase and char not in string.ascii_uppercase):
			new+=char
			continue

		c = ord(char)
		c+= 13

		if(c > ord('a')): #important to check lowercase, because its ascii value is higher, if we used c>ord('A') it will fit both uppercase and lowercase
			if(c > ord('z')):
				c-=26
		else:
			if(c > ord ('Z')):
				c-=26

		new+= chr(c)

	print(new)

#print("ROT13B: ")
#ROT13B("Hello World")

def ROT13C(s):
	new = ""
	for char in s:
		if(char in string.ascii_lowercase):
			i = string.ascii_lowercase.index(char)
			i = (i + 13) % 26
			new += string.ascii_lowercase[i]
			continue
		elif (char in string.ascii_uppercase):
			i = string.ascii_uppercase.index(char)
			i = (i + 13) % 26
			new += string.ascii_uppercase[i]
			continue
		new += char
	print(new)

#print("ROT13C: ")
#ROT13C("Hello World")

def ROT13D(s):
	print(codecs.encode(s, 'rot13'))

#print("ROT13D: ")
#ROT13D("Hello World")

def check_text(text):
	text = text.split(" ")
	d = enchant.Dict("en_US")
	counter = 0
	for word in text:
		if(d.check(word) == True):
			counter+=1
	return counter

def cipher(text, key):
	new = ""
	for char in text:
		if(char in string.ascii_lowercase):
			c = ord(char)
			c+=key
			c-=ord('a')
			c = c % 26
			c += ord('a')
			new+=chr(c)

		elif(char in string.ascii_uppercase):
			c = ord(char)
			c+=key
			c-=ord('A')
			c = c % 26
			c += ord('A')
			new+=chr(c)

		else:
			new+=char

	return new

def decipher(ciphertext):
	result = []
	m = -1
	for i in range(25):
		text = ""
		for char in ciphertext:
			if(char in string.ascii_lowercase):
				text += string.ascii_lowercase[(ord(char) - ord('a') - i + 26) % 26]
			elif(char in string.ascii_uppercase):
				text += string.ascii_uppercase[(ord(char) - ord('A') - i + 26) % 26]
			else:
				text += char
		c = check_text(text)
		if(c > m):
			result = [(text, c, i )]
			m = c
		elif(c == m):
			result.append((text, c, i))

	print("The best result that the ceaser decipher found are for '" + ciphertext + "' are: ")
	for text, c, i in result:
		print(f'key = {i}\ndeciphered text = {text}\nsuccesfull words = {c}\n~~~~~~~~~~~~~~~~~~~~~~~')

decipher("Travhf jvgubhg rqhpngvba vf yvxr fvyire va gur zvar :Q")

