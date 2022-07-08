#include <stdio.h> 
#include "stdlib.h"
#include <string.h>
#include "lib\sqlite3.h"
#include <time.h>

/**
 * 每1分钟扫描一次
 * 如果存在进程
 *   如果存在记录
 *        查看记录时间
 *    如果时间不是今天，删除记录，新增记录
 *    如果时间是今天
 *       查看持续时间是否超时
 *           超时则删除进程
 *           否则持续时间加一分钟
 **/

typedef struct program_duration {
    int *id;
    int *start_time;
    int *duration;
};

int exec_CallBack(void *para, int f_num, char **f_val, char **f_nume) {
    for (int i = 0; i < f_num; i++)
    {
        printf("%-8s:  %-8s", f_nume[i], f_val[i]);
    }
    printf("\n");
    return 0;
}

void Sel(sqlite3 *db, const char *sql) {
    char *errmsg;
    // int nRes = sqlite3_exec(db, sql, exec_CallBack, NULL, &errmsg);
    if (sqlite3_exec(db, sql, &exec_CallBack, NULL, &errmsg) != 0)  {
        printf("error: %s\n", sqlite3_errmsg(db));
    }
    printf("\n");
    return;
}


int main() {
    sqlite3 *db;
    int r = sqlite3_open("program_duration_contol.db", &db);
    char *sql;
    sql = "select * from test";
    Sel(db, sql);
}