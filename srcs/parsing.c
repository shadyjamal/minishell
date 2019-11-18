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
          ft_putendl("unmatched c");
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