
// nodeP* searchProduct(productNode head, char* nama, int mode)
// {
//     nodeP* cursor = head;
//     nodeP* tempStructProduct = NULL;

//     int i;

//     while(cursor != NULL)
//     {
//         char tempProduk[100];
//         char tempCari[100];

//         if(mode == 1) // Cari berdasarkan nama produk
//         {
//             for(i = 0; i<100; i++) {
//                 tempCari[i] = tolower(nama[i]);
//             }
//             tempCari[i] = '\0'; // Tambahkan terminator null pada akhir string

//             for(i = 0; i<100; i++) {
//                 tempProduk[i] = tolower(cursor->nama[i]);
//             }
//             tempProduk[i] = '\0'; // Tambahkan terminator null pada akhir string

//             // Gunakan strstr() untuk mencari substring
//             if(strstr(tempProduk, tempCari) != NULL)
//             {
//                 tempStructProduct = createLinkedListProduct(tempStructProduct, cursor->nama, cursor->kategori, cursor->harga, cursor->stock, cursor->kodeProduk);
//                 if(cursor->next == NULL)
//                 {
//                     return tempStructProduct;
//                 }
//             }
//         }
//         else // Cari berdasarkan kode produk
//         {
//             for(i = 0; nama[i]; i++) {
//                 tempCari[i] = tolower(nama[i]);
//             }
//             tempCari[i] = '\0'; // Tambahkan terminator null pada akhir string

//             for(i = 0; cursor->kodeProduk[i]; i++) {
//                 tempProduk[i] = tolower(cursor->kodeProduk[i]);
//             }
//             tempProduk[i] = '\0'; // Tambahkan terminator null pada akhir string

//             // Gunakan strstr() untuk mencari substring
//             if(strstr(tempProduk, tempCari) != NULL)
//             {
//                 tempStructProduct = createLinkedListProduct(tempStructProduct, cursor->nama, cursor->kategori, cursor->harga, cursor->stock, cursor->kodeProduk);
//                 if(cursor->next == NULL)
//                 {
//                     return tempStructProduct;
//                 }
//             }
//         }

//         cursor = cursor->next;
//     }

//     return NULL;
// }
