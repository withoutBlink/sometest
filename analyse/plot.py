import matplotlib as mplt
import numpy as np
import matplotlib.pyplot as plt
import codecs

datamap = {}
lines = codecs.open('result.txt', 'r', 'gb2312').readlines()

for line in lines:
	datamap[line.split()[0]] = np.array(line.split()[1:]).astype(float)

print(str(datamap.keys()))
list = input("Input line indexs you want to draw, divide by space: \n")
plotlist = list.split()

if len(plotlist) == 0:
	print("No input found!")
	quit(1)

fig, ax = plt.subplots()
for plot in plotlist:
	y = datamap[plot]
	x = np.arange(1, len(y)+1, 1)
	curv, = ax.plot(x, y, label=plot)
	curv.set_dashes([100, 1, 5, 1])

xlabel = input('Input X-label: ')
ylabel = input('Input Y-label: ')

ax.set_xlabel(xlabel)
ax.set_ylabel(ylabel)
ax.legend()
plt.show()
