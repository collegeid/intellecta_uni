#include "base.h"

// Global variables to store data
Mahasiswa *mahasiswaData = NULL;
AkunMahasiswa *akunMahasiswaData = NULL;
Akademik *akademikData = NULL;
Matakuliah *matakuliahData = NULL;
int mahasiswaCount = 0;
int akunCount = 0;
int akademikCount = 0;
int matakuliahCount = 0;



//function untuk populate data
void addAkademik(const char NIM[], int semester, const char matakuliah[], const char tahunAkademik[], float nilaiTugas, float nilaiUTS, float nilaiUAS);
void addMatakuliah(const char matakuliah[], int sks);


// Function prototypes
void addMahasiswa(const char NIM[], const char nama[], const char kelas[], const char email[], const char gender[], int semester);
void addAkunMahasiswa(const char NIM[], const char password[]);
bool checkNIM(const char NIM[]);
bool checkLogin(const char NIM[], const char password[]);
void registerMahasiswa();
void login();
void checkProfile(const char NIM[]);
void displayAkademik(const char NIM[]);
float calculateIP(const char NIM[], int semester);
float calculateIPK(const char NIM[]);
char calculateGrade(float finalGrade);
float GradeToIP(const char grade);


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
    } while (strcmp(gender, "") == 0 || strcmp(gender, "\n") == 0 || strlen(gender) > MAX_GENDER_LENGTH || (strcmp(gender, "L") != 0 && strcmp(gender, "P") != 0));

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
    } else {

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
}

// Function to check profile
void checkProfile(const char NIM[]) {
    for (int i = 0; i < mahasiswaCount; i++) {
        if (strcmp(mahasiswaData[i].NIM, NIM) == 0) {
            printf("------------------------------------------------------------\n");
            printf("======================= Data Diri Anda =====================\n");
            printf("------------------------------------------------------------\n");
            printf("NIM      : %s\n", mahasiswaData[i].NIM);
            printf("Nama     : %s\n", mahasiswaData[i].nama);
            printf("Kelas    : %s\n", mahasiswaData[i].kelas);
            printf("Email    : %s\n", mahasiswaData[i].email);
            printf("Gender   : %s\n", mahasiswaData[i].gender);
            printf("Semester : %d\n", mahasiswaData[i].semester);
            printf("------------------------------------------------------------\n");
            return;
        }
    }
    printf("Profil tidak ditemukan.\n");
}




void displayAkademik(const char NIM[]) {
    printf("--------------------------------------------------------------------------------------------\n");
    printf("======================================= Rekam Akademik =====================================\n");
    printf("--------------------------------------------------------------------------------------------\n");
    
    int currentSemester = -1;
    
    for (int i = 0; i < akademikCount; i++) {
        if (strcmp(akademikData[i].NIM, NIM) == 0) {
            if (currentSemester != akademikData[i].semester) {
                if (currentSemester != -1) {
                    float semesterIP = calculateIP(NIM, currentSemester);
                    printf("--------------------------------------------------------------------------------------------\n");
                    printf("===================================== IP Semester %d: %.2f ==================================\n", currentSemester, semesterIP);
                    printf("--------------------------------------------------------------------------------------------\n");
                }
                currentSemester = akademikData[i].semester;
                printf("========================================= Semester %d =======================================\n", currentSemester);
                printf("--------------------------------------------------------------------------------------------\n");
                printf("| %-30s | %-5s | %-15s | %-5s | %-5s | %-5s | %-5s |\n", "Matakuliah", "SKS", "Tahun Akademik", "Tugas", "UTS", "UAS", "Grade");
                printf("--------------------------------------------------------------------------------------------\n");
            }

            int sks = getSKS(akademikData[i].matakuliah);
            printf("| %-30s | %-5d | %-15s | %-5.2f | %-5.2f | %-5.2f | %-5c |\n", akademikData[i].matakuliah, sks, akademikData[i].tahunAkademik, akademikData[i].nilaiTugas, akademikData[i].nilaiUTS, akademikData[i].nilaiUAS, akademikData[i].grade);
        }
    }
    
    if (currentSemester != -1) {
        float semesterIP = calculateIP(NIM, currentSemester);
        printf("--------------------------------------------------------------------------------------------\n");
        printf("===================================== IP Semester %d: %.2f ==================================\n", currentSemester, semesterIP);
        printf("--------------------------------------------------------------------------------------------\n");
    }
    
    // Display IPK (Cumulative GPA)
    float IPK = calculateIPK(NIM);
    printf("--------------------------------------------------------------------------------------------\n");
    printf("========================================== IPK: %.2f =======================================\n", IPK);
    printf("--------------------------------------------------------------------------------------------\n");
}




// Function to calculate IPK (Cumulative GPA)
float calculateIPK2(const char NIM[]) {
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

// Function to calculate IP (GPA) for a given semester
float calculateIP(const char NIM[], int semester) {
    float totalSKS = 0;
    float totalNilai = 0;

   // printf("Calculating IP for NIM: %s, Semester: %d\n", NIM, semester);

    for (int i = 0; i < akademikCount; i++) {
        if (strcmp(akademikData[i].NIM, NIM) == 0 && akademikData[i].semester == semester) {
            int sks = getSKS(akademikData[i].matakuliah);
            float gradePoint = GradeToIP(akademikData[i].grade);
            totalSKS += sks;
            totalNilai += (gradePoint * sks);

         //   printf("Course: %s, SKS: %d, Grade: %c, Grade Point: %.2f\n", akademikData[i].matakuliah, sks, akademikData[i].grade, gradePoint);
          //  printf("Current Total SKS: %.2f, Current Total Nilai: %.2f\n", totalSKS, totalNilai);
        }
    }

    if (totalSKS == 0) return 0;

    float result = totalNilai / totalSKS;
    // printf("Final Total SKS: %.2f, Final Total Nilai: %.2f, IP: %.2f\n", totalSKS, totalNilai, result);

    return result;
}
// Function to calculate cumulative IPK (Cumulative GPA)



// Function to calculate cumulative IPK (Cumulative GPA)
float calculateIPK(const char NIM[]) {
    float totalIP = 0; // Total IP for all semesters
    int totalSemesters = 0; // Total number of semesters
    int maxSemesters = 14; // Assuming a maximum of 14 semesters

    for (int semester = 1; semester <= maxSemesters; semester++) {
        float semesterIP = calculateIP(NIM, semester);
        if (semesterIP > 0) { // Only count semesters with valid IP
            totalIP += semesterIP;
            totalSemesters++;
        }
    }

    if (totalSemesters == 0) return 0;

    float IPK = totalIP / totalSemesters;
   // printf("Final IPK for NIM %s: %.2f\n", NIM, IPK);

    return IPK;
}



// Function to calculate grade based on final grade
char calculateGrade(float finalGrade) {
    if (finalGrade >= 85) return 'A';
    if (finalGrade >= 70) return 'B';
    if (finalGrade >= 55) return 'C';
    if (finalGrade >= 40) return 'D';
    return 'E';
}

// Function to calculate grade based on final grade
float GradeToIP(char Grade) {
   if (Grade == 'A') return 4.00;
   if (Grade == 'B') return 3.00; 
   if (Grade == 'C') return 2.00; 
   if (Grade == 'D') return 1.00;
    return 0.00;
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

int main_mahasiswa() {
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
