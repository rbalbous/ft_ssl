/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_md.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:50:24 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/10 23:55:08 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				parse_md(char **str, t_args *args, int argc)
{
	if (str[2] == NULL)
	{
		get_prompt(args);
		return (1);
	}
	argc = get_flags_args(args, str, argc);
	return (1);
}
