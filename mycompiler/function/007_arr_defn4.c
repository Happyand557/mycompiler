int main(){
    int a[4][2];
    int b[4][2];
    int c[4][2];
    int d[4][2];
    int e[4][2][1];

    a[3][0] = 7;
    d[3][0] = a[3][0];
    d[2][1] = 1;
    e[0][0][0] = d[2][1];
    e[0][1][0] = 0;
    e[3][1][0] = 5;

    return e[3][1][0] + e[0][0][0] + e[0][1][0] + d[3][0];
}
