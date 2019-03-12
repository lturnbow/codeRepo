# Lauren Turnbow
# Calculating multiplicative inverse
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

def main():
	a = 1
	while (a != 0):
		a = int(input("Enter a (0 to quit): "))
		if a == 0:
			break
		m = int (input("Enter m (number to mod by): "))
		output = multinv(a, m)
		if output == 0:
			print("Multiplicative inverse not found")
		else:
			print(output)
		
if __name__ == "__main__":
	main()
