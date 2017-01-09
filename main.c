/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:16:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 19:16:46 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_env *env, char **ev)
{
	int i;

	i = 0;
	env->input = NULL;
	while (ev[i])
		++i;
	env->ev = malloc(sizeof(char *) * (i + 1));
	env->ev[i] = 0;
	while (i--)
		env->ev[i] = ft_strdup(ev[i]);
	env->dir = malloc(4096);
	getcwd(env->dir, 512);
}

t_env		*env(void)
{
	static t_env	env;

	return (&env);
}

void	ft_hello(int i)
{
	i = 0;
}

int main(int ac, char **av, char **ev)
{
	char *buf;
	t_env *envi;

	envi = env();
	set_env(env(), ev);
	buf = malloc(512);
	signal(SIGINT, exit);
	signal(SIGQUIT, exit);
	signal(SIGTERM, exit);
	(void)av;
	(void)ac;
	// (void)ev;
	ft_printf("%s%s %s%s", "\e[0;32m",envi->dir, PROMPT, "\e[0m");
	while (1)
	{
		if ((ft_read(env())) == 0)
			continue ;
		else if(ft_read(env()) == -1)
			break ;
	}
	ft_putstr("GOODBYE\n");
}
