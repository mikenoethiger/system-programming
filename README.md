# About

This is a collection of C programs, notes and exams that aggregated during the system programming lectures.
These programs are about the linux programming interface.
Error handling has been largely neglected, the programs are reduced to the very fundamental api calls, aiming to get a better grasp of the linux programming interface itself.

# Build

The programs are located in the `src` directory. 

The basic pattern to compile a single program with [gcc](https://gcc.gnu.org/) is as follows:

```
gcc src_file.c -o executable_file
```

This will compile `src_file.c` and generate an executable file called `executable_file` in the same directory. Execute it with `./executable_file`.

A `makefile` is present to compile **all** programs at once to `src/out`:

```
cd src
make
```

Single programs can be compiled using their names:

```
make time1
```

Depending on your operating system, you might miss some libraries that are necessary for a few programs.
E.g., OS X does not provide POSIX `mqueue.h`, thus the message queue programs won't compile on OS X.
Therefore, our lecturer suggested to work on a Raspberry Pi using a linux distribution.
An alternative way is to compile and execute the programs in a docker container.
You can find a `Dockerfile` in this repository which uses an ubuntu image and install the `gcc` compiler, `make`, the `libc` library and the `libncurses` library (all things you need throughout the lecture).

Build the image using the provided shell script:
```
chmod u+x docker-build.sh
./docker-build.sh
```

Afterwards, start a container (this will directly connect you to the container, so you can start hacking):
```
chmod u+x docker-start.sh
./docker-start.sh
```
All files/directories from your working directory will be synced with the container, so you can edit on your computer and compile/execute in the container.
Run `exit` when connected to the container to terminate the session.

# Notes

Lecture notes can be found in markdown format in `./notes`. 
These notes largely consist of links to the man pages of system calls but sometimes also provide complementary comments and usage examples.

Direct Links:
* [LinuxSystemCalls1 File IO, Processes.md](https://github.com/mikenoethiger/system-programming/blob/master/notes/LinuxSystemCalls1%20File%20IO%2C%20Processes.md)
* [LinuxSystemCalls2 Threads, Mutex, Pipes.md](https://github.com/mikenoethiger/system-programming/blob/master/notes/LinuxSystemCalls2%20Threads%2C%20Mutex%2C%20Pipes.md)
* [LinuxSystemCalls3 IPC Sockets.md](https://github.com/mikenoethiger/system-programming/blob/master/notes/LinuxSystemCalls3%20IPC%20Sockets.md)
* [LinuxSystemCalls4 IPC Terminals.md](https://github.com/mikenoethiger/system-programming/blob/master/notes/LinuxSystemCalls4%20IPC%20Terminals.md)
* [LinuxSystemCalls5 IPC Semaphores, Message Queue, Shared Memory.md](https://github.com/mikenoethiger/system-programming/blob/master/notes/LinuxSystemCalls5%20IPC%20Semaphores%2C%20Message%20Queue%2C%20Shared%20Memory.md)
* [LinuxSystemCalls6 Time.md](https://github.com/mikenoethiger/system-programming/blob/master/notes/LinuxSystemCalls6%20Time.md)

# Exams

You can find both of my exams (autumn semester 2019) in the `./exams` directory.

# Collaboration

I advocate sharing of knowledge, you are free to fork, edit and redistribute this repository.
Make sure to send me back your changes/additions as a pull request, such that future students can benefit too.