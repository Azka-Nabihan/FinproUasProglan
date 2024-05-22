/*Proyek Akhir UAS*/
/*
Tanggal : 22/05/2024

no. grup : 11
Nama anggota :
1. Azka Nabihan (2306250541)
2. Muhammad Arya Wiandra (2306218295)

Versi : 2.2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include <windows.h>
#include <omp.h>

// Struktur node untuk produk
typedef struct nodep {
    char nama[100];             // Nama produk
    char kategori[100];         // Kategori produk
    int harga;                  // Harga produk
    int stock;                  // Stok produk
    char kodeProduk[100];       // Kode produk
    struct nodep* next;         // Pointer ke node produk berikutnya
} nodeP;

// Struktur node untuk detail pembelian produk dalam transaksi
typedef struct nodeb {
    char namaProduk[100];       // Nama produk yang dibeli
    int hargaPerPcs;            // Harga per unit produk
    int totalHargaPerPcs;       // Total harga untuk produk tertentu dalam transaksi
    int kuantitasProduk;        // Jumlah produk yang dibeli
} nodeB;

// Struktur node untuk data transaksi pelanggan
typedef struct nodec {
    int kodeTransaksi;          // Kode transaksi
    char waktuTransaksi[50];    // Waktu transaksi
    int totalHarga;             // Total harga transaksi
    int counterProduk;          // Jumlah produk dalam transaksi
    struct nodeb* belanja[100]; // Array dari detail pembelian produk (maksimum 100 produk dalam satu transaksi)
    struct nodec* next;         // Pointer ke node transaksi berikutnya
} nodeC;

// Aliasan untuk pointer ke node produk
typedef nodeP* productNode;
// Aliasan untuk pointer ke node transaksi pelanggan
typedef nodeC* customerNode;


void bumperProgram();
void printMenu();
void printTabelProduk(productNode head, int mode);
nodeP* createLinkedListProduct(productNode head, char* nama, char* kategori, int harga, int stock, char* kodeProduk);
nodeP* searchProduct(productNode head, char *nama, int mode);
nodeP* removeProduct(productNode head, productNode temp);
nodeC *createLinkedListCustomer(customerNode head, char produk[][100], int hargaPerPcs[], int kuantitasProduk[], int counter);
char *generateWaktu();
void freeCustomerList(customerNode head);
void freeProductList(productNode head);
nodeP *updateProduct(productNode head, char kodeProduk[][100], int kuantitasProduk[], int counter);
void printTabelPenjualan(customerNode head);
int generateKodeTransaksi(customerNode head);
void helpMenu();
void saveToFileCustomer(customerNode head);
void saveToFileProduct(productNode head);
nodeP *sortingProduct(productNode head, bool ascending, int select);

int main() {
    // Definisikan
    productNode product = NULL;
    productNode tempProduct = NULL;
    customerNode customer = NULL;
    customerNode tempCustomer = NULL;

    // Set seed untuk generator angka acak
    srand(time(0));

    int selectInt;
    char selectChar[50];

    int selectHelp;
    int select;
    char tempNama[100];
    char tempKategori[100];
    int tempHarga;
    int tempStock;
    char tempKodeProduk[100];
    int counter;
    char tempNamaArr[99][100];  //Asumsikan paling banyak orang beli 99 produk
    int tempHargaArr[99];
    int tempStockArr[99];
    char tempKodeProdukArr[99][100];
    int secChoice;

    bumperProgram();
    system("cls");

    do {
        printMenu();
        scanf("%d", &selectInt);
        system("cls");

        switch (selectInt) {
            case 1: // Tambah Produk
                do {
                    printf("============= Input Produk =============\n");
                    printf("Nama Produk: ");
                    scanf("%s", tempNama);
                    printf("Kategori Produk: ");
                    scanf("%s", tempKategori);
                    printf("Harga: ");
                    scanf("%d", &tempHarga);
                    printf("Stock: ");
                    scanf("%d", &tempStock);
                    printf("Kode Produk: ");
                    scanf("%s", tempKodeProduk);
                    printf("========================================\n");

                    product = createLinkedListProduct(product, tempNama, tempKategori, tempHarga, tempStock, tempKodeProduk);

                    printf("Data berhasil disimpan!\n");
                    printf("Apakah ingin menambah produk lagi (y/n)? ");
                    scanf("%s", selectChar);
                    system("cls");
                } while(strcasecmp(selectChar, "n") != 0);
                break;

            case 2: // Hapus Produk
                if(product == NULL)
                {
                    printf("Data Kosong!\n");
                    system("pause");
                    system("cls");
                    break;
                }

                printf("Data stok produk: \n");
                printTabelProduk(product, 2); // mode memprint semua baris
                printf("Nama produk yang ingin dihapus: ");
                scanf("%s", tempNama);
                system("cls");
                tempProduct = searchProduct(product, tempNama, 1); // Mode 1 untuk mencari berdasarkan nama
                if (tempProduct == NULL)
                {
                    printf("Data Tidak Ditemukan!\n");
                } 
                else {
                    printTabelProduk(tempProduct, 1); // memprint baris pertama saja
                    printf("Apakah benar data tersebut yang ingin dihapus? \n1. Ya\n2. Tidak \nInput: ");
                    scanf("%d", &selectInt);
                    if(selectInt == 1){
                        product = removeProduct(product, tempProduct);
                        printf("Produk berhasil dihapus!\n");}
                }
                system("pause");
                system("cls");
                break;

            case 3: // Catat Penjualan
                counter = 0;
                do{
                    printTabelProduk(product, 3); //mode 3 hanya akan memprint kolom 2 dan 3 saja
                    printf("\n============= Input Penjualan =============\n");
                    printf("Kode produk yang dibeli: ");
                    scanf("%s", tempKodeProduk);
                    tempProduct = searchProduct(product, tempKodeProduk, 2);  // Mode 2 untuk mencari berdasarkan kode produk
                    if(tempProduct == NULL) {
                        printf("Produk tidak ditemukan!\n");
                    } else {
                        printf("Jumlah produk: ");
                        scanf("%d", &tempStock);

                        strcpy(tempNamaArr[counter], tempProduct->nama);
                        tempHargaArr[counter] = tempProduct->harga;
                        tempStockArr[counter] = tempStock;
                        strcpy(tempKodeProdukArr[counter], tempProduct->kodeProduk);
                        counter++;

                        printf("Produk Berhasil Ditambahkan!\n");
                    }
                    printf("==========================================\n");
                    printf("Selesai? (Y/N): ");
                    scanf("%s", selectChar);
                    system("cls");
                } while (strcasecmp(selectChar, "y") != 0);

                // Membuat linked list customer
                customer = createLinkedListCustomer(customer, tempNamaArr, tempHargaArr, tempStockArr, counter);

                // Mengupdate pada stock
                product = updateProduct(product, tempKodeProdukArr, tempStockArr, counter);
                
                break;

            case 4: // Pencarian Produk
                if(product == NULL)
                {
                    printf("Data Kosong!\n");
                    system("pause");
                    system("cls");
                    break;
                }
                printf("Mencari Berdsasarkan: \n1.Nama \n2.Kode Produk \nInput: ");
                scanf("%d", &select);
                if(select == 1)
                {
                    printf("Nama produk yang ingin dicari: ");
                    scanf("%s", tempNama);
                    tempProduct = searchProduct(product, tempNama, 1);     // Mode 1 untuk mencari berdasarkan nama
                    if(tempProduct != NULL)
                    {
                        printTabelProduk(tempProduct, 1);  //mode 1 akan memprint semua baris
                        printf("Produk Ditemukan!\n");
                    } else {
                        printf("Produk Tidak Ditemukan!\n");
                    }
                    system("pause");
                    system("cls");
                    break;
                } else if (select == 2){
                    printf("Kode produk yang ingin dicari: ");
                    scanf("%s", tempKodeProduk);
                    tempProduct = searchProduct(product, tempKodeProduk, 2);     // Mode 2 untuk mencari berdasarkan kode
                    if(tempProduct != NULL)
                    {
                        printTabelProduk(tempProduct, 1); // mode 1 akan memprint baris
                        printf("Produk Ditemukan!\n");
                    } else {
                        printf("Produk Tidak Ditemukan!\n");
                    }
                    system("pause");
                    system("cls");
                    break;
                }
                
            case 5: // Laporan Produk saat ini
                if(product == NULL)
                {
                    printf("Data Kosong!\n");
                    system("pause");
                    system("cls");
                    break;
                }
                printTabelProduk(product, 2);   // Mode 2 akan memprint semuanya
                printf("Apakah ingin diurutkan (y/n) ?");
                scanf("%s", selectChar);
                if(strcasecmp(selectChar, "y") == 0)
                {
                    system("cls");
                    printf("Mengurutkan berdasarkan: \n1. Nama \n2. Harga Kursi\n3. Stock \nInput: ");
                    scanf("%d", &select);
                    printf("Mengurutkan secara: \n1. Ascending \n2. Descending\nInput: ");
                    scanf("%d", &secChoice);
                    if(secChoice == 1){
                        product = sortingProduct(product, true, select);
                    } else if(secChoice == 2){
                        product = sortingProduct(product, false, select);
                    } else {
                        printf("Invalid Input");}
                    system("cls");
                    printTabelProduk(product, 2);   // Mode 2 akan memprint semuanya
                }
                
                printf("Apakah ingin kamu simpan ke dalam file (y/n)? ");
                scanf("%s", selectChar);
                if(strcasecmp(selectChar, "y") == 0)
                {
                    saveToFileProduct(product);
                    printf("Berhasil di Simpan!\n");
                }
                system("pause");
                system("cls");
                break;

            case 6: // Laporan Penjualan
                if(customer == NULL)
                {
                    printf("Data Kosong!\n");
                    system("pause");
                    system("cls");
                    break;
                }
                printTabelPenjualan(customer);
                printf("Apakah ingin kamu simpan ke dalam file (y/n)? ");
                scanf("%s", selectChar);
                if(strcasecmp(selectChar, "y") == 0)
                {
                    saveToFileCustomer(customer);
                    printf("Berhasil di Simpan!\n");
                }
                system("pause");
                system("cls");
                break;

            case 7: // Help
                helpMenu();
                system("cls");
                break;


            case 0: // Keluar Aplikasi
                printf("Keluar aplikasi. Terima kasih!\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (selectInt != 0);


    freeCustomerList(customer);
    freeProductList(product);

    return 0;
}

/**
 * Fungsi untuk mengurutkan linked list produk berdasarkan kriteria tertentu.
 * @param head Pointer ke node pertama dalam linked list produk.
 * @param ascending Menentukan apakah pengurutan dilakukan secara menaik atau menurun.
 * @param select Menentukan kriteria pengurutan: 1 untuk nama, 2 untuk harga, 3 untuk stok.
 * @return Pointer ke node pertama dalam linked list yang telah diurutkan.
 */
