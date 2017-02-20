#!/usr/bin/python

import collections
import sys
import getopt

def costDelete(data, x, costMatrix, n):  #Calculates the cost of aligning i with -
	if(data[x].left[n] == 'A'):
		return costMatrix[1].dash
	elif(data[x].left[n] == 'T'):
		return costMatrix[2].dash
	elif(data[x].left[n] == 'G'):
		return costMatrix[3].dash
	elif(data[x].left[n] == 'C'):
		return costMatrix[4].dash

def costInsert(data, x, costMatrix, m):	 #Calculates the cost of aligning j with -
	if(data[x].right[m] == 'A'):
		return costMatrix[1].dash
	elif(data[x].right[m] == 'T'):
		return costMatrix[2].dash
	elif(data[x].right[m] == 'G'):
		return costMatrix[3].dash
	elif(data[x].right[m] == 'C'):
		return costMatrix[4].dash

def costAlign(data, x, costMatrix, n, m):  #Calculates the cost of aligning i with j
	if(data[x].left[n] == 'A'):
		if(data[x].right[m] == 'A'):
			return costMatrix[1].a
		elif(data[x].right[m] == 'T'):
			return costMatrix[1].t
		elif(data[x].right[m] == 'G'):
			return costMatrix[1].g
		elif(data[x].right[m] == 'C'):
			return costMatrix[1].c
	elif(data[x].left[n] == 'T'):
		if(data[x].right[m] == 'A'):
			return costMatrix[2].a
		elif(data[x].right[m] == 'T'):
			return costMatrix[2].t
		elif(data[x].right[m] == 'G'):
			return costMatrix[2].g
		elif(data[x].right[m] == 'C'):
			return costMatrix[2].c
	elif(data[x].left[n] == 'G'):
		if(data[x].right[m] == 'A'):
			return costMatrix[3].a
		elif(data[x].right[m] == 'T'):
			return costMatrix[3].t
		elif(data[x].right[m] == 'G'):
			return costMatrix[3].g
		elif(data[x].right[m] == 'C'):
			return costMatrix[3].c
	elif(data[x].left[n] == 'C'):
		if(data[x].right[m] == 'A'):
			return costMatrix[4].a
		elif(data[x].right[m] == 'T'):
			return costMatrix[4].t
		elif(data[x].right[m] == 'G'):
			return costMatrix[4].g
		elif(data[x].right[m] == 'C'):
			return costMatrix[4].c


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
	seqStruct = collections.namedtuple('seqStruct',['left','right'])
	data = []
	if inputDataFile:
		f = open(inputDataFile,'r')
	else:
		sys.exit(2)
	seqLengths = []
	for line in f:
		line.strip()
		temp = line.split(',')
		data.append(seqStruct(temp[0],temp[1]))
		seqLengths.append(len(temp[0]))
		seqLengths.append(len(temp[1]))
	# sequences accessed via data[x].left and data[x].right
	f.close()
	if inputMatrixFile:
                f = open(inputMatrixFile,'r')
        else:
                sys.exit(2)
	costStruct = collections.namedtuple('costStruct',['dash','A','T','G','C'])
	costMatrix = []
	i = 0
	for line in f:
		if "*" in line:
			continue
		line.strip()
		temp = line.split(',')
		costMatrix.append(costStruct(temp[1],temp[2],temp[3],temp[4],temp[5]))
	f.close()
	# matrix data accesed via costMatrix[x].dash,costMatrix[x].a and so on
	# costMatrix[0] is cost values for -
	# costMatrix[1] is cost values for a
	# costMatrix[2] is cost values for t
	# costMatrix[3] is cost values for g
	# costMatrix[4] is cost values for c
	
	#ALGORITHM HERE
	seq = 0 #count for seqLengths, incremented with x but by 2
	for x in range(len(data)):
		D = [[0 for h in range(seqLengths[seq+1])] for g in range(seqLengths[seq])]
		for i in range(seqLengths[seq]):
			D[i][0] = i
		for j in range(seqLengths[seq+1]):
			D[0][j] = j
		for i in range(seqLengths[seq]):
			for j in range(seqLengths[seq+1]):
				D[i][j] = min(D[i-1][j] + costDelete(data, x, costMatrix, i), D[i][j-1] + costInsert(data, x, costMatrix, j), D[i-1][j-1] + costAlign(data, x, costMatrix, i, j))
		print D[len(data[x].left)][len(data[x].right)]
		seq = seq +2


if __name__ == "__main__":
	main(sys.argv[1:])
