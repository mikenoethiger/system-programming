**File I/O**

[open](http://man7.org/linux/man-pages/man2/open.2.html)

```C
fd = open(pathname, flags, mode); // -1: error
// e.g. rw-rw-rw- =>
mode_t mode =
S_IRUSR | S_IWUSR |
S_IRGRP | S_IWGRP |
S_IROTH | S_IWOTH;
```
[read](http://man7.org/linux/man-pages/man2/read.2.html)
```C
r = read(fd, buf, n); // r = 0: EOF, -1: error
```
[write](http://man7.org/linux/man-pages/man2/write.2.html)
```C
w = write(fd, buf, n); // w = -1: error
```
[close](http://man7.org/linux/man-pages/man2/close.2.html)
```C
result = close(fd);
```
Manipulate file descriptor: [fcntl](http://man7.org/linux/man-pages/man2/fcntl.2.html)

File Offset: [lseek](http://man7.org/linux/man-pages/man2/lseek.2.html)

Create tmp file: [mkstemp](http://man7.org/linux/man-pages/man3/mkstemp.3.html)

Delete name from filesystem: [unlink](http://man7.org/linux/man-pages/man2/unlink.2.html)

Create directory: [mkdir](http://man7.org/linux/man-pages/man2/mkdir.2.html)

Rename file/directory: [rename](http://man7.org/linux/man-pages/man2/rename.2.html)

Remove file/directory: [remove](http://man7.org/linux/man-pages/man3/mkstemp.3.html)

Remove ruft intern auf:

* [rmdir](http://man7.org/linux/man-pages/man2/rmdir.2.html) für Directories
* [unlink](http://man7.org/linux/man-pages/man2/unlink.2.html) für Files

**Prozesse & Signale**

Process ID: [getpid](http://man7.org/linux/man-pages/man2/getpid.2.html)

Init Prozess hat `PID=1`

Maximale Anzahl PID: `PID_MAX`

Parent Process ID: [getppid](http://man7.org/linux/man-pages/man2/getpid.2.html)

Prozess Tree anzeigen:

```
$ pstree
```

Environment variable (global): [environ](http://man7.org/linux/man-pages/man7/environ.7.html)

Get env variable: [getenv](http://man7.org/linux/man-pages/man3/getenv.3.html)

Set env variable: [putenv](http://man7.org/linux/man-pages/man3/putenv.3.html)

Umgebungsvariable eines Prozesses in Linux anzeigen:

```
$ sudo cat /proc/PID/environ
```
Heap Speicher allozieren: [malloc](http://man7.org/linux/man-pages/man3/malloc.3.html)

Heap Speicher freigeben: [free](http://man7.org/linux/man-pages/man3/malloc.3.html)

Get Program Break (Grenze des Heaps): [sbrk](http://man7.org/linux/man-pages/man2/brk.2.html)

Set Program Break: [brk](http://man7.org/linux/man-pages/man2/brk.2.html)

Speicher auf Stack allozieren: [alloca](http://man7.org/linux/man-pages/man3/alloca.3.html)

**Signale**

[Signals Übersicht](http://man7.org/linux/man-pages/man7/signal.7.html)

* Jedes Signal hat eine Nr. und ein `SIGxxxx` Symbol:
`#define SIGINT 2 // in signal.h`
* Standard Signale vom Kernel an den Prozess: `1-31`
* Daneben gibt es in Linux real-time Signale: `32-64`
* Für Anwendungs-spezifische Use Cases: `SIGRTMIN+n`
* Auf Signale sollte man immer per Symbol verweisen, weil sie je nach System verschiedene Nr. haben.

Blockierte Signale eines Prozesses anzeigen
```
$ cat /proc/PID/status # SigBlk
```
Signale bleiben pending bis sie entblockt werden
```
$ cat /proc/PID/status # SigPnd, ShdPnd
```

Signal Handler setzen: [signal](http://man7.org/linux/man-pages/man2/signal.2.html)
Signal Handle structure:

```C
void handle(int signal) { … }
```
Der return-Wert ist die vorherige Handler-Funktion
```C
old_handle = signal(SIGINT, handle); // save
signal(SIGINT, old_handle); // restore
```
Bei einem Fehler ist der return-Wert `SIG_ERR`
```C
result = signal(SIGINT, handle);
if (result == SIG_ERR) { … }
```
Für default Signal Handler, `SIG_DFL` installieren
```C
result = signal(SIGINT, SIG_DFL);
```
Signal ignorieren, d.h. Handler `SIG_IGN` installieren
```C
result = signal(SIGINT, SIG_IGN);
```
Signal an Prozess senden: [kill](http://man7.org/linux/man-pages/man2/kill.2.html)

* Falls pid = 0 ist, geht das Signal an alle in derselbenProzess-Gruppe, wie der aufrufende Prozess.
* Mit pid = -1 geht das Signal an alle Prozesse, an dieder Aufrufer Signale senden darf, ausser an init.
* Mit sig = 0 wird geprüft, ob Senden möglich ist.

Signal an den eigenen Prozess senden: [raise](http://man7.org/linux/man-pages/man3/raise.3.html)

Get Signal Beschreibung: [strsignal](http://man7.org/linux/man-pages/man3/strsignal.3.html)

Fehlermeldung `msg` gefolgt von Beschreibung von `sig` und `\n` auf stderror printen: [psignal](http://man7.org/linux/man-pages/man3/psignal.3.html)

Prozess suspendieren und auf Signal warten: [pause](http://man7.org/linux/man-pages/man2/pause.2.html)

**Prozess Lebenszyklen**
Neuen Prozess erstellen: [fork](http://man7.org/linux/man-pages/man2/fork.2.html)

Prozess beenden, Ressourcen freigeben: [exit](http://man7.org/linux/man-pages/man3/exit.3.html)

„Harsches“ exit: [_exit](http://man7.org/linux/man-pages/man2/_exit.2.html)

Auf Prozess Zustandsänderung warten: [wait](http://man7.org/linux/man-pages/man2/waitpid.2.html)

Bei normaler und abnormaler Prozess Termination (main Funktion ohne Rückgabewert) werden die offenen File Deskriptoren geschlossen, und File Locks und Speicher-Mappings freigegeben, sowie weitere Ressourcen im Zusammenhang mit Shared Memory, Semaphoren und Prozessgruppen.

Register exit handler: [atexit](http://man7.org/linux/man-pages/man3/atexit.3.html)

Handler werden in eine Liste eingefügt, und bei `exit()` in umgekehrter Registrationsreihenfolge aufgerufen. Der Handler bekommt den Exit status nicht mit, und sollte selber `exit()` auch nicht nochmal aufrufen.

Alternativer exit handler Registrierung: [on_exit](http://man7.org/linux/man-pages/man3/on_exit.3.html)

Immer wenn ein Child-Prozess terminiert, wird das `SIGCHLD` Signal wird zum Parent-Prozess gesendet.

[exec() Familie](http://man7.org/linux/man-pages/man3/exec.3.html)

Laufendes Programm ersetzen: [int result = execve(filepath, argv, envp)](http://man7.org/linux/man-pages/man2/execve.2.html)

Die PID des ausführenden Prozesses bleibt dieselbe.

Nützliche Alternative zu execve: [execlp](http://man7.org/linux/man-pages/man3/exec.3.html)

Das `l` bedeutet, dass die Argument-Liste "offen" ist: `execlp("curl", "-v", "foo.org", (char *) NULL)`. Das `p` bedeutet, dass das file im `$PATH` gesucht wird, wie in der Shell, wenn man keine `/` verwendet.

Set close-on-exit flag
```int flags = fcntl(fd, F_GETFD); // get flags
flags |= FD_CLOEXEC; // add close-on-exec
fcntl(fd, F_SETFD, flags); // set flags
```

Shell Kommandos ausführen: [int system(const char *cmd)](http://man7.org/linux/man-pages/man3/system.3.html)

Auf spezifischen Child warten: [pid_t waitpid(pid_t pid, int *wstatus, int options)](http://man7.org/linux/man-pages/man2/waitpid.2.html)