/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:52:14 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 20:50:58 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include <fcntl.h>

# define READ 0
# define WRITE 1

# define OLD 0
# define NEW 1

void	open_pipe(int fd[2]);

#endif
