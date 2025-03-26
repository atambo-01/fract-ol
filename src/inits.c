/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:27:38 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 01:05:35 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_data	*data_init_3(t_data *data)
{
	data->view = 's';
	data->dist = -1;
	data->max_iterations = 100;
	data->color_0 = 0;
	data->color_1 = 0x0f548c;
	data->color_2 = 0xf2cf1d;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	return (data);
}

t_data	*data_init_2(t_data *data)
{
	if (!data)
		return (NULL);
	data->x_min = -2.0;
	data->x_max = 2.0;
	data->y_min = -2.0;
	data->y_max = 2.0;
	data->c_r = 0.0;
	data->c_i = 0.0;
	data->z.r = 0.0;
	data->z.i = 0.0;
	data->x_c = 0;
	data->y_c = 0;
	data->x = 0.0;
	data->y = 0.0;
	data->step = ((data->x_max - data->x_min) / 1000);
	data->img = NULL;
	data->addr = NULL;
	return (data_init_3(data));
}
/*
	quando estivermos para fazer o bonus e formos generalizar
	o tamanho da janela basta criar duas vars para win_h e
	win_w e dps usar as mesmas para calcular step_x e step_y 
	de resto creio que ja foi bem feito o setup
*/

t_data	*data_init(void)
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
	return (data_init_2(data));
}	
