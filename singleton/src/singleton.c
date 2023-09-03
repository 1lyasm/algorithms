#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
} Db;

typedef struct {
    Db *db;
} SingletonDb;

void err(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

Db *dbAlloc(char *url) {
    Db *db = malloc(sizeof(Db));
    if (!db) err("dbAlloc: malloc failed");
    int urlLen = strlen(url);
    db->url = malloc((urlLen + 1) * sizeof(char));
    if (!db->url) err("dbAlloc: malloc failed");
    db->url[urlLen] = 0;
    memcpy(db->url, url, urlLen * sizeof(char));
    return db;
}

void dbFree(Db *db) {
    free(db->url);
    free(db);
}

void dbPrint(Db *db) { printf("{ \"url\": \"%s\" }\n", db->url); }

SingletonDb *singletonDbAlloc(char *url) {
    SingletonDb *singletonDb = malloc(sizeof(SingletonDb));
    if (!singletonDb) err("singletonDbAlloc: malloc failed");
    singletonDb->db = dbAlloc(url);
    return singletonDb;
}

void singletonDbFree(SingletonDb *singletonDb) {
    dbFree(singletonDb->db);
    free(singletonDb);
}

Db *dbInstance(SingletonDb *singletonDb) { return singletonDb->db; }

int main() {
    SingletonDb *singletonDb = singletonDbAlloc("google.com");
    Db *db1 = dbInstance(singletonDb);
    Db *db2 = dbInstance(singletonDb);
    if (db1 == db2)
        printf("main: db1 == db2\n");
    else
        printf("main: db1 != db2\n");
    singletonDbFree(singletonDb);
    return 0;
}
