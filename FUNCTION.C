/*
This software is a work from yzonesoft, released under GNU GPL licence.
The things you are not allowed to do are the following,
1) Removing my credits in any part of the software
2) saying that all this software is yours 
* read GNU GPL licence for more info
* also read the GNU GPL licence faq

   __  __
  \  \/ / 
   \ / /   ___   __     __    __      ___   __  ___  __          __    __   __
    | |      /  |  |  |/  |  |_      \__   |  |  |  |_   |   |  /__\  |__| |_
    |_|    /__  |__|  |   |  |__      __/  |__|  |  |    \/\/   |  |  | \  |__

   yzonesoft@yahoo.com                              Copyright (C) 2005  Yogesh       
   http://yzonesoft.buildtolearn.net

for info about compiling this software read readme.txt

Copyright (C) 2005  Yogesh
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "allegro.h"
#include "jpgalleg.h"
#include "bol.h"
#include "data.h"
#include "time.h"
#include <alrand/alrand.h>

#define     BLACK           0               // COLOUR(card)
#define     RED             1

#define     ACE             0               // VALUE(card)
#define     DEUCE           1

#define     CLUB            0               // SUIT(card)
#define     DIAMOND         1
#define     HEART           2
#define     SPADE           3

#define     SUIT(card)      ((card) % 4)
#define     VALUE(card)     ((card) / 4)
#define     COLOUR(card)    (SUIT(card) == DIAMOND || SUIT(card) ==HEART)

#define     MAXPOS         21
#define     MAXCOL          9    // includes top row as column 0




 time_t t;
 
 char *time_str,time_now[2];
  int time_hr,time_min,time_tmp[2];
 int first_time=1;            //FLAG,loop using it,run once
 int time_check=1,time_out=2,time_pmin=200;
 int mouse_ready=1;  //flag says that mouse is ready to accept events
 int mouse_rready=1; //for right click
int main_menu_y;   //to adjust hight according to show_full_display

 int free_flag=0; //flag to remove the mouse cursor showing on the freecell
 long my_seed;


void do_it_one_time()
{
 int i,j;
 int color;

 if(global.colour_depth==1)
 {
   colour.transperent=0;
   colour.black=makecol(0,0,0);
   colour.blue=makecol(0,0,255);
   colour.white=makecol(255,255,255);
   colour.surface_grey=makecol(202,202,202);
   colour.dark_grey_boundry=makecol(127,127,127);
   colour.light_grey_boundry=makecol(223,223,223);
   colour.item_selected=makecol(0,0,127);
   colour.bg_green_dark=makecol(0,120,0);
   colour.bg_green_light=makecol(0,255,0);
 }


 if(global.colour_depth==2)
  {
   colour.transperent=makecol(255,0,255); 
   colour.black=makecol(0,0,0);
   colour.blue=makecol(0,0,255);
   colour.white=makecol(255,255,255);
   colour.surface_grey=makecol(230,230,230);
   colour.dark_grey_boundry=makecol(127,127,127);
   colour.light_grey_boundry=makecol(223,223,223);
   colour.item_selected=makecol(0,0,127);
   colour.bg_green_dark=makecol(0,120,0);
   colour.bg_green_light=makecol(0,255,0);
  }
  
 if(global.colour_depth==2)
 {
  color=getpixel(data[XKING_L].dat,0,0);
   for(i=0;i<32;i++)
   {
    for(j=0;j<32;j++)
     {
         if(color==getpixel(data[XKING_L].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.transperent);
         else
           putpixel(buffer,500+i,300+j,getpixel(data[XKING_L].dat,i,j));
     }
   }
     blit(buffer,data[XKING_L].dat,500,300,0,0,32,32);

   for(i=0;i<32;i++)
   {
    for(j=0;j<32;j++)
     {
         if(color==getpixel(data[XKING_R].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.transperent);
         else
           putpixel(buffer,500+i,300+j,getpixel(data[XKING_R].dat,i,j));
     }
   }
     blit(buffer,data[XKING_R].dat,500,300,0,0,32,32);

  color=getpixel(data[XKING_W].dat,0,0);
   for(i=0;i<32;i++)
   {
    for(j=0;j<32;j++)
     {
         if(color==getpixel(data[XKING_W].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.bg_green_dark);
         else
           putpixel(buffer,500+i,300+j,getpixel(data[XKING_W].dat,i,j));
     }
   }
     blit(buffer,data[XKING_W].dat,500,300,0,0,32,32);


 }

 rectfill(mouse,0,0,12,21,colour.white);
 line(mouse,1,1,1,15,colour.black);
 line(mouse,1,1,10,10,colour.black);
 line(mouse,10,11,7,11,colour.black);
 line(mouse,7,11,10,18,colour.black);
 line(mouse,8,19,9,19,colour.black);
 line(mouse,5,13,7,18,colour.black);
 line(mouse,1,15,4,12,colour.black);
 triangle(mouse,1,0,11,0,11,10,colour.transperent);
 line(mouse,0,0,0,20,colour.transperent);
 line(mouse,11,0,11,20,colour.transperent);
 line(mouse,1,16,1,20,colour.transperent);
 line(mouse,2,15,2,20,colour.transperent);
 line(mouse,3,14,3,20,colour.transperent);
 line(mouse,4,13,4,20,colour.transperent);
 line(mouse,5,15,5,20,colour.transperent);
 line(mouse,6,17,6,20,colour.transperent);
 line(mouse,7,19,7,20,colour.transperent);
 line(mouse,10,19,10,20,colour.transperent);
 line(mouse,8,12,8,12,colour.transperent);
 line(mouse,9,12,9,14,colour.transperent);
 line(mouse,10,12,10,16,colour.transperent);

 blit(mouse,temp,1,0,0,0,10,20);     //Just shifting the mouse pointer to left
 blit(mouse,temp,0,0,10,0,1,20);
 blit(temp,mouse,0,0,0,0,11,20);
 blit(temp,data[XMOUSE].dat,0,0,0,0,11,20);

rectfill(data[XMOUSE_DOWN].dat,0,0,2,12,colour.transperent);
rectfill(data[XMOUSE_DOWN].dat,11,0,13,12,colour.transperent);
line(data[XMOUSE_DOWN].dat,0,26,0,17,colour.transperent);
line(data[XMOUSE_DOWN].dat,1,26,1,19,colour.transperent);
line(data[XMOUSE_DOWN].dat,2,26,2,21,colour.transperent);
line(data[XMOUSE_DOWN].dat,3,26,3,23,colour.transperent);
line(data[XMOUSE_DOWN].dat,4,26,4,25,colour.transperent);
line(data[XMOUSE_DOWN].dat,5,26,5,26,colour.transperent);
line(data[XMOUSE_DOWN].dat,13,26,13,17,colour.transperent);
line(data[XMOUSE_DOWN].dat,12,26,12,19,colour.transperent);
line(data[XMOUSE_DOWN].dat,11,26,11,21,colour.transperent);
line(data[XMOUSE_DOWN].dat,10,26,10,23,colour.transperent);
line(data[XMOUSE_DOWN].dat,9,26,9,25,colour.transperent);
line(data[XMOUSE_DOWN].dat,8,26,8,26,colour.transperent);


// blit(data[XMOUSE_DOWN].dat,mouse,0,0,0,0,14,27);
// mouse1.h=27;
// mouse1.w=14;

rectfill(data[XMOUSE_UP].dat,0,6,2,18,colour.transperent);
rectfill(data[XMOUSE_UP].dat,6,6,8,18,colour.transperent);
line(data[XMOUSE_UP].dat,3,0,0,3,colour.transperent);
line(data[XMOUSE_UP].dat,2,0,0,2,colour.transperent);
line(data[XMOUSE_UP].dat,1,0,0,1,colour.transperent);
line(data[XMOUSE_UP].dat,0,0,0,0,colour.transperent);
line(data[XMOUSE_UP].dat,5,0,8,3,colour.transperent);
line(data[XMOUSE_UP].dat,6,0,8,2,colour.transperent);
line(data[XMOUSE_UP].dat,7,0,8,1,colour.transperent);
line(data[XMOUSE_UP].dat,8,0,8,0,colour.transperent);
 set_mouse_sprite_focus(0,0);
 mouse_x=SCREEN_W/2;
 mouse_y=SCREEN_H/2;

 mouse1.x=mouse_x;
 mouse1.y=mouse_y;
 mouse1.px=mouse1.x;
 mouse1.py=mouse1.y; 
 mouse1.Fx=mouse1.x;
 mouse1.Fy=mouse1.y; 
}


//======================================================


void init_screen(int type)
{
 BITMAP *bmp;
 int i,j;


if(global.cheat==1)
  global.cheat=0;

//blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,11,20);
if(settings.background!=1)
{
rectfill(dblbuffer,0,0,SCREEN_W,SCREEN_H,colour.bg_green_dark);
rectfill(background,0,0,SCREEN_W,SCREEN_H,colour.bg_green_dark);
}

if(settings.background==1)
{
   chdir("bg");
   bmp = load_jpg(settings.bg, NULL);

for(i=0;i<SCREEN_W;i=i+bmp->w)
 {
 for(j=0;j<SCREEN_H;j=j+bmp->h)
  {
   blit(bmp,dblbuffer,0,0,i,j,bmp->w,bmp->h);
   blit(bmp,background,0,0,i,j,bmp->w,bmp->h);
  }
 }
chdir(game_path);
destroy_bitmap(bmp);
}
 if(settings.fullscreen==1 || settings.status_bar==1)
 {
  if(global.colour_depth==2)
  {
  for(i=0;i<27;i++)
   line(dblbuffer,0,i,SCREEN_W,i,makecol(240-((i)*7),240-((i)*7),240-((i)*7)) );  //upto 21
  }
  else
  rectfill(dblbuffer,0,0,SCREEN_W,26,colour.item_selected);
  if(global.colour_depth==1)
  {
  rectfill(dblbuffer,7,7,24,22,colour.surface_grey);
  line(dblbuffer,7,22,24,22,colour.black);
  line(dblbuffer,24,7,24,22,colour.black);
  line(dblbuffer,8,21,23,21,colour.dark_grey_boundry);
  line(dblbuffer,23,8,23,21,colour.dark_grey_boundry);
  line(dblbuffer,8,8,22,8,colour.white);
  line(dblbuffer,9,12,22,12,colour.white);
  rectfill(dblbuffer,9,9,22,10,makecol(0,0,255));
  }
   if(global.colour_depth==1)
   {
   textprintf_ex(dblbuffer,data[XSANS].dat,25,8,colour.white,-1,"Bolitaire 0.63a 18th Mar 2005");
   textprintf_ex(dblbuffer,data[XSANS].dat,26,8,colour.white,-1,"Bolitaire 0.63a 18th Mar 2005");
   }
   else
   {
   textprintf_ex(dblbuffer,data[XSANS].dat,9,8,colour.white,-1,"Bolitaire 0.63a 18th Mar 2005");
   textprintf_ex(dblbuffer,data[XSANS].dat,10,8,colour.white,-1,"Bolitaire 0.63a 18th Mar 2005");
   
   }
  blit(dblbuffer,buffer,0,0,SCREEN_W-27,6,21,19);
  buttons_related(dblbuffer,SCREEN_W-27,6,SCREEN_W-7,24,1);
  blit(buffer,dblbuffer,SCREEN_W-27,6,0,0,21,19);

  line(dblbuffer,SCREEN_W-21,18,SCREEN_W-14,11,colour.black);
  line(dblbuffer,SCREEN_W-21,19,SCREEN_W-13,11,colour.black);
  line(dblbuffer,SCREEN_W-20,19,SCREEN_W-13,12,colour.black);
  line(dblbuffer,SCREEN_W-21,12,SCREEN_W-14,19,colour.black);
  line(dblbuffer,SCREEN_W-21,11,SCREEN_W-13,19,colour.black);
  line(dblbuffer,SCREEN_W-20,11,SCREEN_W-13,18,colour.black);

  line(dblbuffer,SCREEN_W-1,0,SCREEN_W-1,SCREEN_H-1,colour.black);                    //black color
  line(dblbuffer,SCREEN_W-2,1,SCREEN_W-2,SCREEN_H-2,colour.dark_grey_boundry);              // dark grey boundry
  line(dblbuffer,0,SCREEN_H-1,SCREEN_W-1,SCREEN_H-1,colour.black);
  line(dblbuffer,1,SCREEN_H-2,SCREEN_W-2,SCREEN_H-2,colour.dark_grey_boundry);

  line(dblbuffer,0,0,0,SCREEN_H-2,colour.light_grey_boundry);
  line(dblbuffer,1,1,1,SCREEN_H-3,colour.light_grey_boundry);    //or colour.white
  line(dblbuffer,0,0,SCREEN_W-2,0,colour.light_grey_boundry);
  line(dblbuffer,1,1,SCREEN_W-3,1,colour.white);    //or colour.white

  rect(dblbuffer,2,2,SCREEN_W-3,SCREEN_H-3,colour.surface_grey);

  rectfill(dblbuffer,0,SCREEN_H-28,SCREEN_W-1,SCREEN_H-1,colour.surface_grey);

  blit(dblbuffer,buffer,0,0,0,SCREEN_H-28,SCREEN_W,28);
  buttons_related(dblbuffer,0,SCREEN_H-28,SCREEN_W-1,SCREEN_H-1,0);             //status bar
  blit(buffer,dblbuffer,0,SCREEN_H-28,0,0,SCREEN_W,28);

  blit(dblbuffer,buffer,0,0,SCREEN_W-26,SCREEN_H-25,72,21);
  buttons_related(dblbuffer,SCREEN_W-76,SCREEN_H-25,SCREEN_W-5,SCREEN_H-5,3);
  blit(buffer,dblbuffer,SCREEN_W-26,SCREEN_H-25,0,0,72,21);

  line(dblbuffer,SCREEN_W-81,SCREEN_H-25,SCREEN_W-81,SCREEN_H-5,colour.white);
  line(dblbuffer,SCREEN_W-80,SCREEN_H-25,SCREEN_W-80,SCREEN_H-5,colour.dark_grey_boundry);
//  line(screen,501,575,501,595,colour.white);
//  line(screen,502,575,502,595,colour.dark_grey_boundry);
  main_menu_y=27;
  rectfill(dblbuffer,2,main_menu_y,SCREEN_W-3,main_menu_y+18,colour.surface_grey);      // main button back colour
  line(dblbuffer,2,main_menu_y+19,2,main_menu_y+SCREEN_H-56,colour.dark_grey_boundry);
  FOCUS_Y=160;
  }
 else
  {
   main_menu_y=0;
  FOCUS_Y=133;
  rectfill(dblbuffer,0,main_menu_y,SCREEN_W,main_menu_y+18,colour.surface_grey);      // main button back colour
  }

  line(dblbuffer,2,main_menu_y+19,SCREEN_W-3,main_menu_y+19,colour.dark_grey_boundry);
   
  textprintf_ex(dblbuffer,data[XSANS].dat,menustart,main_menu_y,0,-1,"%s",menus[0][0]);   
  line(dblbuffer,14,main_menu_y+14,24,main_menu_y+14,0); 
  textprintf_ex(dblbuffer,data[XSANS].dat,menustart+50,main_menu_y,0,-1,"%s",menus[1][0]); 
  line(dblbuffer,63,main_menu_y+14,74,main_menu_y+14,0);
  if(global.xtra_menu_active==1)
  {
  textprintf_ex(dblbuffer,data[XSANS].dat,menustart+93,main_menu_y,0,-1,"%s",menus[2][0]); 
  line(dblbuffer,106,main_menu_y+14,116,main_menu_y+14,0);
  }

      if(type==0)
      {
         fn=0;
         active_number=1;
           form[fn].card=61;  // 61  means no card
           form[fn].w=50;
           form[fn].h=16;
           form[fn].x=menustart-7;
           form[fn].y=main_menu_y+1;
           form[fn].type=3;
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=1;
           form[fn].n=502;
           activeform[active_number]=fn;
           active_number=active_number+1;
           //form[fn].Focus_y=FOCUS_Y;
           fn=fn+1; 


           form[fn].card=61;
           form[fn].w=43;
           form[fn].h=16;
           form[fn].x=menustart+43;
           form[fn].y=main_menu_y+1;
           form[fn].type=3;
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=1;
           form[fn].n=503;
           activeform[active_number]=fn;
           active_number=active_number+1;
           //form[fn].Focus_y=FOCUS_Y;
           fn=fn+1; 
    if(global.xtra_menu_active==1)
    {
           form[fn].card=61;
           form[fn].w=54;
           form[fn].h=16;
           form[fn].x=menustart+86;
           form[fn].y=main_menu_y+1;
           form[fn].type=3;
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=1;
           form[fn].n=504;
           activeform[active_number]=fn;
           active_number=active_number+1;
           //form[fn].Focus_y=FOCUS_Y;
           fn=fn+1; 
     }

//  buttons_related(screen,773,6,793,24,1); just for reference EXIT button
           global.exit_fn=fn;
           form[fn].card=61;
           form[fn].w=20;    //this set is for EXIT button
           form[fn].h=18;
           form[fn].x=SCREEN_W-27;    
           form[fn].y=6;
           form[fn].type=4;
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           form[fn].n=501;   //SPECIAL BUTTON NUMBER 1 EXIT
           activeform[active_number]=fn;
           active_number=active_number+1;

           //form[fn].Focus_y=FOCUS_Y;
           fn=fn+1; 
        }
 if(settings.fullscreen==1 || settings.status_bar==1)
   {
     rectfill(timetemp,0,0,55,14,colour.surface_grey);
     textprintf_ex(timetemp,data[XSANS].dat,0,0,0,-1,"%d:%.2d %c%c",time_hr,time_min,time_now[0],time_now[1]);
     blit(timetemp,dblbuffer,0,0,730,577,55,15);
  }

   blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h);   //there is a chance of dirty mouse blit if mouse_x changes when reaching draw_mouse
   masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
   blit(dblbuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}



//============================================================================================================
void ca_things(BITMAP *bitmap,char *s,int x,int y,int x1,int y1,int w,int h,int type)
{
 int i,j;
 if(type==601)
  {
     form[fn].card=61;  // 61  means no card
     form[fn].w=w;
     form[fn].h=h;
     form[fn].x=form[dialog_fn].x+x1;
     form[fn].y=form[dialog_fn].y+y1;
     form[fn].type=21;  //special number for buttons
     form[fn].selected=0;
     form[fn].rselected=0;
     form[fn].can_over=0;
     fn=fn+1; 

    rectfill(bitmap,x1,y1,x1+w,y1+h,colour.surface_grey);
    line(bitmap,x1,y1+h,x1+w,y1+h,0);
    line(bitmap,x1+w,y1+h,x1+w,y1,0);
    line(bitmap,x1+1,y1+h-1,x1+w-1,y1+h-1,colour.dark_grey_boundry);
    line(bitmap,x1+w-1,y1+h-1,x1+w-1,y1+1,colour.dark_grey_boundry);
    line(bitmap,x1,y1,x1,y1+h-1,colour.white);
    line(bitmap,x1,y1,x1+w-1,y1,colour.white);
    line(bitmap,x1+1,y1+1,x1+1,y1+h-2,colour.light_grey_boundry);
    line(bitmap,x1+1,y1+1,x1+w-2,y1+1,colour.light_grey_boundry);

    if(browser.ampobe!=1)
    textprintf_ex(bitmap,data[XSANS].dat,x,y,0,-1,"%s",s);
    else
    textprintf_ex(bitmap,data[XSANS2].dat,x,y,0,-1,"%s",s);
  }

  if(type==611)       //this is for creating list box
  {
    rectfill(bitmap,x1+2,y1+2,x1+w-2,y1+h-2,colour.white);
    line(bitmap,x1,y1+h,x1+w,y1+h,colour.white);
    line(bitmap,x1+w,y1+h,x1+w,y1,colour.white);
    line(bitmap,x1+1,y1+h-1,x1+w-1,y1+h-1,colour.light_grey_boundry);
    line(bitmap,x1+w-1,y1+h-1,x1+w-1,y1+1,colour.light_grey_boundry);
    line(bitmap,x1,y1,x1,y1+h-1,0);
    line(bitmap,x1,y1,x1+w-1,y1,0);
    line(bitmap,x1+1,y1+1,x1+1,y1+h-2,colour.dark_grey_boundry);
    line(bitmap,x1+1,y1+1,x1+w-2,y1+1,colour.dark_grey_boundry);

//rectfill(bitmap,x1+w-17,y1+2,x1+w-2,y1+17,0);
 for(i=y1+2;i<y1+h-17;i=i+1)
 {
  if(i%2)
  {
   for(j=x1+w-17;j<x1+w-1;j=j+2)
   putpixel(bitmap,j,i,colour.surface_grey);
  }
 else
  {
   for(j=x1+w-17+1;j<x1+w-1;j=j+2)
   putpixel(bitmap,j,i,colour.surface_grey);
  }
 }

    buttons_related(bitmap,x1+w-17,y1+2,x1+w-2,y1+17,630);
    buttons_related(bitmap,x1+w-17,y1+h-17,x1+w-2,y1+h-2,630);
 i=0;                                  //vertical up
  for(j=0;j<=4;j++)
     {
     line(bitmap,x1+w-17+7-i,y1+2+5+j,x1+w-17+7+i,y1+2+5+j,colour.black);
      i=i+1;
      }
 i=4;                                  //vertical bottom
  for(j=0;j<=4;j++)
     {
     line(bitmap,x1+w-17+7-i,y1+h-17+6+j,x1+w-17+7+i,y1+h-17+6+j,colour.black);
      i=i-1;
      }
   i=form[dialog_fn].x+x1+w-17; //just getting i=form[fn].x
     if(i-form[dialog_fn].x>400)
     {
      browser.f_u=form[dialog_fn].y+y1+3+15;
      browser.f_d=form[dialog_fn].y+y1+h-18;      
     }
     else
     {
      browser.d_u=form[dialog_fn].y+y1+3+15;     
      browser.d_d=form[dialog_fn].y+y1+h-18;     
     }

     form[fn].card=61;  // 61  means no card
     form[fn].w=15;
     form[fn].h=15;
     form[fn].x=form[dialog_fn].x+x1+w-17;
     form[fn].y=form[dialog_fn].y+y1+2;
     form[fn].type=22;  //special number for scrll buttons
     if(form[fn].x-form[dialog_fn].x>400)
        form[fn].n=51;  //51 for up scroll
       else
        form[fn].n=53;  //51 for up scroll        
     form[fn].selected=0;
     form[fn].rselected=0;
     form[fn].can_over=0;
     fn=fn+1; 

     form[fn].card=61;  // 61  means no card
     form[fn].w=15;
     form[fn].h=15;
     form[fn].x=form[dialog_fn].x+x1+w-17;
     form[fn].y=form[dialog_fn].y+y1+h-17;
     form[fn].type=22;  //special number for scroll buttons
     if(form[fn].x-form[dialog_fn].x>400)
        form[fn].n=52;  //51 for up scroll
       else
        form[fn].n=54;  //51 for up scroll        
     form[fn].selected=0;
     form[fn].rselected=0;
     form[fn].can_over=0;
     fn=fn+1; 
//~~~~~~reserving for scroll bars~~~~~~~~~~~~~~
     form[fn].card=61;  // 61  means no card
     form[fn].w=0;
     form[fn].h=0;
     form[fn].x=form[dialog_fn].x+x1+w-17;
     form[fn].y=0;
     form[fn].type=24;  //special number for scroll buttons
     if(form[fn].x-form[dialog_fn].x>400)
        browser.file_scroll=fn;  //51 for file
       else
        browser.dir_scroll=fn;  //51 for dir        
     form[fn].selected=0;
     form[fn].rselected=0;
     form[fn].can_over=0;
     fn=fn+1; 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    rectfill(bitmap,x1,y1,x1+w,y1+h,colour.white);
//    rect(bitmap,x1,y1,x1+w,y1+h,colour.dark_grey_boundry);    
  }

}

//=============================================================
void init_dir_files()   //to set up the directories for browser
{
//  char chrs[34];
  int i,j;
  browser.first_dir_fn=fn;
  for(i=0;i<browser.contain_dir;i++)
   {
//    if(windows_version==1 | dos_version==1)
//        textprintf_ex(form1,data[XSANS2].dat,12,79+i*16,colour.black,-1,"%s",directory[i].name);
//     else
//        textprintf_ex(form1,data[XSANS2].dat,12,57+i*16,colour.black,-1,"%s",directory[i].name);     
     form[fn].card=61;  // 61  means no card
     form[fn].w=250;
     form[fn].h=17;
     form[fn].x=form[dialog_fn].x+10;
    if(windows_version==1 | dos_version==1)
       form[fn].y=form[dialog_fn].y+77+i*16;
     else
       form[fn].y=form[dialog_fn].y+55+i*16;
     form[fn].type=32;  //seelct one
     form[fn].selected=0;
     form[fn].rselected=0;
     form[fn].can_over=0;
     fn=fn+1; 
   }
  browser.first_file_fn=fn;
  for(i=0;i<browser.contain_file;i++)
   {
//      for(j=0;j<34;j++)
//        chrs[j]=file[i].name[j];
//      chrs[j]='\0';  
//    if(windows_version==1 | dos_version==1)
//       textprintf_ex(form1,data[XSANS2].dat,306,79+i*16,colour.black,-1,"%s",chrs);
//     else
//       textprintf_ex(form1,data[XSANS2].dat,306,57+i*16,colour.black,-1,"%s",chrs);
     form[fn].card=61;  // 61  means no card
     form[fn].w=250;
     form[fn].h=17;
     form[fn].x=form[dialog_fn].x+304;
    if(windows_version==1 | dos_version==1)
      form[fn].y=form[dialog_fn].y+77+i*16;
     else
      form[fn].y=form[dialog_fn].y+55+i*16;
     form[fn].type=31;  //special number for selecting multiple files
     form[fn].selected=0;
     form[fn].rselected=0;
     form[fn].can_over=0;
     fn=fn+1; 

   }


}


//======================================================================================
void buttons_related(BITMAP *bitmap,int x1,int y1,int x2,int y2,int button_type)
{
  int w,h;
  int no_mouse;
  w=x2-x1;
  h=y2-y1;
  no_mouse=0;


// if(mouse_x>=x1 && mouse_y>=y1 && mouse_x <x2 && mouse_y <=h)
  if(button_type>600)
    {
    button_type=button_type-600;
    no_mouse=2;
    }     
   else if(button_type>500)
    {
    button_type=button_type-500;
    no_mouse=1;
    }     
   
   if(no_mouse==0)
   mouse_null(bitmap,x1,y1,w+1,h+1);

  if( button_type==55 || button_type==54 || button_type==53)   //Radio_button
   {
     rectfill(temp,0,0,w+1,h+1,colour.surface_grey);
     if(button_type==55 || button_type==54)
        rectfill(temp,2,2,9,9,colour.white);

     line(temp,4,0,7,0,colour.dark_grey_boundry);
     line(temp,4,1,7,1,0);
     line(temp,4,10,7,10,colour.light_grey_boundry);
     line(temp,4,11,7,11,colour.white);               
     
     line(temp,2,1,3,1,colour.dark_grey_boundry);
     line(temp,2,2,3,2,0);
     line(temp,2,9,3,9,colour.light_grey_boundry);
     line(temp,2,10,3,10,colour.white);               
      
     line(temp,8,1,9,1,colour.dark_grey_boundry);
     line(temp,8,2,9,2,0);
     line(temp,8,9,9,9,colour.light_grey_boundry);
     line(temp,8,10,9,10,colour.white);               
     
     line(temp,0,4,0,7,colour.dark_grey_boundry);
     line(temp,1,4,1,7,0);
     line(temp,10,4,10,7,colour.light_grey_boundry);
     line(temp,11,4,11,7,colour.white);               

     line(temp,1,2,1,3,colour.dark_grey_boundry);     
     line(temp,10,2,10,3,colour.white);          
     line(temp,1,8,1,9,colour.dark_grey_boundry);     
     line(temp,10,8,10,9,colour.white);          

     putpixel(temp,2,3,0);     
     putpixel(temp,9,3,colour.light_grey_boundry);          
     putpixel(temp,2,8,0);     
     putpixel(temp,9,8,colour.light_grey_boundry);          

   }
 
 if( button_type==54)   //Radio_button
    {
      rect(temp,5,4,6,7,0);
      rect(temp,4,5,7,6,0);               
     }
     
   if( button_type==56 || button_type==57 || button_type==58 || button_type==59)   //Text_input
   {
    rectfill(temp,2,2,w-2,h-2,colour.white);
    line(temp,0,h,w,h,colour.white);
    line(temp,w,h,w,h-h,colour.white);
    line(temp,1,h-1,w-1,h-1,colour.light_grey_boundry);
    line(temp,w-1,h-1,w-1,1,colour.light_grey_boundry);
    line(temp,0,0,0,h-1,0);
    line(temp,0,0,w-1,0,0);
    line(temp,1,1,1,h-2,colour.dark_grey_boundry);
    line(temp,1,1,w-2,1,colour.dark_grey_boundry);
   }

   if(button_type==58 || button_type==59)   //check surface grey
     rectfill(temp,2,2,10,10,colour.surface_grey);

   if(button_type==59)
      button_type=57;

   if(button_type==57)   //check box tick mark
   {
    line(temp,3,7,5,9,0);   
    line(temp,3,6,5,8,0);   
    line(temp,3,5,6,8,0);   
    line(temp,6,6,9,3,0);   
    line(temp,6,7,9,4,0);
    line(temp,6,8,9,5,0);                      
   }


  if( button_type==1)   //Draws full button
   {
    rectfill(temp,2,2,w-2,h-2,colour.surface_grey);
    button_type=0;
   }

  if( button_type==10)   //makes the button pressed
   {
    blit(temp,buffer,0,0,0,0,w+1,h+1);
    blit(buffer,temp,3,3,4,4,w-5,h-5);
    button_type=5;
   }
  if( button_type==14)   //makes the small buttons pressed
   {
    blit(temp,buffer,0,0,0,0,w+1,h+1);
    blit(buffer,temp,2,2,3,3,w-5,h-5);    
    button_type=5;
   }
  if( button_type==15)   //makes the small buttons pressed
   {
    blit(temp,buffer,0,0,0,0,w+1,h+1);
    blit(buffer,temp,3,3,2,2,w-4,h-4);    
    button_type=0;
   }



  if( button_type==11)
   {
    blit(temp,buffer,0,0,0,0,w+1,h+1);
    blit(buffer,temp,4,4,3,3,w-5,h-5);
    button_type=0;
   }

  if( button_type==0)    //Draws button outline,used for buttons
   {
    line(temp,0,h,w,h,0);
    line(temp,w,h,w,0,0);
    line(temp,1,h-1,w-1,h-1,colour.dark_grey_boundry);
    line(temp,w-1,h-1,w-1,1,colour.dark_grey_boundry);
    line(temp,0,0,0,h-1,colour.white);
    line(temp,0,0,w-1,0,colour.white);
    line(temp,0+1,0+1,1,h-2,colour.light_grey_boundry);
    line(temp,0+1,0+1,w-2,0+1,colour.light_grey_boundry);
   }

  if( button_type==34)    //makes clicked scroll bar darker
  {
    rectfill(temp,2,2,w-2,h-2,colour.light_grey_boundry);
    button_type=31; 
  }
  if( button_type==30)    //Draws button for scroll bars
  {
    rectfill(temp,2,2,w-2,h-2,colour.surface_grey);
    button_type=31;  
  }
  if( button_type==31)    //Draws button for scroll bars
   {
    line(temp,0,h,w,h,0);
    line(temp,w,h,w,0,0);
    line(temp,1,h-1,w-1,h-1,colour.dark_grey_boundry);
    line(temp,w-1,h-1,w-1,1,colour.dark_grey_boundry);
    line(temp,0,0,0,h-1,colour.light_grey_boundry);
    line(temp,0,0,w-1,0,colour.light_grey_boundry);
    line(temp,0+1,0+1,1,h-2,colour.white);
    line(temp,0+1,0+1,w-2,0+1,colour.white);
   }
  if(button_type==32)         //scrll button pressed
  {
    rect(temp,0,0,w,h,colour.dark_grey_boundry);
    rect(temp,1,1,w-1,h-1,colour.surface_grey);
  }


  if(button_type==2)         //Menu bold
  {
    line(temp,0,h,w,h,colour.dark_grey_boundry);
    line(temp,w,h,w,0,colour.dark_grey_boundry);
    line(temp,0,0,0,h-1,colour.white);
    line(temp,0,0,w-1,0,colour.white);
   }
  if(button_type==3 || button_type==20)            //Menu selected
  {

    blit(temp,buffer,0,0,0,0,w+1,h+1);
    blit(buffer,temp,1,1,2,2,w-3,h-3);

    line(temp,0,h,w,h,colour.white);
    line(temp,w,h,w,0,colour.white);
    line(temp,0,0,0,h-1,colour.dark_grey_boundry);
    line(temp,0,0,w-1,0,colour.dark_grey_boundry);
    if(button_type==20)
       button_type=21;
   }

  if(button_type==4)             //Restore original formate
  {
//    rect(temp,2,2,w+2,h+2,colour.surface_grey);
    rect(temp,0,0,w,h,colour.surface_grey);
   }

   if(button_type==7|| button_type==22)             //Restore original formate
  {
    blit(temp,buffer,0,0,0,0,w+1,h+1);
    blit(buffer,temp,2,2,1,1,w-2,h-2);
    if(button_type==7)
  rect(temp,0,0,w,h,colour.surface_grey);
    else
     button_type=6;

   }

  if(button_type==5)         //my photo frame or button pressed
  {
    line(temp,0,h,w,h,colour.light_grey_boundry);
    line(temp,w,h,w,h-h,colour.light_grey_boundry);
    line(temp,1,h-1,w-1,h-1,colour.white);
    line(temp,w-1,h-1,w-1,1,colour.white);
    line(temp,0,0,0,h-1,0);
    line(temp,0,0,w-1,0,0);
    line(temp,1,1,1,h-2,colour.dark_grey_boundry);
    line(temp,1,1,w-2,1,colour.dark_grey_boundry);
  }
 if( button_type==6)    //buttons under the main_menu
   {
    line(temp,0,h,w,h,colour.dark_grey_boundry);
    line(temp,w,h,w,0,colour.dark_grey_boundry);
    line(temp,0,0,0,h-1,colour.white);
    line(temp,0,0,w-1,0,colour.white);

    line(temp,1,h-1,w-1,h-1,colour.dark_grey_boundry);
    line(temp,w-1,h-1,w-1,0,colour.dark_grey_boundry);
   }

 if( button_type==21)    //buttons under the main_menu to pressed
   {
//    line(temp,0,h,w,h,colour.white);
//   line(temp,w,h,w,0,colour.white);
//    line(temp,0,0,0,h-1,colour.dark_grey_boundry);
//    line(temp,0,0,w-1,0,colour.dark_grey_boundry);
//    line(temp,0,0,0,h-2,colour.dark_grey_boundry);
//    line(temp,0,0,w-2,0,colour.dark_grey_boundry);

    line(temp,1,h-1,w-1,h-1,colour.surface_grey);
    line(temp,w-1,h-1,w-1,0,colour.surface_grey);
   }

 if( button_type==100)    //the card placings
    {
    rectfill(temp,0,0,w,h,colour.bg_green_dark);
    line(temp,1,h,w,h,colour.bg_green_light);
    line(temp,w,1,w,h,colour.bg_green_light);
    line(temp,0,0,0,h,colour.black);
    line(temp,0,0,w-1,0,colour.black);
   }

 if( button_type==101)    //inverse of the 100
    {
    rectfill(temp,0,0,w,h,colour.bg_green_dark);
    line(temp,1,h,w,h,colour.black);
    line(temp,w,1,w,h,colour.black);
    line(temp,0,0,0,h,colour.bg_green_light);
    line(temp,0,0,w-1,0,colour.bg_green_light);
   }
   if(no_mouse==0)
     mouse_screen(bitmap,x1,y1,w+1,h+1);
     
   if(no_mouse==2)
 blit(temp,bitmap,0,0,x1,y1,w+1,h+1);

}




//===============================================================================================================
void draw_mouse()
{

int i,c;
if(mplayer.play==1)
{
  poll_music();
  get_curr_time();
  if(mplayer.Prun_sec!=mplayer.run_sec) 
   {
    display_curr_time();
    if(mpi[7].selected!=1)
    update_seeker_scroll();
   }
}  

mouse1.x=mouse_x;
mouse1.y=mouse_y;
mouse1.Fx=mouse1.x;
mouse1.Fy=mouse1.y;


if(flag.change_mouse>0)
{

  if(flag.change_mouse==1)
    {
    mouse1.x=mouse1.x-7;
    mouse1.y=mouse1.y-mouse1.h+1;
    if(mouse1.Fx<=change_mouse_area[0] || mouse1.Fx>=change_mouse_area[1] || mouse1.Fy<=change_mouse_area[2] || mouse1.Fy>=change_mouse_area[3])
     {


       blit(mouse_bg,dblbuffer,0,0,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
       blit(dblbuffer,screen,mouse1.px,mouse1.py,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
       flag.check_mouse=1;
       mouse1.h=20;
       mouse1.w=11;
       blit(data[XMOUSE].dat,mouse,0,0,0,0,mouse1.w,mouse1.h);
       set_mouse_sprite_focus(0,0);
       flag.change_mouse=0;
       flag.prob_click_events=0;
     }


    }
  if(flag.change_mouse==2)
    {
     mouse1.x=mouse1.x-4;
     if(mouse1.Fx<change_mouse_area[0] || mouse1.Fx>=change_mouse_area[1] || mouse1.Fy<=change_mouse_area[2] || mouse1.Fy>=change_mouse_area[3])
      {
        free_flag=0;
        for(i=1;i<(free_n+1);i++)
          {
            c=free_cell[i];

            if(mouse1.Fx>=freecell[c].x && mouse1.Fx<freecell[c].x+freecell[c].w && mouse1.Fy>freecell[c].y && mouse1.Fy<freecell[c].y+freecell[c].h)
             {
             change_mouse_area[0]=freecell[c].x;
             change_mouse_area[1]=freecell[c].x+freecell[c].w;
             change_mouse_area[2]=freecell[c].y;
             change_mouse_area[3]=freecell[c].y+freecell[c].h;
             global.cell_num=c;
             free_flag=1;
             }
           }
       if(free_flag==0)
        {
         blit(dblbuffer,mouse_bg,mouse1.px+9,mouse1.py,9,0,2,20);
         blit(dblbuffer,mouse_bg,mouse1.px,mouse1.py+19,0,19,11,1);
         mouse1.h=20;
         mouse1.w=11;
         blit(data[XMOUSE].dat,mouse,0,0,0,0,mouse1.w,mouse1.h);
         set_mouse_sprite_focus(0,0);
        flag.frees=1;
        flag.prob_click_events=0;
        flag.change_mouse=0;
         }
     }
   }

}

//if(first_time==1)
//{
// mouse1.px=mouse1.x;
// mouse1.py=mouse1.y;

// blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);
// masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
// blit(dblbuffer,screen,mouse1.x,mouse1.y,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
// first_time=0;
// }



   mouse1.changey=mouse1.y-mouse1.py;
   mouse1.changex=mouse1.x-mouse1.px;

//      mouseP_y=mouse1.py;
//      mouseP_x=mouse1.px;   
   

//rectfill(buffer,460,410,700,440,53484);
//textprintf_ex(buffer,font,460,410,9567,-1,"%d  %d %d %d",mouse1.ax[1],mouse1.ay[1],mouse1.ax[2],mouse1.ay[2]);
//blit(buffer,screen,460,410,460,410,240,30);
//rest(100);

if(global.mouse_active==1)
{
  if(mouse1.changey !=0 || mouse1.changex !=0)
  {

     blit(mouse_bg,dblbuffer,0,0,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
     blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
     masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);

           if(mouse1.changey>=0)
           {
               if(mouse1.changex>=0)
               {
                     if(mouse1.changey<mouse1.h && mouse1.changex<mouse1.w)
                        blit(dblbuffer,screen,mouse1.px,mouse1.py,mouse1.px,mouse1.py,(mouse1.x-mouse1.px)+mouse1.w,(mouse1.y-mouse1.py)+mouse1.h);
    
                     if(mouse1.changey>=mouse1.h || mouse1.changex>=mouse1.w)
                      {
                        blit(dblbuffer,screen,mouse1.x,mouse1.y,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                        blit(dblbuffer,screen,mouse1.px,mouse1.py,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
                      }
               }
         
               if(mouse1.changex<0)
               {
                     if(mouse1.changey<mouse1.h && -mouse1.changex<mouse1.w)
                        blit(dblbuffer,screen,mouse1.px+mouse1.changex,mouse1.py,mouse1.px+mouse1.changex,mouse1.py,(mouse1.px-mouse1.x)+mouse1.w,(mouse1.y-mouse1.py)+mouse1.h);
  
                     if(mouse1.changey>=mouse1.h || -mouse1.changex>=mouse1.w)
                      {
                        blit(dblbuffer,screen,mouse1.x,mouse1.y,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                        blit(dblbuffer,screen,mouse1.px,mouse1.py,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
                      }
               }    
           }

  
  
           if(mouse1.changey<0)
           {
               if(mouse1.changex>=0)
               {
                     if(-mouse1.changey<mouse1.h && mouse1.changex<mouse1.w)
                        blit(dblbuffer,screen,mouse1.px,mouse1.py+mouse1.changey,mouse1.px,mouse1.py+mouse1.changey,(mouse1.x-mouse1.px)+mouse1.w,(mouse1.py-mouse1.y)+mouse1.h);
              
                     if(-mouse1.changey>=mouse1.h || mouse1.changex>=mouse1.w)
                      {
                        blit(dblbuffer,screen,mouse1.x,mouse1.y,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                        blit(dblbuffer,screen,mouse1.px,mouse1.py,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
                      }
               }
         
               if(mouse1.changex<0)
               {
                     if(-mouse1.changey<mouse1.h && -mouse1.changex<mouse1.w)
                        blit(dblbuffer,screen,mouse1.x,mouse1.y,mouse1.x,mouse1.y,(mouse1.px-mouse1.x)+mouse1.w,(mouse1.py-mouse1.y)+mouse1.h);

                     if(-mouse1.changey>=mouse1.h || -mouse1.changex>=mouse1.w)
                      {
                        blit(dblbuffer,screen,mouse1.x,mouse1.y,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                        blit(dblbuffer,screen,mouse1.px,mouse1.py,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
                      }
               }
       
           }
         
  }

if(mouse1.px != mouse1.x)
 mouse1.px = mouse1.x;

if(mouse1.py != mouse1.y)
 mouse1.py = mouse1.y;    
  
}

}


//=========================================================================

void mouse_null(BITMAP *bitmap,int x,int y,int w,int h)
{
//  temp=create_bitmap(w,h);
  blit(bitmap,temp,x,y,0,0,w,h);
  blit(mouse_bg,temp,0,0,mouse1.x-x,mouse1.y-y,mouse1.w,mouse1.h);
}

void mouse_screen(BITMAP *bitmap,int x,int y,int w,int h)
{
 blit(temp,mouse_bg,mouse1.x-x,mouse1.y-y,0,0,w-(mouse1.x-x),h-(mouse1.y-y));
 masked_blit(mouse,temp,0,0,mouse1.x-x,mouse1.y-y,mouse1.w,mouse1.h);
 blit(temp,bitmap,0,0,x,y,w,h);
// destroy_bitmap(temp);
}
//======================================================================================================

void main_menu_selection()
{
 int h1,h2,h3;
 int w1,w2,w3;
 int xx1,xx2,xx3;  //just to make difference
 int yy1,yy2,yy3;
 int ak=20;   // just a temp variable
 int x;    //keep text x position away from menu
 int take_break=0;
 int i;

if(menuselected>0)
  {
          P_submenu=0;
          h1=27+7*ak;   
          w1=170;
          x=20;
          
          h2=13+4*ak;   
          w2=162;
          xx2=45;
          
          h3=6+global.num_xtra_submenu*ak;
          w3=206;
          xx3=88;

 if(settings.fullscreen==1 || settings.status_bar==1)
   {
    yy1=45;
    yy2=yy1;
    yy3=yy1;
    xx1=3;

    }
   else
    {
     yy1=18;
     yy2=yy1;
     yy3=yy1;
     xx1=0;
    }

   if(P_menu>=0)
   {

      if(P_menu==0)
      {

                for(i=402;i<=408;i++)
                 delete_form(i,-1);           
                P_submenu=0;
                 delete_form(502,-1);
                if(mouse1.x<=form[1].x+form[1].w)
                  blit(temp,mouse_bg,500,mouse1.y-yy1,xx1-mouse1.x,0,mouse1.x+mouse1.w-xx1,h1-(mouse1.y-yy1));
                if(mouse1.x>=xx1)
                  blit(temp,mouse_bg,mouse1.x+500-xx1,mouse1.y-yy1,0,0,mouse1.w,mouse1.h);

                blit(temp,dblbuffer,500,0,xx1,yy1,w1+1,h1+1);
                blit(dblbuffer,screen,xx1,yy1,xx1,yy1,w1+1,h1+1);
               }             

               if(P_menu==1)
               {
                   for(i=412;i<=415;i++)
                      delete_form(i,-1);           
                   P_submenu=0;
                   delete_form(503,-1);
                   if(mouse1.x<xx2 && mouse1.x+mouse1.w >xx2)
                      blit(temp,mouse_bg,500,mouse1.y-yy2,xx2-mouse1.x,0,mouse1.x+mouse1.w-xx2,h2-(mouse1.y-yy2));
                   if(mouse1.x>=xx2)
                      blit(temp,mouse_bg,mouse1.x+500-xx2,mouse1.y-yy2,0,0,mouse1.w,mouse1.h);
                   blit(temp,dblbuffer,500,0,xx2,yy2,w2+1,h2+1);
                   blit(dblbuffer,screen,xx2,yy2,xx2,yy2,w2+1,h2+1);
               }

               if(P_menu==2)
               {
//                   readkey();
                   for(i=422;i<422+global.num_xtra_submenu;i++)
                      delete_form(i,-1);           
                   P_submenu=0;
                   delete_form(504,-1);
                   if(mouse1.x<xx3 && mouse1.x+mouse1.w >xx3)
                      blit(temp,mouse_bg,500,mouse1.y-yy3,xx3-mouse1.x,0,mouse1.x+mouse1.w-xx3,h3-(mouse1.y-yy3));
                   if(mouse1.x>=xx3)
                      blit(temp,mouse_bg,mouse1.x+500-xx3,mouse1.y-yy3,0,0,mouse1.w,mouse1.h);
                   blit(temp,dblbuffer,500,0,xx3,yy3,w3+1,h3+1);
                   blit(dblbuffer,screen,xx3,yy3,xx3,yy3,w3+1,h3+1);
               }

         }





//******************
     if(menuselected==3)
       {
         form[fn].type=3;
         form[fn].card=61;    
         form[fn].w=w3;
         form[fn].h=h3;
         form[fn].x=xx3;
         form[fn].y=yy3;
         form[fn].selected=0;
         form[fn].rselected=0;
         form[fn].can_over=0;
         form[fn].n=504;
         activeform[active_number]=fn;
         active_number=active_number+1;
         //form[fn].Focus_y=FOCUS_Y;
         fn=fn+1;    
         for(i=0;i<global.num_xtra_submenu;i++)
         {
         form[fn].type=5;  //Special type for menu
         form[fn].card=61;    
         form[fn].w=196;
         form[fn].h=20;
         form[fn].x=xx3+6;         
         if(i==0)
           {
           form[fn].y=yy3+3;
           form[fn].can_over=1;
           }
         if(i==1)
           {
           form[fn].y=yy3+2+ak;
           form[fn].can_over=1;
           }
         form[fn].selected=0;
         form[fn].rselected=0;
         form[fn].overed=0;
         form[fn].n=422+i;
         activeform[active_number]=fn;
         active_number=active_number+1;
         //form[fn].Focus_y=FOCUS_Y;
         fn=fn+1;    

         }
          blit(dblbuffer,temp,xx3,yy3,500,0,w3+1,h3+1);
          blit(mouse_bg,temp,0,0,mouse1.x+500-xx3,mouse1.y-yy3,mouse1.w,mouse1.h);
          buttons_related(temp,xx3,yy3,xx3+w3,yy3+h3,501);
          i=4;
          if(global.colour_depth==2 && settings.background==1)
          {
          textprintf_ex(temp,data[XSANS].dat,x,4,0,-1,"%s",menus[2][1]);
          textprintf_ex(temp,data[XSANS].dat,184,4,0,-1,"%s","F8");
          line(temp,x-1,4+15,x+10,4+15,0);
          i=4+ak;
          }
          if(settings.mplayer==1)
          {
          textprintf_ex(temp,data[XSANS].dat,x,i,0,-1,"%s",menus[2][global.num_xtra_submenu]);
          textprintf_ex(temp,data[XSANS].dat,184,i,0,-1,"%s","F9");
          line(temp,x,i+15,x+8,i+15,0);
          }
        blit(temp,mouse_bg,mouse1.x-xx3,mouse1.y-yy3,0,0,w3+1-(mouse1.x-xx3),h3+1-(mouse1.y-yy3));
        masked_blit(mouse,temp,0,0,mouse1.x-xx3,mouse1.y-yy3,mouse1.w,mouse1.h);
        blit(temp,dblbuffer,0,0,xx3,yy3,w3+1,h3+1);
        blit(dblbuffer,screen,xx3,yy3,xx3,yy3,w3+1,h3+1);                      

       }
//******************
     if(menuselected==1)
       {
         form[fn].type=3;
         form[fn].card=61;    
         form[fn].w=w1;
         form[fn].h=h1;
         form[fn].x=xx1;
         form[fn].y=yy1;
         form[fn].selected=0;
         form[fn].rselected=0;
         form[fn].can_over=0;
         form[fn].n=502;
         activeform[active_number]=fn;
         active_number=active_number+1;
         //form[fn].Focus_y=FOCUS_Y;
         fn=fn+1;    

         for(i=0;i<7;i++)
         {
         form[fn].type=5;  //Special type for menu
         form[fn].card=61;    
         form[fn].w=158;
         form[fn].h=20;
         form[fn].x=xx1+6;         
         if(i==0)
           {
           form[fn].y=yy1+3;
           form[fn].can_over=1;
           }
         if(i==1)
           {
           form[fn].y=yy1+2+ak;
           form[fn].can_over=1;
           }
         if(i==2)
          {
           form[fn].y=yy1+2+2*ak;
             if(show_restart==1)
               form[fn].can_over=1;
              else
               form[fn].can_over=0;               
          }
         if(i==3)
          {
           form[fn].y=yy1+9+3*ak;
           form[fn].can_over=1;
           }    
         if(i==4)
          { 
           form[fn].y=yy1+9+4*ak;
           form[fn].can_over=1;
          }
         if(i==5)
           {
           form[fn].y=yy1+16+5*ak;
             if(show_undo==1)
               form[fn].can_over=1;
              else
               form[fn].can_over=0;               

           }
         if(i==6)
          {
           form[fn].y=yy1+23+6*ak;
           form[fn].can_over=1;
          }                


         form[fn].selected=0;
         form[fn].rselected=0;
         form[fn].overed=0;
         form[fn].n=402+i;
         activeform[active_number]=fn;
         active_number=active_number+1;
         //form[fn].Focus_y=FOCUS_Y;
         fn=fn+1;    
         }
       
          blit(dblbuffer,temp,xx1,yy1,500,0,w1+1,h1+1);
          blit(mouse_bg,temp,0,0,mouse1.x+500-xx1,mouse1.y-yy1,mouse1.w,mouse1.h);
          buttons_related(temp,xx1,yy1,xx1+w1,yy1+h1,501);
          textprintf_ex(temp,data[XSANS].dat,x,4,0,-1,"%s",menus[0][1]);
          textprintf_ex(temp,data[XSANS].dat,140,4,0,-1,"%s","F2");
          line(temp,x-1,4+15,x+10,4+15,0);
          
          textprintf_ex(temp,data[XSANS].dat,x,4+ak,0,-1,"%s",menus[0][2]);
          textprintf_ex(temp,data[XSANS].dat,140,4+ak,0,-1,"%s","F3");
          line(temp,x,4+ak+15,x+8,4+ak+15,0);

        if(show_restart==1)
        {
          textprintf_ex(temp,data[XSANS].dat,x,4+2*ak,0,-1,"%s",menus[0][3]);
          line(temp,x-1,4+2*ak+15,x+10,4+2*ak+15,0);
        }
        else
        {
         textprintf_ex(temp,data[XSANS].dat,x,4+2*ak,colour.dark_grey_boundry,-1,"%s",menus[0][3]);
         textprintf_ex(temp,data[XSANS].dat,x+1,4+1+2*ak,colour.white,-1,"%s",menus[0][3]);         
         line(temp,x-1,4+2*ak+15,x+10,4+2*ak+15,colour.dark_grey_boundry);
         line(temp,x-1+1,4+1+2*ak+15,x+1+10,4+1+2*ak+15,colour.white);         
        
        }
          
              
          line(temp,3,4+3*ak,166,4+3*ak,colour.dark_grey_boundry);
          line(temp,3,5+3*ak,166,5+3*ak,colour.white);
          
          textprintf_ex(temp,data[XSANS].dat,x,11+3*ak,0,-1,"%s",menus[0][4]);
          textprintf_ex(temp,data[XSANS].dat,140,11+3*ak,0,-1,"%s","F4");
          line(temp,x+8,11+3*ak+15,x+13,11+3*ak+15,0);
          textprintf_ex(temp,data[XSANS].dat,x,11+4*ak,0,-1,"%s",menus[0][5]);
          textprintf_ex(temp,data[XSANS].dat,140,11+4*ak,0,-1,"%s","F5");
          line(temp,x,11+4*ak+15,x+8,11+4*ak+15,0);

          line(temp,3,11+5*ak,166,11+5*ak,colour.dark_grey_boundry);
          line(temp,3,12+5*ak,166,12+5*ak,colour.white);
        
        
        if(show_undo==1)
        {
        textprintf_ex(temp,data[XSANS].dat,x,18+5*ak,0,-1,"%s",menus[0][6]);
        textprintf_ex(temp,data[XSANS].dat,140,18+5*ak,0,-1,"%s","F10");
        line(temp,x,18+5*ak+15,x+9,18+5*ak+15,0);
        }
        else
        {
         textprintf_ex(temp,data[XSANS].dat,x,18+5*ak,colour.dark_grey_boundry,-1,"%s",menus[0][6]);        
         textprintf_ex(temp,data[XSANS].dat,x+1,18+1+5*ak,colour.white,-1,"%s",menus[0][6]);                
        textprintf_ex(temp,data[XSANS].dat,140,18+5*ak,colour.dark_grey_boundry,-1,"%s","F10");
        textprintf_ex(temp,data[XSANS].dat,140+1,18+1+5*ak,colour.white,-1,"%s","F10");        
        line(temp,x,18+5*ak+15,x+9,18+5*ak+15,colour.dark_grey_boundry);
        line(temp,x+1,18+1+5*ak+15,x+1+9,18+1+5*ak+15,colour.white);        
        }

          line(temp,3,18+6*ak,166,18+6*ak,colour.dark_grey_boundry);
          line(temp,3,19+6*ak,166,19+6*ak,colour.white);
        
        textprintf_ex(temp,data[XSANS].dat,x,25+6*ak,0,-1,"%s",menus[0][7]);
        line(temp,x+9,25+6*ak+15,x+14,25+6*ak+15,0);
        
        
        //mouse_screen(BITMAP *bitmap,int x,int y,int w,int h)
        blit(temp,mouse_bg,mouse1.x-xx1,mouse1.y-yy1,0,0,w1+1-(mouse1.x-xx1),h1+1-(mouse1.y-yy1));
        masked_blit(mouse,temp,0,0,mouse1.x-xx1,mouse1.y-yy1,mouse1.w,mouse1.h);
        blit(temp,dblbuffer,0,0,xx1,yy1,w1+1,h1+1);
        blit(dblbuffer,screen,xx1,yy1,xx1,yy1,w1+1,h1+1);
      }    

      if(menuselected==2)
       {
         form[fn].type=3;
         form[fn].card=61;    
         form[fn].w=w2;
         form[fn].h=h2;
         form[fn].x=xx2;
         form[fn].y=yy2;
         form[fn].selected=0;
         form[fn].rselected=0;
         form[fn].can_over=0;
         form[fn].n=503;
         activeform[active_number]=fn;
         active_number=active_number+1;
         //form[fn].Focus_y=FOCUS_Y;
         fn=fn+1;  
           
           


       for(i=0;i<4;i++)
         {
         form[fn].type=5;  //Special type for menu
         form[fn].card=61;    
         form[fn].w=150;
         form[fn].h=20;
         form[fn].x=xx2+6;         
         if(i==0)
           form[fn].y=yy2+3;
         if(i==1)
           form[fn].y=yy2+9+ak;
         if(i==2)
           form[fn].y=yy2+9+2*ak;
         if(i==3)
           form[fn].y=yy2+9+3*ak;


         form[fn].selected=0;
         form[fn].rselected=0;
         form[fn].overed=0;
         form[fn].n=412+i;
         form[fn].can_over=1;         
         activeform[active_number]=fn;
         active_number=active_number+1;
         fn=fn+1;    
         }

         
          blit(dblbuffer,temp,xx2,yy2,500,0,w2+1,h2+1);
          blit(mouse_bg,temp,0,0,mouse1.x+500-xx2,mouse1.y-yy2,mouse1.w,mouse1.h);
          buttons_related(temp,xx2,yy2,xx2+w2,yy2+h2,501);
          textprintf_ex(temp,data[XSANS].dat,x,4,0,-1,"%s",menus[1][1]);
          textprintf_ex(temp,data[XSANS].dat,132,4,0,-1,"%s","F1");
          line(temp,x-1,4+15,x+10,4+15,0);   
          line(temp,3,4+ak,158,4+ak,colour.dark_grey_boundry);
          line(temp,3,5+ak,158,5+ak,colour.white);
         
          textprintf_ex(temp,data[XSANS].dat,x,11+ak,0,-1,"%s",menus[1][2]);
           line(temp,x,11+ak+15,x+9,11+ak+15,0);   
          textprintf_ex(temp,data[XSANS].dat,x,11+2*ak,0,-1,"%s",menus[1][3]);
           line(temp,x-1,11+2*ak+15,x+9,11+2*ak+15,0);   
          textprintf_ex(temp,data[XSANS].dat,x,11+3*ak,0,-1,"%s",menus[1][4]);
           line(temp,x+10,11+3*ak+15,x+16,11+3*ak+15,0);   
          
          
        blit(temp,mouse_bg,mouse1.x-xx2,mouse1.y-yy2,0,0,w2+1-(mouse1.x-xx2),h2+1-(mouse1.y-yy2));
        masked_blit(mouse,temp,0,0,mouse1.x-xx2,mouse1.y-yy2,mouse1.w,mouse1.h);
        blit(temp,dblbuffer,0,0,xx2,yy2,w2+1,h2+1);
        blit(dblbuffer,screen,xx2,yy2,xx2,yy2,w2+1,h2+1);                      
              
           }       
           
           
   menuselected=0;
  }
}

   
//=================================================================================================



void look_for_mouse_click(void)
{
  if(mouse_b & 1 && mouse_ready==1)
    {
     mouse1.pressed=1;
     mouse1.clicked=1;
    }

 if(mouse_b & 2 && mouse_rready==1)
    {
     mouse1.rpressed=1;
     mouse1.rclicked=1;
    }


}

void process_mouse_click(void)
{
  if(mouse1.released==1)
     mouse1.released=0;
   if(mouse1.clicked==1)
     {
     mouse1.clicked=0;
     mouse_ready=0;
     }
   if(mouse1.pressed==1 && !(mouse_b & 1))
      {
      mouse1.pressed=0;
      mouse1.released=1;
      mouse_ready=1;
      }


   if(mouse1.rreleased==1)
     mouse1.rreleased=0;
   if(mouse1.rclicked==1)
     {
     mouse1.rclicked=0;
     mouse_rready=0;
     }
   if(mouse1.rpressed==1 && !(mouse_b & 2))
      {
      mouse1.rpressed=0;
      mouse1.rreleased=1;
      mouse_rready=1;
      }

}

//=======================================================================
void time_disp()
{
   time(&t);
       time_str=ctime(&t);
       time_tmp[0]=(time_str[11]+2)%10;
       time_tmp[1]=(time_str[12]+2)%10;
       time_hr=time_tmp[0]*10+time_tmp[1];
       time_tmp[0]=(time_str[14]+2)%10;
       time_tmp[1]=(time_str[15]+2)%10;
       time_min=time_tmp[0]*10+time_tmp[1];
//   textprintf_ex(timetemp,font,0,0,154,-1,"%d %d %d",menu_focus_ok,item_selected2,menu_active_flag);
//   blit(timetemp,screen,0,0,200,560,150,18);
//   rectfill(timetemp,0,0,150,18,colour.white);


      if (time_hr>=12)
         {
          time_now[0]='P';
          time_now[1]='M';
          if(time_hr!=12)
          time_hr=time_hr-12;
         }
       else
         {
          if (time_hr==0)
             time_hr=12;
          time_now[0]='A';
          time_now[1]='M';
         }

      if (mouse_x>SCREEN_W-75 &&mouse_x<SCREEN_W-20 && mouse_y>SCREEN_H-24 &&mouse_y<SCREEN_H-6)
         {
          rectfill(timetemp,0,0,150,18,colour.white);
          rect(timetemp,0,0,149,17,0);
          if(time_check==1)
           {
            blit(dblbuffer,buffer,SCREEN_W-153,SCREEN_H-48,SCREEN_W-200,0,150,18);
            time_check=0;
           }
          textprintf_ex(timetemp,data[XSANS].dat,0,0,0,-1," %c%c%c %c%c%c %c%c %c%c%c%c %c%c",time_str[0],time_str[1],time_str[2],time_str[4],time_str[5],time_str[6],time_str[8],time_str[9],time_str[20],time_str[21],time_str[22],time_str[23],time_str[17],time_str[18]);
          if(global.dialog_active==0)
            {
             blit(timetemp,dblbuffer,0,0,SCREEN_W-153,SCREEN_H-48,150,18);
             blit(dblbuffer,screen,SCREEN_W-153,SCREEN_H-48,SCREEN_W-153,SCREEN_H-48,150,18);
            }
          time_out=0;
         }
       else if(time_out<2)
        time_out=1;

      if(time_min!=time_pmin)
       {
         rectfill(timetemp,0,0,55,14,colour.surface_grey);
         textprintf_ex(timetemp,data[XSANS].dat,0,0,0,-1,"%d:%.2d %c%c",time_hr,time_min,time_now[0],time_now[1]);
         if (mouse_x>SCREEN_W-75 && mouse_x<SCREEN_W-20 && mouse_y>SCREEN_H-46 && mouse_y<SCREEN_H-7)
           {
 blit(timetemp,mouse_bg,mouse1.x-(SCREEN_W-70),mouse1.y-(SCREEN_H-23),0,0,55-(mouse1.x-(SCREEN_W-70)),15-(mouse1.y-(SCREEN_H-23)) );
 masked_blit(mouse,timetemp,0,0,mouse1.x-(SCREEN_W-70),mouse1.y-(SCREEN_H-23),11,20);
 blit(timetemp,dblbuffer,0,0,(SCREEN_W-70),(SCREEN_H-23),55,15);
 blit(dblbuffer,screen,(SCREEN_W-70),(SCREEN_H-23),(SCREEN_W-70),(SCREEN_H-23),55,15);

           }
          else
            {
            blit(timetemp,dblbuffer,0,0,(SCREEN_W-70),(SCREEN_H-23),55,15);
            blit(dblbuffer,screen,(SCREEN_W-70),(SCREEN_H-23),(SCREEN_W-70),(SCREEN_H-23),55,15);
            }
            time_pmin=time_min;
       }
    if(time_out==1)
    {
    if(global.dialog_active==0)
      {
      blit(buffer,dblbuffer,SCREEN_W-200,0,SCREEN_W-153,SCREEN_H-48,150,18);
      blit(dblbuffer,screen,SCREEN_W-153,SCREEN_H-48,SCREEN_W-153,SCREEN_H-48,150,18);
      }
     time_check=0;
     time_out=2;
    }
}
//===================================================================================================

 void apply_transparent(BITMAP *bitmap,int type)
 {
  if (type==0)
   {
     line(bitmap,0,0,0,1,colour.transperent);
     line(bitmap,0,0,1,0,colour.transperent);
     line(bitmap,0,95,1,95,colour.transperent);
     line(bitmap,0,95,0,94,colour.transperent);
     line(bitmap,70,95,70,94,colour.transperent);
     line(bitmap,70,95,69,95,colour.transperent);
     line(bitmap,70,0,70,1,colour.transperent);
     line(bitmap,70,0,69,0,colour.transperent);
    }

  if (type==1)
   {
     line(bitmap,729,504,729,505,colour.transperent);
     line(bitmap,729,504,730,504,colour.transperent);
     line(bitmap,729,599,730,599,colour.transperent);
     line(bitmap,729,599,729,598,colour.transperent);
     line(bitmap,799,599,799,598,colour.transperent);
     line(bitmap,799,599,798,599,colour.transperent);
     line(bitmap,798,504,799,505,colour.transperent);
     line(bitmap,799,504,798,504,colour.transperent);
    }



}

 //=======================================================================================
 void add_transparent()
 {
 int i;
 for(i=0;i<70;i++)
   apply_transparent(data[i].dat,0);

 }


//======================================================================================
void alrand_deals(int gamenumber)
{
    int  i, j;                // generic counters
    int  col, pos;
    int  wLeft = 52;          // cards left to be chosen in shuffle
    int deck[52];            // deck of 52 unique cards
    for (col = 0; col < MAXCOL; col++)          // clear the deck
        for (pos = 0; pos < MAXPOS; pos++)
            card[col][pos] = 99;

    /* shuffle cards */

    for (i = 0; i < 52; i++)      // put unique card in each deck loc.
        deck[i] = i;

    alrand_srand(gamenumber);            // gamenumber is seed for rand()
    for (i = 0; i < 52; i++)
    {
        j = alrand_rand() % wLeft;
        card[(i%8)+1][i/8] = deck[j];
        deck[j] = deck[--wLeft];
    }

 }

//=================================================================================================

void ms_deals(int gamenumber)
{
    int  i, j;                // generic counters
    int  col, pos;
    int  wLeft = 52;          // cards left to be chosen in shuffle
    int deck[52];            // deck of 52 unique cards
    for (col = 0; col < MAXCOL; col++)          // clear the deck
        for (pos = 0; pos < MAXPOS; pos++)
            card[col][pos] = 99;

    /* shuffle cards */

    for (i = 0; i < 52; i++)      // put unique card in each deck loc.
        deck[i] = i;

    my_srand(gamenumber);            // gamenumber is seed for rand()
    for (i = 0; i < 52; i++)
    {
        j = my_rand() % wLeft;
        card[(i%8)+1][i/8] = deck[j];
        deck[j] = deck[--wLeft];
    }

 }

//======================================================================================================



void my_srand(long s)
{
  my_seed = s;
}

int my_rand()
{
  my_seed = my_seed*214013 + 2531011;
  return (my_seed>>16)&0x7FFF;
}

//=======================================================================================================



