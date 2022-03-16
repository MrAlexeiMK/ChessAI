#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class matrix {
    public:
        int N, M;
        double **data;

        matrix(const matrix&);
        matrix(vector<vector<double>> d);
        matrix(int n, int m, double** d);
        matrix(int n, int m, double value = 0);
        matrix(vector<double> d);
        matrix(int n, int m, double from, double to);
        matrix();
        void allocSpace();

        ~matrix();

        matrix operator+(const double& other);
        matrix operator+(const matrix& other);
        matrix operator|(const matrix& other);
        matrix operator-(const double& other);
        matrix operator-(const matrix& other);
        matrix operator*(const matrix& other);
        matrix operator*(const double& other);
        matrix operator/(const double& other);
        matrix& operator+=(const matrix& other);
        matrix& operator=(const matrix& other);
        bool operator==(const matrix& other);
        matrix operator-();

        friend std::ostream& operator<< (std::ostream& out, const matrix& x);
        friend std::istream& operator>> (std::istream& in, matrix& x);

        void assign(const matrix& other);
        void swapLines(int i1, int i2);
        vector<double> toList();
        matrix transpose();
        int toTrinagular(bool down);
        void removeColumn(int index);
        void removeRow(int index);
        double determinant();
        void toUnit();
        void fillZeroes();
        matrix submatrix(int fromCol, int toCol);
        matrix inverse();
        matrix gauss(matrix& A, matrix& b);
        void toExpression();
        string toString();
};
#endif