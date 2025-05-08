#include <stdio.h>
#include <math.h>

int MDC(int a, int b){
    if (b == 0) {
        return a;
    }
    return MDC(b, a % b);
}
int euclides_estendido(int a, int b, int *inverso, int *coef) {
    if (b == 0) { //resto igual a zero - acabou
        *inverso = 1;
        *coef = 0;
        return a;
    }

    int coef1_temp, coef2_temp;
    int mdc = euclides_estendido(b, a % b, &coef1_temp, &coef2_temp);

    *inverso = coef2_temp;
    *coef = coef1_temp - (a / b) * coef2_temp;

    return mdc;
}

int multiplcaMOD(int a, int b, int Zn){
    return (a*b)%Zn;
}
// calcular o inverso
int inverso(int divisor, int Zn) {
    int inverso, coef_mod;
    int mdc = euclides_estendido(divisor, Zn, &inverso, &coef_mod);

    if (mdc != 1) {
        printf("N e G não são coprimos, ou seja, G não é invertível em N");
        return -1;
    }

    // Ajusta para resultado
    if(inverso < 0){
        printf("%d nao pertence a Zn %d, entao vamos dar uma volta no relogio.\n", inverso, Zn);
        inverso = inverso + Zn;
    }

    return inverso;
}

int e_primo(int n){
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    int limite = sqrt(n);
    for (int i = 3; i <= limite; i += 2) {
        if (n % i == 0)
            return 0;
    }
    return 1; 
}

// Função para calcular a^b % mod usando exponenciação rápida
int fermat( long a, long b, long p) {
    long result = 1;
    a = a % p;  // Caso a seja maior que p
    while (b > 0) {
        // Se b for ímpar, multiplica a por result
        if (b % 2 == 1) {
            result = (result * a) % p;
        }
        // Calcula a^2 % p
        a = (a * a) % p;
        // Divide b por 2
        b = b / 2;
    }

    return result;
}

int totienteEuler(int n){
    int RelPrimos = 0;
    for(int i = n - 1; i > 0; i--){
        if (MDC(i,n)==1){
            RelPrimos++;
        }
    }
    return RelPrimos;

}
int euler(int a, int b, int n){
    int RelPrimos = 0;
    for(int i = n - 1; i > 0; i--){
        if (MDC(i,n)==1){
            RelPrimos++;
        }
    }


    long result = 1;
    a = a % n;  // Caso a seja maior que p
    while (b > 0) {
        // Se b for ímpar, multiplica a por result
        if (b % 2 == 1) {
            result = (result * a) % n;
        }
        // Calcula a^2 % p
        a = (a * a) % n;
        // Divide b por 2
        b = b / 2;
    }
    return result;
}

int main() {
    // H(/)G mod N
    // int H, G, Zn;
    // printf("insira os valores desejados de H, G, n, no formato 'H G n'\n");
    // scanf("%d %d %d", &H, &G, &Zn);

    int H = 30;
    int G = 29;
    int Zn = 431;
    printf("\nvamos calcular %d(/)%d mod %d:\n", H, G, Zn);

    int inverso1 = inverso(G, Zn);

    printf("Inverso: %d\n", inverso1);
    int a =  multiplcaMOD(H, inverso1, Zn);
    printf("a=%d\n\n\n",a);

    int x, Zn1;
    printf("agora insira o exponte X e o Z no formato 'x z':\n");
    x=8;
    Zn1 = 10;
    // scanf("%d %d", &x, & Zn1);


    printf("Agora vamos calcular %d^%d mod %d\n", a, x, Zn1);
    if(MDC(x, Zn1) == 1){
        printf("X e n1 sao coprimos\n");
    }else{
        printf("X e n1 nao sao coprimos\n");
    }
    int x1;
    if(e_primo(Zn1)){
        printf("N1 e primo\nUsando entao o Pequeno teorema de Format:\n");
        int mod = fermat(a, x,  Zn1);
        printf("O resultado e: %d\n",mod);
        x1 = Zn1 - 1;

    }else{
        printf("N1 nao e primo\nUsando entao o Teorema de Euler:\n");
        int mod;
        mod = euler(a, x,  Zn1);
        printf("O resultado e: %d\n",mod);
        x1 = totienteEuler(Zn1);
        printf("Euler(%d) = %d\n",Zn1, x1); 
    }


    printf("\n\nAgora vamos decompor o x (x = %d):\n", x);

    int q = x/x1;
    int r =  x % x1;
    printf("%d = %d * %d + %d\n", x, x1, q, r);

    
    int mult = euler(a, x1*q, Zn1) * euler(a, r, Zn1);
    printf("\n\n(a^(x1*q)modN * a^rmodN)mod N\n");
    printf("=(%d^(%d*%d)mod%d * %d^%dmod%d)mod%d = %d\n",a,x1,q,Zn1,a,r,Zn1,Zn1, euler(mult, 1, Zn1));
    printf("a^x modN = %d^%d mod%d = %d\nmostrando asim que sao congruentes\n\n\n", a, x, Zn1, euler(a, x, Zn1));




    int x2 =  euler(a, x1, Zn1);
    int f1 = fermat(x2, q, Zn1);
    int f2 = fermat(a, r, Zn1);
    printf("x2 = %d^%d mod %d = %d\n",a, x1, Zn1, x2);
    printf("f1 = %d^%d mod %d = %d\n", x2, q, Zn1, f1);
    printf("f2 = %d^%d mod %d = %d\n", a, r, Zn1, f2);

    printf("(%d^%d mod %d * %d^%d mod %d) mod %d\n", a, x1, Zn1, x2, q, Zn1, Zn1);
    printf("= %d*%d mod %d = %d", f1, f2, Zn1, multiplcaMOD(f1, f2, Zn1));

}
