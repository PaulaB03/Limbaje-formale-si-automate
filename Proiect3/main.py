f = open("input.in")

# Citire gramatica
symbols = f.readline().split()
alphabet = f.readline().split()
start_symbol = f.readline()[0]
nr_production = int(f.readline())
production = {}

for i in range(nr_production):
    str = f.readline().split()
    if str[0] in production:
        production[str[0]].append(str[1])
    else:
        production[str[0]] = [str[1]]

# Citire cuvant
str = f.readline()

f.close()


# Functie pentru concatenarea productiilor
# Exemplu: first = {'A', 'B'} second = {'C', 'D'} => aux = {'AC', 'AD', 'BC', 'BD'}
def create_row(first, second):
    aux = set()

    # Verifica daca celulele sunt goale
    if first == set() or second == set():
        return set()

    # Creeaza toate posibilitatile  
    for f in first:
        for s in second:
            aux.add(f+s)

    return aux


# CYK algorithm
table = [[set() for _ in range(len(str)-i)] for i in range(len(str))]

# Umple prima linie a tabelului
for i in range(len(str)):
    # Verifica daca este o productie
    for p in production:
        if str[i] in production[p]:
            table[0][i].add(p)

# Umple restul tabelului
for i in range(1, len(str)):
    for j in range(len(str) - i):
        for k in range(i):
            row = create_row(table[k][j], table[i-k-1][j+k+1])
            for r in row:
                # Verifica daca este o productie
                for p in production:
                    if r in production[p]:
                        table[i][j].add(p)

# Verificam daca cuvantul apartine in gramatica
if start_symbol in table[len(str)-1][0]:
    print(str + " se afla in gramatica")
else:
    print(str + " nu se afla in gramatica")