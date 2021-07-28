# This Python file uses the following encoding: utf-8

file = open('./testdata.txt')
newfile = open('./sortdata.txt')
datamap = []
lines = file.readlines()
for line in lines:
    datamap.append(line[1:]+":"+line[:1])
datamap.sort()
for line in datamap:
    [second,first] = line.split(":")
    newfile.write(first+second)
