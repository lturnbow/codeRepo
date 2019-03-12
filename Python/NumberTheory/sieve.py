# Lauren Turnbow
# Calculating list of primes using sieve of Eratosthenes 
import math

def SieveOfEratosthenes(a, b):
	if a == 1:
		a = 2
	prime = list(range(a, b + 1))
	
	for i in range(a, b + 1):
		if isPrime(i):
			prime = [elem for elem in prime if (elem % i != 0 or elem == i)]
		else:
			prime = [elem for elem in prime if (elem % i != 0)]		
	
	print(prime)
	
def isPrime(n):
	for i in range(2, int(math.sqrt(n)) + 1):
		if n % i == 0:
			return False
			
	return True	

def main():
	a = 1
	while a != 0:
		a = int(input("Enter starting value (0 to quit): "))
		if a == 0:
			break
		b = int(input("Enter ending value: "))
		SieveOfEratosthenes(a, b)
		
	
if __name__ == "__main__":
	main()
