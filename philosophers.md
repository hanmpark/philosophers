# Philosophers

> Who would have thought that philosopher would be so deadly ?

### Summary

This project is an introduction to threading and processes, and how to work on the same memory
on the same memory space.
You will learn how to manipulate threads.
You will learn about mutexes, semaphores and shared memory.

## CodeVault - Youtube

### Short introduction to threads (pthreads)
To compile the following code you will need the -pthread flag.

```c
int	pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

***Parameters:***
- **thread:** pointer to an unsigned integer value that returns the thread id of the thread created.
- **attr:** pointer to a structure that is used to define thread attributes like detached state, scheduling policy, stack address, etc. Set to *NULL* for default thread attributes.
- **start_routine:** pointer to a subroutine that is executed by the thread. The return type and parameter type of the subroutine must be of type void *. The function has a single attribute but if multiple values need to be passed to the function, a struct must be used.
- **arg:** pointer to void that contains the arguments to the function defined in the earlier argument,

```c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*routine() {
	printf("Test from threadsn\n");
	sleep(3);
	printf("Ending thread\n");
}

int	main(int argc, char *argv[]) {
	pthread_t	t1, t2; // variable that can store the results of the thread
	if (pthread_create(&t1, NULL, &routine, NULL) != 0) {
		return 1;
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0) {
		return 2;
	}
	if (pthread_join(t1, NULL) != 0) {
		return 3;
	}
	if (pthread_join(t2, NULL) != 0) {
		return 4;
	}
	return 0;
}
```

OUTPUT:
```shell
Test from threads
Test from threads
Ending thread
Ending thread
```

Don't forget to error check all your function calls.

### Difference between processes and threads

At first glance they look much the same thing, execute the same code at the same time.

What is the difference ?
With 2 processes:
```c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	x = 2;

void	*routine() {
	x++;
	sleep(2);
	printf("Value of x: %d\n", x);
}

void	*routine2() {
	sleep(2);
	printf("Value of x: %d\n", x);
}

int	main(int argc, char *argv[]) {
	pthread_t	t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL)) {
		return 1;
	}
	if (pthread_create(&t2, NULL, &routine2, NULL)) {
		return 2;
	}
	if (pthread_join(t1, NULL)) {
		return 3;
	}
	if (pthread_join(t2, NULL)) {
		return 4;
	}
	return 0;
}
```

With 2 threads:
```c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main(int argc, char *argv[]) {
	int x = 2;
	int	pid = fork();
	if (pid == -1) {
		return 1;
	}

	if (pid == 0) {
		x++;
	}
	sleep(2);
	printf("Value of x: %d\n", x);

	if (pid != 0) {
		wait(NULL);
	}
	return 0;
}
```

- Processes can contain multiple threads.
- Address space. When Forking, we duplicate the memory. With threads, all the variables has the same address.
- Aside from those 2 differences, all of the threads share the file handlers whilst with processes, files are duplicated.

### What are Race Conditions ?

Imagine having a mailbox and having listeners. All they do is just incremeting the number of mails.

```c
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int	mails = 0;

void *routine() {
	for (int i = 0; i < 1000000; i++) {
		mails++;
		// read mails
		// increment
		// write mails
	}
}

int	main(int argc, char *argv[]) {
	pthread_t	p1, p2;
	if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
		return 1;
	}
	if (pthread_create(&p2, NULL, &routine, NULL) != 0) {
		return 2;
	}
	if (pthread_join(p1, NULL) != 0) {
		return 3;
	}
	if (pthread_join(p2, NULL) != 0) {
		return 4;
	}
	printf("Number of mails: %d\n", mails);
	return 0;
}
```

Why does it happen only when we put a big number ?
It's simply because if you only have 100 iterations, it will be finished by the time it creates the second thread. Thus, you don't have anything interliving.
Even then, it could just happen. It's just that there are fewer chances for it to happen. In computer science, it's incredibly important that our data is exact.