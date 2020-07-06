/**@brief ��ϰʹ��linux�ں��������ܰ�����
 * ��������ṹ��������������ڵ㡢ɾ���ڵ㡢�ƶ��ڵ㡢�����ڵ�
 *
 *@auther Anker @date 2013-12-15
 **/
#include <stdio.h>
#include <stdlib.h>
#include "Mylist.h"
#include "./USART/USART.h"
typedef unsigned int uint32_t;

//����app_info����ṹ
typedef struct application_info
{
    uint32_t  app_id;
    uint32_t  up_flow;
    uint32_t  down_flow;
    struct    list_head app_info_node;//����ڵ�
}app_info;


app_info* get_app_info(uint32_t app_id, uint32_t up_flow, uint32_t down_flow)
{
    app_info *app = (app_info*)malloc(sizeof(app_info));
    if (app == NULL)
    {
        printf("Failed to malloc memory");
        return NULL;
    }
    app->app_id = app_id;
    app->up_flow = up_flow;
    app->down_flow = down_flow;
    return app;
}

static void for_each_app(const struct list_head *head)
{
    struct list_head *pos;
    app_info *app;
    //��������
    list_for_each(pos, head)
    {
        app = list_entry(pos, app_info, app_info_node);
        printf("ap_id: %u\tup_flow: %u\tdown_flow: %u\n",
            app->app_id, app->up_flow, app->down_flow);

    }
}

void destroy_app_list(struct list_head *head)
{
    struct list_head *pos = head->next;
    struct list_head *tmp = NULL;
    while (pos != head)
    {
        tmp = pos->next;
        list_del(pos);
        pos = tmp;
    }
}


int main()
{
    //����һ��app_info
    app_info * app_info_list = (app_info*)malloc(sizeof(app_info));
    app_info *app;
    struct list_head *head;
    
	USART_GPIO_Config();
	USART_Config();
	
    if (app_info_list == NULL)
    {
        printf("Failed to malloc memory\r\n");
        return -1;
    }
    //��ʼ������ͷ��
    head = &app_info_list->app_info_node;
    init_list_head(head);
    
    //��������app_info
    app = get_app_info(1001, 100, 200);
    list_add_tail(&app->app_info_node, head);
    app = get_app_info(1002, 80, 100);
    list_add_tail(&app->app_info_node, head);
    app = get_app_info(1003, 90, 120);
    list_add_tail(&app->app_info_node, head);
    printf("After insert three app_info: \n");
    for_each_app(head);
    
    //����һ���ڵ��Ƶ�ĩβ
    printf("Move first node to tail:\n");
    list_move_tail(head->next, head);
    for_each_app(head);
    
    //ɾ�����һ���ڵ�
    printf("Delete the last node:\n");
    list_del(head->prev);
    for_each_app(head);
    destroy_app_list(head);
    free(app_info_list);
    
    return 0;
}

