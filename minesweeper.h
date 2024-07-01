#ifndef MINESWEEPER_H
#define MINESWEEPER_H

void print_front(char* field);//Print fhe field...it can be used to see back field

char insert_pos_row();//get the A to J

char insert_pos_col();//get the K to T

char insert_opt();//get the F(flag) or O(open)

void option_select(char* field_front_,char* field_back_, char option, int x, int y);//select of F(flag) or O(open)

void verify_victory(char* field_front_, int bomb_amount_);//verify the victory

int bomb_amount(char* field_back_);// counting of the bombs

int open_zero(char* field_front_, char* field_back_, int pos);//when 0 is open, it opens the rest of the zeros;

int char_to_int(char position);//trnsform a char coordinate in int

void game_over(char* field_front_, char* field_back_);//game over, when a bomb is open

void open_pos(int x, int y, char* field_front_, char* field_back_);//open the position

void add_flag(int x, int y, char* field_front_); // add flag in the front area;

char* field_front(); //creat the field showed to player

char* field_back(time_t seed); //creat field area

void minesweeper();//run the game


#endif // MINESWEEPER_H
