/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/01 03:34:15 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

int main(int argc, char **argv)
{
	t_data	data;
	if (argc < 1)
	{
		write(2, "Invalid argc\n", 13);
		exit(EXIT_FAILURE);
	}
	init_data(&data, argv);
	which_set(&data);
	init_mlx(&data);
}

void	init_mlx(t_data *data)
{
	mlx_mouse_hook(data->mlx.win, mouse_event, &data);
	mlx_key_hook(data->mlx.win, key_event, &data);
	mlx_loop(data->mlx.instance);
}

void	init_data(t_data *data, char **argv)
{
	data->points.min_r = -2.0;
	data->points.max_r = 2.0;
	data->points.min_i = -2.0;
	data->points.max_i = 2.0;
	data->mlx.instance = mlx_init(); // inicializa a lib e armazena a instancia dela
	data->mlx.win = mlx_new_window(data->mlx.instance, WIDTH, HEIGHT, "fract'ol"); // inicializa a janela e armazena o ponteiro para a mesma
	data->mlx.img = mlx_new_image(data->mlx.instance, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
	data->max = 100;
	data->zoom = 1;
	if (ft_strcmp(argv[1], "julia") == 0)
	{
		data->type = 'j';
		data->c.r = ft_atod(argv[2]);
		data->c.i = ft_atod(argv[3]);
	}
	else if (ft_strcmp(argv[1], "mandelbrot") == 0)
		data->type = 'm';
	else if (ft_strcmp(argv[1], "burningship") == 0)
		data->type = 'b';
}

void	which_set(t_data *data)
{
	if (data->type == 'j')
		render_julia(data);
	else if (data->type == 'm' || data->type == 'b')
		render_mandel_or_ship(data);
}

int julia(t_complex z, t_data *data)
{
	t_complex	sqrt_z;
	int			iterations;

	iterations = 0;
	sqrt_z.r = z.r * z.r;
	sqrt_z.i = z.i * z.i;
	while(iterations < data->max)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0) // checa se ira tender ao infinito
			return (iterations);
		z.i = z.r * (z.i * 2) + data->c.i; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		z.r = sqrt_z.r - sqrt_z.i + data->c.r; //real ao quadrado + cr -> z(r)^2 + c(r)
		//calcuo pra descobrir o quadrado de numeros complexos
		sqrt_z.r = z.r * z.r;
		sqrt_z.i = z.i * z.i;
		iterations++;
	}
	return (iterations);
}

int mandel_or_ship(t_complex c, t_data *data)
{
	t_complex	z;
	double		sqrt_zr;
	double		sqrt_zi;
	int			iterations;

	iterations = 0;
	z.r = 0;
	z.i = 0;
	sqrt_zr = z.r * z.r;
	sqrt_zi = z.i * z.i;
	while(iterations < data->max)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0) // checa se ira tender ao infinito
			return (iterations);
		if (data->type == 'm')
			z.i = z.r * (z.i * 2) + c.i; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		else if (data->type == 'b')
			z.i = fabs(z.r * z.i * 2) + c.i; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		z.r = sqrt_zr - sqrt_zi + c.r; //real ao quadrado + cr -> z(r)^2 + c(r)
		//calcuo pra descobrir o quadrado de numeros complexos
		sqrt_zr = z.r * z.r;
		sqrt_zi = z.i * z.i;
		iterations++;
	}
	return (iterations);
}

