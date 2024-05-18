# Dining Philosopher Problem

## Overview
This repository contains implementations of the classic Dining Philosopher Problem, a common example used in concurrent algorithm design to illustrate synchronization issues and methods to resolve them. The problem involves philosophers who alternately think and eat, but require two forks to eat, leading to potential conflicts and deadlocks.

## Contents
- **dining_deadlock.c**: A basic implementation of the Dining Philosopher Problem that leads to a deadlock situation.
- **dining_sem.c**: An implementation using semaphores to resolve the deadlock and ensure proper synchronization.
- **dining_mutex.c**: An implementation using mutexes to achieve synchronization and avoid deadlock.
- **SO_Gr23_Projekti.pdf**: Detailed documentation and explanation of the problem, the solutions, and the code structure.

## Files

### dining_deadlock.c
This file contains an implementation of the Dining Philosopher Problem that results in a deadlock. The philosophers pick up their left fork and then attempt to pick up their right fork, leading to a situation where each philosopher holds one fork and waits indefinitely for the other.

### dining_sem.c
This solution utilizes semaphores to prevent deadlock. By using a semaphore to control access to the forks, the philosophers are able to synchronize their actions and avoid the circular wait condition that causes deadlocks.

### dining_mutex.c
This implementation uses mutexes to ensure that only one philosopher can pick up a fork at a time. Mutexes provide mutual exclusion and prevent multiple philosophers from accessing the same resource simultaneously, thus avoiding deadlock.

### documentation.php
The `documentation.php` file contains comprehensive documentation of the Dining Philosopher Problem, including a description of the problem, the deadlock scenario, and detailed explanations of the semaphore and mutex solutions. It also includes code comments and additional references for further reading.

## How to Run
To compile and run any of the C programs, use the following commands in your terminal:

```bash
gcc -o dining_deadlock dining_deadlock.c -lpthread
./dining_philosopher_deadlock

gcc -o dining_sem dining_sem.c -lpthread
./dining_sem

gcc -o dining_mutex dining_mutex.c -lpthread
./dining_mutex
