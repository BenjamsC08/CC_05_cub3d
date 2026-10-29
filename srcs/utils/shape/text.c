/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:11:58 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 11:11:58 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_text	get_text(char *str, t_uint size, int color, t_rect frame)
{
	t_text	text;

	text.str = str;
	text.size = size;
	text.color = color;
	text.frame = frame;
	return (text);
}
