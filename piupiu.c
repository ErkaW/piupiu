#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// MENU
void menu();
void start();
void instructions();
void quit();
void startGame();
void gameover();

// GAME
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAX_HP 20
#define OPPONENT_HP 1
#define BULLETDAMAGE 1
#define OPPONENT_KILL_SCORE1 15
#define OPPONENT_KILL_SCORE2 10
#define OPPONENT_KILL_SCORE34 5
#define PLAYER '@'
#define OPPONENT1 '#'
#define OPPONENT2 '='
#define OPPONENT3 '+'
#define OPPONENT4 '+'
#define OPPONENTDEAD ' '
#define BULLET '*'
#define SPACE ' '
#define CHANCE_OF_ENEMY_SHOOTING 2 // Adjust the probability of enemy shooting

// Score
int score = 0;
int highscore = 0; 
// Player coordinates
int playerX = SCREEN_WIDTH / 2; // Center the player
// Player life
int playerLife = MAX_HP;
// Bullet coordinates
int bulletX = -1;
int bulletY = -1;
// Enemy arrays
int opponent1[SCREEN_WIDTH] = {0};
int opponent2[SCREEN_WIDTH] = {0};
int opponent3[SCREEN_WIDTH] = {0};
int opponent4[SCREEN_WIDTH] = {0};
// Bullet status
int bulletActive = 0;
// Declare the screen buffer
char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH + 1]; 
// Enemy bullet arrays
int enemyBulletX[SCREEN_WIDTH];
int enemyBulletY[SCREEN_WIDTH];
int enemyBulletActive[SCREEN_WIDTH];

// Function prototypes
void gotoxy(int x, int y);
void clearLines(int startY, int endY);
void updateBullet();
void spawnEnemy(int *opponent);
void drawEnemies(int *opponent, int y);
void drawPlayer();
void drawBullet();
void clearBullet();
void drawHUD();
void printScreenBuffer();
void readHighscore();
void writeHighscore();
void updateEnemyBullets();
void drawEnemyBullets();

// MAIN
int main() {
    srand(time(NULL)); // Seed the random number generator
    system("mode con: cols=80 lines=25");
    menu();
}

// MENU FUNCTION
void menu() {
    system("cls");
    int choice;
    printf(" /$$$$$$$  /$$$$$$ /$$   /$$ /$$$$$$$  /$$$$$$ /$$   /$$\n");
    printf("| $$__  $$|_  $$_/| $$  | $$| $$__  $$|_  $$_/| $$  | $$\n");
    printf("| $$  \\ $$  | $$  | $$  | $$| $$  \\ $$  | $$  | $$  | $$\n");
    printf("| $$$$$$$/  | $$  | $$  | $$| $$$$$$$/  | $$  | $$  | $$\n");
    printf("| $$____/   | $$  | $$  | $$| $$____/   | $$  | $$  | $$\n");
    printf("| $$        | $$  | $$  | $$| $$        | $$  | $$  | $$\n");
    printf("| $$       /$$$$$$|  $$$$$$/| $$       /$$$$$$|  $$$$$$/\n");
    printf("|__/      |______/ \\______/ |__/      |______/ \\______/ \n");
    printf("                                                        \n");
    printf("1. Start\n");
    printf("2. Instructions\n");
    printf("3. Quit\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            start();
            break;
        case 2:
            instructions();
            menu();
            break;
        case 3:
            quit();
            break;
        default:
            printf("Invalid input!\n");
            break;
    }
}

void instructions() {
    system("cls");
    printf("\nCara Bermain:\n");
    printf("1. Character player digerakan menggunakan 'A' & 'D' sebagai penggerak utama.\n");
    printf("2. Character player dapat menembak dengan menekan tombol 'C'.\n");
    printf("3. Player dapat bersembunyi di tembok dari tembakan lawan atau menghindarinya.\n");
    printf("4. Nyawa player akan berkurang jika terkena tembakan dari lawan.\n");
    printf("5. Player memiliki 20 HP dan satu tembakan lawan akan mengurangi 2 HP dari player.\n");
    printf("6. Tembakan lawan dapat muncul ditempat random dan dapat menghancurkan tembok.\n");
    printf("7. Jika HP player menyentuh angka '0' maka player akan kalah.\n");
    printf("\nSelamat Bermain !\n");
    printf("\nPress any key to continue . . . ");
    getch();
}

void quit() {
    system("cls");
    printf("Terima kasih telah bermain !");
    printf("\nPress any key to continue . . . ");
    getch();
    exit(0);
}

