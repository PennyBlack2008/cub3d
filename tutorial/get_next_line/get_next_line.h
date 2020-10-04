/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 19:22:26 by jikang            #+#    #+#             */
/*   Updated: 2020/06/08 16:20:42 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int						get_next_line(int fd, char **line);

int						safer_free(void **pp);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *string);
void					*ft_memmove(void *dest, const void *src, size_t len);
char					*ft_strjoin(char const *s1, char const *s2);

#endif
