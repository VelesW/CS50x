from cs50 import get_int

while True:
    number = get_int("Number: ")
    if number > 0:
        break

sum = 0

length = len(str(number))

for i in range(2, length + 1, 2):
    num = (((number % 10**i) - (number % (10 ** (i - 1)))) / (10 ** (i - 1))) * 2
    sumofdigits = (num % 10) + num // 10
    sum += sumofdigits


for i in range(1, length + 1, 2):
    num = ((number % 10**i) - (number % (10 ** (i - 1)))) / (10 ** (i - 1))
    sum += num
check = sum % 10

visa = number
amex = number
master = number

while visa >= 10:
    visa = int(visa / 10)

while amex >= 10**13:
    amex = int(amex / 10**13)

while master >= 10**14:
    master = int(master / 10**14)

if check == 0:
    if visa == 4 and (length == 13 or length == 16):
        print("VISA")
    elif length == 15 and (amex == 34 or amex == 37):
        print("AMEX")
    elif length == 16 and (51 <= master <= 55):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")
