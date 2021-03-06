from pulp import *
import pandas as panda
import matplotlib
matplotlib.use("qt4agg")
import matplotlib.pyplot as pPlot
import math

weatherDF = panda.read_table("OregonCityNew.csv", sep=",") #CHANGE THIS 
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
linear=0
seasonal=0
solar=0
for i in range(0,n):
	linear = (x0 + x1 * x_vals[i])
	seasonal = (x2 * math.cos(2*math.pi * x_vals[i]/364.25) + x3 * math.sin(2*math.pi * x_vals[i]/364.25))
	solar = (x4 * math.cos(2*math.pi * x_vals[i]/(364.25*10.7)) + x5 * math.sin(2*math.pi*x_vals[i]/(364.25 * 10.7)))
	prob += Td >= (linear + seasonal + solar - y_vals[i])
	prob += Td >= -(linear + seasonal + solar - y_vals[i])
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

lin = []
for i in range(n):
	lin.append(value(x0) + value(x1)*x_vals[i])

pPlot.plot(x_vals,y_vals, "bo", x_vals, bestFit, "r", x_vals, lin, "y", linewidth=5.0)
pPlot.axis([0,n,min_temp,max_temp])
pPlot.show()
