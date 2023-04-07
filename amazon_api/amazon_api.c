#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_LEN_RESP 23
#define MAX_LEN_Q 30
#define MAX_LEN_NM 10

struct User {
    char* nm;
    char* pwd;
};

void init(struct User* us) {
    us->nm = (char*) malloc(sizeof(char) * (MAX_LEN_NM + 1));
    us->nm[MAX_LEN_NM] = 0;
    us->pwd = (char*) malloc(sizeof(char) * (MAX_LEN_NM + 1));
    us->pwd[MAX_LEN_NM] = 0;
}

void del(struct User* us) {
    free(us->nm);
    us->nm = NULL;
    free(us->pwd);
    us->pwd = NULL;
}

// 5
// register david david123
// register adam 1Adam1
// login david david123
// login adam 1adam1
// logout david

// Registered Successfully
// Logged In Successfully
// Logged Out Successfully
// 23

void extr_info(int j_st, int i, char** logs, char* dest) {
    int j = j_st;
    while ((j < strlen(logs[i])) && (logs[i][j] != ' ')) {
        dest[j - j_st] = logs[i][j];
        j++;
    }
    dest[j - j_st] = 0;
    // printf("\n%s\n", dest);
    return;
}


bool exists(struct User* rec, int size, char* unm) {
    for (int i = 0; i < size; i++) {
        if (strcmp((const char*) rec[i].nm, (const char*)unm) == 0) {
            return true;
        }
    }
    return false;
}

void dump_rec(struct User* rec, int size) {
    for (int i = 0; i < size; i++) {
        printf("\nname: %s, pwd: %s\n", rec[i].nm, rec[i].pwd);
    }
}

bool check_pwd(struct User* rec, int size, char* nm, char* pwd) {
    for (int i = 0; i < size; i++) {
        if (strcmp(nm, rec[i].nm) == 0) {
            if (strcmp(pwd, rec[i].pwd) == 0) {
                return true;
            }
            else {
                // printf("\nactual: %s, tried: %s\n", rec[i].pwd, pwd);
                return false;}
        }
    }
    return true;
}

char** implementAPI(int logs_count,
    char** logs, int* result_count) {
    char** res = (char**) malloc(sizeof(char*) * logs_count);
    for (int i = 0; i < logs_count; i++) {
        res[i] = (char*) malloc(sizeof(char) * MAX_LEN_RESP);
    }
    char regs[] = "Registered Successfully";
    char regu[] = "Username already exists";
    char logins[] = "Logged In Successfully";
    char loginu[] = "Login Unsuccessful";
    char logouts[] = "Logged Out Successfully";
    char reg[] = "register";
    char login[] = "login";
    char logout[] = "logout";
    struct User* regd = (struct User*) malloc(sizeof(struct User) * logs_count);
    int nregd = 0;
    struct User* logd = (struct User*) malloc(sizeof(struct User) * logs_count);
    int nlogd = 0;
    for (int i = 0; i < logs_count; i++) {  init(&(regd[i]));}
    for (int i = 0; i < logs_count; i++) {  init(&(logd[i]));}
    char unm[MAX_LEN_NM + 1], pwd[MAX_LEN_NM + 1];
    for (int i = 0; i < logs_count; i++) {
        // strncpy(unm, &(logs[i][]));
        if (strncmp((const char*) logs[i],
            (const char*) reg, (size_t) 8) == 0){
            extr_info(9, i, logs, unm);
            extr_info(10 + strlen(unm), i, logs, pwd);
            if (exists(regd, nregd, unm) == true) {
                strcpy((char*) res[i], (const char*) regu);
            }
            else {
                strcpy((char*) res[i], (const char*) regs);
                strcpy(regd[nregd].nm, unm);
                strcpy(regd[nregd].pwd, pwd);
                nregd++;
            }
        }
        else if (strncmp(logs[i], login, 5) == 0){
            extr_info(6, i, logs, unm);
            extr_info(7 + strlen(unm), i, logs, pwd);
            if ((exists(regd, nregd, unm) == false) ||
                (exists(logd, nlogd, unm) == true) ||
                (check_pwd(regd, nregd, unm, pwd) == false)) {
                printf("\nres[i]: %p\n", res[i]);
                strcpy((char*) res[i], (const char*) loginu);
                printf("\nhey\n");
            }
            else {
                strcpy((char*) res[i], (const char*) logins);
                strcpy(logd[nlogd].nm, unm);
                nlogd++;
            }
        }
        else if (strncmp(logs[i], logout, 6) == 0){
            extr_info(7, i, logs, unm);
        }
    }
    printf("\nhey1\n");
    for (int i = 0; i < nregd; i++) { del(&(regd[i])); }
    free(regd); regd = NULL;
    for (int i = 0; i < nlogd; i++) { del(&(logd[i])); }
    free(logd); logd = NULL;
    printf("\nhey2\n");
    return res;
}

int main() {
    int logs_count;
    scanf("%d", &logs_count);
    // printf("\n%d\n", logs_count);
    char** logs = (char**) malloc(sizeof(char*) * logs_count);
    for (int i = 0; i < logs_count; i++) {
        logs[i] = (char*) malloc(sizeof(char) * MAX_LEN_Q);
    }
    fgets(logs[0], MAX_LEN_Q, stdin);
    for (int i = 0; i < logs_count; i++) {
        // printf("\nhey%d\n", i);
        if (fgets(logs[i], MAX_LEN_Q, stdin) == NULL)
            { printf("\nfgets error\n");}
        // else {
        //     logs[i][strlen(logs[i]) - 1] = 0;
        //     printf("\"%s\"\n", logs[i]);
        //     }
    }
    // for (int i = 0; i < logs_count; i++) {
    //     printf("\n%s\n", logs[i]);
    // }
    char** result = NULL;
    result = implementAPI(logs_count, logs, 0);
    printf("\nhey3\n");
    for (int i = 0; i < logs_count; i++) {
        printf("\n%s\n", result[i]);
    }
    for (int i = 0; i < logs_count; i++) {
        free(logs[i]);
        logs[i] = NULL;
    }
    for (int i = 0; i < logs_count; i++) {
        free(result[i]);
        result[i] = NULL;
    }
    free(result);
    result = NULL;
    free(logs);
    logs = NULL;
    return 0;
}
