#include <ncurses.h>
#include <unistd.h>

#define DELAY 35000

/* ======================
 * Source:
 * https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/
 * ======================
 */

int main(int argc, char *argv[]) {
	int x = 0,
			y = 0;

	int max_x = 0,
			max_y = 0;

	int next_x = 0;

	int direction = 1;

	initscr();
	noecho();
	curs_set(FALSE);

	getmaxyx(stdscr, max_y, max_x);

	x = max_x / 2;
	y = max_y / 2;

	while (1) {
		getmaxyx(stdscr, max_y, max_x);

		y = max_y / 2;

		clear();
		mvprintw(y, x, "o");
		refresh();

		usleep(DELAY);

		next_x = x + direction;

		if (next_x >= max_x || next_x < 0) {
			direction*= -1;
		} else {
			x+= direction;
		}

	}

	endwin();

	return 0;
}