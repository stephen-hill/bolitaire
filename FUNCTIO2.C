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
char chrs[34];
int kright=0;
int kleft=1; 
int do_animation;
                
void init_freecell()
{
  int i,j;
  int x,y;
  D_n=1;   //0 represents no choice to place the card at bottom
 
 global.rselected=0;
 global.cardselected=0;
 global.Fcardselected=0;
 global.show_game_select=0; 
 statistics.last_game_status=0;
 global.show_king=1;

 if(global.cheat==0)
 {
  statpack=pack_fopen("statistics.fyl",F_WRITE_PACKED);
  pack_fwrite(&statistics,sizeof(struct statistics),statpack);
  pack_fclose(statpack);
 }   


 flag.calc=0;
 flag.change_mouse=0;
 flag.check_mouse=0;
 flag.dnb_lclick=1; 

 free_n=0;
 cards_left=52;


 for(i=0;i<4;i++)
 {
 fillcell[i]=99;
 fillcolour[i]=99; 
 }

 draw_freecell();
  j=0;
 if(settings.fullscreen==1 || settings.status_bar==1)
    y=50;
   else
     y=23;

if(settings.fullscreen==1)
    x=69;
   else 
    x=4;

  if(settings.background!=1)
  {

    for(i=x;i<(x+69*4);i=i+72)
     {
      freecell[j].x=i;
      freecell[j].type=0;
      freecell[j].y=y;
      freecell[j].w=72;
      freecell[j].h=96;
      freecell[j].card_in=99;
      j=j+1;
     }
  
     if(settings.fullscreen==1)
      i=i+78;
     else
      i=i+65; 

     for(i;i<(x+69*9);i=i+72)
     {
       freecell[j].x=i;
       freecell[j].type=1;
       freecell[j].y=y;
       freecell[j].w=72;
       freecell[j].h=96;
       freecell[j].card_in=99;
       j=j+1;
     }
   }

  if(settings.background==1)
  {

    for(i=x;i<(x+69*4);i=i+73)
     {
      freecell[j].x=i-1;
      freecell[j].type=0;
      freecell[j].y=y-1;
      freecell[j].w=73;    //width has increased to make sure cursor dont change between that gap
      freecell[j].h=96;
      freecell[j].card_in=99;
      j=j+1;
     }
  
     if(settings.fullscreen==1)
      i=i+78;
     else
      i=i+57; 

     for(i;i<(x+69*9);i=i+73)
     {
       freecell[j].x=i;
       freecell[j].type=1;
       freecell[j].y=y-1;
       freecell[j].w=73;   //width has increased to make sure cursor dont change between that gap
       freecell[j].h=96;
       freecell[j].card_in=99;
       j=j+1;
     }
   }



}
//===================================================================================
void king_move()
{
 int x1,x2,y1,y2,kingx,kingy;

  if(settings.background!=1)
  {
     if(settings.fullscreen==1)
     {
       y1=50;
       y2=146;
       x1=356;
       x2=435;
       kingx=380;
       kingy=79;
     }
     else
     {
       y1=23;
       y2=119;
       x1=292;
       x2=345+12;
       kingx=309;
       kingy=52;
       if(settings.status_bar==1)
       { 
        y1=50;
        y2=146;
        kingy=79;
       }
     }
  }

  if(settings.background==1)
  {
     if(settings.fullscreen==1)
     {
       y1=49;
       y2=145;
       x1=359;
       x2=438;
       kingx=382;
       kingy=79;
     }
     else
     {
       y1=22;
       y2=118;
       x1=294;
       x2=341+12;
       kingx=308;
       kingy=52;
       if(settings.status_bar==1)
       { 
        y1=49;
        y2=145;
        kingy=79;
       }
     }
  }


 if(mouse1.Fy>y1 && mouse1.Fy <y2 &&mouse1.Fx <x1  && kright==1)
  {
     blit(background,dblbuffer,kingx,kingy,kingx,kingy,36,36);
     masked_blit(data[XKING_L].dat,dblbuffer,0,0,kingx,kingy,38,38);
     blit(dblbuffer,screen,kingx,kingy,kingx,kingy,36,36);
     kleft=1;
     kright=0;

  }
 if(mouse1.Fy>y1 && mouse1.Fy <y2 &&mouse1.Fx >x2 && kleft==1)
  {
     blit(background,dblbuffer,kingx,kingy,kingx,kingy,36,36);
     masked_blit(data[XKING_R].dat,dblbuffer,0,0,kingx,kingy,38,38);
     blit(dblbuffer,screen,kingx,kingy,kingx,kingy,36,36);
     kleft=0;
     kright=1;
  }



}

//===================================================================================

void place_cards()
{
  int placex,placey;
  int i,j;
 if(settings.fullscreen==1 || settings.status_bar==1)
      placey=30;
     else
      placey=3;      

blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);
    if(settings.ms_deal==1)
      textprintf_ex(dblbuffer,data[XSANS].dat,SCREEN_W-100,placey,0,-1,"%s%d","#MS ",game_number);
    if(settings.alrand_deal==1)
      textprintf_ex(dblbuffer,data[XSANS].dat,SCREEN_W-100,placey,0,-1,"%s%d","#AL ",game_number);

blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h);   //there is a chance of dirty mouse blit if mouse_x changes when reaching draw_mouse
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
blit(dblbuffer,screen,SCREEN_W-100,placey,SCREEN_W-100,placey,80,16);
if(settings.fullscreen==1)
  placex=80;
 else
  placex=12;  
  for(i=1;i<9;i++)
   {
    if(i<5)
     {
 if(settings.fullscreen==1 || settings.status_bar==1)
      placey=160;
     else
      placey=133;      
      for(j=0;j<7;j++)
       {
           form[fn].w=71;
           form[fn].h=96;
           form[fn].x=placex;
           form[fn].y=placey;
           form[fn].type=1;
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=2;
           form[fn].n=0;           
         form[fn].Focus_y=FOCUS_Y;
           if (j==6)
               {
               activeform[active_number]=fn;
               active_number=active_number+1;
               form[fn].topcard=1;
               }
           form[fn].card=card[i][j];
           fn=fn+1;
blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);

        if(global.cheat==2)
        masked_blit(data[52].dat,dblbuffer,0,0,placex,placey,71,96);
        else
        masked_blit(data[card[i][j]].dat,dblbuffer,0,0,placex,placey,71,96);
blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h);   //there is a chance of dirty mouse blit if mouse_x changes when reaching draw_mouse
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  

        blit(dblbuffer,screen,placex,placey,placex,placey,71,96);
        placey=placey+18;
       }
     }
    if(i>4)
     {
 if(settings.fullscreen==1 || settings.status_bar==1)
      placey=160;
     else
      placey=133;      
      for(j=0;j<6;j++)
       {
           form[fn].w=71;
           form[fn].h=96;
           form[fn].x=placex;
           form[fn].y=placey;
           form[fn].type=1;
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=2;
           form[fn].n=0;                      
           form[fn].Focus_y=FOCUS_Y;

blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);
           if(global.cheat==2)
           masked_blit(data[52].dat,dblbuffer,0,0,placex,placey,71,96);
           else
           masked_blit(data[card[i][j]].dat,dblbuffer,0,0,placex,placey,71,96);
blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h);   //there is a chance of dirty mouse blit if mouse_x changes when reaching draw_mouse
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
           blit(dblbuffer,screen,placex,placey,placex,placey,71,96);
            if (j==5)
               {
               activeform[active_number]=fn;
               active_number=active_number+1;
//             form[fn].h=96+(18*5);
               form[fn].topcard=1;
               }
               form[fn].card=card[i][j];
           fn=fn+1;
        placey=placey+18;
       }
     }
if(settings.fullscreen==1)
  placex=placex+71+9;
 else
  placex=placex+71+8;
  }





}

//====================================================================================

void invert_card_color(BITMAP *bitmap)
{
 int i,j;
 int color;
 int r,g,b;
 int touch[3]={0,0,0};  //if black true
rectfill(buffer,729,503-mouse1.h,800,503,colour.transperent);
 for(i=0;i<71;i++)
   {
    for(j=0;j<96;j++)
     {
      color=getpixel(bitmap,i,j);
            if(global.colour_depth==1)
      {
        r=getr8(color);
        g=getg8(color);
        b=getb8(color);
       } 
      if(global.colour_depth==2)
      {
        r=getr24(color);
        g=getg24(color);
        b=getb24(color);
       } 

      if(r==255 && g==255 && b==0)     //yellow
         touch[0]=1;
      if(r==255 && g==0 && b==0)       //red
         touch[1]=1;
      if(r==0 && g==0 && b==0)         //black
         touch[2]=1;


      putpixel(buffer,729+i,504+j,makecol(255-r,255-g,255-b));
          }
   }

 if(touch[0]==0 && touch[1]==1)
 {
 for(i=0;i<71;i++)
   {
    for(j=0;j<96;j++)
     {
      color=getpixel(buffer,729+i,504+j);
      if(global.colour_depth==1)
      {
        r=getr8(color);
        g=getg8(color);
        b=getb8(color);
       } 
      if(global.colour_depth==2)
      {
        r=getr24(color);
        g=getg24(color);
        b=getb24(color);
       } 

      if(r==255 && g==255 && b==255)
      putpixel(buffer,729+i,504+j,makecol(0,255,255));
     }
   }
  }

else if(touch[0]==0 && touch[2]==1)
 {
 for(i=0;i<71;i++)
   {
    for(j=0;j<96;j++)
     {
      color=getpixel(buffer,729+i,504+j);
      if(global.colour_depth==1)
      {
        r=getr8(color);
        g=getg8(color);
        b=getb8(color);
       } 
      if(global.colour_depth==2)
      {
        r=getr24(color);
        g=getg24(color);
        b=getb24(color);
       } 

      if(r==0 && g==0 && b==0)
      putpixel(buffer,729+i,504+j,makecol(0,255,255));
     }
   }
  }
apply_transparent(buffer,1);

}

