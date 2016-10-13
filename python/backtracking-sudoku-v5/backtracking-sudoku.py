import random
import time

def presentSurLigne(sudoku, i, n):
	for j in range(0,9):
		if(sudoku[i][j] == n):
			return True
	return False

def presentSurColonne(sudoku, j, n):
	for i in range(0,9):
		if(sudoku[i][j] == n):
			return True
	return False
	
def presentSurBloc(sudoku, i, j, n):
	blocI = i - i%3
	blocJ = j - j%3
	
	for k in range(blocI, blocI+3):
		for l in range(blocJ, blocJ+3):
			if(sudoku[k][l] == n):
				return True
	return False
	
def determinerCasesVides(sudoku):
	tableauCasesVides = []
	for i in range(0,9):
		for j in range(0,9):
			if(sudoku[i][j] == 0):
				tableauCasesVides += [i*9 + j]
	return tableauCasesVides

def determinerPossibilites(sudoku, tableauCasesVides):
	tableauPossibilites = [0]*len(tableauCasesVides)
	for i in range(0,len(tableauCasesVides)):
		n = tableauCasesVides[i]
		posI = int(n/9)
		posJ = n%9
		for valeurPossible in range(1,10):
			if(presentSurBloc(sudoku, posI, posJ, valeurPossible) == False):
				if(presentSurLigne(sudoku, posI, valeurPossible) == False):
					if(presentSurColonne(sudoku, posJ, valeurPossible) == False):
						tableauPossibilites[i] += 1
						
	tableauPossibilites = sorted(range(len(tableauPossibilites)), key=lambda k: tableauPossibilites[k])
	return tableauPossibilites
									
def sudokuValide(sudoku, position, tableauCasesVides, tableauPossibilites):
	if(position == len(tableauCasesVides)):
		return True
	
	i = int(tableauCasesVides[tableauPossibilites[position]]/9)
	j = tableauCasesVides[tableauPossibilites[position]]%9
	
	tableauValeurs = [ 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 ]
	random.shuffle(tableauValeurs)
	
	for n in range(0,9):
		k = tableauValeurs[n]
		if(presentSurLigne(sudoku, i, k) == False):
			if(presentSurColonne(sudoku, j, k) == False):
				if(presentSurBloc(sudoku, i, j, k) == False):
					sudoku[i][j] = k
					if(sudokuValide(sudoku, position+1,tableauCasesVides,tableauPossibilites)):
						return True
	sudoku[i][j] = 0
	return False
	
sudoku = [
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,3,0,8,5],
			[0,0,1,0,2,0,0,0,0],
			[0,0,0,5,0,7,0,0,0],
			[0,0,4,0,0,0,1,0,0],
			[0,9,0,0,0,0,0,0,0],
			[5,0,0,0,0,0,0,7,3],
			[0,0,2,0,1,0,0,0,0],
			[0,0,0,0,4,0,0,0,9]
		 ]

tableauCasesVides = determinerCasesVides(sudoku)
tableauPossibilites = determinerPossibilites(sudoku,tableauCasesVides)

print("---------- DEBUT DE L'ANALYSE ----------")
debut = time.time()
if(sudokuValide(sudoku,0, tableauCasesVides,tableauPossibilites)):
	print(time.time()-debut)
	for i in range(0,9):
		for j in range(0,9):
			print(sudoku[i][j],end=" ")
		print()
else:
  print("Aucune solution possible")
print("---------- FIN DE L'ANALYSE ----------")
