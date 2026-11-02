#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class Date {
private:
    int ngay, thang, nam;

public:
    Date(int ng = 1, int th = 1, int n = 2025) : ngay(ng), thang(th), nam(n) {}

    int getNgay() const { return ngay; }
    int getThang() const { return thang; }
    int getNam() const { return nam; }

    void setNgay(int ng) { ngay = ng; }
    void setThang(int th) { thang = th; }
    void setNam(int n) { nam = n; }

    friend istream& operator>>(istream& is, Date& d) {
        cout << "   - Nhap ngay: "; is >> d.ngay;
        cout << "   - Nhap thang: "; is >> d.thang;
        cout << "   - Nhap nam: "; is >> d.nam;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        os << (d.ngay < 10 ? "0" : "") << d.ngay << "/"
           << (d.thang < 10 ? "0" : "") << d.thang << "/"
           << d.nam;
        return os;
    }
};

class NhanVien {
private:
    string maNV;
    string tenNV;
    Date ngayVaoLam;
    bool gioiTinh;
    double heSoLuong;

public:
    NhanVien() : maNV("00000000"), tenNV(""), gioiTinh(false), heSoLuong(1.0) {}

    NhanVien(string ma, string ten, Date nvl, bool gt, double hsl)
        : maNV(ma), tenNV(ten), ngayVaoLam(nvl), gioiTinh(gt), heSoLuong(hsl) {}

    NhanVien(const NhanVien& nv) {
        maNV = nv.maNV;
        tenNV = nv.tenNV;
        ngayVaoLam = nv.ngayVaoLam;
        gioiTinh = nv.gioiTinh;
        heSoLuong = nv.heSoLuong;
    }

    string getmanv() const { return maNV; }
    string getTenNV() const { return tenNV; }
    double getHeSoLuong() const { return heSoLuong; }

    double tinhThamNien(int namHienTai = 2026) const {
        int soNam = namHienTai - ngayVaoLam.getNam();
        if (soNam < 0) soNam = 0;
        
        if (soNam < 5) return 0.0;
        return static_cast<double>(soNam) / 100.0;
    }

    double tinhLuong() const {
        double thamNien = tinhThamNien();
        return (heSoLuong * 2390000.0) * (1.0 + thamNien);
    }

    friend istream& operator>>(istream& is, NhanVien& nv) {
        cout << "Nhap ma nhan vien (8 ky tu): ";
        is >> nv.maNV;
        is.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nhap ho ten nhan vien: ";
        getline(is, nv.tenNV);

        cout << "Nhap ngay vao lam:\n";
        is >> nv.ngayVaoLam;

        cout << "Nhap gioi tinh (1: Nu, 0: Nam): ";
        int gt;
        is >> gt;
        nv.gioiTinh = (gt == 1);

        cout << "Nhap he so luong: ";
        is >> nv.heSoLuong;
        is.ignore(numeric_limits<streamsize>::max(), '\n');

        return is;
    }

    friend ostream& operator<<(ostream& os, const NhanVien& nv) {
        os << left << setw(10) << nv.maNV
           << setw(22) << nv.tenNV
           << setw(14) << nv.ngayVaoLam
           << setw(10) << (nv.gioiTinh ? "Nu" : "Nam")
           << setw(12) << fixed << setprecision(2) << nv.heSoLuong
           << setw(15) << fixed << setprecision(0) << nv.tinhLuong();
        return os;
    }
};

struct Node {
    NhanVien data;
    Node* next;
    Node(const NhanVien& nv) : data(nv), next(nullptr) {}
};

class List {
private:
    Node* head;

    typedef bool (*CompareFunc)(const string&, const string&);

