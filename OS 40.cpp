#include <stdio.h>
#include <string.h>

void displayPermissionTable() {
    printf("\n=== PERMISSION REFERENCE TABLE ===\n");
    printf("Symbol\tMeaning\t\tOctal\tBinary\n");
    printf("------\t-------\t\t-----\t------\n");
    printf("r\tRead\t\t4\t100\n");
    printf("w\tWrite\t\t2\t010\n");
    printf("x\tExecute\t\t1\t001\n");
    printf("\nCombinations:\n");
    printf("rwx\tRead+Write+Execute\t7\t111\n");
    printf("rw-\tRead+Write\t\t6\t110\n");
    printf("r-x\tRead+Execute\t\t5\t101\n");
    printf("r--\tRead only\t\t4\t100\n");
    printf("-wx\tWrite+Execute\t\t3\t011\n");
    printf("-w-\tWrite only\t\t2\t010\n");
    printf("--x\tExecute only\t\t1\t001\n");
    printf("---\tNo permission\t\t0\t000\n");
}

void calculatePermissions() {
    char user[4], group[4], others[4];
    int u_perm = 0, g_perm = 0, o_perm = 0;
    
    printf("\nEnter User permissions (e.g., rwx or r-x): ");
    scanf("%s", user);
    printf("Enter Group permissions: ");
    scanf("%s", group);
    printf("Enter Others permissions: ");
    scanf("%s", others);
    
    // Calculate user permissions
    if(strchr(user, 'r')) u_perm += 4;
    if(strchr(user, 'w')) u_perm += 2;
    if(strchr(user, 'x')) u_perm += 1;
    
    // Calculate group permissions
    if(strchr(group, 'r')) g_perm += 4;
    if(strchr(group, 'w')) g_perm += 2;
    if(strchr(group, 'x')) g_perm += 1;
    
    // Calculate others permissions
    if(strchr(others, 'r')) o_perm += 4;
    if(strchr(others, 'w')) o_perm += 2;
    if(strchr(others, 'x')) o_perm += 1;
    
    printf("\n=== CALCULATED PERMISSIONS ===\n");
    printf("Symbolic: -%s%s%s\n", user, group, others);
    printf("Octal: %d%d%d\n", u_perm, g_perm, o_perm);
    printf("Binary: ");
    
    // Display binary
    for(int i = 2; i >= 0; i--) 
        printf("%d", (u_perm >> i) & 1);
    for(int i = 2; i >= 0; i--) 
        printf("%d", (g_perm >> i) & 1);
    for(int i = 2; i >= 0; i--) 
        printf("%d", (o_perm >> i) & 1);
    printf("\n");
}

int main() {
    int choice;
    
    printf("===== LINUX FILE PERMISSION DEMONSTRATION =====\n");
    
    while(1) {
        printf("\n=== MENU ===\n");
        printf("1. View Permission Reference Table\n");
        printf("2. Calculate Permissions\n");
        printf("3. Understanding User Types\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                displayPermissionTable();
                break;
                
            case 2:
                calculatePermissions();
                break;
                
            case 3:
                printf("\n=== LINUX USER TYPES ===\n");
                printf("\n1. ROOT USER (UID 0):\n");
                printf("   - Superuser/Administrator\n");
                printf("   - Can do ANYTHING on system\n");
                printf("   - Bypasses all permission checks\n");
                printf("   - Can access/modify any file\n");
                
                printf("\n2. SYSTEM USERS (UID 1-999):\n");
                printf("   - Used by system services/daemons\n");
                printf("   - e.g., www-data, mysql, daemon\n");
                printf("   - Have limited privileges\n");
                printf("   - Cannot login interactively\n");
                
                printf("\n3. REGULAR USERS (UID 1000+):\n");
                printf("   - Normal human users\n");
                printf("   - Limited to their own files\n");
                printf("   - Must use 'sudo' for admin tasks\n");
                printf("   - Home directory: /home/username\n");
                
                printf("\n4. GROUPS:\n");
                printf("   - Collection of users\n");
                printf("   - File permissions can be set for groups\n");
                printf("   - Common groups: sudo, users, admin, wheel\n");
                printf("   - A user can belong to multiple groups\n");
                break;
                
            case 4:
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
