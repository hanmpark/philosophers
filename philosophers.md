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

### What is a mutex in C ? (pthread_mutex)

```c
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int	mails = 0;
int	lock = 0;

void	*routine() {
	for (int i = 0; i < 1000000; i++) {
		if (lock == 1) {
			// wait until the lock is 0
			// We don't need the lock variable acutally
		}
		lock = 1;
		mails++;
		lock = 0;
	}
}
```

We need this:
```c
pthread_mutex_t mutex;

int	main(int argc, char *argv[]) {
	pthread_mutex_init(&mutex, NULL); // it's gonna set everything to default
	pthread_mutex_destroy(&mutex);
	return 0;
}
```
To use you have to do this:
```c
void	*routine() {
	for (int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex); // this one function does all that for us
		mails++;
		pthread_mutext_unlock(&mutex);
		// read_mails
		// increment
		// write mails
	}
}
```

This locking and unlocking is basically protecting a part of the code from other threads.
Not all instructions have to be like that. If one thread has its own instruction, no need to mutex.

It's better to not use mutexes, use it only when you have to for rapidity's sake.

A race condition can only happen on a multi core processor.

### How to create threads in a loop (pthread_create)

In the previous code, we could see that there is a lot of ```pthrea_create``` calls. Now, we will look at how we could call it inside a loop.

```c
pthread_t	p1, p2, p3, p4;
```
Instead of this, we could create an array instead.
```c
pthread_t	th[4];
int			i;
pthread_mutex_init(&mutex, NULL);
for (i = 0; i < 4; i++) {
	if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
		perror("Failed to create thread");
		return 1;
	}
	if (pthread_join(th[i], NULL) != 0) {
		return 2;
	}
}
pthread_mutex_destroy(&mutex);
printf("Number of mails: %d\n", mails);
return 0;
```
The code above looks fine at first glance... At no point we will have more than 1 thread runnning at the same time. The first thread gets created, then the system waits for the thread to finish its execution and only then it will create another thread.
Basically, do not create and join the thread in the same loop:
```c
for (i = 0; i < 4; i++) {
	if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
		perror("Failed to create thread");
		return 1;
	}
	printf("Thread %d has started\n", i);
}
for (i = 0; i < 4; i++) {
	if (pthread_join(th[i], NULL) != 0) {
		return 2;
	}
	printf("Thread %d has finished execution\n", i);
}
```

### Get return value from a thread (pthread_join)

The code shown below, is a simple program that gives you the results of dice from the threads.

```c
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice() {
	int	value = (rand() % 6) + 1;
	printf("%d\n", value);
}

int	main(int argc, char *argv[]) {
	srand(time(NULL));
	pthread_t	th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
		return 1;
	}
	if (pthread_join(th, NULL) != 0) {
		return 2;
	}
	return 0;
}
```

To get a return value from a thread we are going to look at the ```pthread_join()``` function.
```c
int	pthread_join(pthread_t __th, void **__thread_return);
```
As you can see, the second parameter of the function takes a double pointer to void. This function is going to take a reference to a pointer to void. It is going to set the value a variable.

```c
int	*res;
srand(time(NULL));
pthread_t	th;
...
if (pthread_join(th, (void **) &res) != 0) {
	return 2;
}
printf("Result: %d\n", *res);
return 0;
```
```c
void	*roll_dice() {
	int	value = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	return (void *) result;
}
```

### How to pass arguments to threads in C

> PROBLEM: create 10 threads, each taking a unique prime from the primes array and print int on the screen.

```c
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *arg) {
	int	index = (int *)*arg;
	printf("%d ", primes[index]);
	free(arg);
}

int	main(int argc, char *argv[]) {
	pthread_t th[10];
	for (int i = 0; i < 10; i++) {
		int	*a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0) {
			perror("Failed to create thread");
		}
	}
	for (int i = 0; i < 10; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread");
		}
	}
	return 0;
}
```

### Practical example for using threads #1 (summing numbers from an array)

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *arg) {
	int	index = *(int *)arg;
	int	sum = 0;
	for (int i = 0; i < 5; i++) {
		sum += primes[index + i];
	}
	*(int *)arg = sum;
	return arg;
}

int	main(int argc, char *argv[]) {
	pthread_t	th[2];
	int	i;
	for (i = 0; i < 2; i++) {
		int	*a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0) {
			perror("Failed to create thread");
		}
	}
	int	globalSum = 0;
	for (i = 0; i < 2; i++) {
		int	*r;
		if (pthread_join(th[i], (void **) &r) != 0) {
			perror("Failed to join thread");
		}
		globalSum += *r;
		free(r);
	}
	printf("Global sum: %d\n", globalSum);
	return 0;
}
```

### What is pthread_t ?

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>

#define TRHEAD_NUM 2

void	*routine(void *args) {
	pthread_t	th = pthread_self(); // managed by pthread API
	printf("%ul\n", th); // id of a thread
	printf("%d\n", (pid_t) syscall(SYS_gettid)); // internal thread id
}

int	main(int argc, char *argv[]) {
	pthread_t	th[THREAD_NUM];
	int			i;
	for (i = 0; i < THREAD_NUM; i++) {
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
			perror("Failed to create thread");
		}
		printf("%ul\n", th[i]); // id of a thread
	}

	for (i = 0; i < THREAD_NUM; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread");
		}
	}
	return 0;
}
```

pthread_t should be treated as an opaque data type. Because it could be a struct, unsigned long long, etc. You should never work with their value. Do not assume that pthread_t is a certain type like the code above. It might work but not work as well.

### What are detached threads ?

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>

#define TRHEAD_NUM 2

void	*routine(void *args) {
	sleep(1);
	printf("Finished execution\n");
}

int	main(int argc, char *argv[]) {
	pthread_t	th[THREAD_NUM];
	pthread_attr_t	detachedThread;
	pthread_attr_init(&detachedThread);
	pthread_attr_setdetachstate(&detachedThread, PHTREAD_CREATE_DETACHED);

	int	i;
	for (i = 0; i < THREAD_NUM; i++) {
		if (pthread_create(&th[i], &detachedThread, &routine, NULL) != 0) {
			perror("Failed to create thread");
		}
		pthread_detach(th[i]);
	}

	for (i = 0; i < THREAD_NUM; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread");
		}
	}

	pthread_attr_destroy(&detachedThread);

	return 0;
}
```

A detached thread is no longer joinable. They actually clear their own resources. We will not get the message written in routine() because the actual process has finished its execution, thus the main thread that created the threads, failed to join them.