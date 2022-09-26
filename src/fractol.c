/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/09/26 15:09:24 by vsergio          ###   ########.fr       */
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
	if (keycode == 6)
	{
		ft_printf("Mandelbrot Done\n");
		render_fractol(data, 0, 0);
	}
	else if (keycode == 13)
	{
		ft_printf("Zoom in\n");
		data->points.min_r *= 0.90;
		data->points.max_r *= 0.90;
		data->points.min_i *= 0.90;
		data->points.max_i *= 0.90;
		render_fractol(data, 0, 0);
	}
	else if (keycode == 1)
	{
		ft_printf("Zoom out\n");
		data->points.min_r *= 1.1;
		data->points.max_r *= 1.1;
		data->points.min_i *= 1.1;
		data->points.max_i *= 1.1;
		render_fractol(data, 0, 0);
	}
	else if (keycode == 0)
	{
		ft_printf("Left\n");
		data->points.min_r *= 1.1;
		data->points.max_r *= 0.90;
		render_fractol(data, 0, 0);
	}
	else if (keycode == 2)
	{
		ft_printf("Right\n");
		data->points.min_r *= 0.90;
		data->points.max_r *= 1.1;
		render_fractol(data, 0, 0);
	}
	return (0);
}

int	rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
	int value;

	value = r << 16;
	value += g << 8;
	value += b;
	return (value);
}

int mandelbrot(double cr, double ci, int iterations)
{
	t_complex z;
	double sqrt_zr;
	double sqrt_zi;
	int counter; 
	counter = 0;
	z.r = 0;
	z.i = 0;
	sqrt_zr = z.r * z.r;
	sqrt_zi = z.i * z.i;
	while(counter < iterations)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0) // checa se ira tender ao infinito
			return (counter);
		z.i = z.r * z.i; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		z.i += z.i; //mesma coisa que (zi * 2)
		z.i += ci;
		z.r = sqrt_zr - sqrt_zi + cr; //real ao quadrado + cr -> z(r)^2 + c(r)
		//calcuo pra descobrir o quadrado de numeros complexos
		sqrt_zr = z.r * z.r;
		sqrt_zi = z.i * z.i;
		counter++;
	}
	return (counter);
}
