#include <stdio.h>
#include <stdlib.h>

struct date {
    int year;
    int month;
    int day;
} d1, d2;
 
int main() {
    FILE *fp = fopen("D:\\C\\exe\\test.in", "r");
    if ( fp ) {
        int num;
        fscanf(fp, "%d", &num);
        printf("读出来的数字是: %d", num);
        fclose(fp);
    } else {
        printf("文件不存在");
    }
    return 0;
}


int maxMin(int arr[], int len, int *max, int *min) {
    *max = arr[0];
    *min = arr[0];
    for (int i = 0; i <= len; i++) {
        if (arr[i] > *max) {
            *max = arr[i];
        }
        if (arr[i] < *min) {
            *min = arr[i];
        }
    }
    return 0;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}