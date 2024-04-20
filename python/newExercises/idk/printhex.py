#!/usr/bin/env python3

class HexCounter:
	def __init__(self, max, base):
		self.max = max
		self.base = base
		self.dict = ['0','1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'X']

	def get_next(self, digit):
		I = self.dict.index(digit)
		nextI = I + 1
		return self.dict[nextI]

	def __iter__(self):
		self.current = '0'
		self.first = True
		self.current_dec = 0
		return self

	def __next__(self):
		if(self.first):
			self.first = False
			return f'[dec = {self.current_dec}] ---> [hex = {self.current}]'

		if(not((self.current == self.max and self.base == 'hex') or (str(self.current_dec - 1) == self.max and self.base == 'dec'))):
			current = list(self.current)
			lastD = current[-1]
			nextD = self.get_next(lastD)

			if(nextD != 'X'):
				current[-1] = nextD
				self.current = "".join(current)
				msg = f'[dec = {self.current_dec}] ---> [hex = {self.current}]'	
				self.current_dec += 1
				return msg
			else:
				done = "0"
				current = current[:-1]
				while len(current) != 0:
					lastD = current[-1]
					nextD = self.get_next(lastD)
					if(nextD != 'X'):
						current[-1] = nextD
						self.current = "".join(current) + done
						msg = f'[dec = {self.current_dec}] ---> [hex = {self.current}]'
						self.current_dec += 1
						return msg

					done += '0'
					current = current[:-1]

				self.current = '1' + done
				msg = f'[dec = {self.current_dec}] ---> [hex = {self.current}]'
				self.current_dec += 1
				return msg
		else:
			raise StopIteration


class HexCalculator:
	def __init__(self):
		pass

	def add(a, b):
		pass

	def sub(a, b):
		pass

	def mul(a, b):
		pass

	def div(a, b):
		pass
'''
a = HexCounter('312', 'hex')
for i in a:
	print(i)

a = HexCounter('312', 'dec')
for i in a:
	print(i)
'''
