# Libft - Your Custom C Library - ⭐Grade 125/100

#### Grade rating
- ✅ = Okay project
- ⭐ = Outstanding project

This project consisted on elaborating a custom library with basic functions, mostly from libc. The Libft project allowed me to understand how these functions work, how to implement them, and how to use them.
## Functions from libc

These functions share the same prototypes and implement the same behaviors as the original functions.

- isalpha
- isdigit
- isalnum
- isascii
- isprint
- strlen
- memset
- bzero
- memcpy
- memmove
- strlcpy
- strlcat
- toupper
- tolower
- strchr
- strrchr
- strncmp
- memchr
- memcmp
- strnstr
- atoi
- calloc
- strdup

## Additional Functions

### ft_substr

- Description: Creates a substring from a string.
- Prototype: `char *ft_substr(char const *s, unsigned int start, size_t len)`;

### ft_strjoin

- Description: Concatenates two strings.
- Prototype: `char *ft_strjoin(char const *s1, char const *s2);`

### ft_strtrim

- Description: Removes specified characters from the beginning and end of a string.
- Prototype: `char *ft_strtrim(char const *s1, char const *set);`

### ft_split

- Description: Splits a string into an array of substrings.
- Prototype: `char **ft_split(char const *s, char c);`

### ft_itoa

- Description: Converts an integer to a string.
- Prototype: `char *ft_itoa(int n);`

### ft_strmapi

- Description: Applies a function to each character of a string.
- Prototype: `char *ft_strmapi(char const *s, char (*f)(unsigned int, char));`

### ft_striteri

- Description: Applies a function to each character of a string with index.
- Prototype: `void ft_striteri(char *s, void (*f)(unsigned int, char*));`

### ft_putchar_fd

- Description: Writes a character to a file descriptor.
- Prototype: `void ft_putchar_fd(char c, int fd);`

### ft_putstr_fd

- Description: Writes a string to a file descriptor.
- Prototype: `void ft_putstr_fd(char *s, int fd);`

### ft_putendl_fd

- Description: Writes a string followed by a newline to a file descriptor.
- Prototype: `void ft_putendl_fd(char *s, int fd);`

### ft_putnbr_fd

- Description: Writes an integer to a file descriptor.
- Prototype: `void ft_putnbr_fd(int n, int fd);`

### ft_lstnew

- Description: Creates a new list node.
- Prototype: `t_list *ft_lstnew(void *content);`

### ft_lstadd_front

- Description: Adds a node to the front of a list.
- Prototype: `void ft_lstadd_front(t_list **lst, t_list *new);`

### ft_lstsize

- Description: Counts the number of nodes in a list.
- Prototype: `int ft_lstsize(t_list *lst);`

### ft_lstlast

- Description: Returns the last node of a list.
- Prototype: `t_list *ft_lstlast(t_list *lst);`

### ft_lstadd_back

- Description: Adds a node to the end of a list.
- Prototype: `void ft_lstadd_back(t_list **lst, t_list *new);`

### ft_lstdelone

- Description: Deletes a node and its content.
- Prototype: `void ft_lstdelone(t_list *lst, void (*del)(void *));`

### ft_lstclear

- Description: Deletes all nodes in a list.
- Prototype: `void ft_lstclear(t_list **lst, void (*del)(void *));`

### ft_lstiter

- Description: Applies a function to each node in a list.
- Prototype: `void ft_lstiter(t_list *lst, void (*f)(void *));`



