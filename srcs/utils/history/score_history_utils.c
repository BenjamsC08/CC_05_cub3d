/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_history_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 07:51:56 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/15 07:55:09 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_time_format(char *line)
{
	int	res_sec;

	if (!line || ft_strlen(line) < 5)
		return (FALSE);
	if (ft_isdigit(line[0]) && ft_isdigit(line[1]) && line[2] == ':'
		&& ft_isdigit(line[3]) && ft_isdigit(line[4]))
	{
		res_sec = ((line[3] - '0') * 10) + (line[4] - '0');
		if (res_sec > 59)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static int	convert_and_compute(char *new_min, char *new_sec,
	char *last_min, char *last_sec)
{
	int	new_curr;
	int	last_curr;

	new_curr = ft_atoi(new_min);
	last_curr = ft_atoi(last_min);
	if (last_curr < new_curr)
		return (free(new_min), free(new_sec),
			free(last_min), free(last_sec), -1);
	new_curr = ft_atoi(new_sec);
	last_curr = ft_atoi(last_sec);
	if (last_curr <= new_curr)
		return (free(new_min), free(new_sec),
			free(last_min), free(last_sec), -1);
	return (free(new_min), free(new_sec), free(last_min), free(last_sec), TRUE);
}

int	is_better_time(t_game *game, char *new)
{
	char	*new_min;
	char	*new_sec;
	char	*last_min;
	char	*last_sec;

	new_min = ft_strndup(new, 2);
	if (!new_min)
		return (FALSE);
	new_sec = ft_strndup(new + 3, 2);
	if (!new_sec)
		return (free(new_min), FALSE);
	if (game->data_desc->last_best_time)
	{
		last_min = ft_strndup(game->data_desc->last_best_time, 2);
		if (!last_min)
			return (free(new_min), free(new_sec), FALSE);
		last_sec = ft_strndup(game->data_desc->last_best_time + 3, 2);
		if (!last_sec)
			return (free(new_min), free(new_sec), free(last_min), FALSE);
		return (convert_and_compute(new_min, new_sec, last_min, last_sec));
	}
	return (free(new_min), free(new_sec), TRUE);
}
