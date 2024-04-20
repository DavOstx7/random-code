def method1A(arr):

	tmpArr = arr
	newArr = []

	if(len(arr) == 0):
		return newArr

	while len(arr) >= 2:

		minnn = tmpArr[0]
		for i in range(1, len(tmpArr)):
			if(tmpArr[i] < minnn):
				minnn = tmpArr[i]

		newArr.append(minnn)
		tmpArr.remove(minnn)		

	newArr += tmpArr # newArr.append(tmpArr[0])

	return newArr

def method1B(arr):

	newArr = []

	if(len(arr) == 0):
		return arr

	smallest = arr[0]
	biggest = arr[0]

	for num in arr:
		if(num > biggest):
			biggest = num
		if(num < smallest):
			smallest = num

	maxvalue = biggest + 1
	minvalue = smallest - 1

	last = minvalue

	for _ in range(len(arr)):
		
		smallest = maxvalue
		for number in arr:
			if(number < smallest and number > last):
				smallest = number
		newArr.append(smallest)
		last = smallest

	return newArr


def method2(arr):
	
	newArr = []
	count = {}
	for num in arr:
		counter = 0

		for number in arr:
			if(num == number):
				continue
			if (num > number):
				counter+=1

		count[counter] = num

	for i in range(len(arr)):
		newArr.append(count[i])

	return newArr

		

def method3(arr):
	
	start = 0

	tmpArr = arr

	while True:
		if(start == len(arr)):
			break
		smallest = tmpArr[start]
		for i in range(start, len(tmpArr)):
			if(tmpArr[i] < smallest):
				smallest = tmpArr[i]
		tmpArr.remove(smallest)
		tmpArr.insert(start, smallest)
		start+=1

	return tmpArr

test = [1,5,787294,412,331,51]

print(method2(test))