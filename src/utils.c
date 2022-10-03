/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:20:56 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/03 10:07:52 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

int	key_event(int keycode, t_data *dt)
{
	int	interrupter;

	interrupter = 1;
	if (keycode == 53)
	{
		mlx_destroy_window(dt->init, dt->win);
		exit(EXIT_FAILURE);
	}
	else if (keycode >= 123 && keycode <= 126 && interrupter++)
		shift(keycode, dt);
	if (interrupter > 1)
	{
		mlx_clear_window(dt->init, dt->win);
		which_fractal(dt);
	}
	return (0);
}

void	shift(int keycode, t_data *dt)
{
	if (keycode == 123)
	{
		dt->max_r -= 0.03 / (dt->zoom * 4);
		dt->min_r -= 0.03 / (dt->zoom * 4);
	}
	else if (keycode == 124)
	{
		dt->min_r += 0.03 / (dt->zoom * 4);
		dt->max_r += 0.03 / (dt->zoom * 4);
	}
	else if (keycode == 125)
	{
		dt->min_i -= 0.03 / (dt->zoom * 4);
		dt->max_i -= 0.03 / (dt->zoom * 4);
	}
	else if (keycode == 126)
	{
		dt->min_i += 0.03 / (dt->zoom * 4);
		dt->max_i += 0.03 / (dt->zoom * 4);
	}
}

int	mouse_event(int button, int x, int y, t_data *dt)
{
	int	interrupter;

	interrupter = 1;
	if (button == 4 && interrupter++)
		zoom(dt, x, y, 1.1);
	else if (button == 5 && interrupter++)
		zoom(dt, x, y, 0.9);
	if (interrupter > 1)
	{
		mlx_clear_window(dt->init, dt->win);
		which_fractal(dt);
	}
	return (0);
}

void	zoom(t_data *dt, int x, int y, double value)
{
	double	new_r;
	double	new_i;

	new_r = dt->min_r + (x / HEIGHT) * (dt->max_r - dt->min_r);
	new_i = dt->max_i - (y / WIDTH) * (dt->max_i - dt->min_i);
	dt->min_r = new_r + (dt->min_r - new_r) * value;
	dt->max_r = new_r + (dt->max_r - new_r) * value;
	dt->min_i = new_i + (dt->min_i - new_i) * value;
	dt->max_i = new_i + (dt->max_i - new_i) * value;
	dt->zoom++;
}

int	close_win(t_data *dt)
{
	mlx_destroy_window(dt->init, dt->win);
	exit(1);
	return (0);
}
