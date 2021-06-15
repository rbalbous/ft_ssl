/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 16:52:42 by rbalbous          #+#    #+#             */
/*   Updated: 2020/10/10 15:05:00 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t g_base_64[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'
};

void	init_base(t_base *base, t_infos *infos, char *str, uint32_t i)
{
	uint32_t	h;

	h = ((uint32_t)str[i]) << 16;
	if (i + 1 < infos->len)
		h += ((uint32_t)str[i + 1]) << 8;
	if (i + 2 < infos->len)
		h += ((uint32_t)str[i + 2]);
	base->h0 = (uint8_t)(h >> 18) & 63;
	base->h1 = (uint8_t)(h >> 12) & 63;
	base->h2 = (uint8_t)(h >> 6) & 63;
	base->h3 = (uint8_t)h & 63;
}

uint8_t		get_base_index(char i)
{
	uint8_t	index;

	index = 0;
	while (index < 64 && g_base_64[index] != i)
	{
		index++;
	}
	if (index == 64)
		index = 0;
	return (index);
}

void	init_decrypt_base(t_base *base, char *str, uint32_t i)
{
	if (str[i] == '\n')
		i++;
	if (!(str[i]))
		exit(ft_dprintf(2, "decrypt error %d", i));
	base->h0 = get_base_index(str[i]);
	if (!(str[i + 1]))
		exit(ft_dprintf(2, "decrypt error %d", i + 1));
	base->h1 = get_base_index(str[i + 1]);
	if (!(str[i + 2]))
		exit(ft_dprintf(2, "decrypt error %d", i + 2));
	base->h2 = get_base_index(str[i + 2]);
	if (!(str[i + 3]))
		exit(ft_dprintf(2, "decrypt error %d", i + 3));
	base->h3 = get_base_index(str[i + 3]);
	base->r0 = (base->h0 << 2);
	base->r0 = base->r0 ^ (base->h1 >> 4);
	base->r1 = (base->h1 << 4);
	base->r1 = base->r1 ^ (base->h2 >> 2);
	base->r2 = base->h2 << 6;
	base->r2 = base->r2 ^ base->h3;
}

uint32_t	add_elem(char *result, uint32_t result_index, uint8_t base)
{
	static int count = 0;

	result[result_index] = g_base_64[base];
	count++;
	result_index++;
	if (count == 64)
	{
		result[result_index] = '\n';
		result_index++;
		count = 0;
	}
	return (result_index);
}

uint32_t	count_letters(char *str)
{
	uint32_t i;
	uint32_t count;

	i = 0;
	count = 0;
	while (str [i])
	{
		if ((str[i] >= 'A' &&  str[i] <= 'Z')
		|| (str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= '0' && str[i] <= '9') 
		|| str[i] == '+' || str[i] == '/' || str[i] == '=')
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	*new_str(t_infos *infos, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char*)malloc(sizeof(tmp) * (infos->len + 1))))
		exit(ft_dprintf(2, "malloc error\n"));
	while (str[i])
	{
		if ((str[i] >= 'A' &&  str[i] <= 'Z') 
		|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')
		|| str[i] == '+' || str[i] == '/' || str[i] == '=')
		{
			tmp[j] = str[i];
			if (str[i] == '=')
				infos->len--;
			j++;
		}
		i++;
	}
	return (tmp);
}

void	base_decrypt(t_infos *infos, char *str)
{
	uint32_t	index_input;
	uint32_t	result_index;
	char		*result;
	uint32_t	tot_len;
	t_base		base;

	index_input = 0;
	result_index = 0;
	infos->len = count_letters(str);
	if (infos->len % 4 != 0)
		return ;
	str = new_str(infos, str);
	tot_len = (infos->len * 3) / 4;
	if (!(result = (char*)malloc(sizeof(result) * (tot_len + 1))))
		exit(ft_dprintf(2, "malloc error\n"));
	while (str[index_input] && index_input < infos->len)
	{
		init_decrypt_base(&base, str, index_input);
		result[result_index++] = base.r0;
		result[result_index++] = base.r1;
		result[result_index++] = base.r2;
		index_input += 4;
	}
	result[result_index] = 0;
	ft_printf("%s", result);
}

void	base64(t_args *args, t_infos *infos, char *str, char *file)
{
	(void)file;
	uint32_t	index_input;
	uint32_t	result_index;
	t_base		base;
	char		*result;
	uint32_t	tot_len;
	uint32_t	add_padding;

	if (!str)
		return;
	if (args->arg_d == 1)
		return (base_decrypt(infos, str));
	index_input = 0;
	result_index = 0;
	add_padding = infos->len % 3;
	tot_len = (infos->len * 4) / 3 + infos->len % 3;
	tot_len += tot_len / 64;
	if (!(result = (char*)malloc(sizeof(result) * (tot_len + 1))))
		exit(ft_dprintf(2, "malloc error\n"));
	base = (t_base){0, 0, 0, 0, 0, 0, 0};
	while (index_input < infos->len)
	{
		init_base(&base, infos, str, index_input);
		result_index = add_elem(result, result_index, base.h0);
		result_index = add_elem(result, result_index, base.h1);
		if (index_input + 1 < infos->len)
			result_index = add_elem(result, result_index, base.h2);
		if (index_input + 2 < infos->len)
			result_index = add_elem(result, result_index, base.h3);
		index_input += 3;
	}
	if (add_padding > 0)
	{
		while (add_padding < 3)
		{
			result[result_index++] = '=';
			add_padding++;
		}
	}
	result[result_index] = 0;
	ft_printf("%s\n", result);
}

int		get_file_base(t_args *args, t_infos *infos, char **str, int index)
{
	int		i;
	char	*file;

	i = 0;
	index++;
	if (!str[index])
		exit(ft_dprintf(2, "file error :\nusage: -i <file>"));
	file = ft_strdup(str[index]);
	parse_file(args, infos, file, 0);
	return (1);
}

int		parse_base_flags(t_args *args, t_infos *infos, char **str, int argc)
{
	int32_t		index;
	uint32_t	i;

	index = 2;
	while (index < argc)
	{
		i = 0;
		if (str[index][i] != '-' || !str[index][++i])
			exit(ft_dprintf(2, "invalid argument %s\n", str[index]));
		while (str[index][i])
		{
			if (str[index][i] == 'i')
			{
				get_file_base(args, infos, str, index);
				if (index + 2 >= argc)
					return (1);
				else
				{
					index += 2;
					i = 0;
					if (str[index][i] != '-' || !str[index][++i])
						exit(ft_dprintf(2, "invalid argument %s\n", str[index]));
					continue ;
				}
			}
			else if (str[index][i] == 'o')
			{
				args->arg_o = 1;
			}
			else if (str[index][i] == 'e')
			{
				args->arg_e = 1;
				args->arg_d = 0;
			}
			else if (str[index][i] == 'd')
			{
				args->arg_e = 0;
				args->arg_d = 1;
			}
			else
				exit(ft_dprintf(2, "unknown option %s\n", str[index]));
			i++;
		}
		index++;
	}
	return (0);
}

int		parse_base64(t_args *args, t_infos *infos, char **str, int argc)
{
	(void)str;

	if (argc < 3)
	{
		treat_file(args, infos, NULL, 0);
		return (1);
	}
	else
	{
		if (!(parse_base_flags(args, infos, str, argc)))
			treat_file(args, infos, NULL, 0);
	}
	return (0);
}
