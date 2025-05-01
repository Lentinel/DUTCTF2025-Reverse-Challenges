#include <stdio.h>
#include <string.h>

int main() {
    char s[64];
    char s2[64] = {0};  // 用于存储构造出的 flag 字符串

    // 动态构造 flag 字符串
    strcat(s2, "DUT");
    strcat(s2, "CTF{");
    strcat(s2, "r3v");
    strcat(s2, "3R53_");
    strcat(s2, "1$_");
    strcat(s2, "\\/");
    strcat(s2, "3ry_");
    strcat(s2, "f(_)");
    strcat(s2, "n&ea");
    strcat(s2, "5y!");
    strcat(s2, "}");

    printf("Input the flag: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = 0;  // 去掉输入中的换行符

    if (strcmp(s, s2) == 0) {
        puts("Correct!");
    } else {
        puts("Wrong!");
    }

    return 0;
}
