/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/09/24 20:07:48 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int main(int argc, char **argv)
{
	t_data		data;
	
	argv[0] = 0;
	if (argc != 1)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	data.points.min_r = -2.0;
	data.points.max_r = 1.0;
	data.points.min_i = -1.5;
	data.points.max_i = 1.5;

	data.mlx.instance = mlx_init(); // inicializa a lib e armazena a instancia dela
	data.mlx.win = mlx_new_window(data.mlx.instance, WIDTH, HEIGHT, "fract'ol"); // inicializa a janela e armazena o ponteiro para a mesma
	//render_fractol(&data);
	mlx_mouse_hook(data.mlx.win, key_event, &data);
	mlx_key_hook(data.mlx.win, key_event, &data);
	mlx_loop(data.mlx.instance);
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == 13)
	{
		ft_printf("W\n");
		render_fractol(data, 0, 0);
	}
	else if (keycode == 12)
	{
		ft_printf("Scroll up\n");
		data->points.min_r += data->points.min_r * 0.1;
		data->points.max_r -= data->points.min_r * 0.1;
		data->points.min_i += data->points.min_r * 0.1;
		data->points.max_i -= data->points.min_r * 0.1;
		render_fractol(data, 0, 0);
	}
	else if (keycode == 14)
	{
		ft_printf("Scroll down\n");
		data->points.min_r -= data->points.min_r * 0.1;
		data->points.max_r += data->points.min_r * 0.1;
		data->points.max_i += data->points.min_r * 0.1;
		data->points.min_i -= data->points.min_r * 0.1;
		render_fractol(data, 0, 0);
	}
	else if (keycode == 0)
	{
		ft_printf("A\n");
		data->points.min_r += data->points.min_r * 0.1;
		data->points.max_r += data->points.min_r * 0.1;
		render_fractol(data, 0, 0);
	}
	else if (keycode == 2)
	{
		ft_printf("D\n");
		data->points.min_r -= data->points.min_r * 0.1;
		data->points.max_r -= data->points.min_r * 0.1;
		render_fractol(data, 0, 0);
	}
	return (0);
}

int	rgb_to_int(unsigned int t, unsigned int r, unsigned int g, unsigned int b)
{
	int value;

	value = t << 24;
	value += r << 16;
	value += g << 8;
	value += b;
	return (value);
}

int mandelbrot(double cr, double ci, int iterations)
{
	t_complex z;
	double temp;
	int counter; 

	counter = 0;
	z.r = 0;
	z.i = 0;
	while(counter < iterations)
	{
		if (sqrt(z.r * z.r + z.i * z.i) > 2) // checa se ira tender ao infinito
			return (counter);
		temp = z.r * z.i * 2 + ci; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		z.r = z.r * z.r - z.i * z.i + cr; //real ao quadrado + cr -> z(r)^2 + c(r)
		//calcuo pra descobrir o quadrado de numeros complexos
		z.i = temp;
		counter++;
	}
	return (counter);
}
