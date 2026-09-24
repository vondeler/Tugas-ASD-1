#include <iostream>

struct Memory{
        int data;
        Memory* next;
        Memory* prev;
};

class ListDoubly{
private:
        Memory* head;
        Memory* tail;
        int banyakNode;

        void hapusMemory(Memory* target){

                if (target == nullptr) return;

                if (target->prev != nullptr){
                        target->prev->next = target->next;
                } else {
                        head = target->next;
                }

                if (target->next != nullptr){
                        target->next->prev = target->prev;
                } else {
                        tail = target->prev;
                }

                delete target;
                banyakNode--;

        }

public:

        ListDoubly(){
                head = nullptr;
                tail = nullptr;
                banyakNode = 0;
        }

        ListDoubly(const ListDoubly&) = delete;
        ListDoubly& operator=(const ListDoubly&) = delete;

        ~ListDoubly(){
                Memory* current = head;
                while (current != nullptr)
                {
                        Memory* next = current->next;
                        delete current;
                        current = next;
                }
        }
        
        void sisipDepan(int x){
                Memory* baru = new Memory;
                baru->data = x;
                baru->next = head;
                baru->prev = nullptr;

                if (head != nullptr) {
                        head->prev = baru;
                } else {
                        tail = baru;
                }

                head = baru;
                banyakNode++;
        }

        void sisipBelakang(int x){
                Memory* baru = new Memory;
                baru->data = x;
                baru->next = nullptr;
                baru->prev = tail;

                if (tail != nullptr) {
                        tail->next = baru;
                } else {
                        head = baru;
                }

                tail = baru;
                banyakNode++;
        }

        int ambil(int i) const {
                Memory* p = head;

                if (i < 0 || i >= banyakNode) {
                        return -1;
                }

                for (int j = 0; j < i; j++) {
                        p = p->next;
                }

                return p->data;
        }

        int cari(int k) const {
                Memory* p = head;
                int indeks = 0;

                while (p != nullptr) {
                        if (p->data == k) {
                                return indeks;
                        }

                        p = p->next;
                        indeks++;
                }

                return -1;
        }

        bool hapusDepan() {
                if (head == nullptr) {
                        return false;
                }

                Memory* target = head;
                hapusMemory(target);

                return true;
        }

        bool hapusNilai(int k){
                Memory* p = head;

                while (p != nullptr) {
                        if (p->data == k) {
                                hapusMemory(p);
                                return true;
                        }

                        p = p->next;
                }

                return false;
        }
        
        int ukuran() const {
                return banyakNode;
        }

        void cetak() const {
                std::cout << " null <-> ";

                Memory* p = head;

                while (p != nullptr) {
                        std::cout << "[" << p->data << "] <-> ";
                        p = p->next;
                }

                std::cout << "null (n=" << banyakNode << ")\n";
        }

        void cetakMundur() const {
                std::cout << " null <-> ";

                Memory* p = tail;

                while (p != nullptr) {
                        std::cout << "[" << p->data << "] <-> ";
                        p = p->prev;
                }

                std::cout << "null\n";
        }

        bool verifikasiRantai() const {
                if (banyakNode == 0) {
                        return head == nullptr && tail == nullptr;
                }
                if (head == nullptr || tail == nullptr) {
                        return false;
                }
                
                if (head->prev != nullptr || tail->next != nullptr) {
                        return false;
                }

                int hitung = 0;
                Memory* p = head;
                Memory* sebelumnya = nullptr;

                while (p != nullptr) {
                        if (p->prev != sebelumnya) { return false;}
                        sebelumnya = p;
                        p = p->next;
                        hitung++;
                }
                        
                if (sebelumnya != tail || hitung != banyakNode) {return false;}
                        
                hitung = 0;
                p = tail;
                Memory* berikutnya = nullptr;

                while (p != nullptr) {
                        if (p->next != berikutnya) {return false;}
                        berikutnya = p;
                        p = p->prev;
                        hitung++;}

                if (berikutnya != head || hitung != banyakNode) {
                return false;}

                return true;
        }
};

int gagal = 0;
 
void cek(const char* nama, bool kondisi) {
        std::cout << "  [" << (kondisi ? "LULUS" : "GAGAL") << "] " << nama << "\n";
        if (!kondisi) gagal++;
}
 
