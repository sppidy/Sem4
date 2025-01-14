#include <stdio.h>
#include <math.h>

void extractDataBits(int code[], int data[], int totalBits) {
    int parityBitIndex = 0, dataIndex = 0;

    for (int i = 0; i < totalBits; i++) {
        if ((i + 1) == pow(2, parityBitIndex)) {
            parityBitIndex++;
        } else {
            data[dataIndex++] = code[i];
        }
    }
}

int main() {
    int totalBits;

    printf("Enter the total number of bits (including parity bits): ");
    scanf("%d", &totalBits);

    int code[totalBits];

    printf("Enter the received Hamming code:\n");
    for (int i = 0; i < totalBits; i++) {
        scanf("%d", &code[i]);
    }

    int parityBits = 0;
    while (pow(2, parityBits) < totalBits + 1) {
        parityBits++;
    }

    int extractedDataBits = totalBits - parityBits;
    int extractedData[extractedDataBits];

    extractDataBits(code, extractedData, totalBits);

    printf("Extracted data bits: ");
    for (int i = 0; i < extractedDataBits; i++) {
        printf("%d", extractedData[i]);
    }
    printf("\n");

    return 0;
}