//=============================================================================================
void mouse_released_events()
{
  char s[3]; //this is used to change drives
  int i,j;
  int x;  //to find time of a song
        if(form[global.exit_fn].selected==1)
          {
           if(mouse1.Fx<form[global.exit_fn].x || mouse1.Fx>form[global.exit_fn].x+form[global.exit_fn].w || mouse1.Fy<form[global.exit_fn].y || mouse1.Fy>form[global.exit_fn].y+form[global.exit_fn].h)
           {
             buttons_related(dblbuffer,SCREEN_W-27,6,SCREEN_W-7,24,11);
             blit(dblbuffer,screen,SCREEN_W-27,6,SCREEN_W-27,6,21,19);
             form[global.exit_fn].selected=0;
           }
          else
           {
             buttons_related(dblbuffer,SCREEN_W-27,6,SCREEN_W-7,24,11);
             blit(dblbuffer,screen,SCREEN_W-27,6,SCREEN_W-27,6,21,19);
             form[global.exit_fn].selected=0;
             if(cards_left==0)
               EXIT_PROGRAM=1;
             if(cards_left!=0)
               {
                 menu_select_F=1;
                 menus_flag[0][0]=1;
                 global.exit_program=1;
               }
          }
         }

  if(dialog_fn>0)
   {

     if(browser.ampobe==1)
      {
       for(i=fn-1;i>=dialog_fn;i--)
        {
         if(form[i].selected==1 && form[i].type==21)
           {
             form[i].selected=0;
             buttons_related(dblbuffer,form[i].x,form[i].y,form[i].x+form[i].w,form[i].y+form[i].h,11);  
             blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
             if(mouse1.Fx>form[i].x && mouse1.Fx<form[i].x+form[i].w && mouse1.Fy>form[i].y && mouse1.Fy<form[i].y+form[i].h)
              {                    
                if(form[i].n==41)  //selectin cwd
                {
                     for(j=0;j<browser.file_n;j++)
                      {

                         strcpy(playlist[mplayer.media_n].s,curr_dir);
                         strcat(playlist[mplayer.media_n].s,"\\");
                         strcat(playlist[mplayer.media_n].s,file[j].name);
                         strcpy(playlist[mplayer.media_n].name,file[j].name); //chance of over flow
                         playlist[mplayer.media_n].size_bytes=file[j].size;
                         get_song_length(file[j].size);
                         playlist[mplayer.media_n].selected=0;
                         if(playlist[mplayer.media_n].min!=0 || playlist[mplayer.media_n].sec !=0)
                           mplayer.media_n=mplayer.media_n+1;
                      }

                    remove_dialog();                                         
                 if(cards_left!=0)
                   global.show_game_select=0;  
                 if(cards_left==0)
                   global.show_game_select=1;  
                 init_pl_scroll_bars();
                 update_pl_scroll(mplayer.first_pl_n,1);

                  break;

                }

               if(form[i].n==42)  //selectin dir
                {
                     directory[browser.dir_selected].selected=0; //this is to avoid blitting of this folder when next browser opens
                     chdir(directory[browser.dir_selected].name);
                     initialize_dir_file();
                     getcwd(curr_dir,256);
                     for(j=0;j<browser.file_n;j++)
                      {
                         strcpy(playlist[mplayer.media_n].s,curr_dir);
                         strcat(playlist[mplayer.media_n].s,"\\");
                         strcat(playlist[mplayer.media_n].s,file[j].name);
                         strcpy(playlist[mplayer.media_n].name,file[j].name); //chance of over flow
                         playlist[mplayer.media_n].size_bytes=file[j].size;
                         get_song_length(file[j].size);
                         playlist[mplayer.media_n].selected=0;
                         if(playlist[mplayer.media_n].min!=0 || playlist[mplayer.media_n].sec !=0)
                           mplayer.media_n=mplayer.media_n+1;
                      }
                
                    remove_dialog();                                         
                 if(cards_left!=0)
                   global.show_game_select=0;  
                 if(cards_left==0)
                   global.show_game_select=1;  

                 init_pl_scroll_bars();
                 update_pl_scroll(mplayer.first_pl_n,1);
                 break;

                }

               if(form[i].n==43)  //selectin file
                {
                   if(browser.mode==1)
                   {
                     for(j=0;j<browser.file_n;j++)
                      {
                       if(file[j].selected==1)
                        {
                         file[j].selected=0;
                         strcpy(playlist[mplayer.media_n].s,curr_dir);
                         strcat(playlist[mplayer.media_n].s,"\\");
                         strcat(playlist[mplayer.media_n].s,file[j].name);
                         strcpy(playlist[mplayer.media_n].name,file[j].name); //chance of over flow
                         playlist[mplayer.media_n].size_bytes=file[j].size;
                         get_song_length(file[j].size);
                         playlist[mplayer.media_n].selected=0;
                         if(playlist[mplayer.media_n].min!=0 || playlist[mplayer.media_n].sec !=0)
                           mplayer.media_n=mplayer.media_n+1;
                        }

                      }
//                      for(i=mplayer.media_n-1;i>=0;i--)
//                              textprintf_ex(screen,font,10,10+i*16,46,-1,"%s",playlist[i].s);
//                          readkey();
                    remove_dialog();                                         
                 if(cards_left!=0)
                   global.show_game_select=0;  
                 if(cards_left==0)
                   global.show_game_select=1;  
                 init_pl_scroll_bars();
                 update_pl_scroll(mplayer.first_pl_n,1);

                  break;
                   }
                   else
                   {
                   global.redraw_screen=1;                   
                 remove_dialog();                                         
                 if(cards_left!=0)
                   global.show_game_select=0;  
                 if(cards_left==0)
                   global.show_game_select=1;  
                   
                   }
                   

                
                }


                if(form[i].n>60)   //for drive buttons
                 {
                  s[0]=form[i].n;
                  s[1]=':';
                  s[2]='/';
                     chdir(s);                  
                     getcwd(curr_dir,256);
                     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
                     rectfill(form1,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y-form[dialog_fn].y,form[browser.up_fn].x+572-form[dialog_fn].x,form[browser.up_fn].y+form[browser.up_fn].h-form[dialog_fn].y,colour.dark_grey_boundry);
                     textprintf_ex(form1,data[XSANS2].dat,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y+3-form[dialog_fn].y,colour.white,-1,"%s",curr_dir);
                     blit(form1,dblbuffer,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y-form[dialog_fn].y,form[browser.up_fn].x+76,form[browser.up_fn].y,496,form[browser.up_fn].h);
                     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
                     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  

                     blit(dblbuffer,screen,form[browser.up_fn].x+76,form[browser.up_fn].y,form[browser.up_fn].x+76,form[browser.up_fn].y,496,form[browser.up_fn].h);

                     for(j=0;j<browser.file_n;j++)
                        file[j].selected=0;                     
                     directory[browser.dir_selected].selected=0;
                     initialize_dir_file();
                     init_scroll_bars();
                     update_file_scroll(0,1);
                     update_dir_scroll(0,1);                     
                 
                 }


                if(browser.up_fn==i)
                 {
                     chdir("..");
    getcwd(curr_dir,250);
    rectfill(form1,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y-form[dialog_fn].y,form[browser.up_fn].x+572-form[dialog_fn].x,form[browser.up_fn].y+form[browser.up_fn].h-form[dialog_fn].y,colour.dark_grey_boundry);
    textprintf_ex(form1,data[XSANS2].dat,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y+3-form[dialog_fn].y,colour.white,-1,"%s",curr_dir);
    blit(form1,dblbuffer,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y-form[dialog_fn].y,form[browser.up_fn].x+76,form[browser.up_fn].y,496,form[browser.up_fn].h);
    blit(dblbuffer,screen,form[browser.up_fn].x+76,form[browser.up_fn].y,form[browser.up_fn].x+76,form[browser.up_fn].y,496,form[browser.up_fn].h);

                     for(j=0;j<browser.file_n;j++)
                        file[j].selected=0;                     
                     directory[browser.dir_selected].selected=0;
                     initialize_dir_file();
                     init_scroll_bars();
                     update_file_scroll(0,1);
                     update_dir_scroll(0,1);                     
                 }
              }
           }

         if(form[i].selected==1 && form[i].type==22)
           {
             form[i].selected=0;
             buttons_related(dblbuffer,form[i].x,form[i].y,form[i].x+form[i].w,form[i].y+form[i].h,31);  
             blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
           }

             if(form[i].selected==1 && form[i].type==24)
              {
               form[i].selected=0;
               buttons_related(form1,form[i].x-form[dialog_fn].x,form[i].y-form[dialog_fn].y,form[i].x+form[i].w-form[dialog_fn].x,form[i].y+form[i].h-form[dialog_fn].y,630);           
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
               blit(form1,dblbuffer,form[i].x-form[dialog_fn].x,form[i].y-form[dialog_fn].y,form[i].x,form[i].y,form[i].w,form[i].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
               blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                 
              }




        }




      }


    if(global.menu_selected==5)    //Options
       {


      if(form[dialog_fn+6].selected==1)
        {
          form[dialog_fn+6].selected=0;
          if(mouse1.Fx>form[dialog_fn+6].x && mouse1.Fx<form[dialog_fn+6].x+form[dialog_fn+6].w && mouse1.Fy>form[dialog_fn+6].y && mouse1.Fy<form[dialog_fn+6].y+form[dialog_fn+6].h)
            {
              if(settings.background==0)
               {
              buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15+12,form[dialog_fn].y+116+12,56);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15,form[dialog_fn].y+116,12,12);
              buttons_related(form1,15,116,27,128,656); 
                 settings.background=1;
               }
             else
                {
                 buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15+12,form[dialog_fn].y+116+12,57);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15,form[dialog_fn].y+116,12,12);
                 buttons_related(form1,15,116,27,128,657); 
                 settings.background=0;

                } 
            }
           else
            {
              if(settings.background==0)
                {
              buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15+12,form[dialog_fn].y+116+12,57);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15,form[dialog_fn].y+116,12,12);
              buttons_related(form1,15,116,27,128,657); 
                 
                }
              if(settings.background==1)
                {
                 buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15+12,form[dialog_fn].y+116+12,56);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15,form[dialog_fn].y+116,12,12);
              buttons_related(form1,15,116,27,128,656); 
                } 
            }
        }          



      if(form[dialog_fn+4].selected==1)
        {
          form[dialog_fn+4].selected=0;
          if(mouse1.Fx>form[dialog_fn+4].x && mouse1.Fx<form[dialog_fn+4].x+form[dialog_fn+4].w && mouse1.Fy>form[dialog_fn+4].y && mouse1.Fy<form[dialog_fn+4].y+form[dialog_fn+4].h)
            {
              if(settings.animation==1)
                {
              buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15+12,form[dialog_fn].y+96+12,56);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15,form[dialog_fn].y+96,12,12);
              buttons_related(form1,15,96,27,108,656); 
                 settings.animation=0;
                 
                }
               else
                {
                 buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15+12,form[dialog_fn].y+96+12,57);  
                 blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15,form[dialog_fn].y+96,12,12);
                 buttons_related(form1,15,96,27,108,657); 
                 settings.animation=1;
                } 
              set_config_int( "settings", "animation", settings.animation);
            }
           else
            {
              if(settings.animation==1)
                {
              buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15+12,form[dialog_fn].y+96+12,57);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15,form[dialog_fn].y+96,12,12);
              buttons_related(form1,15,96,27,108,657); 
                 
                }
              if(settings.animation==0)
                {
                 buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15+12,form[dialog_fn].y+96+12,56);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15,form[dialog_fn].y+96,12,12);
              buttons_related(form1,15,96,27,108,656); 
                } 
            }
        }          

       if(form[dialog_fn+2].selected==1)
          {
          form[dialog_fn+2].selected=0;
          if(mouse1.Fx>form[dialog_fn+2].x && mouse1.Fx<form[dialog_fn+2].x+form[dialog_fn+2].w && mouse1.Fy>form[dialog_fn+2].y && mouse1.Fy<form[dialog_fn+2].y+form[dialog_fn+2].h)
            {
              buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+64,form[dialog_fn].x+15+12,form[dialog_fn].y+64+12,55);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+64,form[dialog_fn].x+15,form[dialog_fn].y+64,12,12);
              buttons_related(form1,15,64,27,76,655);  
              buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+38,form[dialog_fn].x+15+12,form[dialog_fn].y+38+12,54);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+38,form[dialog_fn].x+15,form[dialog_fn].y+38,12,12);
              buttons_related(form1,15,38,27,50,654);  
              settings.ms_deal=1;
              settings.alrand_deal=0;
              set_config_int( "settings", "ms_deal", settings.ms_deal);
              set_config_int( "settings", "alrand_deal", settings.alrand_deal);              
            }
          else
           {
            buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+38,form[dialog_fn].x+15+12,form[dialog_fn].y+38+12,55);                          
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+38,form[dialog_fn].x+15,form[dialog_fn].y+38,12,12);
           }
          }
        if(form[dialog_fn+3].selected==1)
          {
              form[dialog_fn+3].selected=0;
          if(mouse1.Fx>form[dialog_fn+3].x && mouse1.Fx<form[dialog_fn+3].x+form[dialog_fn+2].w && mouse1.Fy>form[dialog_fn+3].y && mouse1.Fy<form[dialog_fn+3].y+form[dialog_fn+3].h)
           {
              buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+38,form[dialog_fn].x+15+12,form[dialog_fn].y+38+12,55);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+38,form[dialog_fn].x+15,form[dialog_fn].y+38,12,12);
              buttons_related(form1,15,38,27,50,655);  
              buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+64,form[dialog_fn].x+15+12,form[dialog_fn].y+64+12,54);  
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+64,form[dialog_fn].x+15,form[dialog_fn].y+64,12,12);
              buttons_related(form1,15,64,27,76,654);  
              settings.ms_deal=0;
              settings.alrand_deal=1;
              set_config_int( "settings", "ms_deal", settings.ms_deal);
              set_config_int( "settings", "alrand_deal", settings.alrand_deal);              
           }
         else
           {
            buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+64,form[dialog_fn].x+15+12,form[dialog_fn].y+64+12,55);              
              blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+64,form[dialog_fn].x+15,form[dialog_fn].y+64,12,12);
           }
          }
       }


  if(global.menu_selected==4)      // statistics
     {
       if(form[dialog_fn+2].selected==1)
        {
          buttons_related(dblbuffer,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].x+form[dialog_fn+2].w,form[dialog_fn+2].y+form[dialog_fn+2].h,11);      
          blit(dblbuffer,screen,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].w+1,form[dialog_fn+2].h+1);      
          form[dialog_fn+2].selected=0;
          if(mouse1.Fx>form[dialog_fn+2].x && mouse1.Fx<form[dialog_fn+2].x+form[dialog_fn+2].w && mouse1.Fy>form[dialog_fn+2].y && mouse1.Fy<form[dialog_fn+2].y+form[dialog_fn+2].h)
             {
               remove_dialog();
             if(cards_left!=0)
               global.show_game_select=0;  
             }
        }
     }
  if(global.menu_selected==2)      // Select game Dialog
     {
    if(form[dialog_fn+2].selected==1)
    {
       buttons_related(dblbuffer,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].x+form[dialog_fn+2].w,form[dialog_fn+2].y+form[dialog_fn+2].h,11);      
          blit(dblbuffer,screen,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].w+1,form[dialog_fn+2].h+1);      
       form[dialog_fn+2].selected=0;
       if(mouse1.Fx>form[dialog_fn+2].x && mouse1.Fx<form[dialog_fn+2].x+form[dialog_fn+2].w && mouse1.Fy>form[dialog_fn+2].y && mouse1.Fy<form[dialog_fn+2].y+form[dialog_fn+2].h)
         {
            remove_dialog();
           if(get_game_number>0)
             {
              init_screen(0);
              init_freecell();
                    if(settings.ms_deal==1)
                      ms_deals(get_game_number);
                    if(settings.alrand_deal==1)
                      alrand_deals(get_game_number);
              global.show_game_select=0;
              game_number=get_game_number;
              place_cards();
             }

          if(get_game_number<=0 && cards_left==0)
              global.show_game_select=1;
 
         }

    }

       if(form[dialog_fn+3].selected==1)
        {
          buttons_related(dblbuffer,form[dialog_fn+3].x,form[dialog_fn+3].y,form[dialog_fn+3].x+form[dialog_fn+3].w,form[dialog_fn+3].y+form[dialog_fn+3].h,11);      
          blit(dblbuffer,screen,form[dialog_fn+3].x,form[dialog_fn+3].y,form[dialog_fn+3].x,form[dialog_fn+3].y,form[dialog_fn+3].w+1,form[dialog_fn+3].h+1);      
          form[dialog_fn+3].selected=0;
            if(mouse1.Fx>form[dialog_fn+3].x && mouse1.Fx<form[dialog_fn+3].x+form[dialog_fn+3].w && mouse1.Fy>form[dialog_fn+3].y && mouse1.Fy<form[dialog_fn+3].y+form[dialog_fn+3].h)
              {
               remove_dialog();
                 if(cards_left!=0)
                   global.show_game_select=0;  
                 if(cards_left==0)
                   global.show_game_select=1;  

              }
         }
 
     }

   if(global.menu_selected==1)      // New game Dialog
     {
   if(form[dialog_fn+2].selected==1)
    {
       buttons_related(dblbuffer,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].x+form[dialog_fn+2].w,form[dialog_fn+2].y+form[dialog_fn+2].h,11);      
          blit(dblbuffer,screen,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].x,form[dialog_fn+2].y,form[dialog_fn+2].w+1,form[dialog_fn+2].h+1);      
       form[dialog_fn+2].selected=0;
       if(mouse1.Fx>form[dialog_fn+2].x && mouse1.Fx<form[dialog_fn+2].x+form[dialog_fn+2].w && mouse1.Fy>form[dialog_fn+2].y && mouse1.Fy<form[dialog_fn+2].y+form[dialog_fn+2].h)
        {
         remove_dialog();    
         if(cards_left>0)
           if(global.cheat==0)
            do_statistics();

               if(global.show_game_select!=2 && global.exit_program==0)
                 {
                    init_screen(0);
                    init_freecell();
                     if(global.restart_same_game==0)
                       game_number=rand()%32000;
                    global.restart_same_game=0;
                    if(settings.ms_deal==1)
                      ms_deals(game_number);
                    if(settings.alrand_deal==1)
                      alrand_deals(game_number);
                    place_cards();
                  }
               if(global.exit_program==1)
                    EXIT_PROGRAM=1;
                
               if(global.show_game_select==2)
                 {
                  menu_select_F=1;
                  global.show_game_select=1;
                  menus_flag[0][1]=1;
                 }
         }

    }
   if(form[dialog_fn+3].selected==1)
    {
      buttons_related(dblbuffer,form[dialog_fn+3].x,form[dialog_fn+3].y,form[dialog_fn+3].x+form[dialog_fn+3].w,form[dialog_fn+3].y+form[dialog_fn+3].h,11);      
          blit(dblbuffer,screen,form[dialog_fn+3].x,form[dialog_fn+3].y,form[dialog_fn+3].x,form[dialog_fn+3].y,form[dialog_fn+3].w+1,form[dialog_fn+3].h+1);      
    form[dialog_fn+3].selected=0;
       if(mouse1.Fx>form[dialog_fn+3].x && mouse1.Fx<form[dialog_fn+3].x+form[dialog_fn+3].w && mouse1.Fy>form[dialog_fn+3].y && mouse1.Fy<form[dialog_fn+3].y+form[dialog_fn+3].h)
           {
              remove_dialog();
              if(cards_left!=0)
                global.show_game_select=0;  
            }

         }
      }

   if(form[dialog_fn+1].selected==1)
     {
        buttons_related(dblbuffer,form[dialog_fn+1].x,form[dialog_fn+1].y,form[dialog_fn+1].x+form[dialog_fn+1].w,form[dialog_fn+1].y+form[dialog_fn+1].h,15);       
          blit(dblbuffer,screen,form[dialog_fn+1].x,form[dialog_fn+1].y,form[dialog_fn+1].x,form[dialog_fn+1].y,form[dialog_fn+1].w+1,form[dialog_fn+1].h+1);      
        form[dialog_fn+1].selected=0;   
        if(mouse1.Fx>form[dialog_fn+1].x && mouse1.Fx<form[dialog_fn+1].x+form[dialog_fn+1].w && mouse1.Fy>form[dialog_fn+1].y && mouse1.Fy<form[dialog_fn+1].y+form[dialog_fn+1].h)
           {
            remove_dialog();
                 if(cards_left!=0)
                   global.show_game_select=0;  
                 if(cards_left==0)
                   global.show_game_select=1;  
           }
      }
    if(form[dialog_fn].selected==1)
     {
     form[dialog_fn].selected=0;
       global.mouse_active=1;
     }   
   }

}


