#include <iostream>
#include <conio.h> // include library untuk getch
#include <cstring> // include library untuk strcmp
using namespace std;
char loop;

// Struktur untuk nilai mahasiswa
struct Nilai {
    double absen, tugas, uts, uas, akhir;
    char huruf;
};

// Struktur untuk data mahasiswa
struct Mahasiswa {
    char nama[100]; // nama menggunakan array karakter
    char npm[20];   // NPM menggunakan array karakter
    Nilai nilai;
    Mahasiswa* next;
};

// Fungsi untuk menampilkan garis pembatas
void line() {
    cout << "==========================================================" << endl;
}

// Fungsi untuk menampilkan header pada tiap pilihan program
void kepala() {
    line();
    cout << "||              DATA MAHASISWA INFORMATIKA              ||" << endl;
    line();
}

// Fungsi untuk menambahkan data mahasiswa
void tambahData(Mahasiswa*& head, Mahasiswa*& tail, int& jumlahData) {
    do {
        Mahasiswa* baru = new Mahasiswa;
        cout << "Masukkan NPM           : "; cin >> baru->npm;

        // Memeriksa apakah NPM sudah ada dalam linked list
        Mahasiswa* current = head;
        bool npmExists = false;
        while (current != nullptr) {
            if (strcmp(current->npm, baru->npm) == 0) {
                npmExists = true;
                break;
            }
            current = current->next;
        }
        if (npmExists) {
            line();
            cout << "NPM sudah terpakai. Mohon masukkan data yang berbeda." << endl;
            line();
            delete baru;
            continue; // Melanjutkan iterasi untuk meminta NPM yang baru
        }

        cout << "Masukkan Nama          : "; cin.ignore(); cin.getline(baru->nama, 100);

        // Memeriksa apakah nama sudah ada dalam linked list
        current = head;
        bool nameExists = false;
        while (current != nullptr) {
            if (strcmp(current->nama, baru->nama) == 0) {
                nameExists = true;
                break;
            }
            current = current->next;
        }
        if (nameExists) {
            line();
            cout << "Nama sudah terpakai. Mohon masukkan data yang berbeda." << endl;
            line();
            delete baru;
            continue; // Melanjutkan iterasi untuk meminta data yang baru
        }

        cout << "Masukkan Nilai Absen   : "; cin >> baru->nilai.absen;
        cout << "Masukkan Nilai Tugas   : "; cin >> baru->nilai.tugas;
        cout << "Masukkan Nilai UTS     : "; cin >> baru->nilai.uts;
        cout << "Masukkan Nilai UAS     : "; cin >> baru->nilai.uas;

        // Menghitung nilai akhir
        baru->nilai.akhir = (0.1 * baru->nilai.absen) + (0.2 * baru->nilai.tugas) + (0.3 * baru->nilai.uts) + (0.4 * baru->nilai.uas);

        if (baru->nilai.akhir > 80)
            baru->nilai.huruf = 'A';
        else if (baru->nilai.akhir > 70)
            baru->nilai.huruf = 'B';
        else if (baru->nilai.akhir > 60)
            baru->nilai.huruf = 'C';
        else
            baru->nilai.huruf = 'D';

        baru->next = nullptr;

        if (head == nullptr) { // Jika linked list masih kosong
            head = baru;
            tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }
        jumlahData++;

        line();
        cout << "Data Berhasil ditambahkan." << endl;
        line();
        cout <<"Apakah Ingin menambahkan lagi? (y/t): "; cin >>loop;
        line();
    } while ((loop == 'y') || (loop == 'Y'));
}

// Fungsi untuk menampilkan data mahasiswa
void tampilData(Mahasiswa* head, int jumlahData) {
    if (jumlahData > 0) {
        int i = 0;
        while (head != nullptr) {
            cout << "Data ke-" << i+1 << endl;
            cout << "NPM          : " << head->npm << endl;
            cout << "Nama         : " << head->nama << endl;
            cout << "Nilai Absen  : " << head->nilai.absen << endl; 
            cout << "Nilai Tugas  : " << head->nilai.tugas << endl;
            cout << "Nilai UTS    : " << head->nilai.uts << endl;
            cout << "Nilai UAS    : " << head->nilai.uas << endl;
            cout << "Nilai Akhir  : " << head->nilai.akhir << endl;
            cout << "Nilai Mutu   : " << head->nilai.huruf << "\n"<< endl;
            head = head->next;
            i++;
        }
    } else {
        cout << "Belum ada data." << endl;
    }
}

