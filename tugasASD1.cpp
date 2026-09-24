#include <iostream>
#include <stdexcept>

using namespace std;

class ListArray {
private:
    int* data;      // Pointer memori array
    int _ukuran;    // Jumlah data terisi
    int kapasitas;  // Kapasitas maksimal saat ini

    // Fungsi internal memperbesar kapasitas (doubling)
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
    // Konstruktor (inisialisasi awal)
    ListArray(int kapAwal = 2) {
        kapasitas = kapAwal;
        _ukuran = 0;
        data = new int[kapasitas];
    }

    // Ini adalah Destructor: bertugas membebaskan blok memori agar tidak memory leak
    ~ListArray() {
        delete[] data;
    }

    // Menyisipkan di depan (wajib geser elemen)
    void sisipDepan(int x) {
        if (_ukuran == kapasitas) perbesar();
        for (int i = _ukuran; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = x;
        _ukuran++;
    }

    // Menyisipkan di belakang (isi slot kosong ujung)
    void sisipBelakang(int x) {
        if (_ukuran == kapasitas) perbesar();
        data[_ukuran] = x;
        _ukuran++;
    }

    // Akses elemen langsung dari indeks
    int ambil(int i) const {
        if (i < 0 || i >= _ukuran) throw out_of_range("Indeks di luar batas");
        return data[i];
    }

    // Menghapus elemen paling depan (geser ke kiri)
    bool hapusDepan() {
        if (_ukuran == 0) return false;
        for (int i = 0; i < _ukuran - 1; i++) {
            data[i] = data[i + 1];
        }
        _ukuran--;
        return true;
    }

    // Menghapus nilai k spesifik (geser ke kiri setelah ketemu)
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

    // Mencari indeks dari nilai k
    int cari(int k) const {
        for (int i = 0; i < _ukuran; i++) {
            if (data[i] == k) return i;
        }
        return -1;
    }

    // Mengembalikan jumlah elemen
    int ukuran() const {
        return _ukuran;
    }

    // Cetak dengan visualisasi slot kosong '...'
    void cetak() const {
        cout << "[ ";
        for (int i = 0; i < kapasitas; i++) {
            if (i < _ukuran) {
                cout << data[i] << " ";
            } else {
                cout << "... ";
            }
        }
        cout << "]\n";
    }
};

int main() {
    ListArray list;

    cout << "Sisip belakang 10 : ";
    list.sisipBelakang(10);
    list.cetak();

    cout << "Sisip belakang 20 : ";
    list.sisipBelakang(20);
    list.cetak();

    cout << "Sisip depan 5     : ";
    list.sisipDepan(5);
    list.cetak();

    cout << "Sisip belakang 30 : ";
    list.sisipBelakang(30);
    list.cetak();

    cout << "Sisip depan 1     : ";
    list.sisipDepan(1);
    list.cetak();

    cout << "Ambil indeks ke-3 : " << list.ambil(3) << "\n";
    
    cout << "Cari nilai 20     : Ada di indeks " << list.cari(20) << "\n";

    cout << "Hapus depan       : ";
    list.hapusDepan();
    list.cetak();

    cout << "Hapus nilai 10    : ";
    list.hapusNilai(10);
    list.cetak();

    cout << "Total elemen      : " << list.ukuran() << "\n";

    return 0;
}