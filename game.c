#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25

void draw(int plane[HEIGHT][WIDTH]); //Нарисовать поле (printw для ncurses)
void fill_zero(int plane[HEIGHT][WIDTH]); //заполнить нулями
int read_file(int plane[HEIGHT][WIDTH]); //пользователь вводит число, мы читаем файл и заполняем поле так, как в файле. При ошибке вернуть 1
int read_speed(int * speed); // скорость обновления кадров. При ошибке вернуть 1
void init(); //Все команды для запуска ncurses
void mark_for_death(int plane[HEIGHT][WIDTH]); // Пометить все поля, которые умрут числом 2
void mark_for_resurrection(int plane[HEIGHT][WIDTH]); // Пометить все поля, которые будут жить числом 3
void death(int plane[HEIGHT][WIDTH]); |// заменить 2 на 0 
void resurrection(int plane[HEIGHT][WIDTH]); //заменить 3 на 1
int count_neighbours(int y, int x, int plane[HEIGHT][WIDTH]); //  The board is assumed to be self-contained. Поэтому вычет по модулю 80





void the_game() {
    int plane[HEIGHT][WIDTH];
    fill_zero(plane);
    int speed;
    int flag = 1;
    if (read_file(plane) || read_speed(speed)){
        printf("n/a");
        flag = 0;
    }
    init();
    while (flag)
    {
        draw();
        if (getchar() == ' '){
            flag = 0;
        }
        mark_for_death(plane[HEIGHT][WIDTH]);
        mark_for_resurrection(plane[HEIGHT][WIDTH]);
        death(plane[HEIGHT][WIDTH]);
        resurrection(plane[HEIGHT][WIDTH]);
        napms(speed * 100);
    }
}


int count_neighbours(int y, int x, int plane[HEIGHT][WIDTH]){
    cnt = 0;
    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            if (plane[(HEIGHT + dy + y)%HEIGHT][(WIDTH + dx + x)%WIDTH] % 2 == 1){
                cnt += (dx != 0 || dy != 0) ? 1 : 0;
            }
        }
    }
    return cnt;
}

void mark_for_death(int plane[HEIGHT][WIDTH]){
    int cnt;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cnt = count_neighbours(i, j, plane)
            if ((cnt < 2 || cnt > 3) && (plane[i][j] == 1)) {
                plane[i][j] = 3;
            }
        }
    }
}

void death(int plane[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (plane[i][j] == 3) {
                plane[i][j] = 0;
            }
        }
    }
}

void init() {
    initscr();
    cbreak();               // Отключаем буферизацию строк
    noecho();               // Не отображаем вводимые символы
    keypad(stdscr, TRUE);   // Включаем специальные клавиши
    nodelay(stdscr, TRUE);  // Неблокирующий ввод
    curs_set(0);            // Скрываем курсор
}


void draw(int plane[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (plane[i][j]%2) {
                printw("ඞ");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
}


int main() {
    the_game();
    return 0;
}
