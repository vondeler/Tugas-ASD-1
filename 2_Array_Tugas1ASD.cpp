#include <iostream>

using namespace std;

class ListArray {
private:
    int* data;
    int _ukuran;
    int kapasitas;

    void perbesar() {
        int kapasitasBaru = (kapasitas == 0) ? 1 : kapasitas * 2;
        int* dataBaru = new int[kapasitasBaru];

        for (int i = 0; i < _ukuran; i++) {
            dataBaru[i] = data[i];
        }

        delete[] data;
        
        data = dataBaru;
        kapasitas = kapasitasBaru;
    }

public:
    ListArray(int kapAwal = 2) {
        kapasitas = kapAwal;
        _ukuran = 0;
        data = new int[kapasitas];
    }

    ListArray(const ListArray&) = delete;
    ListArray& operator=(const ListArray&) = delete;

    ~ListArray() {
        delete[] data;
    }

    void sisipDepan(int x) {
        if (_ukuran == kapasitas) perbesar();
        for (int i = _ukuran; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = x;
        _ukuran++;
    }

    void sisipBelakang(int x) {
        if (_ukuran == kapasitas) perbesar();
        data[_ukuran] = x;
        _ukuran++;
    }

    int ambil(int i) const {
        if (i < 0 || i >= _ukuran) return -1;
        return data[i];
    }

    bool hapusDepan() {
        if (_ukuran == 0) return false;
        for (int i = 0; i < _ukuran - 1; i++) {
            data[i] = data[i + 1];
        }
        _ukuran--;
        return true;
    }

    bool hapusNilai(int k) {
        for (int i = 0; i < _ukuran; i++) {
            if (data[i] == k) {
                for (int j = i; j < _ukuran - 1; j++) {
                    data[j] = data[j + 1];
                }
                _ukuran--;
                return true;
            }
        }
        return false;
    }

    int cari(int k) const {
        for (int i = 0; i < _ukuran; i++) {
            if (data[i] == k) return i;
        }
        return -1;
    }

    int ukuran() const {
        return _ukuran;
    }

    void cetak() const {
        cout << "[ ";
        for (int i = 0; i < kapasitas; i++) {
            if (i < _ukuran) {
                cout << data[i] << " ";
            } else {
                cout << "... ";
            }
        }
        cout << "] (n=" << _ukuran << ", kap=" << kapasitas << ")\n";
    }

    bool verifikasiInternal() const {
        return (_ukuran >= 0 && _ukuran <= kapasitas && data != nullptr);
    }
};

int gagal = 0;

void cek(const char* nama, bool kondisi) {
    cout << "  [" << (kondisi ? "LULUS" : "GAGAL") << "] " << nama << "\n";
    if (!kondisi) gagal++;
}

void periksa(const ListArray& l, const char* label) {
    cout << label << "\n";
    cout << "  cetak :"; l.cetak();
    bool ok = l.verifikasiInternal();
    cout << "  verifikasi array: " << (ok ? "OK" : "GAGAL") << "\n\n";
    if (!ok) gagal++;
}

int main() {
    cout << "=== MENGISI TABEL PENGUJIAN SOAL 4 ===\n\n";
    ListArray list;

    // Skenario 1
    periksa(list, "Skenario 1: List Kosong");
    cek("hapusDepan pada list kosong bernilai false", !list.hapusDepan());

    // Skenario 2
    list.sisipBelakang(10);
    periksa(list, "Skenario 2: Satu elemen (setelah sisipBelakang 10)");

    // Skenario 3
    list.sisipDepan(5);
    periksa(list, "Skenario 3: Sisip depan (setelah sisipDepan 5)");

    // Skenario 4
    list.hapusDepan();
    periksa(list, "Skenario 4: Hapus depan (5 dihapus, sisa 10)");

    // Skenario 5
    list.sisipBelakang(20);
    list.sisipBelakang(30);
    cout << "Skenario 5: Operasi pada elemen terakhir\n";
    cout << "  ambil elemen terakhir: " << list.ambil(list.ukuran() - 1) << "\n";
    list.hapusNilai(30);
    periksa(list, "  setelah hapusNilai elemen terakhir (30)");

    // Skenario 6
    cout << "Skenario 6: Kunci tidak ditemukan\n";
    cek("hapusNilai(99) bernilai false", !list.hapusNilai(99));
    periksa(list, "  kondisi list tetap utuh");

    // Skenario 7
    list.sisipDepan(1);
    list.sisipBelakang(40);
    list.hapusDepan();
    list.hapusNilai(20);
    cout << "Skenario 7: Urutan campuran (SisipDepan, SisipBelakang, HapusDepan, HapusNilai)\n";
    periksa(list, "  hasil akhir urutan campuran");

    cout << "Ringkasan\n";
    if (gagal == 0) cout << "SEMUA PENGECEKAN LULUS\n";
    else cout << "JUMLAH GAGAL: " << gagal << "\n";

    return gagal == 0 ? 0 : 1;
}
