#include "minishell.h"

char *ft_parse_quote(t_list **args, char *buffer, char c)
{
     int k;
     int j;
     char buff[200];

     k = 0;
     j = 0;
     while (*buffer)
     {
          if (k == 0 && (*buffer == '\t' || *buffer == ' '))
               break;
          else if (*buffer == c)
               k = (k + 1) % 2;
          else
               buff[j++] = *buffer;
          buffer++;
     }
     buff[j++] = 0;
     if (!k)
          ft_lstpushback(args, buff, j);
     else
     {
          ft_print_error(0, ERR_UNMATCHED, c);
          return (NULL);
     }
     return (buffer);
}

t_list *ft_parsecmd(char *buffer)
{
     char c;
     char *tmp;
     int i;
     t_list *args;

     args = NULL;
     while (*buffer)
     {
          buffer = ft_skip_chars(buffer, "\t ");
          tmp = ft_skip_unitl_char(buffer, "\t '\"");
          i = tmp - buffer;
          if ((c = *tmp) == '"' || c == '\'')
          {
               if (!(buffer = ft_parse_quote(&args, buffer, c)))
                    return (NULL);
          }
          else
          {
               buffer[i++] = 0;
               ft_lstpushback(&args, buffer, i);
               buffer += i - !c;
          }
     }
     return (args);
}

void	ft_parse_dollar(t_list **args, t_list **env)
{
	char *dolr;
	char *tmp;
	t_list **arg;
	t_list **var_env;
	int len_var;

	arg = args;
	while (*arg)
	{
		while ((dolr = ft_strchr((*arg)->content, '$')) && dolr[1])
		{
			*dolr++ = 0;
			len_var = ft_skip_unitl_char(dolr, " \t$") - dolr;
			tmp = "";
			if (*dolr == '$' && (dolr++ || 1))
				tmp = PID;
			else if ((var_env = ft_lstfind(env, dolr, len_var)))
				tmp = (*var_env)->content + len_var + 1;
			ft_lstmodifone((*arg), ft_strnjoin(C_TAB{(*arg)->content, tmp, dolr + len_var}, 3));
			dolr += len_var;
		}
		if (strlen((*arg)->content) == 0)
				ft_lstonedel(arg);
		else
		arg = &(*arg)->next;
	}
}

int ft_parse_tilde(t_list **args, t_env_var *var)
{
	char *tilde;
	char *user;
	t_list *arg;

	arg = *args;
	while (arg)
	{
		tilde = arg->content;
		if (tilde && tilde[0] == '~')
		{
			*tilde++ = 0;
			if (!*tilde || *tilde == '/')
				ft_lstmodifone(arg, ft_strjoin(var->home->content + 5, tilde));
			else if ((user = ft_strjoin("/Users/", tilde)) && !access(user, F_OK))
				ft_lstmodifone(arg, user);
			else
               {
                    ft_print_error(tilde, ERR_UKNUSR, 0);
				return (0);
               }
		}
		arg = arg->next;
	}
	return (1);
}