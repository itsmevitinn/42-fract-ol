/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/09/27 18:17:43 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_data		data;
	
	argv[0] = 0;
	if (argc != 1)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	data.points.min_r = -2;
	data.points.max_r = 1.0;
	data.points.min_i = -1.5;
	data.points.max_i = 1.5;

	data.mlx.instance = mlx_init(); // inicializa a lib e armazena a instancia dela
	data.mlx.win = mlx_new_window(data.mlx.instance, WIDTH, HEIGHT, "fract'ol"); // inicializa a janela e armazena o ponteiro para a mesma
	//render_fractol(&data);
	mlx_mouse_hook(data.mlx.win, mouse_event, &data);
	mlx_key_hook(data.mlx.win, key_event, &data);
	mlx_loop(data.mlx.instance);
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == 6)
	{
		ft_printf("Mandelbrot Done\n");
		render_fractol(data);
	}
	else if (keycode == 0)
	{
		ft_printf("Left\n");
		data->points.min_r -= 0.1;
		data->points.max_r -= 0.1;
		render_fractol(data);
	}
	else if (keycode == 2)
	{
		ft_printf("Right\n");
		data->points.min_r += 0.1;
		data->points.max_r += 0.1;
		render_fractol(data);
	}
	else if (keycode == 13)
	{
		ft_printf("Up\n");
		data->points.min_i -= 0.1;
		data->points.max_i -= 0.1;
		render_fractol(data);
	}
	else if (keycode == 1)
	{
		ft_printf("Down\n");
		data->points.min_i += 0.1;
		data->points.max_i += 0.1;
		render_fractol(data);
	}
	return (0);
}

int	mouse_event(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		ft_printf("Zoom in\n");
		data->points.min_r += data->points.min_r * 0.1;
		data->points.max_r -= data->points.max_r * 0.1;
		data->points.min_i += data->points.min_i * 0.1;
		data->points.max_i -= data->points.max_i * 0.1;
		render_fractol(data);
	}
	else if (button == 5)
	{
		ft_printf("Zoom out\n");
		data->points.min_r -= data->points.min_r * 0.1;
		data->points.max_r += data->points.max_r * 0.1;
		data->points.min_i -= data->points.min_i * 0.1;
		data->points.max_i += data->points.max_i * 0.1;
		render_fractol(data);
	}
	else if (button == 1)
	{
		ft_printf("Mouse position: %i %i\n", x, y);
		double start_r;
		double start_i;
		double last_i;
		double last_r;
		start_r = (HEIGHT / 2) - x;
		start_i = (WIDTH / 2) - y;
		last_r = HEIGHT - abs((int)start_r);
		last_i = WIDTH - abs((int)start_i);
		printf("Start R %f\n", start_r);
		printf("Start I %f\n", start_i);
		printf("Last R %f\n", last_r);
		printf("Last I %f\n", last_i);

		// if (start_r < HEIGHT)
		// 	start_r *= -1;
		// if (start_i < WIDTH)
		// 	start_i *= -1;
		data->points.min_r = start_r / 100;
		data->points.max_r = last_r / 100;
		data->points.min_i = start_i / 100;
		data->points.max_i = last_i / 100;
		ft_printf("Changed center\n");
		render_fractol(data);
	}
	return (0);
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
