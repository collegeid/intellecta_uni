#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.c"


int main() {
    int role;
    printf("Selamat datang!\n");
    printf("Pilih peran Anda:\n");
    printf("1. Mahasiswa\n");
    printf("2. Admin\n");
    printf("Pilihan: ");
    scanf("%d", &role);
    getchar(); 

    if (role == 1) {
       
    } else if (role == 2) {
         main_admin();
    } else {
        printf("Pilihan tidak valid.\n");
    }

    return 0;
}