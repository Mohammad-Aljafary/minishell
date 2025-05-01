#include <minishell.h>

void    clear_all(t_all *all)
{
    if (all->tok_lst)
        clear_list(&all->tok_lst);
    if (all->env_lst)
        clear_list_env(&all->env_lst);
    if (all->exp_lst)
        clear_list_env(&all->exp_lst);
}
