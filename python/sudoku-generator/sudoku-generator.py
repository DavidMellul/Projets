from random import randint

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

def resoudreSudoku(sudoku, position):
	if(position == 81):
		return True
	
	i = int(position/9)
	j = position%9
	
	if(sudoku[i][j] != 0):
		return resoudreSudoku(sudoku, position+1)
	
	for n in range(1,10):
		if(presentSurLigne(sudoku, i, n) == False):
			if(presentSurColonne(sudoku, j, n) == False):
				if(presentSurBloc(sudoku, i, j, n) == False):
					sudoku[i][j] = n
					if(resoudreSudoku(sudoku, position+1)):
						return True
	sudoku[i][j] = 0
	return False

def remplirAleatoirementSudoku(sudoku):
	caseI = randint(0,8)
	caseJ = randint(0,8)
	valeur = randint(1,9)
	
	sudoku[caseI][caseJ] = valeur

def retirerCaseAleatoirementSudoku(sudoku):
	for i in range(0,randint(60,70)):
		caseI = randint(0,8)
		caseJ = randint(0,8)
		sudoku[caseI][caseJ] = 0
	
sudoku = [
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,0,0,0,0],
			[0,0,0,0,0,0,0,0,0]
		 ]

remplirAleatoirementSudoku(sudoku)
resoudreSudoku(sudoku,0)
retirerCaseAleatoirementSudoku(sudoku)
print("---------- DEBUT DE LA GENERATION ----------")
for i in range(0,9):
	for j in range(0,9):
		print(sudoku[i][j],end=" ")
	print()
print("---------- FIN DE LA GENERATION ----------")
