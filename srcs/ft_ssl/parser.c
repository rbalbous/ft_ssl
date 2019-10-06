/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 21:06:12 by rbalbous          #+#    #+#             */
/*   Updated: 2019/10/06 19:09:43 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			do_hash(t_args *args, t_infos *infos, char *str, char *file)
{
	static void	(*hash[4])(t_args*, t_infos *, char*, char*) = {md5, sha256, base64};

	hash[infos->md - 1](args, infos, str, file);
}

size_t	countwords(const char *s)
{
	size_t	count_words;
	size_t	i;

	count_words = 0;
	if (s[0] != ' ' || s[0] != '\t')
		count_words++;
	i = 0;
	while (s[++i])
		if (s[i] != ' ' &&  s[i] != '\t' 
		&& (s[i - 1] == ' ' || s[i - 1] == '\t'))
			count_words++;
	return (count_words);
}

char			**strsplit(const char *s, int *argc, char **str)
{
	size_t	i;
	size_t	index;
	size_t	ct_let;

	index = -1;
	i = 1;
	if (!s)
		return (NULL);
	if ((str = (char**)malloc(sizeof(char*) * (countwords(s) + 1 + 1))) == 0)
		return (NULL);
	str[0] = 0;
	while (++index < ft_strlen(s))
	{
		ct_let = 0;
		if (s[ct_let + index] != ' ' && s[ct_let + index] != '\t'
		&& s[ct_let + index] != '\0')
		{
			while (s[ct_let + index] != ' ' && s[ct_let + index] != '\t'
			&& index + ct_let < ft_strlen(s))
				ct_let++;
			str[i] = ft_strsub(s, (unsigned int)index, ct_let);
			index += ct_let - 1;
			i++;
		}
	}
	str[i] = 0;
	*argc = i - 1;
	return (str);
}

char			*ft_strmjoinfree(char const *s1, char const *s2, int len_s1
					, int len_s2)
{
	char	*str;
	int		i;

	i = 0;
	if ((str = (char*)malloc(sizeof(str) * (len_s1 + len_s2) + 1)) == 0)
		return (NULL);
	if (s1 != NULL)
		ft_strcpy(str, s1);
	while (len_s2 > i)
	{
		str[i + len_s1] = s2[i];
		i++;
	}
	str[len_s1 + i] = 0;
	free((void*)s1);
	return (str);
}

void			treat_file(t_args *args, t_infos *infos, char *file, int fd)
{
	char		buf[10001];
	char		*str;
	int			ret;
	int			len;
	int			i;

	i = 0;
	str = NULL;
	len = 0;
	infos->len = 0;
	while ((ret = read(fd, buf, 10000)) != 0)
	{
		infos->len += ret;
		buf[ret] = 0;
		str = ft_strmjoinfree(str, buf, len, ret);
		len = infos->len;
	}
	do_hash(args, infos, str, file);
}

int				 parse_args(t_args *args, t_infos *infos, char *str, int i)
{
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (str[i] == 'p')
		{
			args->arg_p = 1;
			treat_file(args, infos, NULL, 0);
		}
		else if (str[i] == 'q')
			args->arg_q = 1;
		else if (str[i] == 's')
		{
			args->arg_s = 1;
			return (i);
		}
		else if (str[i] == 'r')
		{
			args->arg_r = 1;
		}
		else
			exit(ft_dprintf(2, "Illegal option -- %c\nusage: ", str[i]) + 
			ft_dprintf(2, USAGE));
		i++;
	}
	return (i);
}

int				parse_file(t_args *args, t_infos *infos, char *str, int i)
{
	char		tmp[256];
	char		*file;
	int			fd;
	int			tmp_i;

	tmp_i = i;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	file = ft_memacpy(&tmp, i);
	if (args->arg_s == 1)
	{
		do_hash(args, infos, str, NULL);
		args->arg_s = 0;
	}
	else
	{
		if ((fd = open(file, O_RDONLY)) == -1)
		{
			ft_printf("%s: No such file or directory\n", file);
			return (i);
		}
		treat_file(args, infos, file, fd);
	}
	return (i);
}

int			get_flags_args(t_args *args, t_infos *infos, char **str, int argc)
{
	int i;
	int	end;

	end = 2;
	while (end < argc)
	{
		i = 0;
		if (str[end][i] == '-')
		{
			i++;
			if (str[end][i] == '-')
			{
				args->arg_nf = 1;
				if (str[end][++i] != ' ' && str[end][i] != '\t')
					disp_usage(args);
			}
			else
				i = parse_args(args, infos, str[end], i);
		}
		else if (str[end][i] != ' ' && str[end][i] != '\t')
			i = parse_file(args, infos, str[end], i);
		if (str[i])
			i++;
		end++;
	}
	if (args->arg_s == 1 && args->arg_nf == 0)
		disp_usage(args);
	if (args->arg_r == 1 && args->arg_nf == 0)
	{
		treat_file(args, infos, NULL, 0);
	}
	return (end);
}

void			check_mdarg(t_args *args, t_infos *infos, char **str, int argc)
{
	static char *str_md[CMD_NB] = CMD_LINE;
	int			i;
	int			(*parsing[CMD_NB + 1])() = {disp_usage, parse_md, parse_md, parse_base64};

	i = CMD_NB - 1;
	while (i > 0)
	{
		if (ft_strcmp(str_md[i], str[1]) == 0)
		{
			break ;
		}
		i--;
	}
	infos->md = i;
	parsing[i](args, infos, str, argc);
}

void		get_new_stdin(t_args *args, t_infos *infos)
{
	char		*str;
	char		*tmp;
	char		**argv;
	int			argc;
	int			i;

	tmp = NULL;
	argc = 0;
	argv = NULL;
	ft_printf("ft_ssl> ");
	while (1)
	{
		if (get_next_line(1, &str) == -1)
			exit(ft_printf("get next line a pas kiffe\n"));
		i = 0;
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			i++;
		tmp = ft_memacpy(str, i);
		argv = strsplit(tmp, &argc, argv);
		infos->error = 2;
		check_mdarg(args, infos, argv, 1);
		ft_printf("ft_ssl> ");
		free(tmp);
		free(str);
	}
}

char		*split_args(int ac, char **av)
{
	char 	*str;
	int		count;
	int		i;
	int		j;

	i = 2;
	count = 0;
	j = 0;
	str = NULL;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			count++;
			j++;
		}
		count++;
		i++;
	}
	count--;
	str = ft_memacpy(av[2], count);
	i = 0;
	while (i < count)
	{
		if (str[i] == 0)
		{
			str[i] = ' ';
		}
		i++;
	}
	return (str);
}

void		parser(int argc, char **argv, t_args *args, t_infos *infos)
{
	if (argc > 1)
	{
		check_mdarg(args, infos, argv, argc);
	}
	else
		get_new_stdin(args, infos);
}
