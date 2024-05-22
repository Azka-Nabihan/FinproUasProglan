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
        printf("-----------------------------------------------------------------------\n");
        printf("| Total Harga: Rp%-52.3f |\n", tempTotalHarga);
        printf("=======================================================================\n");
        system("pause");
        system("cls");
        // Menampilkan total harga
        
        
        cursor = cursor->next;

    }
}