nodeP* sortingProduct(productNode head, bool ascending, int select) {
    productNode sorted = NULL;  // Pointer ke linked list hasil pengurutan
    productNode current = head; // Pointer ke node saat ini dalam iterasi

    // Mulai blok paralel dengan OpenMP
    #pragma omp parallel
    {
        // Hanya satu thread yang menjalankan iterasi while pertama kali
        #pragma omp single
        {
            while (current != NULL) {
                productNode next = current->next; // Simpan pointer ke node selanjutnya

                // Buat tugas OpenMP untuk memproses pengurutan
                #pragma omp task firstprivate(current, next)
                {
                    // Memilih kriteria pengurutan berdasarkan select
                    if (select == 1) { // Berdasarkan nama
                        // Critical section untuk menghindari race condition saat mengakses sorted
                        #pragma omp critical
                        {
                            // Jika sorted kosong atau current harus diletakkan di depan
                            if (sorted == NULL || (ascending ? strcasecmp(current->nama, sorted->nama) < 0 : strcasecmp(current->nama, sorted->nama) > 0)) {
                                current->next = sorted;
                                sorted = current;
                            } else {
                                // Cari tempat yang sesuai untuk current di sorted
                                productNode temp = sorted;
                                while (temp->next != NULL && (ascending ? strcasecmp(temp->next->nama, current->nama) < 0 : strcasecmp(temp->next->nama, current->nama) > 0)) {
                                    temp = temp->next;
                                }
                                current->next = temp->next;
                                temp->next = current;
                            }
                        }
                    } else if(select == 2){ // Berdasarkan harga
                        // Critical section untuk menghindari race condition saat mengakses sorted
                        #pragma omp critical
                        {
                            // Jika sorted kosong atau current harus diletakkan di depan
                            if (sorted == NULL || (ascending ? current->harga < sorted->harga : current->harga > sorted->harga)) {
                                current->next = sorted;
                                sorted = current;
                            } else {
                                // Cari tempat yang sesuai untuk current di sorted
                                productNode temp = sorted;
                                while (temp->next != NULL && (ascending ? temp->next->harga < current->harga : temp->next->harga > current->harga)) {
                                    temp = temp->next;
                                }
                                current->next = temp->next;
                                temp->next = current;
                            }
                        }
                    } else if(select == 3) { //Berdasarkan stock
                        // Critical section untuk menghindari race condition saat mengakses sorted
                        #pragma omp critical
                        {
                            // Jika sorted kosong atau current harus diletakkan di depan
                            if (sorted == NULL || (ascending ? current->stock < sorted->stock : current->stock > sorted->stock)) {
                                current->next = sorted;
                                sorted = current;
                            } else {
                                // Cari tempat yang sesuai untuk current di sorted
                                productNode temp = sorted;
                                while (temp->next != NULL && (ascending ? temp->next->stock < current->stock : temp->next->stock > current->stock)) {
                                    temp = temp->next;
                                }
                                current->next = temp->next;
                                temp->next = current;
                            }
                        }
                    } else {
                        printf("Terdapat kesalahan input pada mode!\n");
                    }
                }
                #pragma omp taskwait // Menunggu semua tugas selesai sebelum melanjutkan iterasi
                current = next; // Pindah ke node berikutnya
            }
        }
    }

    return sorted; // Mengembalikan pointer ke linked list yang telah diurutkan
}


