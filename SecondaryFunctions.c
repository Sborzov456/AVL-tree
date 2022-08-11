#include "SecondaryFunctions.h"

int getInt(int* value)
{
    int n;
    do {
        n = scanf("%d", value);
        if (n < 0) {
            return 0;
        }
        if (n == 0) {
            printf("%s\n", "Error! Repeat input");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}

int dialog(char *msgs[])
{
    char *errorMessage = "";
    int option;
    do{
        puts(errorMessage);
        errorMessage = "You are wrong. Repeate, please!";
        for(int i = 0; i < OPTIONS_NUM; ++i){
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");
        if (!getInt(&option)) {
            option = 0;
        }
    } while(option < 0 || option >= OPTIONS_NUM);
    return option;
}

char* getString()
{
    int n, len, lenRes = 0;
    char buf[51];
    char *res = NULL;
    do {
        n = scanf("%50[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            len = (int)strlen(buf);
            lenRes += len;
            res = realloc(res, (lenRes + 1) * sizeof(char));
            memcpy(res + lenRes - len, buf, len);
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);
    if (lenRes > 0) {
        res[lenRes] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

int max(int a, int b)
{
    if (a >= b) return a;
    else return b;
}
