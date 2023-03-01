#ifndef VOLNOTI_DLIST_H
#define VOLNOTI_DLIST_H

struct dlist_element {
	void *data;
	struct dlist_element *next;
	struct dlist_element *prev;
};

typedef struct dlist_element dlist;

/* first element in list */
dlist *dlist_first(dlist *);

/* last element in list */
dlist *dlist_last(dlist *);

/* add element to the end of the list, returns new element */
dlist *dlist_add(dlist *, void *);

/* returns the list's new head element, after the elements being cycled around by -1 steps */
dlist *dlist_cycle_prev(dlist *l);

/* returns the list's new head element, after the elements being cycled around by +1 steps */
dlist *dlist_cycle_next(dlist *l);

/* returns the list's new head element, after the elements being cycled around by 'n' steps */
dlist *dlist_cycle(dlist *l, int n);

/* free the list (not the data), returns 0 */
dlist *dlist_free(dlist *);

/* delete a list calling func on each data item */
typedef void (*dlist_free_func)(void *);
dlist *dlist_free_with_func(dlist *, dlist_free_func);

/* return the length of the list */
unsigned int dlist_len(dlist *);

/* find an element (returns element or 0) */
typedef int (*dlist_match_func)(dlist*, void *);
dlist *dlist_find(dlist *, dlist_match_func, void *);

/* return nth element or 0 */
dlist *dlist_nth(dlist *l, unsigned int n);

#endif /* VOLNOTI_DLIST_H */
