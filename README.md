# Dining Philosopher Problem

## Overview
This repository contains implementations of the classic Dining Philosopher Problem, a common example used in concurrent algorithm design to illustrate synchronization issues and methods to resolve them. The problem involves philosophers who alternately think and eat, but require two forks to eat, leading to potential conflicts and deadlocks.

## Contents
- **dining_deadlock.c**: A basic implementation of the Dining Philosopher Problem that leads to a deadlock situation.
- **dining_sem.c**: An implementation using semaphores to resolve the deadlock and ensure proper synchronization.
- **dining_mutex.c**: An implementation using mutexes to achieve synchronization and avoid deadlock.
- **SO_Gr23_Projekti.pdf**: Detailed documentation and explanation of the problem, the solutions, and the code structure.

## How to Run
To compile and run any of the C programs, use the following commands in your terminal:

```bash
gcc dining_deadlock.c -o dining_deadlock
./dining_deadlock

gcc dining_sem.c -o dining_sem
./dining_sem

gcc dining_mutex.c -o dining_mutex
./dining_mutex
