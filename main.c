#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.c"

void loginAdmin();

int main() {
    int role = 1;
    printf("Selamat datang!\n");
    printf("Pilih peran Anda:\n");
    printf("1. Mahasiswa\n");
    printf("2. Admin\n");
    printf("Pilihan: ");
    scanf("%d", &role);
    getchar();

    if (role == 1) {
       main_mahasiswa();
    } else if (role == 2) {
       loginAdmin();
    } else {
        printf("Pilihan tidak valid.\n");
    }

    return 0;
}
