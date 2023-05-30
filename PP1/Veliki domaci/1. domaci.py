__author__ = 'popina'

def First(list) :
    if (len(list) == 0) :
        return []

    curElem = list[0]
    curLen = 1
    longLen = 1
    longElem = list[0]

    for idx in range(0, len(list) -1) :
        if list[idx +1] == list[idx] :
            curLen += 1
        else :
            curLen = 1
            curElem = list[idx+1]
        if curLen > longLen :
            longElem = curElem
            longLen = curLen

    return [longElem] * longLen

def Second(list) :
    if (len(list) == 0) :
        print "Nista ne vazi jer je prazna"

    mean = float(0)

    for elem in list  :
        mean += elem
    mean /= len(list)
    print "Srednja vrednost je : ", mean

    val = float(0)
    for elem in list :
        val += (mean - elem) ** 2
    val /= len(list)
    import math
    print "Nesto je", math.sqrt(val)

    mostTimes = 0
    elem = -1

    for cur in list :
        cnt = 0
        for it in list :
            if (it == cur) :
                cnt += 1

        if cnt > mostTimes :
            mostTimes = cnt
            elem = cur
    print "Element koji se najvise puta pojavljuje", elem

def Third(list) :
    sol = []
    for a in list :
        for b in list :
            for c in list :
                if (a * b == c) :
                    sol.extend([a, b, c])

    return sol

print Third([2, 3, 4, 5, 6, 10])