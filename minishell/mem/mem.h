/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:07:25 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:07:29 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stdlib.h>

typedef struct s_gc_node
{
	struct s_gc_node	*prev;
	struct s_gc_node	*next;
	size_t				size;
}	t_gc_node;

typedef struct s_gb
{
	t_gc_node	*fnode;
	t_gc_node	*lnode;
	size_t		tsize;
	size_t		nb_allocs;
}	t_gcan;

void	gc_init(t_gcan *gcan);
void	*gc_malloc(t_gcan *gcan, size_t size);
void	gc_free(t_gcan *gcan, void **ptr);
void	gc_clean(t_gcan *gcan);

#endif
