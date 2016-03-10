/* MARDALE Andrei-Iulian - 311CB */
#include "proc.h"

/*exit codes:
	3 - invalid argc
	2 - could not open file
	1 - could not allocate memory
*/

int main (int argc, char *argv[]) {
	if (argc < 3) {
		return 3;
	}
	
	FILE *in = fopen(argv[1], "r");
	if (!in) return 2;
	
	FILE *out = fopen(argv[2], "w");
	if (!out) {
		fclose(in);
		return 2;
	}
	
	int check = parse(in, out);
	if (check != 1) {
		fclose(in);
		fclose(out);
		return 1;
	}
	
	fclose(in);
	fclose(out);
	return 0;
}
