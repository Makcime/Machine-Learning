# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <codecell>

from constraint import *

# <markdowncell>

# ## Exercice 1 - La variante du probleme des 4 maisons
# 

# <codecell>



maisons = Problem()
maisons.addVariables(["a", "b", "c", "d"], [1, 2, 3, 4])
maisons.addConstraint(AllDifferentConstraint())
maisons.addConstraint(lambda c, d : c > d, ["c", "d"])
maisons.addConstraint(lambda a, d : a - d == 1, ["a", "d"])
maisons.addConstraint(lambda b, d : abs(b - d) > 1, ["b", "d"])
maisons.addConstraint(lambda c: c != 3, ["c"])
maisons.addConstraint(lambda b: b != 1, ["b"])

maisons.getSolutions()

# <markdowncell>

# ## Exercice 2 - Le problème des 4 professeurs

# <codecell>

prob = Problem()
prob.addVariables(["a", "b", "c", "d"], [1, 2, 3, 4, 5])
prob.addConstraint(AllDifferentConstraint())
prob.addConstraint(lambda a: a != 1, ["a"])
prob.addConstraint(lambda b: b != 2, ["b"])
prob.addConstraint(lambda d: d >= 3, ["d"])
prob.addConstraint(lambda b, d: b > d , ["b", "d"])
prob.addConstraint(lambda c, b: abs(c - b ) > 1, ["c", "b"])
prob.addConstraint(lambda c: c != 5, ["c"])

prob.getSolutions()

# <markdowncell>

# ## Exercice 3 - Le problème du zebre

# <markdowncell>

# On s'intéresse au problème suivant, posé initialement par Lewis Caroll :
# 
#     Cinq maisons consécutives, de couleurs différentes, sont habitées par des hommes de différentes nationalités. Chacun possède un animal différent, a une boisson préférée différente et fume des cigarettes différentes. De plus, on sait que :
# 
#         Le norvégien habite la première maison,
#         La maison à coté de celle du norvégien est bleue,
#         L'habitant de la troisième maison boit du lait,
#         L'anglais habite la maison rouge,
#         L'habitant de la maison verte boit du café,
#         L'habitant de la maison jaune fume des kools,
#         La maison blanche se trouve juste après la verte,
#         L'espagnol a un chien,
#         L'ukrainien boit du thé,
#         Le japonais fume des cravens,
#         Le fumeur de old golds a un escargot,
#         Le fumeur de gitanes boit du vin,
#         Le voisin du fumeur de Chesterfields a un renard,
#         Le voisin du fumeur de kools a un cheval.
# 
#     Qui boit de l'eau ? A qui appartient le zèbre ?

# <codecell>

couleurs =  [
 "blanche",
 "rouge",
 "verte",
 "jaune",
 "bleue"]
natio = [ 
 "norvegien",
 "anglais",
 "ukrainien",
 "japonais",
 "espagnol"]
animals = [
 "cheval",
 "renard",
 "zebre",
 "escargot",
 "chien"]
boissons = [
 "the",
 "eau",
 "lait",
 "cafe",
 "vin"]
cigs =  [
 "kools",
 "chesterfields",
 "old_golds",
 "cravens",
 "gitanes"]

# <codecell>

prob = Problem()
prob.addVariables([ 
 "blanche",
 "rouge",
 "verte",
 "jaune",
 "bleue",
 "norvegien",
 "anglais",
 "ukrainien",
 "japonais",
 "espagnol",
 "cheval",
 "renard",
 "zebre",
 "escargot",
 "chien",
 "the",
 "eau",
 "lait",
 "cafe",
 "vin",
 "kools",
 "chesterfields",
 "old_golds",
 "cravens",
 "gitanes"], [1, 2, 3, 4, 5])

# <codecell>

prob.addConstraint(lambda norvegien: norvegien == 1, ["norvegien"])
prob.addConstraint(lambda bleue, norvegien: bleue == norvegien + 1 , ["bleue","norvegien"])
prob.addConstraint(lambda lait: lait == 3, ["lait"])
prob.addConstraint(lambda anglais, rouge: anglais == rouge, ["anglais", "rouge"])
prob.addConstraint(lambda verte, cafe: verte == cafe, ["verte", "cafe"])
prob.addConstraint(lambda jaune, kools: jaune == kools, ["jaune", "kools"])
prob.addConstraint(lambda blanche, verte: blanche == verte + 1, ["blanche", "verte"])
prob.addConstraint(lambda espagnol, chien: espagnol == chien, ["espagnol", "chien"])
prob.addConstraint(lambda ukrainien, the: ukrainien == the, ["ukrainien", "the"])
prob.addConstraint(lambda japonais, cravens: japonais == cravens, ["japonais", "cravens"])
prob.addConstraint(lambda old_golds, escargot: old_golds == escargot, ["old_golds", "escargot"])
prob.addConstraint(lambda gitanes, vin: gitanes == vin, ["gitanes", "vin"])
prob.addConstraint(lambda chesterfields, renard: chesterfields == renard - 1 or chesterfields == renard + 1, ["chesterfields", "renard"])
prob.addConstraint(lambda kools, cheval: kools == cheval - 1 or kools == cheval + 1, ["kools", "cheval"])

