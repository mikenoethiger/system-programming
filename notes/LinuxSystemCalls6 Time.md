# Linux System Calls 6 Time

[gettimeofday](http://man7.org/linux/man-pages/man2/gettimeofday.2.html) (get time in seconds and milliseconds)

[time](http://man7.org/linux/man-pages/man2/time.2.html) (get time in seconds)

[ctime](http://man7.org/linux/man-pages/man3/ctime.3.html) (time_t to string)

[gmtime](http://man7.org/linux/man-pages/man3/gmtime_r.3p.html) (time_t to broken-down UTC time)

[localtime](http://man7.org/linux/man-pages/man3/localtime.3p.html) (time_t to broken-down local time)

[mktime](http://man7.org/linux/man-pages/man3/mktime.3p.html) (broken-down time to time_t)

[asctime](http://man7.org/linux/man-pages/man3/asctime.3.html) (broken-down time to string)

[strftime](http://man7.org/linux/man-pages/man3/strftime.3.html) (broken-down time to string formatted, e.g. [ISO Date](https://en.wikipedia.org/wiki/ISO_8601) "%Y-%m-%dT%H:%M:%SZ")

[strptime](http://man7.org/linux/man-pages/man3/strptime.3.html) (string to broken-down time)

[zdump](http://man7.org/linux/man-pages/man8/zdump.8.html) (timezone dumper command line tool)

[times](http://man7.org/linux/man-pages/man2/times.2.html) 

**Show local time**

```bash
$ zdump /etc/localtime
```

**Structs**

```C
struct timeval { 
   time_t tv_sec;    /* seconds */
   suseconds_t tv_usec; /* microseconds */
}
```

```C
struct tm { 
   int tm_sec;  // Sekunden [0..60]
   int tm_min;  // Minuten [0..59]
   int tm_hour; // Stunde [0..23]
   int tm_mday; // Tag im Monat [1..31]
   int tm_mon;  // Monat im Jahr [0..11]
   int tm_year; // Jahre seit 1900
   int tm_wday; // Wochentag [0..6], So = 0
   int tm_yday; // Tag im Jahr [0..365]
   int tm_isdst; // Daylight Saving Time Flag
}
```