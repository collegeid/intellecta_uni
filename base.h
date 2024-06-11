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
