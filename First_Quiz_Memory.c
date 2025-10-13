#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, string argc[] ){

    //Check the usage, must be for 2 CLA

    if (argc != 2){
        printf("Please provide only one file name\n");
        return 1;
    }

    // Open file

    FILE *input = fopen(argv[1], "r"); // We are opening up the file name we entered and then the r signifies we are opening it up in read-only mode

    uint8_t buffer[4]; // unit8_T ensures that the datatype is of size byte also makes a unsigned integer, so it cannot be a negative value for byte

    // How to create an array of signatures bytes
    uint8_t signature[] = {0x25,0x50,0x44,0x46};

    // How to read the first four bites of a file

    fread(buffer, sizeof(uint8_t), 4, input);


    // Check teh first 4 bytes against the signaure bytes
    for (int i = 0; i < 4; i++){
        if (signature[i] != buffer[i]){
            printf("This is not a PDF!\n");
            return 0;
        }
    }

    //Success
    printf("It is a PDF\n");
    fclose(input);

    return 0;


}
