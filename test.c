// #include <stdio.h>
// #include <time.h>

// int main() {
//     // Mendapatkan waktu saat ini
//     time_t rawtime;
//     struct tm * timeinfo;
//     time(&rawtime);
//     timeinfo = localtime(&rawtime);
    
//     // Mencetak waktu dan tanggal saat ini
//     printf("Waktu dan Tanggal saat ini: %s", asctime(timeinfo));
    
//     return 0;
// }

// #include <stdio.h>
// #include <time.h>

// int main() {
//     // Mendapatkan waktu saat ini
//     time_t rawtime;
//     struct tm * timeinfo;
//     char buffer[80];

//     time(&rawtime);
//     timeinfo = localtime(&rawtime);

//     // Memformat waktu dan tanggal dalam format angka
//     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

//     // Mencetak waktu dan tanggal yang telah diformat
//     printf("Waktu dan Tanggal saat ini: %s\n", buffer);

//     return 0;
// }

// #include <stdio.h>
// #include <time.h>

// int main() {
//     // Mendapatkan waktu saat ini
//     time_t rawtime;
//     struct tm * timeinfo;
//     char buffer[80];

//     time(&rawtime);
//     timeinfo = localtime(&rawtime);

//     // Memformat waktu dan tanggal dalam format yang diinginkan
//     strftime(buffer, sizeof(buffer), "%H:%M:%S, %A, %d-%m-%Y", timeinfo);

//     // Mencetak waktu dan tanggal yang telah diformat
//     printf("Waktu dan Tanggal saat ini: %s\n", buffer);

//     return 0;
// }


#include <stdio.h>
#include <time.h>
#include <locale.h>

int main() {
    // Mengatur locale untuk menggunakan bahasa Indonesia
    setlocale(LC_ALL, "id_ID");

    // Mendapatkan waktu saat ini
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Memformat waktu dan tanggal dalam format yang diinginkan
    strftime(buffer, sizeof(buffer), "%H:%M:%S, %A, %d-%m-%Y", timeinfo);

    // Mencetak waktu dan tanggal yang telah diformat
    printf("Waktu dan Tanggal saat ini: %s\n", buffer);

    return 0;
}
