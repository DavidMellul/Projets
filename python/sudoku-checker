def factorielle(n):
	if(n < 2):
		return 1
	else:
		return n*factorielle(n-1)

def ligneBonne(sudoku, i):
	somme = 0
	for j in range(0,9):
		somme += factorielle(sudoku[i][j])
	return True if somme == 409113 else False

def colonneBonne(sudoku, j):
	somme = 0
	for i in range(0,9):
		somme += factorielle(sudoku[i][j])
	return True if somme == 409113 else False

def blocBon(sudoku, i, j):
	somme = 0
	_i = i - i%3
	_j = j - j%3
	for k in range(_i, _i+3):
		for l in range(_j, _j+3):
			somme += factorielle(sudoku[k][l])
	return True if somme == 409113 else False
	
def sudokuValide(sudoku):
	for i in range(0,9):
		for j in range(0,9):
			if(ligneBonne(sudoku, i) == False or colonneBonne(sudoku, j) == False or blocBon(sudoku, i, j) == False):
				return False
	return True
	
sudoku = [
			[5, 3, 4, 6, 7, 8, 9, 1, 2], 
			[6, 7, 2, 1, 9, 5, 3, 4, 8],
			[1, 9, 8, 3, 4, 2, 5, 6, 7],
			[8, 5, 9, 7, 6, 1, 4, 2, 3],
			[4, 2, 6, 8, 5, 3, 7, 9, 1],
			[7, 1, 3, 9, 2, 4, 8, 5, 6],
			[9, 6, 1, 5, 3, 7, 2, 8, 4], 
			[2, 8, 7, 4, 1, 9, 6, 3, 5], 
			[3, 4, 5, 2, 8, 6, 1, 7, 9] 
		 ]
		 
print("---------- DEBUT DE L'ANALYSE ----------")
print("Ce sudoku est correctement rempli.") if sudokuValide(sudoku) else print("Ce sudoku comporte des erreurs.")
print("---------- FIN DE L'ANALYSE ----------")
