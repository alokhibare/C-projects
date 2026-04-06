#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <sys/select.h>
    #include <termios.h>
#endif

#define HEIGHT 20
#define WIDTH 60

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };
enum Direction dir;

int score, fruit_x, fruit_y, head_x, head_y, tail_length;
int tail_x[100], tail_y[100];

/* --- FLICKER-FREE UTILITY --- */
void move_cursor_home() {
#ifdef _WIN32
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    // ANSI escape code to move cursor to row 1, col 1
    printf("\033[H");
#endif
}

void hide_cursor() {
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    printf("\033[?25l");
#endif
}

/* --- INPUT HANDLING --- */
int input_available() {
#ifdef _WIN32
    return _kbhit();
#else
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
#endif
}

char get_key() {
#ifdef _WIN32
    return _getch();
#else
    char ch;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void spawn_fruit() {
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
}

void setup() {
    // Clear screen only ONCE at the start
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    hide_cursor();
    dir = STOP;
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    spawn_fruit();
    score = 0;
    tail_length = 0;
}

void draw() {
    move_cursor_home(); // Overwrite the current frame instead of clearing

    printf("Score: %d | WASD to move | X to exit   \n", score);
    
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            if (j == 0 || j == WIDTH + 1) {
                printf("#");
            } else if (i == head_y && (j - 1) == head_x) {
                printf("O"); // Snake Head
            } else if (i == fruit_y && (j - 1) == fruit_x) {
                printf("F"); // Fruit
            } else {
                int is_tail = 0;
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == (j - 1) && tail_y[k] == i) {
                        printf("o"); // Snake Tail
                        is_tail = 1;
                        break;
                    }
                }
                if (!is_tail) printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    fflush(stdout); 
}

void input() {
    if (input_available()) {
        char ch = get_key();
        switch (ch) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': exit(0);
        }
    }
}

void logic() {
    if (dir == STOP) return;

    // Move tail
    int prevX = tail_x[0], prevY = tail_y[0], prev2X, prev2Y;
    tail_x[0] = head_x; tail_y[0] = head_y;
    for (int i = 1; i < tail_length; i++) {
        prev2X = tail_x[i]; prev2Y = tail_y[i];
        tail_x[i] = prevX; tail_y[i] = prevY;
        prevX = prev2X; prevY = prev2Y;
    }

    // Move head
    switch (dir) {
        case LEFT:  head_x--; break;
        case RIGHT: head_x++; break;
        case UP:    head_y--; break;
        case DOWN:  head_y++; break;
        default: break;
    }

    // Wrap-around borders
    if (head_x >= WIDTH) head_x = 0; else if (head_x < 0) head_x = WIDTH - 1;
    if (head_y >= HEIGHT) head_y = 0; else if (head_y < 0) head_y = HEIGHT - 1;

    // Tail collision
    for (int i = 0; i < tail_length; i++) {
        if (tail_x[i] == head_x && tail_y[i] == head_y) {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            printf("GAME OVER! Final Score: %d\n", score);
            printf("developed by Alok.");
            exit(0);
        }
    }

    // Eat fruit
    if (head_x == fruit_x && head_y == fruit_y) {
        score += 10;
        tail_length++;
        spawn_fruit();
    }
}

int main() {
    srand(time(NULL));
    setup();

    while (1) {
        draw();
        input();
        logic();

        #ifdef _WIN32
            Sleep(80); // Roughly 12 frames per second
        #else
            usleep(80000); 
        #endif
    }
    return 0;
}
