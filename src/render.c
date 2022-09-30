/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:03:51 by Vitor             #+#    #+#             */
/*   Updated: 2022/09/30 05:33:44 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	render_fractol(t_data *data)
{
	t_complex	c;
	int			iterations;
	int			i_pos;
	int			r_pos;
	
	mlx_clear_window(data->mlx.instance, data->mlx.win);
	i_pos = 0;
	while(i_pos < HEIGHT)
	{
		r_pos = 0;
		c.i = data->points.min_i + i_pos * (data->points.max_i - data->points.min_i) / HEIGHT; // posicao imaginaria de C de acordo com o tamanho de pixels + o tamanho no plano (-2.0 ate 1.0, diminuindo 0.3 (distancia entre os pontos / largura) a cada passada ());
		while(r_pos < WIDTH)
		{
			c.r = data->points.min_r + r_pos * (data->points.max_r - data->points.min_r) / WIDTH; // posicao imaginaria do C de acordo com tamanho de pixels e a posicao do plano (-1.5 a 1.5) diminuindo 0.3 (distancia entre os pontos / altura) a cada passada;
			//o real ira andar para a direita, ate o final da linha, pois o eixo eh horizontal e vai da esquerda pra direita
			iterations = mandelbrot(c.r, c.i, data->max);
			if (iterations < data->max)
				my_mlx_pixel_put(data, r_pos, i_pos, get_hsv(iterations, data->max));
			else
				my_mlx_pixel_put(data, r_pos, i_pos, 000000);
			r_pos++;
		}
		i_pos++;
	}
	mlx_put_image_to_window(data->mlx.instance, data->mlx.win, 	data->mlx.img, 0, 0);
}

void	render_julia(t_data *data)
{
	t_complex	z;
	int			iterations;
	int			i_pos;
	int			r_pos;
	
	mlx_clear_window(data->mlx.instance, data->mlx.win);
	i_pos = 0;
	while(i_pos < HEIGHT)
	{
		r_pos = 0;
		z.i = data->points.min_i + i_pos * (data->points.max_i - data->points.min_i) / HEIGHT; // posicao imaginaria de C de acordo com o tamanho de pixels + o tamanho no plano (-2.0 ate 1.0, diminuindo 0.3 (distancia entre os pontos / largura) a cada passada ());
		while(r_pos < WIDTH)
		{
			z.r = data->points.min_r + r_pos * (data->points.max_r - data->points.min_r) / WIDTH; // posicao imaginaria do C de acordo com tamanho de pixels e a posicao do plano (-1.5 a 1.5) diminuindo 0.3 (distancia entre os pontos / altura) a cada passada;
			//o real ira andar para a direita, ate o final da linha, pois o eixo eh horizontal e vai da esquerda pra direita
			iterations = juliaset(z, data->max);
			if (iterations < data->max)
				my_mlx_pixel_put(data, r_pos, i_pos, get_hsv(iterations, data->max));
			else
				my_mlx_pixel_put(data, r_pos, i_pos, 000000);
			r_pos++;
		}
		i_pos++;
	}
	mlx_put_image_to_window(data->mlx.instance, data->mlx.win, 	data->mlx.img, 0, 0);
}

int	get_hsv(int iterations, int max)
{
	double h;
	double s;
	double v;

	h = 360 * iterations / max;
	s = 1;
	v = 1;
	return (hsv_to_rgb(h, s, v));
}

int	hsv_to_rgb(double h, double s, double v)
{
	int M;
	int m;
	int z;
	int rgb;

	M = 255 * v;
	m = M * (1 - s);
	z = (M-m) * (1 - abs(((int)h/60) % 2 - 1));

	rgb = 0;
	if (h >= 0 && h < 60)
		rgb = M << 16 | (z + m) << 8 | m;
	else if (h >= 60 && h < 120)
		rgb = (z + m) << 16 | M << 8 | m;
	else if (h >= 120 && h < 180)
		rgb = m << 16 | M << 8 | z + m;
	else if (h >= 180 && h < 240)
		rgb = m << 16 | (z + m) << 8 | M;
	else if (h >= 240 && h < 300)
		rgb = (z + m) << 16 | m << 8 | M;
	else if (h >= 300 && h < 360)
		rgb = M << 16 | m << 8 | z + m;
	return (rgb);
}
