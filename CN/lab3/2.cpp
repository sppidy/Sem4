#include <stdio.h>
#include <math.h>

void calculateParityBits1962(int data[], int n, int hammingCode[]) {
    int r = 0;

    // Calculate the number of parity bits needed
    while ((1 << r) < (n + r + 1)) {
        r++;
    }

    int j = 0;
    for (int i = 1; i <= n + r; i++) {
        if ((i & (i - 1)) == 0) {
            hammingCode[i - 1] = 0; // Initialize parity bits to 0
        } else {
            hammingCode[i - 1] = data[j];
            j++;
        }
    }

    // Calculate parity bits
    for (int i = 0; i < r; i++) {
        int parityPos = 1 << i;
        int parity = 0;
        for (int j = 1; j <= n + r; j++) {
            if (j & parityPos) {
                parity ^= hammingCode[j - 1];
            }
        }
        hammingCode[parityPos - 1] = parity; // Set the calculated parity bit
    }
}

void encodeHamming1962(int data[], int n, int hammingCode[]) {
    calculateParityBits1962(data, n, hammingCode);
}

int main() {
    int n;
    printf("Enter the number of data bits: ");
    scanf("%d", &n);

    int data[n];
    printf("Enter the data bits: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data[i]);
    }

    int r = 0;
    while ((1 << r) < (n + r + 1)) {
        r++;
    }
    printf("Number of parity bits: %d\n", r);
    
    int hammingCode[n + r];
    for (int i = 0; i < n + r; i++) {
        hammingCode[i] = 0; // Initialize the Hamming code array
    }

    encodeHamming1962(data, n, hammingCode);
    printf("Encoded data with parity bits (MSB to LSB): ");
    for (int i = n + r - 1; i >= 0; i--) {
        printf("%d ", hammingCode[i]);
    }
    printf("\n");

    printf("Parity bits (r1, r2, r4, r8):\n");
    for (int i = 0; i < r; i++) {
        printf("r%d = %d\n", (1 << i), hammingCode[(1 << i) - 1]);
    }
    printf("\n");

    return 0;
}