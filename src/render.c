/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:03:51 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/01 05:48:45 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	render_mandel_or_ship(t_data *data)
{
	t_complex	c;
	int			iterations;

	mlx_clear_window(data->mlx.instance, data->mlx.win);
	data->x_pos = 0;
	while (data->x_pos < HEIGHT)
	{
		data->y_pos = 0;
		c.i = data->points.min_i + data->x_pos * (data->points.max_i - data->points.min_i) / HEIGHT;
		while (data->y_pos < WIDTH)
		{
			c.r = data->points.min_r + data->y_pos * (data->points.max_r - data->points.min_r) / WIDTH;
			iterations = equation_m_b(c, data);
			if (iterations < data->max)
				my_mlx_pixel_put(data, data->y_pos, data->x_pos, get_hsv(iterations, data->max));
			else
				my_mlx_pixel_put(data, data->y_pos, data->x_pos, 000000);
			data->y_pos++;
		}
		data->x_pos++;
	}
	mlx_put_image_to_window(data->mlx.instance, data->mlx.win, data->mlx.img, 0, 0);
}

void	render_julia(t_data *data)
{
	t_complex	z;
	int			iterations;

	mlx_clear_window(data->mlx.instance, data->mlx.win);
	data->x_pos = 0;
	while (data->x_pos < HEIGHT)
	{
		data->y_pos = 0;
		z.i = data->points.min_i + data->x_pos * (data->points.max_i - data->points.min_i) / HEIGHT;
		while (data->y_pos < WIDTH)
		{
			z.r = data->points.min_r + data->y_pos * (data->points.max_r - data->points.min_r) / WIDTH;
			iterations = equation_j(z, data);
			if (iterations < data->max)
				my_mlx_pixel_put(data, data->y_pos, data->x_pos, get_hsv(iterations, data->max));
			else
				my_mlx_pixel_put(data, data->y_pos, data->x_pos, 000000);
			data->y_pos++;
		}
		data->x_pos++;
	}
	mlx_put_image_to_window(data->mlx.instance, data->mlx.win, data->mlx.img, 0, 0);
}

int	get_hsv(int iterations, int max)
{
	double	h;
	double	s;
	double	v;

	h = 360 * iterations / max;
	s = 1;
	v = 1;
	return (hsv_to_rgb(h, s, v));
}

int	hsv_to_rgb(double h, double s, double v)
{
	int	max;
	int	m;
	int	z;
	int	rgb;

	max = 255 * v;
	m = max * (1 - s);
	z = (max - m) * (1 - abs(((int)h / 60) % 2 - 1));
	rgb = 0;
	if (h >= 0 && h < 60)
		rgb = max << 16 | (z + m) << 8 | m;
	else if (h >= 60 && h < 120)
		rgb = (z + max) << 16 | max << 8 | m;
	else if (h >= 120 && h < 180)
		rgb = m << 16 | max << 8 | z + m;
	else if (h >= 180 && h < 240)
		rgb = m << 16 | (z + m) << 8 | max;
	else if (h >= 240 && h < 300)
		rgb = (z + m) << 16 | m << 8 | max;
	else if (h >= 300 && h < 360)
		rgb = max << 16 | m << 8 | z + m;
	return (rgb);
}
