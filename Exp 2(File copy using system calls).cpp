#include <stdio.h>

int main() {
    FILE *src, *dest;
    char sourceFile[100], destFile[100];
    char buffer[1024];
    size_t bytes;

    printf("Enter source file name: ");
    scanf("%s", sourceFile);

    printf("Enter destination file name: ");
    scanf("%s", destFile);

    src = fopen(sourceFile, "rb");
    if (src == NULL) {
        printf("Cannot open source file\n");
        return 1;
    }

    dest = fopen(destFile, "wb");
    if (dest == NULL) {
        printf("Cannot create/open destination file\n");
        fclose(src);
        return 1;
    }

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
    return 0;
}

