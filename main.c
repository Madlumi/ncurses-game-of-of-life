#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>

typedef struct _cell{
int data;
}cell;
typedef struct _square{
   int x;
   int y;
   int w;
   int h;
}square;
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{	WINDOW *win;
	int startx, starty, width, height;
	int ch;
	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
   square sq={.x=0,.y=0,.w=COLS-3,.h=LINES-2};
   sq.x=(COLS - sq.w )/2;
   sq.y=(LINES- sq.h )/2;
	refresh();
   win = newwin(sq.h, sq.w, sq.y, sq.x);
	box(win, 0 , 0);		
	wrefresh(win);		
   timeout(100);
   while(getch() != KEY_F(1)){
      
      for (int yy = 1; yy < sq.h-1; yy++){
      int lw = rand()%sq.w-2;
         for (int xx = 1; xx < lw; xx++){
         mvwaddch(win,yy, xx, rand()%127);
      }
      }
	box(win, 0 , 0);		
	wrefresh(win);
   }
 
		
	endwin();
	return 0;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
