/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:02:06 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/03 11:32:48 by vsergio          ###   ########.fr       */
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

typedef struct s_hsv
{
	double h;
	double s;
	double v;
}				t_hsv;

typedef struct s_data
{
	t_complex		c;
	char			type;
	int				max;
	int				zoom;
	int				x_pos;
	int				y_pos;
	void			*init;
	void			*win;
	void			*img;
	void			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	double			min_r;
	double			max_r;
	double			min_i;
	double			max_i;
}					t_data;

int		equation_m_b(t_complex c, t_data *dt);
int		equation_j(t_complex z, t_data *dt);
int		key_event(int keycode, t_data *dt);
int		mouse_event(int button, int x, int y, t_data *dt);
int		get_hsv(int iterations, int max);
int		hsv_to_rgb(t_hsv hsv);
int		close_win(t_data *dt);
void	which_fractal(t_data *dt);
void	init_data(t_data *dt);
void	my_mlx_pixel_put(t_data *dt, int x, int y, int color);
void	render_mandel_or_ship(t_data *dt);
void	render_julia(t_data *dt);
void	zoom(t_data *dt, int x, int y, double values);
void	check_parameters(t_data *dt, int argc, char **argv);
void	shift(int keycode, t_data *dt);
void	suggest_exit(void);
#endif