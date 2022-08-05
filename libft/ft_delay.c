/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:43:46 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/20 16:55:41 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

void	ft_delay(int m_secs)
{
	int		start_time;

	start_time = clock();
	while (clock() < start_time + m_secs)
		;
}
