/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:03:51 by Vitor             #+#    #+#             */
/*   Updated: 2022/09/26 18:55:09 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	render_fractol(t_data *data, int imaginary, int real)
{
	t_complex	c;
	int			i_pos;
	int			r_pos;
	int 		depth;
	int			iterations;

	data->mlx.img = mlx_new_image(data->mlx.instance, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
	
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
				my_mlx_pixel_put(data, r_pos, i_pos, get_hsv(depth, iterations));
			}
			else
				my_mlx_pixel_put(data, r_pos, i_pos, 000000);
			r_pos++;
		}
		// o imaginario quebra a linha pois o eixo eh vertical e vai descendo
		i_pos++;
	}
	mlx_put_image_to_window(data->mlx.instance, data->mlx.win, 	data->mlx.img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int check_negative(int number)
{
	if (number < 0)
		return (number *= -1);
	return (number);
}

int	hsv_to_rgb(double h, double s, double v)
{
	int M;
	int m;
	int z;

	// double r;
	// double g;
	// double b;
	int rgb;

	M = 255 * v;
	m = M * (1 - s);
	z = (M-m) * (1 - check_negative(h/60) % 2 - 1);

	// r = 0;
	// g = 0;
	// b = 0;
	rgb = 0;
	if (h >= 0 && h < 60)
	{
		//r = M;
		//g = z + m; 
		//b = m;
		rgb = (M << 16); 
		rgb += (z + m) << 8;
		rgb += m;
	}
	else if (h >= 60 && h < 120)
	{
		// r = z + m;
		// g = M;
		// b = m;
		rgb = (z + m) << 16; 
		rgb += M << 8;
		rgb += m;
	}
	else if (h >= 120 && h < 180)
	{
		// r = m;
		// g = M;
		// b = z + m;
		rgb = m << 16; 
		rgb += M << 8;
		rgb += z + m;
	}
	else if (h >= 180 && h < 240)
	{
		// r = m;
		// g = z + m;
		// b = M;
		rgb = m << 16; 
		rgb += (z + m) << 8;
		rgb += M;
	}
	else if (h >= 240 && h < 300)
	{
		// r = z + m;
		// g = m;
		// b = M;
		rgb = (z + m) << 16; 
		rgb += m << 8;
		rgb += M;
	}
	else if (h >= 300 && h < 360)
	{
		// r = M;
		// g = m;
		// b = z + m;
		rgb = M << 16; 
		rgb += m << 8;
		rgb += z + m;
	}
	// return (rgb_to_int(r, g, b));
	return (rgb);
}

int	get_hsv(double iterations, double max)
{
	double h;
	double s;
	double v;
	int converted;
	
	h = 360.0 * (iterations / max);
	s = 1;
	v = 1;
	
	converted = hsv_to_rgb(h, s, v);
	return (converted);
}
