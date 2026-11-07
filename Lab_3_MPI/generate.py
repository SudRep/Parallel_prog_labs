import os

import numpy as np

sizes = [200, 400, 600, 1200, 1600, 2000]

for N in sizes:
    folder =f"size_{N}"
    os.makedirs(folder, exist_ok=True)

    A = np.random.randint(1, 11,(N,N))
    B = np.random.randint(1, 11,(N,N))

    np.savetxt(os.path.join(folder, 'Matrix_A.txt'), A, fmt='%d', header=str(N), comments='')
    np.savetxt(os.path.join(folder, 'Matrix_B.txt'), B, fmt='%d', header=str(N), comments='')
    print(f"\nСгенерировано для N={N} успешно !")