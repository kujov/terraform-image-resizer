#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void startInfrastructure() {
    printf("Starting infrastructure...\n");
    system("terraform init");
    system("terraform apply -auto-approve");
    system("clear");
    printf("infrastructure is up and running...\n");
}

void stopInfrastructure() {
    printf("Stopping infrastructure...\n");
    system("terraform destroy -auto-approve");
    system("clear");
    printf("infrastructure has been successfully destroyed...\n");
}

void uploadImage() {
    printf("Uploading Image...\n");
    //to be continued
}

void handleUnknownCommand(const char *commandName) {
    printf("Error! Unknown command: %s\n", commandName);
}

void performInfrastructureAction(const char *commandName) {
    if (strcmp(commandName, "start") == 0) {
        startInfrastructure();
    } else if (strcmp(commandName, "stop") == 0) {
        stopInfrastructure();
    } else if (strcmp(commandName, "download") == 0) {
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
