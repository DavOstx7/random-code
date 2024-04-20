#!/usr/bin/env python3

import string

class Counter: #Works for bases 2 to 36.
	def __init__(self, max, base, maxDec = False):
		self.max = max
		self.base = base
		self.maxDec = maxDec
		d = ['0','1', '2', '3', '4', '5', '6', '7', '8', '9'] + list(string.ascii_uppercase)
		if(base > 36 or base < 2):
			print(f"Base needs to be between 2 and 36, and yours is base{base}")
			exit()
		self.dict = d[:base] + ['!']

	def get_next(self, digit):
		try:
			I = self.dict.index(digit)
			nextI = I + 1
			return self.dict[nextI]
		except:
			print(f"ERROR: The max value you gave does not appear in base{self.base}, exiting.")
			exit()

	def __iter__(self):
		self.current = '0'
		self.first = True
		self.current_dec = 0
		return self

	def __next__(self):
		if(self.first):
			self.first = False
			msg = f'[base{self.base} = {self.current}] ---> [dec = {self.current_dec}]'
			self.current_dec += 1
			return msg

		if(not((self.current == self.max and self.maxDec == False) or (str(self.current_dec - 1) == self.max and self.maxDec  == True))):
			current = list(self.current)
			lastD = current[-1]
			nextD = self.get_next(lastD)

			if(nextD != '!'):
				current[-1] = nextD
				self.current = "".join(current)
				msg = f'[base{self.base} = {self.current}] ---> [dec = {self.current_dec}]'
				self.current_dec += 1
				return msg
			else:
				done = "0"
				current = current[:-1]
				while len(current) != 0:
					lastD = current[-1]
					nextD = self.get_next(lastD)
					if(nextD != '!'):
						current[-1] = nextD
						self.current = "".join(current) + done
						msg = f'[base{self.base} = {self.current}] ---> [dec = {self.current_dec}]'
						self.current_dec += 1
						return msg

					done += '0'
					current = current[:-1]

				self.current = '1' + done
				msg = f'[base{self.base} = {self.current}] ---> [dec = {self.current_dec}]'
				self.current_dec += 1
				return msg
		else:
			raise StopIteration

a = Counter('31', 19)
for i in a:
	print(i)


print('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
a = Counter('11', 2, maxDec = True)
for i in a:
	print(i)
