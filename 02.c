#include<stdio.h>
#include<math.h>

int main(){
    int n;

    scanf("%d", &n);

    float p[n],q[n], d, aux;

    for(int i = 0; i < n; i++){
            scanf("%f", &p[i]);
    }

    for(int i = 0; i < n; i++){
            scanf("%f", &q[i]);
    }


    for (int i = 0; i < n; i++){
       aux += pow(q[i]-p[i],2);
    }

    d = sqrt(aux);

    printf("A distancia Euclideana entre os pontos eh: %.2f\n", d);

    return 0;

}
