/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:31 by astalha           #+#    #+#             */
/*   Updated: 2023/05/26 15:16:30 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
#define MINISHEL_H

#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

 enum words_types{
    word,
    sq_word,
    dq_word,
    r_redirect,
    l_redirect,
    here_doc, 
    append,
    pi_pe,
    space};

typedef struct s_expand
{
    char    *word;
    int     exp;
    struct s_expand *next;
}               t_expand;

typedef struct s_list_env
{
    char *variable;
    char *content;
    int     c;
    struct s_list_env *next;
}               t_list_env;

typedef struct s_infos
{
    int     n_pipes;
    int     is_quote;
    int     flag;
    int     pos;
    int     start;
    int     len;
    int     is_finish;
    t_list_env  *env;
}               t_infos;

typedef struct s_data
{
    char    *word;
    int    type;
    t_expand    *vars;
    t_infos *infos;
    struct  s_data *next;
}              t_data;


int quoting_checker(char *str);
t_data    *lexer(char *str, t_infos *infos);
char	*ft_substr_parse(char const *s, t_infos	*infos);
//linked_list
void	ft_lstadd_back(t_data **lst, t_data *new);
void	ft_lstadd_front(t_data **lst, t_data *new);
int	ft_lstsize(t_data *lst);
t_data	*ft_lstlast(t_data *lst);
t_data	*ft_lstnew(char *content, t_infos	*infos);
//cleaners
void     clean_list(t_data   **lst_words);


int     syntaxe_checker(t_data  *cmd_line);
int     strat_end_checker(char *str);
void    get_the_dollar(t_data   *cmd_line);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strrchr_env(const char *s, int c);
int	builts_in(int ac, char **av, char **env);
void    print_error(int code, int type);
void	grep_env(char **env, t_list_env **enev);

t_expand	*ft_lstnew_exp(char *content, t_infos	*infos);
void	ft_lstadd_back_exp(t_expand **lst, t_expand *new);
#endif

