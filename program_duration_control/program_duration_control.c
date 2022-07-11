#include <stdio.h> 
#include "stdlib.h"
#include <string.h>
#include "lib\sqlite3.h"
#include <time.h>

/**
 * 每1分钟扫描一次
 * 如果存在进程
 *   如果存在记录
 *       查看记录时间 
 *    如果时间不是今天，删除记录，新增记录
 *    如果时间是今天
 *       查看持续时间是否超时
 *           超时则删除进程
 *           否则持续时间加一分钟
 **/

sqlite3 *db;

struct tm *now;
time_t now_timestamp;

long allow_duration_ordinary = 2*60*60*1000;
long allow_duration_day_off = 5*60*60*1000;

char *to_kill_pids[65525] = {0};
int to_kill_pid_num = 0;

char **program_list = {"chrome", "ToDesk"};

typedef struct Program_duration {
    int id;
    long start_time;
    int duration;
} *PD;

// After confirming program exists
void get_store() {
    char *sql;
    sql = "select * from main";
    // The logic is in the exec_db_CallBack
    sql_exec(sql, &exec_db_CallBack);
}

PD parse_CallBack(int f_num, char **f_val, char **f_nume) {
    PD pd = malloc(sizeof(PD));
    for (int i = 0; i < f_num; i++) {
        if (f_nume[i] == "id") 
            pd->id = f_val[i];
        else if ((f_nume[i] == "start_time"))
            pd->start_time = f_val[i];
        else if ((f_nume[i] == "duration"))
            pd->duration = f_val[i];
    }
    return pd;
}

int exec_db_CallBack(void *para, int f_num, char **f_val, char **f_nume) {
    PD pd = parse_CallBack(f_num, f_val, f_nume);
    if (pd->id == NULL) {
        // 不存在记录，则新增
        insert();
        return 0;
    }
    
    if (is_today(pd->start_time)) {
        duration_handle(pd);
        return;
    }
    // update
    update_for_new_day(pd->id);
    return 0;
}

void update_for_new_day(int id) {
    char sql[100];
    sprintf(sql, "update main set start_time = %d and duration = 0 where id = %d", now_timestamp, id);
    sql_exec(sql, NULL);
}

void add_minute(int id, int duration) {
    char sql[100];
    sprintf(sql, "update main set duration = %d where id = %d", duration, id);
    sql_exec(sql, NULL);
}

void insert() {
    char sql[100];
    sprintf(sql, "insert into main (id, start_time, duration) values (1, %d, 0)", now_timestamp);
    sql_exec(sql, NULL);
}

// 处理超时
void duration_handle(PD pd) {
    long allow_duration = now->tm_wday > 5 ? allow_duration_day_off : allow_duration_ordinary;
    if (pd->duration > allow_duration) {
        // timeout for kill
        kill();
        return;
    }
    // duration add one minute
    add_minute(pd->id, (pd->duration) + 1);
}

int is_today(long t_time) {
    struct tm *t_time_info = localtime(&t_time);

    if (now->tm_year == t_time_info->tm_year && now->tm_mday == t_time_info->tm_mday) {
        return 1;
    }
    return 0;
}

void sql_exec(char *sql, sqlite3_callback Callback) {
    char *errmsg;
    // int nRes = sqlite3_exec(db, sql, exec_db_CallBack, NULL, &errmsg);
    if (sqlite3_exec(db, sql, Callback, NULL, &errmsg) != 0)  {
        printf("error: %s\n", sqlite3_errmsg(db));
    }
    printf("\n");
    return;
}

int exec_command(char *command, char *mode) {
    FILE *fp;

    if ((fp = _popen(command, mode)) == NULL) {
        perror("Fail to Open\n");
        return 1;
    }

    
    return 0;
}

void kill() {
    if (to_kill_pid_num > 0) {
        for (int i = 0; i < to_kill_pid_num; i++) {
            char command_prefix[50] = "taskkill /f /t /im ";
            char *to_kill_command = strcat(command_prefix, to_kill_pids[i]);
            system(to_kill_command);
        }
    }
}

void get_to_kill_pids() {
    FILE *fp;
    //TODO program list
    char *command[65525];
    sprintf();
    if ((fp = _popen("tasklist | find /i \"chrome.exe\"", "r")) == NULL) {
        perror("Fail to Open\n");
        return 1;
    }

    char *buf[65525] = {0};
    empty();
    while (fgets(buf, 65525, fp) != NULL) {
        char *revbuf[100] = {0};
        split(buf," ", to_kill_pids, &to_kill_pid_num);
    }
}

void empty() {
    for (int i = 0; i < 65525; i++) {
        to_kill_pids[i] = 0;
    }
    
}

void split(char *src,const char *separator,char **dest,int *num) {
     char *pNext;
     int count = 0;
     if (src == NULL || strlen(src) == 0)
        return;
     if (separator == NULL || strlen(separator) == 0)
        return;
     pNext = strtok(src,separator);
     while(pNext != NULL) {
          *dest++ = pNext;
          ++count;
         pNext = strtok(NULL,separator);
    }
    *num = count;
}

int main() {
    time(&now_timestamp);
    now = localtime(&now_timestamp);

    if (exec_command("tasklist | find /i \"chrome.exe\"", "r") == 0) {
        int r = sqlite3_open("program_duration_control/program_duration_control.db", &db);
        get_store();
    }
}