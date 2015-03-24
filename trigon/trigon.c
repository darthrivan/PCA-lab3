#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define N 6000
#define PUNTS 1000
#define BUFFER_SIZE 5096

int main(int argc, char *argv[])
{
	unsigned int i, r, j, n;
	double d, x, y;

	double buffer[BUFFER_SIZE];
	int index = 0;

	double cosines[PUNTS];
	double sines[PUNTS];
	int computed[PUNTS];

	if (argc == 1) n = N; else n = atoi(argv[1]);

	srand(0);

		r = rand();
		for (j=0, d=0; j<PUNTS; j++)
		{
			x = cos(d);
			y = sin(d);
			// computed[j] = 1;
			cosines[j] = x;
			sines[j] = y;
			// write(1, &x, sizeof(double));
			// write(1, &y, sizeof(double));
			buffer[index++] = r*x;
			buffer[index++] = r*y;
			if (index >= BUFFER_SIZE) {
				write(1, buffer, BUFFER_SIZE*sizeof(double));
				index = 0;
			}
			d += 2*M_PI/PUNTS;
		}

	for (i=1; i<n; i++)
	{
		r = rand();
		for (j=0, d=0; j<PUNTS; j++)
		{
			x = cosines[j];
			y = sines[j];
			// write(1, &x, sizeof(double));
			// write(1, &y, sizeof(double));
			buffer[index++] = r*x;
			buffer[index++] = r*y;
			if (index >= BUFFER_SIZE) {
				write(1, buffer, BUFFER_SIZE*sizeof(double));
				index = 0;
			}
			d += 2*M_PI/PUNTS;
		}
	}
	write(1, buffer, index*sizeof(double));
	return 0;
}