void start() {
    system("cls");
    printf(" /$$$$$$$  /$$$$$$ /$$   /$$ /$$$$$$$  /$$$$$$ /$$   /$$\n");
    printf("| $$__  $$|_  $$_/| $$  | $$| $$__  $$|_  $$_/| $$  | $$\n");
    printf("| $$  \\ $$  | $$  | $$  | $$| $$  \\ $$  | $$  | $$  | $$\n");
    printf("| $$$$$$$/  | $$  | $$  | $$| $$$$$$$/  | $$  | $$  | $$\n");
    printf("| $$____/   | $$  | $$  | $$| $$____/   | $$  | $$  | $$\n");
    printf("| $$        | $$  | $$  | $$| $$        | $$  | $$  | $$\n");
    printf("| $$       /$$$$$$|  $$$$$$/| $$       /$$$$$$|  $$$$$$/\n");
    printf("|__/      |______/ \\______/ |__/      |______/ \\______/ \n");
    printf("                                                        \n");
    printf("\nLoading...\n");
    for (int i = 0; i < 5; i++) {
        printf("===");
        fflush(stdout);
        Sleep(1000);
    }
    printf("\nPress any key to continue . . . ");
    getch();
    system("cls");
    startGame();
}

void gameover() {
    system("cls");
    printf(" /$$$$$$$  /$$$$$$ /$$   /$$ /$$$$$$$  /$$$$$$ /$$   /$$\n");
    printf("| $$__  $$|_  $$_/| $$  | $$| $$__  $$|_  $$_/| $$  | $$\n");
    printf("| $$  \\ $$  | $$  | $$  | $$| $$  \\ $$  | $$  | $$  | $$\n");
    printf("| $$$$$$$/  | $$  | $$  | $$| $$$$$$$/  | $$  | $$  | $$\n");
    printf("| $$____/   | $$  | $$  | $$| $$____/   | $$  | $$  | $$\n");
    printf("| $$        | $$  | $$  | $$| $$        | $$  | $$  | $$\n");
    printf("| $$       /$$$$$$|  $$$$$$/| $$       /$$$$$$|  $$$$$$/\n");
    printf("|__/      |______/ \\______/ |__/      |______/ \\______/ \n");
    printf("                                                        \n");
    printf("\nGame Over !\n");
    printf("\nYour Score: %d", score);
    printf("\nHighscore: %d", highscore);
    printf("\n1. Restart\n");
    printf("2. Menu\n");
    printf("3. Quit\n");
    printf("Please enter your choice: ");
    int c;
    scanf("%d", &c);
    switch (c) {
        case 1:
            startGame();
            break;
        case 2:
            menu();
            break;
        case 3:
            quit();
            break;
        default:
            printf("Invalid input!\n");
            break;
    }
}

// GAME FUNCTION
void startGame() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // Read the highscore from the highscore file
    readHighscore();

    // Initialize enemy arrays
    memset(enemyBulletX, -1, SCREEN_WIDTH * sizeof(int));
    memset(enemyBulletY, -1, SCREEN_WIDTH * sizeof(int));
    memset(enemyBulletActive, 0, SCREEN_WIDTH * sizeof(int));
    spawnEnemy(opponent1);
    spawnEnemy(opponent2);
    spawnEnemy(opponent3);
    spawnEnemy(opponent4);

    while (playerLife > 0) {
        // Update game
        updateBullet();
        updateEnemyBullets();

        // Clear only the lines that need to be updated
        clearLines(0, 3);
        clearLines(4, SCREEN_HEIGHT - 5);
        clearLines(SCREEN_HEIGHT - 4, SCREEN_HEIGHT + 1);

        // Draw game elements
        clearBullet(); // Clear the bullet's previous position
        drawEnemies(opponent1, 0);
        drawEnemies(opponent2, 1);
        drawEnemies(opponent3, 2);
        drawEnemies(opponent4, 3);
        drawPlayer();
        drawBullet();
        drawEnemyBullets();
        drawHUD();

        // Print the entire buffer to the console
        printScreenBuffer();

        // Check for collision with enemies and bullets
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            if (opponent4[i] && bulletX == i && bulletY == SCREEN_HEIGHT - 5) {
                if (bulletActive) {
                    bulletActive = 0;
                    opponent4[i] = 0;
                    score += OPPONENT_KILL_SCORE34;
                }
            } else if (opponent3[i] && bulletX == i && bulletY == SCREEN_HEIGHT - 5) {
                if (bulletActive) {
                    bulletActive = 0;
                    opponent3[i] = 0;
                    score += OPPONENT_KILL_SCORE34;
                }
            } else if (opponent2[i] && bulletX == i && bulletY == SCREEN_HEIGHT - 5) {
                if (bulletActive) {
                    bulletActive = 0;
                    opponent2[i] = 0;
                    score += OPPONENT_KILL_SCORE2;
                }
            } else if (opponent1[i] && bulletX == i && bulletY == SCREEN_HEIGHT - 5) {
                if (bulletActive) {
                    bulletActive = 0;
                    opponent1[i] = 0;
                    score += OPPONENT_KILL_SCORE1;
                }
            }
        }

        // Player input
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' && playerX > 0) {
                playerX--;
            } else if (key == 'd' && playerX < SCREEN_WIDTH - 3) {
                playerX++;
            } else if (key == 'c' && !bulletActive) {
                bulletX = playerX;
                bulletY = SCREEN_HEIGHT - 3;
                bulletActive = 1;
            }
        }

        // Enemy shooting
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            if (rand() % 100 < CHANCE_OF_ENEMY_SHOOTING) {
                // Find an inactive enemy bullet and activate it
                for (int j = 0; j < SCREEN_WIDTH; j++) {
                    if (!enemyBulletActive[j]) {
                        enemyBulletX[j] = i;
                        enemyBulletY[j] = 4;
                        enemyBulletActive[j] = 1;
                        break;
                    }
                }
            }
        }

        // Clear the bullet's previous position
        clearBullet();

        // Update bullet position
        updateBullet();

        // Draw the updated bullet
        drawBullet();

        Sleep(100);
    }
    
    // Update highscore
    if (score > highscore) {
        highscore = score;
    }

    // Add the highscore to the highscore file
    writeHighscore();

    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    gameover();
}

