import math
import numpy as np

def SieveOfEratosthenes(n):
	prime = list(range(2, n + 1))
	
	for i in range(2, int(math.sqrt(n)) + 1):
		if isPrime(i):
			prime = [elem for elem in prime if (elem % i != 0 or elem == i)]
		else:
			prime = [elem for elem in prime if (elem % i != 0)]		
	
	return prime
	
def factorization(pList, n):
		num = int(n)
		l = []
		i = 0
		while num != 1:
			if num % pList[i] == 0:    
				num = (int(num) // int(pList[i]))
				l.append(pList[i]) 
			elif num % pList[i] != 0:
				if i == len(pList) - 1:
					break
				i = i + 1 
		
		if num != 1:
			l.append(num)
		
		p = []
		e = []
		p.append("p")
		e.append("e")
		d_list = list(set(l))
		d_list.sort()
		for i in range(0, len(d_list)):
			p.append(d_list[i])
			c = l.count(d_list[i])
			e.append(c)
			
		m = [ p , e ]
		print((np.matrix(m)))
		
def isPrime(n):
	for i in range(2, int(math.sqrt(n)) + 1):
		if n % i == 0:
			return False
			
	return True
	
def main():
	n1 = 1
	while n1 != 0:
		p = 50000
		primeList = SieveOfEratosthenes(p)
		n1 = int(eval(input("Enter number to factor (0 to quit): ")))
		if n1 == 0: 
			break
		factorization(primeList, n1)
	
if __name__ == "__main__":
	main()
