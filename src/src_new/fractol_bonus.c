/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:22:03 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/03 12:22:04 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

int	main(int argc, char **argv)
{
	t_data	dt;

	check_parameters(&dt, argc, argv);
	init_data(&dt);
	which_fractal(&dt);
	mlx_mouse_hook(dt.win, mouse_event, &dt);
	mlx_key_hook(dt.win, key_event, &dt);
	mlx_hook(dt.win, 17, 0, close_win, &dt);
	mlx_loop(dt.init);
}

void	init_data(t_data *dt)
{
	dt->init = mlx_init();
	dt->win = mlx_new_window(dt->init, WIDTH, HEIGHT, "fract'ol");
	dt->img = mlx_new_image(dt->init, WIDTH, HEIGHT);
	dt->addr = mlx_get_data_addr(dt->img, &dt->bpp, &dt->line_len, &dt->endian);
	dt->min_r = -2.0;
	dt->max_r = 2.0;
	dt->min_i = -2.0;
	dt->max_i = 2.0;
	dt->max = 140;
	dt->zoom = 1;
}

void	which_fractal(t_data *dt)
{
	if (dt->type == 'j')
		render_julia(dt);
	else if (dt->type == 'm' || dt->type == 'b')
		render_mandel_or_ship(dt);
}

int	equation_j(t_complex z, t_data *dt)
{
	t_complex	sqrt_z;
	int			iterations;

	iterations = 0;
	sqrt_z.r = z.r * z.r;
	sqrt_z.i = z.i * z.i;
	while (iterations < dt->max)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0)
			return (iterations);
		z.i = z.r * z.i * 2 + dt->c.i;
		z.r = sqrt_z.r - sqrt_z.i + dt->c.r;
		sqrt_z.r = z.r * z.r;
		sqrt_z.i = z.i * z.i;
		iterations++;
	}
	return (iterations);
}

int	equation_m_b(t_complex c, t_data *dt)
{
	t_complex	z;
	t_complex	sqrt_z;
	int			iterations;

	iterations = 0;
	z.r = 0;
	z.i = 0;
	sqrt_z.r = z.r * z.r;
	sqrt_z.i = z.i * z.i;
	while (iterations < dt->max)
	{
		if ((z.r * z.r + z.i * z.i) > 4.0)
			return (iterations);
		if (dt->type == 'm')
			z.i = z.r * (z.i * 2) + c.i;
		else if (dt->type == 'b')
			z.i = fabs(z.r * z.i * 2) + c.i;
		z.r = sqrt_z.r - sqrt_z.i + c.r;
		sqrt_z.r = z.r * z.r;
		sqrt_z.i = z.i * z.i;
		iterations++;
	}
	return (iterations);
}
