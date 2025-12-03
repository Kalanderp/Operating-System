#include <stdio.h>
#include <string.h>

struct directory {
    char dname[20];
    char fname[20][20];
    int fcount;
} dir;

int main() {
    int choice;
    char file[20];

    // Initialize directory name
    strcpy(dir.dname, "main_directory");
    dir.fcount = 0;

    while (1) {
        printf("\n--- Single Level Directory ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. List Files\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1: {
            printf("Enter file name: ");
            scanf("%s", file);

            int exists = 0;
            for (int i = 0; i < dir.fcount; i++) {
                if (strcmp(file, dir.fname[i]) == 0) {
                    exists = 1;
                    break;
                }
            }

            if (exists) {
                printf("File already exists!\n");
            } else {
                strcpy(dir.fname[dir.fcount], file);
                dir.fcount++;
                printf("File created successfully.\n");
            }
            break;
        }

        case 2: {
            printf("Enter file name to delete: ");
            scanf("%s", file);

            int found = -1;
            for (int i = 0; i < dir.fcount; i++) {
                if (strcmp(file, dir.fname[i]) == 0) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                for (int i = found; i < dir.fcount - 1; i++) {
                    strcpy(dir.fname[i], dir.fname[i + 1]);
                }
                dir.fcount--;
                printf("File deleted successfully.\n");
            } else {
                printf("File not found.\n");
            }
            break;
        }

        case 3: {
            printf("Enter file name to search: ");
            scanf("%s", file);

            int search = 0;
            for (int i = 0; i < dir.fcount; i++) {
                if (strcmp(file, dir.fname[i]) == 0) {
                    search = 1;
                    break;
                }
            }

            if (search)
                printf("File found!\n");
            else
                printf("File not found.\n");

            break;
        }

        case 4:
            printf("\nDirectory Name: %s\n", dir.dname);
            printf("Files:\n");
            if (dir.fcount == 0)
                printf("  No files.\n");
            else
                for (int i = 0; i < dir.fcount; i++)
                    printf("  %s\n", dir.fname[i]);
            break;

        case 5:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}

