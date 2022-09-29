/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/09/29 00:24:00 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

int main(int argc, char **argv)
{
	t_data	data;

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
	data.mlx.img = mlx_new_image(data.mlx.instance, WIDTH, HEIGHT);
	data.mlx.addr = mlx_get_data_addr(data.mlx.img, &data.mlx.bits_per_pixel, &data.mlx.line_length, &data.mlx.endian);
	data.max = 140;
	render_fractol(&data);
	mlx_mouse_hook(data.mlx.win, mouse_event, &data);
	mlx_key_hook(data.mlx.win, key_event, &data);
	mlx_loop(data.mlx.instance);
}

int mandelbrot(double cr, double ci, int max)
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
	while(iterations < max)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0) // checa se ira tender ao infinito
			return (iterations);
		z.i = z.r * (z.i * 2) + ci; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		//z.i += z.i; //mesma coisa que (zi * 2)
		//z.i += ci;
		z.r = sqrt_zr - sqrt_zi + cr; //real ao quadrado + cr -> z(r)^2 + c(r)
		//calcuo pra descobrir o quadrado de numeros complexos
		sqrt_zr = z.r * z.r;
		sqrt_zi = z.i * z.i;
		iterations++;
	}
	return (iterations);
}
