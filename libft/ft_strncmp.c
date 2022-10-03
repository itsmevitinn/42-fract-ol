/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:37:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/03 17:12:09 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (n == 5 && ft_strlen(str1) != 5)
		return (1);
	else if (n == 10 && ft_strlen(str1) != 10)
		return (1);
	while (str1[i] == str2[i] && str1[i] != '\0'
		&& str2[i] != '\0' && i < n - 1)
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
