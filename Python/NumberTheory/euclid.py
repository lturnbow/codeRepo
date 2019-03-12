import numpy as np

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
	
	m.append([result[0][0], originalA, result[1][0], originalB, prevr])
	print(np.matrix(m))

	return prevr
	
def main():
	n1 = 1
	n2 = 1
	
	while n1 or n2 != 0:
		n1 = int(input("Enter first number (0 to quit): "))
		if n1 == 0:
			break
		n2 = int(input("Enter second number (0 to quit): "))
		if n2 == 0: 
			break
		val = Euclid(n1, n2)
		if val == 0:
			print(str(n2) +" divides " + str(n1))
		else:
			print("Greatest Common Divisor is: %d" % (val))
		print("\n")
	
if __name__ == "__main__":
	main()
