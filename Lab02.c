#include <stdio.h>
#include <math.h>

int read(){

    int n;

    scanf("%d", &n);

    while(n <= 0){
        printf("digite um numero maior ou igual a 1\n");
        scanf("%d", &n);
    }


    return n;
}

float calc(int n){
    
    float p[n], q[n], aux, d;


    for(int i = 1; i <= n; i++){
        scanf("%f", &p[i]);
    }

    for(int j = 1; j <= n; j++){
        scanf("%f", &q[j]);
    }

    for(int k = 1; k <= n; k++){
        aux += pow(p[k] - q[k], 2);
    }

    d = sqrt(aux);


    return d;
}


int main(){

    float d;

    d = calc(read());
    
    printf("A distancia Euclideana entre os pontos eh: %.2f", d);

    return 0;
}