#!/usr/bin/env python3

import numpy as np

def options(x,y):
    return [(x+1, y), (x-1, y), (x, y+1), (x, y-1)]

def solution(matrix):
    save1 = []
    r = 0
    c = 0

    for row in matrix:
        c=0
        for num in row:
            if(num == 1):
                save1.append((r,c))
            c+=1
        r+=1
   
    #print(save1)
    """
     [1 0 0 0 0 0]
     [0 1 0 1 1 1]
     [0 0 1 0 1 0]
     [1 1 0 0 1 0]
     [1 0 0 0 0 1]
    """

    links={}
    for x, y in save1:
        t = (x,y)
        check_list=options(x ,y)
        for x1,y1 in check_list:
            t1 = (x1,y1)
            if(t1 in save1):
                if(t in links):
                    links[t].append(t1)
                else:
                    links[t]=[]
                    links[t].append(t1)
    #print(links)
    """
    {(1, 3): [(1, 4)], (1, 4): [(2, 4), (1, 5), (1, 3)], (1, 5): [(1, 4)], (2, 4): [(3, 4), (1, 4)], (3, 0): [(4, 0), (3, 1)], (3, 1): [(3, 0)], (3, 4): [(2, 4)], (4, 0): [(3, 0)]}
    """

    saveD = []
    for x,y in save1:
        t = (x,y)

        if(x==0 or y==0):
            continue
        if(t not in links):
            matrix[x,y] = 0
            continue

        done = []
        linksArr = links[t]
        flag=True
        exited=False
        for p in linksArr:
            if(exited==True):
                break
            if([0] == 0 or p[0] == matrix.shape[0] -1 or p[1] == 0 or p[1] == matrix.shape[1] -1):
                flag=False
                break
            if(p in done):
                continue
            for k in links[p]:
                if(k[0] == 0 or k[0] == matrix.shape[0] -1 or k[1] == 0 or k[1] == matrix.shape[1] -1):
                    exited=True
                    flag=False
                    break
                if(k not in linksArr):
                    linksArr.append(k)
            done.append(p)
        if(flag == True):
            matrix[x,y] = 0

    return matrix
         


matrix = np.array([[1, 0, 0, 0, 0, 0], [0, 1, 0, 1, 1, 1,], [0, 0, 1, 0, 1, 0], [1, 1, 0, 0, 1, 0], [1, 0, 0, 0, 0, 1]])
print(matrix)
print("       |\n       |\n       |\n       V")
print(solution(matrix))

