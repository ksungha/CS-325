#!/usr/bin/python

import collections
import sys
import getopt

###costDelete - takes a string, cost matrix, and m and determines cost of deletion at m

def costDelete(str1, costMatrix, m):  
	if(str1[m] == 'A'):
		return int(costMatrix[0].a)
	elif(str1[m] == 'T'):
		return int(costMatrix[0].t)
	elif(str1[m] == 'G'):
		return int(costMatrix[0].g)
	elif(str1[m] == 'C'):
		return int(costMatrix[0].c)

###costInsert - takes a string, cost matrix, and n and determines cost of insertion at n

def costInsert(str2, costMatrix, n):
	if(str2[n] == 'A'):
		return int(costMatrix[1].dash)
	elif(str2[n] == 'T'):
		return int(costMatrix[2].dash)
	elif(str2[n] == 'G'):
		return int(costMatrix[3].dash)
	elif(str2[n] == 'C'):
		return int(costMatrix[4].dash)

###costAlign - takes 2 string and a cost matrix, calculates the cost of aligning them at n and m

def costAlign(str1, str2, costMatrix, n, m):
	if(str1[n] == 'A'):
		if(str2[m] == 'A'):
			return int(costMatrix[1].a)
		elif(str2[m] == 'T'):
			return int(costMatrix[1].t)
		elif(str2[m] == 'G'):
			return int(costMatrix[1].g)
		elif(str2[m] == 'C'):
			return int(costMatrix[1].c)
	elif(str1[n] == 'T'):
		if(str2[m] == 'A'):
			return int(costMatrix[2].a)
		elif(str2[m] == 'T'):
			return int(costMatrix[2].t)
		elif(str2[m] == 'G'):
			return int(costMatrix[2].g)
		elif(str2[m] == 'C'):
			return int(costMatrix[2].c)
	elif(str1[n] == 'G'):
		if(str2[m] == 'A'):
			return int(costMatrix[3].a)
		elif(str2[m] == 'T'):
			return int(costMatrix[3].t)
		elif(str2[m] == 'G'):
			return int(costMatrix[3].g)
		elif(str2[m] == 'C'):
			return int(costMatrix[3].c)
	elif(str1[n] == 'C'):
		if(str2[m] == 'A'):
			return int(costMatrix[4].a)
		elif(str2[m] == 'T'):
			return int(costMatrix[4].t)
		elif(str2[m] == 'G'):
			return int(costMatrix[4].g)
		elif(str2[m] == 'C'):
			return int(costMatrix[4].c)

###Edit Distance - takes 2 strings and costMatrix, returns minimum edit distance

def editDistance(str1, str2, costMatrix):
	m = len(str1)
	n = len(str2)

	print str1,'\n',str2
	print m,'\n',n
	tbl = {}
	tbl[0, 0] = 0
	for i in range(1, m): tbl[i, 0] = tbl[i-1, 0] + int(costDelete(str1, costMatrix, i))
	for j in range(1, n-1): tbl[0, j] = tbl[0, j-1] + int(costInsert(str2, costMatrix, j))
	for i in range(1, m):
		for j in range(1, n-1):
			val1 = tbl[i-1, j] + int(costDelete(str1, costMatrix, i))
			val2 = tbl[i, j-1] + int(costInsert(str2, costMatrix, j))
			val3 = tbl[i-1, j-1] + int(costAlign(str1, str2, costMatrix, i, j))
			tbl[i, j] = min(val1, val2, val3)
	print i,'\n',j
	return tbl[i, j]
	

##############MAIN##################

def main(argv):
	inputDataFile = ""
	inputMatrixFile = ""
	try:
      		opts, args = getopt.getopt(argv,"hi:m:",["ifile=","mfile="])
	except getopt.GetoptError:
	      	print 'usage: seqAllign.py -i <input file> -m <cost matrix file>'
      		sys.exit(2)
   	for opt, arg in opts:
      		if opt == '-h':
			print 'seqAllign.py -i <input file> -m <cost matrix file>'
         		sys.exit()
      		elif opt in ("-i", "--ifile"):
         		inputDataFile = arg
      		elif opt in ("-m", "--mfile"):
         		inputMatrixFile = arg
	if inputMatrixFile:
                f = open(inputMatrixFile,'r')
        else:
                sys.exit(2)
	costStruct = collections.namedtuple('costStruct',['dash','a','t','g','c'])
	costMatrix = []
	i = 0
	for line in f:
		if "*" in line:
			continue
		line.strip()
		temp = line.split(',')
		costMatrix.append(costStruct(int(temp[1]),int(temp[2]),int(temp[3]),int(temp[4]),int(temp[5])))
	f.close()
	# matrix data accesed via costMatrix[x].dash,costMatrix[x].a and so on
	# costMatrix[0] is cost values for -
	# costMatrix[1] is cost values for a
	# costMatrix[2] is cost values for t
	# costMatrix[3] is cost values for g
	# costMatrix[4] is cost values for c


	if inputDataFile:
		f = open(inputDataFile,'r')
	else:
		sys.exit(2)
	seqLengths = []
	for line in f:
		line.strip()
		temp = line.split(',')
		seq1 = temp[0]
		seq2 = temp[1]
		print editDistance(seq1, seq2, costMatrix)
	f.close()
	

if __name__ == "__main__":
	main(sys.argv[1:])
