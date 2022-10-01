/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 04:40:33 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/01 04:40:39 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

double	ft_atod(char *string)
{
	double	first_part; //salvamos o numero antes da virgula em um double, pra depois somar com o numero apos a virgula
	double	second_part;
	int		len;
	int		negative;

	if (string[0] == '-')
		negative = 1;
	else
		negative = 0;
	first_part = ft_atoi(string); // atoi de "100.8" -> 100
	while(*string && *string != '.') //avancamos o ponteiro pra descobrirmos o numero apos a virgula
		string++;
	string++;
	second_part = ft_atoi(string); //atoi de "8" -> 8
	len = ft_strlen(string);
	while(len--) //aqui iremos descobrir o numero apos a virgula, exemplo, "8", iremos dividir o 8 por 10 ate o numero ficar apos a virgula/ menor que 0
		second_part = second_part / 10; // 8 / 10 = 0.8
	if (negative == 0) //se for positivo, somos as 2 partes
		return (first_part + second_part);
	else // se for negativo, somo a primeira parte com a seg
		return (first_part + -second_part);
}
