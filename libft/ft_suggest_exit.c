/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_suggest_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:55:42 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/05 11:55:44 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	suggest_exit(void)
{
	ft_printf("Wrong parameters!\nTry something below: \n");
	ft_printf("./fractol mandelbrot\n");
	ft_printf("./fractol julia −0.4 0.6\n");
	exit(EXIT_FAILURE);
}
