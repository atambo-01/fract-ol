/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:19:16 by atambo            #+#    #+#             */
/*   Updated: 2024/09/28 15:19:18 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_cmplx	add(t_cmplx a, t_cmplx b)
{
	t_cmplx	res;

	res.r = a.r + b.r;
	res.i = a.i + b.i;
	return (res);
}

t_cmplx	mult(t_cmplx a, t_cmplx b)
{
	t_cmplx	res;

	res.r = (a.r * b.r) - (a.i * b.i);
	res.i = (a.r * b.i) + (a.i * b.r);
	return (res);
}
