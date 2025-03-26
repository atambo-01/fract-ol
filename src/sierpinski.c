/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:32:26 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 21:14:15 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	point_in_triangle(t_sierp *s)
{
	double	t;
	double	ss;
	double	area;

	area = 0.5 * (-s->v1y * s->v2x + s->v0y * (-s->v1x + s->v2x) + s->v0x
			* (s->v1y - s->v2y) + s->v1x * s->v2y);
	ss = 1 / (2 * area) * (s->v0y * s->v2x - s->v0x * s->v2y + (s->v2y - s->v0y)
			* s->px + (s->v0x - s->v2x) * s->py);
	t = 1 / (2 * area) * (s->v0x * s->v1y - s->v0y * s->v1x
			+ (s->v0y - s->v1y) * s->px + (s->v1x - s->v0x) * s->py);
	return (ss >= 0 && t >= 0 && (1 - ss - t) >= 0);
}

static int	small_triangle(t_sierp *s)
{
	t_sierp	s2;

	s2.px = s->px;
	s2.py = s->py;
	s2.v0x = (s->v0x + s->v1x) / 2.0;
	s2.v0y = (s->v0y + s->v1y) / 2.0;
	s2.v1x = (s->v1x + s->v2x) / 2.0;
	s2.v1y = (s->v1y + s->v2y) / 2.0;
	s2.v2x = (s->v2x + s->v0x) / 2.0;
	s2.v2y = (s->v2y + s->v0y) / 2.0;
	return (point_in_triangle(&s2));
}

static int	update_p(t_sierp *s, int opt)
{
	if (opt == 1)
	{
		s->px = s->v0x + (s->px - s->v0x) * 2.0;
		s->py = s->v0y + (s->py - s->v0y) * 2.0;
	}
	if (opt == 2)
	{
		s->px = s->v1x + (s->px - s->v1x) * 2.0;
		s->py = s->v1y + (s->py - s->v1y) * 2.0;
	}
	if (opt == 3)
	{
		s->px = s->v2x + (s->px - s->v2x) * 2.0;
		s->py = s->v2y + (s->py - s->v2y) * 2.0;
	}
}

static int	init_s(t_sierp *s, t_data *data, double x, double y)
{
	s->px = data->x_min + (x / (double)WIDTH) * (data->x_max - data->x_min);
	s->py = data->y_min + (y / (double)HEIGHT) * (data->y_max - data->y_min);
	s->v0x = data->x_min + (data->x_max - data->x_min) * 0.5;
	s->v0y = data->y_max;
	s->v1x = data->x_min;
	s->v1y = data->y_min;
	s->v2x = data->x_max;
	s->v2y = data->y_min;
}

int	draw_sierpinski(t_data *data, double x, double y)
{
	t_sierp	s;
	int		depth;
	double	d[3];

	init_s(&s, data, x, y);
	if (!point_in_triangle(&s))
		return (get_color_1(data, data->x_c, data->y_c, 0));
	depth = 0;
	while (depth < data->sierp)
	{
		sierp_util(&s, (double *)&d);
		if (small_triangle(&s))
			return (get_color_1(data, data->x_c, data->y_c, 0));
		if (d[0] <= d[1] && d[0] <= d[2])
			update_p(&s, 1);
		else if (d[1] <= d[0] && d[1] <= d[2])
			update_p(&s, 2);
		else
			update_p(&s, 3);
		depth++;
	}
	get_color_1(data, data->x_c, data->y_c, data->max_iterations);
}
