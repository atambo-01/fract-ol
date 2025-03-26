/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:27:38 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 14:48:32 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_data	*data_init_3(t_data *data)
{
	data->x_min = -2.0;
	data->x_max = 2.0;
	data->y_min = -2.0;
	data->y_max = 2.0;
	data->x_step = ((data->x_max - data->x_min) / WIDTH);
	data->y_step = ((data->y_max - data->y_min) / HEIGHT);
	data->img = NULL;
	data->view = 's';
	data->sierp = SIERPINSKI;
	data->dist = -1;
	data->max_iterations = ITERATIONS;
	data->color_0 = 0;
	data->color_1 = 0x0f548c;
	data->color_2 = 0xf2cf1d;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	return (data);
}

t_data	*data_init_2(t_data *data, char **av)
{
	if (!data)
		return (NULL);
	data->c_r = 0.0;
	data->c_i = 0.0;
	data->z.r = 0.0;
	data->z.i = 0.0;
	data->x_c = 0;
	data->y_c = 0;
	data->x = 0.0;
	data->y = 0.0;
	data->addr = NULL;
	data->max_zoom = DBL_MAX;
	data->min_zoom = DBL_MIN;
	if (ft_strcmp(av[1], "j") == 0)
		data->fractal = 'j';
	else if (ft_strcmp(av[1], "m") == 0)
		data->fractal = 'm';
	else if (ft_strcmp(av[1], "s") == 0)
	{
		data->fractal = 's';
		data->max_zoom = 2871.807116;
	}
	return (data_init_3(data));
}

t_data	*data_init(char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		exit(1);
	}
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fract-ol");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data);
		exit(1);
	}
	return (data_init_2(data, av));
}	
