# Linux System Calls 2 Threads, Mutex, Pipes

**Threads**

Use the `-pthread gcc` flag when compiling programs that use pthreads.

Threads teilen sich:
* PID und Parent PID
* Signal Handler
* Terminal
* Working Directory

[pthreads](http://man7.org/linux/man-pages/man7/pthreads.7.html)

Thread erstellen: [pthread_create](http://man7.org/linux/man-pages/man3/pthread_create.3.html)

Thread beenden (im thread callback aufrufen): [pthread_exit](http://man7.org/linux/man-pages/man3/pthread_exit.3.html)

Thread canceln: [pthread_cancel](http://man7.org/linux/man-pages/man3/pthread_cancel.3.html)

Eigene Thread ID: [pthread_self](http://man7.org/linux/man-pages/man3/pthread_self.3.html)

Thread ID’s vergleichen: [pthread_equal](http://man7.org/linux/man-pages/man3/pthread_equal.3.html)

Auf Thread Ende warten: [pthread_join](http://man7.org/linux/man-pages/man3/pthread_join.3.html)

Falls Thread nicht gejoined wird, wird er zu einem Zombie-Thread, wie Prozesse ohne `wait()`.

Threads unjoinable machen: [pthread_detach](http://man7.org/linux/man-pages/man3/pthread_detach.3.html)

Threads teilen sich: PID und Parent ID, Offene File Deskriptoren, Signal Handler, Terminal, Working Directory, CPU Zeit und konsumierte Ressourcen, Limiten für Ressourcen.

Threads erhalten separat: Thread ID, Signal Maske, errno Variable, Stack.

**Mutex**

Mutex = Mutual Exclusion (Gegenseitiger Ausschluss)

Critical Section = Derselbe Code, der wenn mehrmalig parallel ausgeführt zu Fehlern führt. 

Mutex locken: [pthread_mutex_lock](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_lock.html)

Falls die Mutex Sperre zu ist, blockiert `pthread_mutex_lock()`

Mutex unlocken: [pthread_mutex_unlock](https://linux.die.net/man/3/pthread_mutex_unlock)

Check if mutex locked: [pthread_mutex_trylock](http://man7.org/linux/man-pages/man3/pthread_mutex_trylock.3p.html) (returns `EBUSY` if already locked)

Timed lock: [pthread_mutex_timedlock](http://man7.org/linux/man-pages/man3/pthread_mutex_timedlock.3p.html)

```C
const struct timespec *t = {1, 0}; // 1s + 0ns
int pthread_mutex_timedlock(mutex, t); // (returns ETIMEDOUT after timeout)
```

Mutex Beispiel: http://man7.org/tlpi/code/online/dist/threads/thread_incr_mutex.c.html

**Pipes**

Create a pipe: [pipe](http://man7.org/linux/man-pages/man2/pipe.2.html)

```C
int fd[2];
pipe(fd);
```

Two file descriptors will be created and communication flows from `fd[1]` to `fd[0]`. Usually this call is followed by a fork.

Create a named pipe (FIFO): [mkfifo](http://man7.org/linux/man-pages/man3/mkfifo.3.html)

This will create a file annotated with the `p` when using `ls -la`. This file can now be opened by one process with `O_RDONLY` and by another process with `O_WRONLY`. Open blocks until both ends are opened.