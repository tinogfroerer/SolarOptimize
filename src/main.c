#include <stdio.h>

#include "soltrack.h"

int main(int argc, char **argv)
{
	soltrack_init(-45.0, 45.0);
	
	printf("TILT:\n");
	print_tilt();
	printf("\nVECTOR:\n");
	print_orth_with_spin();
	
	return 0;
}
