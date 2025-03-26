/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:17:13 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 10:36:01 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	xy_lim_add(t_data *data, double dx, double dy)
{
	data->x_min += dx;
	data->x_max += dx;
	data->y_min += dy;
	data->y_max += dy;
}


void xy_lim_zoom(t_data *data, double zoom_factor, int mouse_x, int mouse_y)
{
    double x_range = data->x_max - data->x_min;
    double y_range = data->y_max - data->y_min;

    // Calculate mouse position as a proportion of the screen (0.0 to 1.0)
    double x_proportion = (double)mouse_x / WIDTH;
    double y_proportion = (double)mouse_y / HEIGHT;

    double x_adjustment = x_range * (1.0 - zoom_factor);
    double y_adjustment = y_range * (1.0 - zoom_factor);

    data->x_min += x_adjustment * x_proportion;
    data->x_max -= x_adjustment * (1.0 - x_proportion);
    data->y_min += y_adjustment * y_proportion;
    data->y_max -= y_adjustment * (1.0 - y_proportion);
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
