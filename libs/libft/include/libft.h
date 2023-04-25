/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:43:58 by ccamargo          #+#    #+#             */
/*   Updated: 2022/11/09 19:00:31 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

/**
 * @brief A list of nodes with content.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* <ctype.h> functions: */
/**
 * @brief The ft_isalnum() function checks if the char c is alphanumeric.
 * 
 * @param c A character to be checked.
 * 
 * @return (int) Returns 1 if c is alphanumeric or 0 if c is not alphanumeric.
 */
int			ft_isalnum(int c);

/**
 * @brief The ft_isalpha() function checks if the char c is alphabetic.
 * 
 * @param c A character to be checked.
 * 
 * @return (int) Returns 1 if c is alphabetic or 0 if c is not alphabetic.
 */
int			ft_isalpha(int c);

/**
 * @brief The ft_isascii() function checks if the char c is an ASCII character.
 * 
 * @param c A character to be checked.
 * 
 * @return (int) Returns 1 if c is an ASCII character or 0 if c is not an ASCII
 * character.
 */
int			ft_isascii(int c);

/**
 * @brief The ft_isdigit() function checks if the char c is a number.
 * 
 * @param c A character to be checked.
 * 
 * @return (int) Returns 1 if c is a number or 0 if c is not a number.
 */
int			ft_isdigit(int c);

/**
 * @brief The ft_isprint() checks if the char c is printable.
 * 
 * @param c A character to be checked.
 * 
 * @return (int) Returns 1 if c is printable or 0 if c is not printable.
 */
int			ft_isprint(int c);

/**
 * @brief The ft_toupper() transforms char c to uppercase if it is a lowercase
 * letter.
 * 
 * @param c A character to be transformed.
 * 
 * @return (int) Returns the character c transformed to uppercase or it's
 * original form case c is not a lowercase letter.
 */
int			ft_toupper(int c);

/**
 * @brief The ft_tolower() transforms char c to lowercase if it is a uppercase
 * letter.
 * 
 * @param c A character to be transformed.
 * 
 * @return (int) Returns the character c transformed to lowercase or it's
 * original form case c is not a uppercase letter.
 */
int			ft_tolower(int c);

/* <string.h> functions: */
/* Memory: */
/**
 * @brief The ft_memcmp() function compares the first n bytes (each
 * interpreted as unsigned char) of the memory areas s1 and s2.
 *
 * @param s1 Pointer to the first memory area to be compared.
 * @param s2 Pointer to the second memory area to be compared.
 * @param n Buffer size in bytes.
 * 
 * @return (int) Returns an integer less than, equal to, or greater than zero
 * if the first n bytes of s1 is found, respectively, to be less than, to
 * match, or be greater than the first n bytes of s2.
 */
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief The ft_memchr() function scans the initial n bytes of the memory
 * area pointed to by s for the first instance of c.
 *
 * @param s Pointer to the initial memory area.
 * @param c Character to be searched.
 * @param n Buffer size.
 * 
 * @return (void *) Return a pointer str to the matching byte or NULL if it
 * does not occur.
 */
void		*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief The ft_memset() function fills the first n bytes of the memory area
 * pointed to by s with the constant byte c.
 *
 * @param s Pointer of memory area.
 * @param c Constant byte to fill memory area.
 * @param n Number of bytes to fill.
 * 
 * @return (void *) Returns a pointer to the memory area s.
 */
void		*ft_memset(void *s, int c, size_t n);

/**
 * @brief The ft_memcpy() function copies n bytes from memory area src to
 * memory area dest.
 *
 * @param dest Destination pointer of memory area.
 * @param src Source pointer of memory area.
 * @param n Buffer size in bytes.
 * 
 * @return (void *) Returns a pointer to the memory area dest.
 */
void		*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief The ft_memmove() function copies n bytes from memory area src to
 * memory area dest.
 *
 * @param dest Destination pointer of memory area.
 * @param src Source pointer of memory area.
 * @param n Buffer size in bytes.
 * 
 * @return (void *) Returns a pointer to the memory area dest.
 */
void		*ft_memmove(void *dest, const void *src, size_t n);

/* Strings: */
/**
 * @brief The ft_strlen() function calculates the length of the string pointed
 * to by s, excluding the terminating null byte ('\0').
 *
 * @param s Pointer to the initial area of the string.
 * 
 * @return (size_t) Returns the number of bytes in the string pointed to by s.
 */
size_t		ft_strlen(const char *s);

/**
 * @brief The ft_strdup() function returns a pointer to a new string which is a
 * duplicate of the string s.
 *
 * @param s1 Pointer to the start of the string do be copied.
 * 
 * @return (char *) On success, returns a pointer to the duplicated string. It
 * returns NULL if insufficient memory was available, with errno set to
 * indicate the cause of the error.
 */
char		*ft_strdup(const char *s);

/**
 * @brief The ft_strchr() functions returns a pointer to the first occurrence
 * of the character c in the string s.
 *
 * @param s Pointer to the string memory area.
 * @param c Character to be searched inside the string s.
 * 
 * @return (char *) Return a pointer to the matched character or NULL if the
 * character is not found.
 */
