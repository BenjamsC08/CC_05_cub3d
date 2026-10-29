/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 08:49:54 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/11 08:50:20 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	now_ms(void)
{
	struct timeval	tv;
	unsigned int	ms;

	gettimeofday(&tv, NULL);
	ms = (unsigned int)(tv.tv_sec * 1000u + tv.tv_usec / 1000u);
	return (ms);
}
