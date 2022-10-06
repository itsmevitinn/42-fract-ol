/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:03:51 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/03 12:24:14 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	render_mandel(t_data *dt)
{
	t_complex	c;
	int			i;

	mlx_clear_window(dt->init, dt->win);
	dt->x_pos = 0;
	while (dt->x_pos < HEIGHT)
	{
		dt->y_pos = 0;
		c.i = dt->max_i - (dt->x_pos / HEIGHT) * (dt->max_i - dt->min_i);
		while (dt->y_pos < WIDTH)
		{
			c.r = dt->min_r + (dt->y_pos / WIDTH) * (dt->max_r - dt->min_r);
			i = equation_m(c, dt);
			if (i < dt->max)
				my_mlx_pixel_put(dt, dt->y_pos, dt->x_pos, get_hsv(i, dt->max));
			else
				my_mlx_pixel_put(dt, dt->y_pos, dt->x_pos, 000000);
			dt->y_pos++;
		}
		dt->x_pos++;
	}
	mlx_put_image_to_window(dt->init, dt->win, dt->img, 0, 0);
}

void	render_julia(t_data *dt)
{
	t_complex	z;
	int			i;

	mlx_clear_window(dt->init, dt->win);
	dt->x_pos = 0;
	while (dt->x_pos < HEIGHT)
	{
		dt->y_pos = 0;
		z.i = dt->max_i - (dt->x_pos / HEIGHT) * (dt->max_i - dt->min_i);
		while (dt->y_pos < WIDTH)
		{
			z.r = dt->min_r + (dt->y_pos / WIDTH) * (dt->max_r - dt->min_r);
			i = equation_j(z, dt);
			if (i < dt->max)
				my_mlx_pixel_put(dt, dt->y_pos, dt->x_pos, get_hsv(i, dt->max));
			else
				my_mlx_pixel_put(dt, dt->y_pos, dt->x_pos, 000000);
			dt->y_pos++;
		}
		dt->x_pos++;
	}
	mlx_put_image_to_window(dt->init, dt->win, dt->img, 0, 0);
}

int	get_hsv(int iterations, int max)
{
	t_hsv	hsv;

	hsv.h = 360.0 * iterations / max;
	hsv.s = 1;
	hsv.v = 0.5 * (iterations / max) + 0.5;
	return (hsv_to_rgb(hsv));
}

int	hsv_to_rgb(t_hsv hsv)
{
	int	max;
	int	m;
	int	z;
	int	rgb;

	max = 255 * hsv.v;
	m = max * (1 - hsv.s);
	z = (max - m) * (1 - abs(((int)hsv.h / 60) % 2 - 1));
	rgb = 0;
	if (hsv.h >= 0 && hsv.h < 60)
		rgb = max << 16 | (z + m) << 8 | m;
	else if (hsv.h >= 60 && hsv.h < 120)
		rgb = (z + max) << 16 | max << 8 | m;
	else if (hsv.h >= 120 && hsv.h < 180)
		rgb = m << 16 | max << 8 | z + m;
	else if (hsv.h >= 180 && hsv.h < 240)
		rgb = m << 16 | (z + m) << 8 | max;
	else if (hsv.h >= 240 && hsv.h < 300)
		rgb = (z + m) << 16 | m << 8 | max;
	else if (hsv.h >= 300 && hsv.h < 360)
		rgb = max << 16 | m << 8 | z + m;
	return (rgb);
}

void	my_mlx_pixel_put(t_data *dt, int x, int y, int color)
{
	char	*dst;

	dst = dt->addr + (y * dt->line_len + x * (dt->bpp / 8));
	*(unsigned int *)dst = color;
}