/**
 * Fungsi untuk menyimpan informasi produk ke dalam file teks.
 * @param head Pointer ke node pertama dalam linked list produk.
 */
void saveToFileProduct(productNode head) {
    FILE *file = fopen("laporan_produk.txt", "w"); // Membuka file untuk ditulis
    if (file == NULL) { // Memeriksa keberhasilan pembukaan file
        perror("Gagal membuka file"); // Menampilkan pesan kesalahan jika gagal
        return;
    }

    // Menulis header laporan produk ke file
    fprintf(file, "================================================================================================\n");
    fprintf(file, "|                                     Laporan Stok Produk                                       |\n");
    fprintf(file, "================================================================================================\n");
    fprintf(file, "| %-4s | %-15s | %-16s | %-18s | %-11s | %-13s |\n", "No", "Nama Produk", "Kategori", "Harga (satuan)", "Stock", "Kode Produk");
    fprintf(file, "================================================================================================\n");

    productNode cursor = head; // Pointer ke node saat ini dalam iterasi
    int nomor = 1; // Variabel untuk nomor urutan produk
    while (cursor != NULL) { // Melakukan iterasi melalui seluruh node produk
        float hargaSatuan = cursor->harga / 1000.0; // Menghitung harga satuan dalam format rupiah
        // Menulis informasi produk ke file
        fprintf(file, "| %-4d | %-15s | %-16s | Rp%-16.2f | %-11d | %-13s |\n", nomor, cursor->nama, cursor->kategori, hargaSatuan, cursor->stock, cursor->kodeProduk);
        cursor = cursor->next; // Pindah ke node produk berikutnya
        nomor++; // Menambah nomor urutan
    }

    fprintf(file, "------------------------------------------------------------------------------------------------\n");
    fclose(file); // Menutup file setelah selesai
}

