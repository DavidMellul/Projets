a = 0
b = 1
c = 0
n = int(input("Nombre de termes : "))

for i in range (1, n+1):
    c = a+b
    b = a
    a= c
print(c)
