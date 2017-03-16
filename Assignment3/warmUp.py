from pulp import *
import math

# list for x and y coordinates
x_vals = [1, 2, 3, 5, 7, 8, 10]
y_vals = [3, 5, 7, 11, 14, 15, 19]

# check list values for correctness
print "\nValue of x_vals list:"
print x_vals
print "\nValue of y_vals list:"
print y_vals

# min and max for constraints
max_val = max(y_vals)
min_val = min(y_vals)
print "\nMax Value: %f\nMin Value: %f" %(max_val,min_val)
n = len(x_vals)
print "Length of n:%d" %(n)

# linear programming section
prob = LpProblem("Warm-up question", LpMinimize)
a = LpVariable("a")
b = LpVariable("b")
M = LpVariable("M")
prob += M

lin=0

for i in range(0,n):
	lin = (a * x_vals[i] + b - y_vals[i])
	prob += M >= (lin)
	prob += M >= -(lin)

print prob

# solve and print output
status = prob.solve()
print "\n\nObjective of LP:%f" %(value(prob.objective))
print "LP Status:%s" %LpStatus[prob.status]
print "Value of a:%f" %(value(a))
print "Value of b:%f" %(value(b))
