#include <iostream>
#include <string>
using namespace std;

class HocSinh {
private:
    string hoTen;
    string ngaySinh;
    float toan, ly, hoa;

public:
    HocSinh(string ht = "", string ns = "", float t = 0,
            float l = 0, float h = 0)
    {
        hoTen = ht;
        ngaySinh = ns;
        toan = t;
        ly = l;
        hoa = h;
    }

    float diemTB() const {
        return (toan + ly + hoa) / 3;
    }

    bool operator>(const HocSinh& hs) const {
        return diemTB() > hs.diemTB();
    }

    bool operator<(const HocSinh& hs) const {
        return diemTB() < hs.diemTB();
    }

    bool operator==(const HocSinh& hs) const {
        return hoTen == hs.hoTen;
    }

    friend istream& operator>>(istream& in, HocSinh& hs) {
        cout << "Ho ten: ";
        getline(in >> ws, hs.hoTen);

        cout << "Ngay sinh: ";
        getline(in, hs.ngaySinh);

        cout << "Diem Toan: ";
        in >> hs.toan;

        cout << "Diem Ly: ";
        in >> hs.ly;

        cout << "Diem Hoa: ";
        in >> hs.hoa;

        return in;
    }

    friend ostream& operator<<(ostream& out, const HocSinh& hs) {
        out << hs.hoTen << "\t"
            << hs.ngaySinh << "\t"
            << hs.toan << "\t"
            << hs.ly << "\t"
            << hs.hoa << "\t"
            << hs.diemTB();

        return out;
    }
};

template<class T>
class Array {
private:
    int size;
    T* data;

public:

    Array() {
        size = 0;
        data = NULL;
    }

    Array(int n) {
        size = n;
        data = new T[size];

        for (int i = 0; i < size; i++)
            data[i] = T();
    }

    Array(T arr[], int n) {
        size = n;
        data = new T[size];

        for (int i = 0; i < size; i++)
            data[i] = arr[i];
    }

    Array(const Array& other) {
        size = other.size;

        data = new T[size];

        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    ~Array() {
        delete[] data;
    }

    Array& operator=(const Array& other) {

        if (this != &other) {

            delete[] data;

            size = other.size;

            data = new T[size];

            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }

        return *this;
    }

    T& operator[](int index) {
        return data[index];
    }

    int operator()(const T& x) {
        for (int i = 0; i < size; i++)
            if (data[i] == x)
                return i;

        return -1;
    }

    void sort(bool ascending = true) {

        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {

                bool condition;

                if (ascending)
                    condition = data[i] > data[j];
                else
                    condition = data[i] < data[j];

                if (condition) {
                    T temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }

    friend istream& operator>>(istream& in, Array<T>& a) {

        for (int i = 0; i < a.size; i++) {
            cout << "\nHoc sinh thu " << i + 1 << ":\n";
            in >> a.data[i];
        }

        return in;
    }

    friend ostream& operator<<(ostream& out,
                               const Array<T>& a) {

        for (int i = 0; i < a.size; i++)
            out << a.data[i] << endl;

        return out;
    }
};

int main() {

    int n;

    cout << "Nhap so hoc sinh: ";
    cin >> n;

    Array<HocSinh> ds(n);

    cout << "\nNhap danh sach hoc sinh:\n";
    cin >> ds;

    cout << "\nDanh sach vua nhap:\n";
    cout << ds;

    cout << "\nSap xep tang dan theo diem trung binh:\n";
    ds.sort(true);
    cout << ds;

    cout << "\nSap xep giam dan theo diem trung binh:\n";
    ds.sort(false);
    cout << ds;

    return 0;
}