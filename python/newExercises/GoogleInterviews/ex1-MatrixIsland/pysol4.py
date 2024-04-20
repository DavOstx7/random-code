#!/usr/bin/env python3 

import numpy as np

def options1(matrix, r,c, maxr, maxc):
    l = [(r+1, c), (r-1, c), (r, c+1), (r, c-1)]
    arr = []
    for x,y in l:
        if (x <= maxr and x>=0 and y<= maxc and y>=0):
            if(matrix[x,y] == 1):
                arr.append((x,y))
    return arr

def TryGetToEdge(matrix, rc, maxr, maxc, visited):
    if(rc in visited):
        return False
    r = rc[0]
    c = rc[1]

    visited.append(rc)
    if(r == 0 or c == 0 or r == maxr or c == maxc):

        return True
    check_list = options1(matrix,r,c,maxr,maxc)


    if(len(check_list) == 0):
        return False
    for xy in check_list:
        result = TryGetToEdge(matrix, xy, maxr, maxc, visited)
        if(result == True):
            return True
    return False

    
def solution(matrix):
    r=0
    for row in matrix:
        c=0
        for value in row:
            if(value == 1):
                if(TryGetToEdge(matrix, (r,c), matrix.shape[0]-1, matrix.shape[1]-1, []) == False): 
                    matrix[r,c]=0 #It won't effect other 1's because the 1's we delete won't have connection to the border anyway
            c+=1
        r+=1

    return matrix

"""
[[1 0 0 0 0 0]
 [0 1 0 1 1 1]
 [0 0 1 0 1 0]
 [1 1 0 0 1 0]
 [1 0 0 0 0 1]]
       |
       |
       |
       V
[[1 0 0 0 0 0]
 [0 0 0 1 1 1]
 [0 0 0 0 1 0]
 [1 1 0 0 1 0]
 [1 0 0 0 0 1]]
"""

matrix = np.array([[1, 0, 0, 0, 0, 0], [0, 1, 0, 1, 1, 1,], [0, 0, 1, 0, 1, 0], [1, 1, 0, 0, 1, 0], [1, 0, 0, 0, 0, 1]])
print(matrix)
print("       |\n       |\n       |\n       V")
print(solution(matrix))

