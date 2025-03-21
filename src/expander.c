
#include <minishell.h>

char    *search_env(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            return (env->value);
        }
        env = env->next;
    }
    return (NULL);
}

/* void    expander(t_token *tok_lst, t_env *env_lst)
{
    char    *sub;
    char    *temp;
    char    *new_word;
    int     i, j;

    while (tok_lst)  
    {
        i = 0;
        while (tok_lst->word[i])
        {
            if (!ft_strchr(tok_lst->word, '"') && !ft_strchr(tok_lst->word, '\''))
            {
                while (tok_lst->word[i] && tok_lst->word[i] != '$')
                    i++;
                if (!tok_lst->word[i] || tok_lst->word[i] != '$')
                    break;
                j = ++i;
                while (tok_lst->word[j] && tok_lst->word[j] != ' ' && tok_lst->word[j] != '\t' && tok_lst->word[j] != '\0' && tok_lst->word[j] != '$')
                    j++;
                sub = ft_substr(tok_lst->word, i, j - i);
                temp = search_env(env_lst, sub);
                free(sub);

                if (temp)
                {
                    new_word = ft_strjoin(ft_substr(tok_lst->word, 0, i - 1), temp);
                    new_word = ft_strjoin(new_word, ft_substr(tok_lst->word, j, ft_strlen(tok_lst->word) - j));
                    free(tok_lst->word);
                    tok_lst->word = new_word;
                }
                else
                {
                    new_word = ft_substr(tok_lst->word, 0, i - 1);
                    free(tok_lst->word);
                    tok_lst->word = new_word;
                    i++;
                }
            }
            i++;
        }
        tok_lst = tok_lst->next;
    }
} */ 

void    replace(t_token *p, t_env *envp)
{
    int i;
    int j;
    char    *temp;
    char    *env;

    i = 0;
    j = 0;
    while (p)
    {
    }
}

void    expander(t_token *tok_lst, t_env *env_lst)
{
    t_token *p;

    (void)env_lst;
    p = NULL;
    break_string(&p, tok_lst->word);
    replace(p, env_lst);
    print_list(p);
}