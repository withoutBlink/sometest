
import numpy as np
import codecs

lines = codecs.open('Data(公开).txt', 'r', 'gb2312').readlines()
datamap = {}
midlist = []

for line in lines : # except unwanted lines
    if len(line.strip()) == 0:
        continue
    elif line.find("应力数据") > -1:
        continue
    elif line.find("------") > -1:
        continue
    elif line.find("级 别") > -1:
        continue
    elif line.find("轴压") > -1:
        continue
    elif line.find("弯矩") > -1:
        continue
    elif line.find("剪力") > -1:
        continue
    elif line.find("内压") > -1:
        continue
    elif line.find("测点名称") > -1:
        continue
    elif line.find("序  号") > -1:
        continue
    elif line.find("wy") > -1:
        continue
    elif line.find("位移数据") > -1:
        continue
    else:
        key = line.split()[1]
        datamap[key] = np.array(line.split()[2:]).astype(float)
        if len(key) > 4 and key[4] == 'a':
            midlist.append(key[:4])

print(midlist)

for key in midlist:
    akey = key + 'a'
    bkey = key + 'b'
    ckey = key + 'c'
    if bkey in datamap and ckey in datamap:
        arr_1 = datamap[akey]
        arr_2 = datamap[bkey]
        arr_3 = datamap[ckey]
        arr_out=(((arr_1-arr_2)**2+(arr_2-arr_3)**2+(arr_3-arr_1)**2)/2)**0.5
        datamap[key+'M'] = arr_out

resultfile = codecs.open('result.txt', 'w', 'gb2312')
finlist = []
for key in datamap:
    line = str(key)+'\t'
    for col in list(datamap[key]):
        line = line + str(col) + '\t'
    finlist.append(line)

datalist = []
for line in finlist:
    datalist.append(line[1:]+":"+line[:1])
datalist.sort()
for line in datalist:
    [second,first] = line.split(":")
    resultfile.write(first+second+'\n')


