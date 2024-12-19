#include <stdio.h>

int main() {
    int n, choice;

    // Input the number of data bits
    printf("Enter the number of data bits: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid number of bits.\n");
        return 1;
    }

    int data[n];
    printf("Enter the data bits (0 or 1): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data[i]);
        if (data[i] != 0 && data[i] != 1) {
            printf("Invalid input. Only 0 or 1 allowed.\n");
            return 1;
        }
    }

    printf("1. Even Parity\n2. Odd Parity\nEnter your choice: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        return 1;
    }

    int count_ones = 0;
    for (int i = 0; i < n; i++) {
        if (data[i] == 1) {
            count_ones++;
        }
    }

    int parity_bit = (choice == 1) ? (count_ones % 2) : !(count_ones % 2);

    printf("Generated data with parity bit: ");
    for (int i = 0; i < n; i++) {
        printf("%d", data[i]);
    }
    printf("%d\n", parity_bit);

    int received_data[n + 1];
    printf("Enter the received data with parity bit: ");
    for (int i = 0; i < n + 1; i++) {
        scanf("%d", &received_data[i]);
        if (received_data[i] != 0 && received_data[i] != 1) {
            printf("Invalid input. Only 0 or 1 allowed.\n");
            return 1;
        }
    }

    count_ones = 0;
    for (int i = 0; i < n; i++) {
        if (received_data[i] == 1) {
            count_ones++;
        }
    }

    int recalculated_parity = (choice == 1) ? (count_ones % 2) : !(count_ones % 2);

    if (recalculated_parity == received_data[n]) {
        printf("Data accepted: No error.\n");
    } else {
        printf("Error detected in the data.\n");
    }

    return 0;
}
