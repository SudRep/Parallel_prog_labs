import numpy as np


N = 5 # размер матрицы N x N

A = np.random.randint(1, 11,(N,N))
B = np.random.randint(1, 11,(N,N))

np.savetxt("Matrix_A.txt", A, fmt="%d", header=str(N), comments="")
np.savetxt("Matrix_B.txt", B, fmt="%d", header=str(N), comments="")

print(f"\nФайлы матриц {N}x{N} успешно созданы!")