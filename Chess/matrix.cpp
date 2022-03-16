#include "matrix.h"
#include "logManager.h"

matrix::~matrix() {
	for (int i = 0; i < N; ++i) {
		delete[] data[i];
	}
	delete[] data;
}

matrix::matrix(const matrix& a) {
	assign(a);
}

matrix::matrix(vector<vector<double>> d) {
	N = d.size();
	M = d[0].size();
	allocSpace();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			data[i][j] = d[i][j];
		}
	}
}

matrix::matrix(int n, int m, double** d) {
	N = n;
	M = m;
	allocSpace();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			data[i][j] = d[i][j];
		}
	}
}

matrix::matrix(int n, int m, double value) {
	N = n;
	M = m;
	allocSpace();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			data[i][j] = value;
		}
	}
}

matrix::matrix(vector<double> v) {
	N = v.size();
	M = 1;
	allocSpace();
	for (int i = 0; i < N; ++i) data[i][0] = v[i];
}

matrix::matrix(int n, int m, double from, double to) {
	N = n;
	M = m;
	allocSpace();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			data[i][j] = from + (double)((double)rand() / RAND_MAX) * (to - from);
		}
	}
}

matrix::matrix() {
	N = 1;
	M = 1;
	allocSpace();
	data[0][0] = 1;
}

void matrix::allocSpace() {
	data = new double* [N];
	for (int i = 0; i < N; ++i) {
		data[i] = new double[M];
	}
}

void matrix::assign(const matrix& a) {
	N = a.N;
	M = a.M;
	allocSpace();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			data[i][j] = a.data[i][j];
		}
	}
}

vector<double> matrix::toList() {
	vector<double> res;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			res.push_back(data[i][j]);
		}
	}
	return res;
}

void matrix::removeRow(int index) {
	matrix m(N-1, M);
	int y = 0;
	int shift = 0;
	while (y < N) {
		if (y == index) shift = -1;
		else {
			for (int x = 0; x < M; ++x) {
				m.data[y+shift][x] = data[y][x];
			}
		}
		++y;
	}
	assign(m);
}

void matrix::removeColumn(int index) {
	matrix m(N, M-1);
	int x = 0;
	int shift = 0;
	while (x < M) {
		if (x == index) shift = -1;
		else {
			for (int y = 0; y < N; ++y) {
				m.data[y][x+shift] = data[y][x];
			}
		}
		++x;
	}
	assign(m);
}

void matrix::swapLines(int i1, int i2) {
	double temp;
	for (int i = 0; i < M; ++i) {
		temp = data[i1][i];
		data[i1][i] = data[i2][i];
		data[i2][i] = temp;
	}
}

matrix matrix::transpose() {
	matrix temp(M, N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			temp.data[j][i] = data[i][j];
		}
	}
	return temp;
}

int matrix::toTrinagular(bool down = true) {
	int swaps = 0;
	int size = M < N ? M : N;
	double l1, l2;
	if (down) {
		for (int L1 = 0; L1 < size; ++L1) {
			for (int L2 = L1 + 1; L2 < N; ++L2) {
				l1 = data[L1][L1];
				l2 = data[L2][L1];

				if (l2 == 0) continue;
				else if (l1 == 0) {
					swapLines(L1, L2);
					++swaps;
					l1 = data[L1][L1];
					l2 = data[L2][L1];
				}
				double x = -(l2 / l1);

				for (int i = L1; i < M; ++i) {
					if (i == L1) data[L2][i] = 0;
					else data[L2][i] = data[L2][i] + data[L1][i] * x;
				}
			}
		}
	}
	else {
		for (int L1 = 1; L1 <= size - 1; ++L1) {
			for (int L2 = L1 - 1; L2 >= 0; --L2) {
				l1 = data[L1][L1];
				l2 = data[L2][L1];

				if (l2 == 0) continue;
				else if (l1 == 0) {
					swapLines(L1, L2);
					++swaps;
					l1 = data[L1][L1];
					l2 = data[L1][L2];
				}
				double x = -(l2 / l1);

				for (int i = L1; i < M; ++i) {
					if (i == L1) data[L2][i] = 0;
					else data[L2][i] = data[L2][i] + data[L1][i] * x;
				}
			}
		}
	}
	return swaps;
}

double matrix::determinant() {
	int swaps = toTrinagular();
	double ans = data[0][0];
	for (int i = 1; i < N; ++i)
	{
		ans = ans * data[i][i];
	}
	return (swaps % 2 == 0) ? ans : -ans;
}

void matrix::toUnit() {
	int size = M < N ? M : N;
	toTrinagular();
	toTrinagular(false);
	for (int i = 0; i < size; ++i) {
		double x = data[i][i];
		for (int j = 0; j < M; ++j) {
			data[i][j] = data[i][j] / x;
		}
	}
}

void matrix::fillZeroes() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			data[i][j] = 0;
		}
	}
}

matrix matrix::submatrix(int fromCol, int toCol) {
	int cols = toCol - fromCol + 1;
	matrix temp(N, cols);
	for (int i = 0; i < N; ++i) {
		for (int j = fromCol - 1; j < toCol; ++j) {
			temp.data[i][j - fromCol + 1] = data[i][j];
		}
	}
	return temp;
}

matrix matrix::inverse() {
	if (N == M) {
		matrix E(N, N);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (i != j) E.data[i][j] = 0;
				else E.data[i][j] = 1;
			}
		}
		matrix a = (*this) | E;
		a.toUnit();
		for (int i = 0; i < a.N; ++i) {
			if (a.data[i][i] == 0) {
				throw std::invalid_argument("Determinant = 0");
			}
		}
		return a.submatrix(N + 1, 2 * N);
	}
	else {
		throw std::invalid_argument("Invalid matrix dimensions");
	}
}

