/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:15:30 by msakovyc          #+#    #+#             */
/*   Updated: 2018/06/16 16:16:07 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_base(char *s, int base)
{
	int result;
	int minus;

	result = 0;
	minus = 0;
	while (*s == ' ' || (*s > 8 && *s < 14) || (*s == '0') || *s == 'x')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-' && base == 10)
			minus = 1;
		s++;
	}
	while ((*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= 'F')
			|| (*s >= 'a' && *s <= 'f'))
		if (*s >= '0' && *s <= '9')
			result = result * base + (int)*s++ - '0';
		else if (*s >= 'A' && *s <= 'F')
			result = result * base + (int)*s++ - 'A' + 10;
		else
			result = result * base + (int)*s++ - 'a' + 10;
	if (minus && base == 10)
		return (-result);
	return (result);
}
