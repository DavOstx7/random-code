#!/usr/bin/env python3

class Block:
	def __init__(self, gym, school, store):
		self.gym = gym
		self.school = school
		self.store = store

	def return_status(self, s):
		if(s == "gym"):
			return self.gym
		if(s == "school"):
			return self.school
		if(s == "store"):
			return self.store
		return None

def IsFinished(status):
	for key in status:
		if(status[key][0] == False):
			return False
	return True

def myQ1(blocks, reqs):
	#blocks ---> [()]
	startI = 0
	endI = len(blocks) - 1
	result = {}

	for i in range(len(blocks)):
		current_block = blocks[i]
		status = {}
		for req in reqs:
			if(current_block.return_status(req)):
				status[req] = (True, 0) #("Reach Status", Blocks/Steps)
			else:
				status[req] = (False, None)

		x = 0
		while True:
		#	print(f'in while for block NUMBER - {i}, status looks like this: {status}')
			x+=1
			if(IsFinished(status)):
				break

			right = i + x
			left = i - x

			if(left >=  startI and right <= endI):
				lblock = blocks[left]
				rblock = blocks[right]
				for req in status:
					if(status[req][0] == False and (lblock.return_status(req) == True or rblock.return_status(req) == True)):
						status[req] = (True, x)
				continue


			if(left >= startI):
				lblock = blocks[left]
				for req in status:
					if(status[req][0] == False and lblock.return_status(req) == True):
						status[req] = (True, x)
				continue

			if(right <= endI):
				rblock = blocks[right]
				for req in status:
					if(status[req][0] == False and rblock.return_status(req) == True):
						status[req] = (True, x)
				continue

			print("Some of the reqs aren't found in this set of blocks, error code raised")
			exit(1)

		sum = 0
		for req in status:
			sum+=status[req][1]
		result[i] = sum

	best = ""
	amount = -1
	print(result)
	for block in result:
		d = result[block]
		if(len(best) == 0):
			best = f'{block}'
			amount = d
		else:
			if(d < amount):
				best = f'{block}'
				amount = d
			elif (d == amount):
				best+=f' {block}'

	print(f"The best block/blocks is/are: {best}, and it takes a total of {amount} to reach all the requirements")

def hisQ1(blocks, reqs):
	#blocks ---> [()]
	startI = 0
	endI = len(blocks) - 1
	result = {}

	for i in range(len(blocks)):
		current_block = blocks[i]
		status = {}
		for req in reqs:
			if(current_block.return_status(req)):
				status[req] = (True, 0) #("Reach Status", Blocks/Steps)
			else:
				status[req] = (False, None)

		x = 0
		while True:
		#	print(f'in while for block NUMBER - {i}, status looks like this: {status}')
			x+=1
			if(IsFinished(status)):
				break

			right = i + x
			left = i - x

			if(left >=  startI and right <= endI):
				lblock = blocks[left]
				rblock = blocks[right]
				for req in status:
					if(status[req][0] == False and (lblock.return_status(req) == True or rblock.return_status(req) == True)):
						status[req] = (True, x)
				continue


			if(left >= startI):
				lblock = blocks[left]
				for req in status:
					if(status[req][0] == False and lblock.return_status(req) == True):
						status[req] = (True, x)
				continue

			if(right <= endI):
				rblock = blocks[right]
				for req in status:
					if(status[req][0] == False and rblock.return_status(req) == True):
						status[req] = (True, x)
				continue

			print("Some of the reqs aren't found in this set of blocks, error code raised")
			exit(1)

		max = -1
		for req in status:
			if(status[req][1] > max):
				max = status[req][1]
		result[i] = max

	best = ""
	amount = -1
	print(result)
	for block in result:
		d = result[block]
		if(len(best) == 0):
			best = f'{block}'
			amount = d
		else:
			if(d < amount):
				best = f'{block}'
				amount = d
			elif (d == amount):
				best+=f' {block}'

	print(f"The best block/blocks is/are: {best}, and it takes at worst {amount} to reach all the requirements")


blocks = [Block(False,True,False), Block(True, False, False), Block(True, True, False), Block(False, True, False), Block(False, True, True)]
reqs = ["gym", "school", "store"]
hisQ1(blocks, reqs)
myQ1(blocks, reqs)

print("~~~~~~~~~\n\nSwitching Question\n\n~~~~~~~~~")
def Q2(buildruns):

	maxSeq = -1
	lastPer = -1
	seq = 0

	for buildrun in buildruns:

		countT = 0
		for boolean in buildrun:
			if(boolean == True):
				countT+=1
			else:
				break

		countF = len(buildrun) - countT
		greenPer = 100 * (countT / (countT + countF))
		print(f'The green precentege for {buildrun} is {greenPer}')

	#	print(f'LastPer = {lastPer}, GreenPer = {greenPer}')

		if(greenPer > lastPer):
			seq+=1
		else:
	#		print("breaked strek was: " + str(seq))
			if(seq > maxSeq):
				maxSeq = seq
			seq = 1

		lastPer = greenPer

	if(seq > maxSeq):
		maxSeq = seq

	print("Max sequence was: " + str(maxSeq))



buildruns = [[True, True, True, False, False], [True, True, True, True, False], [True, True, True, True, True, True, False, False, False], [True, False, False, False, False, False], [True, False], [True, True, True, True, False, False]]
Q2(buildruns)

