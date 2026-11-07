#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include <mpi.h>

using namespace std;

void ReaderMatrix(const string& FilePath, int& N, vector<int>& M) {
    ifstream file(FilePath);
    if (!file.is_open()) throw runtime_error("Не удалось открыть файл: " + FilePath);

    file >> N;
    int len = (N * N);
    M.resize(len);
    for (int i = 0; i < len; ++i) {
        file >> M[i];
    }
    file.close();
}

void WriterMatrix(const string& FilePath, int N, const vector<int>& M) {
    ofstream file(FilePath);
    if (!file.is_open()) throw runtime_error("Не удалось создать файл: " + FilePath);

    file << N << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file << M[i * N + j] << " ";
        }
        file << endl;
    }
    file.close();
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 0;
    vector<int> A, B, C;

    try {
        if (rank == 0) {
            ReaderMatrix("Matrix_A.txt", N, A);
            int dummyN;
            ReaderMatrix("Matrix_B.txt", dummyN, B);
        }

        MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int rows_per_proc = N / size;
        int remainder = N % size;
        vector<int> sendcounts(size), displs(size), recvcounts(size), rdispls(size);

        int offset = 0;
        for (int i = 0; i < size; ++i) {
            int rows = rows_per_proc + (i < remainder ? 1 : 0);
            sendcounts[i] = rows * N;
            displs[i] = offset;
            recvcounts[i] = sendcounts[i];
            rdispls[i] = offset;
            offset += sendcounts[i];
        }

        int local_rows = rows_per_proc + (rank < remainder ? 1 : 0);
        vector<int> local_A(local_rows * N);
        vector<int> local_C(local_rows * N, 0);

        double start_time = MPI_Wtime();

        MPI_Scatterv(rank == 0 ? A.data() : NULL, sendcounts.data(), displs.data(), MPI_INT,
            local_A.data(), local_A.size(), MPI_INT, 0, MPI_COMM_WORLD);

        if (rank != 0) B.resize(N * N);
        MPI_Bcast(B.data(), N * N, MPI_INT, 0, MPI_COMM_WORLD);

        for (int i = 0; i < local_rows; ++i) {
            for (int k = 0; k < N; ++k) {
                int a = local_A[i * N + k];
                for (int j = 0; j < N; ++j) {
                    local_C[i * N + j] += a * B[k * N + j];
                }
            }
        }

        if (rank == 0) C.resize(N * N);
        MPI_Gatherv(local_C.data(), local_C.size(), MPI_INT,
            rank == 0 ? C.data() : NULL, recvcounts.data(), rdispls.data(), MPI_INT, 0, MPI_COMM_WORLD);

        double end_time = MPI_Wtime();

        if (rank == 0) {
            WriterMatrix("Result_Matrix.txt", N, C);
            cout << "Размер матрицы: " << N << " x " << N << endl;
            cout << "Процессов: " << size << endl;
            cout << "Время выполнения: " << (end_time - start_time) << " сек" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Finalize();
    return 0;
}