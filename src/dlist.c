#include "dlist.h"

dlist *
dlist_last(dlist *l)
{
	if (! l)
		return NULL;

	while(l && l->next)
		l = l->next;
	return l;
}

dlist *
dlist_first(dlist *l)
{
	while(l && l->prev)
		l = l->prev;
	return l;
}

dlist *
dlist_add(dlist *l, void *d)
{
	dlist *new_elem;
	
	l = dlist_last(l);
	new_elem = malloc(sizeof(dlist));
	new_elem->prev = l;
	new_elem->next = 0;
	new_elem->data = d;
	if(l)
		l->next = new_elem;
	return new_elem;
}

dlist *
dlist_cycle_prev(dlist *l)
{
	if (! l)
		return NULL;

	dlist *first_elem = dlist_first(l);
	dlist *last_elem = dlist_last(l);
	dlist *prev = last_elem->prev;

	if (dlist_len(first_elem) == 1)
		return first_elem;

	if (prev)
		prev->next = NULL;

	first_elem->prev = last_elem;
	last_elem->prev = NULL;
	last_elem->next = first_elem;

	first_elem = last_elem;
	return first_elem;
}

dlist *
dlist_cycle_next(dlist *l)
{
	if (! l)
		return NULL;

	dlist *first_elem = dlist_first(l);
	dlist *last_elem = dlist_last(l);
	dlist *next = first_elem->next;

	if (dlist_len(first_elem) == 1)
		return first_elem;

	if (next)
		next->prev = NULL;

	last_elem->next = first_elem;
	first_elem->prev = last_elem;
	first_elem->next = NULL;

	first_elem = next;
	return first_elem;
}

dlist *
dlist_cycle(dlist *l, int n)
{
	if (! l)
		return NULL;

	dlist *first_elem = dlist_first(l);

	if (n < 0)
	{
		while (n != 0)
		{
			first_elem = dlist_cycle_prev(first_elem);
			n++;
		}
	}

	if (n > 0)
	{
		while (n != 0)
		{
			first_elem = dlist_cycle_next(first_elem);
			n--;
		}
	}
	return first_elem;
}

dlist *
dlist_free(dlist *l)
{
	if (! l)
		return NULL;

	l = dlist_first(l);
	
	while(l) {
		dlist *c = l;
		l = l->next;
		free(c);
	}
	
	return NULL;
}

dlist *
dlist_find(dlist *l, dlist_match_func func, void *data)
{
	if (! l)
		return NULL;

	if (! data)
		return NULL;

	for(l = dlist_first(l); l; l = l->next)
		if(func(l, data))
			break;
	return l;
}

dlist *
dlist_free_with_func(dlist *l, dlist_free_func func)
{
	l = dlist_first(l);
	
	while(l) {
		dlist *c = l;
		if(l->data)
			func(l->data);
		l = l->next;
		free(c);
	}
	
	return NULL;
}

unsigned int
dlist_len(dlist *l)
{
	unsigned int n = 0;
	
	l = dlist_first(l);
	while(l) {
		n++;
		l = l->next;
	}
	
	return n;
}

dlist *
dlist_nth(dlist *l, unsigned int n)
{
	unsigned int i = 0;
	l = dlist_first(l);
	while(l && i != n) {
		i++;
		l = l->next;
	}
	
	return l;
}