# Philosophers

> Who would have thought that philosopher would be so deadly ?

## Summary

This project is an introduction to threading and processes, and how to work on the same memory
on the same memory space.
You will learn how to manipulate threads.
You will learn about mutexes, semaphores and shared memory.

### Dining Philosophers Problem
**The Dining Philosophers** problem is a classic synchronization problem in computer science that illustrates challenges in resource allocation and concurrency. It involves a group of philosophers sitting around a table, with each philosopher alternating between eating, sleeping and thinking. There is a chopstick placed between each pair of adjacent philosophers. The problem arises when each philosopher needs two chopsticks to eat, but there are only as many chopsticks as there are philosophers.

The challenge is to devise a solution that allows each philosopher to eat without causing a **deadlock**. Different synchronization techniques like **mutexes** or **semaphores** can be used to manage access to the chopsticks and ensure that only one philosopher can pick up both chopsticks at the same time, while others wait their turn.

## Code structure
### ./philo
![philo](https://github.com/Nonino42/philosophers/blob/master/code_struct/philo.png)
### ./philo_bonus
![philo](https://github.com/Nonino42/philosophers/blob/master/code_struct/philo_bonus.png)

### Short introduction to threads
> A thread is a separate sequence of execution within a program. It allows for **multitasking** and **concurrent execution** of tasks by dividing a program into smaller units. Threads share the **same memory space and resources**, but have their own program counters and stacks. They are used to improve performance, responsiveness, and resource utilization in concurrent programming.

***
## Difficulties
### Difference between processes and threads

At first glance they look much the same thing, execute the same code at the same time.

But:
- A single process can contain multiple threads.
- Address space: when Forking, we duplicate the memory. With threads, ***all the variables has the same address***.

Thus, when there are multiple threads, we will have to be careful accessing the memory.

### Race conditions 🏎

> A race condition in C occurs when multiple parts of a program try to **access or manipulate** shared data **simultaneously**, leading to unpredictable or erroneous results. It's like a "race" between different parts of the code to complete their operations first, and the outcome of the race is uncertain and can vary each time the program runs.

Race conditions can cause bugs that are challenging to debug because they are often unpredictable and dependent on the timing and interleaving of operations. Proper synchronization techniques, such as **locks** or **mutexes**, can be used to address race conditions and ensure the correct behavior of concurrent programs.

### Deadlocks 🔒

> A deadlock in concurrent programming is a situation where two or more threads or processes are unable to proceed because each is waiting for the other to release a resource that it holds. This results in a standstill or a permanent blocking of progress, where the involved threads or processes are unable to continue their execution.

***
## Compiling

First of all, there are 2 versions of my program:
* One version (mandatory) in which each philosopher is represented by a **thread** and uses **mutexes**.
* Another version (bonus) in which each philosopher is represented by a **process** and uses **semaphores**.

To compile my program you will have to `make`. Then run the program as follow:
```zsh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
