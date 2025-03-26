/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:55:36 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 22:59:26 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "../ft_printf/includes/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "stdio.h"

# define ESC		65307
# define UP			65363
# define DOWN		65361
# define LEFT		65362
# define RIGHT		65364
# define DBL_MAX	1.7976931348623157e+308
# define DBL_MIN	2.2250738585072014e-308
# define WIDTH		1080
# define HEIGHT		1080
# define ITERATIONS	100
# define SIERPINSKI	3

typedef struct s_cmplx
{
	double	r;
	double	i;
}	t_cmplx;

typedef struct s_sierp
{
	double	v0x;
	double	v0y;
	double	v1x;
	double	v1y;
	double	v2x;
	double	v2y;
	double	px;
	double	py;
}	t_sierp;

typedef struct s_data
{
	int		line_len;
	int		bpp;
	int		endian;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	t_cmplx	c;
	t_cmplx	z;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	max_zoom;
	double	min_zoom;
	double	c_r;
	double	c_i;
	double	x;
	double	y;
	int		x_c;
	int		y_c;
	double	x_step;
	double	y_step;
	int		fractal;
	int		color_0;
	int		color_1;
	int		color_2;
	int		max_iterations;
	char	view;
	int		dist;
	int		sierp;
	t_sierp	s;
}	t_data;

//check_inputs.c
void		print_valid_params(void);
int			ft_isdigit(char c);
int			ft_is_double(const char *str);
int			check_input_2(char **av);
int			check_input(int ac, char **av);
//color.c
int			get_color_component(int base_color, int next_color,
				double ratio, int i);
int			get_color_2(int out_color, int int_color,
				int iterations, int max_iterations);
void		update_colors(t_data *data, int iterations);
int			get_color_1(t_data *data, int x_c, int y_c, int iterations);
//cmplx.c
t_cmplx		add(t_cmplx a, t_cmplx b);
t_cmplx		mult(t_cmplx a, t_cmplx b);
//draw_fractal.c
void		draw_fractal(t_data*data, double x, double y);
void		draw_mandelbrot(t_data*data, double x, double y, t_cmplx z);
void		draw_julia(t_data*data, double x, double y, t_cmplx z);
//ft_atoi_f.c
double		ft_atoi_f_2(const char *str, double fraction, double result);
double		ft_atoi_f(const char *str);
//inits.c
t_data		*data_init_3(t_data *data);
t_data		*data_init_2(t_data *data, char **av);
t_data		*data_init(char **av);
//inputs.c
void		draw_if(t_data *data);
void		key_hook_2(int keycode, t_data *data);
int			key_hook(int keycode, t_data *data);
int			mouse_hook(int button, int x, int y, t_data *data);
//input_utils.c
void		xy_lim_zoom(t_data *data, double zoom_factor,
				int mouse_x, int mouse_y);
void		xy_lim_add(t_data *data, double dx, double dy);
int			close_window(t_data *data);
double		zoom_limit(t_data *data);
//utils.c
void		pixel_put_img(t_data *data, int x, int y, int color);
int			ft_strcmp(char *s1, char *s2);
void		ft_put_error(char *s);
int			ft_strlen(char const *str);
// sierpinski.c
int			sierp_util(t_sierp *s, double *d);
//sierpinski.c
static void	init_sierpinski(t_data *data, double x, double y);
static void	update_sierpinski_point(t_data *data);
int			draw_sierpinski(t_data *data, double x, double y);

#endif
