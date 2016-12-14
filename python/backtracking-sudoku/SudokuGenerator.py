'''
  M322 - Modélisation mathématique
  Travail dirigé par : Olivier PANTZ
  SudokuSolver.py - Un programme permettant de générer un sudoku compliqué à résoudre.
  Auteurs : Loïs LONG, David MELLUL (et Abdoullah REZGUI)
'''

#Utilisation de random pour mélanger les tableaux, et de copy pour copier des matrices par copie de valeurs et non pas par référence.
import random
from random import randint
import copy
import pprint

#Méthode pour savoir si un nombre donné est présent dans une ligne donnée du sudoku
def presentSurLigne(sudoku, i, n):
	for j in range(0,9):
		if(sudoku[i][j] == n):
			return True
	return False

#Méthode pour savoir si un nombre donné est présent dans une colonne donnée du sudoku
def presentSurColonne(sudoku, j, n):
	for i in range(0,9):
		if(sudoku[i][j] == n):
			return True
	return False

#Méthode pour savoir si un nombre donné est présent dans un bloc donné du sudoku
def presentSurBloc(sudoku, i, j, n):
	blocI = i - i%3
	blocJ = j - j%3

	for k in range(blocI, blocI+3):
		for l in range(blocJ, blocJ+3):
			if(sudoku[k][l] == n):
				return True
	return False

#Méthode pour savoir si l'on peut mettre le nombre n dans la case en position {i,j}
def casePossible(sudoku, i, j, n):
    return (presentSurLigne(sudoku,i,n) == False and presentSurColonne(sudoku,j,n) == False and presentSurBloc(sudoku,i,j,n) == False)

#Méthode qui permet de déterminer toutes les cases vides (=0) du sudoku
def determinerCasesVides(sudoku):
	tableauCasesVides = []
	for i in range(0,9):
		for j in range(0,9):
			if(sudoku[i][j] == 0):
				tableauCasesVides += [i*9 + j]
	return tableauCasesVides

#Méthode qui permet de déterminer quel est le nombre de nombres possibles que l'on peut mettre dans chaque case du sudoku
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
	tableauPossibilitesRange =  sorted(range(len(tableauPossibilites)),key=lambda x:tableauPossibilites[x])
	return tableauPossibilitesRange

#Méthode qui permet de déterminer exactement quels sont les nombres possibles que l'on peut mettre dans chaque case du sudoku
def determinerValeursPossible(sudoku, tableauCasesVides,tableauPossibilites):
	tableauValeursPossibles = [[] for _ in range(len(tableauCasesVides))]
	for position in range(0, len(tableauCasesVides)):
		n = tableauCasesVides[tableauPossibilites[position]]
		posI = int(n/9)
		posJ = n%9
		for valeurPossible in range(1,10):
			if(presentSurBloc(sudoku, posI, posJ, valeurPossible) == False):
				if(presentSurLigne(sudoku, posI, valeurPossible) == False):
					if(presentSurColonne(sudoku, posJ, valeurPossible) == False):
						tableauValeursPossibles[position] += [valeurPossible]
	return tableauValeursPossibles

#Méthode qui permet de connaître quelles sont les cases déjà remplies du sudoku
def determinerCasesPleines(sudoku):
  tableauCasesPleines = []
  for i in range(0,81):
    posI = int(i/9)
    posJ = i%9
    if(sudoku[posI][posJ] != 0):
      tableauCasesPleines += [i]
  return tableauCasesPleines

#Méthode qui retire une case du sudoku
def retirerCase(sudoku,i,j):
  sudoku[i][j] = 0


#Méthode basique de backtracking
def methodeBasique(sudoku, position):
	if(position == 81):
		return True

	i = int(position/9)
	j = position%9

	if(sudoku[i][j] != 0):
		return methodeBasique(sudoku, position+1)


	tableauValeursPossibles = [ 1 , 2 , 3 , 4 , 5  , 6 , 7 , 8 , 9 ]
	random.shuffle(tableauValeursPossibles)
	for n in range(0,9):
		k = tableauValeursPossibles[n]
		if(presentSurLigne(sudoku, i, k) == False):
			if(presentSurColonne(sudoku, j, k) == False):
				if(presentSurBloc(sudoku, i, j, k) == False):
					sudoku[i][j] = k
					if(methodeBasique(sudoku, position+1)):
						return True
	sudoku[i][j] = 0
	return False

#Méthode qui permet de résoudre un sudoku par backtracking
#Le principe est de ne penser à remplir que les cases vides sans se préocupper des cases déjà remplies
#Le programme commence par traiter les cases ayant le moins de possibilités, et ne teste que les nombres possibles
#Lorsque une solution est trouvée, la méthode s'arrête.
def methodeIntelligenteDetection(sudoku, position, tableauCasesVides, tableauPossibilites, tableauValeursPossibles):
	if(position == len(tableauCasesVides)):
	  global nb_solutions
	  nb_solutions += 1
	  if(nb_solutions == 2):
	    return True
	  return False

	i = int(tableauCasesVides[tableauPossibilites[position]]/9)
	j = tableauCasesVides[tableauPossibilites[position]]%9

	for n in range(0,len(tableauValeursPossibles[position])):
		k = tableauValeursPossibles[position][n]
		if(casePossible(sudoku,i,j,k) == True):
			sudoku[i][j] = k
			if(methodeIntelligenteDetection(list(sudoku), position+1,tableauCasesVides,tableauPossibilites, tableauValeursPossibles)):
			  return True

	sudoku[i][j] = 0

#Méthode qui permet de créer un nouveau sudoku vide
def nouveauSudokuVide():
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
  return sudoku


#------------------------------------------------------------------ GENERATION ------------------------------------------------------------------

#Le nombre de solutions trouvées pour un sudoku donné
nb_solutions = 0


def resoudre(sudoku):
  tableauCasesVides = determinerCasesVides(sudoku)
  tableauPossibilites = determinerPossibilites(sudoku,tableauCasesVides)
  tableauValeursPossibles = determinerValeursPossible(sudoku,tableauCasesVides,tableauPossibilites)
  methodeIntelligenteDetection(sudoku,0,tableauCasesVides,tableauPossibilites,tableauValeursPossibles)

def generation():
  tableauRetour = []
  sudokusDejaTestes = []

  global nb_solutions
  sudokuGenere = nouveauSudokuVide()
  sudokuBase = nouveauSudokuVide()
  methodeBasique(sudokuBase,0)
  sudokuGenere = copy.deepcopy(sudokuBase)

  while(len(determinerCasesPleines(sudokuGenere)) >= 25):
    sudokuBase = nouveauSudokuVide()
    methodeBasique(sudokuBase,0)
    if(sudokuBase not in sudokusDejaTestes):
      sudokuGenere = copy.deepcopy(sudokuBase)
      sudokusDejaTestes += [sudokuBase]
      tableauCasesPleines = determinerCasesPleines(sudokuGenere)
      random.shuffle(tableauCasesPleines)
      iterateur = 0
      while( iterateur < 81):
        position = tableauCasesPleines[iterateur]
        posI = int(position/9)
        posJ = position%9
        nb_solutions = 0
        retirerCase(sudokuGenere,posI,posJ)
        resoudre(copy.deepcopy(sudokuGenere))
        if(nb_solutions == 2):
          sudokuGenere[posI][posJ] = copy.deepcopy(sudokuBase[posI][posJ])
        iterateur += 1
  tableauRetour = [sudokuGenere,sudokuBase]
  return tableauRetour
