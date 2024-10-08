/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:21:01 by atambo            #+#    #+#             */
/*   Updated: 2024/09/28 15:21:03 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	ft_atoi_f_2(const char *str, double fraction, double result)
{
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result = result + ((*str++) - '0') * fraction;
			fraction /= 10;
		}
	}
	return (result);
}

double	ft_atoi_f(const char *str)
{
	double	result;
	double	fraction;
	int		sign;

	sign = 1;
	result = 0.0;
	fraction = 0.1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result * sign > DBL_MAX)
			return (DBL_MAX);
		if (result * sign < -DBL_MAX)
			return (-DBL_MAX);
		str++;
	}
	result = ft_atoi_f_2(str, fraction, result);
	return (result * sign);
}
