#define MAX 1000000
int a[256], b[256], c[256];
int main () {
    int i,j,k =0;
    for (j=0;j<MAX;j++){
        for (j=0;j<MAX;j++){
            for (i=0; i<256; i++){
                a[i] = b[i] + c[i];
        }
    }
    return 0;
    }
}

