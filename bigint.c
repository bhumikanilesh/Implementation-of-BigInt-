#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DIGITS 310
#define MAX_INPUT_LENGTH 320

typedef struct {
    char digits[MAX_DIGITS];
    int length;
    int sign;
} BigInt;

BigInt createBigInt(const char *num);
void printBigInt(const BigInt *a);
BigInt addBigInt(const BigInt *a, const BigInt *b);
BigInt subtractBigInt(const BigInt *a, const BigInt *b);
BigInt multiplyBigInt(const BigInt *a, const BigInt *b);

BigInt createBigInt(const char *num) {
    BigInt result;
    result.length = 0;
    result.sign = 1;

    int start = 0;
    if (num[0] == '-') {
        result.sign = -1;
        start = 1;
    } else if (num[0] == '+') {
        start = 1;
    }

    int num_length = strlen(num) - start;

    if (num_length > MAX_DIGITS) {
        fprintf(stderr, "Error: Input exceeds maximum supported digits (%d).\n", MAX_DIGITS);
        exit(1);
    }

    for (int i = 0; i < num_length; i++) {
        if (num[start + i] < '0' || num[start + i] > '9') {
            fprintf(stderr, "Error: Invalid character in input.\n");
            exit(1);
        }
        result.digits[num_length - i - 1] = num[start + i] - '0';
    }

    result.length = num_length;
    return result;
}

void printBigInt(const BigInt *a) {
    if (a->sign == -1) {
        printf("-");
    }
    for (int i = a->length - 1; i >= 0; i--) {
        printf("%d", a->digits[i]);
    }
    printf("\n");
}

BigInt addBigInt(const BigInt *a, const BigInt *b) {
    BigInt result;
    result.length = 0;
    result.sign = 1;

    if (a->sign == b->sign) {
        result.sign = a->sign;
        int carry = 0;
        for (int i = 0; i < a->length || i < b->length || carry; i++) {
            if (result.length >= MAX_DIGITS) {
                fprintf(stderr, "Error: Addition result exceeds maximum digit limit.\n");
                exit(1);
            }

            int digitSum = carry;
            if (i < a->length) digitSum += a->digits[i];
            if (i < b->length) digitSum += b->digits[i];

            result.digits[result.length++] = digitSum % 10;
            carry = digitSum / 10;
        }
    } else {
        BigInt absA = *a, absB = *b;
        absA.sign = absB.sign = 1;

        if (a->sign == 1) {
            result = subtractBigInt(a, &absB);
        } else {
            result = subtractBigInt(b, &absA);
        }
    }
    return result;
}

BigInt subtractBigInt(const BigInt *a, const BigInt *b) {
    BigInt result;
    result.length = 0;
    result.sign = 1;

    if (a->sign != b->sign) {
        BigInt absB = *b;
        absB.sign *= -1;
        return addBigInt(a, &absB);
    }

    if (a->length == b->length) {
        bool equal = true;
        for (int i = a->length - 1; i >= 0; i--) {
            if (a->digits[i] != b->digits[i]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            BigInt zero = { .length = 1, .digits = {0}, .sign = 1 };
            return zero;
        }
    }

    const BigInt *larger = a;
    const BigInt *smaller = b;
    if (a->length < b->length || (a->length == b->length && a->digits[a->length - 1] < b->digits[b->length - 1])) {
        larger = b;
        smaller = a;
        result.sign = -1;
    } else {
        result.sign = a->sign;
    }

    int borrow = 0;
    for (int i = 0; i < larger->length || borrow; i++) {
        if (result.length >= MAX_DIGITS) {
            fprintf(stderr, "Error: Subtraction result exceeds maximum digit limit.\n");
            exit(1);
        }

        int diff = larger->digits[i] - borrow;
        if (i < smaller->length) diff -= smaller->digits[i];

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[result.length++] = diff;
    }
    while (result.length > 1 && result.digits[result.length - 1] == 0) {
        result.length--;
    }
    return result;
}

BigInt multiplyBigInt(const BigInt *a, const BigInt *b) {
    BigInt result;
    memset(&result, 0, sizeof(BigInt));
    result.sign = a->sign * b->sign;

    for (int i = 0; i < a->length; i++) {
        int carry = 0;
        for (int j = 0; j < b->length || carry; j++) {
            if (i + j >= MAX_DIGITS) {
                fprintf(stderr, "Error: Multiplication result exceeds maximum digit limit.\n");
                exit(1);
            }

            int product = result.digits[i + j] + a->digits[i] * (j < b->length ? b->digits[j] : 0) + carry;
            result.digits[i + j] = product % 10;
            carry = product / 10;
        }
    }

    result.length = a->length + b->length;
    while (result.length > 1 && result.digits[result.length - 1] == 0) {
        result.length--;
    }

    return result;
}

int main() {
    char input_a[MAX_INPUT_LENGTH], input_b[MAX_INPUT_LENGTH];
    int operation;

    printf("Enter first number: ");
    scanf("%319s", input_a);
    
    printf("Enter second number: ");
    scanf("%319s", input_b);

    printf("Select operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &operation);

    BigInt a = createBigInt(input_a);
    BigInt b = createBigInt(input_b);

    switch (operation) {
        case 1: {
            BigInt sum = addBigInt(&a, &b);
            printf("Sum: ");
            printBigInt(&sum);
            break;
        }
        case 2: {
            BigInt diff = subtractBigInt(&a, &b);
            printf("Difference: ");
            printBigInt(&diff);
            break;
        }
        case 3: {
            BigInt product = multiplyBigInt(&a, &b);
            printf("Product: ");
            printBigInt(&product);
            break;
        }
        default:
            printf("Invalid operation!\n");
    }
    return 0;
}
