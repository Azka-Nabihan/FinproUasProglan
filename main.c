#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include <windows.h>

// Mendefinisikan Struct product Menggunakan Stack
typedef struct nodep {
    char nama[100];
    char kategori[100];
    int harga;
    int stock;
    char kodeProduk[100];
    struct nodep* next;
} nodeP;

typedef struct nodeb {
    char namaProduk[100];
    int hargaPerPcs;
    int totalHargaPerPcs;
    int kuantitasProduk;
} nodeB;

typedef struct nodec {
    int kodeTransaksi;
    char waktuTransaksi[50];
    int totalHarga;
    int counterProduk;
    struct nodeb* belanja[100]; // Maksimum 100 Produk dalam satu transaksi;
    struct nodec* next;
} nodeC;



typedef nodeP* productNode;
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

int main() {
    // Definisikan
    productNode product = NULL;
    productNode tempProduct = NULL;
    customerNode customer = NULL;
    customerNode tempCustomer = NULL;

<<<<<<< HEAD
    // Set seed untuk generator angka acak
    srand(time(0));

    int selectInt;
    char selectChar[50];
=======
    int selectHelp;
    int select;
>>>>>>> cc7a088fc4e3dbebac413cb1a2c05d0c2135bd75
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

    bumperProgram();
    system("cls");

    do {
        printMenu();
        scanf("%d", &selectInt);
        system("cls");

        switch (selectInt) {
            case 1: // Tambah Produk
<<<<<<< HEAD
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
                } while (strcasecmp(selectChar, "n") != 0);
=======
                printf("Nama Produk: ");
                scanf("%s", tempNama);
                printf("Kategori Produk: ");
                scanf("%s", tempKategori);
                printf("Harga: ");
                scanf("%d", &tempHarga);
                printf("Stock: ");
                scanf("%d", &tempStock);
                printf("Kode Produk (Format: xxx(K/A/O)mmyyyy) ");
                scanf("%s", tempKodeProduk);
                product = createLinkedList(product, tempNama, tempKategori, tempHarga, tempStock, tempKodeProduk);
                printf("Data berhasil disimpan!\n");
>>>>>>> cc7a088fc4e3dbebac413cb1a2c05d0c2135bd75
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
                printTabelProduk(product, 2); // mode selain 1 akan memprint semuanya
                printf("Nama produk yang ingin dihapus: ");
                scanf("%s", tempNama);
                system("cls");
                tempProduct = searchProduct(product, tempNama, 1); // Mode 1 untuk mencari berdasarkan nama
                if (tempProduct == NULL)
                {
                    printf("Data Tidak Ditemukan!\n");
                } 
                else {
                    printTabelProduk(tempProduct, 1);
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
                    printf("============= Input Penjualan =============\n");
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
                printf("Nama produk yang ingin dicari: ");
                scanf("%s", tempNama);
                tempProduct = searchProduct(product, tempNama, 1);     // Mode 1 untuk mencari berdasarkan nama
                if(tempProduct != NULL)
                {
                    printTabelProduk(tempProduct, 1);  //mode selain 1 akan memprint semuanya
                    printf("Produk Ditemukan!\n");
                } else {
                    printf("Produk Tidak Ditemukan!\n");
                }
                system("pause");
                system("cls");
                break;

            case 5: // Laporan Produk saat ini
                if(product == NULL)
                {
                    printf("Data Kosong!\n");
                    system("pause");
                    system("cls");
                    break;
                }
                printTabelProduk(product, 2);   // Mode selain 1 akan memprint semuanya
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
<<<<<<< HEAD
                helpMenu();
                system("cls");
                break;
=======
    printf("====================================\n");
    printf("               HELP MENU\n");
    printf("====================================\n");
    printf("1. Informasi Tambah Produk\n");
    printf("2. Informasi Hapus Produk\n");
    printf("3. Informasi Catat Penjualan\n");
    printf("4. Informasi Pencarian Produk\n");
    printf("5. Informasi Laporan Produk saat ini\n");
    printf("6. Informasi Laporan Penjualan\n");
    printf("7. Informasi Help\n");
    printf("0. Informasi Keluar aplikasi\n");
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
            //belum
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
            //belom
            break;
            

        }
                break; //break switch main menu awas ketuker
>>>>>>> cc7a088fc4e3dbebac413cb1a2c05d0c2135bd75

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

void saveToFileProduct(productNode head) {
    FILE *file = fopen("laporan_produk.txt", "w");
    if (file == NULL) {
        perror("Gagal membuka file");
        return;
    }

    fprintf(file, "================================================================================================\n");
    fprintf(file, "|                                     Laporan Stok Produk                                       |\n");
    fprintf(file, "================================================================================================\n");
    fprintf(file, "| %-4s | %-15s | %-16s | %-18s | %-11s | %-13s |\n", "No", "Nama Produk", "Kategori", "Harga (satuan)", "Stock", "Kode Produk");
    fprintf(file, "================================================================================================\n");

    productNode cursor = head;
    int nomor = 1;
    while (cursor != NULL) {
        float hargaSatuan = cursor->harga / 1000.0;
        fprintf(file, "| %-4d | %-15s | %-16s | Rp%-16.2f | %-11d | %-13s |\n", nomor, cursor->nama, cursor->kategori, hargaSatuan, cursor->stock, cursor->kodeProduk);
        cursor = cursor->next;
        nomor++;
    }

    fprintf(file, "------------------------------------------------------------------------------------------------\n");
    fclose(file);
}


void saveToFileCustomer(customerNode head) {
    FILE *file = fopen("laporan_penjualan.txt", "w");
    if (file == NULL) {
        perror("Gagal membuka file");
        return;
    }

    fprintf(file, "=================================================================================================\n");
    fprintf(file, "|                                  LAPORAN PENJUALAN                                             |\n");
    fprintf(file, "=================================================================================================\n");
    fprintf(file, "| %-20s | %-20s | %-20s | %-20s |\n", "Kode Transaksi", "Waktu Transaksi", "Nama Produk", "Total Harga");
    fprintf(file, "=================================================================================================\n");

    customerNode cursor = head;
    while (cursor != NULL) {
        // Menampilkan informasi transaksi ke dalam file
        for (int i = 0; i < cursor->counterProduk; i++) {
            float tempHargaTotalPcs = cursor->belanja[i]->totalHargaPerPcs / 1000;
            fprintf(file, "| %-20d | %-20s | %-20s | Rp%-18.3f |\n", cursor->kodeTransaksi, cursor->waktuTransaksi, cursor->belanja[i]->namaProduk, tempHargaTotalPcs);
        }
        // Menampilkan total harga transaksi
        float tempTotalHarga = cursor->totalHarga / 1000;
        fprintf(file, "-----------------------------------------------------------------------------------------------\n");
        fprintf(file, "| %-72s | Rp%-18.3f |\n", "Total Harga Transaksi:", tempTotalHarga);
        fprintf(file, "=================================================================================================\n");

        cursor = cursor->next;
    }

    fclose(file);
}


void helpMenu(){
    int selectHelp;
    printf("====================================\n");
    printf("               HELP MENU\n");
    printf("====================================\n");
    printf("1. Informasi Tambah Produk\n");
    printf("2. Informasi Hapus Produk\n");
    printf("3. Informasi Catat Penjualan\n");
    printf("4. Informasi Pencarian Produk\n");
    printf("5. Informasi Laporan Produk saat ini\n");
    printf("6. Informasi Laporan Penjualan\n");
    printf("7. Informasi Help\n");
    printf("0. Informasi Keluar aplikasi\n");
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
            //belum
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
            //belom
            break;
            

        }
}

void printTabelPenjualan(customerNode head)
{
    int i;
    customerNode cursor = head;

    while(cursor != NULL)
    {
        // Menghitung total harga dalam format float
        float tempTotalHarga = cursor->totalHarga / 1000;

        // Menampilkan informasi transaksi
        printf("\nKode Transaksi: %d\n", cursor->kodeTransaksi);
        printf("Waktu Transaksi: %s\n", cursor->waktuTransaksi);
        printf("=======================================================================\n");
        printf("| %-15s | %-15s | %-13s | %-15s |\n", "Produk", "Harga(pcs)", "Kuantitas", "Total");
        printf("=======================================================================\n");

        // Menampilkan daftar belanja
        for (i = 0; i < cursor->counterProduk; i++)
        {
            float tempHargaPcs = cursor->belanja[i]->hargaPerPcs / 1000;
            float tempHargaTotalPcs = cursor->belanja[i]->totalHargaPerPcs / 1000;
            printf("| %-15s | Rp%-13.3f | %-13d | Rp%-13.3f |\n", cursor->belanja[i]->namaProduk, tempHargaPcs, cursor->belanja[i]->kuantitasProduk, tempHargaTotalPcs);
        }
        // Menampilkan total harga
        printf("-----------------------------------------------------------------------\n");
        printf("| Total Harga: Rp%-52.3f |\n", tempTotalHarga);
        printf("=======================================================================\n");

        cursor = cursor->next;
    }
}


nodeP* updateProduct(productNode head, char kodeProduk[][100], int kuantitasProduk[], int counter)
{
    if (head == NULL || counter <= 0) {
        return head; // Tidak ada perubahan
    }

    nodeP *cursor = head;
    int i = 0;
    while (cursor != NULL && i < counter)
    {
        // Pemeriksaan batas
        if (i >= counter) {
            break;
        }

        if (strcasecmp(cursor->kodeProduk, kodeProduk[i]) == 0)
        {
            // Jika Produk ditemukan, maka stok akan dikurangi
            if (cursor->stock >= kuantitasProduk[i]) {
                cursor->stock -= kuantitasProduk[i];
            } else {
                printf("Stok produk '%s' tidak mencukupi\n", kodeProduk[i]);
                break; // Hentikan iterasi jika stok tidak mencukupi
            }
            i++;
        }

        cursor = cursor->next;
    }
    return head;
}

char* generateWaktu() {
    // Mengatur locale untuk menggunakan bahasa Indonesia
    setlocale(LC_ALL, "id_ID");

    // Mendapatkan waktu saat ini
    time_t rawtime;
    struct tm * timeinfo;
    char *buffer = (char *)malloc(50 * sizeof(char)); // Alokasi dinamis

    if (buffer == NULL) {
        perror("Gagal mengalokasikan memori");
        exit(EXIT_FAILURE);
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Memformat waktu dan tanggal dalam format yang diinginkan
    strftime(buffer, 50, "%H:%M:%S, %d-%m-%Y", timeinfo);

    return buffer;
}

int generateKodeTransaksi(customerNode head)
{
    customerNode cursor = head;
    int boundedRandomNumber;
    bool unique;

    do {

        unique = true;
        // Jika Anda ingin menghasilkan angka acak dalam rentang tertentu, misalnya 100 hingga 1100
        boundedRandomNumber = rand() % 1000 + 100;

        while (cursor != NULL) {
            if (cursor->kodeTransaksi == boundedRandomNumber) {
                unique = false;
                break;
            }
            cursor = cursor->next;
        }

    } while (!unique);

    return boundedRandomNumber;
}

nodeC *createLinkedListCustomer(customerNode head, char produk[][100], int hargaPerPcs[], int kuantitasProduk[], int counter)
{
    int i;

    /// Mengalokasikan memori untuk node baru
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
        
    // Mengatur waktu transaksi
    char *waktu = generateWaktu();
    strcpy(new_node->waktuTransaksi, waktu);
    free(waktu);

    new_node->kodeTransaksi = generateKodeTransaksi(head);
    new_node->counterProduk = counter;
    new_node->totalHarga = 0;

    // Mengisi data produk
    for (i = 0; i < counter; i++)
    {
        strcpy(new_node->belanja[i]->namaProduk, produk[i]);
        new_node->belanja[i]->hargaPerPcs = hargaPerPcs[i];
        new_node->belanja[i]->totalHargaPerPcs = hargaPerPcs[i] * kuantitasProduk[i];
        new_node->belanja[i]->kuantitasProduk = kuantitasProduk[i];
        new_node->totalHarga += new_node->belanja[i]->totalHargaPerPcs;
    }
    

    // Menambahkan node baru ke linked list
    new_node->next = head;

    return new_node;
}

void freeCustomerList(customerNode head) {
    nodeC* currentCustomer = head;

    while (currentCustomer != NULL) {
        // Bebaskan setiap produk dalam array belanja
        for (int i = 0; i < currentCustomer->counterProduk; i++) {
            if (currentCustomer->belanja[i] != NULL) {
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

nodeP* searchProduct(productNode head, char* nama, int mode)
{
    nodeP* cursor = head;
    nodeP* copy = malloc(sizeof(nodeP));
    
    int i;
    

    while(cursor != NULL)
    {
        char tempProduk[100];
        char tempCari[100];
        
        if(mode == 1)   // Cari berdasarkan nama produk
        {
            for(i = 0; nama[i]; i++) {
                tempCari[i] = tolower(nama[i]);
            }
            tempCari[i] = '\0'; // Tambahkan terminator null pada akhir string

            for(i = 0; cursor->nama[i]; i++) {
                tempProduk[i] = tolower(cursor->nama[i]);
            }
            tempProduk[i] = '\0'; // Tambahkan terminator null pada akhir string

            if(strstr(tempCari, tempProduk) != NULL)
            {
                return cursor;
            }
            cursor = cursor->next;

        } else {    // Cari berdasarkan kode produk
            for(i = 0; nama[i]; i++) {
                tempCari[i] = tolower(nama[i]);
            }
            tempCari[i] = '\0'; // Tambahkan terminator null pada akhir string

            for(i = 0; cursor->nama[i]; i++) {
                tempProduk[i] = tolower(cursor->kodeProduk[i]);
            }
            tempProduk[i] = '\0'; // Tambahkan terminator null pada akhir string

            if(strstr(tempCari, tempProduk) != NULL)
            {

                return cursor;
            }
            cursor = cursor->next;
        }
        
    }

    return NULL;
}

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

void printTabelProduk(productNode head, int mode) {
    productNode cursor = head;
    float tempHarga;
    printf("=====================================================================================\n");
    printf("| %-15s | %-15s | %-17s | %-10s | %-12s |\n", "Nama Produk", "Kategori", "Harga (satuan)", "Stock", "Kode Produk");
    printf("=====================================================================================\n");
    
    if(mode == 1){ // Hanya akan memprint baris pertama
        tempHarga = cursor->harga / 1000;
        printf("| %-15s | %-15s | Rp%-15.3f | %-10d | %-12s |\n", cursor->nama, cursor->kategori, tempHarga, cursor->stock, cursor->kodeProduk);
    } else {    // Memprint semuanya
        while (cursor != NULL) {
            tempHarga = cursor->harga / 1000;
            printf("| %-15s | %-15s | Rp%-15.3f | %-10d | %-12s |\n", cursor->nama, cursor->kategori, tempHarga, cursor->stock, cursor->kodeProduk);
            cursor = cursor->next;
        }
    }
    
    printf("-------------------------------------------------------------------------------------\n");
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
    printf("||  Versi: 1.0                            ||\n");
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
