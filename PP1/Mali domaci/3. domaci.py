__author__ = 'popina'

# assume, name is right

fileName = raw_input("Unesite ime datoteke")
fIn = open(fileName, "r")

dic = {}
for line in fIn :
    listWord = line.split()
    for word in listWord :
        tmp = word.lower()
        dic[tmp] = dic.get(tmp, 0) + 1
fIn.close()

list = []
for key in dic :
    list.append( (key, dic[key]))
for idx1 in range(0, len(list) - 1) :
    for idx2 in range(idx1 + 1, len(list)) :
        if (list[idx1][1] < list[idx2][1]) :
            list[idx1], list[idx2] = list[idx2], list[idx1]

for idx in range(0, 4) :
    print list[idx][0]


