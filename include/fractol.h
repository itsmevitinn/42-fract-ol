/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:06 by vsergio           #+#    #+#             */
/*   Updated: 2022/09/30 05:29:17 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 700.0
# define HEIGHT 700.0
# include <math.h>
# include "../mlx/mlx.h"
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
	int			max;
	int			zoom;
}				t_data;

int		mandelbrot(double ci, double cr, int times);
int		key_event(int keycode, t_data *data);
int		mouse_event(int button, int x, int y, t_data *data);
int		get_hsv(int iterations, int max);
int		hsv_to_rgb(double h, double s, double v);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	render_fractol(t_data *data);
int 	burningship(double cr, double ci, int max);
void	zoom(t_data *data, int x, int y, double values);
int 	juliaset(t_complex z, int max);
void	render_julia(t_data *data);
#endif
