#!/usr/bin/python

import collections
import sys
import getopt

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
	for line in f:
		line.strip()
		temp = line.split(',')
		data.append(seqStruct(temp[0],temp[1]))
	# sequences accessed via data[x].left and data[x].right
	f.close()
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
		costMatrix.append(costStruct(temp[1],temp[2],temp[3],temp[4],temp[5]))
	f.close()
	# matrix data accesed via costMatrix[x].dash,costMatrix[x].a and so on
	# costMatrix[0] is cost values for -
	# costMatrix[1] is cost values for a
	# costMatrix[2] is cost values for t
	# costMatrix[3] is cost values for g
	# costMatrix[4] is cost values for c
	

	#ALGORITHM HERE
	for x in data:
		for i in data[x].left:
			for j in data[x].right:
				


if __name__ == "__main__":
	main(sys.argv[1:])
