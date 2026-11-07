import numpy as np
import os

sizes = [200, 400, 600, 1200, 1600, 2000]

print("Верификации результатов с суперкомпьютера:\n")

for size in sizes:
    folder = f"size_{size}"
    matrix_a_path = os.path.join(folder, "Matrix_A.txt")
    matrix_b_path = os.path.join(folder, "Matrix_B.txt")

    result_path = os.path.join("MPI_results", str(size), f"Result_{size}.txt")

    A = np.loadtxt(matrix_a_path, skiprows=1)
    B = np.loadtxt(matrix_b_path, skiprows=1)
    C_cpp = np.loadtxt(result_path, skiprows=1)

    C_python = A @ B


    if np.allclose(C_cpp, C_python):
        print(f"✅ {size}x{size}: Результат совпал!")
    else:
        print(f"❌ {size}x{size}: ОШИБКА! Результаты не совпали.")

print("\nВерификация завершена!")