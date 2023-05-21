#pragma once

int Mouse_click(int x, int y ,int width, int height); 
int mouse_click_wait(int x, int y ,int width, int height,int time, bool flag);

int Key_press(int VK, int time, bool extended);
int Key_down(int VK,bool extended);
int Key_up(int VK,bool extended);

int Char_press(char c,int time);
int Char_down(char c,bool extended);
int Char_up(char c);

void key_do(int screen_type);