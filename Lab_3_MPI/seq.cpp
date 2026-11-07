#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include <chrono>

using namespace std;

void ReaderMatrix(const string& FilePath, int& N, vector<int>& M) {
    ifstream file(FilePath);
    if (!file.is_open()) throw runtime_error("Не удалось открыть файл: " + FilePath);
    file >> N;
    M.resize(N * N);
    for (int i = 0; i < N * N; ++i) {
        file >> M[i];
    }
    file.close();
}

void WriterMatrix(const string& FilePath, int N, const vector<int>& M) {
    ofstream file(FilePath);
    if (!file.is_open()) throw runtime_error("Не удалось создать файл");
    file << N << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file << M[i * N + j] << " ";
        }
        file << endl;
    }
    file.close();
}

int main() {
    int N = 0;
    vector<int> A, B, C;

    try {
        ReaderMatrix("Matrix_A.txt", N, A);
        ReaderMatrix("Matrix_B.txt", N, B);
        C.resize(N * N, 0);

        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                int a = A[i * N + k];
                for (int j = 0; j < N; ++j) {
                    C[i * N + j] += a * B[k * N + j];
                }
            }
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;

        WriterMatrix("Result_Seq.txt", N, C);

        cout << "Последовательная программа" << endl;
        cout << "Размер матрицы: " << N << " x " << N << endl;
        cout << "Время выполнения: " << diff.count() << " сек" << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}