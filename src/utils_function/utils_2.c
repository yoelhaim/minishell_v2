/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:49:23 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/29 10:57:39 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_err(char *firs_s, char *midl_s, char *last_s)
{
	char	*str;

	str = NULL;
	if (!firs_s)
		return (NULL);
	if (midl_s && last_s)
		str = ft_strjoin(firs_s, ft_strjoin(midl_s, last_s));
	else if (!midl_s && last_s)
		str = ft_strjoin(firs_s, last_s);
	else
		str = "error ";
	return (str);
}

int	checkerr_red(char *buff, int tmp_red, t_node *str)
{
	if ((!strcmp(buff, "<") || !strcmp(buff, "<<") \
	|| !strcmp(buff, ">") || !strcmp(buff, ">>")) \
	&& (tmp_red >= 3 && tmp_red <= 6))
	{
		if (str->next->type == 1 && str->next->next != NULL)
			str = str->next;
		if (str->next->type != 11 && str->next->type != 9)
			return (ft_putstr_fd(create_err(NL_ERROR_MESSSAGE \
			, NULL, "\n"), 2), ERROR_RETURN);
	}
	return (1);
}
