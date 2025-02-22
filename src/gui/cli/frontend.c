/*!
    @file
    @brief Tetris frontend part implementation
*/
#include <ncurses.h>
//#include <stdlib.h>

#include "frontend.h"

/*!
    @brief Interface output
*/
void InterfaceOutput(int code) {
  GameInfo_t instance = updateCurrentState();

  DeleteStartBanner();
  DeleteGameOver();
  PrintGameField((const int **)instance.field);

  if (code == 1 || code == 2) {
    if (code == 2)
      DrawingGameOver();

    DrawingStartBanner();
  }

  if (instance.pause)
    DrawPause();
  else
    DeletePause();

  DrawingNextFigureField();
  DrawingFieldBorders();

  DrawingHighScore(instance.high_score);
  DrawingScore(instance.score);
  DrawingLevel(instance.level);

  DrawingNextFigure(instance.next[0][4], instance.next[0][5]);
}

/*!
    @brief Print game field
    @param field Field
*/
void PrintGameField(const int **field) {

  attrset(A_BOLD);

  int color = 0;

  wchar_t block = OutputFigureBlock_Uni;

  for (int i = 0; i < FieldRows; i++)
    for (int j = 0; j < FieldCols; j++)
      if (j < 12 || (j > LeftBorder && i < RightBorder)) {
        color = GetColor(field[i][j]);

        attron(COLOR_PAIR(color));

        if (field[i][j] >= FigureSym)
          mvprintw(i, j * 3, "%lc", block);
        else
          mvprintw(i, j * 3, "%c", ' ');

        attroff(COLOR_PAIR(color));
      }

  attroff(A_BOLD);
}

/*!
    @brief Print rectangle
    @param top_y Top coordinate
    @param bottom_y Bottom coordinate
    @param left_x Left coordinate
    @param right_x Right coordinate
*/
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++)
    MVADDCH(top_y, i, ACS_HLINE);

  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);

  i = left_x + 1;

  for (; i < right_x; i++)
    MVADDCH(bottom_y, i, ACS_HLINE);

  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

/*!
    @brief Drawing field borders
*/
void DrawingFieldBorders() {
  attrset(A_BOLD);
  print_rectangle(-3, FieldRows - 3, 0, 30);
  attroff(A_BOLD);
}

/*!
    @brief Drawing game over
*/
void DrawingGameOver() {
  int color = Red;

  attrset(A_BOLD);

  PrintColorWc(4, 9, Fire_Uni, 0);

  PrintColorStr(4, 12, "GAME OVER", color);

  PrintColorWc(4, 22, Fire_Uni, 0);

  attroff(A_BOLD);
}

/*!
    @brief Clear game over from interface
*/
void DeleteGameOver() { mvprintw(4, 9, "%s", "               "); }

/*!
    @brief Print color string
    @param x X coordinate
    @param y Y coordinate
    @param string String
    @param color Color
*/
void PrintColorStr(int x, int y, const char *string, int color) {

  attron(COLOR_PAIR(color));

  mvprintw(x, y, "%s", string);

  attroff(COLOR_PAIR(color));
}

/*!
    @brief Print color wchar_t
    @param x X coordinate
    @param y Y coordinate
    @param wc symbol
    @param color Color
*/
void PrintColorWc(int x, int y, wchar_t symbol, int color) {

  attron(COLOR_PAIR(color));

  mvprintw(x, y, "%lc", symbol);

  attroff(COLOR_PAIR(color));
}

/*!
    @brief Drawing start banner
*/
void DrawingStartBanner() {
  int color = Yellow;

  attrset(A_BOLD);

  PrintColorStr(6, 7, "Click", 0);

  PrintColorStr(6, 13, "ENTER", color);

  PrintColorStr(6, 18, " for start", 0);

  wchar_t wc = ArrowDown_Uni;

  PrintColorWc(8, 12, wc, color);

  PrintColorStr(8, 13, "  Descent", 0);

  wc = ArrowRight_Uni;

  PrintColorWc(10, 12, wc, color);

  PrintColorStr(10, 13, "  Move", 0);

  PrintColorStr(10, 20, "Right", Green);

  wc = ArrowLeft_Uni;

  PrintColorWc(12, 12, wc, color);

  PrintColorStr(12, 13, "  Move", 0);

  PrintColorStr(12, 20, "Left", Cyan);

  PrintColorStr(14, 12, "r", color);

  PrintColorStr(14, 14, " Rotation", 0);

  PrintColorStr(16, 12, "p", color);

  PrintColorStr(16, 13, "  Pause", Red);

  wc = Pause_Uni;

  PrintColorWc(16, 21, wc, 0);

  PrintColorStr(18, 12, "q", color);

  PrintColorStr(18, 13, "  Exit", Red);

  attroff(A_BOLD);
}

/*!
    @brief Clear start banner from interface
*/
void DeleteStartBanner() {
  for (int i = 6; i < 19; i++)
    mvprintw(i, 7, "%s", "                    ");
}

/*!
    @brief Drawing pause
*/
void DrawPause() {
  attrset(A_BOLD);

  print_rectangle(17, 20, 34, 55);

  PrintColorStr(20, 38, "PAUSE ", Red);

  wchar_t wc = Pause_Uni;
  ;
  PrintColorWc(20, 44, wc, 0);

  attroff(A_BOLD);
}

/*!
    @brief Clear pause from interface
*/
void DeletePause() {
  for (int i = 19; i < 23; i++)
    mvprintw(i, 34, "%s", "                         ");
}

/*!
    @brief Drawing next figure field
*/
void DrawingNextFigureField() {
  attrset(A_BOLD);

  print_rectangle(-2, 4, 34, 55);

  PrintColorStr(1, 38, "NEXT", Green);

  attroff(A_BOLD);
}

/*!
    @brief Drawing high score
    @param high_score High score
*/
void DrawingHighScore(int high_score) {
  attrset(A_BOLD);

  PrintColorStr(8, 38, "HIGHSCORE", Magenta);

  mvprintw(9, 55, "%d", high_score);

  attroff(A_BOLD);
}

/*!
    @brief Drawing score
    @param score Score
*/
void DrawingScore(int score) {
  attrset(A_BOLD);

  mvprintw(13, 53, "%s", "          ");

  print_rectangle(9, 12, 34, 55);

  PrintColorStr(12, 38, "SCORE", Blue);
  // mvprintw(12, 38, "%s","SCORE");

  mvprintw(13, 55, "%d", score);

  attroff(A_BOLD);
}

/*!
    @brief Drawing level
    @param level Level
*/
void DrawingLevel(int level) {
  attrset(A_BOLD);

  mvprintw(17, 55, "%s", "   ");

  print_rectangle(13, 16, 34, 55);

  PrintColorStr(16, 38, "LEVEL", Red);

  mvprintw(17, 55, "%d", level);

  attroff(A_BOLD);
}

/*!
    @brief Drawing next figure
    @param next Next figure
    @param color Color
*/
void DrawingNextFigure(int next, int color) {
  int sym = 0;

  attrset(A_BOLD);
  attron(COLOR_PAIR(color));

  wchar_t wc = L'\0';

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 5; j++) {

      sym = figures[next * 2 + i][j];

      if (!sym)
        wc = L' ';
      else
        wc = OutputFigureBlock_Uni;

      mvprintw(i + 3, j * 3 + 40, "%lc", wc);
    }

  attroff(COLOR_PAIR(color));
  attroff(A_BOLD);
}

/*!
    @brief Get color
    @param i x coordinate
    @param j y coordinate
*/
int GetColor(int symbol) {
  return symbol >= FigureSym ? symbol - FigureSym : 0;
}