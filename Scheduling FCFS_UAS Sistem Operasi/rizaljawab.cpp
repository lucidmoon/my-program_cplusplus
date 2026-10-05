#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Struktur diperbarui agar membedakan burst time dan waktu selesai aktual
struct Proses {
    string nama;
    int tiba;           // Arrival Time
    int burst_time;     // Lama eksekusi (dibaca dari kolom 'wselesai' rizdama.txt)
    int wselesai;       // Completion Time (waktu rampungnya proses)
    int waktu_tunggu;   // Waiting Time
};

int main() {
    Proses daftarProses[100];
    
    // Membaca file input
    ifstream inFile("rizaldama.txt");
    if (!inFile) {
        cerr << "Gagal membuka file rizaldama.txt!" << endl;
        return 1;
    }

    string header1, header2, header3;
    inFile >> header1 >> header2 >> header3;

    // Membaca kolom ke-3 (wselesai di rizdama) sebagai burst_time
    for (int i = 0; i < 100; ++i) {
        inFile >> daftarProses[i].nama >> daftarProses[i].tiba >> daftarProses[i].burst_time;
    }
    inFile.close();

    // 1. MENGURUTKAN BERDASARKAN WAKTU TIBA (FCFS)
    for (int i = 0; i < 100 - 1; ++i) {
        for (int j = 0; j < 100 - i - 1; ++j) {
            if (daftarProses[j].tiba > daftarProses[j + 1].tiba) {
                Proses temp = daftarProses[j];
                daftarProses[j] = daftarProses[j + 1];
                daftarProses[j + 1] = temp;
            }
        }
    }

    // 2. MENGHITUNG WAKTU TUNGGU & WAKTU SELESAI AKTUAL (FCFS)
    int waktu_saat_ini = 0; 
    
    for (int i = 0; i < 100; ++i) {
        // Jika CPU menganggur menunggu proses tiba
        if (waktu_saat_ini < daftarProses[i].tiba) {
            waktu_saat_ini = daftarProses[i].tiba;
        }
        
        // Waktu tunggu = Kapan CPU mulai memproses - Kapan proses tiba
        daftarProses[i].waktu_tunggu = waktu_saat_ini - daftarProses[i].tiba;
        
        // Waktu saat ini bertambah seiring CPU mengerjakan proses (burst time)
        waktu_saat_ini += daftarProses[i].burst_time;
        
        // Waktu rampungnya proses di CPU (Completion Time)
        daftarProses[i].wselesai = waktu_saat_ini;
    }

    // 3. MENYIMPAN HASIL KE rizjawab.txt
    ofstream outFile("rizaljawab.txt");
    if (!outFile) {
        cerr << "Gagal membuat file rizaljawab.txt!" << endl;
        return 1;
    }

    // Menulis header kolom (Sesuai instruksi: 4 kolom)
    outFile << left << setw(10) << "proses" 
            << setw(10) << "tiba" 
            << setw(15) << "wselesai" 
            << setw(15) << "waktu_tunggu" << "\n";

    // Menulis data akhir ke dalam file
    for (int i = 0; i < 100; ++i) {
        outFile << left << setw(10) << daftarProses[i].nama 
                << setw(10) << daftarProses[i].tiba 
                << setw(15) << daftarProses[i].wselesai 
                << setw(15) << daftarProses[i].waktu_tunggu << "\n";
    }

    outFile.close();

    cout << "Silakan compile dan jalankan ulang untuk melihat update di 'rizaljawab.txt'." << endl;

    return 0;
}