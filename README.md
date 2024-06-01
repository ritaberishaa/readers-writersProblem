# First Readers-Writers Problem

## Overview
This C program implements the first readers-writers problem using POSIX semaphores and threads. It demonstrates how multiple readers can read simultaneously from a shared resource, while writers gain exclusive access to write to the resource. This ensures no reader reads the resource while a writer writes to it.

## Features
- **Concurrency Handling**: Uses POSIX semaphores to manage concurrent access between readers and writers.
- **Thread Management**: Employs POSIX threads to simulate multiple readers and writers accessing a shared resource.

## How It Works
The program uses two semaphores (`x` and `y`) and arrays of pthreads (`readerthreads` and `writerthreads`) to manage access between readers and writers. The `x` semaphore controls access to modify the `readercount`, which tracks the number of readers currently reading. The `y` semaphore ensures that either any number of readers or a single writer can access the shared resource, but not both.

### Reader Function
- Waits for semaphore `x` to modify the `readercount`.
- If it is the first reader, it also waits on semaphore `y` to block writers.
- After reading, it decrements `readercount` and, if it's the last reader, signals semaphore `y` to allow writers to proceed.

### Writer Function
- Waits for semaphore `y` to ensure exclusive access to the shared resource.
- After writing, it signals `y` to allow other operations (read or write) to proceed.

## Compilation and Execution
Ensure you have a C compiler installed (e.g., GCC) and your system supports POSIX threads and semaphores.

### Compiling the Code
Run the following command to compile the program:
```bash
gcc -o readers_writers readers_writers.c -lpthread
