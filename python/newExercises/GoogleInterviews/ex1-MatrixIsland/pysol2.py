#!/usr/bin/env python3

import numpy as np

def GetToEdge(save1, rc, edgesR, edgesC, visited):
    r = rc[0]
    c = rc[1]

    if(r in edgesR or c in edgesC):
        return True
    
    if(rc in visited):
        return False

    visited.append(rc)
    options = [(r+1,c), (r-1,c), (r,c+1), (r,c-1)]

    for t in options:
        if(t in save1):
            if(GetToEdge(save1, t, edgesR, edgesC, visited)):
                return True
    
    return False

def solution(matrix):
    save1 = []

    r = 0
    for row in matrix:
        c = 0
        for num in row:
            if (num == 1):
                save1.append((r,c))
            c+=1
        r+=1

    r,c = matrix.shape
    edgesR = [0, r-1]
    edgesC = [0, c-1]
    
    saveD = []
    for rc in save1:
        if(GetToEdge(save1, rc, edgesR, edgesC, []) == False):
            saveD.append(rc)

    for r,c in saveD:
        matrix[r,c] = 0

    return matrix
        


matrix = np.array([[1, 0, 0, 0, 0, 0], [0, 1, 0, 1, 1, 1,], [0, 0, 1, 0, 1, 0], [1, 1, 0, 0, 1, 0], [1, 0, 0, 0, 0, 1]])
""" [1 0 0 0 0 0]
    [0 1 0 1 1 1]
    [0 0 1 0 1 0]
    [1 1 0 0 1 0]
    [1 0 0 0 0 1]
"""
print(matrix)
print("       |\n       |\n       |\n       V")
print(solution(matrix))
