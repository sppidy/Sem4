#include<stdio.h>
#include <math.h>

void calculateParityBits(int data[], int code[], int dataBits, int totalBits) {
    int parityBitIndex = 0;

    for (int i = 0; i < totalBits; i++) {
        if ((i + 1) == pow(2, parityBitIndex)) {
            parityBitIndex++;
            continue;
        }
        code[i] = data[--dataBits];
    }

    parityBitIndex = 0;
    for (int i = 0; i < totalBits; i++) {
        if ((i + 1) == pow(2, parityBitIndex)) {
            int parity = 0;
            for (int j = i; j < totalBits; j++) {
                if (((j + 1) & (i + 1)) != 0) {
                    parity ^= code[j];
                }
            }
            code[i] = parity;
            parityBitIndex++;
        }
    }
}

void detectAndCorrectError(int code[], int totalBits) {
    int errorPosition = 0;

    for (int i = 0; i < log2(totalBits) + 1; i++) {
        int parity = 0;
        for (int j = 0; j < totalBits; j++) {
            if (((j + 1) & (1 << i)) != 0) {
                parity ^= code[j];
            }
        }
        errorPosition += parity * pow(2, i);
    }

    if (errorPosition) {
        printf("Error detected at position %d.\n", errorPosition);
        code[errorPosition - 1] ^= 1;
    } else {
        printf("No errors detected.\n");
    }
}

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
    int dataBits, totalBits;

    printf("Enter the number of data bits: ");
    scanf("%d", &dataBits);

    int parityBits = 0;
    while (pow(2, parityBits) < dataBits + parityBits + 1) {
        parityBits++;
    }
    totalBits = dataBits + parityBits;

    int data[dataBits], code[totalBits];

    printf("Enter the data bits (one by one):\n");
    for (int i = 0; i < dataBits; i++) {
        scanf("%d", &data[i]);
    }

    for (int i = 0; i < totalBits; i++) {
        code[i] = 0;
    }

    calculateParityBits(data, code, dataBits, totalBits);

    printf("Encoded Hamming Code: ");
    for (int i = totalBits - 1; i >= 0; i--) {
        printf("%d", code[i]);
    }
    printf("\n");

    printf("Introduce an error by flipping a bit (0 for no error):\n");
    int errorIndex;
    scanf("%d", &errorIndex);
    if (errorIndex > 0 && errorIndex <= totalBits) {
        code[errorIndex - 1] ^= 1;
    }

    detectAndCorrectError(code, totalBits);

    printf("Corrected Hamming Code: ");
    for (int i = totalBits - 1; i >= 0; i--) {
        printf("%d", code[i]);
    }
    printf("\n");

    int extractedDataBits = totalBits - parityBits;
    int extractedData[extractedDataBits];

    extractDataBits(code, extractedData, totalBits);

    printf("Extracted data bits: ");
    for (int i = extractedDataBits - 1; i >= 0; i--) {
        printf("%d", extractedData[i]);
    }
    printf("\n");

    printf("Number of redundant bits=%d\n", parityBits);
    printf("The redundant bits are:\n");
    printf("r1=%d\n", code[0]);
    printf("r2=%d\n", code[1]);
    printf("r4=%d\n", code[3]);
    // printf("r8=%d\n", code[8]);

    return 0;
}