import time

t = time.time()
f = open('smallfile.txt', 'r')
for line in f.readlines():
	print(line.strip())
time1 = time.time() - t

t = time.time()
with open('smallfile.txt') as f:
	for line in f:
		print(line.strip())
time2 = time.time() - t

print(f"time1 = {time1} | time2 = {time2}")
if(time1 < time2):
	print(f'time1 is better performance wise, by {time2 - time1}')
else:
	print(f'time2 is better performance wise, by {time1 - time2}')


t = time.time()
f = open('bigfile.txt', 'r')
for line in f.readlines():
	print(line.strip())
time1 = time.time() - t

t = time.time()
with open('bigfile.txt') as f:
	for line in f:
		print(line.strip())
time2 = time.time() - t

print(f"time1 = {time1} | time2 = {time2}")
if(time1 < time2):
	print(f'time1 is better performance wise, by {time2 - time1}')
else:
	print(f'time2 is better performance wise, by {time1 - time2}')


