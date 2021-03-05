#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lfg(int mod){
    int f[100], op, j, k, out;
    f[0] = 1;
    f[1] = 1;
    srandom(time(0));
    op = random() % 4;
    j = random() % 100;
    k = random() % 100;
    for(int i = 2; i < 100; i++){
        f[i] = f[i - 1] + f[i - 2];
    }
    switch(op){
        case 0:
            out = f[99 - j] + f[99 -k];
            break;
        case 1:
            out = f[99 - j] - f[99 -k];
            break;
        case 2:
            out = f[99 - j] * f[99 -k];
            break;
        case 3:
            out = f[99 - j]^f[99 -k];
            break;
    }
    return out % mod;
}