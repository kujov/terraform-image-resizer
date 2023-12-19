//DISCLAIMER: This code is probably the worst code you've seen. It was coded in a few minutes ;)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void startInfrastructure() {
    printf("Starting infrastructure...\n");
    system("terraform init");
    system("terraform apply -auto-approve");

    FILE *fp = popen("terraform output -raw first_bucket_name", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error executing Terraform output command\n");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);

    pclose(fp);

    strtok(buffer, "\n");

    setenv("FIRST_BUCKET_NAME", buffer, 1);

    FILE *envFile = fopen(".kenin", "w");
    if (envFile != NULL) {
        fprintf(envFile, "FIRST_BUCKET_NAME=%s\n", getenv("FIRST_BUCKET_NAME"));
        fclose(envFile);
    } else {
        fprintf(stderr, "Error creating .kenin file\n");
    }

    printf("Infrastructure is up and running...\n");
}

void stopInfrastructure() {
    printf("Stopping infrastructure...\n");
    system("terraform destroy -auto-approve");
    system("clear");
    printf("infrastructure has been successfully destroyed...\n");
}

void flushStdin();

void uploadImage() {
    printf("Uploading Image...\n");

    FILE *envFile = fopen(".kenin", "r");
    if (envFile != NULL) {
        char buffer[1024];

        if (fgets(buffer, sizeof(buffer), envFile) != NULL) {
            char *value = strchr(buffer, '=');
            if (value != NULL) {
                value++;
                strtok(value, "\n");

                printf("Enter the file path to upload: ");
                flushStdin();  // Flush stdinput buffer or somehow it doesnt work lol
                fgets(buffer, sizeof(buffer), stdin);
                strtok(buffer, "\n");

                FILE *file = fopen(buffer, "r");
                if (file != NULL) {
                    fclose(file);

                    char command[2048];
                    snprintf(command, sizeof(command), "aws s3 cp \"%s\" s3://%s/", buffer, value);

                    int result = system(command);

                    if (result == 0) {
                        printf("File uploaded successfully to S3 bucket: %s\n", value);
                    } else {
                        fprintf(stderr, "Error uploading file to S3\n");
                    }
                } else {
                    fprintf(stderr, "File does not exist: %s\n", buffer);
                }
            }
        }

        fclose(envFile);
    } else {
        fprintf(stderr, "Error opening .kenin file\n");
    }
}

void flushStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void handleUnknownCommand(const char *commandName) {
    printf("Error! Unknown command: %s\n", commandName);
}

void performInfrastructureAction(const char *commandName) {
    if (strcmp(commandName, "start") == 0) {
        startInfrastructure();
    } else if (strcmp(commandName, "stop") == 0) {
        stopInfrastructure();
    } else if (strcmp(commandName, "upload") == 0) {
        uploadImage();
    } else {
        handleUnknownCommand(commandName);
    }
}

int main(void) {
    char commandName[20];

    printf("Enter the infrastructure service action: ");

    if (scanf("%19s", commandName) != 1) {
        printf("Error reading input.\n");
        return 1;
    }

    performInfrastructureAction(commandName);

    return 0;
}
