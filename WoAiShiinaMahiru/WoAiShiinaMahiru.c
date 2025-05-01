#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdint.h> 

const uint8_t r1[] = { 
    0x52, 0x46, 0x56, 0x55, 0x51, 0x31, 0x52, 0x47, 0x65, 0x7A, 0x59, 0x34, 
    0x4D, 0x47, 0x52, 0x6A, 0x4E, 0x54, 0x55, 0x78, 0x4C, 0x54, 0x49, 0x31, 
    0x4F, 0x44, 0x51, 0x74, 0x4F, 0x44, 0x41, 0x77, 0x5A, 0x53, 0x31, 0x69, 
    0x4F, 0x47, 0x4A, 0x6D, 0x4C, 0x57, 0x51, 0x7A, 0x59, 0x7A, 0x4D, 0x35, 
    0x4D, 0x7A, 0x52, 0x6B, 0x4F, 0x54, 0x64, 0x6C, 0x4F, 0x48, 0x30, 0x3D 
};

const char r2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void r3(const unsigned char *r4, size_t r5, char *r6) {
    int r7 = 0, r8 = 0;
    unsigned char r9[3], r10[4];
    size_t r11 = 0;
    
    while (r5--) {
        r9[r7++] = *(r4++);
        if (r7 == 3) {
            r10[0] = (r9[0] & 0xfc) >> 2;
            r10[1] = ((r9[0] & 0x03) << 4) | ((r9[1] & 0xf0) >> 4);
            r10[2] = ((r9[1] & 0x0f) << 2) | ((r9[2] & 0xc0) >> 6);
            r10[3] = r9[2] & 0x3f;

            for (r7 = 0; r7 < 4; r7++) {
                r6[r11++] = r2[r10[r7]];
            }
            r7 = 0;
        }
    }

    if (r7) {
        for (r8 = r7; r8 < 3; r8++) {
            r9[r8] = '\0';
        }
        r10[0] = (r9[0] & 0xfc) >> 2;
        r10[1] = ((r9[0] & 0x03) << 4) | ((r9[1] & 0xf0) >> 4);
        r10[2] = ((r9[1] & 0x0f) << 2) | ((r9[2] & 0xc0) >> 6);
        r10[3] = r9[2] & 0x3f;

        for (r8 = 0; r8 < r7 + 1; r8++) {
            r6[r11++] = r2[r10[r8]];
        }
    }

    while (r11 % 4) {
        r6[r11++] = '=';
    }
    r6[r11] = '\0';
}

int main() {
    char r13[256];
    char r14[512];

    printf("Input flag: ");
    fgets(r13, sizeof(r13), stdin);

    r13[strcspn(r13, "\n")] = '\0';

    r3((unsigned char *)r13, strlen(r13), r14);

    if (memcmp(r14, r1, strlen((char *)r1)) == 0) {
        printf("Nice! \n");
    } else {
        printf("Not good. \n");
    }

    return 0;
}
