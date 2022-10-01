/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/01 05:47:47 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_parameters(&data, argc, argv);
	init_data(&data);
	which_fractal(&data);
	mlx_mouse_hook(data.mlx.win, mouse_event, &data);
	mlx_key_hook(data.mlx.win, key_event, &data);
	mlx_loop(data.mlx.instance);
}

void	init_data(t_data *data)
{
	data->mlx.instance = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.instance, WIDTH, HEIGHT, "fract'ol");
	data->mlx.img = mlx_new_image(data->mlx.instance, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
	data->points.min_r = -2.0;
	data->points.max_r = 2.0;
	data->points.min_i = -2.0;
	data->points.max_i = 2.0;
	data->max = 100;
	data->zoom = 1;
}

void	which_fractal(t_data *data)
{
	if (data->type == 'j')
		render_julia(data);
	else if (data->type == 'm' || data->type == 'b')
		render_mandel_or_ship(data);
}

int	equation_j(t_complex z, t_data *data)
{
	t_complex	sqrt_z;
	int			iterations;

	iterations = 0;
	sqrt_z.r = z.r * z.r;
	sqrt_z.i = z.i * z.i;
	while (iterations < data->max)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0)
			return (iterations);
		z.i = z.r * (z.i * 2) + data->c.i;
		z.r = sqrt_z.r - sqrt_z.i + data->c.r;
		sqrt_z.r = z.r * z.r;
		sqrt_z.i = z.i * z.i;
		iterations++;
	}
	return (iterations);
}

int	equation_m_b(t_complex c, t_data *data)
{
	t_complex	z;
	t_complex	sqrt_z;
	int			iterations;

	iterations = 0;
	z.r = 0;
	z.i = 0;
	sqrt_z.r = z.r * z.r;
	sqrt_z.i = z.i * z.i;
	while (iterations < data->max)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0)
			return (iterations);
		if (data->type == 'm')
			z.i = z.r * (z.i * 2) + c.i;
		else if (data->type == 'b')
			z.i = fabs(z.r * z.i * 2) + c.i;
		z.r = sqrt_z.r - sqrt_z.i + c.r;
		sqrt_z.r = z.r * z.r;
		sqrt_z.i = z.i * z.i;
		iterations++;
	}
	return (iterations);
}
