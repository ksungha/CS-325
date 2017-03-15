from pulp import *
import pandas as panda
import matplotlib
matplotlib.use("qt4agg")
import matplotlib.pyplot as pPlot
import math

#####
##Read in OregonCityNew.csv file and convert it into a table
#####
weatherDF = panda.read_table("OregonCityNew.csv", sep=",")
weatherDF.drop('STATION', axis=1, inplace=True)
panda.DataFrame(weatherDF)
x_vals = weatherDF['DAY'].tolist()
y_vals = weatherDF['AVERAGE'].tolist()
n = len(x_vals)
n = len(x_vals)
max_temp = max(y_vals)
min_temp = min(y_vals)
prob = LpProblem("min abs dev", LpMinimize)
x0 = LpVariable("x0")
x1 = LpVariable("x1")
x2 = LpVariable("x2")
x3 = LpVariable("x3")
x4 = LpVariable("x4")
x5 = LpVariable("x5")
Td = LpVariable("Tdvar")
prob += Td
lin=0
seas=0
sol=0
for i in range(0,n):
	lin = (x0 + x1 * x_vals[i])
	seas = (x2 * math.cos(2*math.pi * x_vals[i]/364.25) + x3 * math.sin(2*math.pi * x_vals[i]/364.25))
	sol = (x4 * math.cos(2*math.pi * x_vals[i]/(364.25*10.7)) + x5 * math.sin(2*math.pi*x_vals[i]/(364.25 * 10.7)))
	prob += Td >= (lin + seas + sol - y_vals[i])
	prob += Td >= -(lin + seas + sol - y_vals[i])
status = prob.solve()
print "\n\nObjective of LP:%f" %(value(prob.objective))
print "Value of x0:%f" %(value(x0))
print "Value of x1:%f" %(value(x1))
print "Value of x2:%f" %(value(x2))
print "Value of x3:%f" %(value(x3))
print "Value of x4:%f" %(value(x4))
print "Value of x5:%f" %(value(x5))
bestFit = []
for i in range(n):
	bestFit.append(value(x0)+value(x1)*x_vals[i]+value(x2)*math.cos(2*math.pi*x_vals[i]/364.25)+value(x3)*math.sin(2*math.pi*x_vals[i]/364.25)+value(x4)*math.cos(2*math.pi*x_vals[i]/(364.25*10.7))+value(x5)*math.sin(2*math.pi*x_vals[i]/(364.25 * 10.7)))

linear = []
for i in range(n):
	linear.append(value(x0) + value(x1)*x_vals[i])

pPl0t.plot(x_vals,y_vals, "bo", x_vals, bestFit, "r", x_vals, linear, "y", linewidth=5.0)
pPl0t.axis([0,n,min_temp,max_temp])
pPlot.show()
