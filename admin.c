#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mahasiswa.c"  // Menghubungkan dengan file mahasiswa.c

void adminMenu();
void addMahasiswaAdmin();
void editMahasiswaAdmin();
void deleteMahasiswaAdmin();
void viewMahasiswaAdmin();
void addNilaiAdmin();
void editNilaiAdmin();
void viewNilaiAdmin();

void adminMenu() {
    int choice;
    do {
        printf("Manajemen Akun:\n1. Tambah Akun Mahasiswa\n2. Edit Akun Mahasiswa\n3. Lihat Data Mahasiswa\n4. Hapus Akun Mahasiswa\n5. Kembali\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left in buffer

        switch (choice) {
            case 1:
                addMahasiswaAdmin();
                break;
            case 2:
                editMahasiswaAdmin();
                break;
            case 3:
               viewMahasiswaAdmin();
                break;
            case 4:
                deleteMahasiswaAdmin();
                break;
            case 5:
                return;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (choice != 5);
}

void addMahasiswaAdmin() {
    char NIM[MAX_NIM_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    char nama[MAX_NAMA_LENGTH + 1];
    char kelas[MAX_KELAS_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
    char gender[MAX_GENDER_LENGTH + 1];
    int semester;

    // Input student data
    do {
        printf("Masukkan NIM: ");
        fgets(NIM, sizeof(NIM), stdin);
        strtok(NIM, "\n");  // Remove newline character
    } while (strcmp(NIM, "") == 0 || strlen(NIM) > MAX_NIM_LENGTH);

    if (checkNIM(NIM)) {
        printf("NIM sudah terdaftar.\n");
        return;
    }

    do {
        printf("Masukkan Password: ");
        fgets(password, sizeof(password), stdin);
        strtok(password, "\n");  // Remove newline character
    } while (strcmp(password, "") == 0 || strlen(password) > MAX_PASSWORD_LENGTH);

    do {
        printf("Masukkan Nama: ");
        fgets(nama, sizeof(nama), stdin);
        strtok(nama, "\n");  // Remove newline character
    } while (strcmp(nama, "") == 0 || strlen(nama) > MAX_NAMA_LENGTH);

    do {
        printf("Masukkan Kelas: ");
        fgets(kelas, sizeof(kelas), stdin);
        strtok(kelas, "\n");  // Remove newline character
    } while (strcmp(kelas, "") == 0 || strlen(kelas) > MAX_KELAS_LENGTH);

    do {
        printf("Masukkan Email: ");
        fgets(email, sizeof(email), stdin);
        strtok(email, "\n");  // Remove newline character
    } while (strcmp(email, "") == 0 || strlen(email) > MAX_EMAIL_LENGTH);

    do {
        printf("Masukkan Gender (L/P): ");
        fgets(gender, sizeof(gender), stdin);
        strtok(gender, "\n");  // Remove newline character
    } while (strcmp(gender, "") == 0 || strlen(gender) > MAX_GENDER_LENGTH);

    printf("Masukkan Semester: ");
    scanf("%d", &semester);
    getchar();  // Consume newline character left in buffer

    // Add student account and profile
    addAkunMahasiswa(NIM, password);
    addMahasiswa(NIM, nama, kelas, email, gender, semester);
    printf("Akun Mahasiswa berhasil ditambahkan.\n");
}

void editMahasiswaAdmin() {
    char NIM[MAX_NIM_LENGTH + 1];
    printf("Masukkan NIM Mahasiswa yang akan diedit: ");
    fgets(NIM, sizeof(NIM), stdin);
    strtok(NIM, "\n");  // Remove newline character

    if (!checkNIM(NIM)) {
        printf("NIM tidak terdaftar.\n");
        return;
    } else {

    char nama[MAX_NAMA_LENGTH + 1];
    char kelas[MAX_KELAS_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
    char gender[MAX_GENDER_LENGTH + 1];
    int semester;

    // Input updated student data
    printf("Masukkan Nama baru: ");
    fgets(nama, sizeof(nama), stdin);
    strtok(nama, "\n");  // Remove newline character

    printf("Masukkan Kelas baru: ");
    fgets(kelas, sizeof(kelas), stdin);
    strtok(kelas, "\n");  // Remove newline character

    printf("Masukkan Email baru: ");
    fgets(email, sizeof(email), stdin);
    strtok(email, "\n");  // Remove newline character

    printf("Masukkan Gender baru (L/P): ");
    fgets(gender, sizeof(gender), stdin);
    strtok(gender, "\n");  // Remove newline character

    printf("Masukkan Semester baru: ");
    scanf("%d", &semester);
    getchar();  // Consume newline character left in buffer

    // Update student data
    for (int i = 0; i < mahasiswaCount; i++) {
        if (strcmp(mahasiswaData[i].NIM, NIM) == 0) {
            strncpy(mahasiswaData[i].nama, nama, MAX_NAMA_LENGTH);
            strncpy(mahasiswaData[i].kelas, kelas, MAX_KELAS_LENGTH);
            strncpy(mahasiswaData[i].email, email, MAX_EMAIL_LENGTH);
            strncpy(mahasiswaData[i].gender, gender, MAX_GENDER_LENGTH);
            mahasiswaData[i].semester = semester;
            printf("Data Mahasiswa berhasil diupdate.\n");
            return;
        }
    }
    }
}

void deleteMahasiswaAdmin() {
    char NIM[MAX_NIM_LENGTH + 1];
    printf("Masukkan NIM Mahasiswa yang akan dihapus: ");
    fgets(NIM, sizeof(NIM), stdin);
    strtok(NIM, "\n");  // Remove newline character

    if (!checkNIM(NIM)) {
        printf("NIM tidak terdaftar.\n");
        return;
    } else {

    // Remove student data
    for (int i = 0; i < mahasiswaCount; i++) {
        if (strcmp(mahasiswaData[i].NIM, NIM) == 0) {
            for (int j = i; j < mahasiswaCount - 1; j++) {
                mahasiswaData[j] = mahasiswaData[j + 1];
            }
            mahasiswaCount--;
            mahasiswaData = realloc(mahasiswaData, mahasiswaCount * sizeof(Mahasiswa));

            // Remove student account data
            for (int k = 0; k < akunCount; k++) {
                if (strcmp(akunMahasiswaData[k].NIM, NIM) == 0) {
                    for (int l = k; l < akunCount - 1; l++) {
                        akunMahasiswaData[l] = akunMahasiswaData[l + 1];
                    }
                    akunCount--;
                    akunMahasiswaData = realloc(akunMahasiswaData, akunCount * sizeof(AkunMahasiswa));
                    printf("Akun Mahasiswa berhasil dihapus.\n");
                    return;
                }
            }
        }
    }

}
}

void viewMahasiswaAdmin() {
    printf("Data Mahasiswa:\n");
    for (int i = 0; i < mahasiswaCount; i++) {
        printf("NIM: %s, Nama: %s, Kelas: %s, Email: %s, Gender: %s, Semester: %d\n", mahasiswaData[i].NIM, mahasiswaData[i].nama, mahasiswaData[i].kelas, mahasiswaData[i].email, mahasiswaData[i].gender, mahasiswaData[i].semester);
    }
}


void displayMatakuliah() {
    printf("Daftar Mata Kuliah:\n");
    for (int i = 0; i < matakuliahCount; i++) {
        printf("%d. %s (%d SKS)\n", matakuliahData[i].id, matakuliahData[i].matakuliah, matakuliahData[i].sks);
    }
}
void addNilaiAdmin() {
    char NIM[MAX_NIM_LENGTH + 1];
    char tahunAkademik[MAX_TAHUN_AKADEMIK_LENGTH + 1];
    int semester;
    float nilaiTugas, nilaiUTS, nilaiUAS;
    int selectedCourse;

    printf("Masukkan NIM: ");
    fgets(NIM, sizeof(NIM), stdin);
    strtok(NIM, "\n");  // Remove newline character

    if (!checkNIM(NIM)) {
        printf("NIM tidak terdaftar.\n");
        return;
    } else {
        // Display the list of courses
        displayMatakuliah();

        // Input course number
        printf("Masukkan nomor Mata Kuliah: ");
        scanf("%d", &selectedCourse);
        getchar();  // Consume newline character left in buffer

        // Get the name of the selected course based on the input number
        char matakuliah[MAX_MATKUL_LENGTH + 1];
        if (selectedCourse >= 1 && selectedCourse <= matakuliahCount) {
            strncpy(matakuliah, matakuliahData[selectedCourse - 1].matakuliah, MAX_MATKUL_LENGTH);
        } else {
            printf("Nomor Mata Kuliah tidak valid.\n");
            return;
        }

        printf("Masukkan Tahun Akademik(eg: 2023/2024): ");
        fgets(tahunAkademik, sizeof(tahunAkademik), stdin);
        strtok(tahunAkademik, "\n");  // Remove newline character

        printf("Masukkan Semester: ");
        scanf("%d", &semester);
        getchar();  // Consume newline character left in buffer

        printf("Masukkan Nilai Tugas: ");
        scanf("%f", &nilaiTugas);
        getchar();  // Consume newline character left in buffer

        printf("Masukkan Nilai UTS: ");
        scanf("%f", &nilaiUTS);
        getchar();  // Consume newline character left in buffer

        printf("Masukkan Nilai UAS: ");
        scanf("%f", &nilaiUAS);
        getchar();  // Consume newline character left in buffer

        addAkademik(NIM, semester, matakuliah, tahunAkademik, nilaiTugas, nilaiUTS, nilaiUAS);
        printf("Nilai berhasil ditambahkan.\n");
    }
}

void editNilaiAdmin() {
    char NIM[MAX_NIM_LENGTH + 1];
    char matakuliah[MAX_MATKUL_LENGTH + 1];
    char tahunAkademik[MAX_TAHUN_AKADEMIK_LENGTH + 1];
    int semester;
    float nilaiTugas, nilaiUTS, nilaiUAS;

    printf("Masukkan NIM: ");
    fgets(NIM, sizeof(NIM), stdin);
    strtok(NIM, "\n");  // Remove newline character

    if (!checkNIM(NIM)) {
        printf("NIM tidak terdaftar.\n");
        return;
    } else {
        printf("Pilih Mata Kuliah:\n");
        displayMatakuliah(); // Menampilkan daftar mata kuliah

        int selectedMatakuliah;
        printf("Masukkan nomor Mata Kuliah: ");
        scanf("%d", &selectedMatakuliah);
        getchar();  // Consume newline character left in buffer

        if (selectedMatakuliah < 1 || selectedMatakuliah > matakuliahCount) {
            printf("Nomor Mata Kuliah tidak valid.\n");
            return;
        }

        strncpy(matakuliah, matakuliahData[selectedMatakuliah - 1].matakuliah, sizeof(matakuliah));

        printf("Masukkan Tahun Akademik: ");
        fgets(tahunAkademik, sizeof(tahunAkademik), stdin);
        strtok(tahunAkademik, "\n");  // Remove newline character

        printf("Masukkan Semester: ");
        scanf("%d", &semester);
        getchar();  // Consume newline character left in buffer

        // Search for the existing grade
        float prevNilaiTugas = -1, prevNilaiUTS = -1, prevNilaiUAS = -1;
        for (int i = 0; i < akademikCount; i++) {
            if (strcmp(akademikData[i].NIM, NIM) == 0 && strcmp(akademikData[i].matakuliah, matakuliah) == 0 && strcmp(akademikData[i].tahunAkademik, tahunAkademik) == 0 && akademikData[i].semester == semester) {
                prevNilaiTugas = akademikData[i].nilaiTugas;
                prevNilaiUTS = akademikData[i].nilaiUTS;
                prevNilaiUAS = akademikData[i].nilaiUAS;
                break;
            }
        }

        // Display previous grades if found
        if (prevNilaiTugas >= 0 && prevNilaiUTS >= 0 && prevNilaiUAS >= 0) {
          // Input new grades
        printf("Masukkan Nilai Tugas (kosongkan jika tidak ingin mengubah, nilai sebelumnya %.2f): ", prevNilaiTugas);
        char input[10];
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "\n") != 0) {
            sscanf(input, "%f", &nilaiTugas);
        } else {
            nilaiTugas = prevNilaiTugas;  // Use previous value if input is empty
        }

        printf("Masukkan Nilai UTS (kosongkan jika tidak ingin mengubah, nilai sebelumnya %.2f): ", prevNilaiUTS);
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "\n") != 0) {
            sscanf(input, "%f", &nilaiUTS);
        } else {
            nilaiUTS = prevNilaiUTS;  // Use previous value if input is empty
        }

        printf("Masukkan Nilai UAS (kosongkan jika tidak ingin mengubah, nilai sebelumnya %.2f): ", prevNilaiUAS);
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "\n") != 0) {
            sscanf(input, "%f", &nilaiUAS);
        } else {
            nilaiUAS = prevNilaiUAS;  // Use previous value if input is empty
        }
        } else {
            printf("Nilai sebelumnya tidak ditemukan.\n");
        }

       

        // Update the grades
        for (int i = 0; i < akademikCount; i++) {
            if (strcmp(akademikData[i].NIM, NIM) == 0 && strcmp(akademikData[i].matakuliah, matakuliah) == 0 && strcmp(akademikData[i].tahunAkademik, tahunAkademik) == 0 && akademikData[i].semester == semester) {
                akademikData[i].nilaiTugas = nilaiTugas;
                akademikData[i].nilaiUTS = nilaiUTS;
                akademikData[i].nilaiUAS = nilaiUAS;
                printf("Nilai berhasil diupdate.\n");
                return;
            }
        }

        printf("Nilai tidak ditemukan.\n");
    }
}

