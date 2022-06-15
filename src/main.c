/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:34:24 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/15 02:53:02 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_init(t_minishell *data)
{
	data->input = NULL;
}

int	main(void)
{
	t_minishell	data;
	char		*buff;
	int			i;

	ft_init(&data);
	i = -1;
	while (++i < 1)
	{
		buff = readline("MINISHELL>");
		tokenizer(&data, buff);
		display_input(data.input);
		free_input(&data.input);
		free(buff);
	}
	return (0);
}
