import cs50

number = cs50.get_int('Number: ')
length = len(str(number))

sum = 0
m = number

for i in range(length):
    if i % 2 == 1:
        digit = m % 10
        ddigit = digit * 2
        if ddigit > 9:
            sum = sum + 1 + ddigit % 10
        else:
            sum = sum + ddigit
    m = m // 10

v = number

for i in range(length):
    if i % 2 == 0:
        digit = v % 10
        sum = sum + digit
    v = v // 10

print(sum)

checksum = (sum % 10 == 0)

firsttwo = int(number / (10**(length - 2)))

print(length)
print(firsttwo)
print(checksum)


if length == 15 and (firsttwo == 34 or firsttwo == 37) and checksum:
    print('AMEX')

elif length == 16 and (firsttwo == 51 or firsttwo == 52 or firsttwo == 53 or firsttwo == 54 or firsttwo == 55) and checksum:
    print('MASTERCARD')

elif (length == 16 or length == 13) and firsttwo // 10 == 4 and checksum:
    print('VISA')

else:
    print('INVALID')