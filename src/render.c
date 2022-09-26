/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:03:51 by Vitor             #+#    #+#             */
/*   Updated: 2022/09/26 15:10:21 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	my_mlx_pixelput(t_data *data, int x, int y, int color);
int	render_fractol(t_data *data, int imaginary, int real)
{
	t_complex	c;
	int			i_pos;
	int			r_pos;
	int 		depth;
	int			iterations;
	double hue;
	int saturation;
	int value;

	data->mlx.img = mlx_new_image(data->mlx.instance, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
	
	value = 255;
	saturation = 255;
	i_pos = imaginary;
	iterations = 1000;
	while(i_pos < HEIGHT)
	{
		r_pos = real;
		c.i = data->points.min_r + i_pos * (data->points.max_r - data->points.min_r) / HEIGHT; // posicao real de C de acordo com o tamanho de pixels + o tamanho no plano (-2.0 ate 1.0, diminuindo 0.3 (distancia entre os pontos / largura) a cada passada ());
		while(r_pos < WIDTH)
		{
			c.r = data->points.min_i + r_pos * (data->points.max_i - data->points.min_i) / WIDTH; // posicao imaginaria do C de acordo com tamanho de pixels e a posicao do plano (-1.5 a 1.5) diminuindo 0.3 (distancia entre os pontos / altura) a cada passada;
			//o real ira andar para a direita, ate o final da linha, pois o eixo eh horizontal e vai da esquerda pra direita
			if (mandelbrot(c.r, c.i, iterations) < iterations)
			{
				depth = mandelbrot(c.r, c.i, iterations);
				hue = (255.0 * depth / iterations);
				my_mlx_pixelput(data, r_pos, i_pos, rgb_to_int(depth, depth, depth));
			}
			else
				my_mlx_pixelput(data, r_pos, i_pos, 000000);
			r_pos++;
		}
		// o imaginario quebra a linha pois o eixo eh vertical e vai descendo
		i_pos++;
	}
	mlx_put_image_to_window(data->mlx.instance, data->mlx.win, 	data->mlx.img, 0, 0);
	return (0);
}

void	my_mlx_pixelput(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	hsv_to_rgb(double h, double s, double v)
{
	double M;
	double m;

	double r;
	double g;
	//double b;

	M = 255 * v;
	m = M*(1-s);

	if (h > 0 && h < 60)
	{

	}
	else if (h > 60 && h < 120)
	{

	}
	else if (h > 120 && h < 180)
	{

	}
	else if (h > 180 && h < 240)
	{

	}
	else if (h > 240 && h < 300)
	{

	}
	else if (h > 300 && h < 360)
	{
		r = M;
		g = m;
	}
}

void	get_hsv(double iterations, double max)
{
	double h;
	double s;
	double v;

	
	s = 1;
	v =	1.0 * (iterations / max);
	h = 360.0 * (iterations / max);
	
	hsv_to_rgb(h, s, v);
}
