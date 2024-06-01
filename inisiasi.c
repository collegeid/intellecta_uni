#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mahasiswa.c"

void startApp() {
    printf("Selamat datang.. Pilih menu:\n");
    // Placeholder for actual app start logic
}

int main() {
    printf("INISIASI\n");

    char softwareName[100];

    while (1) {
        printf("Masukkan nama software: ");
        if (fgets(softwareName, sizeof(softwareName), stdin) == NULL) {
            printf("ERROR\n");
            printf("OUTPUT - error: Gagal membaca nama software\n");
            return 1; // Exit with error code
        }

        // Remove newline character if present
        size_t len = strlen(softwareName);
        if (len > 0 && softwareName[len - 1] == '\n') {
            softwareName[len - 1] = '\0';
        }

        if (strlen(softwareName) == 0) {
            printf("ERROR\n");
            printf("OUTPUT - error: Nama software tidak boleh kosong\n");
        } else {
            break;
        }
    }

    printf("Software Name: %s\n", softwareName);

    startApp();

    // Call function from mahasiswa.c
    main_mahasiswa();

    return 0;
}
