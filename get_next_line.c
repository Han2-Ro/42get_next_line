/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2023/09/27 19:16:44 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_after(char **str, int len)
{
	int		i;
	int		j;
	char	*res;
	char	*remainder;

	i = 0;
	j = 0;
	if (len <= 0)
		len = ft_strlen(*str);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, *str, len + 1);
	remainder = malloc((ft_strlen(*str) - len + 1) * sizeof(char));
	if (!remainder)
		return (NULL);
	ft_strlcpy(remainder, *str + len, ft_strlen(*str) - len + 1);
	free(*str);
	*str = remainder;
	return (res);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	static char	*str = NULL;
	int			nl_i;
	void		*ptr;

	if (!str)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	nl_i = get_i_of_newline(str);
	while (nl_i < 0)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			if (*str)
				return (trim_after(&str, nl_i + 1));
			else
				return (free(str), str = NULL, NULL);
		}
		ptr = str;
		str = ft_strjoin(str, buffer);
		if (!str)
			return (NULL);
		free(ptr);
		nl_i = get_i_of_newline(str);
	}
	return (trim_after(&str, nl_i + 1));
}
