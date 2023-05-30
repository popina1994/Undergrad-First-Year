__author__ = 'popina'

def First() :
    sec = int (raw_input("Unesite broj sekundi"))

    DAYS_IN_MONTH = 30
    HOURS_IN_DAY = 24
    MINUTES_IN_HOUR = 60
    SEC_IN_MINUTE = 60

    month = sec / (DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR * SEC_IN_MINUTE)
    sec -= month * DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR * SEC_IN_MINUTE

    day = sec / (HOURS_IN_DAY * MINUTES_IN_HOUR * SEC_IN_MINUTE)
    sec -= day * HOURS_IN_DAY * MINUTES_IN_HOUR * SEC_IN_MINUTE

    hour = sec / (MINUTES_IN_HOUR * SEC_IN_MINUTE)
    sec -= hour * MINUTES_IN_HOUR * SEC_IN_MINUTE

    min = sec / SEC_IN_MINUTE
    sec -= min * SEC_IN_MINUTE

    print month, day, hour, min, sec
def Second() :
    a = float (raw_input("Unesite koeficijent uz x^2 "))
    b = float( raw_input("Unesite koeficijent uz x "))
    c = float( raw_input("Unesite slobodni koeficijent "))
    d = b * b - 4 * a * c

    print d, ", ",
    import math
    if (d > 0) :
        print  (- b + math.sqrt(d)) / (2 * a), ", ", (- b - math.sqrt(d)) / (2 * a)
    elif d < 0 :
        print  (- b / (2 * a)), " + ", (math.sqrt(-d)) / (2 * a), "i , ", (- b / (2 * a)), "+",  (- math.sqrt(-d)) / (2 * a), "i"
    else :
        print -b / (2 * a)
Second()
