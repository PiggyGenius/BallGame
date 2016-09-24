#ifndef game_h
#define game_h

int Game_Start_Clicker_Analizer(int* ball_x,int* ball_y)

int Ball_Approval(int x,int y,int ball_value,int grid[10][15])

int Check_End_Game(int grid[10][15])

void Grid_Restore(int ball_value,int grid[10][15])

void Grid_Fixer(int grid[10][15])

void End_Game_Display(char* image)

int End_Game_Launcher(int grid[10][15])

int Mouse_Clicked_Manager(int grid[10][15], int difficulty)

int Mouse_Position_Manager(int grid[10][15], int difficulty)

int Game_Start(int difficulty, char* string_score, int grid[10][15], int score)

#endif