/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:40:17 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/02 20:20:35 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	check_parameters(t_data *dt, int argc, char **argv)
{
	if (ft_strcmp(argv[1], "julia") == 0 && argc == 4)
	{
		dt->type = 'j';
		dt->c.r = ft_atod(argv[2]);
		dt->c.i = ft_atod(argv[3]);
	}
	else if (ft_strcmp(argv[1], "mandelbrot") == 0 && argc == 2)
		dt->type = 'm';
	else if (ft_strcmp(argv[1], "burningship") == 0 && argc == 2)
		dt->type = 'b';
	else
	{
		ft_printf("Wrong parameters!\nTry something below: \n");
		ft_printf("./fractol mandelbrot\n./fractol burningship\n");
		ft_printf("./fractol julia −0.4 0.6\n");
		exit(EXIT_FAILURE);
	}
}
