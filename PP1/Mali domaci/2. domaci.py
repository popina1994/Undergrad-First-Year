__author__ = 'popina'

def gcd(x, y) :
    global cnt
    cnt += 1
    if (y > 0) :
        return gcd(y, x % y)
    elif (y == 0) :
        return x


uslov = raw_input("Unesite x ili Dosta za prekid ")
while (uslov != "Dosta") :
    x = int(uslov)
    y = int (raw_input("Unesite y"))
    cnt = 0
    print "NZD: ", gcd(x, y)
    print "Broj ulazaka je: ", cnt
    uslov = raw_input("Unesite x ili Dosta za prekid ")

print "Program zavrsen"