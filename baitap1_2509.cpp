#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Polynomial {
private:
    int degree;
    double* coef;

public:
    Polynomial(int deg = 0) {
        degree = deg;
        coef = new double[degree + 1]();
    }

    Polynomial(const Polynomial& p) {
        degree = p.degree;
        coef = new double[degree + 1];
        for (int i = 0; i <= degree; i++)
            coef[i] = p.coef[i];
    }

    ~Polynomial() {
        delete[] coef;
    }

    Polynomial& operator=(const Polynomial& p) {
        if (this != &p) {
            delete[] coef;
            degree = p.degree;
            coef = new double[degree + 1];
            for (int i = 0; i <= degree; i++)
                coef[i] = p.coef[i];
        }
        return *this;
    }

    Polynomial operator+(const Polynomial& p) const {
        int maxDeg = max(degree, p.degree);
        Polynomial temp(maxDeg);
        for (int i = 0; i <= maxDeg; i++) {
            double a = (i <= degree) ? coef[i] : 0;
            double b = (i <= p.degree) ? p.coef[i] : 0;
            temp.coef[i] = a + b;
        }
        return temp;
    }

    Polynomial operator-(const Polynomial& p) const {
        int maxDeg = max(degree, p.degree);
        Polynomial temp(maxDeg);
        for (int i = 0; i <= maxDeg; i++) {
            double a = (i <= degree) ? coef[i] : 0;
            double b = (i <= p.degree) ? p.coef[i] : 0;
            temp.coef[i] = a - b;
        }
        return temp;
    }

    double operator[](int index) const {
        if (index >= 0 && index <= degree)
            return coef[index];
        return 0;
    }

    double operator()(double x) const {
        double s = 0;
        for (int i = degree; i >= 0; i--) {
            s = s * x + coef[i]; 
        }
        return s;
    }

    friend istream& operator>>(istream& in, Polynomial& p);
    friend ostream& operator<<(ostream& out, const Polynomial& p);
};

istream& operator>>(istream& in, Polynomial& p) {
    cout << "Nhap bac da thuc: ";
    in >> p.degree;
    delete[] p.coef;
    p.coef = new double[p.degree + 1];
    for (int i = 0; i <= p.degree; i++) {
        cout << "He so x^" << i << ": ";
        in >> p.coef[i];
    }
    return in;
}

ostream& operator<<(ostream& out, const Polynomial& p) {
    for (int i = p.degree; i >= 0; i--) {
        out << p.coef[i];
        if (i > 0) out << "x^" << i << " + ";
    }
    return out;
}

int main() {
    Polynomial p1, p2;
    cout << "--- Nhap da thuc P1 ---\n";
    cin >> p1;
    cout << "\n--- Nhap da thuc P2 ---\n";
    cin >> p2;

    cout << "\nP1 = " << p1 << endl;
    cout << "P2 = " << p2 << endl;
    cout << "P1 + P2 = " << p1 + p2 << endl;
    cout << "P1 - P2 = " << p1 - p2 << endl;
    cout << "He so x^2 cua P1: " << p1[2] << endl;

    double x;
    cout << "Nhap x de tinh P1(x): ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1(x) << endl;

    return 0;
}