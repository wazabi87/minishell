/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 19:16:28 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_read(t_env *env)
{
	env->input = malloc(INPUT_SIZE);
	*env->input = '\0';
	if(get_next_line(1, &env->input) == 0)
		error(1, NULL);
	if (*env->input != '\0')
		ft_reco_cmd(env->input, env);
	env->input[0] = '\0';
	ft_printf("%s%s %s%s", "\e[0;32m", env->dir, PROMPT, "\e[0m");
	return (0);
}

void	ft_echo(char *input)
{
	int		i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		++input;
	if (!input)
		ft_putchar('\n');
	ft_putstr(input);
}

void	ft_cd(char *inp, t_env *env)
{
	int		i;

	i = 0;
	while (inp[i] && (inp[i] == ' ' || inp[i] == '\t' || inp[i] == '\n'))
		++inp;
	if (!inp[i])
	{
		if (chdir("/") == -1)
			error(-1, NULL);
		getcwd(env->dir, 512);
		return ;
	}
	if (inp[ft_strlen(inp) - 1] == '\n')
		inp[ft_strlen(inp) - 1] = '\0';
	if (chdir(inp) == -1)
		error(-1, NULL);
	getcwd(env->dir, 512);
}

void	ft_reco_cmd(char *input, t_env *env)
{
	if (ft_cmpspec(input, "cd", 0) == 1)
		ft_cd(input + 2, env);
	else if (ft_cmpspec(input, "echo", 0) == 1)
		ft_echo(input + 4);
	else if (ft_cmpspec(input, "setenv", 1) == 1)
		add_var_to_env(env, input + 6);
	else if (ft_cmpspec(input, "unsetenv", 1) == 1)
		suppr_var_env(env, input + 8);
	else if (ft_cmpspec(input, "env", 0) == 1)
		print_env(env);
	else if (*input == '\n')
		return ;
	else
		error(-2, input);
}