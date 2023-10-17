#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>

#define SPD 50
#define start_cell_density 30
#define l_ico '@'
#define d_ico ' '

typedef struct _cell{
   int data;
}cell;

typedef struct _square{
   int x, y, w, h;
}square;

void printArea(WINDOW *w, cell **c,square camsq, square areasq);
void live(cell **area, cell **areaT,square sq);

int main(int argc, char *argv[]){
   WINDOW *win;
   cell **area;cell **areaT;
   int ch;
   //ncuses init
   initscr();
   noecho();
   cbreak();
   keypad(stdscr, TRUE);
   timeout(SPD);
   //square
   square screensq={.x=0,.y=0,.w=COLS,.h=LINES};
   square sq={.x=0,.y=0,.w=COLS-3,.h=LINES-2};
   sq.x=(COLS - sq.w )/2;
   sq.y=(LINES- sq.h )/2;

   //area and tmp area
   square areasq={.x=0,.y=0,.w=200,.h=200};
   area= (cell **)calloc(areasq.w, sizeof(cell *)); 
   areaT= (cell **)calloc(areasq.w, sizeof(cell *)); 
   for(int i = 0;i < areasq.w; ++i){
      area[i] = (cell *)calloc(areasq.h, sizeof(cell));
   }
   for(int i = 0;i < areasq.w; ++i){
      areaT[i] = (cell *)calloc(areasq.h, sizeof(cell));
   }
   
   win = newwin(sq.h, sq.w, sq.y, sq.x);

   //set base cell data
   for (int yy = 0; yy < areasq.h; yy++){for (int xx = 0; xx < areasq.w; xx++){
         area[xx][yy].data=rand()%100<start_cell_density;   
   }}

   //main loop

   int c;
	while((c = getch()) != 'q'){
      switch(c){
         case 'j':
            areasq.y+=1;
				break;
			case 'k':
            areasq.y-=1;
				break;
         case 'l':
            areasq.x+=2;
				break;
			case 'h':
            areasq.x-=2;
				break;
		}
      if(areasq.x<0){areasq.x+=areasq.w;}
      if(areasq.y<0){areasq.y+=areasq.h;}
      printArea(win,area,sq,areasq);
      box(win, 0 , 0);		
      live(area,areaT,areasq);
      wrefresh(win);

      //rezise
      if(COLS!=screensq.w || LINES != screensq.h){
         screensq.w=COLS;screensq.h=LINES;
         sq.w=COLS-3;sq.h=LINES-2;
         sq.x=(COLS - sq.w )/2;sq.y=(LINES- sq.h )/2;
         win = newwin(sq.h, sq.w, sq.y, sq.x);
      }
   }
   //exit
   endwin();
   return 0;
}
void live(cell **area, cell **areaT, square sq){
   for (int yy = 1; yy < sq.h-1; yy++){for (int xx = 1; xx < sq.w-1; xx++){
      areaT[xx][yy].data=area[xx][yy].data;
   }}

   for (int yy = 1; yy < sq.h-1; yy++){for (int xx = 1; xx < sq.w-1; xx++){
      int neigh=0;
      for(int a = -1; a <=1 ; a++){for(int b = -1; b <=1 ; b++){
         if(a!=0 || b!=0){
            neigh+=areaT[xx+a][yy+b].data;
         }
      }}
      if (areaT[xx][yy].data==1 && (neigh==2 || neigh==3)){
         area[xx][yy].data=1;
      }else if(neigh==3){
         area[xx][yy].data=1;
      }else{
         area[xx][yy].data=0;
      }
   }}
}

void printArea(WINDOW *w, cell **area, square camsq, square areasq){
   for (int yy = 1; yy < camsq.h-1; yy++){for (int xx = 1; xx < camsq.w-1; xx++){
      if(area[(xx+(areasq.x))%(areasq.w-2)+1][(yy+(areasq.y))%(areasq.h-2)+1].data==0){
         mvwaddch(w,yy, xx, d_ico);
      }else{
         mvwaddch(w,yy, xx, l_ico);
      }
   }}
}