void matrix::toExpression() {
	string alph = "abcdefghijklmnopqrstuvwxyz";
	string sym = "";
	for (int i = 0; i < N; ++i) {
		bool check = false;
		sym = "";
		for (int j = 0; j < M; ++j) {
			if (check) sym = "+";
			double temp = data[i][j];
			string var = string(j / alph.size() + 1, alph[j % alph.size()]);
			if (j == M - 1) {
				if (check) cout << "=" << temp << endl;
			}
			else if (temp != 0) {
				if (temp == 1) cout << sym << var;
				else cout << sym << "(" << temp << ")" << var;
				if (!check) check = true;
			}
		}
	}
}

matrix matrix::gauss(matrix& A, matrix& b) {
	if (b.M == 1 && A.N == b.N) {
		matrix temp = A | b;
		cout << endl;
		cout << "Your expression:" << endl;
		temp.toExpression();
		temp.toUnit();
		bool no_sol = false;
		for (int i = temp.N - 1; i >= 0; --i) {
			bool ch = true;
			if (temp.data[i][temp.M - 1] != 0) {
				for (int j = 0; j < temp.M - 1; ++j) {
					if (temp.data[i][j] != 0) {
						ch = false;
						break;
					}
				}
				if (ch) {
					no_sol = true;
					break;
				}
			}
		}
		if (!no_sol) {
			cout << "Result:" << endl;
			temp.toExpression();
		}
		else {
			cout << "No solution" << endl;
		}
		return temp;
	}
	throw std::invalid_argument("Invalid matrix dimensions");
}

istream& operator>> (istream& in, matrix& x) {
	try {
		in >> x.N >> x.M;
		x.data = new double* [x.N];
		for (int i = 0; i < x.N; ++i) {
			x.data[i] = new double[x.M];
		}
		for (int i = 0; i < x.N; ++i) {
			for (int j = 0; j < x.M; ++j) {
				in >> x.data[i][j];
			}
		}
	}
	catch (...) {
		throw std::invalid_argument("Matrix input error");
	}
	return in;
}

ostream& operator<< (ostream& out, const matrix& x) {
	try {
		for (int i = 0; i < x.N; ++i) {
			for (int j = 0; j < x.M; ++j) {
				out << x.data[i][j] << " ";
			}
			out << endl;
		}
	}
	catch (...) {
		throw std::invalid_argument("Matrix output error");
	};
	return out;
}

matrix matrix::operator+ (const double& other) {
	matrix temp(N, M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			temp.data[i][j] = data[i][j] + other;
		}
	}
	return temp;
}

matrix matrix::operator+ (const matrix& other) {
	if (N == other.N && M == other.M) {
		matrix temp(N, M);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				temp.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return temp;
	}
	else {
		throw std::invalid_argument("Invalid matrix dimensions");
	}
}

matrix& matrix::operator+= (const matrix& other) {
	if (N == other.N && M == other.M) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return *this;
	}
	throw std::invalid_argument("Invalid matrix dimensions");
}

matrix matrix::operator| (const matrix& a) {
	if (N == a.N) {
		matrix temp(N, M + a.M);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				temp.data[i][j] = data[i][j];
			}
		}
		for (int i = 0; i < N; ++i) {
			for (int j = M; j < M + a.M; ++j) {
				temp.data[i][j] = a.data[i][j - M];
			}
		}
		return temp;
	}
	else {
		throw std::invalid_argument("Invalid matrix dimensions");
	}
}

matrix matrix::operator- (const double& other) {
	return (*this) + (-(double)other);
}

matrix matrix::operator- () {
	matrix temp(N, M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			temp.data[i][j] = -data[i][j];
		}
	}
	return temp;
}

matrix& matrix::operator= (const matrix& other) {
	if (this != &other) {
		if (N != other.N || M != other.M) {
			for (int i = 0; i < N; ++i) {
				delete[] data[i];
			}
			delete data;
			N = other.N;
			M = other.M;
			allocSpace();
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				data[i][j] = other.data[i][j];
			}
		}
	}
	return *this;
}

matrix matrix::operator-(const matrix& other) {
	return (*this + (-(matrix)other));
}

matrix matrix::operator*(const double& other) {
	matrix temp(N, M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			temp.data[i][j] = data[i][j] * other;
		}
	}
	return temp;
}

matrix matrix::operator/(const double& other) {
	if ((double)other != 0) return (*this) * ((double)1 / other);
	throw std::invalid_argument("divide by zero");
}


bool matrix::operator== (const matrix& other) {
	return (N == other.N && M == other.M && data == other.data);
}

matrix matrix::operator*(const matrix& other) {
	if (M == other.N) {
		matrix temp(N, other.M);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < other.M; ++j) {
				for (int k = 0; k < M; ++k) {
					temp.data[i][j] = temp.data[i][j] + data[i][k] * other.data[k][j];
				}
			}
		}
		return temp;
	}
	else if (N == other.N && M == other.M) {
		matrix temp(N, M);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				temp.data[i][j] = data[i][j] * other.data[i][j];
			}
		}
		return temp;
	}
	throw std::invalid_argument("Invalid matrix dimensions");
}

string matrix::toString() {
	string res = "("+to_string(N)+";"+to_string(M)+")\n";
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			res += to_string(data[i][j])+" ";
		}
		res += "\n";
	}
	return res;
}