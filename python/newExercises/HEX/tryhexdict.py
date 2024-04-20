#!/usr/bin/env python3

hexdict = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
hexdict2 = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', '-1']

def pythonsol(r):
    s1 = ""
    for i in range(r):
        s1+= f'{hex(i)} '

    print(s1)

"1DF --> 1E0"
"1ff --> 200"

def solution1(hexdict, r):
    s2 = ""
    num = '0x0'
    for i in range(r):
        s2 += f'{num} '
        num = num.split('x')[1]
        x = 1
        while True:
            rightd = num[len(num) -x] 
            rightI = hexdict.index(rightd) 
            nextI = rightI + 1
            if(len(num) - x == -1):
                    num = '1' + num
                    break
            if(nextI == len(hexdict)):
                helpl = list(num)
                helpl[len(num) -x] = '0'
                num = ""
                num = num.join(helpl)
            else:
                helpl = list(num)
                helpl[len(num) -x] = hexdict[nextI]
                num = ""
                num = num.join(helpl)
                break
            x+=1
        num = '0x' + num
    print(s2)

def helprec(num, hexdict2, x=1):
    if(x > len(num)):
        return '1' + num
    if(num[-x] == 'f'):
        helpl = list(num)
        helpl[-x] = '0'
        num = ""
        num = num.join(helpl)
    else:
        helpl = list(num)
        index = hexdict2.index(num[-x])
        helpl[-x] = hexdict2[index+1]
        num = ""
        num = num.join(helpl)
        return num
    return helprec(num, hexdict2, x=x+1)

def solution2(hexdict2, last ='', nums='0x0', maxiter=300, current=1):
    if(current==maxiter):
        print(nums)
        return
    if(last == ''):
        last=nums
    rightd = last[len(last) -1]
    rightI = hexdict2.index(rightd)
    nextI = rightI + 1
    nextd = hexdict2[nextI]
    newnum = ''
    if(nextd == '-1'):
        newnum = helprec(num=last.split('x')[1], hexdict2 = hexdict2)
        newnum = f'0x{newnum}'
    else:
        helpl = list(last)
        helpl[len(last) -1] = nextd
        newnum = ""
        newnum = newnum.join(helpl)
    nums = nums + f' {newnum}'
    solution2(hexdict2, last = newnum, nums=nums, current=current+1)


def DecToHexDigit(hexdict, digit):
    if(digit >= 10 and digit<= 15):
        digit=hexdict[digit]
    return digit

def DecToHexNumber(i):
    x = 16
    while x < i:
        x*=16
    x=x//16

    full = i

    num=''
    while True:
        if(x == 1):
            full = DecToHexDigit(hexdict, full)
            num+=str(full)
            break
        div = full // x
        div = DecToHexDigit(hexdict, div)
        num+=str(div)
        mul = full % x
        full = mul
        x//=16
    return num

def solution3(hexdict, r):
    """
    s3 = ""
    for i in range(100):
        div = i // 16
        mul = i % 16
        if(div >= 10 and div<= 15):
            div = hexdict[div]
        if(mul >= 10 and mul <= 15):
            mul = hexdict[mul]
        num = str(mul)
        if(div!= 0):
            num = str(div) + num
        s3+=f'0x{num} '
    print(s3)
    """
    s3 = ""
    for i in range(r):
        num='0x' + DecToHexNumber(i)
        s3+=f'{num} '
    print(s3)

pythonsol(300)
print("------------------------------------\n\nHEX\n\n------------------------------------")
solution1(hexdict, 300)
print("------------------------------------\n\nHEX\n\n------------------------------------")
solution2(hexdict2=hexdict2)
print("------------------------------------\n\nHEX\n\n------------------------------------")
solution3(hexdict, 300)



