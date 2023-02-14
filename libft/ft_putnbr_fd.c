/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:51:12 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/13 21:57:20 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cal_putnbr(long long n, int fd)
{
	char	c;

	if (n > 9)
		ft_cal_putnbr(n / 10, fd);
	c = (char)('0' + (n % 10));
	write(fd, &c, 1);
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	num = (long long) n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	ft_cal_putnbr(num, fd);
	return ;
}
