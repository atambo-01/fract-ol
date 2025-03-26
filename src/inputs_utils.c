/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:17:13 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 09:56:49 by atambo           ###   ########.fr       */
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
    double mouse_x_coord = mouse_x + 0.5;
    double mouse_y_coord = HEIGHT - (mouse_y + 0.5);
    
    double x_range = data->x_max - data->x_min;
    double y_range = data->y_max - data->y_min;
    
    double anchor_x = data->x_min + (mouse_x_coord / WIDTH) * x_range;
    double anchor_y = data->y_min + (mouse_y_coord / HEIGHT) * y_range;
    
    x_range *= zoom_factor;
    y_range *= zoom_factor;
    
    data->x_min = anchor_x - (mouse_x_coord / WIDTH) * x_range;
    data->x_max = data->x_min + x_range;
    data->y_min = anchor_y - (mouse_y_coord / HEIGHT) * y_range;
    data->y_max = data->y_min + y_range;
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