void periksa(const ListDoubly& l, const char* label) {
        std::cout << label << "\n";
        std::cout << "  maju  :"; l.cetak();
        std::cout << "  mundur:"; l.cetakMundur();
        bool ok = l.verifikasiRantai();
        std::cout << "  verifikasi rantai: " << (ok ? "OK" : "GAGAL") << "\n\n";
        if (!ok) gagal++;
}

int main(){
        std::cout << "Pengujian Sisip Depan dan Sisip Belakang (sisipDepan dan sisipBelakang)\n";
        ListDoubly list;
        periksa(list, "Kondisi Awal masih kosong");
        list.sisipBelakang(10);
        periksa(list, "Setelah sisipBelakang(10)");
        list.sisipBelakang(20);
        periksa(list, "Setelah sisipBelakang(20)");
        list.sisipBelakang(30);
        list.sisipBelakang(40);
        periksa(list, "Setelah sisipBelakang(30), sisipBelakang(40)");
        list.sisipDepan(5);
        periksa(list, "Setelah sisipDepan(5)");
        cek("ukuran() == 5", list.ukuran() == 5);
        cek("ambil(0) == 5", list.ambil(0) == 5);

        std::cout << "Pengujian Hapus depan dan Hapus nilai (hapusDepan dan hapusNilai)\n";
        list.hapusDepan();
        periksa(list, "Setelah hapusDepan (5 hilang)");
        list.hapusNilai(10);
        periksa(list, "Setelah hapusNilai(10)");
        list.hapusNilai(20);
        periksa(list, "Setelah hapusNilai(20)");
        list.hapusNilai(30);
        periksa(list, "Setelah hapusNilai(30)");
        list.hapusNilai(40);
        periksa(list, "Setelah hapusNilai(40)");
        cek("ukuran() == 0", list.ukuran() == 0);

        std::cout << "Hapus Satu Satunya Memory/Node\n";
        list.sisipDepan(42);
        periksa(list, "list berisi satu elemen [42]");
        cek("hapusNilai(42) bernilai true", list.hapusNilai(42));
        periksa(list, "Setelah hapusNilai(42) (kembali kosong)");
        cek("ukuran() == 0", list.ukuran() == 0);

        std::cout << "Pengujian Hapus Depan Hanya Satu Memory/Node\n";
        list.sisipDepan(11);
        periksa(list, "Kondisi List berisi satu elemen [11]");
        cek("hapusDepan() dengan hanya satu elemen", list.hapusDepan());
        periksa(list, "Setelah hapusDepan() (kembali kosong)");
        cek("ukuran() == 0", list.ukuran() == 0);

        std::cout << "Pengujian Hapus Depan pada list kosong\n";
        periksa(list, "Kondisi masih kosong");
        cek("hapusDepan() pada list kosong bernilai false", !list.hapusDepan());
        periksa(list, "Setelah hapusDepan() gagal (tetap kosong)");

        std::cout << "Pengujian Hapus Nilai yang tidak ada\n";
        list.sisipDepan(15);
        list.sisipDepan(25);
        list.sisipDepan(35);
        periksa(list, "list berisi 3 elemen [35, 25, 15]");
        cek("hapusNilai(99) bernilai false", !list.hapusNilai(99));
        periksa(list, "List tidak berubah");

        std::cout << "\n Destructor (dibuat, dipakai, dihancurkan)\n";
        {
        ListDoubly d;
        for (int i = 1; i <= 5; i++) d.sisipBelakang(i * 10);
        d.sisipDepan(0);
        periksa(d, "Isi di dalam scope");
        d.hapusDepan();
        d.hapusNilai(30);
        periksa(d, "Setelah sebagian dihapus");
        std::cout << "akhir scope: destructor dipanggil\n";
        }
        {
        ListDoubly kosong;
        }
        std::cout << "list kosong juga berhasil dihancurkan\n";
 
        std::cout << "\nRingkasan\n";
        if (gagal == 0) std::cout << "SEMUA PENGECEKAN LULUS\n";
        else std::cout << "JUMLAH GAGAL: " << gagal << "\n";
        return gagal == 0 ? 0 : 1;
}

