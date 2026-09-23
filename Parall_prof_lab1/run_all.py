import subprocess
import numpy as np
import os

exe_path = os.path.join("x64", "Debug", "Parallel_prog_Lab_1.exe")

result = subprocess.run([exe_path], capture_output=True, text=True)
if result.returncode != 0:
    print("Ошибка при запуске C++ программы!")
    print(result.stderr)
else:
    print(result.stdout)
    A = np.loadtxt('Matrix_A.txt', skiprows=1)
    B = np.loadtxt('Matrix_B.txt', skiprows=1)
    C_cpp = np.loadtxt('Result_Matrix.txt', skiprows=1)
    C_python = A @ B
    print("Матрица программы С++: ")
    print(C_cpp)
    print("Матрица программы Python: ")
    print(C_python)

    if np.allclose(C_cpp, C_python):
        print("\n✅Результат совпал✅")
    else:
        print("\n❌Результат не совпал❌")