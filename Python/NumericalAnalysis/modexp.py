import math

def modexp(a, x, m):
	b = bin(x)
	
	for i in range(0, len(b)):
		b[i] = (2 ** i) * b[i]
		
	tempA = a
	list1 = []
	list1.append(tempA)
	
	for i in range(0, len(b)):
		tempA = (tempA * tempA) % m
		list1.append(tempA)
	
	mult = 1
	for i in range(0, len(b)):
		if b[i] >= 1:
			mult *= list1[i]
			
	print(mult % m)
	
def bin(x):
	l = []
	while x != 1:
		r = x % 2
		x = math.floor(x / 2)
		l.append(r)
	
	l.append(x)

	return l
		
def main():
	a = 1
	while a != 0:
		a = int(input("Enter a (0 to quit): "))
		if a == 0:
			break
		x = int(input("Enter x: "))
		m = int(input("Enter m: "))
		modexp(a, x, m)

	
if __name__ == "__main__":
	main()
