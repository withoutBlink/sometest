import matplotlib as mplt
import numpy as np
import matplotlib.pyplot as plt

datamap = {}
lines = open('sortdata.txt', 'r').readlines()

for line in lines:
	datamap[line.split()[0]] = np.array(line.split()[1:]).astype(int)


#list = input("Input id you want to draw: \n")
list = "2013a 2045a 1123b"

if len(list) == 0:
	print("No input found!")
	quit(1)

plotlist = list.split()

x_title = input("x axis title: ")
y_title = input("y axis title: ")

fig, ax = plt.subplots()
for plot in plotlist:
	y = datamap[plot]
	x = np.arange(1, 5, 1)
	line, = ax.plot(x, y, label=plot)
#	line.set_dashes([100, 1, 5, 1]) 

ax.set(xlabel=x_title, ylabel=y_title, title="Whatever it is")
ax.legend()
plt.show()
