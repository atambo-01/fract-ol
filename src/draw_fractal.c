/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:17:59 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 22:26:45 by atambo           ###   ########.fr       */
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

void	draw_init(t_data *data)
{
	data->x_step = ((data->x_max - data->x_min) / WIDTH);
	data->y_step = ((data->y_max - data->y_min) / HEIGHT);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
}

void	draw_fractal(t_data *data, double x, double y)
{
	draw_init(data);
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
				draw_sierpinski(data, x, y);
			data->y_c++;
			y += data->x_step;
		}
		data->x_c++;
		x += data->y_step;
	}
}
