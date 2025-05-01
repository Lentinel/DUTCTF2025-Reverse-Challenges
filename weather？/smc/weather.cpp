#include <stdio.h>
#include <string.h>
#include <windows.h>

const char* custom_b64_table = "ZYXABCDEFGHIJKLMNOPQRSTUVWzyxabcdefghijklmnopqrstuvw0123456789+/";
const char* expected_hex = "5E52425D593C5E534D2244746775707067505A724C5324774140747265405A725C43247D4653522072594545";

// 编码用的工具函数
void fun_000003(const char* flag, char* hex_result) {
    unsigned char encoded_base64[128] = { 0 };
    int len = strlen(flag);
    int j = 0;

    for (int i = 0; i < len; i += 3) {
        int c1 = flag[i];
        int c2 = (i + 1 < len) ? flag[i + 1] : 0;
        int c3 = (i + 2 < len) ? flag[i + 2] : 0;

        encoded_base64[j++] = custom_b64_table[(c1 >> 2) & 0x3F];
        encoded_base64[j++] = custom_b64_table[((c1 << 4) | (c2 >> 4)) & 0x3F];
        encoded_base64[j++] = custom_b64_table[((c2 << 2) | (c3 >> 6)) & 0x3F];
        encoded_base64[j++] = custom_b64_table[c3 & 0x3F];
    }

    encoded_base64[j] = '\0';

    for (int i = 0; i < j; i++) {
        encoded_base64[i] = encoded_base64[i] - 3;
        encoded_base64[i] ^= 0x12;
    }

    for (int i = 0; i < j; i++) {
        sprintf_s(&hex_result[i * 2], 3, "%02X", encoded_base64[i]);
    }
    hex_result[j * 2] = '\0';
}

//====================== .function 段验证逻辑 ======================
#pragma comment(linker, "/SECTION:.func,ERW")
#pragma code_seg(push, ".func")
__declspec(code_seg(".func"))
void __stdcall fun_logic(const char* input) {
    char hex_result[256];

    // 将提示字符串手动拼接，防止出现在 .rdata
    char msg1[] = { 'Y','o','u',' ','a','r','e',' ','r','i','g','h','t',',',' ','a','n','d',' ',
                    'w','h','a','t','\'','s',' ','t','h','e',' ','f','l','a','g',' ','o','n',' ',
                    'e','a','r','t','h',' ','n','o','w','?','\n','\0' };

    char msg2[] = { 'C','o','n','g','r','a','t','s','!',' ','C','o','r','r','e','c','t','.','\n','\0' };

    char msg3[] = { 'W','r','o','n','g','.','\n','\0' };

    // 真实 flag 手动构造，防止放入 .rdata
    char debug_news[] = {
        'D','U','T','C','T','F','{',
        's','u','n','n','y','_',
        'a','n','d','_',
        's','e','c','r','e','t',
        '}','\0'
    };

    fun_000003(input, hex_result);

    if (strcmp(hex_result, expected_hex) == 0) {
        printf("%s", msg1);
        return;
    }

    if (strcmp(input, debug_news) == 0) {
        printf("%s", msg2);
    }
    else {
        printf("%s", msg3);
    }
}
#pragma code_seg(pop)

//====================== SMC 解密代码 ======================
void fun_000005(char* source, int len, char key) {
    for (int i = 0; i < len; i++) {
        source[i] ^= key;
    }
}

void fun_000006(char* base, const char* secname) {
    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)base;
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)(base + dos->e_lfanew);
    PIMAGE_SECTION_HEADER sec = IMAGE_FIRST_SECTION(nt);

    for (int i = 0; i < nt->FileHeader.NumberOfSections; i++, sec++) {
        if (strncmp((char*)sec->Name, secname, IMAGE_SIZEOF_SHORT_NAME) == 0) {
            DWORD size = sec->SizeOfRawData;
            char* addr = base + sec->VirtualAddress;
            fun_000005(addr, size, 0x3);  // 解密
            break;
        }
    }
}

void fun_000007() {
    char* base = (char*)GetModuleHandle(NULL);

    // 段名 .func 拆开来动态拼接
    char secname[8];
    secname[0] = '.';
    secname[1] = 'f';
    secname[2] = 'u';
    secname[3] = 'n';
    secname[4] = 'c';
    secname[5] = '\0';

    fun_000006(base, secname);  // 传入拼接后的段名
}


//====================== 主程序入口 ======================
int main() {
    // 解密 .function 段
    fun_000007();

    // 调用假flag验证函数
    char hex_result[256];
    char input[256];
    printf("What's the weather today?\n> ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    fun_000003(input, hex_result);

    // 调用验证函数
    fun_logic(input);

    system("pause");
    return 0;
}

