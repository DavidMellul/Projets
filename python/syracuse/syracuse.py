n = int(input("Veuillez saisir un entier : "))
vol = 0

while(n != 1):
	if(n % 2 == 0):
		n /= 2
	else:
		n = n*3 + 1
	vol +=1
print("Le temps de vol du nombre ",n," est ",vol)
