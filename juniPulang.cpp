#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Jadwal {
    string namaMatkul;
    string namaDosen;
    string ruangKelas;
    string jamKuliah;
};

string spasiKeUnderscore(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') str[i] = '_';
    }
    return str;
}

string underscoreKeSpasi(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '_') str[i] = ' ';
    }
    return str;
}

string keLowercaseManual(string str) {
    string hasil = str;
    for (int i = 0; i < hasil.length(); i++) {
        if (hasil[i] >= 'A' && hasil[i] <= 'Z') {
            hasil[i] = hasil[i] + 32; 
        }
    }
    return hasil;
}

bool mengandungKataKunci(string teks, string kataKunci) {
    string teksLower = keLowercaseManual(teks);
    string kunciLower = keLowercaseManual(kataKunci);
    
    if (kunciLower.length() > teksLower.length()) 
		return false;
    
    for (int i = 0; i <= teksLower.length() - kunciLower.length(); i++) {
        int j;
        for (j = 0; j < kunciLower.length(); j++) {
            if (teksLower[i + j] != kunciLower[j]) 
				break;
        }
        if (j == kunciLower.length()) 
			return true; 
    }
    return false;
}

// Fungsi tulis ulang semua data ke file txt (Dipakai setelah edit atau hapus data)
void simpanUlangSemuaKeFile(const Jadwal daftarJadwal[], int jumlahData) {
    ofstream fileOutput("jadwal.txt"); 
    if (fileOutput.is_open()) {
        for (int i = 0; i < jumlahData; i++) {
            fileOutput << spasiKeUnderscore(daftarJadwal[i].namaMatkul) << " "
                       << spasiKeUnderscore(daftarJadwal[i].namaDosen) << " "
                       << spasiKeUnderscore(daftarJadwal[i].ruangKelas) << " "
                       << spasiKeUnderscore(daftarJadwal[i].jamKuliah) << "\n";
        }
        fileOutput.close();
    }
}


// Membaca data dari file
void loadData(Jadwal daftarJadwal[], int &jumlahData) {
    ifstream fileInput("jadwal.txt");
    jumlahData = 0;
    
    if (fileInput.is_open()) {
        while (fileInput >> daftarJadwal[jumlahData].namaMatkul 
                         >> daftarJadwal[jumlahData].namaDosen 
                         >> daftarJadwal[jumlahData].ruangKelas 
                         >> daftarJadwal[jumlahData].jamKuliah) {
            
            daftarJadwal[jumlahData].namaMatkul = underscoreKeSpasi(daftarJadwal[jumlahData].namaMatkul);
            daftarJadwal[jumlahData].namaDosen = underscoreKeSpasi(daftarJadwal[jumlahData].namaDosen);
            daftarJadwal[jumlahData].ruangKelas = underscoreKeSpasi(daftarJadwal[jumlahData].ruangKelas);
            daftarJadwal[jumlahData].jamKuliah = underscoreKeSpasi(daftarJadwal[jumlahData].jamKuliah);
            
            jumlahData++;
        }
        fileInput.close();
    }
}

