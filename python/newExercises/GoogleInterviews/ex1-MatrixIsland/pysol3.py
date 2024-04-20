#!/usr/bin/env python3

import numpy as np

def options(r,c, maxr, maxc):
    l = [(r+1, c), (r-1, c), (r, c+1), (r, c-1)]
    arr = []
    for x,y in l:
        if (x <= maxr and x>=0 and y<= maxc and y>=0):
            arr.append((x,y))
    return arr
    

def addToArr(bigarr, smallarr):
    for t in smallarr:
        if(t not in bigarr):
            bigarr.append(t)
    return bigarr

def connections(matrix, rc, arr, visited):
    if(rc in visited):
        return arr
    visited.append(rc)
    r = rc[0]
    c = rc[1]
    check_list = options(r,c, matrix.shape[0] -1, matrix.shape[1] -1 )
    arr.append(rc)
    for x,y in check_list:
        if(matrix[x,y] == 1):
            connections(matrix, (x,y), arr, visited)
    return arr

    
    
def solution(matrix):
    edges=[]
    r = 0
    for row in matrix:
        c=0
        for value in row:
            if(value == 1):
                if(r == 0 or c == 0 or r == matrix.shape[0] -1 or c == matrix.shape[1] -1 ):
                    edges.append((r,c))
            c+=1
        r+=1
    """
     [1 0 0 0 0 0]
     [0 1 0 1 1 1]
     [0 0 1 0 1 0]
     [1 1 0 0 1 0]
     [1 0 0 0 0 1]
     """
    #print(edges)
    """
    [(0, 0), (1, 5), (3, 0), (4, 0), (4, 5)]
    """
    links = []
    for edge in edges:
        link = connections(matrix, edge, [], [])
        addToArr(links, link)

    r = 0
    for row in matrix:
        c=0
        for value in row:
            if(value == 1):
                if((r,c) not in links):
                    matrix[r,c]=0
            c+=1
        r+=1

    return matrix


matrix = np.array([[1, 0, 0, 0, 0, 0], [0, 1, 0, 1, 1, 1,], [0, 0, 1, 0, 1, 0], [1, 1, 0, 0, 1, 0], [1, 0, 0, 0, 0, 1]])
print(matrix)
print("       |\n       |\n       |\n       V")
print(solution(matrix))

