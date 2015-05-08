# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <codecell>

from constraint import *

# <codecell>

prob = Problem( MinConflictsSolver())
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

# <codecell>


