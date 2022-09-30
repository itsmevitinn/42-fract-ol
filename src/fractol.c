/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:04 by vsergio           #+#    #+#             */
/*   Updated: 2022/09/30 05:29:06 by vsergio          ###   ########.fr       */
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
	// if (ft_strncmp(argv[1], "mandelbrot"))
	data.points.min_r = -2.0;
	data.points.max_r = 2.0;
	data.points.min_i = -2.0;
	data.points.max_i = 2.0;
	data.mlx.instance = mlx_init(); // inicializa a lib e armazena a instancia dela
	data.mlx.win = mlx_new_window(data.mlx.instance, WIDTH, HEIGHT, "fract'ol"); // inicializa a janela e armazena o ponteiro para a mesma
	data.mlx.img = mlx_new_image(data.mlx.instance, WIDTH, HEIGHT);
	data.mlx.addr = mlx_get_data_addr(data.mlx.img, &data.mlx.bits_per_pixel, &data.mlx.line_length, &data.mlx.endian);
	data.max = 100;
	data.zoom = 1;
	render_julia(&data);
	// render_fractol(&data);
	mlx_mouse_hook(data.mlx.win, mouse_event, &data);
	mlx_key_hook(data.mlx.win, key_event, &data);
	mlx_loop(data.mlx.instance);
}

int juliaset(t_complex z, int max)
{
	double		sqrt_zr;
	double		sqrt_zi;
	int			iterations;
	double		ci;
	double		cr;

	iterations = 0;
	cr = -0.7269;
	ci = 0.1889;
	sqrt_zr = z.r * z.r;
	sqrt_zi = z.i * z.i;
	while(iterations < max)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0) // checa se ira tender ao infinito
			return (iterations);
		z.i = z.r * (z.i * 2) + ci; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
		z.r = sqrt_zr - sqrt_zi + cr; //real ao quadrado + cr -> z(r)^2 + c(r)
		//calcuo pra descobrir o quadrado de numeros complexos
		sqrt_zr = z.r * z.r;
		sqrt_zi = z.i * z.i;
		iterations++;
	}
	return (iterations);
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

int burningship(double cr, double ci, int max)
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
		z.i = fabs(z.r * z.i * 2) + ci; // imaginario ao quadrado + ci -> z(i)^2 + c(i)
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
