/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:20:56 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/01 05:49:49 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx.instance, data->mlx.win);
		exit(EXIT_FAILURE);
	}
	else if (keycode == 123)
	{
		data->points.max_r -= 0.03 / data->zoom;
		data->points.min_r -= 0.03 / data->zoom;
	}
	else if (keycode == 124)
	{
		data->points.min_r += 0.03 / data->zoom;
		data->points.max_r += 0.03 / data->zoom;
	}
	else if (keycode == 126)
	{
		data->points.min_i -= 0.03 / data->zoom;
		data->points.max_i -= 0.03 / data->zoom;
	}
	else if (keycode == 125)
	{
		data->points.min_i += 0.03 / data->zoom;
		data->points.max_i += 0.03 / data->zoom;
	}
	which_fractal(data);
	return (0);
}

int	mouse_event(int button, int x, int y, t_data *data)
{
	if (button == 4)
		zoom(data, x, y, 1.1);
	else if (button == 5)
		zoom(data, x, y, 0.9);
	which_fractal(data);
	return (0);
}

void	zoom(t_data *data, int x, int y, double value)
{
	double	x_cartesian;
	double	y_cartesian;

	x_cartesian = (x / HEIGHT) * (data->points.max_r - data->points.min_r) + data->points.min_r;
	y_cartesian = (y / WIDTH) * (data->points.max_i - data->points.min_i) + data->points.min_i;
	data->points.min_r = x_cartesian + (data->points.min_r - x_cartesian) * value;
	data->points.max_r = x_cartesian + (data->points.max_r - x_cartesian) * value;
	data->points.min_i = y_cartesian + (data->points.min_i - y_cartesian) * value;
	data->points.max_i = y_cartesian + (data->points.max_i - y_cartesian) * value;
	data->zoom++;
}

void	check_parameters(t_data *data, int argc, char **argv)
{
	if (ft_strcmp(argv[1], "julia") == 0 && argc == 4)
	{
		data->type = 'j';
		data->c.r = ft_atod(argv[2]);
		data->c.i = ft_atod(argv[3]);
	}
	else if (ft_strcmp(argv[1], "mandelbrot") == 0 && argc == 2)
		data->type = 'm';
	else if (ft_strcmp(argv[1], "burningship") == 0 && argc == 2)
		data->type = 'b';
	else
	{
		exit(EXIT_FAILURE);
	}
}
