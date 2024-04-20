#!/usr/bin/env python3 

import numpy as np

def solution(matrix):
    pass

















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

