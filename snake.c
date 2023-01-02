#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int m, n, f, rx, ry, c, i, j, status, c_inp, wait=1, nx, ny, el = -5, move =0;
    char input;
    char inp_prv[2];
    int inputs[8] = {'u','U','r','R','L','l','D','d'};

    do {
        printf("Oyun alanının satır ve sütun sayısını giriniz : ");
        scanf("%d %d", &m, &n);
    } while((m == 1 && n == 1) || m < 1 || n < 1);

    do {
        printf("Oyun alanında yer alacak yemek sayısını giriniz (min:1,max:%d) : ", m*n-1);
        scanf("%d", &f);
    } while(f < 1 || f > m*n-1);

    int f_locs[f+1][2], s[m*n][2], board[m][n];  

    while(i <= f){
        rx = rand() % m, ry = rand() % n;
        c = 0, j = 0;
        while(j <= f && c == 0){
            if (rx == f_locs[j][0] && ry == f_locs[j][1]) c = 1;
            j++;
        }
        f_locs[i][0] = rx, f_locs[i][1] = ry;
        if(c == 0) i++;
    }
    s[c][0] = f_locs[0][0], s[c][1] = f_locs[0][1];

    for(i = 0; i < m; i++) for(j = 0; j < n; j++) board[i][j] = -1;
    for(i = 0; i < f+1; i++){
        board[f_locs[i][0]][f_locs[i][1]] = 0;
        if(!i) board[f_locs[i][0]][f_locs[i][1]] = 1;
    }

    while(status == 0){
        for(i = 0; i < n*4 + 1; i++) printf("#");
        printf("\n");
        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++) {
                    if(j == 0) printf("#");
                    if(board[i][j] == -1) printf("   ");
                    else printf("%-3d", board[i][j]);
                    if(j != n-1) printf("|");
                    if(j == n-1) printf("#  ");
            }
            printf("\n");
        }
        for(i = 0; i < n*4 + 1; i++) printf("#");
        printf("\n");

        do{
            c_inp = 0, i = 0;
            printf("yön belirtiniz : ");
            scanf(" %c", &input);
            while(i < 8 && c_inp == 0) if(input == inputs[i++]) c_inp++;

            if (c_inp == 0) printf("yanlış karakter girdin \n");
            else if(c && (inp_prv[0] == input || inp_prv[1] == input)) {
                printf("ters yönde gidemezsin \n");
                c_inp = 0;
            }
        } while(c_inp == 0);

        rx=0, ry=0;
        if(input == 'u' || input == 'U') rx = -1;
        else if(input == 'l' || input == 'L') ry = -1;
        else if(input == 'D' || input == 'd') rx = 1;
        else if(input == 'r' || input == 'R') ry = 1;

        nx = s[c][0] + rx, ny = s[c][1] + ry;
        inp_prv[0] = inputs[8 - i];
        if(inp_prv[0] >= 65 && inp_prv[0] <= 90) inp_prv[1] = inp_prv[0] + 32;
        else inp_prv[1] = inp_prv[0] - 32;

        if(nx < 0 || nx >= m || ny < 0 || ny >= n) status = 1;
        else el = board[nx][ny];

        if(wait == 0) c++;
        else{
            board[s[0][0]][s[0][1]] = -1;
            for(i = 0; i < c; i++) s[i][0] = s[i+1][0], s[i][1] = s[i+1][1];
        }

        s[c][0] = nx, s[c][1] = ny;
        board[s[c][0]][s[c][1]] = 0;
        for(i = 0; i <= c; i++)  board[s[i][0]][s[i][1]]++;

        if(f == 0) status = 2;
        else if(el > 0 || el < -1) status = 1;
        move++;

        if(el == 0) wait = 0, f--;
        else wait = 1;
    }
    if(status == 2) printf("kazandın, hamle sayınız : %d", move);
    else if(status == 1) 
        printf("kaybettiniz, hamle sayısı : %d, yılanın büyüklüğü : %d, kalan yemek sayısı : %d", move, c+1, f);
    return 0;
}