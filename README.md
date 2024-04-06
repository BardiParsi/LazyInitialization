# Lazy Initialization with Multithreading in C++

## Overview
This repository contains a C++ solution that demonstrates the proper way of implementing lazy initialization with multithreading. Lazy initialization is a design pattern used to defer the creation of an object until it is needed. Multithreading is utilized to ensure thread safety and efficient utilization of system resources.

## Requirements
- C++20 compatible compiler
- This code has been tested and confirmed to work with both Mingw g++ and Windows MSVC compilers. GCC compiler should be avoided.
- Standard C++ libraries
- Git

## Usage
To use this solution, follow these steps:
1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/BardiParsi/LazyInitialization.git
    ```
2. Navigate to the cloned directory:
    ```bash
    cd LazyInitialization1
    ```
3. Compile the source code:
    ```bash
    g++ -std=c++20 -pthread main.cpp -o main
    ```
4. Run the executable:
    ```bash
    ./main
    ```

## Implementation Details
The solution consists of the following key components:
- `ExpensiveObject`: Represents an expensive object that is initialized lazily.
- `LazyInitialization`: Manages the lazy initialization of `ExpensiveObject` using a mutex and atomic flags to ensure thread safety and efficient resource utilization.
- `main`: Demonstrates the usage of `LazyInitialization` with multiple threads.

## Code Explanation
- `ExpensiveObject`: Simulates an expensive object that takes some time to initialize.
- `LazyInitialization`: Implements lazy initialization using `std::once_flag` and `std::atomic<bool>`. The `useObject()` function ensures that the object is initialized only once and is thread-safe.
- `main`: Creates a vector of multiple threads that attempt to use the `ExpensiveObject` simultaneously, demonstrating the effectiveness of lazy initialization and multithreading.

## Contributing
Contributions are welcome! Feel free to submit issues or pull requests for any improvements or additional features.

## License
This project is licensed under the GNU General Public License (GPL).
Author: Bardi (Masoud) Parsi
Contact: farsi.masoud@gmail.com
