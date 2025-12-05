#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
    char department[30];
};

void add_employee(FILE *fp) {
    struct Employee emp;
    
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter name: ");
    scanf("%s", emp.name);
    printf("Enter salary: ");
    scanf("%f", &emp.salary);
    printf("Enter department: ");
    scanf("%s", emp.department);
    
    // Move to position based on ID (random access)
    fseek(fp, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, fp);
    
    printf("Employee added successfully!\n");
}

void display_employee(FILE *fp) {
    int id;
    struct Employee emp;
    
    printf("Enter employee ID to display: ");
    scanf("%d", &id);
    
    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    
    if(fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
        if(emp.id != 0) {
            printf("\nEmployee Details:\n");
            printf("ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Salary: %.2f\n", emp.salary);
            printf("Department: %s\n", emp.department);
        } else {
            printf("Employee not found!\n");
        }
    } else {
        printf("Error reading record!\n");
    }
}

void update_employee(FILE *fp) {
    int id;
    struct Employee emp;
    
    printf("Enter employee ID to update: ");
    scanf("%d", &id);
    
    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    
    if(fread(&emp, sizeof(struct Employee), 1, fp) == 1 && emp.id != 0) {
        printf("Current details:\n");
        printf("Name: %s\n", emp.name);
        printf("Salary: %.2f\n", emp.salary);
        printf("Department: %s\n", emp.department);
        
        printf("\nEnter new name: ");
        scanf("%s", emp.name);
        printf("Enter new salary: ");
        scanf("%f", &emp.salary);
        printf("Enter new department: ");
        scanf("%s", emp.department);
        
        fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
        fwrite(&emp, sizeof(struct Employee), 1, fp);
        
        printf("Employee updated successfully!\n");
    } else {
        printf("Employee not found!\n");
    }
}

void display_all(FILE *fp) {
    struct Employee emp;
    
    printf("\nAll Employee Records:\n");
    printf("ID\tName\t\tSalary\t\tDepartment\n");
    
    fseek(fp, 0, SEEK_SET);
    
    for(int i = 0; i < 100; i++) {
        if(fread(&emp, sizeof(struct Employee), 1, fp) == 1 && emp.id != 0) {
            printf("%d\t%-15s\t%.2f\t\t%s\n", 
                   emp.id, emp.name, emp.salary, emp.department);
        }
    }
}

int main() {
    FILE *fp;
    int choice;
    
    // Open file in binary mode for random access
    fp = fopen("employees.dat", "rb+");
    
    // If file doesn't exist, create it
    if(fp == NULL) {
        fp = fopen("employees.dat", "wb+");
        if(fp == NULL) {
            printf("Error creating file!\n");
            return 1;
        }
    }
    
    // Initialize all records with ID=0
    struct Employee emp = {0, "", 0.0, ""};
    for(int i = 0; i < 100; i++) {
        fwrite(&emp, sizeof(struct Employee), 1, fp);
    }
    
    while(1) {
        printf("\n1. Add Employee\n2. Display Employee\n3. Update Employee\n4. Display All\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: add_employee(fp); break;
            case 2: display_employee(fp); break;
            case 3: update_employee(fp); break;
            case 4: display_all(fp); break;
            case 5: 
                fclose(fp);
                return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