void tambahData(Jadwal daftarJadwal[], int &jumlahData) {
    Jadwal baru;
    cout << "\n=== INPUT JADWAL KULIAH BARU ===\n";
    
    cout << "1. Nama Mata Kuliah   : ";
    cin.ignore(); 
    getline(cin, baru.namaMatkul);
    cout << "2. Nama Dosen Pengampu: ";
    getline(cin, baru.namaDosen);
    cout << "3. Ruang Kelas        : ";
    getline(cin, baru.ruangKelas);
    cout << "4. Jam (Contoh 07:30-09:10): ";
    getline(cin, baru.jamKuliah);
    
    // PROSES CEK BENTROK (Berdasarkan Ruangan & Jam)
    for (int i = 0; i < jumlahData; i++) {
        if (keLowercaseManual(daftarJadwal[i].ruangKelas) == keLowercaseManual(baru.ruangKelas) && 
            keLowercaseManual(daftarJadwal[i].jamKuliah) == keLowercaseManual(baru.jamKuliah)) {
            
            cout << "\n[ ERROR ] Jadwal Gagal Disimpan!\n";
            cout << "Alasan  : Bentrok dengan matkul \"" << daftarJadwal[i].namaMatkul 
                 << "\" di ruangan " << daftarJadwal[i].ruangKelas << " pada jam tersebut.\n";
            return; 
        }
    }
    
    daftarJadwal[jumlahData] = baru;
    jumlahData++;
    
    ofstream fileOutput("jadwal.txt", ios::app);
    if (fileOutput.is_open()) {
        fileOutput << spasiKeUnderscore(baru.namaMatkul) << " "
                   << spasiKeUnderscore(baru.namaDosen) << " "
                   << spasiKeUnderscore(baru.ruangKelas) << " "
                   << spasiKeUnderscore(baru.jamKuliah) << "\n";
        fileOutput.close();
        cout << "\n[ Sukses ] Jadwal baru berhasil disimpan!\n";
    }
}

void tampilkanTabel(const Jadwal daftarJadwal[], int jumlahData) {
    if (jumlahData == 0) {
        cout << "\n[ Jadwal Kuliah Masih Kosong. Silakan Input Data Terlebih Dahulu ]\n";
        return;
    }
    
    cout << "\n" << setfill('=') << setw(110) << "" << setfill(' ') << "\n";
    cout << left << setw(5) << "NO" 
         << setw(35) << "MATA KULIAH"       
         << setw(28) << "DOSEN PENGAMPU"   
         << setw(25) << "RUANG KELAS"      
         << setw(17) << "JAM KULIAH" << "\n";
    cout << setfill('-') << setw(110) << "" << setfill(' ') << "\n";
    
    for (int i = 0; i < jumlahData; i++) {
        cout << left << setw(5) << (i + 1)
             << setw(35) << daftarJadwal[i].namaMatkul  
             << setw(28) << daftarJadwal[i].namaDosen
             << setw(25) << daftarJadwal[i].ruangKelas  
             << setw(17) << daftarJadwal[i].jamKuliah << "\n";
    }
    cout << setfill('=') << setw(110) << "" << setfill(' ') << "\n";
}

bool cekKondisiSort(Jadwal a, Jadwal b, int kriteria, int arah) {
    if (kriteria == 1) {
        return (arah == 1) ? (keLowercaseManual(a.namaMatkul) > keLowercaseManual(b.namaMatkul)) 
                           : (keLowercaseManual(a.namaMatkul) < keLowercaseManual(b.namaMatkul));
    } else if (kriteria == 2) {
        return (arah == 1) ? (keLowercaseManual(a.namaDosen) > keLowercaseManual(b.namaDosen)) 
                           : (keLowercaseManual(a.namaDosen) < keLowercaseManual(b.namaDosen));
    } else if (kriteria == 3) {
        return (arah == 1) ? (a.ruangKelas > b.ruangKelas) : (a.ruangKelas < b.ruangKelas);
    }
    return false;
}

void urutkanData(Jadwal* daftarJadwal, int jumlahData) {
    if (jumlahData <= 1) {
        cout << "\nData minimal harus ada 2 jadwal untuk diurutkan.\n";
        return;
    }
    int kriteria, arah;
    cout << "\n--- MENU URUTKAN JADWAL ---\n";
    cout << "Urutkan Berdasarkan:\n1. Nama Mata Kuliah\n2. Nama Dosen\n3. Ruang Kelas\nPilih (1-3): ";
    cin >> kriteria;
    cout << "Arah:\n1. Ascending (A-Z)\n2. Descending (Z-A)\nPilih (1-2): ";
    cin >> arah;

    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (cekKondisiSort(daftarJadwal[j], daftarJadwal[j + 1], kriteria, arah)) {
                Jadwal temp = daftarJadwal[j];
                daftarJadwal[j] = daftarJadwal[j + 1];
                daftarJadwal[j + 1] = temp;
            }
        }
    }
    cout << "\nJadwal berhasil diurutkan!\n";
    tampilkanTabel(daftarJadwal, jumlahData);
}

