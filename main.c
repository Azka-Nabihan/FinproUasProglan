#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Mendefinisikan Struct product
typedef struct node {
    char nama[100];
    char kategori[100];
    int harga;
    int stock;
    char kodeProduk[100];
    struct node* next;
} nodeP;

typedef nodeP* productNode;

void bumperProgram();
void printMenu();
void printTabelProduk(productNode head, int mode);
nodeP* createLinkedList(productNode head, char* nama, char* kategori, int harga, int stock, char* kodeProduk);
nodeP* searchProduct(productNode head, char *nama);
nodeP *removeProduct(productNode head, productNode temp);

int main() {
    // Definisikan
    productNode product = NULL;
    productNode temp = NULL;

    int select;
    char tempNama[100];
    char tempKategori[100];
    int tempHarga;
    int tempStock;
    char tempKodeProduk[100];

    bumperProgram();

    printf("\n\n"); // Ganti ini dengan sleep dan clear nanti

    do {
        printMenu();
        scanf("%d", &select);

        switch (select) {
            case 1: // Tambah Produk
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
                product = createLinkedList(product, tempNama, tempKategori, tempHarga, tempStock, tempKodeProduk);
                printf("Data berhasil disimpan!\n");
                break;

            case 2: // Hapus Produk
                printTabelProduk(product, 2);  //mode selain 1 akan memprint semuanya
                printf("Nama produk yang ingin dihapus: ");
                scanf("%s", tempNama);
                temp = searchProduct(product, tempNama);
                if(temp == NULL){
                    printf("Data Tidak Ditemukan!\n");
                } 
                else {
                    printTabelProduk(temp, 1);
                    printf("Apakah benar data tersebut yang ingin dihapus? \n1. Ya\n2. Tidak \nInput: ");
                    scanf("%d", &select);
                    if(select == 1){
                        product = removeProduct(product, temp);
                        printf("Produk berhasil dihapus!\n");
                    }
                }
                break;

            case 3: // Catat Penjualan
                // kode
                break;

            case 4: // Pencarian Produk
                printf("Nama produk yang ingin dicari: ");
                scanf("%s", tempNama);
                temp = searchProduct(product, tempNama);
                if(temp != NULL)
                {
                    printTabelProduk(temp, 1);  //mode selain 1 akan memprint semuanya
                    printf("Produk Ditemukan!\n");
                } else {
                    printf("Produk Tidak Ditemukan!\n");
                }
                break;

            case 5: // Laporan Produk saat ini
                printTabelProduk(product, 2);
                break;

            case 6: // Laporan Penjualan
                // kode
                break;

            case 7: // Help
                // kode
                break;

            case 0: // Keluar Aplikasi
                printf("Keluar aplikasi. Terima kasih!\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (select != 0);

    return 0;
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
            head == NULL;

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

nodeP* searchProduct(productNode head, char* nama)
{
    nodeP* cursor = head;
    nodeP* copy = malloc(sizeof(nodeP));
    
    int i;
    

    while(cursor != NULL)
    {
        char tempNamaProduct[100];
        char tempNamaCari[100];

        for(i = 0; nama[i]; i++) {
            tempNamaCari[i] = tolower(nama[i]);
        }
        tempNamaCari[i] = '\0'; // Tambahkan terminator null pada akhir string

        for(i = 0; cursor->nama[i]; i++) {
            tempNamaProduct[i] = tolower(cursor->nama[i]);
        }
        tempNamaProduct[i] = '\0'; // Tambahkan terminator null pada akhir string

        if(strstr(tempNamaCari, tempNamaProduct) != NULL)
        {

            return cursor;
        }
        cursor = cursor->next;
    }

    return NULL;
}

nodeP* createLinkedList(productNode head, char* nama, char* kategori, int harga, int stock, char* kodeProduk) {
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
    printf("| %-15s | %-15s | %-15s | %-10s | %-12s |\n", "Nama Produk", "Kategori", "Harga (satuan)", "Stock", "Kode Produk");
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
    printf("3. Catat Penjualan\n");
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
    printf("||  Dibuat oleh: Kelompok 11              ||\n");
    printf("||  Versi: 1.0                            ||\n");
    printf("||  Selamat datang!                       ||\n");
    printf("============================================\n\n");
}
