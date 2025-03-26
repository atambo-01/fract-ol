/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:44:13 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 22:24:37 by atambo           ###   ########.fr       */
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

void	key_hook_3(int keycode, t_data *data)
{
	if (keycode == '1' && data->sierp > 0)
	{
		data->sierp--;
	}
	if (keycode == '2' && data->sierp <= 45)
	{
		data->sierp++;
	}
}

void	key_hook_2(int keycode, t_data *data)
{
	double	change;

	change = 0.0001 * 2 * data->color_2 * sin(2);
	if (keycode == ' ')
	{
		data->color_1 += change;
		data->color_2 += change;
	}
	if (keycode == 'a')
	{
		data->view = 's';
	}
	if (keycode == 's')
	{
		data->view = 'l';
	}
	if (keycode == 'd')
	{
		data->dist = data->dist * -1;
	}
	else
		key_hook_3(keycode, data);
}

int	key_hook(int keycode, t_data *data)
{
	double	dxy;

	printf("level %d\n", data->sierp);
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
	double	zoom;

	zoom = data->x_max - data->x_min;
	if (button == 4 && x >= 0 && y >= 0)
	{
		if (zoom <= data->min_zoom)
			ft_put_error("Max zoom lvl\n");
		else
			xy_lim_zoom(data, 0.9, x, y);
	}
	else if (button == 5 && y >= 0 && x >= 0)
	{
		if (zoom >= data->max_zoom)
			ft_put_error("Min zoom lvl\n");
		else
			xy_lim_zoom(data, 1.1, x, y);
	}
	draw_if(data);
	return (0);
}
