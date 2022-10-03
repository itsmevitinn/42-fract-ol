/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 04:40:33 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/03 17:19:36 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

double	ft_atod(char *string)
{
	double	first_part;
	double	second_part;
	int		len;
	int		negative;

	if (string[0] == '-')
		negative = 1;
	else
		negative = 0;
	first_part = ft_atoi(string);
	while (*string && *string != '.')
		string++;
	string++;
	second_part = ft_atoi(string);
	len = ft_strlen(string);
	while (len--)
		second_part = second_part / 10;
	if (negative == 0)
		return (first_part + second_part);
	else
		return (first_part + -second_part);
}
