#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"

void print_front(char* field){
	int j = 0;
	
	for(int i = 0; i<144; i++){
		printf("%c ",field[i]);
		j++;
		if(j==12){
			printf("\n");
			j=0;
		}
	}
}

char insert_pos_row(){
	char pos;
	printf("\nInsert A to J position:\n");
	scanf(" %c",&pos);
	while((pos<65)||(pos>74)){
		printf("\nInvalid\n");
		printf("Insert A to J position:\n");
		scanf(" %c",&pos);	
	}
	return pos;
}

char insert_pos_col(){
	char pos;
	printf("\nInsert K to T position:\n");
	scanf(" %c",&pos);
	while((pos<75)||(pos>84)){
		printf("\nInvalid\n");
		printf("Insert K to T position:\n");
		scanf(" %c",&pos);		
	}
	return pos;
}

char insert_opt(){
	char pos_;
	printf("\nInsert O(open) or F(flag):\n");
	scanf(" %c",&pos_);
	return pos_;
}

void option_select(char* field_front_,char* field_back_, char option, int x, int y){
	if(option == 'F'){
		add_flag(x, y, field_front_);
	}
	if(option == 'O'){
		 open_pos(x, y, field_front_, field_back_);
	}
}

void verify_victory(char* field_front_, int bomb_amount_){
	int flag = 0;
	for(int i=0; i<144; i++){
		if(field_front_[i]=='*')flag++;
	}
	if(flag==bomb_amount_){
		printf("flag: %i",flag);
		printf("bomb_amount: %i",bomb_amount_);
		printf("VICTORY");
		exit(0);
	}
}

int bomb_amount(char* field_back_){
	int bomb_amount_ = 0;
	for(int i=0; i<144; i++){
		if(field_back_[i]=='b')bomb_amount_++;
	}
	return bomb_amount_;
}

int open_zero(char* field_front_, char* field_back_, int pos){
	field_front_[pos] = (field_back_[pos]=='0')? '0' : field_front_[pos];
	if((field_back_[pos-13]=='0')&&(field_front_[pos-13]!='0'))open_zero(field_front_,field_back_,pos-13);
	if((field_back_[pos-12]=='0')&&(field_front_[pos-12]!='0'))open_zero(field_front_,field_back_,pos-12);
	if((field_back_[pos-11]=='0')&&(field_front_[pos-11]!='0'))open_zero(field_front_,field_back_,pos-11);
	if((field_back_[pos-1]=='0')&&(field_front_[pos-1]!='0'))open_zero(field_front_,field_back_,pos-1);
	if((field_back_[pos+1]=='0')&&(field_front_[pos+1]!='0'))open_zero(field_front_,field_back_,pos+1);
	if((field_back_[pos+11]=='0')&&(field_front_[pos+11]!='0'))open_zero(field_front_,field_back_,pos+11);
	if((field_back_[pos+12]=='0')&&(field_front_[pos+12]!='0'))open_zero(field_front_,field_back_,pos+12);
	if((field_back_[pos+13]=='0')&&(field_front_[pos+13]!='0'))open_zero(field_front_,field_back_,pos+13);
	return 0;
}

int char_to_int(char position){
	return ((position-64)<11) ? position-64 : (position-64)-10;
}

void game_over(char* field_front_, char* field_back_){
	printf("\n GAME OVER\n");
	
	for(int i = 0; i < 144; i++){
		field_front_[i] = (field_back_[i] =='b') ? 'b' : field_front_[i];
	}
	
	print_front(field_front_);
	
	exit(0);
	
}

void open_pos(int x, int y, char* field_front_, char* field_back_){
	int pos;
	if(field_back_[x+(y*12)]!='b'){
		if(field_back_[x+(y*12)]!='0'){
			field_front_[x+(y*12)] = field_back_[x+(y*12)];
		}
		else{
			pos = x+(y*12);
			open_zero(field_front_, field_back_,pos);
		}
	}
	else{
		game_over(field_front_, field_back_);
	}
}

void add_flag(int x, int y, char* field_front_){
	
	field_front_[x+(y*12)] = '?';
	
}

char* field_front(){
	
	char* field;
	field = (char*) malloc(144*sizeof(char));
	int row = 0;
	
	//side area
	for(int i = 0; i < 144; i++)field[i] = '+';
	
	//coordenate x create
	for(int i = 1; i < 11; i++)field[i] = '@' + i;
	
	//coordenate y create
	for(int i = 12; i < 121; i=i+12)field[i] = 'J' + (i/12);
	
	
	//creating the bombs
	for(int i = 13; i < 131; i++){
		i 	= (row==10) ? i+2 : i;
		row	= (row==10) ? row = 0 : row; 
		field[i] = '*';  
		row++;

	}
	row = 0;

	return field;
		
}

char* field_back(time_t seed){
	
	char* field;
	field = (char*) malloc(144*sizeof(char));
	int nbomb = 0;
	int row = 0;
	
	//seed randon value
	srand(seed);

	//side area
	for(int i = 0; i < 144; i++)field[i] = 'w';
	
	//creating the bombs
	for(int i = 13; i < 131; i++){
		i 	= (row==10) ? i+2 : i;
		row	= (row==10) ? row = 0 : row; 
		field[i] = ((rand()%3)==1) ? 'b':'0';  
		row++;

	}
	row = 0;
	
	//creating the values
	for(int i = 13; i < 131; i++){
		i 	= (row==10) ? i+2 : i;
		row	= (row==10) ? row = 0 : row; 
		
		if(field[i]=='0'){
			if(field[i-13]=='b')nbomb++;
			if(field[i-12]=='b')nbomb++;
			if(field[i-11]=='b')nbomb++;
			if(field[i-1 ]=='b')nbomb++;
			if(field[i+1 ]=='b')nbomb++;
			if(field[i+11]=='b')nbomb++;
			if(field[i+12]=='b')nbomb++;
			if(field[i+13]=='b')nbomb++;
			field[i] = '0' + nbomb;			
		}
		
		row++;
		nbomb = 0;
	}	

	return field;
	
}

void minesweeper(){
	
	char* field_back_ = field_back(time(NULL));
	char* field_front_= field_front();
	char opt;
	int row = 0;
	int col = 0;
	int bomb_amount_ = bomb_amount(field_back_);
	
	print_front(field_front_);
	
	while(1){
		row = char_to_int(insert_pos_row());
		col = char_to_int(insert_pos_col());
		opt = insert_opt();
		
		option_select(field_front_,field_back_,opt, row, col);
		
		print_front(field_front_);
		verify_victory(field_front_, bomb_amount_);
	}
	
}
