#include <stdio.h>
#include <stdlib.h>
#include "nbtrees.h"

int main() {
    Isi_Tree T;
    int menu, idx;
    infotype cari, data1, data2;
    Create_tree(T, jml_maks);

    // pre defined tree
    T[1] = Nb('A', 2, 0, 0);
    T[2] = Nb('B', 4, 3, 1);
    T[3] = Nb('C', 6, 0, 1);   
    T[4] = Nb('D', 0, 5, 2);
    T[5] = Nb('E', 9, 0, 2);
    T[6] = Nb('F', 0, 7, 3);
    T[7] = Nb('G', 0, 8, 3);
    T[8] = Nb('H', 0, 0, 3);
    T[9] = Nb('I', 0, 10, 5);
    T[10] = Nb('J', 0, 0, 5);

    do {
        printf("\nOPERASI NON-BINARY TREE\n");
        printf("1. PreOrder Traversal\n");
        printf("2. InOrder Traversal\n");
        printf("3. PostOrder Traversal\n");
        printf("4. Level Order Traversal\n");
        printf("5. Print Tree\n");
        printf("6. Search tree node\n");
        printf("7. Count number of leaf\n");
        printf("8. Find level node tree\n");
        printf("9. Get depth of tree\n");
        printf("10. Compare 2 tree nodes\n");
        printf("11. Exit\n");
        printf("Pilih menu: ");
        scanf("%d", &menu);
        
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        switch(menu) {
            case 1:
                printf("PreOrder Traversal: ");
                PreOrder(T);
                break;
            case 2:
                printf("InOrder Traversal: ");
                InOrder(T);
                break;
            case 3:
                printf("PostOrder Traversal: ");
                PostOrder(T);
                break;
            case 4:
                printf("Level Order Traversal: ");
                Level_order(T, jml_maks);
                break;
            case 5:
                PrintTree(T);
                break;
            case 6:
                printf("Masukkan info node yang dicari: ");
                scanf(" %c", &cari);
                if (Search(T, cari))
                    printf("Node %c ditemukan di tree.\n", cari);
                else
                    printf("Node %c tidak ditemukan di tree.\n", cari);
                break;
            case 7:
                printf("Jumlah daun: %d\n", nbDaun(T));
                break;
            case 8:
                printf("Masukkan info node: ");
                scanf(" %c", &cari);
                idx = Level(T, cari);
                if (idx != -1)
                    printf("Level node %c: %d\n", cari, idx);
                else
                    printf("Node %c tidak ditemukan.\n", cari);
                break;
            case 9:
                printf("Depth/tinggi tree: %d\n", Depth(T));
                break;
            case 10:
                printf("Masukkan info node pertama: ");
                scanf(" %c", &data1);
                printf("Masukkan info node kedua: ");
                scanf(" %c", &data2);
                printf("Node terbesar: %c\n", Max(data1, data2));
                break;
            case 11:
                printf("Keluar program.\n");
                break;
            default:
                printf("Menu tidak valid.\n");
        }
    } while(menu != 11);

    return 0;
}
