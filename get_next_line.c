/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2023/09/20 16:07:49 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	x = 0;
	char		*buffer;
	char		*str;
	int 		nl_i;
	void		*ptr;

	buffer = malloc(BUFFER_SIZE * sizeof(char));
	while (nl_i < 0)
	{
		read(fd, buffer, BUFFER_SIZE);
		ptr = str;
		str = ft_strjoin(str, buffer);
		free(ptr);
		nl_i = get_i_of_newline(str);
	}
	
	return (NULL);
}
