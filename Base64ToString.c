#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// For strcpy_s on Windows
#ifdef _WIN32
#else
// Custom implementation of strcpy_s for Linux and other platforms
int strcpy_s(char* dest, size_t dest_size, const char* src) {
    if (strlen(src) + 1 > dest_size) {
        return 1; // Error: source is too large
    }
    strcpy(dest, src);
    return 0;
}
#endif

int main(int argc, char* argv[]) {
    //--------------------------------//
    // Get input and length           //
    //--------------------------------//

    char* input = NULL;
    size_t inputLength = 0;

    // Handle input from command-line argument or standard input
    if (argc > 1) {
        // Get input from the first command-line argument
        input = argv[1];
        inputLength = strlen(input);
    }
    else {
        // Read input from standard input
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Failed to read input\n");
            return 1;
        }
        // Remove the newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
        inputLength = strlen(buffer);

        // Allocate memory for input and copy the buffer content
        input = malloc(inputLength + 1);
        if (input == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        strcpy_s(input, inputLength + 1, buffer);
    }

    // Check input is valid
    if (inputLength == 0) {
        printf("Input string is empty\n");
        if (argc == 1) {
            free(input); // Only free if dynamically allocated
        }
        return 1;
    }

    // Define the Base64 character table
    const char base64Table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    // Calculate the effective length of the input (ignoring '=' padding)
    size_t effectiveLength = inputLength;
    while (input[effectiveLength - 1] == '=') {
        effectiveLength--;
    }

    //---------------------------------------------------//
    // Convert Base64 chars to 6-bit binary values       //
    //---------------------------------------------------//

    // Allocate memory to store the binary representation
    int* binary6BitArray = malloc(effectiveLength * 6 * sizeof(int));
    if (binary6BitArray == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int binaryPosition = 0;

    // Convert each Base64 character to its 6-bit binary equivalent
    for (size_t i = 0; i < effectiveLength; i++) {
        // Locate the character in the Base64 table
        char* base64CharPosition = strchr(base64Table, input[i]);
        if (base64CharPosition != NULL) {
            // Get the decimal value of the character from the table
            int decimalValue = (int)(base64CharPosition - base64Table);

            // Convert the decimal value to a 6-bit binary array
            int binaryArray[6] = { 0, 0, 0, 0, 0, 0 };
            for (int j = 5; j >= 0; j--) {
                binaryArray[j] = decimalValue % 2;
                decimalValue /= 2;
            }

            // Append the binary values to binary6BitArray
            for (int j = 0; j < 6; j++) {
                binary6BitArray[binaryPosition++] = binaryArray[j];
            }
        }
    }

    // Free dynamically allocated input if it was from standard input
    if (argc == 1) {
        free(input);
    }

    //---------------------------------------------------//
    // Combine 6-bit groups into 8-bit ASCII chars  //
    //---------------------------------------------------//

    // Calculate the number of ASCII chars
    size_t asciiLength = binaryPosition / 8;

    // Allocate memory to store the ASCII output
    char* asciiOutput = malloc(asciiLength + 1);
    if (asciiOutput == NULL) {
        printf("Memory allocation failed\n");
        free(binary6BitArray);
        return 1;
    }

    // Convert 6-bit binary groups to 8-bit ASCII chars
    for (size_t i = 0; i < asciiLength; i++) {
        int asciiValue = 0;

        // Combine 8 binary bits into a single ASCII char
        for (int j = 0; j < 8; j++) {
            asciiValue += binary6BitArray[i * 8 + j] * (int)pow(2, 7 - j);
        }

        // Store the ASCII char
        asciiOutput[i] = (char)asciiValue;
    }

    // Free memory allocated for the 6-bit binary array
    free(binary6BitArray);

    // Null-terminate the ASCII string
    asciiOutput[asciiLength] = '\0';

    //------------------------//
    // Print the decoded text //
    //------------------------//

    printf("%s\n", asciiOutput);

    // Free the memory allocated for the ASCII output
    free(asciiOutput);

    return 0;
}
