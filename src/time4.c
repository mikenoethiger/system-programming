#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

/* =============================================
 * Syspr13Assessment_4ibb1, 10)
 * Schreiben Sie ein Programm, das "gestern",
 * 00:00:00 als Datum ausgibt. Der Output des
 * Programms soll so aussehen, mit dem aktuellen
 * Datum, im Default-Format:
 * $ ./yesterday
 * today: Sun Jun 2 16:40:44 2019
 * yesterday: Sat Jun 1 00:00:00 2019
 * =============================================
 */


int main() {
	// Idee:
	// 1. time_t t, struct tm broken
	// 2. time(&t)
	// 3. print ctime(&t)
	// 4. broken = localtime(&t)
	// 5. broken.mday -= 1
	//    broken.tm_sec = 0
	//    broken.tm_min = 0
	//    broken.tm_hour = 0
	// 6. t = mktime(broken)
	// 7. print ctime(&t)

	time_t t;
	struct tm tm;
	time(&t);
	printf("today: %s\n", ctime(&t));
	tm = *localtime(&t);
	tm.tm_mday -= 1;
	tm.tm_sec = 0;
	tm.tm_min = 0;
	tm.tm_hour = 0;
	t = mktime(&tm);
	printf("yesterday: %s\n", ctime(&t));

	return 0;
}