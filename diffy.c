#include <stdio.h>
#include <unistd.h>

int CanonicalToDiffy(void) {
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
						if (isdigit(buf) || islower(buf)) {
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
