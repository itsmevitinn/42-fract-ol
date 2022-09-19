#include <stdio.h>
#include <math.h>

int mandelbrot(double c, int times);
int main(int argc, char **argv)
{
	int count_x;
	int count_y;
	double c;
	int x;
	int y;
	// double	min_r;
	// double max_r;
	// double min_i;
	// double max_i;
	// int cr;
	// int ci;
	// int zi;
	// int zr;
	// max_r = 1.0;
	// min_r = -2.0;
	// min_i = -1.5;
	// max_i = 1.5;
	// z = (zi + zr);
	c = -2;
	count_x = 0;
	x = 60; // -> real;
	y = 100; // -> imaginary;
	// count_y = 0;
	int times = 50;

	// ci = min_i + column * (max_i - min_i);
	// cr = min_r + line * (max_r - min_r);
	// cr = (cr + ci);	
	int checker = 0;
	while(count_x < x)
	{
		// count_y = 0;
		// while(count_y < y)
		// {
		checker = mandelbrot(c, times);
		c += 3.0 / 60; // divido por 3 por causa da distancia entre -2 e 1, e divido pela quantidade de x
		if (checker < times)
			printf(" ");
		else
			printf(".");
		// 	count_y++;
		// }
		count_x++;
	}
}

int mandelbrot(double c, int times)
{
	double z;
	int iterator = 0;

	z = 0;

	while(iterator < times)
	{
		z = (z * z) + c;
		if (sqrt(z * z) > 2)
			break;
		else
			iterator++;
	}
	return (iterator);
}
