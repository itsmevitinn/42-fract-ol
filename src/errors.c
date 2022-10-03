/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:40:17 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/03 17:12:56 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	check_parameters(t_data *dt, int argc, char **argv)
{
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "julia", 5) == 0 && argc == 4)
		{
			dt->type = 'j';
			dt->c.r = ft_atod(argv[2]);
			dt->c.i = ft_atod(argv[3]);
		}
		else if (ft_strncmp(argv[1], "mandelbrot", 10) == 0 && argc == 2)
			dt->type = 'm';
		else
			suggest_exit();
	}
	else
		suggest_exit();
}

void	suggest_exit(void)
{
	ft_printf("Wrong parameters!\nTry something below: \n");
	ft_printf("./fractol mandelbrot\n");
	ft_printf("./fractol julia −0.4 0.6\n");
	exit(EXIT_FAILURE);
}
