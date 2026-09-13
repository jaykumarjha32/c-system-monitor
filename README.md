# C System Monitor

A menu-driven Linux command-line utility developed in C for monitoring basic system information such as system uptime, memory usage, process count, and hostname.

## Overview

The project demonstrates C programming and Linux system-level concepts by reading system information from the Linux `/proc` filesystem.

The application provides an interactive menu through which users can select different monitoring operations.

## Features

- View system uptime
- View total, available, and used memory
- View the number of existing processes
- View system hostname
- Display all available monitoring information
- Handle invalid user input

## Technologies

- C
- Linux
- GCC
- Linux `/proc` filesystem

## C Concepts Demonstrated

- Functions
- Pointers
- Structures
- Character arrays
- File handling
- String processing
- Loops
- Conditional statements
- Switch-case
- Error handling
- Directory operations

## Linux Concepts

The project interacts with Linux system information through:

- `/proc/uptime` - system uptime
- `/proc/meminfo` - memory information
- `/proc/sys/kernel/hostname` - system hostname
- `/proc` - process information

## Compilation

Compile the program using GCC:

```bash
gcc -Wall -Wextra -o system_monitor system_monitor.c

## Execution

```bash
./system_monitor
