from PIL import Image, ImageFilter
import sys

#Affiche l'aide ainsi que les informations utiles à l'utilisation de ce programme en ligne de commande
def help():
    print("NAME")
    print("\timg - Un manipulateur d'images.")
    print("SYNOPSIS")
    print("\timg -h |")
    print("\timg   -c | -f | -i | -n | -r | -v | -b | -s | -al | -rl | -at | -rt | -sg | -sd | -bw | -ms | -ps | -gbw [FICHIER]")
    print("\timg   -c | -f | -i | -n | -r | -v | -b | -s | -al | -rl | -at | -rt | -sg | -sd | -bw | -ms | -ps | -gbw [FICHIER] -o [FICHIER_OUTPUT]")
    print("\timg   -c | -f | -i | -n | -r | -v | -b | -s | -al | -rl | -at | -rt | -sg | -sd | -bw | -ms | -ps | -gbw [FICHIER] -save")
    print("DESCRIPTION")
    print("\timg est un programme réalisé en Python permettant de transformer des images")
    print("OPTIONS")
    print("\t-h")
    print("\t\tAffiche l'aide")
    print("\t-save")
    print("\t\tPermet de sauvegarder l'image modifiée, en écrasant l'image précédente inaltérée")
    print("\t-o [FICHIER_OUTPUT]")
    print("\t\tPermet de spécifier le fichier dans lequel sauvegarder la sortie de ce programme")
    print("\t-i [IMAGE]")
    print("\t\tPermet d'illuminer l'image et de la magnifier")
    print("\t-n [IMAGE]")
    print("\t\tPermet de transformer l'image en négatif")
    print("\t-r [IMAGE]")
    print("\t\tPermet de transformer l'image en nuances de rouge")
    print("\t-v [IMAGE]")
    print("\t\tPermet de transformer l'image en nuances de vert")
    print("\t-b [IMAGE]")
    print("\t\tPermet de transformer l'image en nuances de bleu")
    print("\t-bw [IMAGE]")
    print("\t\tPermet de transformer l'image en noir et blanc")
    print("\t-gbw [IMAGE]")
    print("\t\tPermet de transformer l'image en noir et blanc granulé")
    print("\t-c [IMAGE]")
    print("\t\tPermet de transformer l'image en lui attribuant des couleurs plus chaudes")
    print("\t-f [IMAGE]")
    print("\t\tPermet de transformer l'image en lui attribuant des couleurs plus froides")
    print("\t-s [IMAGE]")
    print("\t\tPermet de transformer l'image en lui appliquant un filtre sépia")
    print("\t-al [IMAGE]")
    print("\t\tPermet de transformer l'image en la rendant plus lumineuse")
    print("\t-rl [IMAGE]")
    print("\t\tPermet de transformer l'image en la rendant moins lumineuse")
    print("\t-at [IMAGE]")
    print("\t\tPermet de transformer l'image en lui attribuant des couleurs avec plus de teinte")
    print("\t-rt [IMAGE]")
    print("\t\tPermet de transformer l'image en lui attribuant des couleurs avec moins de teinte")
    print("\t-ps [IMAGE]")
    print("\t\tPermet de transformer l'image en lui attribuant des couleurs avec plus de saturation")
    print("\t-ms [IMAGE]")
    print("\t\tPermet de transformer l'image en lui attribuant des couleurs avec moins de saturation")
    print("\t-sg [IMAGE]")
    print("\t\tPermet de transformer l'image en déplaçant ses composantes RGB vers la gauche")
    print("\t-sd [IMAGE]")
    print("\t\tPermet de transformer l'image en déplaçant ses composantes RGB vers la droite")
    print("AUTHOR")
    print("\tDavid Mellul")
    sys.exit(0)

#Affiche l'erreur rencontrée lors de l'appel au programme en ligne de commande
def error():
    print("Erreur de syntaxe : img <option> <fichier>")
    print("Pour plus de détails : img -h")
    sys.exit(0)

#Vérifie la syntaxe de la commande et renvoie un tableau sous la forme : { Filtre , Fichier } || { Filtre , Fichier , Sortie }
def checkArguments():
    arguments = sys.argv
    listeArgumentsPossibles = [ "-c" , "-f" , "-i" , "-n" , "-r" , "-v" , "-b" , "-s" , "-al" , "-rl" , "-at" , "-rt" , "-sg" , "-sd" , "-bw" , "-ms" , "-ps" , "-gbw"]

    if(len(arguments) < 2 or len(arguments) > 5):
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

    if(len(arguments) == 4):
        if(arguments[1] in listeArgumentsPossibles):
            if(arguments[3] == "-save"):
                return [ arguments[1][1:] , arguments[2] , arguments[2] ]
            else:
                error()
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

#Retourne la valeur de l'addition des trois composantes RGB de deux couleurs
def addition(c1 , c2):
    r1, v1, b1 = c1
    r2, v2, b2 = c2
    return ( (r1+r2) , (v1+v2) , (b1+b2) )

#Retourune la version plus chaude d'une couleur
def chauffer(couleur):
    r,v,b = couleur
    r = r+20 if (r+20 <= 255) else 255
    b = b-20 if (b-20 >= 0) else 0
    return ( r , v , b)

#Retourne la version plus froide d'une couleur
def refroidir(couleur):
    r,v,b = couleur
    r = r-20 if (r-20 >= 0) else r
    b = b+20 if (b+20 <= 255) else 255
    return ( r , v , b )

