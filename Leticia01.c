#include<stdio.h>

int main(){
    int n,a=0,cont=0,acesso=0;

    scanf("%d", &n);

    for(int i = 1; i<=n; i++){
            scanf("%d",&a);
        if(acesso < 1000000){
            acesso+=a;
            cont=i;
        }
    }

    printf("%d", cont);

    return 0;

}
