from operator import mul, mod
from functools import reduce
import math

def multinv(a, m):
	if math.gcd(a, m) != 1:
		return 0;
		
	originalm = m 
	t = 0
	r = 1

	while (a > 1): 
		temp = t
		t = r - (a // m) * t 
		r = temp
		tempa = a
		a = m
		m = tempa % m
		
	while (r < 0):
		r += originalm 

	return r 
		
def crt3(mInput, aInput):
	a = aInput[0]
	b = aInput[1]
	c = aInput[2]
	
	m1 = mInput[0]
	m2 = mInput[1]
	m3 = mInput[2]
	
	M3 = m1 * m2
	M2 = m1 * m3
	M1 = m2 * m3
	
	b1 = multinv(M1, m1)
	b2 = multinv(M2, m2)
	b3 = multinv(M3, m3)
	
	x = a * M1 * b1 + b * M2 * b2 + c * M3 * b3
	
	y = m1 * m2 * m3
	return x % y
		
def crt4(mInput, aInput):
	a = aInput[0]
	b = aInput[1]
	c = aInput[2]
	d = aInput[3]
	
	m1 = mInput[0]
	m2 = mInput[1]
	m3 = mInput[2]
	m4 = mInput[3]
	
	M3 = m1 * m2 * m4
	M2 = m1 * m3 * m4
	M1 = m2 * m3 * m4
	M4 = m1 * m2 * m3
	
	b1 = multinv(M1, m1)
	b2 = multinv(M2, m2)
	b3 = multinv(M3, m3)
	b4 = multinv(M4, m4)
	
	x = a * M1 * b1 + b * M2 * b2 + c * M3 * b3 + d * M4 * b4
	
	y = m1 * m2 * m3 * m4
	return x % y
	
	
def main():
	n1 = 1
	while (n1 != 0):
		n1 = int(input("Would you like 3 or 4 sets of numbers? (Enter 3 or 4, 0 to quit): "))
		if n1 == 4:
			a1 = int(input("Enter a1: "))
			a2 = int(input("Enter a2: "))
			a3 = int(input("Enter a3: "))
			a4 = int(input("Enter a4: "))
			
			m1 = int(input("Enter m1: "))
			m2 = int(input("Enter m2: "))
			m3 = int(input("Enter m3: "))
			m4 = int(input("Enter m4:"))
		
			m = [m1, m2, m3, m4]
			a = [a1, a2, a3, a4]
			
			output = crt4(m, a)
			if output != 0:
				print(output, (m1 * m2 * m3 * m4))
			else:
				print("No solution")
			
		if n1 == 3:
			a1 = int(input("Enter a1: "))
			a2 = int(input("Enter a2: "))
			a3 = int(input("Enter a3: "))
			
			m1 = int(input("Enter m1: "))
			m2 = int(input("Enter m2: "))
			m3 = int(input("Enter m3: "))
		
			m = [m1, m2, m3]
			a = [a1, a2, a3]
			output = crt3(m, a)
			if output != 0:
				print(output, (m1 * m2 * m3))
			else:
				print("No solution")
		
		if n1 == 0:
			break


if __name__ == '__main__':
	main()
