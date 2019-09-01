/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 21:06:12 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/01 16:46:41 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			do_hash(t_args *args, char *str, char *file)
{
	static void	(*hash[2])(t_args*, char*, char*) = {md5, sha256};

	hash[args->md](args, str, file);
}

void			trim_str(t_args *args, char *str, char *file, int i)
{
	char		*to_hash;
	int			index;

	to_hash = NULL;
	index = 0;
	while (str[i + index] != 0 && str[i + index] != ' ' && str[i + index] != '	')
	{
		index++;
	}
	if (str[i + index] == 0)
		do_hash(args, str + i, file);
	else
	{
		if (!(to_hash = (char *)malloc(sizeof(to_hash) * (index + 1))))
			exit(ft_dprintf(2, "malloc error while initializing 'to_hash'"));
		ft_strncpy(to_hash, str + i, index);
		do_hash(args, to_hash, file);
	}
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

void			treat_file(char *file, int fd, t_args *args)
{
	char		buf[10001];
	char		*str;
	int			ret;
	int			len;
	int			i;

	i = 0;
	str = NULL;
	len = 0;
	while ((ret = read(fd, buf, 10000)) != 0)
	{
		buf[ret] = 0;
		str = ft_strmjoinfree(str, buf, len, ret);
		len = ft_strlen(str);
	}
	do_hash(args, str, file);
}

void			get_prompt(t_args *args)
{
	char		buff[10001];
	char		*str;
	int			ret;
	int			len;
	int			i;

	i = 0;
	str = NULL;
	len = 0;
	while ((ret = read(0, buff, 10000)) != 0)
	{
		buff[ret] = 0;
		str = ft_strmjoinfree(str, buff, len, ret);
		len = ft_strlen(str);
	}
	do_hash(args, str, NULL);
}

int				 parse_args(t_args *args, char *str, int i)
{
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (str[i] == 'p')
		{
			args->arg_p = 1;
			get_prompt(args);
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

int				parse_file(t_args *args, char *str, int i)
{
	char		tmp[256];
	char		*file;
	int			j;
	int			fd;
	int			tmp_i;

	j = 0;
	tmp_i = i;
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	file = ft_memacpy(&tmp, j);
	if (args->arg_s == 1)
	{
		trim_str(args, str, NULL, tmp_i);
		args->arg_s = 0;
	}
	else
	{
		if ((fd = open(file, O_RDONLY)) == -1)
		{
			ft_printf("%s: No such file or directory\n", file);
			return (i);
		}
		treat_file(file, fd, args);
	}
	return (i);
}

void		get_flags_args(t_args *args, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			if (str[i] == '-')
			{
				args->arg_nf = 1;
				if (str[++i] != ' ' && str[i] != '\t')
					disp_usage_exit();
			}
			else
				i = parse_args(args, str, i);
		}
		else if (str[i] != ' ' && str[i] != '\t')
			i = parse_file(args, str, i);
		if (str[i])
			i++;
	}
	if (args->arg_s == 1 && args->arg_nf == 0)
		disp_usage_exit();
	if (args->arg_r == 1 && args->arg_nf == 0)
		get_prompt(args);
}

int				check_mdarg(char *str, char **str_md)
{
	int			i;

	i = 0;
	while (i < CMD_NB)
	{
		if (ft_strcmp(str_md[i], str) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void		get_new_stdin(t_args *args, char **str_md)
{
	char		*str;
	char		*tmp;
	int			i;

	tmp = NULL;
	ft_printf("ft_ssl> ");
	while (1)
	{
		if (get_next_line(1, &str) == -1)
			exit(ft_printf("get next line a pas kiffe\n"));
		i = 0;
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			i++;
		tmp = ft_memacpy(str, i);
		if ((args->md = check_mdarg(tmp, str_md)) > -1)
		{
			if (!str[i])
			{
				get_prompt(args);
				return ;
			}
			get_flags_args(args, str, i);
			return ;
		}
		else
		{
			disp_usage_ssl(str);
			ft_printf("ft_ssl> ");
		}
		free(tmp);
		free(str);
	}
}

char		*split_args(int ac,char **av)
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

void		parser(int argc, char **argv, t_args *args)
{
	char		*str;
	static char *str_md[CMD_NB] = CMD_LINE;

	if (argc > 1)
	{
		if ((args->md = check_mdarg(argv[1], str_md)) > -1)
		{
			str = split_args(argc, argv);
			if (str == NULL)
			{
				get_prompt(args);
				return ;
			}
			get_flags_args(args, str, 0);
			return ;
		}
		else
			disp_usage_ssl_exit(argv[1]);
	}
	get_new_stdin(args, str_md);
}
