#include <stdio.h>
#include <unistd.h>

int main(void) {
	enum {
		S_PA0, // after single \n
		S_PAR, // after multiple \n
		S_TXT, // within a word
		S_XPA, // after escaped \n
		S_SPA, // after single or multiple space
		S_ESC, // after \e but before \n
	} state = S_PAR;
	char buf;
	while (1) {
		ssize_t res = read(0, &buf, 1);
		if (res < 0) {
			perror("read(3)");
			return 1;
		}
		if (res == 0)
			break;
		switch (buf) {
			case ' ':
			case '\t':
				switch (state) {
					case S_ESC: fprintf(stderr, "Space after S_ESC\n"); break;
					case S_TXT: state = S_SPA; break;
					default: break;
				}
				break;
			case '\e':
				switch (state) {
					case S_PA0:
					case S_TXT:
					case S_SPA: state = S_ESC; break;
					default: break;
				}
				break;
			case '\n':
				switch (state) {
					case S_PA0:
					case S_XPA: putchar('\n'); state = S_PAR; break;
					case S_TXT:
					case S_SPA: state = S_PA0; break;
					case S_ESC: state = S_XPA; break;
					default: break;
				}
				break;
			default:
				switch (state) {
					case S_PA0:
					case S_XPA:
					case S_SPA: putchar(' ');
					default: putchar(buf); state = S_TXT; break;
				}
				break;
			case '\x05': putchar('\n'); state = S_PAR; break;
		}
	}
	return 0;
}
