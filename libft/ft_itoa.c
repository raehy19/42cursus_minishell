/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:23:02 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/11 16:18:10 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str, size_t len)
{
	size_t	i;
	char	temp;

	i = 0;
	while (i < len - 1 - i)
	{
		temp = *(str + i);
		*(str + i) = *(str + len - 1 - i);
		*(str + len - 1 - i) = temp;
		++i;
	}
	return (str);
}

size_t	ft_cal_digit(long long n)
{
	size_t	digit;

	digit = 1;
	while (n > 9)
	{
		n /= 10;
		++digit;
	}
	return (digit);
}

size_t	ft_cal_itoa(char *dst, size_t i, long long num)
{
	*(dst + i) = '0' + (num % 10);
	if (num < 10)
		return (i);
	else
		return (ft_cal_itoa(dst, i + 1, num / 10));
}

char	*ft_itoa(int n)
{
	long long	num;
	char		*dst;
	size_t		size;

	size = 0;
	num = (long long) n;
	if (num < 0)
	{
		num *= -1;
		++size;
	}
	size += ft_cal_digit(num);
	dst = (char *) malloc (sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	if (ft_cal_itoa(dst, 0, num) + 1 < size)
		*(dst + size - 1) = '-';
	*(dst + size) = '\0';
	return (ft_strrev(dst, size));
}