char		*ft_strchr(const char *s, int c);

/**
 * @brief The ft_strrchr() function finds the end of the string `s`, then
 * returns a pointer to the first occurrence of the character `c` in the
 * string `s` by iterating backwards.
 *
 * @param s Pointer to the string memory area.
 * @param c Character to be searched inside the string s.
 * 
 * @return char* Return a pointer to the matched character or NULL if the
 * character is not found.
 */
char		*ft_strrchr(const char *s, int c);

/**
 * @brief The ft_strncmp() function compares the two strings s1 and s2. The
 * locale is not taken into account.
 *
 * @param s1 Pointer to the area of memory of the first string.
 * @param s2 Pointer to the area of memory of the second string.
 * @param n Buffer size in bytes to compare both strings.
 * 
 * @return (int) Return an integer less than, equal to, or greater than zero if
 * s1 (or the first n bytes thereof) is found, respectively, to be less than,
 * to match, or be greater than s2.
 */
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/* BSD (<bsd/string.h>): */
/**
 * @brief The ft_strlcpy() function copies up to size - 1 characters from the
 * NUL-terminated string src to dst, NUL-terminating the result.
 *
 * @param dst Pointer to the destination area of memory.
 * @param src Pointer to the source area of memory.
 * @param size Buffer size in bytes.
 * 
 * @return (size_t) Returns the length of src.
 */
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief The ft_strlcat() function appends the NUL-terminated string src to
 * the end of dst.  It will append at most size - strlen(dst) - 1 bytes,
 * NUL-terminating the result.
 *
 * @param dest Pointer to the destination area of memory.
 * @param src Pointer to the source area of memory.
 * @param size Buffer size in bytes.
 * 
 * @return (size_t) Return the total length of the string, that is the initial
 * length of dst plus the length of src.
 */
size_t		ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief The ft_strnstr() function locates the first occurrence of the
 * null-terminated string little in the string big, where not more than `len`
 * characters are searched. Characters that appear after a `\\0` character are
 * not searched.
 *
 * @param big String to be searched by `little`.
 * @param little String to search in `big`.
 * @param len Number of bytes to search.
 * 
 * @return (char *) If little is an empty string, big is returned. If little
 * occurs nowhere in big, NULL is returned. Otherwise a pointer to the first
 * character of the first occurrence of little is returned.
 */
char		*ft_strnstr(const char *big, const char *little, size_t len);

/* <stdlib.h> functions: */
/**
 * @brief The ft_atoi() function converts the initial portion of the string
 * pointed to by nptr to int.
 *
 * @param nptr Points to the area of memory of the beginning of string to be
 * converted.
 *
 * @return (int) The converted value or 0 on error.
 */
int			ft_atoi(const char *nptr);

/**
 * @brief The calloc() function allocates memory for an array of nmemb
 * elements of size bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero. If nmemb or size is 0, then calloc() returns
 * either NULL, or a unique pointer value that can later be successfully
 * passed to free().
 *
 * @param nmemb Number of elements to be allocated.
 * @param size Size of bytes for each element.
 *
 * @return (void *) Returns a pointer to the allocated memory that is suitably
 * aligned for any kind of variable. On error, these functions return NULL.
 * NULL may also be returned by a successful call to calloc() with nmemb or
 * size equal to zero.
 */
void		*ft_calloc(size_t nmemb, size_t size);

/* <strings.h> functions: */
void		ft_bzero(void *s, size_t n);	// Deprecated; use memset instead

/* New functions: */
/**
 * @brief The ft_substr() function allocates (with malloc(3)) and returns a
 * substringfrom the string ’s’. The substring begins at index ’start’ and is
 * of maximum size ’len’.
 *
 * @param s The string from which to create the substring.
 * @param start The start index of the substring in the string’s’.
 * @param len The maximum length of the substring.
 * 
 * @return (char *) Returns the substring. NULL if the allocation fails.
 */
char		*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief The ft_strjoin() function allocates (with malloc(3)) and returns a
 * new string, which is the result of the concatenation of ’s1’ and ’s2’.
 *
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * 
 * @return (char *) Returns the new string or NULL if the allocation fails.
 */
char		*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief The ft_strtrim() function allocates (with malloc(3)) and returns a
 * copy of ’s1’ with the characters specified in ’set’ removed from the
 * beginning and the end of the string.
 *
 * @param s1 The string to be trimmed.
 * @param set The set of characters to trim.
 * 
 * @return (char *) Returns the trimmed string, or NULL if allocation fails.
 */
char		*ft_strtrim(char const *s1, char const *set);

/**
 * @brief The ft_split() function allocates (with ft_calloc) and returns an
 * array of strings obtained by splitting ’s’ using the character ’c’ as a
 * delimiter. The array must be ended by a NULL pointer.
 *
 * @param s The string to be split.
 * @param c The delimiter character.
 * 
 * @return (char **) Returns a matrix of two splitted arrays, else returns NULL
 * if allocation fails.
 */
char		**ft_split(char const *s, char c);

