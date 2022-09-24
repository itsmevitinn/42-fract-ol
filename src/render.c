/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:03:51 by Vitor             #+#    #+#             */
/*   Updated: 2022/09/24 20:09:39 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	render_fractol(t_data *data, int imaginary, int real)
{
	t_complex	c;
	int			i_pos;
	int			r_pos;
	int 		depth;
	int			iterations;

	i_pos = imaginary;
	iterations = 1000;
	while(i_pos < HEIGHT)
	{
		r_pos = real;
		c.i = data->points.min_r + i_pos * (data->points.max_r - data->points.min_r) / HEIGHT; // posicao real de C de acordo com o tamanho de pixels + o tamanho no plano (-2.0 ate 1.0, diminuindo 0.3 (distancia entre os pontos / largura) a cada passada ());
		while(r_pos < WIDTH)
		{
			c.r = data->points.min_i + r_pos * (data->points.max_i - data->points.min_i) / WIDTH; // posicao imaginaria do C de acordo com tamanho de pixels e a posicao do plano (-1.5 a 1.5) diminuindo 0.3 (distancia entre os pontos / altura) a cada passada;
			//o real ira andar para a direita, ate o final da linha, pois o eixo eh horizontal e vai da esquerda pra direita
			if (mandelbrot(c.r, c.i, iterations) < iterations)
			{
				depth = mandelbrot(c.r, c.i, iterations);
				mlx_pixel_put(data->mlx.instance, data->mlx.win, r_pos, i_pos, rgb_to_int(depth, depth + 345, depth + 567, depth + 789));
			}
			else
				mlx_pixel_put(data->mlx.instance, data->mlx.win, r_pos, i_pos, 000000);
			r_pos++;
		}
		// o imaginario quebra a linha pois o eixo eh vertical e vai descendo
		i_pos++;
	}
	return (0);
}
