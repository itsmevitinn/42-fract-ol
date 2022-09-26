/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:06 by vsergio           #+#    #+#             */
/*   Updated: 2022/09/26 17:56:18 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 700
# define HEIGHT 700
# include <math.h>
# include "../mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_complex
{
	double r;
	double i;
}				t_complex;

typedef struct s_positions
{
	double min_r;
	double max_r;
	double min_i;
	double max_i;
}				t_positions;

typedef struct s_mlx
{
	void	*instance;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_data
{
	t_mlx		mlx;
	t_positions	points;
}				t_data;

// int	rgb_to_int(int t, int r, int g, int b);
int		mandelbrot(double ci, double cr, int times);
int		key_event(int keycode, t_data *data);
int		rgb_to_int(unsigned int r, unsigned int g, unsigned int b);
int		render_fractol(t_data *data, int i_pos, int r_pos);
int		get_hsv(double iterations, double max);
int		hsv_to_rgb(double h, double s, double v);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
