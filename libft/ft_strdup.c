/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 04:20:38 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/08/08 04:20:38 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*new_str;
	unsigned int	i;

	i = 0;
	if (!s)
		return ((void *)0);
	new_str = (char *)malloc(ft_strlen(s) + 1);
	if (!new_str)
		return ((void *)0);
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
