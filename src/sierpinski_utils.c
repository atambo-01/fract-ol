/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:55:59 by atambo            #+#    #+#             */
/*   Updated: 2025/03/26 22:00:50 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	sierp_util(t_sierp *s, double *d)
{
	d[0] = (s->px - s->v0x) * (s->px - s->v0x)
		+ (s->py - s->v0y) * (s->py - s->v0y);
	d[1] = (s->px - s->v1x) * (s->px - s->v1x)
		+ (s->py - s->v1y) * (s->py - s->v1y);
	d[2] = (s->px - s->v2x) * (s->px - s->v2x)
		+ (s->py - s->v2y) * (s->py - s->v2y);
}
