/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-duf <cvan-duf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 10:47:37 by cvan-duf          #+#    #+#             */
/*   Updated: 2019/06/11 12:46:39 by cvan-duf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			ft_swap_float(float *a, float *b)
{
	float		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}