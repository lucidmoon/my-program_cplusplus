#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    // Inisialisasi seed untuk random number generator agar hasil berbeda tiap kali dijalankan
    srand(time(0));

    // Deklarasi matriks menggunakan array 2 dimensi (100 baris, 3 kolom)
    // Kolom 0: ID Proses (1-100) -> nantinya dicetak dengan awalan 'P'
    // Kolom 1: Waktu Tiba (0-99)
    // Kolom 2: Waktu Selesai (3-20)
    int matriks[100][3];

    // Mengisi matriks dengan data yang diminta (100 record)
    for (int i = 0; i < 100; ++i) {
        matriks[i][0] = i + 1;                 // ID Proses dari 1 hingga 100
        matriks[i][1] = rand() % 100;          // Angka random bulat positif 0 hingga 99
        matriks[i][2] = (rand() % 18) + 3;     // Angka random bulat positif 3 hingga 20
    }

    // Membuka file output dengan nama rizdama.txt
    ofstream outFile("rizaldama.txt");

    // Pengecekan apakah file berhasil dibuat/dibuka
    if (!outFile) {
        cerr << "Gagal membuat file rizaldama.txt!" << endl;
        return 1;
    }

    // Menulis header kolom ke dalam file teks
    outFile << left << setw(10) << "proses" 
            << setw(10) << "tiba" 
            << setw(15) << "wselesai" << "\n";

    // Menulis isi matriks ke dalam file
    for (int i = 0; i < 100; ++i) {
        // Menggabungkan huruf 'P' dengan ID proses untuk kolom pertama
        string proses = "P" + to_string(matriks[i][0]);
        
        outFile << left << setw(10) << proses 
                << setw(10) << matriks[i][1] 
                << setw(15) << matriks[i][2] << "\n";
    }

    // Menutup file setelah selesai menulis
    outFile.close();

    cout << "Berhasil! Matriks 3 kolom dengan 100 record telah di-generate." << endl;
    cout << "Silakan cek file 'rizaldama.txt' di dalam direktori program Anda." << endl;

    return 0;
}