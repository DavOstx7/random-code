import random

def return_min_number(arr):
	if(len(arr) == 0):
		return []
	m = arr[0][1]

	for i in range(1, len(arr)):
		if(arr[i][1] < m):
			m = arr[i][1]

	return m

def return_max_number(arr):
	if(len(arr) == 0):
		return []
	m = arr[0][1]

	for i in range(1, len(arr)):
		if(arr[i][1] > m):
			m = arr[i][1]

	return m

def fix_arr(arr, m):
	mult = 1
	check = m * 1.0
	while check.is_integer() == False:
		mult = mult * 10.0
		check = m * mult
	

	newArr = []
	for value, num in arr:
		newArr.append((value, int(num * mult)))
	return newArr

def is_arr_dividable(arr, x):
	for _, num in arr:
		if(num % x != 0):
			return False
	return True

def reduce_size(arr):
	divider = 2
	saveD = 1

	m = return_max_number(arr)

	while divider <= m//2:
		if(is_arr_dividable(arr, divider)):
			saveD = divider
		divider+=1

	newArr = []
	for value, num in arr:
		newArr.append((value, num//saveD))
	return newArr


def random_by_chances(arr):
	m = return_min_number(arr)

	if(m < 1):
		arr = fix_arr(arr, m)

	reduced_arr = reduce_size(arr)
	info1 = ""; info2 = ""
	for value, chance in reduced_arr:
		info1 += str(value) + ":"
		info2 += str(chance) + ":"
	info1 = info1[:-1]; info2 = info2[:-1]

	print(f"for {info1} the chances are {info2}")

	s = ""
	for value, relation in reduced_arr:
		s+=value * relation
	rnd = random.choice(s)
	print("chosen: " + rnd)
	
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
print("~~~~~~~~~~~~~~~~~~~~~~MY SOLUTION~~~~~~~~~~~~~~~~~~~~~~")
chances = [("a", 0.065), ("m", 0.95), ("x", 0.4), ("k", 4)]
random_by_chances(chances)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

print()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
print('~~~~~~~~~~~~~~~~~~~~~~RANDOM SOLUTION~~~~~~~~~~~~~~~~~~~~~~')

values = ["a", "m", "x", "k"]
weights = [0.065, 0.95, 0.4, 4]
print(f'for the values: {values} and weights of: {weights}')
print(f'the value: {random.choices(values, weights=weights)[0]} was chosen!')
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


