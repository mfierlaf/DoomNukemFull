/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:11:51 by mfierlaf          #+#    #+#             */
/*   Updated: 2019/10/11 12:07:45 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"
#include <fcntl.h>

int	ft_file_size_line(char *file)
{
	int		fd;
	int		result;
	char	*line;

	result = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		result++;
	}
	return (result);
}