// Move the cursor to the specified coordinate
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Set the cursor position
}

// Clear the screen
void clearLines(int startY, int endY) {
    for (int y = startY; y <= endY; y++) {
        gotoxy(0, y);
        printf("%*s", SCREEN_WIDTH, ""); // Clear the line
    }
}

// Update the bullet position and check for collision
void updateBullet() {
    if (bulletActive) {
        bulletY--;
        if (bulletY < 0) {
            bulletActive = 0;
        }
    }
}

// Spawn enemies at the top of the screen
void spawnEnemy(int *opponent) {
    memset(opponent, 1, SCREEN_WIDTH * sizeof(int));
}

// Draw enemies into the buffer based on the enemy array and y-coordinate
void drawEnemies(int *opponent, int y) {
    // check if the enemy is dead
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        if (opponent[i] == 0) {
            gotoxy(i, y);
            printf("%c", OPPONENTDEAD);
        }
    }
    // Draw enemy based on the enemy array
    char enemyChar;
    if (opponent == opponent1) {
        enemyChar = OPPONENT1;
    } else if (opponent == opponent2) {
        enemyChar = OPPONENT2;
    } else if (opponent == opponent3) {
        enemyChar = OPPONENT3;
    } else if (opponent == opponent4) {
        enemyChar = OPPONENT4;
    }
    // if the enemy is alive, draw it
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        if (opponent[i]) {
            gotoxy(i, y);
            printf("%c", enemyChar);
        }
    }
}

// Draw the player into the buffer
void drawPlayer() {
    gotoxy(playerX, SCREEN_HEIGHT - 2);
    printf("%c", PLAYER);
}

void drawBullet() {
    if (bulletActive) {
        gotoxy(bulletX, bulletY);
        printf("%c", BULLET);
    }
}

void clearBullet() {
    if (bulletActive) {
        gotoxy(bulletX, bulletY);
        printf("%c", SPACE);
    }
}

void readHighscore() {
    FILE *highscoreFile = fopen("highscore.txt", "r");
    fscanf(highscoreFile, "%d", &highscore);
    fclose(highscoreFile);
}

void drawHUD() {
    gotoxy(0, SCREEN_HEIGHT);
    printf("Score: %d", score);
    gotoxy(SCREEN_WIDTH - 10, SCREEN_HEIGHT);
    printf("Highscore: %d", highscore);
    gotoxy(0, SCREEN_HEIGHT + 1);
    printf("Life: ");
    for (int i = 0; i < MAX_HP; i++) {
        if (i < playerLife) {
            printf("$");
        } else {
            printf("%c", SPACE);
        }
    }
}

void printScreenBuffer() {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
            gotoxy(0, y);
            printf("%s", screenBuffer[y]);
    }
}

void writeHighscore() {
    FILE *highscoreFile = fopen("highscore.txt", "w");
    fprintf(highscoreFile, "%d", highscore);
    fclose(highscoreFile);
}

void updateEnemyBullets() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        if (enemyBulletActive[i]) {
            enemyBulletY[i]++;
            if (enemyBulletY[i] >= SCREEN_HEIGHT) {
                enemyBulletActive[i] = 0;
            } else if (enemyBulletX[i] == playerX && enemyBulletY[i] == SCREEN_HEIGHT - 2) {
                enemyBulletActive[i] = 0;
                playerLife -= BULLETDAMAGE;
                if (playerLife <= 0) {
                    gameover();
                }
            }
        }
    }
}

void drawEnemyBullets() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        if (enemyBulletActive[i]) {
            gotoxy(enemyBulletX[i], enemyBulletY[i]);
            printf("%c", BULLET);
        }
    }
}