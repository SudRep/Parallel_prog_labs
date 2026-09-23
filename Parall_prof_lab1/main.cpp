import std;
using namespace std;

void ReaderMatrix(const filesystem::path& FilePath, vector<vector<int>>& M) {
	if (filesystem::exists(FilePath)) {
		ifstream file(FilePath);
		if (!file.is_open()) {
			throw runtime_error("Не удалось открыть файл");
		}
		int size;
		file >> size;
		M = vector<vector<int>>(size, vector<int>(size));
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				file >> M[i][j];
			}
		}
		file.close();
	}
	else {
		throw runtime_error("Такого файла не существует");
	}
}

void PrintMatrix(const vector<vector<int>>& M) {
	for (int i = 0; i < M.size(); ++i) {
		for (int j = 0; j < M.size(); ++j) {
			print("{:3} ", M[i][j]);
		}
		println("");
	}
}

void WriterMatrix(const filesystem::path& FilePath, const vector<vector<int>>& M) {
	ofstream file(FilePath);
	if (!file.is_open())
		throw runtime_error("Не удалось создать файл");
	file << M.size() << endl;
	for (int i = 0; i < M.size(); ++i) {
		for (int j = 0; j < M.size(); ++j) {
			file << M[i][j] << " ";
		}
		file << endl;
	}
	file.close();
}

void MultiplyMatrix(const vector<vector<int>>& M_A, const vector<vector<int>>& M_B, 
	vector<vector<int>>& M_C) {
	M_C = vector<vector<int>>(M_A.size(), vector<int>(M_A.size(), 0));
	for (int i = 0; i < M_A.size(); ++i) {
		for (int k = 0; k < M_A.size(); ++k) {
			for (int j = 0; j < M_A.size(); ++j) {
				M_C[i][j] += M_A[i][k] * M_B[k][j];
			}
		}
	}

}

int main() {
	vector<vector<int>> Matrix_A;
	vector<vector<int>> Matrix_B;
	vector<vector<int>> Matrix_C;
	try {
		ReaderMatrix("Matrix_A.txt", Matrix_A);
		//PrintMatrix(Matrix_A);
		println("");
		ReaderMatrix("Matrix_B.txt", Matrix_B);
		//PrintMatrix(Matrix_B);
		println("");
		auto start = chrono::high_resolution_clock::now();
		MultiplyMatrix(Matrix_A, Matrix_B, Matrix_C);
		auto end = chrono::high_resolution_clock::now();

		chrono::duration<double, milli> result = end - start;

		//PrintMatrix(Matrix_C);
		WriterMatrix("Result_Matrix.txt", Matrix_C);
		println("Размер матрицы {} x {}", Matrix_C.size(), Matrix_C.size());
		println("Время выполнения: {}мс", result.count());
	}
	catch (exception& e) {
		println("{}", e.what());
	}
	return 0;
}