/**
 * Fungsi untuk menyimpan informasi penjualan ke dalam file teks.
 * @param head Pointer ke node pertama dalam linked list transaksi penjualan.
 */
void saveToFileCustomer(customerNode head) {
    FILE *file = fopen("laporan_penjualan.txt", "w"); // Membuka file untuk ditulis
    if (file == NULL) { // Memeriksa keberhasilan pembukaan file
        perror("Gagal membuka file"); // Menampilkan pesan kesalahan jika gagal
        return;
    }

    // Menulis header laporan penjualan ke file
    fprintf(file, "=================================================================================================\n");
    fprintf(file, "|                                  LAPORAN PENJUALAN                                            |\n");
    fprintf(file, "=================================================================================================\n");
    fprintf(file, "| %-21s | %-21s | %-21s | %-21s |\n", "Kode Transaksi", "Waktu Transaksi", "Nama Produk", "Total Harga");
    fprintf(file, "=================================================================================================\n");

    customerNode cursor = head; // Pointer ke node saat ini dalam iterasi
    while (cursor != NULL) { // Melakukan iterasi melalui seluruh node transaksi penjualan
        // Menampilkan informasi transaksi ke dalam file
        for (int i = 0; i < cursor->counterProduk; i++) {
            float tempHargaTotalPcs = cursor->belanja[i]->totalHargaPerPcs / 1000; // Menghitung total harga per barang dalam format rupiah
            fprintf(file, "| %-21d | %-21s | %-21s | Rp%-19.3f |\n", cursor->kodeTransaksi, cursor->waktuTransaksi, cursor->belanja[i]->namaProduk, tempHargaTotalPcs);
        }
        // Menampilkan total harga transaksi
        float tempTotalHarga = cursor->totalHarga / 1000; // Menghitung total harga transaksi dalam format rupiah
        fprintf(file, "-----------------------------------------------------------------------------------------------\n");
        fprintf(file, "| %-7s | Rp%-18.3f |\n", "Total Harga Transaksi:", tempTotalHarga);
        fprintf(file, "=================================================================================================\n");

        cursor = cursor->next; // Pindah ke node transaksi penjualan berikutnya
    }

    fclose(file); // Menutup file setelah selesai
}

