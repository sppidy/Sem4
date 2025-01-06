

#include <stdio.h>
#include <math.h>

void calculateParityBits(int data[], int n, int hammingCode[]) {
    int r = 0;

    while (pow(2, r) < (n + r + 1)) {
        r++;
    }

    int j = 0;
    for (int i = 1; i <= n + r; i++) {
        if ((i & (i - 1)) == 0) {
            // This is a parity bit position
            hammingCode[i - 1] = 0;
        } else {
            // This is a data bit position
            hammingCode[i - 1] = data[j];
            j++;
        }
    }

    for (int i = 0; i < r; i++) {
        int parityPos = pow(2, i);
        int parity = 0;
        for (int j = 1; j <= n + r; j++) {
            if (j & parityPos) {
                parity ^= hammingCode[j - 1];
            }
        }
        hammingCode[parityPos - 1] = parity;
    }
}

void encodeHamming(int data[], int n, int hammingCode[]) {
    calculateParityBits(data, n, hammingCode);
}

void decodeHamming(int hammingCode[], int n, int decodedData[]) {
    int r = 0;

    while (pow(2, r) < (n + 1)) {
        r++;
    }

    int errorPos = 0;
    for (int i = 0; i < r; i++) {
        int parityPos = pow(2, i);
        int parity = 0;
        for (int j = 1; j <= n; j++) {
            if (j & parityPos) {
                parity ^= hammingCode[j - 1];
            }
        }
        if (parity != 0) {
            errorPos += parityPos;
        }
    }

    if (errorPos != 0) {
        hammingCode[errorPos - 1] ^= 1;
    }

    int j = 0;
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) != 0) {
            decodedData[j] = hammingCode[i - 1];
            j++;
        }
    }
}

int main() {
    int data[] = {1, 0, 1, 1}; 
    int n = sizeof(data) / sizeof(data[0]);
    int hammingCode[7];

    encodeHamming(data, n, hammingCode);
    printf("Encoded data: ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", hammingCode[i]);
    }
    printf("\n");

    hammingCode[2] ^= 1;

    int decodedData[4];
    decodeHamming(hammingCode, 7, decodedData);
    printf("Decoded data: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", decodedData[i]);
    }
    printf("\n");

    return 0;
}