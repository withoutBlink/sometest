
import numpy as np

lines = open('sortdata.txt', 'r').readlines()
datamap = {}
midlist = []
for line in lines :
	akey=line.split()[0]
	datamap[key] = np.array(line.split()[1:]).astype(int)
	if len(key) > 4 and akey[4] == 'a':
                midlist.append(akey[:3]+'b')
        else 
                continue

for bkey in midlist:
	ckey = bkey[:3] + 'c'
	if datamap.keys().isdisjoint(bkey) and datamap.keys().isdisjoint(ckey):
		# calculate





for line in lines :
	if len(line.split()) < 4:
		quit(1)
        numkey = line.split()[:3]
	tarkey1 = numkey + 'a'
	tarkey2 = numkey + 'b'
	tarkey3 = numkey + 'c'
	if datamap.keys().isdisjoint(tarkey1) and datamap.keys().isdisjoint(tarkey1)
        if len(key) > 4 and akey[4] == 'a':
                midlist.append(akey[:3]+'b')
        else
                continue