//============================================================================================
void mouse_click_events()
{
  int z,j,k,l,m,n;
  int z2;
  int i,c,d;
  int temp1,temp2,tmp_compt;
  int tmp_prev_pos[2];
  int temps;
  int r_n,r_n1,r_n2; //replace number
  int r_n1high;  //to get thighest value of r_n1
  int sweep_freecell;
  int loop_sweep;
  int place_freecell;
  int take_action=1;
  do_animation=0;
  sweep_freecell=0;       
  loop_sweep=1;
  place_freecell=1;

  if(dialog_fn>0)
   { 
       for(i=fn-1;i>=dialog_fn;i--)
        {
         if(mouse1.Fx>form[i].x && mouse1.Fx<form[i].x+form[i].w && mouse1.Fy>form[i].y && mouse1.Fy<form[i].y+form[i].h)
           {

             if(form[i].type==24)
              {
               form[i].selected=1;
//               buttons_related(dblbuffer,form[i].x,form[i].y,form[i].x+form[i].w,form[i].y+form[i].h,34);  
//               blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                 
              }


             if(form[i].type==22)
              {
               form[i].selected=1;
               buttons_related(dblbuffer,form[i].x,form[i].y,form[i].x+form[i].w,form[i].y+form[i].h,32);  
               blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);

               if(form[i].n==54 && browser.first_dir_n+browser.contain_dir<browser.dir_n)
                   update_dir_scroll(browser.first_dir_n+1,1);
               if(form[i].n==53 && browser.first_dir_n!=0)
                   update_dir_scroll(browser.first_dir_n-1,1);

               if(form[i].n==52 && browser.first_file_n+browser.contain_file<browser.file_n)
                   update_file_scroll(browser.first_file_n+1,1);
               if(form[i].n==51 && browser.first_file_n!=0)
                   update_file_scroll(browser.first_file_n-1,1);
                 
              }

             if(form[i].type==21)
              {
               form[i].selected=1;
               buttons_related(dblbuffer,form[i].x,form[i].y,form[i].x+form[i].w,form[i].y+form[i].h,10);  
               blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
//                textprintf_ex(screen,font,100,100,2000,-1,"%d %d",dialog_fn,i); 
//                readkey();
              }


             if(form[i].type==32 && (browser.first_dir_n+i-browser.first_dir_fn<browser.dir_n) )
              {
               if(form[i].selected==0)
                 {
                     for(j=0;j<34;j++)
                       chrs[j]=directory[browser.first_dir_n+i-browser.first_dir_fn].name[j];
                     chrs[j]='\0';  

                    directory[browser.first_dir_n+i-browser.first_dir_fn].selected=1;
                    form[i].selected=1;
                    rectfill(form1,form[i].x-form[dialog_fn].x,form[i].y+1-form[dialog_fn].y,form[i].x+form[i].w-form[dialog_fn].x,form[i].y+form[i].h-form[dialog_fn].y-2,colour.item_selected);  
                    textprintf_ex(form1,data[XSANS2].dat,form[i].x+2-form[dialog_fn].x,form[i].y+2-form[dialog_fn].y,colour.white,-1,"%s",chrs);
                    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
                    blit(form1,dblbuffer,form[i].x-form[dialog_fn].x,form[i].y-form[dialog_fn].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
                    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
                    blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);

                           if(browser.dir_selected!=-1)
                            {
                              n=browser.first_dir_fn;
                              temp2=0;
                              for(m=browser.first_dir_n;m<browser.first_dir_n+browser.contain_dir;m++)
                              {
                                if(browser.dir_selected==m)
                                {
                                    for(j=0;j<34;j++)
                                     chrs[j]=directory[browser.first_dir_n+n-browser.first_dir_fn].name[j];
                                    chrs[j]='\0';  
                                    directory[m].selected=0;
                                    form[n].selected=0;
                                    rectfill(form1,form[n].x-form[dialog_fn].x,form[n].y+1-form[dialog_fn].y,form[n].x+form[n].w-form[dialog_fn].x,form[n].y+form[n].h-form[dialog_fn].y-2,colour.white);  
                                    textprintf_ex(form1,data[XSANS2].dat,form[n].x+2-form[dialog_fn].x,form[n].y+2-form[dialog_fn].y,colour.black,-1,"%s",chrs);
                                    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
                                    blit(form1,dblbuffer,form[n].x-form[dialog_fn].x,form[n].y-form[dialog_fn].y,form[n].x,form[n].y,form[n].w+1,form[n].h+1);
                                    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
                                    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
                                    blit(dblbuffer,screen,form[n].x,form[n].y,form[n].x,form[n].y,form[n].w+1,form[n].h+1);
                                    temp2=1;
                                    break;
                                }
                                n=n+1;
                             }
                             if(temp2==0)
                               directory[browser.dir_selected].selected=0;
                           }
                           browser.dir_selected=browser.first_dir_n+i-browser.first_dir_fn;
                  }
                 else
                  {
                     for(j=0;j<browser.file_n;j++)
                        file[j].selected=0;                     

                     directory[browser.first_dir_n+i-browser.first_dir_fn].selected=0;
                     form[i].selected=0;
                     chdir(directory[browser.dir_selected].name);
    getcwd(curr_dir,250);
    rectfill(form1,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y-form[dialog_fn].y,form[browser.up_fn].x+572-form[dialog_fn].x,form[browser.up_fn].y+form[browser.up_fn].h-form[dialog_fn].y,colour.dark_grey_boundry);
    textprintf_ex(form1,data[XSANS2].dat,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y+3-form[dialog_fn].y,colour.white,-1,"%s",curr_dir);
    blit(form1,dblbuffer,form[browser.up_fn].x+76-form[dialog_fn].x,form[browser.up_fn].y-form[dialog_fn].y,form[browser.up_fn].x+76,form[browser.up_fn].y,496,form[browser.up_fn].h);
    blit(dblbuffer,screen,form[browser.up_fn].x+76,form[browser.up_fn].y,form[browser.up_fn].x+76,form[browser.up_fn].y,496,form[browser.up_fn].h);
                     initialize_dir_file();
                     init_scroll_bars();
                     update_file_scroll(0,1);
                     update_dir_scroll(0,1);                     
                  }

              }




             if(form[i].type==31 && (browser.first_file_n+i-browser.first_file_fn<browser.file_n) )
              {
               if(form[i].selected==0)
                 {
                     for(j=0;j<34;j++)
                       chrs[j]=file[browser.first_file_n+i-browser.first_file_fn].name[j];
                     chrs[j]='\0';  

                    file[browser.first_file_n+i-browser.first_file_fn].selected=1;
                    form[i].selected=1;
                    rectfill(form1,form[i].x-form[dialog_fn].x,form[i].y+1-form[dialog_fn].y,form[i].x+form[i].w-form[dialog_fn].x,form[i].y+form[i].h-form[dialog_fn].y-2,colour.item_selected);  
                    textprintf_ex(form1,data[XSANS2].dat,form[i].x+2-form[dialog_fn].x,form[i].y+2-form[dialog_fn].y,colour.white,-1,"%s",chrs);
                    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
                    blit(form1,dblbuffer,form[i].x-form[dialog_fn].x,form[i].y-form[dialog_fn].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
                    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
                    blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                           if(browser.mode==2)
                            {
                              bgsample = load_jpg(file[browser.first_file_n+i-browser.first_file_fn].name, NULL);
                              if(windows_version==1 || dos_version==1)
                              {
                              m=316;
                              n=362;
                              }
                              else
                              {
                              m=316;
                              n=358;
                              }
                              rectfill(form1,m,n,m+123,n+123,colour.surface_grey);
                              blit(bgsample,form1,0,0,m,n,124,124);
                              blit(form1,dblbuffer,m,n,form[dialog_fn].x+m,form[dialog_fn].y+n,124,124);
                              blit(dblbuffer,screen,form[dialog_fn].x+m,form[dialog_fn].y+n,form[dialog_fn].x+m,form[dialog_fn].y+n,124,124);
                              destroy_bitmap(bgsample);
                            }
                           if(browser.file_selected!=-1 && browser.mode==2)
                            {
                              n=browser.first_file_fn;
                              temp2=0;
                              for(m=browser.first_file_n;m<browser.first_file_n+browser.contain_file;m++)
                              {
                                if(browser.file_selected==m)
                                {
                                    for(j=0;j<34;j++)
                                     chrs[j]=file[browser.first_file_n+n-browser.first_file_fn].name[j];
                                    chrs[j]='\0';  
                                    file[m].selected=0;
                                    form[n].selected=0;
                                    rectfill(form1,form[n].x-form[dialog_fn].x,form[n].y+1-form[dialog_fn].y,form[n].x+form[n].w-form[dialog_fn].x,form[n].y+form[n].h-form[dialog_fn].y-2,colour.white);  
                                    textprintf_ex(form1,data[XSANS2].dat,form[n].x+2-form[dialog_fn].x,form[n].y+2-form[dialog_fn].y,colour.black,-1,"%s",chrs);
                                    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
                                    blit(form1,dblbuffer,form[n].x-form[dialog_fn].x,form[n].y-form[dialog_fn].y,form[n].x,form[n].y,form[n].w+1,form[n].h+1);
                                    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
                                    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
                                    blit(dblbuffer,screen,form[n].x,form[n].y,form[n].x,form[n].y,form[n].w+1,form[n].h+1);
                                    temp2=1;
                                    break;
                                }
                                n=n+1;
                             }
                             if(temp2==0)
                               file[browser.file_selected].selected=0;
                           }
                           browser.file_selected=browser.first_file_n+i-browser.first_file_fn;
                  }
                 else
                  {
                     for(j=0;j<34;j++)
                       chrs[j]=file[browser.first_file_n+i-browser.first_file_fn].name[j];
                     chrs[j]='\0';  

                    file[browser.first_file_n+i-browser.first_file_fn].selected=0;
                    form[i].selected=0;
                    rectfill(form1,form[i].x-form[dialog_fn].x,form[i].y+1-form[dialog_fn].y,form[i].x+form[i].w-form[dialog_fn].x,form[i].y+form[i].h-form[dialog_fn].y-2,colour.white);  
                    textprintf_ex(form1,data[XSANS2].dat,form[i].x+2-form[dialog_fn].x,form[i].y+2-form[dialog_fn].y,colour.black,-1,"%s",chrs);
                    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
                    blit(form1,dblbuffer,form[i].x-form[dialog_fn].x,form[i].y-form[dialog_fn].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
                    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
                    blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                    if(browser.mode==2)
                      browser.file_selected=-1;

                  }

              }

           }
      }


     if(global.menu_selected==5)
       {
          if(settings.ms_deal==0 && mouse1.Fx>form[dialog_fn+2].x && mouse1.Fx<form[dialog_fn+2].x+form[dialog_fn+2].w && mouse1.Fy>form[dialog_fn+2].y && mouse1.Fy<form[dialog_fn+2].y+form[dialog_fn+2].h)
            {
             form[dialog_fn+2].selected=1;
             buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+38,form[dialog_fn].x+15+12,form[dialog_fn].y+38+12,53);  
             blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+38,form[dialog_fn].x+15,form[dialog_fn].y+38,12,12);
            }

          if(settings.alrand_deal==0 && mouse1.Fx>form[dialog_fn+3].x && mouse1.Fx<form[dialog_fn+3].x+form[dialog_fn+3].w && mouse1.Fy>form[dialog_fn+3].y && mouse1.Fy<form[dialog_fn+3].y+form[dialog_fn+3].h)
           {
                form[dialog_fn+3].selected=1;
             buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+64,form[dialog_fn].x+15+12,form[dialog_fn].y+64+12,53);  
             blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+64,form[dialog_fn].x+15,form[dialog_fn].y+64,12,12);
            }

         if(mouse1.Fx>form[dialog_fn+4].x && mouse1.Fx<form[dialog_fn+4].x+form[dialog_fn+4].w && mouse1.Fy>form[dialog_fn+4].y && mouse1.Fy<form[dialog_fn+4].y+form[dialog_fn+4].h)
           {
             form[dialog_fn+4].selected=1;
             if(settings.animation==0)
               {
                buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15+12,form[dialog_fn].y+96+12,58);  
             blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15,form[dialog_fn].y+96,12,12);
                }
              else
                {
                buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15+12,form[dialog_fn].y+96+12,59);                
             blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+96,form[dialog_fn].x+15,form[dialog_fn].y+96,12,12);
                }
            }

        if(dos_version==0)
         {
         if(mouse1.Fx>form[dialog_fn+6].x && mouse1.Fx<form[dialog_fn+6].x+form[dialog_fn+6].w && mouse1.Fy>form[dialog_fn+6].y && mouse1.Fy<form[dialog_fn+6].y+form[dialog_fn+6].h)
           {
             form[dialog_fn+6].selected=1;
             if(settings.status_bar==0)
               {
                buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15+12,form[dialog_fn].y+116+12,58);  
             blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15,form[dialog_fn].y+116,12,12);
               }
              else
               {
                buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15+12,form[dialog_fn].y+116+12,59);                
             blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+116,form[dialog_fn].x+15,form[dialog_fn].y+116,12,12);
               }
           }
         if(settings.status_bar==0 && mouse1.Fx>form[dialog_fn+7].x && mouse1.Fx<form[dialog_fn+6].x+form[dialog_fn+7].w && mouse1.Fy>form[dialog_fn+7].y && mouse1.Fy<form[dialog_fn+7].y+form[dialog_fn+7].h)
           {
             form[dialog_fn+7].selected=1;
             if(settings.status_bar==0)
               {
                buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+136,form[dialog_fn].x+15+12,form[dialog_fn].y+136+12,58);  
                blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+136,form[dialog_fn].x+15,form[dialog_fn].y+136,12,12);
               }
              else
               {
                buttons_related(dblbuffer,form[dialog_fn].x+15,form[dialog_fn].y+136,form[dialog_fn].x+15+12,form[dialog_fn].y+136+12,59);                
                blit(dblbuffer,screen,form[dialog_fn].x+15,form[dialog_fn].y+136,form[dialog_fn].x+15,form[dialog_fn].y+136,12,12);
               }
            }
          }

       }


      if( mouse1.Fx>form[dialog_fn].x && mouse1.Fx<form[dialog_fn].x+form[dialog_fn].w && mouse1.Fy>form[dialog_fn].y && mouse1.Fy<form[dialog_fn].y+form[dialog_fn].h)
        {
             if(mouse1.Fx>form[dialog_fn+1].x && mouse1.Fx<form[dialog_fn+1].x+form[dialog_fn+1].w && mouse1.Fy>form[dialog_fn+1].y && mouse1.Fy<form[dialog_fn+1].y+form[dialog_fn+1].h)  
               {
                form[dialog_fn+1].selected=1;
                buttons_related(dblbuffer,form[dialog_fn+1].x,form[dialog_fn+1].y,form[dialog_fn+1].x+form[dialog_fn+1].w,form[dialog_fn+1].y+form[dialog_fn+1].h,14);  
                blit(dblbuffer,screen,form[dialog_fn+1].x,form[dialog_fn+1].y,form[dialog_fn+1].x,form[dialog_fn+1].y,form[dialog_fn+1].w+1,form[dialog_fn+1].h+1);
               }
             else
               {
                 if(mouse1.Fy-form[dialog_fn].y<22)
                  {
                    global.mouse_active=0;
                    form[dialog_fn].selected=1;
                    xtra_x=mouse1.px+mouse1.w-(form[dialog_fn].x+form[dialog_fn].w);
                    if(xtra_x<0)
                       xtra_x=0;
                  }
               }
         }
   }
     if(  (settings.fullscreen==1 || settings.status_bar==1) && global.dialog_active==0 && mouse1.Fx>form[global.exit_fn].x && mouse1.Fx<form[global.exit_fn].x+form[global.exit_fn].w && mouse1.Fy>form[global.exit_fn].y && mouse1.Fy<form[global.exit_fn].y+form[global.exit_fn].h)
     {
      form[global.exit_fn].selected=1;
      buttons_related(dblbuffer,SCREEN_W-27,6,SCREEN_W-7,24,10);
      blit(dblbuffer,screen,SCREEN_W-27,6,SCREEN_W-27,6,21,19);
     }

  if(overed>=0)
    {
   //   textprintf_ex(screen,font,500,400,45,-1,"%d",form[overed].selected);
      if(form[overed].selected==0)
      {
      buttons_related(dblbuffer,form[overed].x,form[overed].y,form[overed].x+form[overed].w,form[overed].y+form[overed].h,3);  
             blit(dblbuffer,screen,form[overed].x,form[overed].y,form[overed].x,form[overed].y,form[overed].w+1,form[overed].h+1);
      form[overed].selected=1;
      if(form[overed].n==502)
        menuselected=1;
      if(form[overed].n==503)
        menuselected=2;
      if(form[overed].n==504)
        menuselected=3;

       main_menu_sel_f=1; 
      main_menu_selection();
      P_menu=overed;        
       }    
      
         if(form[overed].selected==1)
        {
          for(i=3;i<active_number;i++)
           {
             if(form[overed].n==form[activeform[i]].n && (mouse1.x>form[overed].x && mouse1.x<form[overed].x+form[overed].w && mouse1.y<form[overed].y+form[overed].h && mouse1.y>form[overed].y) || (mouse1.x>form[activeform[i]].x && mouse1.x<form[activeform[i]].x+form[activeform[i]].w && mouse1.y<form[activeform[i]].y+form[activeform[i]].h && mouse1.y>form[activeform[i]].y) )
              {          
                take_action=0;
               // textprintf_ex(screen,font,540,400,45,-1,"%d  %d",mouse1.x,i);
                if(form[activeform[i]].n==502)
                   temps=i+7;
                 if(form[activeform[i]].n==503)
                   temps=i+4;
                 if(form[activeform[i]].n==504)
                   temps=i+global.num_xtra_submenu;

         for(j=P_submenu;j<P_submenu+7;j++)
            {
              if(form[activeform[j]].overed==1 && mouse1.x>form[overed].x && mouse1.x<form[activeform[j]].x+form[activeform[j]].w && mouse1.y<form[activeform[j]].y+form[activeform[j]].h && mouse1.y>form[activeform[j]].y && form[activeform[j]].type==5)
              {
                  if(form[2].selected==1) 
                       menus_flag[2][form[activeform[j]].n-422]=1;
                  if(form[1].selected==1) 
                       menus_flag[1][form[activeform[j]].n-412]=1;
                  if(form[0].selected==1) 
                       menus_flag[0][form[activeform[j]].n-402]=1;
                       menu_select_F=1;
                        take_action=1; 
                        break;

               }
             }         

                break;
           
              }                
           
           }    
           if(take_action==1)
           {
             buttons_related(dblbuffer,form[overed].x,form[overed].y,form[overed].x+form[overed].w,form[overed].y+form[overed].h,7);            
             blit(dblbuffer,screen,form[overed].x,form[overed].y,form[overed].x,form[overed].y,form[overed].w+1,form[overed].h+1);
             form[overed].can_over=1;
             form[overed].selected=0;
             for(i=3;i<fn;i++)
              {
               if(form[overed].n==form[i].n )
               {
                 if(mouse1.x>=form[i].x && mouse1.y+mouse1.h>=form[i].y && mouse1.x+mouse1.w<=form[i].x+form[i].w && mouse1.y+mouse1.h<= form[i].y+form[i].h)
                      blit(temp,mouse_bg,mouse1.x+500-form[i].x,mouse1.y-form[i].y,0,0,mouse1.w,mouse1.h);

                 if(mouse1.x>=form[i].x && mouse1.y>=form[i].y && (mouse1.x+mouse1.w>form[i].x+form[i].w || mouse1.h+mouse1.y>form[i].y+form[i].h) )
                      blit(temp,mouse_bg,mouse1.x+500-form[i].x,mouse1.y-form[i].y,0,0,form[i].x+form[i].w+1-mouse1.x,form[i].y+form[i].h+1-mouse1.y);

                 if(mouse1.x+mouse1.w>=form[i].x && mouse1.y+mouse1.h>=form[i].y && mouse1.x<form[i].x && mouse1.y<=form[i].y+form[i].h)
                      blit(temp,mouse_bg,500,mouse1.y-form[i].y,form[i].x-mouse1.x,0,mouse1.x+mouse1.h-form[i].x,form[i].y+form[i].h+1-mouse1.y);                 
                   masked_blit(mouse,temp,0,0,mouse1.x+500-form[i].x,mouse1.y-form[i].y,mouse1.w,mouse1.h);
                   blit(temp,dblbuffer,500,0,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                   blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                   break; 
                }    
              
              }    
              if(form[overed].n==502)
               {
               for(i=402;i<=408;i++)
                delete_form(i,-1);           
               }

             if(form[overed].n==503)
               {
                for(i=412;i<=415;i++)
                  delete_form(i,-1);
               }              

             if(form[overed].n==504)
               {
                for(i=422;i<422+global.num_xtra_submenu;i++)
                  delete_form(i,-1);
               }              

            delete_form(form[overed].n,-1);
             main_menu_sel_f=0;
             do_mouse_over=1;
             P_menu=-1;
             overed=-1;
             take_action=0;  
                  
           }
                
        }
    
    }     


if(global.dialog_active==0 && main_menu_sel_f==0)
 {

  if(flag.prob_click_events==1)
    {
      z=global.cardselected;
      c=global.form_num;
      if(mouse1.h!=20)
         change_mouse_cursor();    
      tmp_topcard=form[z].topcard;
      if(tmp_topcard==0)
           shift_card(1,global.form_num,z);

      if(tmp_topcard==1)
         {
          previous_card(global.cardselected);
          temp1=Prev_pos[1]+1;
          tmp_prev_pos[0]=Prev_pos[0];
          tmp_prev_pos[1]=Prev_pos[1];
          for(i=temp1;i>=0;i--)
            {
                   if(i==temp1)
                   {
                      j=1;
                      tmp_compt=check_comptable(card[tmp_prev_pos[0]][i-1],card[tmp_prev_pos[0]][i]);
                      if(tmp_compt==0)
                      {
                        shift_card(1,global.form_num,global.cardselected);
                        break;
                      }
                   }


                   if(tmp_compt==1)
                   {
                     do_animation=1;
                     if(i<temp1)
                     {
                       previous_card(global.cardselected);
                       global.cardselected=Prev_card;
                     }
                     effects[j]=global.cardselected;
                     j=j+1;
                   }
                   global.free_ca=global.free_ca-1;
                   if(global.free_ca<0)
                      break;
                   tmp_compt=check_comptable(card[tmp_prev_pos[0]][i-2],card[tmp_prev_pos[0]][i-1]);
                   if( (card[tmp_prev_pos[0]][i-1]/4) -(form[c].card/4) ==0)
                      break;
                   if(tmp_compt==0)
                   {
                      previous_card(global.cardselected);
                      global.cardselected=Prev_card;
                      effects[j]=global.cardselected;
                      j=j+1;
                      break;
                   }
            }
//##########################################################
            if(do_animation==1)
            {
               r_n=0;
               r_n1=0;
               r_n2=0;
               r_n1high=0;
               calc_free_spaces();
               temp2=global.free_ca; //to make sure that loop 2 doesnt run unnecessarily
//textprintf_ex(screen,font,100,380,54546,-1,"%d",global.free_ca);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
               for(i=1;i<j-1;i++)
               {
                 calc_free_spaces();
                 if(form[c].card==98 && global.free_fca==0)
                   break;

                if(global.free_fca==0 && global.free_columns>=1 )
                {
                  for(k=active_number;k>0;k--)
                  {
                    z2=activeform[k];
                    if(form[z2].card==98)
                    {
                       global.cardselected=effects[i];
                       r_n1=r_n1+1;
                       r_n2=r_n2+1;
                       if(r_n1>r_n1high)
                          r_n1high=r_n1;
                       replace2[r_n1][r_n2]=global.cardselected;
                       global.form_num=z2;
                       shift_card(1,global.form_num,global.cardselected);
                       global.form_num=global.cardselected;
                       for(l=r_n;l>0;l--)
                        {
                          global.cardselected=replace[l];                        
                           r_n2=r_n2+1;
                           replace2[r_n1][r_n2]=global.cardselected;
                          shift_card(1,global.form_num,global.cardselected);                        
                          global.form_num=global.cardselected;
                        }
                       place_freecell=0;
                       store_rn2[r_n1]=r_n2;
                       r_n=0;
                       r_n2=0;
                       calc_free_spaces();
                       global.form_num=c;
                       break;
                     }
                  }
//rectfill(screen,100,340,180,360,234);
//textprintf_ex(screen,font,100,340,54546,-1,"1");
//                       readkey();
                }


                if(global.free_columns==0 && r_n1>1 && i!=(temp2-1) && (j-1)-i>global.free_fca+1)   //loop 2
                 {
                   for(k=r_n1-1;k>0;k--)
                    {                 
                       r_n2=store_rn2[k];
                       for(l=1;l<=global.free_fca;l++)
                       {
                         d=free_cell[l];
                         global.cell_num=d;
                         global.cardselected=replace2[l][r_n2];
                         r_n2=r_n2-1;                         
                         r_n=r_n+1;
                         replace[r_n]=global.cardselected;
                         shift_card(2,global.cell_num,global.cardselected);
                         calc_free_spaces();
                      }
                       global.form_num=replace2[r_n1][store_rn2[r_n1]];
                       global.cardselected=replace2[k][r_n2];
                       replace2[r_n1][store_rn2[r_n1]+1]=global.cardselected;
                       shift_card(1,global.form_num,global.cardselected);
                       global.form_num=global.cardselected;
//rectfill(screen,100,340,180,360,234);
//textprintf_ex(screen,font,100,340,54546,-1,"%d   %d   %d",3,r_n1,store_rn2[r_n1]);
//                       readkey();
                      store_rn2[k]=0;
                      r_n2=store_rn2[r_n1];
                      r_n2=r_n2+1;
                       for(l=r_n;l>0;l--)
                        {
                          global.cardselected=replace[l];                        
                           r_n2=r_n2+1;
                           replace2[r_n1][r_n2]=global.cardselected;
                          shift_card(1,global.form_num,global.cardselected);                        
                          global.form_num=global.cardselected;
                        }
                       store_rn2[r_n1]=r_n2;
                       r_n=0;
                       r_n2=0;
                    }
                      r_n1=0;
//rectfill(screen,100,340,180,360,234);
//textprintf_ex(screen,font,100,340,54546,-1,"2");
//                       readkey();
                 }

                if(place_freecell==1)      //this loop put chain cards to left freecell
                {
                  for(k=1;k<=global.free_fca;k++)
                  {
                    d=free_cell[k];
                    global.cell_num=d;
                    global.cardselected=effects[i];
                    r_n=r_n+1;
                    replace[r_n]=global.cardselected;
                    shift_card(2,global.cell_num,global.cardselected);
                    calc_free_spaces();
                    break;
                  }
                }
                place_freecell=1;
            }
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//textprintf_ex(screen,font,100,400,34546,-1,"Gooooooooooooooooooooooooooooooooooooooooooooood");
//readkey();
           global.cardselected=effects[i];
           shift_card(1,global.form_num,global.cardselected);
           calc_free_spaces();
           global.form_num=global.cardselected;
           for(i=r_n;i>0;i--)
           {
              global.cardselected=replace[i];
              shift_card(1,global.form_num,global.cardselected);
              calc_free_spaces();
              global.form_num=global.cardselected;
           }
           c=global.cardselected;
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//readkey();
           for(i=r_n1;i>0;i--)
           {
              place_freecell=1;
              r_n=0;
//................
              for(j=store_rn2[i];j>0;j--)
              {
               if(j==1 && global.free_fca==0)
               {
                  global.cardselected=replace2[i][j];
                  shift_card(1,global.form_num,global.cardselected);
                  calc_free_spaces();
                  global.form_num=global.cardselected;
                  place_freecell=0;
                  for(k=r_n;k>0;k--)
                  {
                     global.cardselected=replace[k];
                     shift_card(1,global.form_num,global.cardselected);
                     calc_free_spaces();
                     global.form_num=global.cardselected;
//                   readkey();
                  }
               }

              if(place_freecell==1)
              {
                for(k=1;k<=global.free_fca;k++)
                {
                  d=free_cell[k];
                  global.cell_num=d;
                  global.cardselected=replace2[i][j];
                  r_n=r_n+1;
                  replace[r_n]=global.cardselected;
                  shift_card(2,global.cell_num,global.cardselected);
                  calc_free_spaces();
                  break;
                }
              }
             }
//................
           }

   temp2=r_n1+1;
   c=global.form_num;
//***************************************************************************
   for(i=temp2;i<=r_n1high;i++)
   {
    place_freecell=1;
    r_n=0; 
    r_n1=0;
    r_n2=0;   
    for(j=store_rn2[i];j>0;j--)
    {

               if(j==1)
               {
                  global.form_num=c;
                  global.cardselected=replace2[i][j];
                  shift_card(1,global.form_num,global.cardselected);
                  global.form_num=global.cardselected;
                  for(k=r_n;k>0;k--)
                  {
                     global.cardselected=replace[k];
                     shift_card(1,global.form_num,global.cardselected);
                     global.form_num=global.cardselected;

                  }
//rectfill(screen,100,340,180,360,234);
//textprintf_ex(screen,font,100,340,54546,-1,"14");
//                       readkey();
                         for(m=r_n1;m>0;m--)
                         {
                            calc_free_spaces();
                            r_n=0;
                            for(n=store_rn2[m];n>0;n--)
                            {
                                if(n>1)
                                {
                                for(k=1;k<=global.free_fca;k++)
                                 {
                                   d=free_cell[k];
                                   global.cell_num=d;
                                   global.cardselected=replace2[m][n];
                                   r_n=r_n+1;
                                   replace[r_n]=global.cardselected;
                                   shift_card(2,global.cell_num,global.cardselected);
                                   calc_free_spaces();
//                                   readkey();
                                   break;
                                 }
                                  }
                                  if(n==1)
                                   {
                                   global.cardselected=replace2[m][n];
                                   shift_card(1,global.form_num,global.cardselected);
                                   global.form_num=global.cardselected;
//                                   readkey();
                                   for(k=r_n;k>0;k--)
                                    {
                                      global.cardselected=replace[k];
                                      shift_card(1,global.form_num,global.cardselected);
                                      calc_free_spaces();
                                      global.form_num=global.cardselected;
//                                   readkey();
                                    }
                                     c=global.cardselected;
                                   }
//rectfill(screen,100,340,180,360,234);
//textprintf_ex(screen,font,100,340,54546,-1,"12");
//                       readkey();

                                 }
//rectfill(screen,100,340,180,360,234);
//textprintf_ex(screen,font,100,340,54546,-1,"12");
//                       readkey();
                             }
                  r_n=0;
                  place_freecell=0;
                  calc_free_spaces();
               }

               if(j>1 && global.free_fca==0 && global.free_columns>=1)
               {
                  for(k=active_number;k>0;k--)
                  {
                    z2=activeform[k];
                    if(form[z2].card==98)
                    {
                       global.cardselected=replace2[i][j];
                       r_n1=r_n1+1;
                       r_n2=r_n2+1;
                       replace2[r_n1][r_n2]=global.cardselected;
                       global.form_num=z2;
                       shift_card(1,global.form_num,global.cardselected);
                       global.form_num=global.cardselected;
                       for(l=r_n;l>0;l--)
                        {
                          global.cardselected=replace[l];                        
                           r_n2=r_n2+1;
                           replace2[r_n1][r_n2]=global.cardselected;
                          shift_card(1,global.form_num,global.cardselected);                        
                          global.form_num=global.cardselected;
                        }
//rectfill(screen,100,340,180,360,234);
//textprintf_ex(screen,font,100,340,54546,-1,"16");
//                       readkey();

                       place_freecell=0;
                       store_rn2[r_n1]=r_n2;
                       r_n=0;
                       r_n2=0;
                       calc_free_spaces();
                       break;
                     }
                  }
               }



              if(place_freecell==1)
              {
                for(k=1;k<=global.free_fca;k++)
                {
                  d=free_cell[k];
                  global.cell_num=d;
                  global.cardselected=replace2[i][j];
                  r_n=r_n+1;
                  replace[r_n]=global.cardselected;
                  shift_card(2,global.cell_num,global.cardselected);
                  calc_free_spaces();
                  break;
                }
              }
              place_freecell=1;

    }
   }
//********************************************************************
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
       }
//##########################################################
    }
      flag.dnb_lclick=0;
      sweep_freecell=1;
 }

  if(flag.prob_click_events==2)
    {
      if(mouse1.h!=20)
         change_mouse_cursor();    
      shift_card(2,global.cell_num,global.cardselected); 
      flag.dnb_lclick=0;
      sweep_freecell=1;
    }


  if(sweep_freecell==1)
    {
      sweep_freecell=0;
        while(loop_sweep)
        {
          loop_sweep=0;

          for(i=1;i<active_number;i++)
           {
           z=activeform[i];
             for(j=0;j<4;j++)
               temp2=check_cell_cards(form[z].card);  //temp2 used to store the cell number
             if(temp2!=0)
               {
                 shift_card(2,temp2,z);
                 calc_free_spaces();
                 loop_sweep=1;
//                 readkey();
               }
           }
        }
       if(cards_left==0)
         {
      //-------------------PLACE BIG KING------------------------//
      if(settings.background==0)
      {
            stretch_image();
            if(settings.fullscreen==1)
              {
                    if(mouse1.x+mouse1.w>50 && mouse1.x < 50+320 && mouse1.y+mouse1.h>190 && mouse1.y<190+320)
                     {
                       masked_blit(buffer,mouse_bg,mouse1.x-50,mouse1.y-190,0,0,mouse1.w,mouse1.h); 
                       masked_blit(mouse,buffer,0,0,mouse1.x-50,mouse1.y-190,mouse1.w,mouse1.h);
                     }
                     blit(buffer,dblbuffer,0,0,50,190,320,320); 
                     blit(dblbuffer,screen,50,190,50,190,320,320);
               }

            if(settings.fullscreen==0)
              {
                    if(mouse1.x+mouse1.w>15 && mouse1.x < 15+320 && mouse1.y+mouse1.h>159 && mouse1.y<159+320)
                     {
                       masked_blit(buffer,mouse_bg,mouse1.x-15,mouse1.y-159,0,0,mouse1.w,mouse1.h); 
                       masked_blit(mouse,buffer,0,0,mouse1.x-15,mouse1.y-159,mouse1.w,mouse1.h);
                     }
                     blit(buffer,dblbuffer,0,0,15,159,320,320); 
                     blit(dblbuffer,screen,15,159,15,159,320,320);
               }
      //-------------------PLACE BIG KING------------------------//
      
      //-------------------CONGRATULATIONS------------------------//      
             rectfill(temp,0,0,200,25,colour.bg_green_dark);
             textprintf_ex(temp,data[XSANS].dat,0,0,makecol(128,248,240),-1,"%s","Congratulations");
             stretch_image2();
             if(settings.fullscreen==1)
              {
                   if(mouse1.x+mouse1.w>430 && mouse1.x < 430+300 && mouse1.y+mouse1.h>250 && mouse1.y < 250+80)
                    {
                     masked_blit(buffer,mouse_bg,mouse1.x-430,mouse1.y-250,0,0,mouse1.w,mouse1.h); 
                     masked_blit(mouse,buffer,0,0,mouse1.x-430,mouse1.y-250,mouse1.w,mouse1.h);
                    }
                   blit(buffer,dblbuffer,0,0,430,250,300,80);  
                   blit(dblbuffer,screen,430,250,430,250,300,80);  
               }

             if(settings.fullscreen==0)
              {
                   if(mouse1.x+mouse1.w>340 && mouse1.x < 340+300 && mouse1.y+mouse1.h>180 && mouse1.y < 180+80)
                    {
                     masked_blit(buffer,mouse_bg,mouse1.x-340,mouse1.y-180,0,0,mouse1.w,mouse1.h); 
                     masked_blit(mouse,buffer,0,0,mouse1.x-340,mouse1.y-180,mouse1.w,mouse1.h);
                    }
                   blit(buffer,dblbuffer,0,0,340,180,300,80);  
                   blit(dblbuffer,screen,340,180,340,180,300,80);  
               }
      //-------------------CONGRATULATIONS------------------------//      

      //-------------------YOU WIN------------------------//            
           rectfill(temp,0,0,200,25,colour.bg_green_dark);
           textprintf_ex(temp,data[XSANS].dat,0,0,makecol(128,248,240),-1,"%s","You Win");
           stretch_image2();
             if(settings.fullscreen==1)
             {
               if(mouse1.x+mouse1.w>500 && mouse1.x < 500+200 && mouse1.y+mouse1.h>330 && mouse1.y < 330+80)
               {
                 masked_blit(buffer,mouse_bg,mouse1.x-500,mouse1.y-330,0,0,mouse1.w,mouse1.h); 
                 masked_blit(mouse,buffer,0,0,mouse1.x-500,mouse1.y-330,mouse1.w,mouse1.h);
               }
               blit(buffer,dblbuffer,0,0,500,330,200,80);  
               blit(dblbuffer,screen,500,330,500,330,200,80);  
             } 

             if(settings.fullscreen==0)
             {
               if(mouse1.x+mouse1.w>412 && mouse1.x < 412+200 && mouse1.y+mouse1.h>260 && mouse1.y < 260+80)
               {
                 masked_blit(buffer,mouse_bg,mouse1.x-412,mouse1.y-260,0,0,mouse1.w,mouse1.h); 
                 masked_blit(mouse,buffer,0,0,mouse1.x-412,mouse1.y-260,mouse1.w,mouse1.h);
               }
               blit(buffer,dblbuffer,0,0,412,260,200,80);  
               blit(dblbuffer,screen,412,260,412,260,200,80);  
             } 
           //colour.bg_green_dark

      //-------------------YOU WIN------------------------// 

      //-------------------HIDE KING------------------------//
        if(settings.fullscreen==1)
         {
           rectfill(buffer,380-20,79-27,380+32+20,79+32+27,colour.transperent);
           rectfill(buffer,380,79,380+32,79+32,colour.bg_green_dark);
            if(mouse1.x+mouse1.w>380 && mouse1.x < 380+32 && mouse1.y+mouse1.h>79 && mouse1.y < 79+32)
             {
              masked_blit(buffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);
              masked_blit(mouse,buffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
             }
           blit(buffer,dblbuffer,380,79,380,79,32,32);
           blit(dblbuffer,screen,380,79,380,79,32,32);
         }  
        else
         {
              if(settings.status_bar==1)
               {
                 rectfill(buffer,309-20,79-27,309+32+20,79+32+27,colour.transperent);
                 rectfill(buffer,309,79,309+32,79+32,colour.bg_green_dark);
                 if(mouse1.x+mouse1.w>309 && mouse1.x < 309+32 && mouse1.y+mouse1.h>79 && mouse1.y < 79+32)
                  {
                   masked_blit(buffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);
                   masked_blit(mouse,buffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                  }
                 blit(buffer,dblbuffer,309,79,309,79,32,32);
                 blit(dblbuffer,screen,309,79,309,79,32,32);
               }

              if(settings.status_bar==0)
               {
                 rectfill(buffer,309-20,52-27,309+32+20,52+32+27,colour.transperent);
                 rectfill(buffer,309,52,309+32,52+32,colour.bg_green_dark);
                 if(mouse1.x+mouse1.w>309 && mouse1.x < 309+32 && mouse1.y+mouse1.h>52 && mouse1.y < 52+32)
                  {
                   masked_blit(buffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);
                   masked_blit(mouse,buffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                  }
                 blit(buffer,dblbuffer,309,52,309,52,32,32);
                 blit(dblbuffer,screen,309,52,309,52,32,32);
               }

         }  
      //-------------------HIDE KING------------------------//
           global.show_king=0;
           global.show_game_select=1;
      }  //ends if(global.colour_depth==1)
           if(global.cheat==0)
           {
            statistics.last_game_status=1;
            do_statistics();
           }
           //blit(mouse_bg,screen,0,0,670,5,mouse1.w,mouse1.h); 
           // readkey();
      }
  }

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
if(flag.dnb_lclick==1)
 {
  for(j=active_number-1;j>0;j--)
  {
    z=activeform[j];

    if( form[z].type==1 && mouse1.Fx>form[z].x && mouse1.Fx<form[z].x+form[z].w && mouse1.Fy>form[z].Focus_y && mouse1.Fy<form[z].y+form[z].h  )
    {
 
      if(form[z].selected==0)
       {
           if(global.cheat==2)
           invert_card_color(data[52].dat);
           else
           invert_card_color(data[form[z].card].dat);
           if(mouse1.y>=form[z].y-20)
           {
             masked_blit(buffer,mouse_bg,729+mouse1.x-form[z].x,504+mouse1.y-form[z].y,0,0,mouse1.w,mouse1.h);
             masked_blit(mouse,buffer,0,0,729+mouse1.x-form[z].x,504+mouse1.y-form[z].y,mouse1.w,mouse1.h);
           }
           masked_blit(buffer,dblbuffer,729,504,form[z].x,form[z].y,form[z].w,form[z].h);
           blit(dblbuffer,screen,form[z].x,form[z].y,form[z].x,form[z].y,form[z].w,form[z].h);
           if(mouse1.y>form[z].y-20)
              blit(mouse_bg,buffer,0,0,729+mouse1.x-form[z].x,504+mouse1.y-form[z].y,mouse1.w,mouse1.h);
           for(k=1;k<active_number;k++)
           {
             z=activeform[k];  //note this
             if(form[z].selected==1  && form[z].type==1) //type 1 to avoid fancy screen $^$%^#$^%%$&^&%$
              {
                form[z].selected=0;
               if(global.cheat==2)
                masked_blit(data[52].dat,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                else
                masked_blit(data[form[z].card].dat,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                blit(dblbuffer,screen,form[z].x,form[z].y,form[z].x,form[z].y,form[z].w,form[z].h);
              }
            }
            z=activeform[j];  //note this
            form[z].selected=1;
            global.Fcardselected=1;
            global.cardselected=z;
            flag.calc=1;
            break;                            //note this break it may be useful to sort order
         }
      else if(form[z].selected==1)
      {
        form[z].selected=0;
        if(global.cheat==2)        
        blit(data[52].dat,cardtemp,0,0,0,0,form[z].w,form[z].h);
        else
        blit(data[form[z].card].dat,cardtemp,0,0,0,0,form[z].w,form[z].h);
        masked_blit(cardtemp,mouse_bg,mouse1.x-form[z].x,mouse1.y-form[z].y,0,0,mouse1.w,mouse1.h);
        masked_blit(mouse,cardtemp,0,0,mouse1.x-form[z].x,mouse1.y-form[z].y,mouse1.w,mouse1.h);
        masked_blit(cardtemp,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
        blit(dblbuffer,screen,form[z].x,form[z].y,form[z].x,form[z].y,form[z].w,form[z].h);
        global.Fcardselected=0;
        break;
      }
    }
  }
}  
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
flag.dnb_lclick=1;
  }
}


//============================================================================================================
void mouse_rclick_events()
{
   int j;

   if(global.dialog_active==0 && main_menu_sel_f==0)
    {
    for(j=fn;j>=0;j--)
   {
     if(form[j].type==1 && form[j].topcard==0)
      {
      if(mouse1.Fx>form[j].x && mouse1.Fx<form[j].x+form[j].w && mouse1.Fy>=form[j].y && mouse1.Fy<form[j].y+18)
        {
          blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
           if(global.cheat==2)
          masked_blit(data[52].dat,dblbuffer,0,0,form[j].x,form[j].y,form[j].w,form[j].h);
           else
          masked_blit(data[form[j].card].dat,dblbuffer,0,0,form[j].x,form[j].y,form[j].w,form[j].h);
          blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);
          masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
          blit(dblbuffer,screen,form[j].x,form[j].y,form[j].x,form[j].y,form[j].w,form[j].h);
          form[j].rselected=1;
          global.rselected=1;
          global.r_clicked_form=j;
          break;
         }
        }
    }
  }
}

//==========================================================================================================
void mouse_rrelease_events()
{

   int j,m,n,t;
    if(global.rselected==1)
      {
          j=global.r_clicked_form;
          //textprintf_ex(screen,data[XSANS].dat,100,100,colour.white,-1,"%d",j);
           if(global.cheat==2)
          blit(data[52].dat,cardtemp2,0,0,0,0,form[j].w,18);
          else
          blit(data[form[j].card].dat,cardtemp2,0,0,0,0,form[j].w,18);
             for(m=1;m<9;m++)
              {
               for (n=0;n<MAX_CARD_L;n++)
                {
                 if(card[m][n]==form[j].card)
                   {
                    t=n;
                     card_position(card[m][n+1]);
                     if(form[Curr_card].selected==0)
                         {
                         if(global.cheat==2)
                         blit(data[52].dat,cardtemp2,0,0,0,18,form[j].w,form[j].h-18);
                         else
                         blit(data[card[m][n+1]].dat,cardtemp2,0,0,0,18,form[j].w,form[j].h-18);
                         }
                     else
                      {
                         invert_card_color(data[card[m][n+1]].dat);
                         blit(buffer,cardtemp2,729,504,0,18,form[j].w,form[j].h-18);
                      }   
                    for(n=n+2;n<MAX_CARD_L;n++)
                       {
                         if(card[m][n]!=99)
                           {
                             card_position(card[m][n]);
                             if(form[Curr_card].selected==0)
                                {
                                if(global.cheat==2)
                                blit(data[52].dat,cardtemp2,0,0,0,((n-t)*18),form[j].w,form[j].h-((n-t)*18));
                                else
                                blit(data[card[m][n]].dat,cardtemp2,0,0,0,((n-t)*18),form[j].w,form[j].h-((n-t)*18));
                                }
                             else
                                {
                                  invert_card_color(data[card[m][n]].dat);
                                  blit(buffer,cardtemp2,729,504,0,((n-t)*18),form[j].w,form[j].h-((n-t)*18));
                                }   
                            }
                          else
                           break;
                        }
                   //blit(data[card[m][n+1]].dat,screen,0,18,0,522,form[j].w,form[j].h-18);
                   global.rselected=0;
                   break;
                   }
                }
              }

          masked_blit(cardtemp2,mouse_bg,mouse1.x-form[j].x,mouse1.y-form[j].y,0,0,mouse1.w,mouse1.h);
          masked_blit(mouse,cardtemp2,0,0,mouse1.x-form[j].x,mouse1.y-form[j].y,mouse1.w,mouse1.h);
          masked_blit(cardtemp2,dblbuffer,0,0,form[j].x,form[j].y,form[j].w,form[j].h);
          blit(dblbuffer,screen,form[j].x,form[j].y,form[j].x,form[j].y,form[j].w,form[j].h);
          blit(mouse_bg,cardtemp2,0,0,mouse1.x-form[j].x,mouse1.y-form[j].y,mouse1.w,mouse1.h);
       }
}

//==========================================================================================================
//8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
//8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
//8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
//8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
void mouse_over_events()
{

 int i,j,c;
 int Pfn;  //back card form number
 int take_break_ff=0;  // so menu dont mix up with freecell
 int temps;
 int which_menu; //which menu mouse went after selecting a menu

 if(global.show_king==1)
   king_move(); //ie making the king move :-)

 if(overed>=0)
  {
   if(mouse1.x<form[overed].x || mouse1.x>form[overed].x+form[overed].w || mouse1.y>form[overed].y+form[overed].h || mouse1.y<form[overed].y) 
    {
      if(form[overed].selected==0)
       { 
           buttons_related(dblbuffer,form[overed].x,form[overed].y,form[overed].x+form[overed].w,form[overed].y+form[overed].h,4);
             blit(dblbuffer,screen,form[overed].x,form[overed].y,form[overed].x,form[overed].y,form[overed].w+1,form[overed].h+1);
           form[overed].can_over=1;
           overed=-1;
       }        
      if(form[overed].selected==1)
       {
           
          for(i=global.exit_fn+1;i<active_number;i++)
           {
             if(form[overed].n==form[activeform[i]].n && mouse1.x>form[activeform[i]].x && mouse1.x<form[activeform[i]].x+form[activeform[i]].w && mouse1.y<form[activeform[i]].y+form[activeform[i]].h && mouse1.y>form[activeform[i]].y)
              {          
                 if(form[activeform[i]].n==502)
                   temps=i+7;
                 if(form[activeform[i]].n==503)
                   temps=i+4;
                 if(form[activeform[i]].n==504)
                   temps=i+global.num_xtra_submenu;

                 for(j=i+1;j<=temps;j++)
                  {

  // textprintf_ex(screen,data[XSANS].dat,220,28+(j-i)*20,51,-1,"%d  %d",j,i); 
                   if(mouse1.x>form[activeform[j]].x && form[activeform[j]].overed==0 && form[activeform[j]].can_over==1 && mouse1.x<form[activeform[j]].x+form[activeform[j]].w && mouse1.y<form[activeform[j]].y+form[activeform[j]].h && mouse1.y>form[activeform[j]].y)
                      {
                       form[activeform[j]].overed=1;     //-=================----------============----------------==================================-------------------------=======================---------------------------======================----------------------====================---------------\=========================================\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\=
                       draw_submenu(j);
                       take_break_ff=1; 
                       }

                  }
                if(take_break_ff==1)
                  { 
                   break;
                   take_break_ff=0;
                   }
                 }
              }    
               which_menu=-1;
             if(mouse1.x>form[0].x && mouse1.x<form[0].x+form[0].w && mouse1.y<form[0].y+form[0].h && mouse1.y>form[0].y)             
               which_menu=0;
             else if(mouse1.x>form[1].x && mouse1.x<form[1].x+form[1].w && mouse1.y<form[1].y+form[1].h && mouse1.y>form[1].y)
               which_menu=1;
             else if( ((global.colour_depth==2 && settings.background==1) || settings.mplayer==1) && mouse1.x>form[2].x && mouse1.x<form[2].x+form[2].w && mouse1.y<form[2].y+form[2].h && mouse1.y>form[2].y)
               which_menu=2;

 
            if(which_menu>=0)
             {

             form[which_menu].selected=1;
             form[which_menu].can_over=0;

             buttons_related(dblbuffer,form[overed].x,form[overed].y,form[overed].x+form[overed].w,form[overed].y+form[overed].h,7);            
             blit(dblbuffer,screen,form[overed].x,form[overed].y,form[overed].x,form[overed].y,form[overed].w+1,form[overed].h+1);
             form[overed].can_over=1;
             form[overed].selected=0;

          buttons_related(dblbuffer,form[which_menu].x,form[which_menu].y,form[which_menu].x+form[which_menu].w,form[which_menu].y+form[which_menu].h,3);  
             blit(dblbuffer,screen,form[which_menu].x,form[which_menu].y,form[which_menu].x,form[which_menu].y,form[which_menu].w+which_menu,form[which_menu].h+1);
          menuselected=which_menu+1;
          main_menu_selection(); 
             P_menu=which_menu;
             overed=which_menu;
            }

        }       

    }      
  }          

if(mouse1.y<50 && overed<0 && global.show_menu==1) // This  should be below the above function
    {
     //textprintf_ex(screen,data[XSANS].dat,200,28,17,-1,"%d",form[0].can_over);
     for(i=0;i<active_number;i++)
     {
        // textprintf_ex(screen,data[XSANS].dat,250+i*20,28,0,-1,"%d",i); 
     if(form[activeform[i]].can_over==1 && mouse1.x>form[activeform[i]].x && mouse1.x<form[activeform[i]].x+form[activeform[i]].w && mouse1.y<form[activeform[i]].y+form[activeform[i]].h && mouse1.y>form[activeform[i]].y)
       {
       if(overed==-1)
          {
          buttons_related(dblbuffer,form[activeform[i]].x,form[activeform[i]].y,form[activeform[i]].x+form[activeform[i]].w,form[activeform[i]].y+form[activeform[i]].h,2);  
          blit(dblbuffer,screen,form[activeform[i]].x,form[activeform[i]].y,form[activeform[i]].x,form[activeform[i]].y,form[activeform[i]].w+1,form[activeform[i]].h+1);
          P_menu=-7;  //Any -ive to initialize
          }    
       if(P_menu>=0)
          {
          buttons_related(dblbuffer,form[activeform[i]].x,form[activeform[i]].y,form[activeform[i]].x+form[activeform[i]].w,form[activeform[i]].y+form[activeform[i]].h,3);         
          blit(dblbuffer,screen,form[activeform[i]].x,form[activeform[i]].y,form[activeform[i]].x,form[activeform[i]].y,form[activeform[i]].w+1,form[activeform[i]].h+1);
           if(form[activeform[i]].n==502)
             menuselected=1;
           if(form[activeform[i]].n==503)
             menuselected=2;
           if(form[activeform[i]].n==504)
             menuselected=3;

          main_menu_selection();
          form[activeform[i]].selected=1;
          }    
      // textprintf_ex(screen,data[XSANS].dat,250,28,0,-1,"%s","GOOD_BLADFLSF");       
      form[activeform[i]].can_over=0; 
      //textprintf_ex(screen,data[XSANS].dat,230,28,60,-1,"%s","A"); 
      overed=activeform[i];    
      break;    
        }       
   }    
   
 }    

//88888888888888888888888888888888888888888888888888888888888888888888
if (global.Fcardselected==1 && main_menu_sel_f==0 && global.dialog_active==0)
 {
  if(flag.calc==1)
   calc_free_spaces();
   
 if(D_n>0 && flag.check_mouse==1)
 {
  for(i=1;i<(D_n+1);i++)
  {
   c=mouseD_card[i];
   card_position(form[c].card);

   if(mouse1.Fx>form[c].x && mouse1.Fx<form[c].x+form[c].w && mouse1.Fy>FOCUS_Y && mouse1.Fy<form[c].y+form[c].h)
   {
    mouse1.h=27;
    mouse1.w=14;
    flag.change_mouse=1;
    change_mouse_area[0]=form[c].x;
    change_mouse_area[1]=form[c].x+form[c].w;
    change_mouse_area[2]=FOCUS_Y;
    change_mouse_area[3]=form[c].y+form[c].h;
    blit(dblbuffer,mouse_bg,mouse1.x+11,mouse1.y,11,0,mouse1.w-11,mouse1.h);
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y+20,0,20,mouse1.w,mouse1.h-20);
    blit(data[XMOUSE_DOWN].dat,mouse,0,0,0,0,mouse1.w,mouse1.h);
    set_mouse_sprite_focus(7,27);
    flag.check_mouse=0;
    global.form_num=c;
    flag.prob_click_events=1;
   }
  }
 }

 if(free_n>0 && flag.frees==1)
 {
  for(i=1;i<(free_n+1);i++)
  {
   c=free_cell[i];
   if(mouse1.Fx>=freecell[c].x && mouse1.Fx<freecell[c].x+freecell[c].w && mouse1.Fy>freecell[c].y && mouse1.Fy<freecell[c].y+freecell[c].h)
   {
    mouse1.h=19;
    mouse1.w=9;
    flag.change_mouse=2;
    change_mouse_area[0]=freecell[c].x;
    change_mouse_area[1]=freecell[c].x+freecell[c].w;
    change_mouse_area[2]=freecell[c].y;
    change_mouse_area[3]=freecell[c].y+freecell[c].h;
    blit(mouse_bg,dblbuffer,9,0,mouse1.x+9,mouse1.y,2,20);
    blit(dblbuffer,screen,mouse1.x+9,mouse1.y,mouse1.x+9,mouse1.y,2,20);
    blit(mouse_bg,dblbuffer,0,19,mouse1.x,mouse1.y+19,11,1);
    blit(dblbuffer,screen,mouse1.x,mouse1.y+19,mouse1.x,mouse1.y+19,11,1);
    blit(data[XMOUSE_UP].dat,mouse,0,0,0,0,mouse1.w,mouse1.h);
    set_mouse_sprite_focus(4,0);
    flag.frees=0;
    flag.prob_click_events=2;
    global.cell_num=c;
   }
  }
 }
}


}


//=====================================================================================================
void calc_free_spaces()
{
 int i,j,k,calci;  //chc as c
 int n_active;  //neglect this active form
 int dont_update=0;

 flag.frees=1;
 flag.calc=0;
 D_n=0;
 free_n=0;
 global.free_ca=0;
 global.free_columns=0;

 for(i=0;i<4;i++)
 {
  if(freecell[i].card_in==99)
  {
    free_n=free_n+1;
    free_cell[free_n]=i;
  }
 }
 global.free_fca=free_n;

 for(i=0;i<4;i++)
 {
   if(fillcell[i]==99 && form[global.cardselected].card<4)
   {
     free_n=free_n+1;
     free_cell[free_n]=i+4;
   }

   if(form[global.cardselected].card-fillcell[i]==4)
   {
     free_n=free_n+1;
     free_cell[free_n]=i+4;
     break;
   }
 }

 for(j=1;j<active_number;j++)
 {
   if(form[activeform[j]].card==form[global.cardselected].card)
     n_active=j;
   if(form[activeform[j]].card==98)
     global.free_columns=global.free_columns+1;

 }
 global.free_ca=global.free_fca+1;
 for(i=1;i<=global.free_columns;i++)
   global.free_ca=global.free_ca+i*(global.free_fca+1); 

 previous_card(global.cardselected);

 for(i=Prev_pos[1]+1;i>=0;i--)       //this function is necessery to show the down mouse when there is group of cards to be moved
 {
   card_position(card[Prev_pos[0]][i]);
   if(form[global.cardselected].topcard==0)
     Curr_card=global.cardselected;
   if(i<(Prev_pos[1]+1) )
    {
       if(check_comptable(card[Prev_pos[0]][i],card[Prev_pos[0]][i+1])==0)
       break;
    }

   for(j=1;j<active_number;j++)
   {
    if(n_active!=j && (form[activeform[j]].topcard==1 || (form[activeform[j]].topcard==0 && form[activeform[j]].type==2)) && check_comptable(form[activeform[j]].card,form[Curr_card].card)==1)
    {
     for(k=1;k<=D_n;k++)
     {
      if(activeform[j]==mouseD_card[k])
       dont_update=1;
     }
     if(dont_update==0)
     {
       D_n=D_n+1;
       mouseD_card[D_n]=activeform[j];
       flag.check_mouse=1;
     }
     dont_update=0;
    }
   }

   global.free_ca=global.free_ca-1;
   if(global.free_ca==0)
      break;
   if(form[global.cardselected].topcard==0)
      break;
  }

 global.free_ca=global.free_fca+1;  //this is to restore
 for(i=1;i<=global.free_columns;i++)
   global.free_ca=global.free_ca+i*(global.free_fca+1); 


}
//===================================================================================================
int check_comptable(int card1,int card2)
{
 int calci;
   if(card1==98)
     return(1);


   if(card1/4-card2/4==1)
     {
        calci=card1-card2;
        if(calci==2 || calci==6)
           return(1);

        if(calci==5)
           {
            if(card1%2 != 0)
               return(1);
           }
        if(calci==3)
           {
             if(card1%2 == 0)
               return(1);
           }
      }
 return(0);
}
//=================================================================================================
void previous_card(int j)
{
  int pm=0;
  int pn=0;
  int breakF=0;
  int i;
  for(pm=1;pm<9;pm++)
    {
     for (pn=0;pn<MAX_CARD_L;pn++)
      {
       if(card[pm][pn]==form[j].card)
          {
            if(pn==0)
               {
                Prev_card=-1;
                Prev_pos[1]=-1;
                Prev_pos[0]=pm;
                break;
               }
            for(i=0;i<fn;i++)
               {
                  if(card[pm][pn-1]==form[i].card)
                     {
                      Prev_card=i;
                      Prev_pos[1]=pn-1;
                      Prev_pos[0]=pm;
                      break;
                      breakF=1;
                     }

               }

           }
            if(breakF==1)
              break;

       }
   if(breakF==1)
     break;

   }

}

//====================================================================================
void card_position(int c)
{
  int pm=0;
  int pn=0;
  int i;
  int breakF=0;
  for(pm=1;pm<9;pm++)
    {
     for (pn=0;pn<MAX_CARD_L;pn++)
      {
       if(card[pm][pn]==c)
          {
            for(i=0;i<fn;i++)
              {
               if(form[i].card==c)
                 Curr_card=i;

              }
              Curr_pos[0]=pm;
              Curr_pos[1]=pn;
              breakF=1;
              break;
           }
       }
     if(breakF==1)
       break;

   }
}

//=========================================================================================================
int check_cell_cards(int card1)         //to be used in sweep freecell
 {
 int i,j,check=0,calc,temp;
calc=card1%4;
 for(i=0;i<4;i++)
   {
     if( fillcell[i]==99 && card1<4)
      {
       fillcolour[i]=card1;
       return(i+4);
      }
     if(card1-fillcell[i]==4)
      {
        if(card1 > 3 && card1<8)
            return(i+4);

        for(j=0;j<4;j++)
          {
            if(calc==0 && (fillcolour[j]==1 || fillcolour[j]==2) )
              {
                temp=fillcell[j];
                while(temp>3)
                  {
                   if(card1-temp==3 || card1-temp==2)
                     check=check+1;
                  temp=temp-4;
                  }
              }
          
            if(calc==1 && (fillcolour[j]==0 || fillcolour[j]==3) )
              {
                temp=fillcell[j];
                while(temp>3)
                  {
                   if(card1-temp==5 || card1-temp==2)
                     check=check+1;
                  temp=temp-4;
                  }
              }
         
           if(calc==2 && (fillcolour[j]==0 || fillcolour[j]==3) )
              {
                temp=fillcell[j];
                while(temp>3)
                  {
                   if(card1-temp==6 || card1-temp==3)
                     check=check+1;
                  temp=temp-4;
                  }
              }
     
            if(calc==3 && (fillcolour[j]==1 || fillcolour[j]==2) )
              {
                temp=fillcell[j];
                while(temp>3)
                  {
                   if(card1-temp==6 || card1-temp==5)
                     check=check+1;
                  temp=temp-4;
                  }
              }

           }

       if(check==2)
            return(i+4);

      }


   }
  return(0);
}

//===============================================================================================
void delete_form(int form_number_n,int form_number_fn)
{
  int i,j;
  int take_break=0;
//  textprintf_ex(screen,font,400,20,40,-1,"%d",form_number_n);
  if(form_number_n!=-1)
  {
    for(i=global.exit_fn+1;i<active_number;i++)   //started with 3 so not to delete original active_menu
      {
        if(form[activeform[i]].n==form_number_n)
          {
          for(j=activeform[i];j<fn;j++)
            {
              form[j].type= form[j+1].type;
              form[j].card= form[j+1].card; 
              form[j].topcard= form[j+1].topcard; 
              form[j].n= form[j+1].n;
              form[j].h= form[j+1].h;
              form[j].w= form[j+1].w;
              form[j].x= form[j+1].x;
              form[j].y= form[j+1].y;
              form[j].Focus_y= form[j+1].Focus_y;
              form[j].selected= form[j+1].selected;
              form[j].rselected= form[j+1].rselected;
              form[j].can_over= form[j+1].can_over;
              form[j].overed= form[j+1].overed;
             } 
           take_break=1;                     
          }        
              if(take_break==1)
                {
                for(j=i;j<=(active_number-1);j++)
                   activeform[active_number]=activeform[active_number+1];
                 active_number=active_number-1;
                 fn=fn-1;
                 break;
                }
     
          }
         
     }


  if(form_number_fn!=-1)
  {
   for(i=1;i<active_number;i++)
    {
     if(activeform[i]==form_number_fn)
       {
          for(j=form_number_fn;j<fn;j++)
            {                   
              form[j].type= form[j+1].type;
              form[j].card= form[j+1].card; 
              form[j].topcard= form[j+1].topcard; 
              form[j].n= form[j+1].n;
              form[j].h= form[j+1].h;
              form[j].w= form[j+1].w;
              form[j].x= form[j+1].x;
              form[j].y= form[j+1].y;
              form[j].Focus_y= form[j+1].Focus_y;
              form[j].selected= form[j+1].selected;
              form[j].rselected= form[j+1].rselected;
              form[j].can_over= form[j+1].can_over;
              form[j].overed= form[j+1].overed;              
             } 
           take_break=1;                     
            }        
            if(take_break==1)
                {
                   for(j=i;j<active_number;j++)
                   activeform[active_number]=activeform[active_number+1];             
                active_number=active_number-1;
                fn=fn-1;
                break;
                }
  
          }
       }


}

//=============================================================================================
void hotkeys()
{
   int keyprsd;
   int i,j;

   if(keypressed())
    {
     keyprsd=readkey();
//     rectfill(screen,100,500,200,520,colour.white);
//     textprintf_ex(screen,font,100,500,154,-1,"%d  ",keyprsd);
     
    
   if (keyprsd==12032 && main_menu_sel_f==0 && global.show_menu==1)     //F1 key
     {
          menus_flag[1][0]=1;
          menu_select_F=1;
     
     }

   if (keyprsd==12288 && main_menu_sel_f==0 && global.show_menu==1)     //F2 key
     {
          menus_flag[0][0]=1;
          menu_select_F=1;
     
     }

   if(keyprsd==12288 && (global.menu_selected==14 || global.menu_selected==12 || global.menu_selected==11) )
   {
        if(cards_left==0)
        {
          i=global.menu_selected;
          remove_dialog();
          init_screen(0);
          global.cheat=1;  
          init_freecell();
          if(i==14)
             special_game1();
          if(i==12)
             special_game2();
          if(i==11)
            {
             global.cheat=2;
             alrand_deals(10897);

            }
          place_cards();
   
      }
   
   }

   if (keyprsd==12544 && main_menu_sel_f==0 && global.show_menu==1)     //F3 key
     {
          menus_flag[0][1]=1;
          menu_select_F=1;
     
     }
   if (keyprsd==12800 && main_menu_sel_f==0 && global.show_menu==1)     //F4 key
     {
          menus_flag[0][3]=1;
          menu_select_F=1;
     
     }
   if (keyprsd==13056 && main_menu_sel_f==0 && global.show_menu==1)     //F5 key
     {
          menus_flag[0][4]=1;
          menu_select_F=1;
     
     }

   if (keyprsd==14080 && settings.mplayer==1 && mplayer.active==0 && main_menu_sel_f==0 && global.show_menu==1)     //F9 key
     {
       mplayer.show=1;     
     }

   if (keyprsd==13824 && main_menu_sel_f==0 && global.show_menu==1 && global.colour_depth==2)     //F8 key
    {
     browser.show=1;
     browser.mode=2;
    }

   if (keyprsd==14336 && main_menu_sel_f==0 && show_undo==1 && global.show_menu==1)     //F10 key
     {
          menus_flag[0][5]=1;
          menu_select_F=1;
     
     }
   if (keyprsd==6144 && main_menu_sel_f==0 && global.show_menu==1)     //Alt-X key
     {
          menus_flag[0][6]=1;
          menu_select_F=1;
     
     }


       if (keyprsd==20992 && main_menu_sel_f==1)     //LEFT key
          {
            if(overed==2 && global.xtra_menu_active==1)
            keyprsd=2048;
            else
            keyprsd=1792;
          }
       if (keyprsd==21248 && main_menu_sel_f==1)     //RIGHT KEY
          {
            if(overed==0)
            keyprsd=2048;
            else if(global.xtra_menu_active==1)            
            keyprsd=1280;
           }

     if (keyprsd==1280 && form[2].selected==0 && global.show_menu==1 && global.xtra_menu_active==1)     //ALT-E
      {

        if(P_menu>=0)
        {
             buttons_related(dblbuffer,form[P_menu].x,form[P_menu].y,form[P_menu].x+form[P_menu].w,form[P_menu].y+form[P_menu].h,7);            
             blit(dblbuffer,screen,form[P_menu].x,form[P_menu].y,form[P_menu].x,form[P_menu].y,form[P_menu].w+1,form[P_menu].h+1);
             form[P_menu].can_over=1;
             form[P_menu].selected=0;
        }
        
       overed=2;
       buttons_related(dblbuffer,form[overed].x,form[overed].y,form[overed].x+form[overed].w,form[overed].y+form[overed].h,3);  
         blit(dblbuffer,screen,form[overed].x,form[overed].y,form[overed].x,form[overed].y,form[overed].w+1,form[overed].h+1);

       form[overed].selected=1;
       menuselected=3;
       main_menu_sel_f=1; 
       main_menu_selection();
       P_menu=overed;        

       form[fn-global.num_xtra_submenu].overed=1; 
       draw_submenu(active_number-global.num_xtra_submenu);


      }


     if (keyprsd==1792 && form[0].selected==0 && global.show_menu==1)     //ALT-G
      {
         if(P_menu>=0)
        {
             buttons_related(dblbuffer,form[P_menu].x,form[P_menu].y,form[P_menu].x+form[P_menu].w,form[P_menu].y+form[P_menu].h,7);            
             blit(dblbuffer,screen,form[P_menu].x,form[P_menu].y,form[P_menu].x,form[P_menu].y,form[P_menu].w+1,form[P_menu].h+1);
             form[P_menu].can_over=1;
             form[P_menu].selected=0;
        }

       overed=0;
       buttons_related(dblbuffer,form[overed].x,form[overed].y,form[overed].x+form[overed].w,form[overed].y+form[overed].h,3);  
         blit(dblbuffer,screen,form[overed].x,form[overed].y,form[overed].x,form[overed].y,form[overed].w+1,form[overed].h+1);
       form[overed].selected=1;
       menuselected=1;
       main_menu_sel_f=1; 
       main_menu_selection();
       P_menu=overed;        

       form[fn-7].overed=1; 
       draw_submenu(active_number-7);
      }

if (keyprsd==2048 && form[1].selected==0 && global.show_menu==1)          //ALT H
      {

        if(P_menu>=0)
        {
             buttons_related(dblbuffer,form[P_menu].x,form[P_menu].y,form[P_menu].x+form[P_menu].w,form[P_menu].y+form[P_menu].h,7);            
             blit(dblbuffer,screen,form[P_menu].x,form[P_menu].y,form[P_menu].x,form[P_menu].y,form[P_menu].w+1,form[P_menu].h+1);
             form[P_menu].can_over=1;
             form[P_menu].selected=0;
        }

       overed=1;
       buttons_related(dblbuffer,form[overed].x,form[overed].y,form[overed].x+form[overed].w,form[overed].y+form[overed].h,3);  
         blit(dblbuffer,screen,form[overed].x,form[overed].y,form[overed].x,form[overed].y,form[overed].w+1,form[overed].h+1);
       form[overed].selected=1;
       menuselected=2;
       main_menu_sel_f=1; 
       main_menu_selection();
       P_menu=overed;        

       form[fn-4].overed=1; 
       draw_submenu(active_number-4);


      }


     if(keyprsd==21760 && main_menu_sel_f==1)     //Down key
       {
        if(form[0].selected==1)
         {
           for(j=P_submenu;j<P_submenu+7;j++)
            {
             if(form[activeform[j]].overed==1 && form[activeform[j+1]].type==5)
              {
               if(form[activeform[j+1]].can_over==1)
                 {
                 i=activeform[j];
                 form[i+1].overed=1; 
                 draw_submenu(j+1);
                 }
                else
                 {
                 i=activeform[j];
                 form[i+2].overed=1; 
                 draw_submenu(j+2);
                 } 
                 break;
             }
           }
        }

      if(form[1].selected==1)
         {
           for(j=P_submenu;j<P_submenu+4;j++)
            {
             if(form[activeform[j]].overed==1 && form[activeform[j+1]].type==5)
              {
                 i=activeform[j];
                 form[i+1].overed=1; 
                 draw_submenu(j+1);
                 break;
             }
           }
        }
  
      if(form[2].selected==1 && global.xtra_menu_active==1)
         {
           for(j=P_submenu;j<P_submenu+global.num_xtra_submenu;j++)
            {
             if(form[activeform[j]].overed==1 && form[activeform[j+1]].type==5)
              {
                 i=activeform[j];
                 form[i+1].overed=1; 
                 draw_submenu(j+1);
                 break;
             }
           }
        }



       
      }
      

 
     if(keyprsd==21504 && main_menu_sel_f==1)     //UP key
       {
        if(form[0].selected==1)
         {
           for(j=P_submenu;j<P_submenu+7;j++)
            {
             if(form[activeform[j]].overed==1 && form[activeform[j-1]].type==5)
              {
               if(form[activeform[j-1]].can_over==1)
                 {
                 i=activeform[j];
                 form[i-1].overed=1; 
                 draw_submenu(j-1);
                 }
                else
                 {
                 i=activeform[j];
                 form[i-2].overed=1; 
                 draw_submenu(j-2);
                 } 
                 break;
             }
           }
        }
     if(form[1].selected==1)
         {
           for(j=P_submenu;j<P_submenu+4;j++)
            {
             if(form[activeform[j]].overed==1 && form[activeform[j-1]].type==5)
              {
                 i=activeform[j];
                 form[i-1].overed=1; 
                 draw_submenu(j-1);
                 break;
             }
           }
        }
 
     if(form[2].selected==1 && global.xtra_menu_active==1)
         {
           for(j=P_submenu;j<P_submenu+global.num_xtra_submenu;j++)
            {
             if(form[activeform[j]].overed==1 && form[activeform[j-1]].type==5)
              {
                 i=activeform[j];
                 form[i-1].overed=1; 
                 draw_submenu(j-1);
                 break;
             }
           }
        }
       
                   
      }
      
  if(keyprsd==17165 && main_menu_sel_f==1)     //ENTER key
       {
   
          for(j=P_submenu;j<P_submenu+7;j++)
            {
              if(form[activeform[j]].overed==1 && form[activeform[j]].type==5)
              {
                  if(form[2].selected==1) 
                       menus_flag[2][form[activeform[j]].n-422]=1;
                  if(form[1].selected==1) 
                       menus_flag[1][form[activeform[j]].n-412]=1;
                  if(form[0].selected==1) 
                       menus_flag[0][form[activeform[j]].n-402]=1;

                       menu_select_F=1;
                        break;
               }
             }

          keyprsd=15131;
       }

     if(keyprsd==3694 && form[0].selected==1)     //N key
      {
          menus_flag[0][0]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==4979 && form[0].selected==1)     //S key
      {
          menus_flag[0][1]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==4722 && form[0].selected==1 && show_restart==1)     //R key
      {
          menus_flag[0][2]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==5236 && form[0].selected==1)     //t key
      {
          menus_flag[0][3]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==3951 && form[0].selected==1)     //O key
      {
          menus_flag[0][4]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==5493 && form[0].selected==1 && show_undo==1)     //U key
      {
          menus_flag[0][5]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==6264 && form[0].selected==1)     //x key
      {
          menus_flag[0][6]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==2152 && form[1].selected==1)     //H key
      {
          menus_flag[1][0]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==867 && form[1].selected==1)     //C key
      {
          menus_flag[1][1]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==353 && form[1].selected==1)     //A key
      {
          menus_flag[1][2]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }
     if(keyprsd==610 && form[1].selected==1)     //b key
      {
          menus_flag[1][3]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }

     if(keyprsd==2152 && form[2].selected==1)     //h key
      {
          menus_flag[2][0]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }

     if(keyprsd==353 && form[2].selected==1)     //A key
      {
          menus_flag[2][1]=1;
          menu_select_F=1;
          keyprsd=15131;      
      }

   if(keyprsd==15131 && dialog_fn>0)
     {

            remove_dialog();
                 if(cards_left!=0)
                   global.show_game_select=0;  
                 if(cards_left==0)
                   global.show_game_select=1;  


     }

     if(keyprsd==15131 && main_menu_sel_f==1)     //ESC key
       {
            buttons_related(dblbuffer,form[overed].x,form[overed].y,form[overed].x+form[overed].w,form[overed].y+form[overed].h,7);            
             blit(dblbuffer,screen,form[overed].x,form[overed].y,form[overed].x,form[overed].y,form[overed].w+1,form[overed].h+1);
             form[overed].can_over=1;
             form[overed].selected=0;
             for(i=3;i<fn;i++)
              {
               if(form[overed].n==form[i].n )
               {
                 if(mouse1.x>=form[i].x && mouse1.y+mouse1.h>=form[i].y && mouse1.x+mouse1.w<=form[i].x+form[i].w && mouse1.y+mouse1.h<= form[i].y+form[i].h)
                      blit(temp,mouse_bg,mouse1.x+500-form[i].x,mouse1.y-form[i].y,0,0,mouse1.w,mouse1.h);

                 if(mouse1.x>=form[i].x && mouse1.y>=form[i].y && (mouse1.x+mouse1.w>form[i].x+form[i].w || mouse1.h+mouse1.y>form[i].y+form[i].h) )
                      blit(temp,mouse_bg,mouse1.x+500-form[i].x,mouse1.y-form[i].y,0,0,form[i].x+form[i].w+1-mouse1.x,form[i].y+form[i].h+1-mouse1.y);

                 if(mouse1.x+mouse1.w>=form[i].x && mouse1.y+mouse1.h>=form[i].y && mouse1.x<form[i].x && mouse1.y<=form[i].y+form[i].h)
                      blit(temp,mouse_bg,500,mouse1.y-form[i].y,form[i].x-mouse1.x,0,mouse1.x+mouse1.h-form[i].x,form[i].y+form[i].h+1-mouse1.y);                 

                   masked_blit(mouse,temp,0,0,mouse1.x+500-form[i].x,mouse1.y-form[i].y,mouse1.w,mouse1.h);
                   blit(temp,dblbuffer,500,0,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                   blit(dblbuffer,screen,form[i].x,form[i].y,form[i].x,form[i].y,form[i].w+1,form[i].h+1);
                   break; 
                }    
              
              }    
            if(form[overed].n==502)
               {
               for(i=402;i<=408;i++)
                delete_form(i,-1);           
               }

             if(form[overed].n==503)
               {
                for(i=412;i<=415;i++)
                  delete_form(i,-1);
               }              

            delete_form(form[overed].n,-1);
             main_menu_sel_f=0;
             do_mouse_over=1;
             P_menu=-1;
             overed=-1;
        }


   if(global.menu_selected==5)
     {
       j=(keyprsd & 0xff)-48;
         if(j>=0 && j<10 && ((settings.animation_speed*10+j)<200) && ((settings.animation_speed*10+j)>0) )
           {
            rect(form1,155+(cursor_pos_textbox*8),78,155+(cursor_pos_textbox*8),90,colour.white);
            settings.animation_speed=settings.animation_speed*10+j;
            textprintf_ex(form1,data[XSANS].dat,155,77,0,-1,"%d",settings.animation_speed);
            cursor_pos_textbox=cursor_pos_textbox+1;     
            rect(form1,155+(cursor_pos_textbox*8),78,155+(cursor_pos_textbox*8),90,0);
           }
         if(keyprsd==16136 && settings.animation_speed>0)
           {
           rectfill(form1,form[dialog_fn+5].x-form[dialog_fn].x+2,form[dialog_fn+5].y-form[dialog_fn].y+2,form[dialog_fn+5].x-form[dialog_fn].x+form[dialog_fn+5].w-2,form[dialog_fn+5].y-form[dialog_fn].y+form[dialog_fn+5].h-2,colour.white);
            settings.animation_speed=settings.animation_speed/10;
            if(settings.animation_speed!=0)
              textprintf_ex(form1,data[XSANS].dat,155,77,0,-1,"%d",settings.animation_speed);
            cursor_pos_textbox=cursor_pos_textbox-1;     
            rect(form1,155+(cursor_pos_textbox*8),78,155+(cursor_pos_textbox*8),90,0);
           }
          blit(form1,temp,form[dialog_fn+5].x-form[dialog_fn].x,form[dialog_fn+5].y-form[dialog_fn].y,600,500,form[dialog_fn+5].w,form[dialog_fn+5].h);
          blit(form1,mouse_bg,mouse1.Fx-form[dialog_fn].x,mouse1.Fy-form[dialog_fn].y,0,0,mouse1.w,mouse1.h); 
          masked_blit(mouse,temp,0,0,600+mouse1.Fx-form[dialog_fn+5].x,500+mouse1.Fy-form[dialog_fn+5].y,mouse1.w,mouse1.h);
          blit(temp,dblbuffer,600,500,form[dialog_fn+5].x,form[dialog_fn+5].y,form[dialog_fn+5].w,form[dialog_fn+5].h);       
          blit(dblbuffer,screen,form[dialog_fn+5].x,form[dialog_fn+5].y,form[dialog_fn+5].x,form[dialog_fn+5].y,form[dialog_fn+5].w,form[dialog_fn+5].h);       


      }


   if(global.menu_selected==2)
     {
       j=(keyprsd & 0xff)-48;
         if(j>=0 && j<10 && ((get_game_number*10+j)<32000) && ((get_game_number*10+j)>0) )
           {
            rect(form1,91+(cursor_pos_textbox*8),90,92+(cursor_pos_textbox*8),107,colour.white);
            get_game_number=get_game_number*10+j;
            textprintf_ex(form1,data[XSANS].dat,89,90,0,-1,"%d",get_game_number);
            cursor_pos_textbox=cursor_pos_textbox+1;     
            rect(form1,91+(cursor_pos_textbox*8),90,92+(cursor_pos_textbox*8),107,0);
           }
         if(keyprsd==16136 && get_game_number>0)
           {
           rectfill(form1,form[dialog_fn+4].x-form[dialog_fn].x+2,form[dialog_fn+4].y-form[dialog_fn].y+2,form[dialog_fn+4].x-form[dialog_fn].x+form[dialog_fn+4].w-2,form[dialog_fn+4].y-form[dialog_fn].y+form[dialog_fn+4].h-2,colour.white);
            get_game_number=get_game_number/10;
            if(get_game_number!=0)
            textprintf_ex(form1,data[XSANS].dat,89,90,0,-1,"%d",get_game_number);
            cursor_pos_textbox=cursor_pos_textbox-1;     
            rect(form1,91+(cursor_pos_textbox*8),90,92+(cursor_pos_textbox*8),107,0);


           }
          blit(form1,temp,form[dialog_fn+4].x-form[dialog_fn].x,form[dialog_fn+4].y-form[dialog_fn].y,600,500,form[dialog_fn+4].w,form[dialog_fn+4].h);
          blit(form1,mouse_bg,mouse1.Fx-form[dialog_fn].x,mouse1.Fy-form[dialog_fn].y,0,0,mouse1.w,mouse1.h); 
          masked_blit(mouse,temp,0,0,600+mouse1.Fx-form[dialog_fn+4].x,500+mouse1.Fy-form[dialog_fn+4].y,mouse1.w,mouse1.h);
          blit(temp,dblbuffer,600,500,form[dialog_fn+4].x,form[dialog_fn+4].y,form[dialog_fn+4].w,form[dialog_fn+4].h);       
          blit(dblbuffer,screen,form[dialog_fn+4].x,form[dialog_fn+4].y,form[dialog_fn+4].x,form[dialog_fn+4].y,form[dialog_fn+4].w,form[dialog_fn+4].h);            
      }
  }
}
