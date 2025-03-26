/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:17:59 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 11:48:04 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	is_in_mandelbrot(double x, double y)
{
	double	q;

	q = (x - 0.25) * (x - 0.25) + y * y;
	if ((x + 1) * (x + 1) + y * y <= 0.0625)
	{
		return (1);
	}
	if (q * (q + (x - 0.25)) <= 0.25 * y * y)
	{
		return (1);
	}
	return (0);
}

void	draw_julia(t_data *data, double x, double y, t_cmplx z)
{
	int	iterations;

	data->z.r = x;
	data->z.i = y;
	iterations = 0;
	while (iterations < data->max_iterations)
	{
		z = add(mult(z, z), data->c);
		if (z.r * z.r + z.i * z.i > 4.0)
			break ;
		iterations++;
	}
	get_color_1(data, data->x_c, data->y_c, iterations);
}

void	draw_mandelbrot(t_data *data, double x, double y, t_cmplx z)
{
	int	iterations;

	iterations = 0;
	data->c.r = x;
	data->c.i = y;
	z = data->z;
	if (is_in_mandelbrot(x, y))
		iterations = data->max_iterations;
	else
	{
		while (iterations < data->max_iterations)
		{
			z = add(mult(z, z), data->c);
			if (sqrt(z.r * z.r + z.i * z.i) > 2.0)
				break ;
			iterations++;
		}
	}
	get_color_1 (data, data->x_c, data->y_c, iterations);
}


// Helper function to check if a point is inside a triangle (for initial bounds)
static int point_in_triangle(double px, double py, double x0, double y0, double x1, double y1, double x2, double y2)
{
    double area = 0.5 * (-y1 * x2 + y0 * (-x1 + x2) + x0 * (y1 - y2) + x1 * y2);
    double s = 1 / (2 * area) * (y0 * x2 - x0 * y2 + (y2 - y0) * px + (x0 - x2) * py);
    double t = 1 / (2 * area) * (x0 * y1 - y0 * x1 + (y0 - y1) * px + (x1 - x0) * py);
    return (s >= 0 && t >= 0 && (1 - s - t) >= 0);
}

void draw_sierpinski(t_data *data, double x, double y, t_cmplx z)
{
    (void)z; // Silence unused parameter warning

    // Map pixel to fractal coordinates
    double fx = data->x_min + (x / (double)WIDTH) * (data->x_max - data->x_min);
    double fy = data->y_min + (y / (double)HEIGHT) * (data->y_max - data->y_min);

    // Define triangle vertices
    double v0x = data->x_min + (data->x_max - data->x_min) * 0.5; // Top
    double v0y = data->y_max;
    double v1x = data->x_min;                                      // Bottom left
    double v1y = data->y_min;
    double v2x = data->x_max;                                      // Bottom right
    double v2y = data->y_min;

    // Check if the point is in the base triangle
    if (!point_in_triangle(fx, fy, v0x, v0y, v1x, v1y, v2x, v2y))
    {
        get_color_1(data, data->x_c, data->y_c, 0); // Outside
        return;
    }

    // Recursive check with fixed depth
    int depth = 0;
    double px = fx, py = fy;
    while (depth < 5) // Fixed depth for speed
    {
        // Find closest vertex
        double d0 = (px - v0x) * (px - v0x) + (py - v0y) * (py - v0y);
        double d1 = (px - v1x) * (px - v1x) + (py - v1y) * (py - v1y);
        double d2 = (px - v2x) * (px - v2x) + (py - v2y) * (py - v2y);

        // Check if in the "removed" middle triangle at this level
        if (point_in_triangle(px, py,
                             (v0x + v1x) / 2.0, (v0y + v1y) / 2.0,
                             (v1x + v2x) / 2.0, (v1y + v2y) / 2.0,
                             (v2x + v0x) / 2.0, (v2y + v0y) / 2.0))
        {
            get_color_1(data, data->x_c, data->y_c, 0); // In removed section
            return;
        }

        // Move to next level by scaling toward closest vertex
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

void	draw_fractal(t_data *data, double x, double y)
{
	data->x_step = ((data->x_max - data->x_min) / WIDTH);
	data->y_step = ((data->y_max - data->y_min) / HEIGHT);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	data->x_c = 0;
	x = data->x_min;
	while (x <= data->x_max)
	{
		data->y_c = 0;
		y = data->y_min;
		while (y <= data->y_max)
		{
			if (data->fractal == 'm')
				draw_mandelbrot(data, x, y, data->z);
			else if (data->fractal == 'j')
				draw_julia(data, x, y, data->z);
			else if (data->fractal == 's')
				draw_sierpinski(data, x, y, data->z);
			data->y_c++;
			y += data->x_step;
		}
		data->x_c++;
		x += data->y_step;
	}
}