void helpMenu(){
    int selectHelp;
        printf("               HELP MENU\n");
    printf("====================================\n");
    printf("1. Informasi Tambah Produk\n");
    printf("2. Informasi Hapus Produk\n");
    printf("3. Informasi Penjualan\n");
    printf("4. Informasi Pencarian Produk\n");
    printf("5. Informasi Laporan Produk saat ini\n");
    printf("6. Informasi Laporan Penjualan\n");
    printf("====================================\n");
    printf("Pilih opsi: ");
    scanf("%d", &selectHelp);

        switch (selectHelp) {

            case 1: 
                printf("Memilih menu ini akan menambahkan produk ke dalam gudang dengan meminta keterangan:\n");
                printf("a. Nama produk\n");
                printf("b. Kategori produk (Konsumsi/Aksesoris/Obat bebas)\n");
                printf("c. Harga produk\n");
                printf("d. Kode produk (format: xxx(K/A/O)mmyyyy):\n\n");
                printf("-xxx: diisi angka untuk menandakan barang ke berapa yang telah masuk\n");
                printf("-K/A/O untuk menandakan kategori produk,\n-K untuk konsumsi (makanan dan minuman),\n-A untuk Aksesoris (Peralatan dll),\n-O untuk Obat bebas (Obat batuk dll)\n");
                printf("-mmyyyy untuk menandakan bulan dan tahun produk tersebut dimasukkan ke sistem\n\n");
                break;

            case 2:
                printf("Menghapus produk dari sistem bila produk telah habis");
                break;

            case 3:
                printf("Menu ini akan meminta nama dan jumlah produk untuk dijual ke pembeli, serta mengurangi jumlah produk yang ada di gudang");
                break;

            case 4:
                printf("Menu ini akan mencari produk berdasarkan nama dan menampilkan tabel");
                break;

            case 5:
                printf("Menu ini akan menampilkan informasi terkait barang yang ada di gudang toko mulai dari:\n");
                printf("a. Nama produk\n");
                printf("b. Kategori produk\n");
                printf("c. Harga satuan\n");
                printf("d. Stock produk\n");
                printf("e. Kode produk \n");
                break;

            case 6:
                printf("Menu ini akan menampilkan penjualan-penjualan yang telah dilakukan,");
                printf("setiap penjualan akan menampilkan kode unik transaksi, waktu, dan tanggal penjualan");
                break;

            default:
                break;
        }
}

/**
 * Fungsi untuk mencetak tabel penjualan berdasarkan transaksi yang tersimpan dalam linked list.
 * @param head Pointer ke node pertama dalam linked list transaksi penjualan.
 */
void printTabelPenjualan(customerNode head) {
    int i;
    customerNode cursor = head; // Pointer ke node saat ini dalam iterasi

    // Melakukan iterasi melalui seluruh node transaksi penjualan
    while (cursor != NULL) {
        // Menghitung total harga dalam format float
        float tempTotalHarga = cursor->totalHarga / 1000;

        // Menampilkan informasi transaksi
        printf("\nKode Transaksi: %d\n", cursor->kodeTransaksi);
        printf("Waktu Transaksi: %s\n", cursor->waktuTransaksi);
        printf("=======================================================================\n");
        printf("| %-15s | %-15s | %-13s | %-15s |\n", "Produk", "Harga(pcs)", "Kuantitas", "Total");
        printf("=======================================================================\n");

        // Menampilkan daftar belanja
        for (i = 0; i < cursor->counterProduk; i++) {
            float tempHargaPcs = cursor->belanja[i]->hargaPerPcs / 1000;
            float tempHargaTotalPcs = cursor->belanja[i]->totalHargaPerPcs / 1000;
            printf("| %-15s | Rp%-13.3f | %-13d | Rp%-13.3f |\n", cursor->belanja[i]->namaProduk, tempHargaPcs, cursor->belanja[i]->kuantitasProduk, tempHargaTotalPcs);
        }
        // Menampilkan total harga
        printf("-----------------------------------------------------------------------\n");
        printf("| Total Harga: Rp%-52.3f |\n", tempTotalHarga);
        printf("=======================================================================\n");

        cursor = cursor->next; // Pindah ke node transaksi penjualan berikutnya
    }
}

/**
 * Fungsi untuk mengupdate stok produk berdasarkan kode produk dan kuantitas yang diberikan.
 * @param head Pointer ke node pertama dalam linked list produk.
 * @param kodeProduk Array 2 dimensi yang berisi kode produk.
 * @param kuantitasProduk Array yang berisi kuantitas produk yang akan diupdate.
 * @param counter Jumlah produk yang akan diupdate.
 * @return Pointer ke node pertama dalam linked list produk setelah proses update.
 */
nodeP* updateProduct(productNode head, char kodeProduk[][100], int kuantitasProduk[], int counter) {
    if (head == NULL || counter <= 0) {
        return head; // Tidak ada perubahan
    }

    // Memulai parallel region
    #pragma omp parallel
    {
        // Memulai parallel loop untuk mengupdate stok produk
        #pragma omp for
        for (int i = 0; i < counter; i++) {
            nodeP *cursor = head; // Pointer ke node saat ini dalam iterasi
            while (cursor != NULL) { // Melakukan iterasi melalui seluruh node produk
                if (strcasecmp(cursor->kodeProduk, kodeProduk[i]) == 0) { // Memeriksa apakah kode produk cocok
                    #pragma omp critical
                    {
                        // Jika Produk ditemukan, maka stok akan dikurangi
                        if (cursor->stock >= kuantitasProduk[i]) {
                            cursor->stock -= kuantitasProduk[i];
                        } else {
                            printf("Stok produk '%s' tidak mencukupi\n", kodeProduk[i]);
                        }
                    }
                    break;
                }
                cursor = cursor->next; // Pindah ke node produk berikutnya
            }
        }
    }

    printf("Update produk selesai.\n"); // Menampilkan pesan setelah selesai update
    return head; // Mengembalikan pointer ke node pertama dalam linked list produk
}

