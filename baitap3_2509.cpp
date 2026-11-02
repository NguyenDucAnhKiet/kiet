#include <iostream>
using namespace std;

class Matrix {
private:
    int n;         
    double** data;  

    void allocate() {
        data = new double*[n];
        for (int i = 0; i < n; i++)
            data[i] = new double[n]();
    }

    void freeMemory() {
        if (data != nullptr) {
            for (int i = 0; i < n; i++)
                delete[] data[i];
            delete[] data;
        }
    }

public:
    Matrix(int size = 2) {
        n = size;
        allocate();
    }

    Matrix(const Matrix& m) {
        n = m.n;
        allocate();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                data[i][j] = m.data[i][j];
    }

    ~Matrix() {
        freeMemory();
    }

    Matrix& operator=(const Matrix& m) {
        if (this != &m) {
            freeMemory();
            n = m.n;
            allocate();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    data[i][j] = m.data[i][j];
        }
        return *this;
    }

    double& operator()(int i, int j) {
        return data[i][j];
    }

    const double& operator()(int i, int j) const {
        return data[i][j];
    }

    Matrix operator+(const Matrix& m) const {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res.data[i][j] = data[i][j] + m.data[i][j];
        return res;
    }

    Matrix operator-(const Matrix& m) const {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res.data[i][j] = data[i][j] - m.data[i][j];
        return res;
    }

    Matrix operator*(const Matrix& m) const {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res.data[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    res.data[i][j] += data[i][k] * m.data[k][j];
                }
            }
        }
        return res;
    }

    Matrix& operator+=(const Matrix& m) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                data[i][j] += m.data[i][j];
        return *this;
    }

    friend istream& operator>>(istream& in, Matrix& m);
    friend ostream& operator<<(ostream& out, const Matrix& m);
};

istream& operator>>(istream& in, Matrix& m) {
    cout << "Nhap cap ma tran n: ";
    in >> m.n;
    m.freeMemory();
    m.allocate();
    cout << "Nhap cac phan tu ma tran:\n";
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            in >> m.data[i][j];
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            out << m.data[i][j] << "\t";
        }
        out << endl;
    }
    return out;
}

int main() {
    Matrix m1, m2;
    cout << "--- Nhap Ma Tran 1 ---\n";
    cin >> m1;
    cout << "\n--- Nhap Ma Tran 2 ---\n";
    cin >> m2;

    cout << "\nMa tran 1:\n" << m1;
    cout << "\nMa tran 2:\n" << m2;

    cout << "\nTong (m1 + m2):\n" << m1 + m2;
    cout << "\nHieu (m1 - m2):\n" << m1 - m2;
    cout << "\nTich (m1 * m2):\n" << m1 * m2;

    m1 += m2;
    cout << "\nSau khi m1 += m2:\n" << m1;
    cout << "Phan tu tai (0, 0) cua m1: " << m1(0, 0) << endl;

    return 0;
}