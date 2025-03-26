/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:17:13 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 22:20:59 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	zoom_limit(t_data *data)
{
	if (data->x_max - data->x_min >= data->max_zoom)
		return (1.0);
	if (data->x_max - data->x_min <= data->min_zoom)
		return (-1.0);
	return (0.0);
}

void	xy_lim_add(t_data *data, double dx, double dy)
{
	data->x_min += dx;
	data->x_max += dx;
	data->y_min += dy;
	data->y_max += dy;
}

void	xy_lim_zoom(t_data *data, double zoom_factor, int mouse_x, int mouse_y)
{
	double	x_adj;
	double	y_adj;
	double	x_prop;
	double	y_prop;

	x_prop = (double)mouse_x / WIDTH;
	y_prop = (double)mouse_y / HEIGHT;
	x_adj = (data->x_max - data->x_min) * (1.0 - zoom_factor);
	y_adj = (data->y_max - data->y_min) * (1.0 - zoom_factor);
	data->x_min += x_adj * x_prop;
	data->x_max -= x_adj * (1.0 - x_prop);
	data->y_min += y_adj * y_prop;
	data->y_max -= y_adj * (1.0 - y_prop);
}

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
}