/**
 * Fungsi untuk menghasilkan string yang berisi waktu saat ini dalam format tertentu.
 * Format waktu yang dihasilkan adalah "HH:MM:SS, dd-mm-yyyy".
 * @return String yang berisi waktu saat ini dalam format yang diinginkan.
 *         Harap diberikan dealokasi memori setelah penggunaan.
 */
char* generateWaktu() {
    // Mengatur locale untuk menggunakan bahasa Indonesia
    setlocale(LC_ALL, "id_ID");

    // Mendapatkan waktu saat ini
    time_t rawtime;
    struct tm *timeinfo;
    char *buffer = (char *)malloc(50 * sizeof(char)); // Alokasi dinamis untuk buffer

    if (buffer == NULL) {
        perror("Gagal mengalokasikan memori");
        exit(EXIT_FAILURE);
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Memformat waktu dan tanggal dalam format yang diinginkan
    strftime(buffer, 50, "%H:%M:%S, %d-%m-%Y", timeinfo);

    return buffer; // Mengembalikan string yang berisi waktu saat ini
}

/**
 * Fungsi untuk menghasilkan kode transaksi unik berdasarkan nomor acak dan memastikan bahwa kode transaksi tersebut unik dalam linked list.
 * Kode transaksi yang dihasilkan akan berada dalam rentang 100 hingga 1099.
 * @param head Pointer ke node pertama dalam linked list transaksi pelanggan.
 * @return Kode transaksi unik yang dihasilkan.
 */
int generateKodeTransaksi(customerNode head) {
    int boundedRandomNumber;  // Variabel untuk menyimpan nomor acak yang dihasilkan
    bool unique;  // Variabel untuk menandakan apakah nomor acak tersebut unik

    // Melakukan loop hingga nomor acak yang unik dihasilkan
    do {
        unique = true;  // Setel unique ke true untuk memulai pengecekan
        boundedRandomNumber = rand() % 1000 + 100;  // Menghasilkan nomor acak antara 100 hingga 1099

        // Menghitung jumlah elemen dalam linked list
        int length = 0;
        for (customerNode cursor = head; cursor != NULL; cursor = cursor->next) {
            length++;
        }

        // Parallel region dengan OpenMP untuk memeriksa seluruh linked list
        #pragma omp parallel for
        for (int i = 0; i < length; i++) {
            customerNode cursor = head;
            for (int j = 0; j < i; j++) {
                cursor = cursor->next;
            }
            if (cursor->kodeTransaksi == boundedRandomNumber) {
                #pragma omp critical
                unique = false; // Jika nomor acak ditemukan dalam linked list, setel unique ke false
            }
        }

    // Ulangi loop hingga nomor acak yang dihasilkan unik
    } while (!unique);

    return boundedRandomNumber;  // Mengembalikan nomor acak yang unik sebagai kode transaksi
}

/**
 * Fungsi untuk membuat dan menginisialisasi node baru dalam linked list transaksi pelanggan.
 * @param head Pointer ke node pertama dalam linked list transaksi pelanggan.
 * @param produk Array dua dimensi berisi nama produk yang dibeli.
 * @param hargaPerPcs Array berisi harga per satuan produk.
 * @param kuantitasProduk Array berisi jumlah produk yang dibeli.
 * @param counter Jumlah produk yang dibeli oleh pelanggan.
 * @return Pointer ke node baru yang telah dibuat.
 */
nodeC *createLinkedListCustomer(customerNode head, char produk[][100], int hargaPerPcs[], int kuantitasProduk[], int counter) {
    int i;

    // Mengalokasikan memori untuk node baru
    nodeC *new_node = (nodeC *)malloc(sizeof(nodeC));
    if (!new_node) {
        perror("Gagal mengalokasikan memori");
        exit(EXIT_FAILURE);
    }

    // Mengalokasikan memori untuk setiap produk yang dibeli customer
    for (i = 0; i < counter; i++) {
        new_node->belanja[i] = (nodeB*)malloc(sizeof(nodeB));
        if (!new_node->belanja[i]) {
            perror("Gagal mengalokasikan memori untuk belanja");
            exit(EXIT_FAILURE);
        }
    }

    // Mengatur waktu transaksi dalam bagian master karena tidak perlu paralel
    #pragma omp master
    {
        char *waktu = generateWaktu();
        strcpy(new_node->waktuTransaksi, waktu);
        free(waktu);

        new_node->kodeTransaksi = generateKodeTransaksi(head);
    }

    new_node->counterProduk = counter;
    new_node->totalHarga = 0;

    // Mengisi data produk secara paralel dan mengakumulasi total harga
    int totalHarga = 0;

    #pragma omp parallel for reduction(+:totalHarga)
    for (i = 0; i < counter; i++) {
        strcpy(new_node->belanja[i]->namaProduk, produk[i]);
        new_node->belanja[i]->hargaPerPcs = hargaPerPcs[i];
        new_node->belanja[i]->totalHargaPerPcs = hargaPerPcs[i] * kuantitasProduk[i];
        new_node->belanja[i]->kuantitasProduk = kuantitasProduk[i];
        totalHarga += new_node->belanja[i]->totalHargaPerPcs;
    }

    new_node->totalHarga = totalHarga;

    // Menambahkan node baru ke linked list
    new_node->next = head;

    return new_node;
}

/**
 * Fungsi untuk membebaskan memori yang dialokasikan untuk linked list transaksi pelanggan.
 * @param head Pointer ke node pertama dalam linked list transaksi pelanggan.
 */
void freeCustomerList(customerNode head) {
    nodeC* currentCustomer = head;

    while (currentCustomer != NULL) {
        // Bebaskan setiap produk dalam array belanja
        #pragma omp parallel for
        for (int i = 0; i < currentCustomer->counterProduk; i++) {
            if (currentCustomer->belanja[i] != NULL) {
                #pragma omp critical
                free(currentCustomer->belanja[i]);
            }
        }

        // Simpan pointer ke node berikutnya
        nodeC* tempCustomer = currentCustomer;
        // Pindah ke node berikutnya
        currentCustomer = currentCustomer->next;
        // Bebaskan node saat ini
        free(tempCustomer);
    }
}

void freeProductList(productNode head)
{
    while(head != NULL)
    {
        // Simpan pointer ke node berikutnya
        nodeP *temp = head->next;

        // Membebaskan memori untuk kode saat ini
        free(head);
        
        // Pindah ke node berikutnya
        head = temp;
    }
}

nodeP* removeProduct(productNode head, productNode temp)
{
    // Jika data temp terdapat pada node pertama
    if(temp == head)
    {
        productNode front = head;
        head = head->next;
        front->next = NULL;

        /* Jika ini node terakhir */
        if(front == head)
            head = NULL;

        free(front);

        return head;
    }

    // Jika data temp terdapat pada node terakhir
    if(temp->next == NULL)
    {
        productNode cursor = head;
        productNode back = NULL;
        while(cursor->next != NULL)
        {
            back = cursor;
            cursor = cursor->next;
        }

        if(back != NULL)
            back->next = NULL;

        if(cursor == head)
            head = NULL;

        free(cursor);

        return head;
    }

    // Jika node berada ditengah tengah
    productNode cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == temp)
            break;
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        productNode tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }

    return head;
}
/**
 * Fungsi untuk mencari produk dalam linked list berdasarkan nama atau kode produk.
 * @param head Pointer ke node pertama dalam linked list produk.
 * @param nama String yang berisi nama produk atau kode produk yang ingin dicari.
 * @param mode Mode pencarian: 1 untuk pencarian berdasarkan nama produk, 2 untuk pencarian berdasarkan kode produk.
 * @return Pointer ke node yang berisi produk yang cocok dengan kriteria pencarian, NULL jika tidak ditemukan.
 */
