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

def sudokuValide(sudoku, position):
	if(position == 81):
		return True
	
	i = int(position/9)
	j = position%9
	
	if(sudoku[i][j] != 0):
		return sudokuValide(sudoku, position+1)
	
	for n in range(1,10):
		if(presentSurLigne(sudoku, i, n) == False):
			if(presentSurColonne(sudoku, j, n) == False):
				if(presentSurBloc(sudoku, i, j, n) == False):
					sudoku[i][j] = n
					if(sudokuValide(sudoku, position+1)):
						return True
	sudoku[i][j] = 0
	return False
	
sudoku = [
			[5,3,0,0,7,0,0,0,0],
			[6,0,0,1,9,5,0,0,0],
			[0,9,8,0,0,0,0,6,0],
			[8,0,0,0,6,0,0,0,3],
			[4,0,0,8,0,3,0,0,1],
			[7,0,0,0,2,0,0,0,6],
			[0,6,0,0,0,0,2,8,0],
			[0,0,0,4,1,9,0,0,5],
			[0,0,0,0,8,0,0,7,9]
		 ]
		 
print("---------- DEBUT DE L'ANALYSE ----------")
if(sudokuValide(sudoku,0)):
	for i in range(0,9):
		for j in range(0,9):
			print(sudoku[i][j],end=" ")
		print()
else:
  print("Aucune solution possible")
 print("---------- FIN DE L'ANALYSE ----------")
