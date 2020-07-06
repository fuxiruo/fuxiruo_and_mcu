#ifndef _MY_LIST_H
#define _MY_LIST_H

struct list_head 
{	struct list_head *next, *prev;
};

void init_list_head(struct list_head *list);
void list_add(struct list_head *new, struct list_head *head);
void list_add_tail(struct list_head *new, struct list_head *head);
void list_del(struct list_head *entry);
void list_move(struct list_head *list, struct list_head *head);
void list_move_tail(struct list_head *list,struct list_head *head);

//����member��type�е�λ��
#define offsetof(type, member)  (size_t)(&((type*)0)->member)
 
//����member�ĵ�ַ��ȡtype����ʼ��ַ   
#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))  

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#endif
