/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/05/22 00:11:24 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     main(int ac, char **av, char **env)
{
    char *str;
// (void)ac;
// (void)av;
// (void)env;
if (!av[1])
{
    while(1)
    {
       str = readline("minishel> ");
       
        lexer(str);
        add_history(str);
        free(str);
    }
}
    else 
        builts_in(ac, av, env);
}