/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:44:13 by atambo            #+#    #+#             */
/*   Updated: 2024/09/28 15:44:15 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	draw_if(t_data *data)
{
	if (data->fractal == 1)
		data->fractal = 'm';
	else if (data->fractal == 2)
		data->fractal = 'j';
	draw_fractal(data, data->x, data->y);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	key_hook_2(int keycode, t_data *data)
{
	double	change;

	change = 0.0001 * data->x_max * data->color_2 * sin(data->x_max);
	if (keycode == SPACE)
	{
		data->color_1 += change;
		data->color_2 += change;
	}
	if (keycode == S)
	{
		data->view = 's';
	}
	if (keycode == L)
	{
		data->view = 'l';
	}
	if (keycode == D)
	{
		data->dist = data->dist * -1;
	}
}

int	key_hook(int keycode, t_data *data)
{
	double	dxy;

	dxy = (data->x_max - data->x_min) * 0.05;
	if ((keycode == DOWN) || (keycode == UP))
	{
		if (keycode == DOWN)
			xy_lim_add(data, -dxy, 0.0);
		else
			xy_lim_add(data, +dxy, 0.0);
	}
	if ((keycode == LEFT) || (keycode == RIGHT))
	{
		if (keycode == LEFT)
			xy_lim_add(data, 0.0, -dxy);
		else
			xy_lim_add(data, 0.0, +dxy);
	}
	if (keycode == ESC)
		close_window(data);
	key_hook_2(keycode, data);
	draw_if(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{	
	if (button == 4 && x)
	{
		if (data->x_max - data->x_min <= DBL_MIN)
			ft_put_error("Max zoom lvl\n");
		else
		{
			xy_lim_zoom(data, 0.1 * (data->x_max - data->x_min));
		}
	}
	else if (button == 5 && y)
	{				
		if (data->x_max - data->x_min >= DBL_MAX)
			ft_put_error("Min zoom lvl\n");
		else
		{
			xy_lim_zoom(data, -0.1 * (data->x_max - data->x_min));
		}
	}
	draw_if(data);
	return (0);
}