void cariData(const Jadwal daftarJadwal[], int jumlahData) {
    if (jumlahData == 0) {
        cout << "\n[ Data Kosong ]\n";
        return;
    }
    int pilihan;
    string kataKunci;
    cout << "\n--- MENU PENCARIAN ---\n";
    cout << "1. Cari lewat Nama Mata Kuliah\n2. Cari lewat Nama Dosen\nPilih (1-2): ";
    cin >> pilihan;
    cout << "Masukkan kata kunci: ";
    cin.ignore();
    getline(cin, kataKunci);
    
    cout << "\n--- HASIL PENCARIAN ---\n";
    int nomor = 1;
    for (int i = 0; i < jumlahData; i++) {
        bool cocok = false;
        if (pilihan == 1) cocok = mengandungKataKunci(daftarJadwal[i].namaMatkul, kataKunci);
        else if (pilihan == 2) cocok = mengandungKataKunci(daftarJadwal[i].namaDosen, kataKunci);
        
        if (cocok) {
            if (nomor == 1) {
                cout << left << setw(5) << "NO" << setw(35) << "MATA KULIAH" << setw(28) << "DOSEN PENGAMPU" << setw(25) << "RUANG KELAS" << setw(17) << "JAM KULIAH" << "\n";
                cout << "-------------------------------------------------------------------------------------------------\n";
            }
            cout << left << setw(5) << nomor++
                 << setw(35) << daftarJadwal[i].namaMatkul
                 << setw(28) << daftarJadwal[i].namaDosen
                 << setw(25) << daftarJadwal[i].ruangKelas
                 << setw(17) << daftarJadwal[i].jamKuliah << "\n";
        }
    }
    if (nomor == 1) cout << "[ Jadwal tidak ditemukan ]\n";
}

void editData(Jadwal daftarJadwal[], int jumlahData) {
    if (jumlahData == 0) {
        cout << "\n[ Data Kosong. Tidak ada jadwal yang bisa diedit. ]\n";
        return;
    }
    
    tampilkanTabel(daftarJadwal, jumlahData); 
    
    int nomorEdit;
    cout << "\nMasukkan Nomor Jadwal yang ingin diedit (1-" << jumlahData << "): ";
    cin >> nomorEdit;
    
    if (nomorEdit < 1 || nomorEdit > jumlahData) {
        cout << "[ ERROR ] Nomor jadwal tidak valid!\n";
        return;
    }
    
    int index = nomorEdit - 1; 
    
    Jadwal baru;
    cout << "\n=== MASUKKAN DATA UPDATE JADWAL ===\n";
    cout << "Nama Mata Kuliah Baru    [" << daftarJadwal[index].namaMatkul << "]: ";
    cin.ignore();
    getline(cin, baru.namaMatkul);
    cout << "Nama Dosen Pengampu Baru [" << daftarJadwal[index].namaDosen << "]: ";
    getline(cin, baru.namaDosen);
    cout << "Ruang Kelas Baru         [" << daftarJadwal[index].ruangKelas << "]: ";
    getline(cin, baru.ruangKelas);
    cout << "Jam Kuliah Baru          [" << daftarJadwal[index].jamKuliah << "]: ";
    getline(cin, baru.jamKuliah);
    
    // Cek Bentrok Pas Edit
    for (int i = 0; i < jumlahData; i++) {
        if (i == index) continue; 
        
        if (keLowercaseManual(daftarJadwal[i].ruangKelas) == keLowercaseManual(baru.ruangKelas) && 
            keLowercaseManual(daftarJadwal[i].jamKuliah) == keLowercaseManual(baru.jamKuliah)) {
            
            cout << "\n[ ERROR ] Gagal Update! Jadwal baru bentrok dengan matkul \"" 
                 << daftarJadwal[i].namaMatkul << "\" di ruangan tersebut.\n";
            return; 
        }
    }
    
    daftarJadwal[index] = baru;
    
    simpanUlangSemuaKeFile(daftarJadwal, jumlahData);
    cout << "\n[ Sukses ] Data Jadwal Nomor " << nomorEdit << " Berhasil Diperbarui!\n";
}

