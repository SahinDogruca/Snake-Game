#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int m, n, f, rx, ry, c, i, j, status, input_c, wait=1, nx, ny, el = -5, count =0;
    char input;

    int inputs[8] = {'u','U','r','r','L','l','D','d'};

    do {
        printf("Oyun alanının satır ve sütun sayısını giriniz : ");
        scanf("%d %d", &m, &n);
    } while((m == 1 && n == 1) || m < 1 || n < 1);

    int board[m][n];

    do {
        printf("Oyun alanında yer alacak yemek sayısını giriniz (min:1,max:%d) : ", m*n-1);
        scanf("%d", &f);
    } while(f < 1 || f > m*n-1);

    
    int f_locs[f+1][2];  
    int snake[m*n][2];

    for (i = 0; i <= f; i++) {
        do {
            rx = rand() % m;
            ry = rand() % n;
            c = 0;
            for (j = 0; j <= f && c == 0; j++)
                if (rx == f_locs[j][0] && ry == f_locs[j][1]) c = 1;
            f_locs[i][0] = rx;
            f_locs[i][1] = ry;
        } while (c == 1);
    }

    snake[c][0] = f_locs[0][0], snake[c][1] = f_locs[0][1];

    for(i = 0; i < m; i++) for(j = 0; j < n; j++) board[i][j] = -1;
    for(i = 0; i < f+1; i++){
        board[f_locs[i][0]][f_locs[i][1]] = 0;
        if(!i) board[f_locs[i][0]][f_locs[i][1]] = 1;
    }

    while(status == 0){
        for(i = -1; i <= m; i++){
            for(j = -1; j <= n; j++) {
                if(i == -1 || i == m) printf("   ");
                if(i < m && i >= 0 && j < n && j >= 0){
                    if(j == 0) printf(" ");
                    if(board[i][j] == -1) printf("   ");
                    else printf("%-3d", board[i][j]);
                    if(j != n-1) printf("|");
                }
            }
            printf("\n");
        }

        do{
            input_c = 0, i = 0;
            printf("yön belirtiniz : ");
            scanf(" %c", &input);

            while(i < 8 && input_c == 0){
                if(input == inputs[i]) input_c++;
                i++;
            } 
        } while(input_c == 0);

        rx=0, ry=0;
        if(input == 'u' || input == 'U') rx = -1;
        else if(input == 'l' || input == 'L') ry = -1;
        else if(input == 'D' || input == 'd') rx = 1;
        else if(input == 'r' || input == 'R') ry = 1;

        nx = snake[c][0] + rx;
        ny = snake[c][1] + ry;

        if(nx < 0 || nx >= m || ny < 0 || ny >= n) status = 1;
        else el = board[nx][ny];

        if(wait == 0) c++;
        else{
            board[snake[0][0]][snake[0][1]] = -1;
            for(i = 0; i < c; i++){
                snake[i][0] = snake[i+1][0];
                snake[i][1] = snake[i+1][1];
            }
        }

        snake[c][0] = nx, snake[c][1] = ny;
        board[snake[c][0]][snake[c][1]] = 0;

        for(i = 0; i <= c; i++)  board[snake[i][0]][snake[i][1]]++;
        
        if(el == 0) wait = 0, f--;
        else wait = 1;

        if(f == 0) status = 2;
        else if(el > 0 || el < -1) status = 1;
        count++;
    }

    if(status == 2) printf("kazandın, hamle sayınız : %d", count);
    else if(status == 1) printf("kaybettiniz, hamle sayısı : %d, yılanın büyüklüğü : %d, kalan yemek sayısı : %d", count, board[snake[0][0]][snake[0][1]]-1, f);
}
