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

	tbl = {}
	tbl[0, 0] = 0
	bt = {}
        bt[0,0] = 0
	for i in range(1, m+1):
		tbl[i, 0] = tbl[i-1, 0] + int(costDelete(str1, costMatrix, i-1))
		bt[i, 0] = "D"
	for j in range(1, n+1):
		tbl[0, j] = tbl[0, j-1] + int(costInsert(str2, costMatrix, j-1))
		bt[0, j] = "I"
	for i in range(1, m+1):
		for j in range(1, n+1):
			val1 = tbl[i-1, j] + int(costDelete(str1, costMatrix, i-1))
			val2 = tbl[i, j-1] + int(costInsert(str2, costMatrix, j-1))
			val3 = tbl[i-1, j-1] + int(costAlign(str1, str2, costMatrix, i-1, j-1))
			tbl[i, j] = min(val1, val2, val3)


			if(tbl[i, j] == val1):
                                bt[i,j] = "D"
			elif(tbl[i, j] == val2):
                                bt[i,j] = "I"
                        else:
                                bt[i,j] = "A"
	return tbl[i, j], bt
	

##############MAIN##################

def main(argv):
	inputDataFile = "imp2input.txt"
	inputMatrixFile = "imp2cost.txt"
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
	outfile = open('imp2output.txt', 'w')
	for line in f:
		minseq1 = ''
		minseq2 = ''
		tracestr = ''
		bt = {}
		line.rstrip()
		temp = line.split(',')
		seq1 = temp[0]
		seq2 = temp[1]
		seq2 = seq2[:-1]
		med, bt = editDistance(seq1, seq2, costMatrix)		#editDistance returns min edit dist and backtrace table
		m = len(seq1)
		n = len(seq2)
		while(m > 0 or n > 0):			#loops through backtrace to build the backtrace string
			if(bt[m, n] == 'I'):
				n -= 1
				tracestr = 'I' + tracestr
			elif(bt[m, n] == 'D'):
				m -= 1
				tracestr = 'D' + tracestr
			elif(bt[m, n] == 'A'):
				m -= 1
				n -= 1
				tracestr = 'A' + tracestr
		if(m==0 and n!=0):			#if n or m doesn't reach 0, loops until they are both 0
			for i in range(n):
				n -= 1
				tracestr = 'I' + tracestr
		elif(n==0 and m!=0):
			for i in range(m):		
				m -= 1
				tracestr = 'D' + tracestr
		j = 0
		for i in range(0,len(tracestr)):	#builds the first edited string using the backtrace string
			if(tracestr[i] == 'I'):
				minseq1 = minseq1 + '-'
			elif(tracestr[i] == 'D'):
				minseq1 = minseq1 + seq1[j]
				j += 1
			else:
				minseq1 = minseq1 + seq1[j]
				j += 1
		
		j = 0
		for i in range(0,len(tracestr)):	#builds the second edited string
			if(tracestr[i] == 'I'):
				minseq2 = minseq2 + seq2[j]
				j += 1
			elif(tracestr[i] == 'D'):
				minseq2 = minseq2 + '-'
			else:
				minseq2 = minseq2 + seq2[j]
				j += 1	
		final = minseq1 + ',' + minseq2 + ':' + str(med)
		outfile.write(final+'\n')
	f.close()
	

if __name__ == "__main__":
	main(sys.argv[1:])
