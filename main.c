#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *get_filename(const char *path)
{
    const char *filename = strrchr(path, '/');
    if (filename == NULL)
    {
        filename = strrchr(path, '\\');
    }
    if (filename == NULL)
    {
        filename = path;
    }
    else
    {
        filename++; // remove this character from the path: '/' , '\\'
    }
    return filename;
}

int main(int argc, char *argv[])
{

    if (strcmp(argv[1], "-f") == 0)
    {
        if (strcmp(argv[3], "-new") == 0)
        {
            // printf(get_filename(argv[0]));
            FILE *file = fopen(argv[2], "w"); // w = to write but delete the files before.
            if (file == NULL)
            {
                printf("Fail to open the file %s\n", argv[2]);

                return -3;
            }
            fclose(file);
            printf("File is created %s\n", argv[2]);
            return 0;
        }
        else if (strcmp(argv[3], "-newentry") == 0)
        {
            char *name = argv[4];
            char *phone = argv[5];

            int found = 0;
            char line[100];
            FILE *file = fopen(argv[2], "r");
            if (file == NULL)
            {
                printf("Failed to open the file %s\n", argv[2]);
                return -4;
            }

            while (fgets(line, sizeof(line), file) != NULL)
            {
                char oldname[100];
                char oldphone[100];
                if (sscanf(line, "Name: %99[^,], Phone: %99s", oldname, oldphone) == 2)
                {
                    if (strcmp(oldname, name) == 0 && strcmp(oldphone, phone) == 0)
                    {
                        printf("Entry already exists in the file.\n");
                        found = 1;
                        return -1;
                    }
                }
            }

            fclose(file);

            if (found != 1)
            {
                file = fopen(argv[2], "a"); // the record go in the bottom
                if (file == NULL)
                {
                    printf("Failed to open the file %s\n", get_filename(argv[0]));
                    return -3;
                }

                fprintf(file, "Name: %s, Phone: %s\n", name, phone);
                printf("The record Inserted Successfully\n");
                fclose(file);
            }
            return 0;
        }
        else if (strcmp(argv[3], "-showentry") == 0)
        {
            char *name = argv[4];
            // char *phone = argv[5];
            int found = 0;
            FILE *file = fopen(argv[2], "r");
            if (file == NULL)
            {
                printf("Failed to open the file %s\n", argv[2]);
                return -3;
            }

            char line[100];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                char oldname[100];
                if (sscanf(line, "Name: %99[^,]", oldname) == 1)
                {
                    if (strcmp(oldname, name) == 0)
                    {
                        printf("%s", line);
                        found = 1;
                        return 0;
                    }
                }
            }
            fclose(file);
            if (found != 1)
            {
                printf("Entry not found.\n");
                return -2;
            }
        }
        else if (strcmp(argv[3], "-changeentry") == 0)
        {
            char *name = argv[4];
            char *phone = argv[5];
            int found = 0;
            FILE *file = fopen(argv[2], "r+");
            if (file == NULL)
            {
                printf("Failed to open the file %s\n", argv[2]);
                return -3;
            }

            char line[100];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                char oldname[100];
                char oldphone[100];
                char *new_phone = argv[5];
                if (sscanf(line, "Name: %99[^,], Phone: %99s", oldname, oldphone) == 2)
                {
                    if (strcmp(oldname, name) == 0)
                    {
                        fseek(file, -strlen(line), SEEK_CUR);
                        fprintf(file, "Name: %s, Phone: %s\n", name, new_phone);
                        found = 1;
                        printf("Record updated successfully.\n");
                        return 0;
                    }
                }
            }
            fclose(file);
            if (found != 1)
            {
                printf("Entry Not Found.\n");
                return -2;
            }
        }
        else if (strcmp(argv[3], "-deleteentry") == 0)
        {

            char *nameToDelete = argv[4];
            char line[100];
            int found = 0;
            // int *delete = 0;
            FILE *file = fopen(argv[2], "r");
            if (file == NULL)
            {
                printf("Failed to open the file %s\n", argv[2]);
                return -3;
            }

            FILE *temp = fopen("temp.txt", "w");
            if (temp == NULL)
            {
                printf("Failed to open the file temp file\n");
                return -3;
            }

            while (fgets(line, sizeof(line), file) != NULL)
            {
                if (strstr(line, nameToDelete) != NULL)
                {
                    found = 1;
                }
                else
                {
                    fputs(line, temp);
                }
            }

            fclose(file);
            fclose(temp);
            // printf(argv[2]);

            if (remove(argv[2]) != 0)
            {
                printf("Failed to delete the input file.\n");
                return -4;
            }

            if (rename("temp.txt", argv[2]) != 0)
            {
                printf("Failed to rename the temporary file.\n");
                return -4;
            }
            if (found = 1)
            {
                printf("Contact deleted successfully.\n");
                return 0;
            }
            else
            {
                printf("Contact not Found.\n");
                return -1;
            }
        }
        else if (strcmp(argv[3], "-deleteentries") == 0)
        {

            FILE *file = fopen(argv[2], "w");
            if (file == NULL)
            {
                printf("Failed to open the file %s\n", argv[2]);
                return -3;
            }
            else
            {
                printf("All records deleted from the file %s\n", argv[2]);
                return 0;
            }
        }
        else if (strcmp(argv[3], "-showentries") == 0)
        {
            char ch;
            FILE *file = fopen(argv[2], "r");
            if (file == NULL)
            {
                printf("Failed to open the file %s\n", argv[2]);
                return -3;
            }

            while ((ch = fgetc(file)) != EOF) // EOF = END OF FILE
            {
                printf("%c", ch);
            }

            fclose(file);
            return 0;
        }
        else
        {
            printf("Use correct format\n");
            printf("If you want help type ./%s -h\n", get_filename(argv[0]));
            return -3;
        }
    }
    else if ((strcmp(argv[1], "-h") == 0))
    {
        printf("The Commands are:\n ");
        printf(" -f 'filename' -new //Create the file\n");
        printf(" -f 'filename' -newentry 'Name' 'Phone' //Make the Record\n");
        printf(" -f 'filename' -showentry 'Name' //Display The entry with this name\n");
        printf(" -f 'filename' -changeentry 'Name' 'New Phone' //Change the record\n");
        printf(" -f 'filename' -deleteentry 'Name' //Delete the Entry with this name\n");
        printf(" -f 'filename' -deleteentrie  //Delete all the Entries\n");
        printf(" -f 'filename' -showentries  //Display all the entries\n");
    }
}
