/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:51:26 by atambo            #+#    #+#             */
/*   Updated: 2024/09/25 13:27:36 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	print_valid_params(void)
{
	char	*valid_params;

	valid_params = ""
		"Available options:\n"
		"--------------------------------------------------------------------\n"
		"\t./fractol m\n"
		"\t./fractol j <complex_real> <complex_imaginary>\n"
		"\t./fractol j -0.761682243 0.088785046\n"
		"--------------------------------------------------------------------\n"
		"OBS - for julia the modulus of point should be inside a radius of 4\n"
		"It must fit in a double meaning > than 1E-10 = (0.000 000 000 001)\n"
		"--------------------------------------------------------------------\n"
		"for zooming and 's'(simple) 'l'(layers) ('d')(distorted) for visuals\n"
		"--------------------------------------------------------------------\n";
	ft_put_error(valid_params);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_is_double(const char *str)
{
	int	has_dot;
	int	has_digit;

	has_dot = 0;
	has_digit = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && (ft_isdigit(*str) || *str == '.'))
	{
		if (*str == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (!ft_isdigit(*str))
			return (0);
		else
			has_digit++;
		str++;
	}
	if (!has_digit)
		return (0);
	return (1);
}

int	check_input_2(char **av)
{
	if (ft_strcmp(av[1], "j") != 0)
	{
		ft_put_error("Error, invalid parameters.\n");
		print_valid_params();
		return (-1);
	}
	if (!ft_is_double(av[2]) || !ft_is_double(av[3]))
	{
		ft_put_error("Error, invalid parameters.\n");
		print_valid_params();
		return (-1);
	}
	return (2);
}

int	check_input(int ac, char **av)
{
	if (ac != 2 && ac != 4)
	{
		ft_put_error("Error, invalid parameters.\n");
		print_valid_params();
		return (-1);
	}
	else if (ac == 2 && ft_strcmp(av[1], "m") != 0)
	{
		ft_put_error("Error, invalid parameters.\n");
		print_valid_params();
		return (-1);
	}
	if (ac == 4)
	{
		if (check_input_2(av) == 2)
			return (2);
		else
			return (-1);
	}
	return (1);
}
