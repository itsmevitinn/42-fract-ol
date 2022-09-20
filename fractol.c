#include "fractol.h"
#include <unistd.h>
int mandelbrot(double ci, double cr, int times);
int main(int argc, char **argv)
{
	int		line;
	int		column;
	double	cr;
	double	ci;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	int		largura;
	int		altura;
	min_r = -2.0;
	max_r = 1.0;
	min_i = -1.5;
	max_i = 1.5;
	largura = 100; // -> pixels largura;
	altura = 100; // -> pixels altura;

	line = 0;
	while(line < largura)
	{
		column = 0;
		ci = min_r + line * (max_r - min_r) / largura; // aqui eu decubro a posicao real de C de acordo com o tamanho de pixels;
		// o imaginario quebra a linha pois ele vai de cima para baixo, pq o eixo eh em pe
		while(column < altura)
		{
			cr = min_i + column * (max_i - min_i) / altura; // aqui eu descubro a posicao imaginaria do C de acordo com tamanho de pixels
			//aqui o real ira andar para a direita, ate o final da linha, pois o eixo eh horizontal e vai da esquerda pra direita
			if (mandelbrot(cr, ci, 200) == 0)
				write(1, " ", 1);
			else
				write(1, ".", 1);
			column++;
		}
		write(1, "\n", 1);
		line++;
	}
}

int mandelbrot(double cr, double ci, int times)
{
	double zr;
	double zi;
	double temp;
	int iterator; 

	iterator = 0;
	zr = 0;
	zi = 0;
	while(iterator < times)
	{
		if (sqrt(zr * zr + zi * zi) > 2) // checa se ira tender ao infinito
			return (0);
		temp = 2 * zr * zi + ci; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		zr = zr * zr - zi * zi + cr; //real ao quadrado + cr -> z(r)^2 + c(r)
		zi = temp;
		iterator++;
	}
	return (1);
}
