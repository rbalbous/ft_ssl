/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memacpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:17:11 by rbalbous          #+#    #+#             */
/*   Updated: 2019/06/05 23:37:39 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memacpy(const void *src, size_t len)
{
	void	*dest;

	if (!src || len == 0)
		return (NULL);
	if ((dest = ft_memalloc(len + 1)) == 0)
		return (NULL);
	ft_memcpy(dest, src, len);
	return (dest);
}
