# Lauren Turnbow
# Affine decoding scheme
def affineencode(a, b, s):
	l = {}
	l["a"] = 0
	l["b"] = 1
	l["c"] = 2
	l["d"] = 3
	l["e"] = 4
	l["f"] = 5
	l["g"] = 6
	l["h"] = 7
	l["i"] = 8
	l["j"] = 9
	l["k"] = 10
	l["l"] = 11
	l["m"] = 12
	l["n"] = 13
	l["o"] = 14
	l["p"] = 15
	l["q"] = 16
	l["r"] = 17
	l["s"] = 18
	l["t"] = 19
	l["u"] = 20
	l["v"] = 21
	l["w"] = 22
	l["x"] = 23
	l["y"] = 24
	l["z"] = 25

	alphabet = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
	
	originalCode = []
	for i in range(0, len(s)):
		originalCode.append(l[s[i]])

	word = []
	alphabetCode = []
	code = []
	originalWord = []
	for i in range(0, 26):
		value = (a * i + b) % 26
		code.append(value)
		alphabetCode.append(alphabet[value])
	
	for i in range(0, len(s)):
		for j in range(0, 26):
			if s[i] == alphabetCode[j]:
				originalWord.append(s[i])
				word.append(j)
	
	decoded = []
	for i in range(0, len(word)):
		decoded.append(alphabet[word[i]])
		
	print(originalWord)
	print(originalCode)
	print(word)
	print(decoded)
	

def main():
	a = 1
	while (a != 0):
		a = int(input("Enter a (0 to quit): "))
		if a == 0:
			break
		b = int(input("Enter b: "))
		s = str(input("Enter string to decode (only lower case letters): "))
		affineencode(a, b, s)

if __name__ == '__main__':
	main()
