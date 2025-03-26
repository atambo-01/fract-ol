/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:34:24 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 11:37:43 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_loop(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, key_hook, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook (data->win, 17, 0, close_window, data);
	mlx_loop (data->mlx);
}

int	main(int ac, char **av)
{
	int		set;
	t_cmplx	c;
	t_data	*data;

	c.r = 0.0;
	c.i = 0.0;
	set = check_input(ac, av);
	if (set == 1 || set == 2)
	{	
		if (set == 2)
		{
			c.r = ft_atoi_f(av[2]);
			c.i = ft_atoi_f(av[3]);
		}	
		data = data_init();
		data->c = c;
		data->fractal = set;
		if (ft_strcmp(av[1], "j") == 0)
			data->fractal = 'j';
		else if (ft_strcmp(av[1], "m") == 0)
			data->fractal = 'm';
		else if (ft_strcmp(av[1], "s") == 0)
			data->fractal = 's'; 
		draw_fractal(data, data->x, data->y);
		ft_loop(data);
	}
	return (0);
}
