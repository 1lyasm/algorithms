#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_BRIGHT_GREEN   "\x1b[92m"
#define ANSI_COLOR_CYAN           "\x1b[36m"
#define ANSI_COLOR_RESET          "\x1b[0m"
#define COLOR_BOLD                "\33[1m"
#define CURSOR_OFF                "\33[?25l"
#define CURSOR_ON                 "\33[?25h"

#define MSG1 "OGRENCI ISLEMLERI: \n\
    Ogrenci Ekle, Sil, Guncelle \n\
    Ogrenci Bilgisi Goruntuleme \n\
    Kitap Teslim Etmemis Ogrencileri Listele \n\
    Cezali Ogrencileri Listele \n\
    Tum Ogrencileri Listele \n\
    Kitap Odunc Al/Teslim Et \n"
#define MSG2 "\nKITAP ISLEMLERI: \n\
    Kitap Ekle, Sil, Guncelle \n\
    Kitap Bilgisi Goruntuleme \n\
    Raftaki Kitaplari Listele \n\
    Zamaninda Teslim Edilmeyen Kitaplari Listele \n\
    Kitap-Yazar Eslestir \n\
    Kitabin Yazarini Guncelle \n"
#define MSG3 "\nYAZAR ISLEMLERI: \n\
    Yazar Ekle, Sil, Guncelle \n\
    Yazar Bilgisi Goruntuleme \n\n"

static void printMsg(char *msg, int selIdx, int *choiceCnts) {
    char *cur = strchr(msg, '\n') + 1;
    int i = 0, j = 0, catNamePos = choiceCnts[j];
    int tickPos;
    do {
        for (; i < catNamePos && i < selIdx; ++i) {
            cur = strchr(cur, '\n') + 1;
        }
        if (i == catNamePos) {
            cur = strchr(cur + 1, '\n') + 1;
            catNamePos += choiceCnts[++j];
        }
    } while (i != selIdx);
    tickPos = (int)(cur - msg);
    for (i = 0; i < tickPos; ++i)
        printf("%c", msg[i]);
    printf(ANSI_COLOR_CYAN ">");
    for (i += 1; msg[i] != '\n'; ++i)
        printf("%c", msg[i]);
    printf(ANSI_COLOR_RESET "\n%s", msg + i + 1);
}

static int countChar(char *begin, char *end, int ch) {
    char *cur;
    int cnt = 0;
    for (cur = begin; (end && cur <= end) || (!end && *cur); ++cur)
        if (*cur == ch)
            ++cnt;
    return cnt;
}

static void fail(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

static void fillChoiceCnts(int *cnts, char *str) {
    int i = 0;
    char *begin = strchr(str, ':') + 1, *end = str;
    if (!begin) {
        fail("Invalid message");
    }
    while(end) {
        end = strchr(begin, ':');
        if (end) {
            cnts[i++] = countChar(begin - 1, end, '\n') - 2;
            begin = end + 1;
        }
    }
    cnts[i] = countChar(begin - 1, 0, '\n') - 2;
}

static void getInp() {
    unsigned long catCnt = 3, i;
    char *msg = malloc(1024 * sizeof(char));
    int selIdx = 0, choiceCnt = 0;
    int *choiceCnts = malloc(catCnt * sizeof(int));
    char inp = 0;
    sprintf(msg, "%s%s%s", MSG1, MSG2, MSG3);
    fillChoiceCnts(choiceCnts, msg);
    for (i = 0; i < catCnt; ++i)
        choiceCnt += choiceCnts[i];
    printf(ANSI_COLOR_BRIGHT_GREEN "?"
        ANSI_COLOR_RESET COLOR_BOLD " Ne yapmak istersiniz?"
        ANSI_COLOR_RESET ANSI_COLOR_CYAN " ['w', 's' kullanarak hareket edin]\n"
        ANSI_COLOR_RESET);
    // printf(CURSOR_OFF);
    while (inp != '\n') {
        printMsg(msg, selIdx, choiceCnts);
        do {
            scanf(" %c", &inp);
        } while (inp != 'w' && inp != 's' && inp != '\n');
        if (inp == 'w') 
            --selIdx;
        else if (inp == 's')
            ++selIdx;
        selIdx %= choiceCnt;
    }
    // printf(CURSOR_ON);
    free(choiceCnts);
    free(msg);
}

int main() {
    getInp();
}
