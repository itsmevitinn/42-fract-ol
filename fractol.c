/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/09/22 14:01:45 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int mandelbrot(double ci, double cr, int times);
int main(int argc, char **argv)
{
	t_positions points;
	t_complex c;
	int		height;
	int		width;
	int		i_pos;
	int		r_pos;

	argv = 0;
	if (argc != 1)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	points.min_r = -2.0;
	points.max_r = 1.0;
	points.min_i = -1.5;
	points.max_i = 1.5;
	width = 110; // -> pixels largura;
	height = 110; // -> pixels altura;
	i_pos = 0;
	while(i_pos < height)
	{
		r_pos = 0;
		c.i = points.min_r + i_pos * (points.max_r - points.min_r) / height; // posicao real de C de acordo com o tamanho de pixels + o tamanho no plano (-2.0 ate 1.0, diminuindo 0.3 (distancia entre os pontos / largura) a cada passada ());
		while(r_pos < width)
		{
			c.r = points.min_i + r_pos * (points.max_i - points.min_i) / width; // posicao imaginaria do C de acordo com tamanho de pixels e a posicao do plano (-1.5 a 1.5) diminuindo 0.3 (distancia entre os pontos / altura) a cada passada;
			//o real ira andar para a direita, ate o final da linha, pois o eixo eh horizontal e vai da esquerda pra direita
			if (mandelbrot(c.r, c.i, 200) == 0)
				write(1, " ", 1);
			else
				write(1, ".", 1);
			r_pos++;
		}
		write(1, "\n", 1);
		// o imaginario quebra a linha pois o eixo eh vertical e vai descendo
		i_pos++;
	}
}

int mandelbrot(double cr, double ci, int iterations)
{
	t_complex z;
	double temp;
	int counter; 
	double zrsqr;
	double zisqr;

	counter = 0;
	z.r = 0;
	z.i = 0;
	zrsqr = z.r * z.r;
	zisqr = z.i * z.i;
	while(counter < iterations)
	{
		if (sqrt(z.r * z.r + z.i * z.i) > 2) // checa se ira tender ao infinito
			return (0);
		temp = z.r * z.i * 2 + ci; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		z.r = z.r * z.r - z.i * z.i + cr; //real ao quadrado + cr -> z(r)^2 + c(r)
		//calcuo pra descobrir o quadrado de numeros complexos
		z.i = temp;
		counter++;
	}
	return (1);
}
