# Linux System Calls 4 IPC Terminals

**Terminals**

TTY := Teletype

PTY := Pseudoterminal (master an subordinate device bidirectionally connected through an IPC channel)

Canonical mode := row-wise (i.e. input can be edited before being processed until: NL, EOL, EOL2, EOF, CR occurs)

Noncanonical mode := character-wise

Escape Sequence Library for Linux: [ncurses](http://man7.org/linux/man-pages/man3/ncurses.3x.html)

Introduction to the Unix Curses Library: [curses.pdf](http://heather.cs.ucdavis.edu/~matloff/UnixAndC/CLanguage/Curses.pdf)

Tutorial: [Games with ncurses](https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/)

Check if `fd` is a terminal: [isatty](http://man7.org/linux/man-pages/man3/isatty.3.html)

Get TTY name of an `fd`: [ttyname](http://man7.org/linux/man-pages/man3/ttyname.3.html)

Read terminal attributes: [tcgetattr](http://man7.org/linux/man-pages/man3/tcgetattr.3p.html)

Set terminal attributes: [tcsetattr](http://man7.org/linux/man-pages/man3/tcsetattr.3p.html) (always initialise t with `tcgetattr()`)

```C
struct termios {
    tcflag_t c_iflag; // Input Modes
    tcflag_t c_oflag; // Output Modes
    tcflag_t c_cflag; // Control Modes
    tcflag_t c_lflag; // Local Modes
    cc_t c_cc[NCCS];  // Special Characters
    … // Non-Standard Terminal Attribute
}
```

Command line tool to change terminal attributes: [stty](http://man7.org/linux/man-pages/man1/stty.1.html)

Example for turning off echo flag:
```C
struct termios tp, save;
tcgetattr(STDIN_FILENO, &tp);
save = tp;
tp.c_lflag &= ~ECHO;
tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp); // echo turned off
tcsetattr(STDIN_FILENO, TCSANOW, &save); // restore attributes
```

**Change Terminal In/Output Speed**

[cfgetispeed](http://man7.org/linux/man-pages/man3/cfgetispeed.3p.html)

[cfgetospeed](http://man7.org/linux/man-pages/man3/cfgetospeed.3p.html)

[cfsetispeed](http://man7.org/linux/man-pages/man3/cfsetispeed.3p.html)

[cfsetospeed](http://man7.org/linux/man-pages/man3/cfsetospeed.3p.html)

**Other Stuff**

send `0 (BREAK)` to `fd` for `duration` milliseconds: [tcsendbreak](http://man7.org/linux/man-pages/man3/tcsendbreak.3.html)

Block until terminal output queue sent: [tcdrain](http://man7.org/linux/man-pages/man3/tcdrain.3.html)

Flush in/output queues: [tcflush](http://man7.org/linux/man-pages/man3/tcflush.3.html)

Manage Flow-Control: [tcflow](http://man7.org/linux/man-pages/man3/tcflow.3.html) (Action `TCOON|OFF`, `TCION|OFF`)

Get current window size: [ioctl](http://man7.org/linux/man-pages/man2/ioctl.2.html)

```C
struct winsize {
    unsigned short ws_row, ws_col; // Linux
    unsigned short ws_xpixel, ws_ypixel;
};
```

If the window size changes, the `SIGWINCH` signal is dispatched.