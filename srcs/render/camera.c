/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:33:42 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/07 09:47:49 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	camera_build_from_player(t_player *player, t_cam *camera)
{
	float	half_fov_tangent;

	half_fov_tangent = tanf((FOV_DEG * DEGREE) * 0.5f);
	camera->direction.x = cosf(player->angle);
	camera->direction.y = sinf(player->angle);
	camera->plane.x = -camera->direction.y * half_fov_tangent;
	camera->plane.y = camera->direction.x * half_fov_tangent;
}
