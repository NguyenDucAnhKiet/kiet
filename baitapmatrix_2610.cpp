#include <iostream>
using namespace std;

template <class T>
class Matrix {
private:
    int n;
    T** a;

public:
    Matrix(int size = 2) {
        n = size;

        a = new T*[n];
        for (int i = 0; i < n; i++)
            a[i] = new T[n];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = 0;
    }

    Matrix(const Matrix& m) {
        n = m.n;

        a = new T*[n];
        for (int i = 0; i < n; i++)
            a[i] = new T[n];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = m.a[i][j];
    }

    ~Matrix() {
        for (int i = 0; i < n; i++)
            delete[] a[i];

        delete[] a;
    }

    Matrix& operator=(const Matrix& m) {
        if (this != &m) {

            for (int i = 0; i < n; i++)
                delete[] a[i];
            delete[] a;

            n = m.n;

            a = new T*[n];
            for (int i = 0; i < n; i++)
                a[i] = new T[n];

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    a[i][j] = m.a[i][j];
        }

        return *this;
    }

    T& operator()(int i, int j) {
        return a[i][j];
    }

    Matrix operator+(const Matrix& m) {
        Matrix result(n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result.a[i][j] = a[i][j] + m.a[i][j];

        return result;
    }

    Matrix operator-(const Matrix& m) {
        Matrix result(n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result.a[i][j] = a[i][j] - m.a[i][j];

        return result;
    }

    Matrix operator*(const Matrix& m) {
        Matrix result(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                result.a[i][j] = 0;

                for (int k = 0; k < n; k++)
                    result.a[i][j] += a[i][k] * m.a[k][j];
            }
        }

        return result;
    }

    friend istream& operator>>(istream& in, Matrix<T>& m) {
        for (int i = 0; i < m.n; i++)
            for (int j = 0; j < m.n; j++)
                in >> m.a[i][j];

        return in;
    }

    friend ostream& operator<<(ostream& out, const Matrix<T>& m) {
        for (int i = 0; i < m.n; i++) {
            for (int j = 0; j < m.n; j++)
                out << m.a[i][j] << "\t";
            out << endl;
        }

        return out;
    }
};

int main() {
    Matrix<int> A(2);
    Matrix<int> B(2);

    cout << "Nhap ma tran A:\n";
    cin >> A;

    cout << "Nhap ma tran B:\n";
    cin >> B;

    cout << "\nMa tran A:\n";
    cout << A;

    cout << "\nMa tran B:\n";
    cout << B;

    Matrix<int> C;

    C = A + B;
    cout << "\nA + B:\n";
    cout << C;

    C = A - B;
    cout << "\nA - B:\n";
    cout << C;

    C = A * B;
    cout << "\nA * B:\n";
    cout << C;

    cout << "\nA(1,1) = " << A(1,1);

    return 0;
}   