void hapusData(Jadwal daftarJadwal[], int &jumlahData) {
    if (jumlahData == 0) {
        cout << "\n[ Data Kosong. Tidak ada jadwal yang bisa dihapus. ]\n";
        return;
    }

    tampilkanTabel(daftarJadwal, jumlahData); // Tampilin dulu biar user tahu nomornya

    int nomorHapus;
    cout << "\nMengaktifkan Menu Hapus Data...\n";
    cout << "Masukkan Nomor Jadwal yang ingin dihapus (1-" << jumlahData << "): ";
    cin >> nomorHapus;

    if (nomorHapus < 1 || nomorHapus > jumlahData) {
        cout << "[ ERROR ] Nomor jadwal tidak valid!\n";
        return;
    }

    int indexHapus = nomorHapus - 1; // Konversi ke index array

    // PROSES SHIFT ARRAY (Menggeser data belakang ke depan untuk menutup celah kosong)
    for (int i = indexHapus; i < jumlahData - 1; i++) {
        daftarJadwal[i] = daftarJadwal[i + 1];
    }

    // Karena satu data sudah dihapus, total counter jumlahData kita kurangi 1
    jumlahData--;

    // Tulis ulang file jadwal.txt biar permanen tanpa data yang dihapus tadi
    simpanUlangSemuaKeFile(daftarJadwal, jumlahData);

    cout << "\n[ Sukses ] Jadwal Nomor " << nomorHapus << " berhasil dihapus dari sistem!\n";
}

int main() {
    Jadwal daftarJadwal[100]; 
    int jumlahData = 0;
    int pilihan;
    
    loadData(daftarJadwal, jumlahData); 

    cout << R"(
       /\_/\      _____________________
      ( >.< )    /                     \
      /  v  \   <       WELCOME!       |
     /       \   \_____________________/
    /  | |  | \
   (___|_|___) 
    )" << endl;
    
    system("pause");
    system("cls");
    
    do {
        cout << "\n=====================================\n";
        cout << "   SISTEM INFORMASI JADWAL KULIAH    \n";
        cout << "=====================================\n";
        cout << "1. Lihat Semua Jadwal\n";
        cout << "2. Tambah/Input Jadwal Baru \n"; 
        cout << "3. Urutkan Jadwal \n";
        cout << "4. Cari Jadwal \n";
        cout << "5. Edit Data Jadwal\n"; 
        cout << "6. Hapus Data Jadwal\n";    
        cout << "7. Keluar\n";
        cout << "Pilih Menu (1-7): ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: tampilkanTabel(daftarJadwal, jumlahData); 
				break;
            case 2: tambahData(daftarJadwal, jumlahData); 
				break; 
            case 3: urutkanData(daftarJadwal, jumlahData); 
				break; 
            case 4: cariData(daftarJadwal, jumlahData); 
				break;
            case 5: editData(daftarJadwal, jumlahData); 
				break; 
            case 6: hapusData(daftarJadwal, jumlahData); 
				break; 
            case 7: 
                system("cls"); 
                cout << R"(
                   /\_/\     _______________________
                  ( ^.^ )   /                       \
                  /  v  \  <    TERIMA KASIH!       |
                 /       \  \_______________________/
                /  | |  | \
               (___|_|___) ~*dadah*~
                )" << endl;
                break;
            default: cout << "\nPilihan salah! Masukkan angka 1-7.\n";
        }
    } while (pilihan != 7);
    
    return 0;
}
