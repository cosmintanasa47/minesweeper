#include<stdlib.h>
#include<stdio.h>



void citire(int* lung, int* lat, int* bomba){
    printf("Ce dimensiuni sa aiba tabla? (linii si coloane): ");
    scanf("%d %d",lung, lat);
    printf("\nSi cate bombe? ");
    scanf("%d",bomba);
}

void alocare(int*** matrice, char*** interfata, int lung, int lat){
    *matrice = (int**)malloc(lung * sizeof(int*));
    for(int i = 0; i < lung; i++) (*matrice)[i] = (int*)malloc(lat * sizeof(int));
    *interfata = (char**)malloc(lung * sizeof(char*));
    for(int i = 0; i < lung; i++) (*interfata)[i] = (char*)malloc(lat * sizeof(char));
}

int scriere(int** matrice,char** interfata, int lung, int lat){
    int alive = 1;
    printf("\nBomba are codul %c\n",'b');
    for(int i = 0; i < lung; i++){
        for(int j = 0; j < lat; j++){
            printf("%c ", interfata[i][j]);
            if(interfata[i][j] == 'b') alive = 0;
        }
        printf("\n");
    }
    return alive;
   // printf("Coordonate: ");
  //  scanf("%d %d", &lung, &lat);
}

void actiune(int** matrice, char** interfata, int lung, int lat, int bomba){
    for(int i = 0; i < lung; i++)
        for(int j = 0; j < lat; j++){ matrice[i][j] = 0; interfata[i][j] = '#';}
    
    // random
    for(int i = 0; i < bomba; i++){
        int a = 1;
        while(a){
            int x = rand() % lung;
            int y = rand() % lat;
            if(matrice[x][y] != 99) {matrice[x][y] = 99; a = 0;}
        }
    }
    // numerotare
    for(int i = 0; i < lung; i++)
        for(int j = 0; j < lat; j++){
            if(matrice[i][j] != 99){
                if(i == 0)
                    if(j == 0){
                        if(matrice[i][j+1] == 99) matrice[i][j]++;
                        if(matrice[i+1][j] == 99) matrice[i][j]++;
                        if(matrice[i+1][j+1] == 99) matrice[i][j]++;
                    }
                    else if(j == (lat - 1)){
                        if(matrice[i][j-1] == 99) matrice[i][j]++;
                        if(matrice[i+1][j] == 99) matrice[i][j]++;
                        if(matrice[i+1][j-1] == 99) matrice[i][j]++;
                    }
                    else{
                        if(matrice[i][j-1] == 99) matrice[i][j]++;
                        if(matrice[i+1][j] == 99) matrice[i][j]++;
                        if(matrice[i][j+1] == 99) matrice[i][j]++;
                        if(matrice[i+1][j+1] == 99) matrice[i][j]++;
                        if(matrice[i+1][j-1] == 99) matrice[i][j]++;
                    }

                else if(i == (lung - 1))
                    if(j == 0){
                        if(matrice[i][j+1] == 99) matrice[i][j]++;
                        if(matrice[i-1][j] == 99) matrice[i][j]++;
                        if(matrice[i-1][j+1] == 99) matrice[i][j]++;
                    }
                    else if(j == (lat - 1)){
                        if(matrice[i][j-1] == 99) matrice[i][j]++;
                        if(matrice[i-1][j] == 99) matrice[i][j]++;
                        if(matrice[i-1][j-1] == 99) matrice[i][j]++;
                    }
                    else{
                        if(matrice[i][j-1] == 99) matrice[i][j]++;
                        if(matrice[i-1][j] == 99) matrice[i][j]++;
                        if(matrice[i][j+1] == 99) matrice[i][j]++;
                        if(matrice[i-1][j+1] == 99) matrice[i][j]++;
                        if(matrice[i-1][j-1] == 99) matrice[i][j]++;
                    }

                else if(j == 0 && i != 0 && i != (lung - 1)){
                    if(matrice[i+1][j+1] == 99) matrice[i][j]++;
                    if(matrice[i-1][j] == 99) matrice[i][j]++;
                    if(matrice[i][j+1] == 99) matrice[i][j]++;
                    if(matrice[i-1][j+1] == 99) matrice[i][j]++;
                    if(matrice[i+1][j] == 99) matrice[i][j]++;
                }
                else if(j == (lat - 1) && i != 0 && i != (lung - 1)){
                    if(matrice[i][j-1] == 99) matrice[i][j]++;
                    if(matrice[i-1][j] == 99) matrice[i][j]++;
                    if(matrice[i+1][j-1] == 99) matrice[i][j]++;
                    if(matrice[i+1][j] == 99) matrice[i][j]++;
                    if(matrice[i-1][j-1] == 99) matrice[i][j]++;
                }
                else{
                    if(matrice[i][j-1] == 99) matrice[i][j]++;
                    if(matrice[i-1][j] == 99) matrice[i][j]++;
                    if(matrice[i+1][j-1] == 99) matrice[i][j]++;
                    if(matrice[i+1][j] == 99) matrice[i][j]++;
                    if(matrice[i-1][j-1] == 99) matrice[i][j]++;
                    if(matrice[i+1][j+1] == 99) matrice[i][j]++;
                    if(matrice[i][j+1] == 99) matrice[i][j]++;
                    if(matrice[i-1][j+1] == 99) matrice[i][j]++;
                }

            }
        }
    int stillAlive = 1;
    while(stillAlive){
        stillAlive = scriere(matrice, interfata, lung, lat);
        if(stillAlive == 0) {printf("Ai pierdut!\n"); break;}
        printf("Coordonate (linie si coloana 0 -> n-1) : ");
        int x, y;
        scanf("%d %d", &x, &y);
        if(matrice[x][y] == 99) interfata[x][y] = 'b';
        else if(matrice[x][y] == 0){
            interfata[x][y] = ' ';
            if(x == 0)
                if(y == 0){
                    interfata[x][y+1] = matrice[x][y+1] + '0';
                    interfata[x+1][y] = matrice[x+1][y] + '0';
                    interfata[x+1][y+1] = matrice[x+1][y+1] + '0';
                }
                else if(y == (lat - 1)){
                    interfata[x][y-1] = matrice[x][y-1] + '0';
                    interfata[x+1][y] = matrice[x+1][y] + '0';
                    interfata[x+1][y-1] = matrice[x+1][y-1] + '0';
                }
                else{
                    interfata[x][y-1] = matrice[x][y-1] + '0';
                    interfata[x+1][y] = matrice[x+1][y] + '0';
                    interfata[x][y+1] = matrice[x][y+1] + '0';
                    interfata[x+1][y+1] = matrice[x+1][y+1] + '0';
                    interfata[x+1][y-1] = matrice[x+1][y-1] + '0';
                }
                else if(x == (lung - 1))
                    if(y == 0){
                        interfata[x][y+1] = matrice[x][y+1] + '0';
                        interfata[x-1][y] = matrice[x-1][y] + '0';
                        interfata[x-1][y+1] = matrice[x-1][y+1] + '0';
                    }
                    else if(y == (lat - 1)){
                        interfata[x][y-1] = matrice[x][y-1] + '0';
                        interfata[x-1][y] = matrice[x-1][y] + '0';
                        interfata[x-1][y-1] = matrice[x-1][y-1] + '0';
                    }
                    else{
                        interfata[x][y-1] = matrice[x][y-1] + '0';
                        interfata[x-1][y] = matrice[x-1][y] + '0';
                        interfata[x][y+1] = matrice[x][y+1] + '0';
                        interfata[x-1][y+1] = matrice[x-1][y+1] + '0';
                        interfata[x-1][y-1] = matrice[x-1][y-1] + '0';
                    }

                    else if(y == 0 && x != 0 && x != (lung - 1)){
                        interfata[x+1][y+1] = matrice[x+1][y+1] + '0';
                        interfata[x-1][y] = matrice[x-1][y] + '0';
                        interfata[x][y+1] = matrice[x][y+1] + '0';
                        interfata[x-1][y+1] = matrice[x-1][y+1] + '0';
                        interfata[x+1][y] = matrice[x+1][y] + '0';
                    }
                    else if(y == (lat - 1) && x != 0 && x != (lung - 1)){
                        interfata[x][y-1] = matrice[x][y-1] + '0';
                        interfata[x-1][y] = matrice[x-1][y] + '0';
                        interfata[x+1][y-1] = matrice[x+1][y-1] + '0';
                        interfata[x+1][y] = matrice[x+1][y] + '0';
                        interfata[x-1][y-1] = matrice[x-1][y-1] + '0';
                    }
                    else{
                        interfata[x][y-1] = matrice[x][y-1] + '0';
                        interfata[x-1][y] = matrice[x-1][y] + '0';
                        interfata[x+1][y-1] = matrice[x+1][y-1] + '0';
                        interfata[x+1][y] = matrice[x+1][y] + '0';
                        interfata[x-1][y-1] = matrice[x-1][y-1] + '0';
                        interfata[x+1][y+1] = matrice[x+1][y+1] + '0';
                        interfata[x][y+1] = matrice[x][y+1] + '0';
                        interfata[x-1][y+1] = matrice[x-1][y+1] + '0';
                    }
        }
        else interfata[x][y] = matrice[x][y] + '0';
        for(int i = 0; i < lung; i++)
            for(int j = 0; j < lat; j++)
                if(matrice[i][j] == 0) interfata[i][j] = ' ';
    }
}

int main(){
    int** matrice;
    char** interfata;
    int lung;
    int lat;
    int bomba;
    citire(&lung,&lat,&bomba);
    alocare(&matrice,&interfata, lung, lat);
    actiune(matrice,interfata,lung,lat,bomba);
    free(matrice);
    free(interfata);
    return 0;
}