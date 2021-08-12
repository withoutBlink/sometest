# This Python file uses the following encoding: utf-8
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

#newfile = open('./sortdata.txt')
datamap = []
lines = open('./testdata.txt','r').readlines()

for line in lines:
    datamap.append(line[1:]+":"+line[:1])
datamap.sort()

for line in datamap:
    [second,first] = line.split(":")
    newfile.write(first+second)



fig = plt.figure()
