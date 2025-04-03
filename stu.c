#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

// 定义学生结构体
typedef struct {
    char name[NAME_LENGTH];
    int id;
    float scores[3];  // 假设三门课程成绩
    float average;
} Student;

// 全局变量，存储学生信息
Student students[MAX_STUDENTS];
int studentCount = 0;

// 函数声明
void addStudent();
void displayStudents();
void calculateAverage();
void findStudent();
void saveToFile();
void loadFromFile();

// 添加学生信息
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("学生数量已达到最大值，无法添加更多学生。\n");
        return;
    }

    Student newStudent;
    printf("请输入学生姓名: ");
    scanf("%s", newStudent.name);
    printf("请输入学生 ID: ");
    scanf("%d", &newStudent.id);
    printf("请输入三门课程的成绩: ");
    for (int i = 0; i < 3; i++) {
        scanf("%f", &newStudent.scores[i]);
    }

    students[studentCount++] = newStudent;
    printf("学生信息添加成功！\n");
}

// 显示所有学生信息
void displayStudents() {
    if (studentCount == 0) {
        printf("没有学生信息。\n");
        return;
    }

    printf("姓名\tID\t课程 1 成绩\t课程 2 成绩\t课程 3 成绩\t平均成绩\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%s\t%d\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",
               students[i].name, students[i].id, students[i].scores[0],
               students[i].scores[1], students[i].scores[2], students[i].average);
    }
}

// 计算每个学生的平均成绩
void calculateAverage() {
    for (int i = 0; i < studentCount; i++) {
        float sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += students[i].scores[j];
        }
        students[i].average = sum / 3;
    }
    printf("平均成绩计算完成！\n");
}

// 根据姓名查找学生信息
void findStudent() {
    char name[NAME_LENGTH];
    printf("请输入要查找的学生姓名: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("姓名: %s\n", students[i].name);
            printf("ID: %d\n", students[i].id);
            printf("课程 1 成绩: %.2f\n", students[i].scores[0]);
            printf("课程 2 成绩: %.2f\n", students[i].scores[1]);
            printf("课程 3 成绩: %.2f\n", students[i].scores[2]);
            printf("平均成绩: %.2f\n", students[i].average);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到该学生信息。\n");
    }
}

// 将学生信息保存到文件
void saveToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %d %.2f %.2f %.2f %.2f\n",
                students[i].name, students[i].id, students[i].scores[0],
                students[i].scores[1], students[i].scores[2], students[i].average);
    }

    fclose(file);
    printf("学生信息保存成功！\n");
}

// 从文件中加载学生信息
void loadFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    studentCount = 0;
    while (studentCount < MAX_STUDENTS && fscanf(file, "%s %d %f %f %f %f",
                                                students[studentCount].name,
                                                &students[studentCount].id,
                                                &students[studentCount].scores[0],
                                                &students[studentCount].scores[1],
                                                &students[studentCount].scores[2],
                                                &students[studentCount].average) != EOF) {
        studentCount++;
    }

    fclose(file);
    printf("学生信息加载成功！\n");
}

// 主函数，显示菜单并处理用户输入
int main() {
    int choice;
    do {
        printf("\n学生成绩管理系统\n");
        printf("1. 添加学生信息\n");
        printf("2. 显示所有学生信息\n");
        printf("3. 计算平均成绩\n");
        printf("4. 查找学生信息\n");
        printf("5. 保存学生信息到文件\n");
        printf("6. 从文件中加载学生信息\n");
        printf("0. 退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                calculateAverage();
                break;
            case 4:
                findStudent();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                loadFromFile();
                break;
            case 0:
                printf("退出系统。\n");
                break;
            default:
                printf("无效的选择，请重新输入。\n");
        }
    } while (choice != 0);

    return 0;
}