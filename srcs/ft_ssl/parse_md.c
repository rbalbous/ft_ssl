/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_md.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:50:24 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/16 17:27:00 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				parse_md(t_args *args, t_infos *infos, char **str, int argc)
{
	if (str[2] == NULL)
	{
		treat_file(args, infos, NULL, 0);
		return (1);
	}
	argc = get_flags_args(args, infos, str, argc);
	return (1);
}
