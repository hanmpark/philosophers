# Philosophers

> Who would have thought that philosopher would be so deadly ?

## Summary

This project is an introduction to threading and processes, and how to work on the same memory
on the same memory space.
You will learn how to manipulate threads.
You will learn about mutexes, semaphores and shared memory.

### Short introduction to threads
To manipulate threads, you will need to compile your code with the -pthread flag.
To create one thread you will need to use the following function:

```c
int	pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

***Parameters:***
- **thread:** pointer to an unsigned integer value that returns the thread id of the thread created.
- **attr:** pointer to a structure that is used to define thread attributes like detached state, scheduling policy, stack address, etc. Set to *NULL* for default thread attributes.
- **start_routine:** pointer to a subroutine that is executed by the thread. The return type and parameter type of the subroutine must be of type void *. The function has a single attribute but if multiple values need to be passed to the function, a struct must be used.
- **arg:** pointer to void that contains the argument(s) to the function defined in the earlier argument.

***
## Difficulties
### Difference between processes and threads

At first glance they look much the same thing, execute the same code at the same time.

But:
- A single process can contain multiple threads.
- Address space: when Forking, we duplicate the memory. With threads, ***all the variables has the same address***.

Thus, we will have to be careful accessing the memory.

### Race conditions 🏎

> A race condition in C occurs when multiple parts of a program try to **access or manipulate** shared data **simultaneously**, leading to unpredictable or erroneous results. It's like a "race" between different parts of the code to complete their operations first, and the outcome of the race is uncertain and can vary each time the program runs.

Race conditions can cause bugs that are challenging to debug because they are often unpredictable and dependent on the timing and interleaving of operations. Proper synchronization techniques, such as **locks** or **mutexes**, can be used to address race conditions and ensure the correct behavior of concurrent programs.

### Deadlocks 🔒

> A deadlock in concurrent programming is a situation where two or more threads or processes are unable to proceed because each is waiting for the other to release a resource that it holds. This results in a standstill or a permanent blocking of progress, where the involved threads or processes are unable to continue their execution.

## Compiling

First of all, there are 2 versions of my program:
* One version (mandatory) in which each philosopher is represented by a **thread** and uses **mutexes**.
* Another version (bonus) in which each philosopher is represented by a **process** and uses **semaphores**.

To compile my program you will have to `make`. Then run the program as follow:
```zsh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
