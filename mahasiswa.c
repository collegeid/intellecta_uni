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
#define MAX_MATKUL_LENGTH 49
#define MAX_TAHUN_AKADEMIK_LENGTH 9

// Define structures for student profile, account, academic records, courses, and grades
typedef struct {
    int id;
    char NIM[MAX_NIM_LENGTH + 1];
    char nama[MAX_NAMA_LENGTH + 1];
    char kelas[MAX_KELAS_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
    char gender[MAX_GENDER_LENGTH + 1];
    int semester;
    float IP;
} Mahasiswa;

typedef struct {
    char NIM[MAX_NIM_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
} AkunMahasiswa;

typedef struct {
    int id;
    char matakuliah[MAX_MATKUL_LENGTH + 1];
    int sks;
} Matakuliah;

typedef struct {
    int id;
    char NIM[MAX_NIM_LENGTH + 1];
    int semester;
    char matakuliah[MAX_MATKUL_LENGTH + 1];
    char tahunAkademik[MAX_TAHUN_AKADEMIK_LENGTH + 1];
    float nilaiTugas;
    float nilaiUTS;
    float nilaiUAS;
    char grade;
} Akademik;

// Global variables to store data
Mahasiswa *mahasiswaData = NULL;
AkunMahasiswa *akunMahasiswaData = NULL;
Akademik *akademikData = NULL;
Matakuliah *matakuliahData = NULL;
int mahasiswaCount = 0;
int akunCount = 0;
int akademikCount = 0;
int matakuliahCount = 0;

// Function prototypes
bool checkNIM(const char NIM[]);
bool checkLogin(const char NIM[], const char password[]);
void addMahasiswa(const char NIM[], const char nama[], const char kelas[], const char email[], const char gender[], int semester);
void addAkunMahasiswa(const char NIM[], const char password[]);
void addAkademik(const char NIM[], int semester, const char matakuliah[], const char tahunAkademik[], float nilaiTugas, float nilaiUTS, float nilaiUAS);
void addMatakuliah(const char matakuliah[], int sks);
void registerMahasiswa();
void login();
void checkProfile(const char NIM[]);
void displayAkademik(const char NIM[]);
float calculateIP(const char NIM[], int semester);
float calculateIPK(const char NIM[]);
char calculateGrade(float finalGrade);
void populateSampleData();

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
    mahasiswaData[mahasiswaCount].IP = 0; // Initialize IP
    mahasiswaCount++;
}

// Function to add a new student account
void addAkunMahasiswa(const char NIM[], const char password[]) {
    akunMahasiswaData = realloc(akunMahasiswaData, (akunCount + 1) * sizeof(AkunMahasiswa));
    if (akunMahasiswaData == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(akunMahasiswaData[akunCount].NIM, NIM, MAX_NIM_LENGTH);
    strncpy(akunMahasiswaData[akunCount].password, password, MAX_PASSWORD_LENGTH);
    akunCount++;
}

// Function to add academic records
void addAkademik(const char NIM[], int semester, const char matakuliah[], const char tahunAkademik[], float nilaiTugas, float nilaiUTS, float nilaiUAS) {
    akademikData = realloc(akademikData, (akademikCount + 1) * sizeof(Akademik));
    if (akademikData == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    akademikData[akademikCount].id = akademikCount + 1;
    strncpy(akademikData[akademikCount].NIM, NIM, MAX_NIM_LENGTH);
    akademikData[akademikCount].semester = semester;
    strncpy(akademikData[akademikCount].matakuliah, matakuliah, MAX_MATKUL_LENGTH);
    strncpy(akademikData[akademikCount].tahunAkademik, tahunAkademik, MAX_TAHUN_AKADEMIK_LENGTH);
    akademikData[akademikCount].nilaiTugas = nilaiTugas;
    akademikData[akademikCount].nilaiUTS = nilaiUTS;
    akademikData[akademikCount].nilaiUAS = nilaiUAS;
    akademikData[akademikCount].grade = calculateGrade((nilaiTugas + nilaiUTS + nilaiUAS) / 3); // Calculate and set grade
    akademikCount++;
}

// Function to add a new course
void addMatakuliah(const char matakuliah[], int sks) {
    matakuliahData = realloc(matakuliahData, (matakuliahCount + 1) * sizeof(Matakuliah));
    if (matakuliahData == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    matakuliahData[matakuliahCount].id = matakuliahCount + 1;
    strncpy(matakuliahData[matakuliahCount].matakuliah, matakuliah, MAX_MATKUL_LENGTH);
    matakuliahData[matakuliahCount].sks = sks;
    matakuliahCount++;
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

    // Input student data
    do {
        printf("Masukkan NIM: ");
        fgets(NIM, sizeof(NIM), stdin);
        strtok(NIM, "\n"); // Remove newline character
    } while (strcmp(NIM, "") == 0 || strcmp(NIM, "\n") == 0 || strlen(NIM) > MAX_NIM_LENGTH);

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
        printf("Masukkan Gender (L/P): ");
        fgets(gender, sizeof(gender), stdin);
        strtok(gender, "\n"); // Remove newline character
    } while (strcmp(gender, "") == 0 || strcmp(gender, "\n") == 0 || strlen(gender) > MAX_GENDER_LENGTH);

    printf("Masukkan Semester: ");
    scanf("%d", &semester);
    getchar(); // Consume newline character left in buffer

    // Add student account and profile
    addAkunMahasiswa(NIM, password);
    addMahasiswa(NIM, nama, kelas, email, gender, semester);
    printf("Registrasi berhasil.\n");
}

// Function to log in
void login() {
    char NIM[MAX_NIM_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    printf("Masukkan NIM: ");
    fgets(NIM, sizeof(NIM), stdin);
    strtok(NIM, "\n"); // Remove newline character

    if (!checkNIM(NIM)) {
        printf("NIM tidak terdaftar.\n");
        return;
    }

    printf("Masukkan Password: ");
    fgets(password, sizeof(password), stdin);
    strtok(password, "\n"); // Remove newline character

    if (checkLogin(NIM, password)) {
        printf("Login berhasil.\n");
        int choice;
        do {
            printf("\nMenu:\n1. Check Profile\n2. Display Academic Records\n3. Logout\n");
            printf("Masukkan pilihan: ");
            scanf("%d", &choice);
            getchar(); // Consume newline character left in buffer

            switch (choice) {
                case 1:
                    checkProfile(NIM);
                    break;
                case 2:
                    displayAkademik(NIM);
                    break;
                case 3:
                    printf("Logout berhasil.\n");
                    break;
                default:
                    printf("Pilihan tidak valid.\n");
                    break;
            }
        } while (choice != 3);
    } else {
        printf("Login gagal. NIM atau password salah.\n");
    }
}

// Function to check profile
void checkProfile(const char NIM[]) {
    for (int i = 0; i < mahasiswaCount; i++) {
        if (strcmp(mahasiswaData[i].NIM, NIM) == 0) {
            printf("Profil Mahasiswa:\n");
            printf("NIM: %s\n", mahasiswaData[i].NIM);
            printf("Nama: %s\n", mahasiswaData[i].nama);
            printf("Kelas: %s\n", mahasiswaData[i].kelas);
            printf("Email: %s\n", mahasiswaData[i].email);
            printf("Gender: %s\n", mahasiswaData[i].gender);
            printf("Semester: %d\n", mahasiswaData[i].semester);
         
            return;
        }
    }
    printf("Profil tidak ditemukan.\n");
}

// Function to display academic records
void displayAkademik(const char NIM[]) {
    printf("Rekam Akademik:\n");
    int currentSemester = -1;
    float totalSKS = 0, totalNilai = 0;
    for (int i = 0; i < akademikCount; i++) {
        if (strcmp(akademikData[i].NIM, NIM) == 0) {
            if (currentSemester != akademikData[i].semester) {
                if (currentSemester != -1) {
                    float semesterIP = totalNilai / totalSKS;
                    printf("IP Semester %d: %.2f\n", currentSemester, semesterIP > 4.0 ? 4.0 : semesterIP);
                }
                currentSemester = akademikData[i].semester;
                totalSKS = 0;
                totalNilai = 0;
            }
            printf("Semester: %d\n", akademikData[i].semester);
            printf("Matakuliah: %s\n", akademikData[i].matakuliah);
            printf("Tahun Akademik: %s\n", akademikData[i].tahunAkademik);
            printf("Nilai Tugas: %.2f\n", akademikData[i].nilaiTugas);
            printf("Nilai UTS: %.2f\n", akademikData[i].nilaiUTS);
            printf("Nilai UAS: %.2f\n", akademikData[i].nilaiUAS);

            float finalGrade = (akademikData[i].nilaiTugas + akademikData[i].nilaiUTS + akademikData[i].nilaiUAS) / 3;
            printf("Nilai rata-rata sebelum grade: %.2f (Grade: %c)\n", finalGrade, akademikData[i].grade);

            totalSKS += getSKS(akademikData[i].matakuliah);
            totalNilai += (finalGrade * getSKS(akademikData[i].matakuliah));
        }
    }
    if (currentSemester != -1) {
        float semesterIP = totalNilai / totalSKS;
        printf("IP Semester %d: %.2f\n", currentSemester, semesterIP > 4.0 ? 4.0 : semesterIP);
    }
    // Display IPK (Cumulative GPA)
    float IPK = calculateIPK(NIM);
    printf("IPK: %.2f\n", IPK > 4.0 ? 4.0 : IPK);
}


// Function to calculate IP (GPA for a semester)
float calculateIP(const char NIM[], int semester) {
    int totalSKS = 0;
    float totalNilai = 0;
    for (int i = 0; i < akademikCount; i++) {
        if (strcmp(akademikData[i].NIM, NIM) == 0 && akademikData[i].semester == semester) {
            float finalGrade = (akademikData[i].nilaiTugas + akademikData[i].nilaiUTS + akademikData[i].nilaiUAS) / 3;
            totalNilai += finalGrade * getSKS(akademikData[i].matakuliah);
            totalSKS += getSKS(akademikData[i].matakuliah);
        }
    }
    if (totalSKS == 0) return 0;
    return totalNilai / totalSKS;
}

// Function to calculate IPK (Cumulative GPA)
float calculateIPK(const char NIM[]) {
    int totalSKS = 0;
    float totalNilai = 0;
    for (int i = 0; i < akademikCount; i++) {
        if (strcmp(akademikData[i].NIM, NIM) == 0) {
            float finalGrade = (akademikData[i].nilaiTugas + akademikData[i].nilaiUTS + akademikData[i].nilaiUAS) / 3;
            totalSKS += getSKS(akademikData[i].matakuliah);
            totalNilai += finalGrade * getSKS(akademikData[i].matakuliah);
        }
    }
    if (totalSKS == 0) return 0;
    return totalNilai / totalSKS;
}

// Function to calculate grade based on final grade
char calculateGrade(float finalGrade) {
    if (finalGrade >= 85) return 'A';
    if (finalGrade >= 70) return 'B';
    if (finalGrade >= 55) return 'C';
    if (finalGrade >= 40) return 'D';
    return 'E';
}

// Function to get SKS of a course
int getSKS(const char matakuliah[]) {
    for (int i = 0; i < matakuliahCount; i++) {
        if (strcmp(matakuliahData[i].matakuliah, matakuliah) == 0) {
            return matakuliahData[i].sks;
        }
    }
    return 0;
}

// Function to populate sample data for testing
void populateSampleData() {
    // Add sample students and their accounts
    addMahasiswa("2350081084", "Alice", "A1", "alice@example.com", "L", 1);
    addAkunMahasiswa("2350081084", "password123");
    addMahasiswa("23456789012345", "Bob", "A2", "bob@example.com", "P", 2);
    addAkunMahasiswa("23456789012345", "password234");

    // Add sample courses
    addMatakuliah("Mathematics", 3);
    addMatakuliah("Physics", 4);

    // Add sample academic records
    addAkademik("2350081084", 1, "Mathematics", "2023/2024", 80, 75, 85);
    addAkademik("2350081084", 1, "Physics", "2023/2024", 70, 65, 75);
    addAkademik("2350081084", 2, "Mathematics", "2023/2024", 90, 85, 95);
}

int main() {
    populateSampleData();

    int choice;
    do {
        printf("Menu Utama:\n1. Registrasi Mahasiswa\n2. Login\n3. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left in buffer

        switch (choice) {
            case 1:
                registerMahasiswa();
                break;
            case 2:
                login();
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