    static bool ssBeHon(const string& a, const string& b) { return a < b; }

public:
    List() : head(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    int size() const {
        int count = 0;
        Node* curr = head;
        while (curr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    void themDau(const NhanVien& nv) {
        Node* newNode = new Node(nv);
        newNode->next = head;
        head = newNode;
    }

    void themCuoi(const NhanVien& nv) {
        Node* newNode = new Node(nv);
        if (!head) {
            head = newNode;
            return;
        }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = newNode;
    }

    void themViTriK(const NhanVien& nv, int k) {
        if (k <= 1) {
            themDau(nv);
            return;
        }
        int n = size();
        if (k > n + 1) k = n + 1;

        Node* curr = head;
        for (int i = 1; i < k - 1 && curr; ++i) {
            curr = curr->next;
        }
        if (!curr) {
            themCuoi(nv);
            return;
        }
        Node* newNode = new Node(nv);
        newNode->next = curr->next;
        curr->next = newNode;
    }

    bool xoaDau() {
        if (!head) return false;
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    bool xoaCuoi() {
        if (!head) return false;
        if (!head->next) {
            delete head;
            head = nullptr;
            return true;
        }
        Node* curr = head;
        while (curr->next->next) curr = curr->next;
        delete curr->next;
        curr->next = nullptr;
        return true;
    }

    bool xoaViTriK(int k) {
        if (!head || k < 1) return false;
        if (k == 1) return xoaDau();

        Node* curr = head;
        for (int i = 1; i < k - 1 && curr->next; ++i) {
            curr = curr->next;
        }
        if (!curr->next) return false;

        Node* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        return true;
    }

    NhanVien* operator()(const string& ma) {
        Node* curr = head;
        while (curr) {
            if (curr->data.getmanv() == ma) {
                return &(curr->data);
            }
            curr = curr->next;
        }
        return nullptr;
    }

    void sapXepChonTrucTiep(CompareFunc cmp = ssBeHon) {
        for (Node* i = head; i && i->next; i = i->next) {
            Node* target = i;
            for (Node* j = i->next; j; j = j->next) {
                if (cmp(j->data.getmanv(), target->data.getmanv())) {
                    target = j;
                }
            }
            if (target != i) {
                NhanVien temp = i->data;
                i->data = target->data;
                target->data = temp;
            }
        }
    }

    friend ostream& operator<<(ostream& os, const List& list) {
        if (!list.head) {
            os << "   [Danh sach rong!]\n";
            return os;
        }
        os << "-------------------------------------------------------------------------------\n";
        os << left << setw(10) << "Ma NV"
           << setw(22) << "Ho Ten"
           << setw(14) << "Ngay VL"
           << setw(10) << "Gioi Tinh"
           << setw(12) << "HS Luong"
           << setw(15) << "Luong (VND)" << "\n";
        os << "-------------------------------------------------------------------------------\n";

        Node* curr = list.head;
        while (curr) {
            os << curr->data << "\n";
            curr = curr->next;
        }
        os << "-------------------------------------------------------------------------------\n";
        return os;
    }
};

void hienThiMenu() {
    cout << "\n================= QUAN LY NHAN VIEN =================" << endl;
    cout << "1. Hien thi danh sach nhan vien" << endl;
    cout << "2. Them nhan vien vao dau danh sach" << endl;
    cout << "3. Them nhan vien vao cuoi danh sach" << endl;
    cout << "4. Them nhan vien vao vi tri k" << endl;
    cout << "5. Xoa nhan vien o dau danh sach" << endl;
    cout << "6. Xoa nhan vien o cuoi danh sach" << endl;
    cout << "7. Xoa nhan vien o vi tri k" << endl;
    cout << "8. Tim kiem nhan vien theo Ma NV (Toan tu ())" << endl;
    cout << "9. Sap xep chon truc tiep theo Ma NV" << endl;
    cout << "0. Thoat" << endl;
    cout << "=====================================================" << endl;
    cout << "Lua chon cua ban: ";
}

int main() {
    List ds;
    int luaChon;

    ds.themCuoi(NhanVien("003", "Nguyen Van A", Date(10, 5, 2018), false, 3.5));
    ds.themCuoi(NhanVien("001", "Tran Thi B", Date(15, 8, 2021), true, 2.8));
    ds.themCuoi(NhanVien("002", "Le Van C", Date(20, 1, 2015), false, 4.2));

    do {
        hienThiMenu();
        if (!(cin >> luaChon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le, vui long nhap lai!\n";
            continue;
        }

        switch (luaChon) {
        case 1: {
            cout << "\nDANH SACH NHAN VIEN:\n";
            cout << ds;
            break;
        }
        case 2: {
            NhanVien nv;
            cout << "\nNHAP THONG TIN NHAN VIEN THEM VAO DAU:\n";
            cin >> nv;
            ds.themDau(nv);
            cout << "=> Da them thanh cong!\n";
            break;
        }
        case 3: {
            NhanVien nv;
            cout << "\nNHAP THONG TIN NHAN VIEN THEM VAO CUOI:\n";
            cin >> nv;
            ds.themCuoi(nv);
            cout << "=> Da them thanh cong!\n";
            break;
        }
        case 4: {
            NhanVien nv;
            int k;
            cout << "Nhap vi tri k can them: "; cin >> k;
            cout << "\nNHAP THONG TIN NHAN VIEN:\n";
            cin >> nv;
            ds.themViTriK(nv, k);
            cout << "=> Da them thanh cong!\n";
            break;
        }
        case 5: {
            if (ds.xoaDau()) cout << "=> Da xoa nhan vien dau danh sach!\n";
            else cout << "=> Danh sach rong, khong the xoa!\n";
            break;
        }
        case 6: {
            if (ds.xoaCuoi()) cout << "=> Da xoa nhan vien cuoi danh sach!\n";
            else cout << "=> Danh sach rong, khong the xoa!\n";
            break;
        }
        case 7: {
            int k;
            cout << "Nhap vi tri k can xoa: "; cin >> k;
            if (ds.xoaViTriK(k)) cout << "=> Da xoa nhan vien tai vi tri " << k << "!\n";
            else cout << "=> Vi tri khong hop le hoac danh sach rong!\n";
            break;
        }
        case 8: {
            string ma;
            cout << "Nhap Ma NV can tim: "; cin >> ma;
            NhanVien* res = ds(ma);
            if (res != nullptr) {
                cout << "\n=> TIM THAY NHAN VIEN:\n";
                cout << left << setw(10) << "Ma NV" << setw(22) << "Ho Ten"
                     << setw(14) << "Ngay VL" << setw(10) << "Gioi Tinh"
                     << setw(12) << "HS Luong" << setw(15) << "Luong (VND)" << "\n";
                cout << *res << "\n";
                cout << "Dia chi bo nho cua doi tuong: " << res << "\n";
            } else {
                cout << "=> Khong tim thay nhan vien co ma " << ma << "\n";
            }
            break;
        }
        case 9: {
            ds.sapXepChonTrucTiep();
            cout << "=> Da sap xep chon truc tiep danh sach theo Ma NV tang dan!\n";
            break;
        }
        case 0:
            cout << "Cam on ban da su dung chuong trinh!\n";
            break;
        default:
            cout << "Lua chon khong hop le, vui long nhap lai!\n";
        }
    } while (luaChon != 0);

    return 0;
}