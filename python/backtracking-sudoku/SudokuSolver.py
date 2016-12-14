'''
  M322 - Modélisation mathématique
  Travail dirigé par : Oliver PANTZ
  SudokuSolver.py - Un programme permettant de résoudre un sudoku par backtracking évolué, et de trouver toutes ses solutions.
  Auteurs : Loïs LONG, David MELLUL (et Abdoullah REZGUI)
'''

#Utilisation de random pour mélanger les tableaux, et de copy pour copier des matrices par copie de valeurs et non pas par référence.
import random
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

#Méthode qui permet de résoudre un sudoku par backtracking
#Le principe est de ne penser à remplir que les cases vides sans se préocupper des cases déjà remplies
#Le programme commence par traiter les cases ayant le moins de possibilités, et ne teste que les nombres possibles
#Lorsque une solution est trouvée, la méthode s'arrête.

def methodeIntelligente(sudoku, position, tableauCasesVides, tableauPossibilites, tableauValeursPossibles):
	if(position == len(tableauCasesVides)):
	  global B
	  B = copy.deepcopy(sudoku)
	  return True

	i = int(tableauCasesVides[tableauPossibilites[position]]/9)
	j = tableauCasesVides[tableauPossibilites[position]]%9

	for n in range(0,len(tableauValeursPossibles[position])):
		k = tableauValeursPossibles[position][n]
		if(casePossible(sudoku,i,j,k) == True):
			sudoku[i][j] = k
			if(methodeIntelligente(sudoku, position+1,tableauCasesVides,tableauPossibilites, tableauValeursPossibles)):
			  return True

	sudoku[i][j] = 0
	return False

#Même méthode que précédemment, seulement ici les valeurs ne sont pas testées dans l'ordre mais aléatoirement
def methodeIntelligenteAleatoire(sudoku, position, tableauCasesVides, tableauPossibilites, tableauValeursPossibles):
	if(position == len(tableauCasesVides)):
	  global B
	  B = copy.deepcopy(sudoku)
	  return True

	i = int(tableauCasesVides[tableauPossibilites[position]]/9)
	j = tableauCasesVides[tableauPossibilites[position]]%9

	random.shuffle(tableauValeursPossibles[position])
	for n in range(0,len(tableauValeursPossibles[position])):
		k = tableauValeursPossibles[position][n]
		if(casePossible(sudoku,i,j,k) == True):
			sudoku[i][j] = k
			if(methodeIntelligenteAleatoire(sudoku, position+1,tableauCasesVides,tableauPossibilites, tableauValeursPossibles)):
			  return True

	sudoku[i][j] = 0
	return False

#Méthode qui s'occuppe de trouver toutes les solutions à un sudoku donné.
def methodeIntelligenteDetection(sudoku, position, tableauCasesVides, tableauPossibilites, tableauValeursPossibles):
	if(position == len(tableauCasesVides)):
	  global nb_solutions
	  global B
	  nb_solutions += 1
	  B += [copy.deepcopy(sudoku)]
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
#------------------------------------------------------------------ RESOLUTION ------------------------------------------------------------------

#Le nombre de solutions trouvées pour un sudoku donné
nb_solutions = 0

#Le nombre de méthodes que nous utilisons, avec un tableau de pointeurs sur ces méthodes
nb_methodes = 4
methodes = { 0:methodeIntelligenteDetection, 1:methodeIntelligente, 2:methodeIntelligenteAleatoire, 3:methodeIntelligenteAleatoire }

#La méthode demandée qui s'occupe de résoudre le sudoku A en utilisant la méthode passée en paramètre (un nombre entre 0 et 3)
def resolution(A,methode):
  global methodes

  #Le tableau contenant toutes les solutions
  global B
  B = []

  #Indépendamment de la méthode, on doit savoir à l'avance l'emplacement des cases vides, et les nombres qu'on peut leur attribuer
  tableauCasesVides = determinerCasesVides(A)
  tableauPossibilites = determinerPossibilites(A,tableauCasesVides)
  tableauValeursPossibles = determinerValeursPossible(A, tableauCasesVides, tableauPossibilites)

  #Résolution par la méthode passée en paramètre
  methodes[methode](A,0,tableauCasesVides,tableauPossibilites,tableauValeursPossibles)
  return B

Test =[
[5 ,0 ,0 ,0 ,0 ,3 ,0 ,0 ,0 ],
[6 ,0 ,0 ,8 ,0 ,0 ,0 ,5 ,2 ],
[0 ,9 ,0 ,0 ,6 ,5 ,0 ,1 ,0 ],
[0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ],
[3 ,4 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
[0 ,0 ,5 ,0 ,0 ,4 ,0 ,8 ,7 ],
[0 ,3 ,0 ,0 ,9 ,0 ,1 ,0 ,0 ],
[0 ,0 ,4 ,0 ,0 ,0 ,0 ,6 ,0 ],
[0 ,0 ,2 ,4 ,0 ,0 ,0 ,0 ,0 ]
]
C = resolution(Test,0)
pp = pprint.PrettyPrinter(indent=4)
pp.pprint(C)
