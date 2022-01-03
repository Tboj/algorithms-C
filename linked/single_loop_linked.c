#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

struct Node {
    // 数据
    ElemType data;
    // 下一个节点
    struct Node *next;
} List;

// 定义链表
typedef struct Node *LinkedList;

/**
 * 构造有头单循环链表
*/
struct List* create() {
    struct Node *q = (struct Node*)malloc(sizeof(struct Node));
    q->data = NULL;
    q->next = q;
    return q;
}

/**
 * 头插法
*/
void headInsert(struct Node *q, ElemType data) {
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->data = data;
    p->next = q->next;
    q->next = p;
}

/**
 * 尾插法
*/
void tailInsert(LinkedList linkedList, ElemType data) {
    LinkedList q = malloc(sizeof(LinkedList));
    q->data = data;
    q->next = NULL;
    LinkedList p = linkedList;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = q;
}

/**
 * 遍历
 */
void traverse(struct Node *head) {
    struct Node *q = head->next;
    while (q != head) {
        printf("%d,", q->data);
        q = q->next;
    }
}

/**
 * 删除某个元素
*/
void delete(LinkedList linkedList, ElemType data) {
    LinkedList q = linkedList;
    while (q->next != NULL && q->next->data != data) {
        q = q->next;
    }
    if (q != NULL) {
        q->next = q->next->next;
        free(q->next);
    }
}

/**
 * 单链表倒置
*/
void reversal(LinkedList linkedList) {
    LinkedList q = create();
    LinkedList p = linkedList->next;
    while (p != NULL) {
        
    }
}

void main() {
    LinkedList linkedList = create();
    headInsert(linkedList, 1);
    headInsert(linkedList, 2);
    headInsert(linkedList, 3);
    traverse(linkedList);
}