nodeP* searchProduct(productNode head, char* nama, int mode)
{
    nodeP* cursor = head;
    int i;
    while(cursor != NULL)
    {
        char tempProduk[100];
        char tempCari[100];
        
        // Konversi nama produk atau kode produk menjadi lowercase untuk pencarian case-insensitive
        for(i = 0; nama[i]; i++) {
            tempCari[i] = tolower(nama[i]);
        }
        tempCari[i] = '\0'; // Tambahkan terminator null pada akhir string
        
        if (mode == 1) { // Mode pencarian berdasarkan nama produk
            // Konversi nama produk menjadi lowercase untuk pencarian case-insensitive
            for(i = 0; cursor->nama[i]; i++) {
                tempProduk[i] = tolower(cursor->nama[i]);
            }
            tempProduk[i] = '\0'; // Tambahkan terminator null pada akhir string

        } else { // Mode pencarian berdasarkan kode produk
            // Konversi kode produk menjadi lowercase untuk pencarian case-insensitive
            for(int i = 0; cursor->kodeProduk[i]; i++) {
                tempProduk[i] = tolower(cursor->kodeProduk[i]);
            }
            tempProduk[i] = '\0'; // Tambahkan terminator null pada akhir string
        }

        // Melakukan pencarian substring dalam nama produk atau kode produk
        if (strstr(tempProduk, tempCari) != NULL) {
            return cursor; // Mengembalikan pointer ke node yang cocok dengan kriteria pencarian
        }
        cursor = cursor->next;
    }

    return NULL; // Mengembalikan NULL jika produk tidak ditemukan
}

