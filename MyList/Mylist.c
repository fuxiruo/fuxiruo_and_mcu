#include "Mylist.h"
#include "stdio.h"

#define LIST_POISON1  ((void *) 0) 
#define LIST_POISON2  ((void *) 0)

#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

void init_list_head(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __list_add(struct list_head *newlist,
			      struct list_head *prevlist,
			      struct list_head *nextllist)
{
	nextllist->prev = newlist;
	newlist->next = nextllist;
	newlist->prev = prevlist;
	prevlist->next = newlist;
}

/**
 * list_add - add a new entry,从头部增加
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}


/**
 * list_add_tail - add a new entry,从尾部增加
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}


/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

//移到头部
void list_move(struct list_head *list, struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add(list, head);
}

//移到尾部
void list_move_tail(struct list_head *list,
                      struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}