// Fungsi untuk mengedit data mahasiswa
void editData(Mahasiswa* head, char* npm) {
    Mahasiswa* current = head;
    while (current != nullptr && strcmp(current->npm, npm) != 0) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Data mahasiswa tidak ditemukan." << endl;
        return;
    }

    cout << "Masukkan Nama         : "; cin.ignore(); cin.getline(current->nama,100);
    cout << "Masukkan Nilai Absen  : "; cin >> current->nilai.absen;
    cout << "Masukkan Nilai Tugas  : "; cin >> current->nilai.tugas;
    cout << "Masukkan Nilai UTS    : "; cin >> current->nilai.uts;
    cout << "Masukkan Nilai UAS    : "; cin >> current->nilai.uas;

    // Menghitung nilai akhir
    current->nilai.akhir = (0.1 * current->nilai.absen) + (0.2 * current->nilai.tugas) + (0.3 * current->nilai.uts) + (0.4 * current->nilai.uas);

    if (current->nilai.akhir > 80)
        current->nilai.huruf = 'A';
    else if (current->nilai.akhir > 70)
        current->nilai.huruf = 'B';
    else if (current->nilai.akhir > 60)
        current->nilai.huruf = 'C';
    else
        current->nilai.huruf = 'D';

    line();
    cout << "Data berhasil diubah." << endl;
}

// Fungsi untuk menghapus data mahasiswa
void hapusData(Mahasiswa*& head, int& jumlahData, char* npm) {
    if (head == nullptr) {
        cout << "Data tidak ditemukan." << endl;
        return;
    }

    Mahasiswa* prev = nullptr;
    Mahasiswa* curr = head;

    while (curr != nullptr && strcmp(curr->npm, npm) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        cout << "Data tidak ditemukan." << endl;
        return;
    }

    if (prev == nullptr) {
        head = head->next;
    } else {
        prev->next = curr->next;
    }

    delete curr;
    jumlahData--;
    cout << "Data berhasil dihapus." << endl;
}

// Fungsi untuk membersihkan atau mengosongkan memori yang digunakan oleh program
void hapusSemuaData(Mahasiswa*& head) {
    while (head != nullptr) {
        Mahasiswa* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Mahasiswa* head = nullptr;
    Mahasiswa* tail = nullptr;
    int jumlahData = 0;
    int pilihan;
    char npm[20];

    do {
        kepala();
        cout << "||                     MENU PROGRAM                     ||"<< endl;
        line();
        cout << "||  1.Tambahkan Data Mahasiswa                          ||" << endl;
        cout << "||  2.Tampilkan Data Mahasiswa                          ||" << endl;
        cout << "||  3.Edit Data Mahasiswa                               ||" << endl;
        cout << "||  4.Hapus Data Mahasiswa                              ||" << endl;
        cout << "||  5.Keluar                                            ||" << endl;
        line();
        cout << "Pilih Menu (1-5): "; cin >> pilihan;

        system("cls");
        switch (pilihan) {
            case 1:
                kepala();
                tambahData(head, tail, jumlahData);
                cout << "Tekan Backspace untuk Kembali ke Menu";
                getch();
                system("cls");
                break;
            case 2:
                kepala();
                tampilData(head, jumlahData);
                line();
                cout << "Tekan Backspace untuk Kembali ke Menu";
                getch();
                system("cls");
                break;
            case 3:
                kepala();
                if (jumlahData > 0) {
                    do {
                        cout << "Masukkan NPM          : "; cin >> npm;
                        line();
                        editData(head, npm);
                        line();
                        cout <<"Apakah Ingin mengedit lagi? (y/t): "; cin >>loop;
                        line();
                    } while ((loop == 'y') || (loop == 'Y'));
                } else {
                    cout << "Belum ada data." << endl;
                    line();
                }
                cout << "Tekan Backspace untuk Kembali ke Menu";
                getch();
                system("cls");
                break;
            case 4:
                kepala();
                if (jumlahData > 0) {
                    do{
                        cout << "Masukkan NPM : "; cin >> npm;
                        line();
                        hapusData(head, jumlahData, npm);
                        line();
                        cout <<"Apakah Ingin menghapus lagi? (y/t): "; cin >>loop;
                        line();
                    } while ((loop == 'y') || (loop == 'Y'));
                } else {
                    cout << "Belum ada data." << endl;
                    line();
                }
                cout << "Tekan Backspace untuk Kembali ke Menu";
                getch();
                system("cls");
                break;
            case 5:
                hapusSemuaData(head);
                cout << "\n\tPROGRAM SELESAI. TERIMA KASIH!\t\n" << endl;
                break;
            default:
                kepala();
                cout << "Pilihan tidak valid." << endl;
                line();
                cout << "Tekan Backspace untuk Kembali ke Menu";
                getch();
                system("cls");
                break;
        }
    } while (pilihan != 5);
    return 0;
}