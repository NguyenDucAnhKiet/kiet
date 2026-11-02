#include <iostream>
#include <algorithm>
using namespace std;

class SET {
private:
    int n;
    int size;
    int* data;

    bool contains(int val) const {
        for (int i = 0; i < n; i++) {
            if (data[i] == val) return true;
        }
        return false;
    }

public:
    SET(int sz = 100) {
        size = sz;
        n = 0;
        data = new int[size];
    }

    SET(int arr[], int arr_size, int sz = 100) {
        size = max(sz, arr_size);
        data = new int[size];
        n = 0;
        for (int i = 0; i < arr_size; i++) {
            if (!contains(arr[i])) {
                data[n++] = arr[i];
            }
        }
    }

    SET(const SET& s) {
        size = s.size;
        n = s.n;
        data = new int[size];
        for (int i = 0; i < n; i++) data[i] = s.data[i];
    }

    ~SET() {
        delete[] data;
    }

    SET& operator=(const SET& s) {
        if (this != &s) {
            delete[] data;
            size = s.size;
            n = s.n;
            data = new int[size];
            for (int i = 0; i < n; i++) data[i] = s.data[i];
        }
        return *this;
    }

    SET operator+(int x) const {
        SET res = *this;
        if (!res.contains(x) && res.n < res.size) {
            res.data[res.n++] = x;
        }
        return res;
    }

    SET operator-(int x) const {
        SET res(size);
        for (int i = 0; i < n; i++) {
            if (data[i] != x) {
                res.data[res.n++] = data[i];
            }
        }
        return res;
    }

    SET operator+(const SET& s) const {
        SET res = *this;
        for (int i = 0; i < s.n; i++) {
            res = res + s.data[i];
        }
        return res;
    }

    SET operator-(const SET& s) const {
        SET res = *this;
        for (int i = 0; i < s.n; i++) {
            res = res - s.data[i];
        }
        return res;
    }

    SET operator*(const SET& s) const {
        SET res(max(size, s.size));
        for (int i = 0; i < n; i++) {
            if (s.contains(data[i])) {
                res.data[res.n++] = data[i];
            }
        }
        return res;
    }

    bool operator()(int x) const {
        return contains(x);
    }

    int operator[](int idx) const {
        if (idx >= 0 && idx < n) return data[idx];
        return -1;
    }

    friend ostream& operator<<(ostream& out, const SET& s) {
        out << "{ ";
        for (int i = 0; i < s.n; i++) {
            out << s.data[i] << (i == s.n - 1 ? "" : ", ");
        }
        out << " }";
        return out;
    }
};

int main() {
    int n1, n2;

    cout << "================ NHAP TAP HOP S1 ================\n";
    cout << "Nhap so luong phan tu cua S1: ";
    cin >> n1;
    int* a = new int[n1];
    cout << "Nhap " << n1 << " phan tu cho S1: ";
    for (int i = 0; i < n1; i++) {
        cin >> a[i];
    }
    SET s1(a, n1);

    cout << "\n================ NHAP TAP HOP S2 ================\n";
    cout << "Nhap so luong phan tu cua S2: ";
    cin >> n2;
    int* b = new int[n2];
    cout << "Nhap " << n2 << " phan tu cho S2: ";
    for (int i = 0; i < n2; i++) {
        cin >> b[i];
    }
    SET s2(b, n2);

    cout << "\n================ KET QUA TAP HOP ================\n";
    cout << "Tap hop S1 = " << s1 << endl;
    cout << "Tap hop S2 = " << s2 << endl;

    cout << "\n---------------- PHEP TOAN TAP HOP ----------------\n";
    cout << "Hop 2 tap hop (S1 + S2)  = " << (s1 + s2) << endl;
    cout << "Hieu 2 tap hop (S1 - S2) = " << (s1 - s2) << endl;
    cout << "Giao 2 tap hop (S1 * S2) = " << (s1 * s2) << endl;

    cout << "\n---------------- THAO TAC KHAC ----------------\n";
    int val_add, val_remove, val_check, idx;

    cout << "Nhap 1 so nguyen de THEM vao S1: ";
    cin >> val_add;
    cout << "S1 sau khi + " << val_add << " = " << (s1 + val_add) << endl;

    cout << "\nNhap 1 so nguyen de XOA khoi S1: ";
    cin >> val_remove;
    cout << "S1 sau khi - " << val_remove << " = " << (s1 - val_remove) << endl;

    cout << "\nNhap 1 so nguyen de KIEM TRA co thuoc S1: ";
    cin >> val_check;
    cout << "So " << val_check << (s1(val_check) ? " CO " : " KHONG ") << "thuoc tap S1\n";

    cout << "\nNhap chi so (index) muon truy xuat trong S1 (tu 0 den " << n1 - 1 << "): ";
    cin >> idx;
    cout << "Phan tu S1[" << idx << "] = " << s1[idx] << endl;

    delete[] a;
    delete[] b;

    return 0;
}