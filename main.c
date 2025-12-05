#include <stdio.h>
#define MAX 100

typedef struct {
    int id;
    char name[100];
    float grade;
} Student;

typedef struct {
Student data[MAX];
int n;
} StudentTab;

void CreateArchiveStudent(StudentTab *student);
void printGraduates(StudentTab students);
void BacaArchive(StudentTab *student);
void MenghitungRataRata(StudentTab *students);


void CreateArchiveStudent(StudentTab *student) {
    Student aStudent;
    FILE *StudentFile;

    student->n = 0;

    StudentFile = fopen("Student.csv", "w");
    if (!StudentFile) {
        printf("File error!\n"); return;
    }
    printf("input Student ID =");
    scanf("%d", &aStudent.id);

    while (aStudent.id !=9999) {
        printf ("Name : ");
        scanf("%s", aStudent.name);

        printf ("Grade : ");
        scanf("%f", &aStudent.grade);

        fprintf(StudentFile, "%d,%s,%.2f\n",
            aStudent.id, aStudent.name, aStudent.grade);

        student->data[student->n] = aStudent;
        student->n++;

        printf("input Student ID =");
        scanf("%d", &aStudent.id);
    }
    fclose(StudentFile);
}
void printGraduates(StudentTab students) {
    printf("\nThe Graduates :\n");
    for (int i = 0; i < students.n; i++) {
        if (students.data[i].grade >= 85) {
            printf("ID: %d\n", students.data[i].id);
            printf("Name: %s\n", students.data[i].name);
            printf("Grade: %.2f\n\n", students.data[i].grade);
        }
    }
}
void BacaArchive(StudentTab *Student) {
    printf("\n=== Lihat Data Mahasiswa ===\n");

    for (int i = 0; i < Student->n; i++) {
        printf("Student-%d:\n", i + 1);
        printf("ID: %d\n", Student->data[i].id);
        printf("Name: %s\n", Student->data[i].name);
        printf("Grade: %.2f\n", Student->data[i].grade);
    }
}

void MenghitungRataRata(StudentTab *Student) {

    printf("\n=== Hitung Rata-rata Grade Mahasiswa ===\n");

    if (Student->n == 0) {
        printf("Tidak ada data mahasiswa!\n");
        return;
    }

    float totalGrade = 0;

    for (int i = 0; i < Student->n; i++) {
        totalGrade += Student->data[i].grade;
    }

    float rata = totalGrade / Student->n;

    printf("Rata-rata Grada %d Mahasiswa adalah : %.2f\n",
        Student->n, rata);
}
int main() {
    int pilihan;

    StudentTab dataMahasiswa;
    do {
        printf("\n==== PROGRAM DATA MAHASISWA ====\n");
        printf("1. CreateArchive Student\n");
        printf("2. Baca Archive\n");
        printf("3. MenghitungRataRata\n");
        printf("4. Exit\n");
        printf("pilih 1 - 4 : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: CreateArchiveStudent(&dataMahasiswa); break;
            case 2: BacaArchive(&dataMahasiswa); break;
            case 3: MenghitungRataRata(&dataMahasiswa);
            case 4: printf("keluar dari Program..\n"); break;
            default: printf("pilihan tidak valid!\n");
        }
    }while (pilihan != 3);

    return 0;
}