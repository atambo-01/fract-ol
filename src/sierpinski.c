/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:32:26 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 19:09:17 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int point_in_triangle(t_sierp *s)
{
    double area = 0.5 * (-s->v1y * s->v2x + s->v0y * (-s->v1x + s->v2x)
			+ s->v0x * (s->v1y - s->v2y) + s->v1x * s->v2y);
    double ss = 1 / (2 * area) * (s->v0y * s->v2x - s->v0x * s->v2y +
			(s->v2y - s->v0y) * s->px + (s->v0x - s->v2x) * s->py);
    double t = 1 / (2 * area) * (s->v0x * s->v1y - s->v0y * s->v1x + 
			(s->v0y - s->v1y) * s->px + (s->v1x - s->v0x) * s->py);
    return (ss >= 0 && t >= 0 && (1 - ss - t) >= 0);
}
static int	update_data(t_sierp *s)
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


void draw_sierpinski(t_data *data, double x, double y)
{
    t_sierp s;

    s.px = data->x_min + (x / (double)WIDTH) * (data->x_max - data->x_min);
    s.py = data->y_min + (y / (double)HEIGHT) * (data->y_max - data->y_min);
    s.v0x = data->x_min + (data->x_max - data->x_min) * 0.5; // Top
    s.v0y = data->y_max;
    s.v1x = data->x_min;                                      // Bottom left
    s.v1y = data->y_min;
    s.v2x = data->x_max;                                      // Bottom right
    s.v2y = data->y_min;
    if (!point_in_triangle(&s))
    {
        get_color_1(data, data->x_c, data->y_c, 0); // Outside
        return;
    }
    int depth = 0;
    while (depth < data->sierp) // Fixed depth for speed
    {
        double d0 = (s.px - s.v0x) * (s.px - s.v0x) + (s.py - s.v0y) * (s.py - s.v0y);
        double d1 = (s.px - s.v1x) * (s.px - s.v1x) + (s.py - s.v1y) * (s.py - s.v1y);
        double d2 = (s.px - s.v2x) * (s.px - s.v2x) + (s.py - s.v2y) * (s.py - s.v2y);
		
     	if (update_data(&s))
        {
            get_color_1(data, data->x_c, data->y_c, 0); // In removed section
            return;
        }
	    if (d0 <= d1 && d0 <= d2)
        {
            s.px = s.v0x + (s.px - s.v0x) * 2.0;
            s.py = s.v0y + (s.py - s.v0y) * 2.0;
        }
        else if (d1 <= d0 && d1 <= d2)
        {
            s.px = s.v1x + (s.px - s.v1x) * 2.0;
            s.py = s.v1y + (s.py - s.v1y) * 2.0;
        }
        else
        {
            s.px = s.v2x + (s.px - s.v2x) * 2.0;
            s.py = s.v2y + (s.py - s.v2y) * 2.0;
        }
        depth++;
    }
    get_color_1(data, data->x_c, data->y_c, data->max_iterations); // Inside fractal
}
