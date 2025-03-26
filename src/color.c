/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:16:05 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 22:28:44 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	get_color_component(int base_color, int next_color, double ratio, int i)
{
	int	base;
	int	next;

	base = (base_color >> i) & 0xff;
	next = (next_color >> i) & 0xff;
	return ((int)(base + ratio * (next - base)));
}

int	get_color_2(int out_color, int int_color, int iter, int max_iter)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	ratio = (double)iter / (double)max_iter;
	red = get_color_component(out_color, int_color, ratio, 16);
	green = get_color_component(out_color, int_color, ratio, 8);
	blue = get_color_component(out_color, int_color, ratio, 0);
	if (iter == max_iter)
		return (0xb515cc + (int)(0.01 * out_color));
	return ((red << 16) | (green << 8) | blue);
}

void	update_colors(t_data *data, int iterations)
{
	if (data->dist > 0)
	{
		data->color_1 -= iterations * sin(iterations) / 1.82703449496728343;
		data->color_2 -= iterations * sin(iterations) / 1.82703449496728343;
	}
}

int	get_color_1(t_data *data, int x_c, int y_c, int iterations)
{
	int	color;

	color = 0;
	update_colors(data, iterations);
	if (data->view == 's')
	{
		color = get_color_2(data->color_1, data->color_2,
				iterations, data->max_iterations);
	}
	else if (data->view == 'l')
	{
		color = get_color_2(data->color_1
				* iterations, data->color_2 * iterations, iterations,
				data->max_iterations);
	}
	pixel_put_img(data, x_c, y_c, color);
	return (0);
}