#Retourne la version moins teintée d'une couleur
def retirerLuminosite(couleur):
    r,v,b = couleur
    r *= 1/2
    v *= 1/2
    b *= 1/2
    return ( int(r) , int(v) , int(b) )

#Retourne la version plus teintée d'une couleur
def ajouterLuminosite(couleur):
    r,v,b = negatif(couleur)
    r *= 1/2
    v *= 1/2
    b *= 1/2
    return (couleur[0]+int(r)  , couleur[1]+int(v) , couleur[2]+int(b) )

#Retourne la version modifiée d'une couleur après le déplacement à droite de ses composantes RGB
def shiftDroit(couleur):
    return ( couleur[1] , couleur[2] , couleur[0] )

#Retourne la version modifiée d'une couleur après le déplacement à gauche de ses composantes RGB
def shiftGauche(couleur):
    return ( couleur[2] , couleur[0] , couleur[1] )

#Retourne la version sépia d'une couleur
def sepia(couleur):
    r,v,b = couleur
    r2 = int((r * 0.393) + (v * 0.769) + (b * 0.189))
    v2 = int((r * 0.349) + (v * 0.686) + (b * 0.168))
    b2 = int((r * 0.272) + (v * 0.534) + (b * 0.131))
    return (r2 , v2 , b2)

#Retourne la version d'une couleur avec plus de teinte
def ajouterTeinte(couleur):
    h,s,v = couleur
    h = h+20 if(h+20 <= 360) else h
    return ( h , s , v)     

#Retourne la version d'une couleur avec moins de teinte
def retirerTeinte(couleur):
    h,s,v = couleur
    h = h-20 if(h-20 >= 0) else h
    return ( h , s , v)  

#Retourne la version d'une couleur avec plus de saturation
def ajouterSaturation(couleur):
    h,s,v = couleur
    s = s+30 if(s+30 <= 100) else s
    return ( h , s , v)     

#Retourne la version d'une couleur avec moins de saturation
def retirerSaturation(couleur):
    h,s,v = couleur
    s = s-30 if(s-30 >= 0) else s
    return ( h , s , v)  

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

#Retourne une image avec des couleurs plus intenses et lumineuses de l'image originale
def imageIllumine(image):
    imageRefaite = image.filter(ImageFilter.DETAIL)

    pixelsImage = image.load()
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            c1 = pixelsImage[i , j]
            c2 = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = addition(c1,c2)
    return imageRefaite

#Retourune une image plus chaude de l'image originale
def imageChaude(image):
    imageRefaite = image
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = chauffer(couleur)
    return imageRefaite

#Retourne une image plus froide de l'image originale
def imageFroide(image):
    imageRefaite = image
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = refroidir(couleur)
    return imageRefaite

#Retourne une image plus lumineuse de l'image originale
def imagePlusLumineuse(image):
    imageRefaite = image
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = ajouterLuminosite(couleur)
    return imageRefaite

#Retourne une image moins lumineuse de l'image originale
def imageMoinsLumineuse(image):
    imageRefaite = image
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = retirerLuminosite(couleur)
    return imageRefaite

#Retourne une image modifiée de l'image originale après déplacement à gauche de ses composantes RGB
def imageShiftGauche(image):
    imageRefaite = image
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = shiftGauche(couleur)
    return imageRefaite

#Retourne une image modifiée de l'image originale après déplacement à droite de ses composantes RGB
def imageShiftDroit(image):
    imageRefaite = image
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = shiftDroit(couleur)
    return imageRefaite

#Retourne une image modifiée de l'image originale après application d'un filtre sepia
def imageSepia(image):
    imageRefaite = image
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = sepia(couleur)
    return imageRefaite

#Retourne une image avec plus de teinte de l'image originale
def imagePlusTeintee(image):
    imageRefaite = image.convert('HSV')
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = ajouterTeinte(couleur)
    imageRefaite = imageRefaite.convert('RGB')
    return imageRefaite

#Retourne une image avec moins de teinte de l'image originale
def imageMoinsTeintee(image):
    imageRefaite = image.convert('HSV')
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = retirerTeinte(couleur)
    imageRefaite = imageRefaite.convert('RGB')
    return imageRefaite

#Retourne une image avec plus de saturation de l'image originale
def imagePlusSaturee(image):
    imageRefaite = image.convert('HSV')
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = ajouterSaturation(couleur)
    imageRefaite = imageRefaite.convert('RGB')
    return imageRefaite

#Retourne une image avec moins de saturation de l'image originale
def imageMoinsSaturee(image):
    imageRefaite = image.convert('HSV')
    pixelsImageRefaite = imageRefaite.load()
    for i in range(0,image.size[0]):
        for j in range(0,image.size[1]):
            couleur = pixelsImageRefaite[i , j]
            pixelsImageRefaite[i , j] = retirerSaturation(couleur)
    imageRefaite = imageRefaite.convert('RGB')
    return imageRefaite


def main():
    data = checkArguments()

    filtres = { "bw" : "L" , "gbw" : "1" }
    fonctions = { "c" : imageChaude , "f" : imageFroide , "i" : imageIllumine , "n" : imageNegative , "r" : imageNuancesRouge , "s" : imageSepia , "v" : imageNuancesVert , "b" : imageNuancesBleu , "ms" : imageMoinsSaturee , "ps" : imagePlusSaturee , "sg" : imageShiftGauche , "sd" : imageShiftDroit , "rt" : imageMoinsTeintee , "at" : imagePlusTeintee , "al" : imagePlusLumineuse , "rl" : imageMoinsLumineuse}

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
