/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:20:56 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/01 03:34:27 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx.instance, data->mlx.win);
		// free(data->mlx.instance);
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
	render_mandel_or_ship(data);
	return (0);
}

int	mouse_event(int button, int x, int y, t_data *data)
{
	if (button == 4)
		zoom(data, x, y, 1.1);
	else if (button == 5)
		zoom(data, x, y, 0.9);
	render_mandel_or_ship(data);
	return (0);
}

void	zoom(t_data *data, int x, int y, double value)
{
	double	x_cartesian;
	double	y_cartesian;

	x_cartesian  = (x / HEIGHT) * (data->points.max_r - data->points.min_r) + data->points.min_r;
	y_cartesian  = (y / WIDTH) * (data->points.max_i - data->points.min_i) + data->points.min_i;
	data->points.min_r = x_cartesian + (data->points.min_r - x_cartesian) * value;
	data->points.max_r = x_cartesian + (data->points.max_r - x_cartesian) * value;
	data->points.min_i = y_cartesian + (data->points.min_i - y_cartesian) * value;
	data->points.max_i = y_cartesian + (data->points.max_i - y_cartesian) * value;
	data->zoom++;
}

double	ft_atod(char *string)
{
	double	first_part; //salvamos o numero antes da virgula em um double, pra depois somar com o numero apos a virgula
	double	second_part;
	int		len;
	int		negative;

	if (string[0] == '-')
		negative = 1;
	else
		negative = 0;
	first_part = ft_atoi(string); // atoi de "100.8" -> 100
	while(*string && *string != '.') //avancamos o ponteiro pra descobrirmos o numero apos a virgula
		string++;
	string++;
	second_part = ft_atoi(string); //atoi de "8" -> 8
	len = ft_strlen(string);
	while(len--) //aqui iremos descobrir o numero apos a virgula, exemplo, "8", iremos dividir o 8 por 10 ate o numero ficar apos a virgula/ menor que 0
		second_part = second_part / 10; // 8 / 10 = 0.8
	if (negative == 0) //se for positivo, somos as 2 partes
		return (first_part + second_part);
	else // se for negativo, somo a primeira parte com a seg
		return (first_part + -second_part);
}
