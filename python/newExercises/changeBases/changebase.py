import string

def translate(digit):
	lower = string.ascii_lowercase
	upper = string.ascii_uppercase

	if(type("a") == type(digit)):
		if (digit in "0123456789"):
			return int(digit)
		if (digit in lower):
			return 10 + lower.index(digit)
		elif (digit in upper):
			return 10 + upper.index(digit)
		print(f"ERROR, cant recognize: {digit}")
		exit()

	if(type(1) == type(digit)):
		if(digit < 10):
			return str(digit)
		return str(upper[digit-10])

	print("Type error, exiting")
	exit()

def from_any_to_dec_v1(number, current_base):
	num = str(number)
	num = num[::-1]
	dec = 0
	for i in range(len(num)):
		dec += translate(num[i]) * pow(current_base, i)
	return dec

def from_any_to_dec_v2(number, current_base): #works for only numbers (no LETTERS - A, B, ...)
	dec = 0
	counter = 0
	while (number != 0):
		dec += number % 10 * pow(current_base, counter)
		counter+=1
		number//=10
	return dec

num1 = "C1"
num2 = 10
print(str(from_any_to_dec_v1(num1, 16)))
print(str(from_any_to_dec_v2(num2, 16)))

def from_dec_to_any_v1(number, wanted_base):
	div = 1
	while (div < number):
		div = div * wanted_base

	if(div == 1):
		return number

	div = div // wanted_base
	num = number
	new = ""
	while 1:
		if(div < wanted_base): # div == 1 
			return new + translate(num)
		d = num // div
		num -= d * div # num = num % div
		new = new + translate(d)
		div = div // wanted_base


def from_dec_to_any_v2(number, wanted_base):
	num = number
	new = ""
	while (num != 0):
		m = num % wanted_base
		num = num // wanted_base
		new = translate(m) + new
	return new

def from_bin_to_hex(num): #not really useful codewise, but the idea is to use blocks of 4 binary digits which equal to one hexa digit.
	binary = num
	while (len(binary) % 4 != 0):
		binary = '0' + binary
	hexa = ''
	while binary != '':
		quad = binary[:4]

		binary = binary[4:]


def from_hex_to_bin(): #every hexa digit is equal to one binary
	pass

print(from_dec_to_any_v1(193, 16))
print(from_dec_to_any_v2(193, 16))