# <codecell>

prob.addConstraint(AllDifferentConstraint(), ["blanche", "rouge", "verte", "jaune", "bleue"])
prob.addConstraint(AllDifferentConstraint(), ["the", "eau", "lait", "cafe", "vin"])
prob.addConstraint(AllDifferentConstraint(), ["norvegien", "anglais", "ukrainien", "japonais", "espagnol"])
prob.addConstraint(AllDifferentConstraint(), ["cheval", "renard", "zebre", "escargot", "chien"])
prob.addConstraint(AllDifferentConstraint(), ["kools", "chesterfields", "old_golds", "cravens", "gitanes"])

# <codecell>

solution = prob.getSolution()
prob.getSolution()
alls = prob.getSolutions()

# <codecell>

def affichersolution(sol):
    sortedsol = []
    for i in range(1,6):
        comb = []
        for var in sol:
            if sol[var] == i and var in natio:
                comb.append(var)
        for var in sol:
            if sol[var] == i and var in animals:
                comb.append(var)
        for var in sol:
            if sol[var] == i and var in boissons:
                comb.append(var)
        for var in sol:
            if sol[var] == i and var in cigs:
                comb.append(var)
        for var in sol:
            if sol[var] == i and var in couleurs:
                comb.append(var)
        # print comb
        sortedsol.append(comb)
    
    print ''
    for nat, an, bois, ci, coul in sortedsol:
        print "La maison", coul, "est habitée par un", an,"et un", nat,"qui bois du" , bois, "et fume des", ci 

# <codecell>

affichersolution(solution)

# <codecell>

for s in alls:
    affichersolution(s)

# <markdowncell>

# ## Exercice 4 : Send more money !

# <markdowncell>

# On considère l'addition suivante :
# 
#        SEND
#      + MORE
#     -------
#     = MONEY
# 
# où chaque lettre représente un chiffre différent (compris entre 0 et 9). On souhaite connaitre la valeur de chaque lettre, sachant que la première lettre de chaque mot représente un chiffre différent de 0.

# <codecell>

prob = Problem()
prob.addVariables([ 
 "S",
 "E",
 "N",
 "D",
 "M",
 "O",
 "R",
 "Y"], [0,1,2,3,4,5,6,7,8,9])

# <codecell>

prob.addConstraint(AllDifferentConstraint())
prob.addConstraint(lambda S, M: S != 0 and M != 0, ["S", "M"]) 

# <codecell>

prob.addConstraint(lambda S, E, N, D, M, O, R, Y: 
                   1000*S + 100*E + 10*N + D +1000*M + 100*O + 10*R + E == 10000*M + 1000*O + 100*N + 10*E + Y, 
                   ["S", "E", "N", "D", "M", "O", "R", "Y"])

# <codecell>

prob.addConstraint(lambda S, M: S + M >= 10, ["S", "M"])

# <codecell>

import time

start = time.time()
sol = prob.getSolution()
stop = time.time()

print "temps de calcul = %.3f secondes" % (stop - start)

# <codecell>

print "   SEND \t    %d%d%d%d" % (sol["S"], sol["E"], sol["N"], sol["D"])
print " + MORE \t  + %d%d%d%d" % (sol["M"], sol["O"], sol["R"], sol["E"])
print "------- \t -------"
print "= MONEY \t = %d%d%d%d%d" % (sol["M"], sol["O"], sol["N"], sol["E"], sol["Y"])

# <markdowncell>

# ## Exercice 4 : Donald + gerald = robert?

# <codecell>

prob = Problem()
prob.addVariables([ 
 "D",
 "O",
 "N",
 "A",
 "L",
 "G",
 "E",
 "R",
 "B",
 "T"], [0,1,2,3,4,5,6,7,8,9])

# <codecell>

prob.addConstraint(AllDifferentConstraint())
prob.addConstraint(lambda D, G, R: D != 0 and G != 0 and R != 0, ["D", "G", "R"]) 

# <codecell>

prob.addConstraint(lambda D, O, N, A, L, G, E, R, B, T: 
                   100000*D + 10000*O + 1000*N + 100*A + 10*L + D + 100000*G + 10000*E + 1000*R + 100*A + 10*L + D
                   == 100000*R + 10000*O + 1000*B + 100*E + 10*R + T, 
                   ["D", "O", "N", "A", "L", "G", "E", "R", "B", "T"])

# <codecell>

prob.addConstraint(lambda D, G: D + G < 10, ["D", "G"])
prob.addConstraint(lambda T: T % 2 == 0, ["T"])

# <codecell>

start = time.time()
sol = prob.getSolution()
stop = time.time()

print "temps de calcul = %.3f secondes" % (stop - start)

# <codecell>

print "  DONALD \t   %d%d%d%d%d%d" % (sol["D"], sol["O"], sol["N"], sol["A"], sol["L"], sol["D"])
print "+ GERALD \t + %d%d%d%d%d%d" % (sol["G"], sol["E"], sol["R"], sol["A"], sol["L"], sol["D"])
print "-------- \t --------"
print "= ROBERT \t = %d%d%d%d%d%d" % (sol["R"], sol["O"], sol["B"], sol["E"], sol["R"], sol["T"])

# <codecell>


