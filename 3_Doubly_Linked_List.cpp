#include <iostream>
#include <string>

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
                langkah = 0;

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
                langkah = 4;
        }

public:
        long long langkah;

        ListDoubly(){
                head = nullptr;
                tail = nullptr;
                banyakNode = 0;
                langkah = 0;
        };

        ~ListDoubly(){
                Memory* current = head;
                while (current != nullptr)
                {
                        Memory* next = current->next;
                        delete current;
                        current = next;
                }
        }
        
        void sisipDepan(int data){
                langkah = 0;
                Memory* baru = new Memory;
                baru->data = data;
                baru->next = head;
                baru->prev = nullptr;

                if (head != nullptr) {
                        head->prev = baru;
                } else {
                        tail = baru;
                }

                head = baru;
                banyakNode++;
                langkah = 4;
        }

        void sisipBelakang(int data){
                langkah = 0;
                Memory* baru = new Memory;
                baru->data = data;
                baru->next = nullptr;
                baru->prev = tail;

                if (tail != nullptr) {
                        tail->next = baru;
                } else {
                        head = baru;
                }

                tail = baru;
                banyakNode++;
                langkah = 4;
        }

        int ambil(int i) const {
                Memory* p = head;

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
};
