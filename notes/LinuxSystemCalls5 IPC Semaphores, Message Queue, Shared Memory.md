# Linux System Calls 5 IPC Semaphore, Message Queue, Shared Memory

IPC := Interprocess Communication

POSIX := Portable Operating System Interface

POSIX tools for IPC: Message Queues, Semaphore, Shared Memory

**Semaphores**

[Introduction POSIX Semaphore](http://users.cs.cf.ac.uk/Dave.Marshall/C/node26.html)

[Introduction POSIX Shared Memory](http://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html)

*compile semaphore programs with `-pthread` option*

[sem_open](http://man7.org/linux/man-pages/man3/sem_open.3.html)

[sem_close](http://man7.org/linux/man-pages/man3/sem_close.3.html)

[sem_unlink](http://man7.org/linux/man-pages/man3/sem_unlink.3.html)

[sem_wait](http://man7.org/linux/man-pages/man3/sem_wait.3.html) (blocking)

[sem_trywait](http://man7.org/linux/man-pages/man3/sem_trywait.3.html) (nonblocking)

[sem_timedwait](http://man7.org/linux/man-pages/man3/sem_timedwait.3.html) (with timeout)

[sem_post](http://man7.org/linux/man-pages/man3/sem_post.3.html) (increment semaphore)

[sem_getvalue](http://man7.org/linux/man-pages/man3/sem_getvalue.3.html)

[sem_init](http://man7.org/linux/man-pages/man3/sem_init.3.html) (init unnamed semaphore)

[sem_destroy](http://man7.org/linux/man-pages/man3/sem_destroy.3.html) (specifically for unnamed semaphores, makes `sem_close` and `sem_unlink` obsolete because there is no file descriptor)

Unnamed semaphores are often used between threads of the same process, or parent child processes because they are easier to manage because no name is required.

```C
struct timespec {
    time_t tv_sec; // seconds
    long tv_nsec;  // nanoseconds
}; // seconds+nanoseconds
```

**Message Queues**
[mq_open](http://man7.org/linux/man-pages/man3/mq_open.3.html)

[mq_setattr](http://man7.org/linux/man-pages/man3/mq_setattr.3.html)

[mq_getattr](http://man7.org/linux/man-pages/man3/mq_getattr.3.html)

[mq_receive](http://man7.org/linux/man-pages/man3/mq_receive.3.html)

[mq_send](http://man7.org/linux/man-pages/man3/mq_send.3.html)

[mq_close](http://man7.org/linux/man-pages/man3/mq_close.3.html) (releases file descriptor but doesn’t delete message queue)

[mq_unlink](http://man7.org/linux/man-pages/man3/mq_unlink.3.html) (deletes message queue as soon as no descriptor references it)

[mq_notify](http://man7.org/linux/man-pages/man3/mq_notify.3.html) (register calling process for a notification on the first message, has to be repeated for every notification)

[sigevent](http://man7.org/linux/man-pages/man7/sigevent.7.html)

```C
struct sigevent {
    int sigev_notify;     // SIGEV_NONE|SIGNAL|THREAD
    int sigev_signo;      // Notification Signal
    union sigval sigev_value; // Übergebene Daten
    void (*sigev_notify_function) (union sigval);
    void *sigev_notify_attributes; // Thread attr
    pid_t sigev_notify_thread_id;  // Thread ID
}; // SIGEV_THREAD => wie pthread_create()
union sigval {
    int sival_int; 
    void *sival_ptr;
};
```

```C
struct mq_attr {
    long mq_flags;   // Ignoriert bei mq_open()
    long mq_maxmsg;  // Max. Anzahl Messages
    long mq_msgsize; // Message Grösse in Bytes
    long mq_curmsgs; // Aktuelle Anz. Messages,
}; // ignoriert bei mq_open()
```

Mount virtual filesystem for linux message queues, in order to list queues/messages using `ls` program:

```bash
$ mkdir /dev/mqueue
$ sudo mount -t mqueue none /dev/mqueue
$ exit
$ ls -ld /dev/mqueue
$ cat /dev/mqueue/my_mq
```

**Shared Memory**

[shm_open](http://man7.org/linux/man-pages/man3/shm_open.3.html) (initialises shared memory of size 0)

[ftruncate](http://man7.org/linux/man-pages/man3/ftruncate.3p.html) (set shared memory size)

[mmap](http://man7.org/linux/man-pages/man2/mmap.2.html) (map shared memory to process memory, you can write to the addr argument after this call)

[shm_unlink](http://man7.org/linux/man-pages/man3/shm_unlink.3.html) (removes name while object remains alive until every process released it with `munmap()`)

[munmap](http://man7.org/linux/man-pages/man3/munmap.3p.html)

