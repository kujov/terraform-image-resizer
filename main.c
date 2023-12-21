#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define COMMAND_SIZE 2048

void executeSystemCommand(const char *command) {
    if (system(command) != 0) {
        fprintf(stderr, "Error executing command: %s\n", command);
    }
}

FILE* openFile(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
    }
    return file;
}

void flushStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void setEnvironmentVariable(const char *varName, const char *value) {
    setenv(varName, value, 1);

    FILE *envFile = openFile(".kenin", "w");
    if (envFile != NULL) {
        fprintf(envFile, "%s=%s\n", varName, value);
        fclose(envFile);
    }
}

void startInfrastructure() {
    printf("Starting infrastructure...\n");
    executeSystemCommand("terraform init");
    executeSystemCommand("terraform apply -auto-approve");

    FILE *fp = popen("terraform output -raw first_bucket_name", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    fgets(buffer, sizeof(buffer), fp);
    pclose(fp);

    strtok(buffer, "\n");
    setEnvironmentVariable("FIRST_BUCKET_NAME", buffer);

    printf("Infrastructure is up and running...\n");
}

void stopInfrastructure() {
    printf("Stopping infrastructure...\n");
    executeSystemCommand("terraform destroy -auto-approve");
    executeSystemCommand("clear");
    printf("Infrastructure has been successfully destroyed...\n");
}

void uploadImage() {
    printf("Uploading Image...\n");

    FILE *envFile = openFile(".kenin", "r");
    if (envFile != NULL) {
        char buffer[BUFFER_SIZE];

        if (fgets(buffer, sizeof(buffer), envFile) != NULL) {
            char *bucketName = strchr(buffer, '=');
            if (bucketName != NULL) {
                bucketName++;
                strtok(bucketName, "\n");

                printf("Enter the file path to upload: ");
                flushStdin();
                fgets(buffer, sizeof(buffer), stdin);
                strtok(buffer, "\n");

                char command[COMMAND_SIZE];
                snprintf(command, sizeof(command), "aws s3 cp \"%s\" s3://%s/", buffer, bucketName);
                executeSystemCommand(command);
            }
        }
        fclose(envFile);
    }
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

        printf("\nWelcome to the Infrastructure Management System\n");
    printf("-------------------------------------------------\n");
    printf("Please select an action by entering the command name:\n");
    printf("  start  - Start the infrastructure\n");
    printf("  stop   - Stop the infrastructure\n");
    printf("  upload - Upload an image to the infrastructure\n");
    printf("-------------------------------------------------\n");
    printf("Enter your choice: ");

    if (scanf("%19s", commandName) != 1) {
        printf("Error reading input.\n");
        return 1;
    }
    
    performInfrastructureAction(commandName);

    return 0;
}
