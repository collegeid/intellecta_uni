#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NIM_LENGTH 14
#define MAX_PASSWORD_LENGTH 19
#define MAX_NAMA_LENGTH 49
#define MAX_KELAS_LENGTH 9
#define MAX_EMAIL_LENGTH 49
#define MAX_GENDER_LENGTH 9

// Define structures for student profile and account
typedef struct {
    int id;
    char NIM[MAX_NIM_LENGTH + 1];
    char nama[MAX_NAMA_LENGTH + 1];
    char kelas[MAX_KELAS_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
    char gender[MAX_GENDER_LENGTH + 1];
    int semester;
} Mahasiswa;

typedef struct {
    char NIM[MAX_NIM_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
} AkunMahasiswa;

// Global variables to store student and account data
Mahasiswa *mahasiswaData = NULL;
AkunMahasiswa *akunMahasiswaData = NULL;
int mahasiswaCount = 0;
int akunCount = 0;

// Function to check if NIM is registered
bool checkNIM(const char NIM[]) {
    for (int i = 0; i < akunCount; i++) {
        if (strcmp(akunMahasiswaData[i].NIM, NIM) == 0) {
            return true; // NIM found
        }
    }
    return false; // NIM not found
}

// Function to check login credentials
bool checkLogin(const char NIM[], const char password[]) {
    for (int i = 0; i < akunCount; i++) {
        if (strcmp(akunMahasiswaData[i].NIM, NIM) == 0 && strcmp(akunMahasiswaData[i].password, password) == 0) {
            return true; // Login successful
        }
    }
    return false; // Login failed
}

// Function to add a new student
void addMahasiswa(const char NIM[], const char nama[], const char kelas[], const char email[], const char gender[], int semester) {
    mahasiswaData = realloc(mahasiswaData, (mahasiswaCount + 1) * sizeof(Mahasiswa));
    if (mahasiswaData == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    mahasiswaData[mahasiswaCount].id = mahasiswaCount + 1;
    strncpy(mahasiswaData[mahasiswaCount].NIM, NIM, MAX_NIM_LENGTH);
    strncpy(mahasiswaData[mahasiswaCount].nama, nama, MAX_NAMA_LENGTH);
    strncpy(mahasiswaData[mahasiswaCount].kelas, kelas, MAX_KELAS_LENGTH);
    strncpy(mahasiswaData[mahasiswaCount].email, email, MAX_EMAIL_LENGTH);
    strncpy(mahasiswaData[mahasiswaCount].gender, gender, MAX_GENDER_LENGTH);
    mahasiswaData[mahasiswaCount].semester = semester;
    mahasiswaCount++;
}

// Function to register a new student
void registerMahasiswa() {
    char NIM[MAX_NIM_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    char nama[MAX_NAMA_LENGTH + 1];
    char kelas[MAX_KELAS_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
    char gender[MAX_GENDER_LENGTH + 1];
    int semester;

    do {
        printf("Masukkan NIM: ");
        fgets(NIM, sizeof(NIM), stdin);
        strtok(NIM, "\n"); // Remove newline character
    } while (strcmp(NIM, "") == 0 || strcmp(NIM, "\n") == 0 || strlen(NIM) > MAX_NIM_LENGTH);

    // Check if NIM is already registered
    if (checkNIM(NIM)) {
        printf("NIM sudah terdaftar.\n");
        return;
    }

    do {
        printf("Masukkan Password: ");
        fgets(password, sizeof(password), stdin);
        strtok(password, "\n"); // Remove newline character
    } while (strcmp(password, "") == 0 || strcmp(password, "\n") == 0 || strlen(password) > MAX_PASSWORD_LENGTH);

    do {
        printf("Masukkan Nama: ");
        fgets(nama, sizeof(nama), stdin);
        strtok(nama, "\n"); // Remove newline character
    } while (strcmp(nama, "") == 0 || strcmp(nama, "\n") == 0 || strlen(nama) > MAX_NAMA_LENGTH);

    do {
        printf("Masukkan Kelas: ");
        fgets(kelas, sizeof(kelas), stdin);
        strtok(kelas, "\n"); // Remove newline character
    } while (strcmp(kelas, "") == 0 || strcmp(kelas, "\n") == 0 || strlen(kelas) > MAX_KELAS_LENGTH);

    do {
        printf("Masukkan Email: ");
        fgets(email, sizeof(email), stdin);
        strtok(email, "\n"); // Remove newline character
    } while (strcmp(email, "") == 0 || strcmp(email, "\n") == 0 || strlen(email) > MAX_EMAIL_LENGTH);

    do {
        printf("Masukkan Gender: ");
        fgets(gender, sizeof(gender), stdin);
        strtok(gender, "\n"); // Remove newline character
    } while (strcmp(gender, "") == 0 || strcmp(gender, "\n") == 0 || strlen(gender) > MAX_GENDER_LENGTH);

    do {
        printf("Masukkan Semester: ");
        scanf("%d", &semester);
        while (getchar() != '\n'); // Clear buffer
    } while (semester <= 0);

    // Add new student account
    akunMahasiswaData = realloc(akunMahasiswaData, (akunCount + 1) * sizeof(AkunMahasiswa));
    if (akunMahasiswaData == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(akunMahasiswaData[akunCount].NIM, NIM, MAX_NIM_LENGTH);
    strncpy(akunMahasiswaData[akunCount].password, password, MAX_PASSWORD_LENGTH);
    akunCount++;

    // Add student data
    addMahasiswa(NIM, nama, kelas, email, gender, semester);

    printf("Registrasi berhasil!\n");
}

// Function for student login
void login() {
    char inputNIM[MAX_NIM_LENGTH + 1];
    char inputPassword[MAX_PASSWORD_LENGTH + 1];

    printf("Masukkan NIM: ");
    fgets(inputNIM, sizeof(inputNIM), stdin);
    strtok(inputNIM, "\n"); // Remove newline character

    // Check if NIM is registered
    if (!checkNIM(inputNIM)) {
        printf("NIM tidak terdaftar.\n");
        return;
    }

    printf("Masukkan Password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    strtok(inputPassword, "\n"); // Remove newline character

    // Check if login is successful
    if (checkLogin(inputNIM, inputPassword)) {
        printf("Login berhasil!\n");
    } else {
        printf("Password salah.\n");
    }
}

int main() {
    // Main menu
    int pilihan;
    do {
        printf("\nMenu:\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        while (getchar() != '\n'); // Clear buffer

        switch (pilihan) {
            case 1:
                login(); // Call login function
                break;
            case 2:
                registerMahasiswa(); // Call register function
                break;
            case 3:
                printf("Keluar.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (pilihan != 3);

    // Cleanup memory
    free(mahasiswaData);
    free(akunMahasiswaData);

    return 0;
}
