# Lauren Turnbow
def affineencode(a, b, s):
	alphabet = {}
	alphabet["a"] = 0
	alphabet["b"] = 1
	alphabet["c"] = 2
	alphabet["d"] = 3
	alphabet["e"] = 4
	alphabet["f"] = 5
	alphabet["g"] = 6
	alphabet["h"] = 7
	alphabet["i"] = 8
	alphabet["j"] = 9
	alphabet["k"] = 10
	alphabet["l"] = 11
	alphabet["m"] = 12
	alphabet["n"] = 13
	alphabet["o"] = 14
	alphabet["p"] = 15
	alphabet["q"] = 16
	alphabet["r"] = 17
	alphabet["s"] = 18
	alphabet["t"] = 19
	alphabet["u"] = 20
	alphabet["v"] = 21
	alphabet["w"] = 22
	alphabet["x"] = 23
	alphabet["y"] = 24
	alphabet["z"] = 25
	
	reverse = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]

	originalString = []
	original = []
	newEncode = []
	newString = []
	
	for i in range(0, len(s)):
		originalString.append(s[i])
		original.append(alphabet[s[i]])
		encode = (a * alphabet[s[i]] + b) % 26
		newEncode.append(encode)
		newString.append(reverse[encode])
		
	print(originalString)
	print(original)
	print(newEncode)
	print(newString)

def main():
	a = 1
	while (a != 0):
		a = int(input("Enter a (0 to quit): "))
		if a == 0:
			break
		b = int(input("Enter b: "))
		s = str(input("Enter string to encode (only lower case letters): "))
		affineencode(a, b, s)

if __name__ == '__main__':
	main()
