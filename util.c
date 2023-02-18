#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int diffy(void) {
	enum {
		S_XX, // init
		S_PU, // after [.?:;]
		S_PS, // after [.?:;]	<SP>
		S_LP, // after )
		S_LS, // after )	<SP>
		S_SP, // after  	<SP>
		S_SR, // after  	<SP>(
	} state = S_XX;
	char buf;
	while (1) {
		ssize_t res = read(0, &buf, 1);
		if (res < 0) {
			perror("read(3)");
			return 1;
		}
		if (res == 0)
			break;
		switch (state) {
			case S_XX:
				switch (buf) {
					case '.':
					case '?':
					case ':':
					case ';': putchar(buf); state = S_PU; break;
					case ' ': state = S_SP; break;
					case ')': putchar(buf); state = S_LP; break;
					default: putchar(buf); break;
				}
				break;
			case S_PU:
				switch (buf) {
					case '.':
					case '?':
					case ':':
					case ';': putchar(buf); break;
					case ' ': state = S_PS; break;
					case ')': putchar(buf); state = S_LP; break;
					default: putchar(buf); state = S_XX; break;
				}
				break;
			case S_PS:
				switch (buf) {
					case '.':
					case '?':
					case ':':
					case ';': putchar(' '); putchar(buf); state = S_PU; break;
					case ' ': break;
					case '(': state = S_SR; break;
					case ')': putchar(buf); state = S_LP; break;
					default:
						if (!isdigit(buf) && !islower(buf)) {
							putchar('\n');
						} else {
							putchar(' ');
						}
						putchar(buf);
						state = S_XX;
						break;
				}
				break;
			case S_LP:
				switch (buf) {
					case '.':
					case '?':
					case ':':
					case ';': putchar(buf); state = S_PU; break;
					case ' ': state = S_LS; break;
					case ')': putchar(buf); break;
					default: putchar(buf); state = S_XX; break;
				}
				break;
			case S_LS:
				switch (buf) {
					case '.':
					case '?':
					case ':':
					case ';': putchar(' '); putchar(buf); state = S_PU; break;
					case ' ': break;
					case '(': state = S_SR; break;
					case ')': putchar(' '); putchar(buf); state = S_LP; break;
					default:
						if (isupper(buf)) {
							putchar('\n');
						} else {
							putchar(' ');
						}
						putchar(buf);
						state = S_XX;
						break;
				}
				break;
			case S_SP:
				switch (buf) {
					case '.':
					case '?':
					case ':':
					case ';': putchar(' '); putchar(buf); state = S_PU; break;
					case ' ': break;
					case '(': state = S_SR; break;
					case ')': putchar(' '); putchar(buf); state = S_LP; break;
					default: putchar(' '); putchar(buf); state = S_XX; break;
				}
				break;
			case S_SR:
				switch (buf) {
					case '.':
					case '?':
					case ':':
					case ';': putchar(' '); putchar('('); putchar(buf); state = S_PU; break;
					case ' ': putchar(' '); putchar('('); state = S_SP; break;
					case '(':
					case ')': putchar(' '); putchar('('); putchar(buf); state = S_XX; break;
					default:
						if (isupper(buf)) {
							putchar('\n');
						} else {
							putchar(' ');
						}
						putchar('(');
						putchar(buf);
						state = S_XX;
						break;
				}
				break;
		}
	}
    return 0;
}

int canon(void) {
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

int main(int argc, char *argv[]) {
    if (argc == 1)
        goto usage;

    if (!strcmp(argv[1], "canon"))
        return canon();
    if (!strcmp(argv[1], "diffy"))
        return diffy();

usage:
    fprintf(stderr, "Usage: %s <canon|diffy>\n", argv[0]);
    return 2;
}
