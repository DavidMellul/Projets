from PIL import Image, ImageFilter
import sys

#Affiche l'aide ainsi que les informations utiles à l'utilisation de ce programme en ligne de commande
def help():
    print("NAME")
    print("\timg - Un manipulateur d'images.")
    print("SYNOPSIS")
    print("\timg -h |")
    print("\timg  -i | -n | -r | -v | -b | -bw | -gbw [FICHIER]")
    print("\timg  -i | -n | -r | -v | -b | -bw | -gbw [FICHIER_INPUT] -o [FICHIER_OUTPUT]")
    print("DESCRIPTION")
    print("\timg est un programme réalisé en Python permettant de transformer des images.")
    print("OPTIONS")
    print("\t-h")
    print("\t\tAffiche l'aide.")
    print("\t-o")
    print("\t\tPermet de spécifier le fichier dans lequel sauvegarder la sortie de ce programme.")
    print("\t-i [IMAGE]")
    print("\t\tPermet d'illuminer l'image et de la magnifier.")
    print("\t-n [IMAGE]")
    print("\t\tPermet de transformer l'image en négatif")
    print("\t-r [IMAGE]")
    print("\t\tPermet de transformer l'image en nuances de rouge")
    print("\t-v [IMAGE]")
    print("\t\tPermet de transformer l'image en nuances de vert")
    print("\t-b [IMAGE]")
    print("\t\tPermet de transformer l'image en nuances de bleu")
    print("\t-bw [IMAGE]")
    print("\t\tPermet de transformer l'image en noir et blanc.")
    print("\t-gbw [IMAGE]")
    print("\t\tPermet de transformer l'image en noir et blanc granulé.")


    print("AUTHOR")
    print("\tDavid Mellul")
    sys.exit(0)

#Affiche l'erreur rencontrée lors de l'appel au programme en ligne de commande
def error():
    print("Erreur de syntaxe : img.py <option> <fichier>")
    print("Pour plus de détails : img.py -h")
    sys.exit(0)

#Vérifie la syntaxe de la commande et renvoie un tableau sous la forme : { Filtre , Fichier } || { Filtre , Fichier , Sortie }
def checkArguments():
    arguments = sys.argv
    listeArgumentsPossibles = [ "-i" , "-n" , "-r" , "-v" , "-b" , "-bw" , "-gbw" ]

    if(len(arguments) < 2 or len(arguments) > 5 or len(arguments) == 4):
        error()

    if(len(arguments) == 2):
        if(arguments[1] == "-h"):
            help()
        else:
            error()

    if(len(arguments) == 3):
        if(arguments[1] in listeArgumentsPossibles):
            return [ arguments[1][1:] , arguments[2] ]
        else:
            error()

    if(len(arguments) == 5):
        if(arguments[1] in listeArgumentsPossibles):
            if(arguments[3] == "-o"):
                return [ arguments[1][1:] , arguments[2] , arguments[4] ]
            else:
                error()
        else:
            error()

#Retourne la valeur d'une couleur après application d'un film négatif sur ses trois composantes RGB
def negatif(couleur):
    return ( 255 - couleur[0] , 255 - couleur[1] , 255 - couleur[2] )

#Retourne la moyenne des trois composantes RGB d'une couleur
def moyenne(couleur):
    r, v, b = couleur
    return int((r+v+b)/3)

#Retourne la valeur d'une couleur après avoir effectué l'algorithme "linear blend" (addition des deux couches pour n'en former qu'une seule)
def linearBlend(c1 , c2):
    r1, v1, b1 = c1
    r2, v2, b2 = c2
    return ( (r1+r2) , (v1+v2) , (b1+b2) )


#Retourne une image en négatif de l'image originale
def imageNegative(image):
    imageRefaite = image
    pixelsImage = imageRefaite.load()

    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            pixelsImage[i , j] = negatif(pixelsImage[i , j])
    return imageRefaite

#Retourne une image en nuances de bleu de l'image originale
def imageNuancesBleu(image):
    imageRefaite = image
    pixelsImage = imageRefaite.load()

    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImage[i , j]
            pixelsImage[i , j] = ( 0,0,moyenne(couleur) )
    return imageRefaite

#Retourne une image en nuances de rouge de l'image originale
def imageNuancesRouge(image):
    imageRefaite = image
    pixelsImage = imageRefaite.load()

    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImage[i , j]
            pixelsImage[i , j] = (moyenne(couleur),0,0)
    return imageRefaite

#Retourne une image en nuances de vert de l'image originale
def imageNuancesVert(image):
    imageRefaite = image
    pixelsImage = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImage[i , j]
            pixelsImage[i , j] = (0,moyenne(couleur),0)
    return imageRefaite

#Retourne une image avec des couleurs plus chaudes et lumineuses de l'image originale
def imageIllumine(image):
    imageRefaite = image.filter(ImageFilter.DETAIL)

    pixelsImage = image.load()
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            c1 = pixelsImage[i , j]
            c2 = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = linearBlend(c1,c2)
    return imageRefaite

def main():
    data = checkArguments()

    #Filtres : noir & blanc , noir & blanc granulé (en utilisant 1 seule nuance de gris)
    filtres = { "bw" : "L" , "gbw" : "1" }

    #Fonctions : négatif
    fonctions = { "i" : imageIllumine , "n" : imageNegative , "r" : imageNuancesRouge , "v" : imageNuancesVert , "b" : imageNuancesBleu }

    fichierImage = data[1]
    try:
        imageOriginale = Image.open(fichierImage)
        if(imageOriginale.mode != 'RGB'):
            imageOriginale = imageOriginale.convert('RGB')

        if(data[0] in filtres):
            imageRefaite = imageOriginale.convert(filtres[data[0]])
        else:
             imageRefaite = fonctions[data[0]](imageOriginale)

        if(len(data) == 3):
            imageRefaite.save(data[2])
            print("Fichier sauvegardé : ",data[2])
        else:
            imageRefaite.show()

    except:
        print ("Impossible d'accéder au fichier spécifié")

main()
