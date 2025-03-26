/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:32:26 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 15:18:03 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int point_in_triangle(double px, double py, double x0, double y0, double x1, double y1, double x2, double y2)
{
    double area = 0.5 * (-y1 * x2 + y0 * (-x1 + x2) + x0 * (y1 - y2) + x1 * y2);
    double s = 1 / (2 * area) * (y0 * x2 - x0 * y2 + (y2 - y0) * px + (x0 - x2) * py);
    double t = 1 / (2 * area) * (x0 * y1 - y0 * x1 + (y0 - y1) * px + (x1 - x0) * py);
    return (s >= 0 && t >= 0 && (1 - s - t) >= 0);
}

void draw_sierpinski(t_data *data, double x, double y)
{
    double fx = data->x_min + (x / (double)WIDTH) * (data->x_max - data->x_min);
    double fy = data->y_min + (y / (double)HEIGHT) * (data->y_max - data->y_min);
    double v0x = data->x_min + (data->x_max - data->x_min) * 0.5; // Top
    double v0y = data->y_max;
    double v1x = data->x_min;                                      // Bottom left
    double v1y = data->y_min;
    double v2x = data->x_max;                                      // Bottom right
    double v2y = data->y_min;
    if (!point_in_triangle(fx, fy, v0x, v0y, v1x, v1y, v2x, v2y))
    {
        get_color_1(data, data->x_c, data->y_c, 0); // Outside
        return;
    }
    int depth = 0;
    double px = fx, py = fy;
    while (depth < data->sierp) // Fixed depth for speed
    {
        double d0 = (px - v0x) * (px - v0x) + (py - v0y) * (py - v0y);
        double d1 = (px - v1x) * (px - v1x) + (py - v1y) * (py - v1y);
        double d2 = (px - v2x) * (px - v2x) + (py - v2y) * (py - v2y);
        if (point_in_triangle(px, py,
                             (v0x + v1x) / 2.0, (v0y + v1y) / 2.0,
                             (v1x + v2x) / 2.0, (v1y + v2y) / 2.0,
                             (v2x + v0x) / 2.0, (v2y + v0y) / 2.0))
        {
            get_color_1(data, data->x_c, data->y_c, 0); // In removed section
            return;
        }
        if (d0 <= d1 && d0 <= d2)
        {
            px = v0x + (px - v0x) * 2.0;
            py = v0y + (py - v0y) * 2.0;
        }
        else if (d1 <= d0 && d1 <= d2)
        {
            px = v1x + (px - v1x) * 2.0;
            py = v1y + (py - v1y) * 2.0;
        }
        else
        {
            px = v2x + (px - v2x) * 2.0;
            py = v2y + (py - v2y) * 2.0;
        }
        depth++;
    }

    get_color_1(data, data->x_c, data->y_c, data->max_iterations); // Inside fractal
}
