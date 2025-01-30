# Implementation-of-BigInt-
BigInt implementation in C is a well-structured program that allows arithmetic operations (addition, subtraction, and multiplication) on arbitrarily large integers. Since built-in integer types in C have size limitations (e.g., int and long long), your implementation represents large numbers as arrays of digits.

# BigInt Implementation in C

## Overview
This project implements a **BigInt** (arbitrarily large integer) library in **C** that supports basic arithmetic operations such as:
- Addition
- Subtraction
- Multiplication

Since built-in integer types (like `int` and `long long`) have size limitations, this implementation represents large numbers as **arrays of digits** and performs operations using elementary algorithms.

---

## Features
✅ Supports numbers up to **310 digits**.  
✅ Handles **positive and negative** numbers.  
✅ Performs **addition, subtraction, and multiplication** efficiently.  
✅ Checks for **invalid input** (e.g., non-numeric characters).  
✅ Provides **error handling** for exceeding maximum digits.  

---

## Compilation & Execution

### **Compile the program:**
```sh
gcc -o bigint bigint.c
```

### **Run the program:**
```sh
./bigint
```

### **Sample Input & Output:**
```
Enter first number: 12345678901234567890
Enter second number: 98765432109876543210
Select operation:
1. Addition
2. Subtraction
3. Multiplication
Enter choice (1-3): 1
Sum: 111111111011111111100
```

---

## Implementation Details

### **BigInt Representation**
Each large number is stored in a struct:
```c
#define MAX_DIGITS 310

typedef struct {
    char digits[MAX_DIGITS];  // Stores digits in reverse order
    int length;               // Number of digits
    int sign;                 // 1 for positive, -1 for negative
} BigInt;
```

### **Operations**
#### **1. `createBigInt(const char *num)`**
- Converts a string into a `BigInt` structure.
- Stores digits in **reverse order** for easier calculations.
- Handles sign detection and input validation.

#### **2. `printBigInt(const BigInt *a)`**
- Prints the BigInt in **correct order**.
- Handles negative numbers.

#### **3. `addBigInt(const BigInt *a, const BigInt *b)`**
- Adds two BigInts digit-by-digit.
- Handles carry propagation and different signs.

#### **4. `subtractBigInt(const BigInt *a, const BigInt *b)`**
- Subtracts two BigInts using the **borrow method**.
- Ensures correct handling of negative results.

#### **5. `multiplyBigInt(const BigInt *a, const BigInt *b)`**
- Implements **O(n²) schoolbook multiplication**.
- Handles large numbers efficiently.

---

## Future Improvements
🚀 **Implement Division** – Support integer division and modulus.  
🚀 **Optimize Multiplication** – Use **Karatsuba Algorithm** for faster performance.  
🚀 **Improve Input Handling** – Strip leading zeros and refine error messages.  

---

## License
This project is released under the **MIT License**. Feel free to modify and use it! 🎯