/**
 * Fungsi untuk membuat dan menginisialisasi node baru dalam linked list produk.
 * @param head Pointer ke node pertama dalam linked list produk.
 * @param nama String yang berisi nama produk.
 * @param kategori String yang berisi kategori produk.
 * @param harga Harga satuan produk.
 * @param stock Jumlah stok produk.
 * @param kodeProduk String yang berisi kode produk.
 * @return Pointer ke node baru yang telah dibuat.
 */
nodeP* createLinkedListProduct(productNode head, char* nama, char* kategori, int harga, int stock, char* kodeProduk) {
    // Mengalokasikan memori untuk node baru
    nodeP* new_node = (nodeP*)malloc(sizeof(nodeP));

    // Memeriksa apakah alokasi memori berhasil
    if (new_node == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk node baru\n");
        return NULL; // Mengembalikan NULL untuk menandakan kegagalan alokasi memori
    }

    // Menginisialisasi node baru dengan nilai yang diberikan, data baru akan menjadi paling awal di link list
    strcpy(new_node->nama, nama);
    strcpy(new_node->kategori, kategori);
    new_node->harga = harga;
    new_node->stock = stock;
    strcpy(new_node->kodeProduk, kodeProduk);
    new_node->next = head;

    return new_node;
}

/**
 * Fungsi untuk mencetak tabel produk ke konsol.
 * @param head Pointer ke node pertama dalam linked list produk.
 * @param mode Mode pencetakan: 1 untuk mencetak hanya baris pertama, 2 untuk mencetak seluruh baris, 3 untuk mencetak seluruh baris namun hanya kolom nama produk dan kode produk.
 */
void printTabelProduk(productNode head, int mode) {
    productNode cursor = head;
    float tempHarga;

    // Mode 1: Mencetak hanya baris pertama
    if (mode == 1) {
        tempHarga = cursor->harga / 1000;
        printf("=====================================================================================\n");
        printf("| %-15s | %-15s | %-17s | %-10s | %-12s |\n", "Nama Produk", "Kategori", "Harga (satuan)", "Stock", "Kode Produk");
        printf("=====================================================================================\n");
        printf("| %-15s | %-15s | Rp%-15.3f | %-10d | %-12s |\n", cursor->nama, cursor->kategori, tempHarga, cursor->stock, cursor->kodeProduk);
        printf("-------------------------------------------------------------------------------------\n");

    // Mode 2: Mencetak seluruh baris
    } else if (mode == 2) {
        printf("=====================================================================================\n");
        printf("| %-15s | %-15s | %-17s | %-10s | %-12s |\n", "Nama Produk", "Kategori", "Harga (satuan)", "Stock", "Kode Produk");
        printf("=====================================================================================\n");
        while (cursor != NULL) {
            tempHarga = cursor->harga / 1000;
            printf("| %-15s | %-15s | Rp%-15.3f | %-10d | %-12s |\n", cursor->nama, cursor->kategori, tempHarga, cursor->stock, cursor->kodeProduk);
            cursor = cursor->next;
        }
        printf("-------------------------------------------------------------------------------------\n");

    // Mode 3: Mencetak seluruh baris namun hanya kolom nama produk dan kode produk
    } else if (mode == 3) {
        printf("=====================================\n");
        printf("| %-15s | %-15s |\n", "Nama Produk", "Kode Produk");
        printf("=====================================\n");
        while (cursor != NULL) {
            printf("| %-15s | %-15s |\n", cursor->nama, cursor->kodeProduk);
            cursor = cursor->next;
        }
        printf("-------------------------------------\n");
    }
}


void printMenu() {
    printf("====================================\n");
    printf("               MENU\n");
    printf("====================================\n");
    printf("1. Tambah Produk\n");
    printf("2. Hapus Produk\n");
    printf("3. Penjualan\n");
    printf("4. Pencarian Produk\n");
    printf("5. Laporan Produk saat ini\n");
    printf("6. Laporan Penjualan\n");
    printf("7. Help\n");
    printf("0. Keluar aplikasi\n");
    printf("====================================\n");
    printf("Pilih opsi: ");
}

void bumperProgram() {
    printf("============================================\n");
    printf("||                                        ||\n");
    printf("||        APLIKASI MANAGEMENT PRODUK      ||\n");
    printf("||                 TOKO                   ||\n");
    printf("||                                        ||\n");
    printf("============================================\n");
    Sleep(500);
    printf("||  Dibuat oleh: Kelompok 11              ||\n");
    Sleep(500);
    printf("||  Versi: 2.0                            ||\n");
    Sleep(500);
    printf("||  Selamat datang!                       ||\n");
    Sleep(500);
    printf("============================================\n\n");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".\n");
    Sleep(1500);
}
