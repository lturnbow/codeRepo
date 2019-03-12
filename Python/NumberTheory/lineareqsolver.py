# Lauren Turnbow
# Linear Equation Solver

import numpy as np
import math

def lineareqsolver(a, b, c):
	g = math.gcd(a, b)
	if g != 1 and c % g == 0:
		a /= g
		b /= g
		c /= g
		
	elif g != 1 and c % g != 0:
		return 0
		
	r = Euclid(a, b)
	
	aCoeff = r[1]
	bCoeff = r[3]
	if aCoeff * a + bCoeff * b != 1:
		temp = aCoeff
		aCoeff = bCoeff
		bCoeff = temp
	
	xsign = "pos"
	xnumsign = ""
	if aCoeff > 0:
		xnumsign = "pos"
	elif aCoeff < 0:
		xnumsign = "neg"
		
	ysign = "neg"
	ynumsign = ""
	if bCoeff > 0:
		ynumsign = "pos"
	elif bCoeff < 0:
		ynumsign = "neg"
		
	xt = b
	x = 1
	if xnumsign == "pos":
		x = aCoeff * c
	elif xnumsign == "neg":
		x = -(aCoeff * c)
		
	yt = -a
	y = 1
	if ynumsign == "pos":
		y = bCoeff * c
	elif ynumsign == "neg":
		y = -(bCoeff * c)

	if xnumsign == "pos":
		print(str("x = "), int(xt), str(" t + "), int(x))
	elif xnumsign == "neg":
		print(str("x = "), int(xt), str(" t - "), int(x))
		
	if ynumsign == "pos":
		print(str("y = "), int(yt), str(" t + "), int(y))
	elif ynumsign == "neg":
		print(str("y = "), int(yt), str(" t - "), int(y))
	
	return 1

def Euclid(num1, num2):
	a = num1
	b = num2
	if (num1 >= num2):
		a = num1
		originalA = num1
		b = num2
		originalB = num2
	else:
		a = num2
		originalA = num2
		b = num1
		originalB = num1
	r = a % b
	prevr = r
	
	m = []
	q = []
	
	while r != 0:		
		tempA = a
		tempB = b
		a = tempB
		b = r
		prevr = r
		r = a % b
		m.append([tempA, int(tempA/tempB), tempB, prevr, 0])
		q.append(int(tempA/tempB))
		
	m.append([a, int(a/b), b, r, 0])
	q.append(int(a/b))
	
	a = []
	for i in range(0, len(q)):
		a.append(np.array( [ [0, 1], [1, -q[i] ] ]))	
	
	result = np.array([ [ 1, 0] , [0 , 1] ])
	
	for i in range(0, len(q)):
		result = result.dot(a[i])
	
	r = []
	r.append(num1)
	r.append(result[1][0])
	r.append(num2)
	r.append(result[0][0])
	m.append([result[0][0], originalA, result[1][0], originalB, prevr])
	
	return r


def main():
	a = 1
	while (a != 0):
		a = int(input("Enter a (0 to quit): "))
		if a == 0:
			break
		b = int(input("Enter b: "))
		c = int(input("Enter c: "))
		r = lineareqsolver(a, b, c)
		if r == 0:
			print("No solution")
		
	
if __name__ == '__main__':
	main()