void viewNilaiAdmin() {
    char NIM[MAX_NIM_LENGTH + 1];
    printf("Masukkan NIM untuk melihat nilai: ");
    fgets(NIM, sizeof(NIM), stdin);
    strtok(NIM, "\n");  // Remove newline character

    if (!checkNIM(NIM)) {
        printf("NIM tidak terdaftar.\n");
        return;
    } else {

    printf("Nilai Mahasiswa:\n");
    for (int i = 0; i < akademikCount; i++) {
        if (strcmp(akademikData[i].NIM, NIM) == 0) {
            printf("Mata Kuliah: %s, Tahun Akademik: %s, Semester: %d, Nilai Tugas: %.2f, Nilai UTS: %.2f, Nilai UAS: %.2f\n",
                   akademikData[i].matakuliah, akademikData[i].tahunAkademik, akademikData[i].semester,
                   akademikData[i].nilaiTugas, akademikData[i].nilaiUTS, akademikData[i].nilaiUAS);
        }
    }
    }
}



int main_admin() {
    int choice;
    populateSampleData();  // Memasukkan data sampel untuk pengujian

    do {
        printf("Menu Admin:\n1. Manajemen Akun\n2. Manajemen Akademik\n3. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left in buffer

        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                do {
                    printf("Manajemen Akademik:\n1. Tambah Nilai\n2. Edit Nilai\n3. Lihat Nilai\n4. Kembali ke Menu Utama\n");
                    printf("Masukkan pilihan: ");
                    scanf("%d", &choice);
                    getchar();  // Consume newline character left in buffer

                    switch (choice) {
                        case 1:
                            addNilaiAdmin();
                            break;
                        case 2:
                            editNilaiAdmin();
                            break;
                        case 3:
                            viewNilaiAdmin();
                            break;
                        case 4:
                            break;  // Keluar dari loop
                        default:
                            printf("Pilihan tidak valid.\n");
                            break;
                    }
                } while (choice != 4);
                break;
            case 3:
                printf("Terima kasih telah menggunakan sistem ini.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (choice != 3);

    // Free allocated memory
    free(mahasiswaData);
    free(akunMahasiswaData);
    free(akademikData);
    free(matakuliahData);

    return 0;
}