/**
 * @brief The ft_itoa() function allocates (with malloc(3)) and returns a
 * string representing the integer received as an argument. Negative numbers
 * must be handled.
 *
 * @param n The integer to convert.
 * 
 * @return (char *) Returns the string representing the integer. NULL if the
 * allocation fails.
 */
char		*ft_itoa(int n);

/**
 * @brief The ft_strmapi() function applies the function ’f’ to each character
 * of the string ’s’ to create a new string (with malloc(3)) resulting from
 * successive applications of ’f’.
 *
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * 
 * @return (char *) The string created from the successive applications of ’f’.
 * Returns NULL if the allocation fails.
 */
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief The ft_striteri() function applies the function ’f’ on each character
 * of the string passed as argument, passing its index as first argument. Each
 * character is passed by address to ’f’ to be modified if necessary.
 * 
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 */
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief The ft_putchar_fd() function outputs the character ’c’ to the given
 * filedescriptor.
 *
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 */
void		ft_putchar_fd(char c, int fd);

/**
 * @brief The ft_putstr_fd outputs the string ’s’ to the given filedescriptor.
 *
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void		ft_putstr_fd(char *s, int fd);

/**
 * @brief The ft_putendl_fd() function outputs the string ’s’ to the given
 * filedescriptor, followed by a newline.
 *
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void		ft_putendl_fd(char *s, int fd);

/**
 * @brief The ft_putnbr_fd() function outputs the integer ’n’ to the given
 * filedescriptor.
 *
 * @param n The integer to output.
 * @param fd The file descriptor on which to write.
 */
void		ft_putnbr_fd(int n, int fd);

/*
* Bonus functions:
 */
/**
 * @brief The ft_lstnew() function allocates (with malloc(3)) and returns a
 * new element. The variable ’content’ is initialized with the value of the
 * parameter ’content’. The variable ’next’ is initialized to NULL.
 *
 * @param content The content to create the new element with.
 * 
 * @return (t_list *) The new element.
 */
t_list		*ft_lstnew(void *content);

/**
 * @brief The ft_lstadd_front() function adds the element ’new’ at the
 * beginning of the list.
 *
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the element to be added to the list.
 */
void		ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief The ft_lstsize() function counts the number of elements in a list.
 *
 * @param lst The beginning of a list.
 * 
 * @return (int) Returns the length of a list.
 */
int			ft_lstsize(t_list *lst);

/**
 * @brief The ft_lstlast() returns the last element of the list.
 *
 * @param lst The beginning of the list.
 * 
 * @return (t_list *) Returns the last element of the list. Returns NULL if
 * `lst` is empty or is already in the last element.
 */
t_list		*ft_lstlast(t_list *lst);

/**
 * @brief The ft_lstadd_back() function adds the `new` element at the end of
 * the list.
 * 
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the element to be added to the list.
 */
void		ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief The ft_lstdelone() function takes as a parameter an element and frees
 * the memory of the element’s content using the function ’del’ given as a
 * parameter and free the element. The memory of ’next’ must not be freed.
 *
 * @param lst The element to free.
 * @param del The address of the function used to delete the content.
 */
void		ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief The ft_lstclear() function deletes and frees the given element and
 * every successor of that element, using the function ’del’ and free(3).
 * Finally, the pointer to the list must be set to NULL.
 *
 * @param lst The adress of a pointer to an element.
 * @param del The adress of the function used to delete the content of the
 * element.
 */
void		ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief The ft_lstiter() function iterates the list ’lst’ and applies the
 * function ’f’ to the content of each element.
 *
 * @param lst The adress of a pointer to an element.
 * @param f The adress of the function used to iterate on the list.
 */
void		ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief The ft_lstmap() function iterates the list ’lst’ and applies the
 * function ’f’ to the content of each element. Creates a new list resulting of
 * the successive applications of the function ’f’. The ’del’ function is used
 * to delete the content of an element if needed.
 *
 * @param lst The adress of a pointer to an element.
 * @param f The adress of the function used to iterate on the list.
 * @param del The adress of the function used to delete the content of an
 * element if needed.
 * 
 * @return (t_list *) Returns the new list or NULL if the allocation fails.
 */
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* 
* Adcional functions:
 */
/**
 * @brief The ft_freethis() function simply free a malloc'd pointer and points
 * it to whatever the user wants. i.e. NULL.
 * 
 * @param str The address of the pointer to be free'd.
 * @param content The target to point str to.
 */
void		ft_freethis(char **str, void *content);

/**
 * @brief The ft_putnbr_base_fd() function outputs a number in any base given
 * as a the second argument to a given filedescryptor.
 * 
 * @param nbr The integer to output.
 * @param base The numerical base to be outputed to.
 * @param fd The file descriptor on which to write.
 */
void		ft_putnbr_base_fd(int nbr, char *base, int fd);

/**
 * @brief The ft_atoll() function converts the initial portion of the string
 * pointed to by nptr to long long.
 *
 * @param nptr Points to the area of memory of the beginning of string to be
 * converted.
 *
 * @return (long long) The converted value or 0 on error.
 */
long long	ft_atoll(const char *nptr);
#endif
