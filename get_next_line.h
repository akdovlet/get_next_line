/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:40:25 by akdovlet          #+#    #+#             */
/*   Updated: 2026/05/20 09:13:29 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

int		ak_strchr(char *str, int c);
int		ak_strlen(char *str);
char	*ak_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*read_to_newline(int fd, char *buffer);
void	clean_static(char *buffer);
char	*extract_line(char *tmp);

#endif
