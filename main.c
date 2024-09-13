#include <stdio.h>
#include <stdlib.h>

struct student {
    char name[50];
    char Class[100];
    int roll_number;
    float *marks;
    float percentage;
};

void calculate_percentage(struct student *s, int num_subjects);
void save_to_file(struct student *s, int num_students, int num_subjects, const char *filename);

int main() {
    int num_students, num_subjects;

    // Asking for number of students and subjects
    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    printf("Enter the number of subjects: ");
    scanf("%d", &num_subjects);

    struct student s[num_students];

    // Allocate memory for marks dynamically based on number of subjects
    for (int i = 0; i < num_students; i++) {
        s[i].marks = (float *)malloc(num_subjects * sizeof(float));
    }

    // Input details for each student
    for (int i = 0; i < num_students; i++) {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter name: ");
        scanf("%s", s[i].name);

        printf("Enter roll no: ");
        scanf("%d", &s[i].roll_number);

        printf("Enter class: ");
        scanf("%s", s[i].Class);

        float total_marks = 0;

        for (int j = 0; j < num_subjects; j++) {
            printf("Enter the marks in subject %d (out of 100): ", j + 1);
            scanf("%f", &s[i].marks[j]);
            total_marks += s[i].marks[j];
        }

        // Calculate percentage for the student
        s[i].percentage = total_marks / num_subjects;
        printf("\n");
    }

    // Display the student information with percentage
    printf("\nName\t\tRoll no\t\tClass\t\tMarks\t\tPercentage\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < num_students; i++) {
        printf("%s\t\t%d\t\t%s\t\t", s[i].name, s[i].roll_number, s[i].Class);
        for (int j = 0; j < num_subjects; j++) {
            printf("%.2f\t", s[i].marks[j]);
        }
        printf("%.2f%%\n", s[i].percentage); // Display the percentage
    }

    // Save the student details to a text file
    save_to_file(s, num_students, num_subjects, "student_records.txt");

    // Free dynamically allocated memory for marks
    for (int i = 0; i < num_students; i++) {
        free(s[i].marks);
    }

    return 0;
}

// Function to save student data to a file
void save_to_file(struct student *s, int num_students, int num_subjects, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "Name\tRoll No\tClass\tMarks\t\tPercentage\n");
    fprintf(file, "-------------------------------------------------------------\n");

    for (int i = 0; i < num_students; i++) {
        fprintf(file, "%s\t%d\t%s\t", s[i].name, s[i].roll_number, s[i].Class);
        for (int j = 0; j < num_subjects; j++) {
            fprintf(file, "%.2f\t", s[i].marks[j]);
        }
        fprintf(file, "%.2f%%\n", s[i].percentage);
    }

    fclose(file);
    printf("Student information saved to %s\n", filename);
}
