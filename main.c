/*Proyek Akhir UAS*/
/*
Tanggal : 22/05/2024

no. grup : 11
Nama anggota :
1. Azka Nabihan (2306250541)
2. Muhammad Arya Wiandra (2306218295)

Versi : 2.0
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
#include "function.h"

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

