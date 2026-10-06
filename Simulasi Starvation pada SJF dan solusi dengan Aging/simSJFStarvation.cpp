//=================================================================
// Simulasi Starvation Pada Algoritma Shortest Job First
// Muhammad Rizal (251106040011)
//=================================================================

#include <iostream>
using namespace std;

const int MAX_PROC = 6;

struct Process {
    int id;
    int arrival;
    int burst;
    int is_completed;
};

// Fungsi untuk menyalin array agar skenario bisa diulang
void copyArray(Process src[], Process dest[], int n) {
    for(int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Fungsi utama simulasi penjadwalan
void runScheduling(Process p[], int n, bool use_aging) {
    int current_time = 0;
    int completed = 0;
    int wait_tolerance = 15; // Batas waktu tunggu maksimal sebelum fitur Aging aktif

    while (completed != n) {
        int idx = -1;
        int min_burst = 999999;
        bool aging_triggered = false;

        for (int i = 0; i < n; i++) {
            // Cek apakah proses sudah tiba dan belum selesai
            if (p[i].arrival <= current_time && p[i].is_completed == 0) {
                
                int wait_time = current_time - p[i].arrival;
                
                // MEKANISME AGING: Jika waktu tunggu melebihi toleransi, paksa eksekusi
                if (use_aging && wait_time >= wait_tolerance) {
                    idx = i;
                    aging_triggered = true;
                    break; // Hentikan pencarian, langsung proses yang kelaparan ini
                }

                // Logika Normal SJF: Cari burst time terkecil
                if (!aging_triggered && p[i].burst < min_burst) {
                    min_burst = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            int wait_time = current_time - p[idx].arrival;
            
            if (aging_triggered) {
                cout << " -> [AGING AKTIF! Tunggu: " << wait_time << "ms] P" << p[idx].id;
            } else {
                cout << " -> P" << p[idx].id;
            }
            
            current_time += p[idx].burst; // CPU mengeksekusi proses
            p[idx].is_completed = 1;
            completed++;
        } else {
            current_time++; // CPU idle jika belum ada proses yang tiba
        }
    }
    cout << "\n";
}

int main() {
    // Skenario: 
    // P2 memiliki burst time sangat besar (40).
    // Proses setelahnya (P3-P6) memiliki burst time kecil (5).
    Process original_processes[MAX_PROC] = {
        {1, 0, 10, 0},
        {2, 1, 40, 0}, // Korban Starvation
        {3, 2,  5, 0},
        {4, 3,  5, 0},
        {5, 4,  5, 0},
        {6, 5,  5, 0}
    };

    Process p_scenario1[MAX_PROC];
    Process p_scenario2[MAX_PROC];

    copyArray(original_processes, p_scenario1, MAX_PROC);
    copyArray(original_processes, p_scenario2, MAX_PROC);

    cout << "=== SIMULASI 1: SJF MURNI (Kondisi Starvation) ===" << endl;
    cout << "Urutan: P1";
    runScheduling(p_scenario1, MAX_PROC, false);
    // Penjelasan Skenario 1: 
    // P2 terus dilewati oleh P3, P4, P5, dan P6 karena burst time P2 (40) selalu 
    // lebih besar dari proses lain yang baru tiba. P2 tereksekusi paling akhir.

    cout << "\n=== SIMULASI 2: SJF DENGAN AGING (Solusi Starvation) ===" << endl;
    cout << "Urutan: P1";
    runScheduling(p_scenario2, MAX_PROC, true);
    // Penjelasan Skenario 2:
    // Setelah P3 dan P4 dieksekusi, waktu tunggu P2 melampaui batas toleransi (15).
    // Sistem langsung mengintervensi algoritma SJF dan memaksa P2 untuk dieksekusi 
    // sebelum P5 dan P6, menyelamatkannya dari kelaparan eksekusi.

    return 0;
}