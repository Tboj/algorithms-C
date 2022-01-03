#include <stdio.h>

struct Node {
    /**/
    int data;
} List;

struct Node* test() {
    //这里malloc要返回一个指针也是 Node*
   struct Node *q = (struct Node*)malloc(sizeof(struct Node));
   q->data = 1;
   return q;
}

void print(struct Node q) {
    printf("data=%d", q.data);
}

int main() {
    print(*test());
}

