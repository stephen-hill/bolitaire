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


void draw_submenu(int j)
{
    int bg_color;
    int textcolor;
   if(P_submenu>0)
    {
        form[activeform[P_submenu]].overed=0;
        bg_color=colour.surface_grey;
        textcolor=0;
        draw_submenu_pictures(bg_color,textcolor,P_submenu);
    }
        bg_color=colour.item_selected;
        textcolor=colour.white;

    draw_submenu_pictures(bg_color,textcolor,j);
    P_submenu=j;

}

//===================================================================================================


void draw_submenu_pictures(int bg_color,int textcolor,int j)
{
    int x,ak;
    int x1,y1;
    x=20;
    ak=20;

    if(form[activeform[j]].n<412)
     {
 if(settings.fullscreen==1 || settings.status_bar==1)
         x1=3;
        else
         x1=0;
     }
    else if(form[activeform[j]].n<422)
      x1=45;
    else if(form[activeform[j]].n<432)  
      x1=88;
    
 if(settings.fullscreen==1 || settings.status_bar==1)
      y1=45;
     else
      y1=18;

blit(mouse_bg,temp,0,0,mouse1.x-x1,mouse1.y-y1,mouse1.w,mouse1.h);
rectfill(temp,form[activeform[j]].x-x1,form[activeform[j]].y-y1,form[activeform[j]].x-x1+form[activeform[j]].w-1,form[activeform[j]].y-y1+form[activeform[j]].h-1,bg_color);
//blit(temp,screen,0,0,300,45,170,200);               
//readkey();
    if( form[activeform[j]].n==402)
     {

          textprintf_ex(temp,data[XSANS].dat,x,4,textcolor,-1,"%s",menus[0][1]);
          textprintf_ex(temp,data[XSANS].dat,140,4,textcolor,-1,"%s","F2");
          line(temp,x-1,4+15,x+10,4+15,textcolor);
      }
     if( form[activeform[j]].n==403)
     {
//          textprintf_ex(screen,data[XSANS].dat,10,300,46,-1,"%d",form[activeform[j]].h);
          textprintf_ex(temp,data[XSANS].dat,x,4+ak,textcolor,-1,"%s",menus[0][2]);
          textprintf_ex(temp,data[XSANS].dat,140,4+ak,textcolor,-1,"%s","F3");
          line(temp,x,4+ak+15,x+8,4+ak+15,textcolor);


     }       
     if( form[activeform[j]].n==404)
     {
        textprintf_ex(temp,data[XSANS].dat,x,4+2*ak,textcolor,-1,"%s",menus[0][3]);
          line(temp,x-1,4+2*ak+15,x+10,4+2*ak+15,textcolor);
       }       
     if( form[activeform[j]].n==405)
     {
           textprintf_ex(temp,data[XSANS].dat,x,11+3*ak,textcolor,-1,"%s",menus[0][4]);
          textprintf_ex(temp,data[XSANS].dat,140,11+3*ak,textcolor,-1,"%s","F4");
          line(temp,x+8,11+3*ak+15,x+13,11+3*ak+15,textcolor);
 
     }       
     if( form[activeform[j]].n==406)
     {
          textprintf_ex(temp,data[XSANS].dat,x,11+4*ak,textcolor,-1,"%s",menus[0][5]);
          textprintf_ex(temp,data[XSANS].dat,140,11+4*ak,textcolor,-1,"%s","F5");
          line(temp,x,11+4*ak+15,x+8,11+4*ak+15,textcolor);
     }       
     if( form[activeform[j]].n==407)
     {
         textprintf_ex(temp,data[XSANS].dat,x,18+5*ak,textcolor,-1,"%s",menus[0][6]);
        textprintf_ex(temp,data[XSANS].dat,140,18+5*ak,textcolor,-1,"%s","F10");
        line(temp,x,18+5*ak+15,x+9,18+5*ak+15,textcolor);
 
     }       
      
     if( form[activeform[j]].n==408)
     {
        textprintf_ex(temp,data[XSANS].dat,x,25+6*ak,textcolor,-1,"%s",menus[0][7]);
        line(temp,x+9,25+6*ak+15,x+14,25+6*ak+15,textcolor);
 
     }       

     if( form[activeform[j]].n==412)
     {
          textprintf_ex(temp,data[XSANS].dat,x,4,textcolor,-1,"%s",menus[1][1]);
          textprintf_ex(temp,data[XSANS].dat,132,4,textcolor,-1,"%s","F1");
          line(temp,x-1,4+15,x+10,4+15,textcolor);   
 
     }
     if( form[activeform[j]].n==413)
     {
          textprintf_ex(temp,data[XSANS].dat,x,11+ak,textcolor,-1,"%s",menus[1][2]);
           line(temp,x,11+ak+15,x+9,11+ak+15,textcolor);   

     }
     if( form[activeform[j]].n==414)
     {
           textprintf_ex(temp,data[XSANS].dat,x,11+2*ak,textcolor,-1,"%s",menus[1][3]);
           line(temp,x-1,11+2*ak+15,x+9,11+2*ak+15,textcolor);   

     }
     if( form[activeform[j]].n==415)
     {
           textprintf_ex(temp,data[XSANS].dat,x,11+3*ak,textcolor,-1,"%s",menus[1][4]);
           line(temp,x+10,11+3*ak+15,x+16,11+3*ak+15,textcolor);   

     }

     if( form[activeform[j]].n==422)
     {
           textprintf_ex(temp,data[XSANS].dat,x,4,textcolor,-1,"%s",menus[2][1]);
           textprintf_ex(temp,data[XSANS].dat,184,4,textcolor,-1,"%s","F8");
           line(temp,x+10,4+15,x+16,4+15,textcolor);   

     }
     if( form[activeform[j]].n==423)
     {
           textprintf_ex(temp,data[XSANS].dat,x,4+ak,textcolor,-1,"%s",menus[2][2]);
          textprintf_ex(temp,data[XSANS].dat,184,4+ak,textcolor,-1,"%s","F9");
           line(temp,x+10,4+ak+15,x+16,4+ak+15,textcolor);   

     }


   blit(temp,mouse_bg,mouse1.x-x1,mouse1.y-y1,0,0,mouse1.w,mouse1.h);
   masked_blit(mouse,temp,0,0,mouse1.x-x1,mouse1.y-y1,mouse1.w,mouse1.h);
   blit(temp,dblbuffer,form[activeform[j]].x-x1,form[activeform[j]].y-y1,form[activeform[j]].x,form[activeform[j]].y,form[activeform[j]].w,form[activeform[j]].h);
   blit(dblbuffer,screen,form[activeform[j]].x,form[activeform[j]].y,form[activeform[j]].x,form[activeform[j]].y,form[activeform[j]].w,form[activeform[j]].h);
}
//=========================================================================================================================================
void do_submenu_options()
{
  int i,j;
  int color,color2;
  int r,g,b;
  

  if(menus_flag[0][6]==1)
      {
       if(cards_left==0)
          EXIT_PROGRAM=1;
      if(cards_left!=0)
         {
           menus_flag[0][0]=1;
           global.exit_program=1;
         }
          
       menus_flag[0][6]=0;
      }

  if(menus_flag[0][2]==1)
      {
       global.menu_selected=3;
       if(cards_left!=0)
         {
           menus_flag[0][0]=1;
           global.restart_same_game=1;
         }
       if(cards_left==0)
         {
           init_screen(0);
           init_freecell();
           if(settings.ms_deal==1)
              ms_deals(game_number);
           if(settings.alrand_deal==1)
              alrand_deals(game_number);
           place_cards();
         }
       menus_flag[0][2]=0;
      }


  if(menus_flag[0][1]==1)
      {
       if(cards_left!=0 && global.show_game_select==0)
         {
         menus_flag[0][0]=1;
         global.show_game_select=2;
         }
       if(global.show_game_select==1)
         {
           create_a_form(SCREEN_W/2-230/2,SCREEN_H/2-170/2,230,170);
           textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"Select Game");      
           textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"Select Game");     
           textprintf_ex(form1,data[XSANS].dat,40,40,0,-1,"Select a game number");         
           textprintf_ex(form1,data[XSANS].dat,65,56,0,-1,"from 1 to 32000");            
           buttons_related(form1,86,87,140,110,600+56); 
  
           rect(form1,91,90,92,107,0);
  
           ca_things(form1,"Ok",67,130,40,125,70,25,601); 
           ca_things(form1,"Cancel",132,130,120,125,70,25,601); 
           
           global.show_game_select=0;
           global.menu_selected=2;
           cursor_pos_textbox=0;
           get_game_number=0;

           form[fn].card=61;  // 61  means no card
           form[fn].w=54;
           form[fn].h=23;
           form[fn].x=form[dialog_fn].x+86;
           form[fn].y=form[dialog_fn].y+87;
           form[fn].type=11;  
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           form[fn].n=99;
           activeform[active_number]=fn;
           active_number=active_number+1;
           //form[fn].Focus_y=FOCUS_Y;
           fn=fn+1; 


    blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
    blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
    masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         

         }

         menus_flag[0][1]=0;
      }
 

    if(menus_flag[0][0]==1)
      {
       if(cards_left!=0)
        {
           global.menu_selected=1;
           create_a_form(SCREEN_W/2-320/2,SCREEN_H/2-110/2,320,110);
           textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"Bolitaire");      
           textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"Bolitaire");     
           textprintf_ex(form1,data[XSANS].dat,20,40,0,-1,"Are you sure you want to quit this game?");
           ca_things(form1,"YES",106,75,80,70,75,25,601); 
           ca_things(form1,"NO",194,75,165,70,75,25,601); 
   
           blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
           blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
           blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
           blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
           masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
           blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         

       }


       if(cards_left==0)
        {
       init_screen(0);
       init_freecell();
       game_number=rand()%32000;
       if(settings.ms_deal==1)
          ms_deals(game_number);
       if(settings.alrand_deal==1)
          alrand_deals(game_number);
       place_cards();
       form[0].can_over=1;
       form[1].can_over=1;
       overed=0;
       show_restart=1;
       }
       menus_flag[0][0]=0;
      }

    if(menus_flag[0][3]==1)
      {
        global.menu_selected=4;
        create_a_form(SCREEN_W/2-280/2,SCREEN_H/2-310/2,280,310);
        textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"Statistics");      
        textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"Statistics");     

      textprintf_ex(form1,data[XSANS].dat,20,36,0,-1,"This session");    
      if(curr_win+curr_loss !=0)
        textprintf_ex(form1,data[XSANS].dat,220,36,0,-1,"%d",(curr_win*100)/(curr_win+curr_loss));
       else                                
        textprintf_ex(form1,data[XSANS].dat,220,36,0,-1,"%d",0);

      textprintf_ex(form1,data[XSANS].dat,240,36,0,-1,"%s","%");    
      
      textprintf_ex(form1,data[XSANS].dat,77,53,0,-1,"won:");    
      textprintf_ex(form1,data[XSANS].dat,170,53,0,-1,"%d",curr_win);      
      textprintf_ex(form1,data[XSANS].dat,77,71,0,-1,"lost:");                
      textprintf_ex(form1,data[XSANS].dat,170,71,0,-1,"%d",curr_loss);      

      textprintf_ex(form1,data[XSANS].dat,20,110,0,-1,"Total"); 
      if(statistics.total_win+statistics.total_loss !=0)   
        textprintf_ex(form1,data[XSANS].dat,220,110,0,-1,"%d",( statistics.total_win*100)/(statistics.total_win+statistics.total_loss));      
       else
        textprintf_ex(form1,data[XSANS].dat,220,110,0,-1,"%d",0);             
       
      textprintf_ex(form1,data[XSANS].dat,240,110,0,-1,"%s","%");    
      textprintf_ex(form1,data[XSANS].dat,77,128,0,-1,"won:");  
      textprintf_ex(form1,data[XSANS].dat,170,128,0,-1,"%d",statistics.total_win);         
      textprintf_ex(form1,data[XSANS].dat,77,146,0,-1,"lost:");   
      textprintf_ex(form1,data[XSANS].dat,170,146,0,-1,"%d",statistics.total_loss);                      

      textprintf_ex(form1,data[XSANS].dat,20,185,0,-1,"Streaks");    
      textprintf_ex(form1,data[XSANS].dat,77,203,0,-1,"wins:");  
      textprintf_ex(form1,data[XSANS].dat,170,203,0,-1,"%d",statistics.win_streak);         
      textprintf_ex(form1,data[XSANS].dat,77,221,0,-1,"losses:");                
      textprintf_ex(form1,data[XSANS].dat,170,221,0,-1,"%d",statistics.loss_streak);       
      textprintf_ex(form1,data[XSANS].dat,77,239,0,-1,"current:");                
      textprintf_ex(form1,data[XSANS].dat,170,239,0,-1,"%d",statistics.curr_streak);       
      
      ca_things(form1,"Ok",130,275,100,270,80,25,601); 

    blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
    blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
    masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         
    menus_flag[0][3]=0;
      }

   if(menus_flag[0][4]==1)
      {
        create_a_form(SCREEN_W/2-228/2,SCREEN_H/2-155/2,228,155);        
          line(form1,5,85,130,85,colour.dark_grey_boundry);
          line(form1,6,86,131,86,colour.white);

          line(form1,130,84,130,56,colour.dark_grey_boundry);
          line(form1,131,85,131,55,colour.white);

          line(form1,130,55,221,55,colour.dark_grey_boundry);
          line(form1,131,56,222,56,colour.white);

        textprintf_ex(form1,data[XSANS].dat,135,57,colour.white,-1,"speed(1-200):");
           buttons_related(form1,152,75,197,93,600+56); 
        textprintf_ex(form1,data[XSANS].dat,155,77,0,-1,"%d",settings.animation_speed);

          if(settings.animation_speed<10)
             cursor_pos_textbox=1;
          else if(settings.animation_speed<100)
             cursor_pos_textbox=2;
          else if(settings.animation_speed<1000)
             cursor_pos_textbox=3;
                       
           rect(form1,155+cursor_pos_textbox*8,78,155+cursor_pos_textbox*8,90,0);


        textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"Options");      
        textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"Options");     

      if(settings.animation==1)
        buttons_related(form1,15,96,27,108,657);
       else
        buttons_related(form1,15,96,27,108,656);

          if(settings.ms_deal==1)
             {
               buttons_related(form1,15,38,27,50,654);
               buttons_related(form1,15,64,27,76,655);
             }
          if(settings.alrand_deal==1) 
             {
               buttons_related(form1,15,38,27,50,655);
               buttons_related(form1,15,64,27,76,654);
             }

        textprintf_ex(form1,data[XSANS].dat,37,36,0,-1,"MS Freecell Deals");        
        textprintf_ex(form1,data[XSANS].dat,37,62,0,-1,"Alrand Deals");           
        textprintf_ex(form1,data[XSANS].dat,37,94,0,-1,"Animation(card movement)"); 


          global.menu_selected=5;
           form[fn].card=61;  // 61  means no card
           form[fn].w=205;
           form[fn].h=24;
           form[fn].x=form[dialog_fn].x+8;
           form[fn].y=form[dialog_fn].y+32;
           form[fn].type=11;  // Special number for forms
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           form[fn].n=99;
           activeform[active_number]=fn;
           active_number=active_number+1;
           fn=fn+1; 
           

          form[fn].card=61;  // 61  means no card
           form[fn].w=120;
           form[fn].h=24;
           form[fn].x=form[dialog_fn].x+8;
           form[fn].y=form[dialog_fn].y+58;
           form[fn].type=11;  // Special number for forms
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           form[fn].n=99;
           activeform[active_number]=fn;
           active_number=active_number+1;
           fn=fn+1; 
         form[fn].card=61;  // 61  means no card 
           form[fn].w=205;
           form[fn].h=18;
           form[fn].x=form[dialog_fn].x+8;
           form[fn].y=form[dialog_fn].y+94;
           form[fn].type=11;  // Special number for forms
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           form[fn].n=99;
           activeform[active_number]=fn;
           active_number=active_number+1;
           fn=fn+1; 

         form[fn].card=61;  // 61  means no card 
           form[fn].w=45;
           form[fn].h=18;
           form[fn].x=form[dialog_fn].x+152;
           form[fn].y=form[dialog_fn].y+75;
           form[fn].type=11;  // Special number for forms
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           form[fn].n=99;
           activeform[active_number]=fn;
           active_number=active_number+1;
           fn=fn+1; 

       if(global.colour_depth!=1)
       {
         form[fn].card=61;  // 61  means no card 
           form[fn].w=205;
           form[fn].h=18;
           form[fn].x=form[dialog_fn].x+8;
           form[fn].y=form[dialog_fn].y+112;
           form[fn].type=11;  // Special number for forms
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           form[fn].n=99;
           activeform[active_number]=fn;
           active_number=active_number+1;
           fn=fn+1; 

      temp_background=settings.background;
      if(settings.background==0)
        buttons_related(form1,15,116,27,128,657);
       else
        buttons_related(form1,15,116,27,128,656);
      
        textprintf_ex(form1,data[XSANS].dat,37,114,0,-1,"No background*"); 
        textprintf_ex(form1,data[XSANS].dat,13,136,0,-1,"*");         
        textprintf_ex(form1,data[XSANS].dat,27,133,0,-1,"start new game to see effect");         
       }
     else
       {
      if(settings.background==0)
        buttons_related(form1,15,116,27,128,657);
       else
        buttons_related(form1,15,116,27,128,656);

        textprintf_ex(form1,data[XSANS].dat,37,114,colour.dark_grey_boundry,-1,"No background*"); 
        textprintf_ex(form1,data[XSANS].dat,38,115,colour.white,-1,"No background*"); 
        textprintf_ex(form1,data[XSANS].dat,13,136,0,-1,"*");         
        textprintf_ex(form1,data[XSANS].dat,27,133,0,-1,"start new game to see effect");         
       }
     
    blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
    blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
    masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         

         menus_flag[0][4]=0;
       }

   if(menus_flag[0][5]==1)    //Undo
      {
       menus_flag[0][5]=0;
      }


 
   if(menus_flag[1][0]==1)
      {

        create_a_form(SCREEN_W/2-390/2,SCREEN_H/2-340/2,390,340);
        textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"Help");      
        textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"Help");     



      buttons_related(form1,8,30,380,330,656);
      rectfill(form1,10,32,378,328,colour.white);

        i=45;
        j=17;

        textprintf_ex(form1,data[XSANS].dat,18,i,0,-1,"Object of the game");
        textprintf_ex(form1,data[XSANS].dat,18+1,i,0,-1,"Object of the game");
        textprintf_ex(form1,data[XSANS].dat,18,i+j,0,-1,"You must move all the cards to the home cells(cells"); 
        textprintf_ex(form1,data[XSANS].dat,18,i+2*j,0,-1,"that are right side of the king) using free cells");        
        textprintf_ex(form1,data[XSANS].dat,18,i+3*j,0,-1,"(cells that are left side of the king).");
        i=i+25+4*j;
        j=17;

        textprintf_ex(form1,data[XSANS].dat,18,i,0,-1,"Playing the game");
        textprintf_ex(form1,data[XSANS].dat,18+1,i,0,-1,"Playing the game");
        textprintf_ex(form1,data[XSANS].dat,18,i+j,0,-1,"To move a(or group of) card click a card, then click"); 
        textprintf_ex(form1,data[XSANS].dat,18,i+2*j,0,-1,"where mouse turns into a arrow. To de-select the");
        textprintf_ex(form1,data[XSANS].dat,18,i+3*j,0,-1,"card, click the card again.");   
        
        i=i+25+4*j;
        j=17;
        textprintf_ex(form1,data[XSANS].dat,18,i,0,-1,"Note");
        textprintf_ex(form1,data[XSANS].dat,18+1,i,0,-1,"Note");
        textprintf_ex(form1,data[XSANS].dat,18,i+j,0,-1,"Use Alt + X to immediatly terminate the program."); 
        textprintf_ex(form1,data[XSANS].dat,18,i+2*j,0,-1,"When you terminate the program with a incomplete");
        textprintf_ex(form1,data[XSANS].dat,18,i+3*j,0,-1,"game then it will be taken as loss on the next");
        textprintf_ex(form1,data[XSANS].dat,18,i+4*j,0,-1,"instance when the program is run.");   

    blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
    blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
    masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         
    menus_flag[1][0]=0;
      }

   if(menus_flag[1][1]==1)
      {
    global.menu_selected=11;
         create_a_form(SCREEN_W/2-412/2,SCREEN_H/2-290/2,412,290);
        textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"Credits");      
        textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"Credits");     

  color=getpixel(data[XLOGO_BW].dat,43,23);
  color2=getpixel(data[XLOGO_BW].dat,0,0);

  for(i=0;i<120;i++)
   {
    for(j=0;j<60;j++)
     {
       if(color2==getpixel(data[XLOGO_BW].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.transperent);
       if(color==getpixel(data[XLOGO_BW].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.light_grey_boundry);
     }
   }
  for(j=0;j<6;j++)
    {
   for(i=0;i<4;i++)
     {
      if(j%2==0)
        masked_blit(buffer,form1,500,300,i*130-65,30+j*70,120,60);
      if(j%2==1)
        masked_blit(buffer,form1,500,300,5+i*130,30+j*70,120,60);


     }
    }

        i=38;
        j=17;

      textprintf_ex(form1,data[XSANS].dat,13,i,makecol(0,40,192),-1,"Thanks to");
      textprintf_ex(form1,data[XSANS].dat,13+72,i,makecol(248,96,88),-1,"RayBrujo");
      textprintf_ex(form1,data[XSANS].dat,14+72,i,makecol(248,96,88),-1,"RayBrujo");
      textprintf_ex(form1,data[XSANS].dat,13+145,i,makecol(0,40,192),-1,"for the windows rand() function code.");
      
      textprintf_ex(form1,data[XSANS].dat,13,i+j,makecol(0,40,192),-1,"Thanks to");
      textprintf_ex(form1,data[XSANS].dat,13+72,i+j,makecol(248,96,88),-1,"Jim horne");
      textprintf_ex(form1,data[XSANS].dat,14+72,i+j,makecol(248,96,88),-1,"Jim horne");
      textprintf_ex(form1,data[XSANS].dat,13+145,i+j,makecol(0,40,192),-1,"for the code to generate ms deals.");

      textprintf_ex(form1,data[XSANS].dat,13,i+2*j,makecol(0,40,192),-1,"Thanks to");
      textprintf_ex(form1,data[XSANS].dat,13+72,i+2*j,makecol(248,96,88),-1,"Fladimir da Gorf");
      textprintf_ex(form1,data[XSANS].dat,14+72,i+2*j,makecol(248,96,88),-1,"Fladimir da Gorf");
      textprintf_ex(form1,data[XSANS].dat,13+187,i+2*j,makecol(0,40,192),-1,"for helping with scroll bar.");

      textprintf_ex(form1,data[XSANS].dat,13,i+3*j,makecol(0,40,192),-1,"Thanks to");
      textprintf_ex(form1,data[XSANS].dat,13+72,i+3*j,makecol(248,96,88),-1,"kazzmir, Evert, lillo.");
      textprintf_ex(form1,data[XSANS].dat,14+72,i+3*j,makecol(248,96,88),-1,"kazzmir, Evert, lillo.");

        i=i+12+4*j;
        j=17;

      textprintf_ex(form1,data[XSANS].dat,14,i,makecol(0,128,128),-1,"Thanks to the developers of allegro, dev-cpp, alrand,");
      textprintf_ex(form1,data[XSANS].dat,14,i+j,makecol(0,128,128),-1,"jpgalleg, freedos, cwsdpmi, card pictures, gcc,");
      textprintf_ex(form1,data[XSANS].dat,14,i+2*j,makecol(0,128,128),-1,"image forge, linux, djgpp and those I left :-)");

      i=i+12+3*j;
      j=17;

      textprintf_ex(form1,data[XSANS].dat,14,i,makecol(40,104,0),-1,"Thanks to those who reported bugs, comments and those");
      textprintf_ex(form1,data[XSANS].dat,14,i+j,makecol(40,104,0),-1,"who enjoyed using this program.");

       i=i+12+2*j;
  
      textprintf_ex(form1,data[XSANS].dat,14,i,makecol(0,128,128),-1,"This software is dedicated to my brother M. Ravi shankar");
      textprintf_ex(form1,data[XSANS].dat,14,i+j,makecol(0,128,128),-1,"and his two year old son R. Varun chand, also dedicated");
      textprintf_ex(form1,data[XSANS].dat,14,i+2*j,makecol(0,128,128),-1,"to my mother and father, and all of my family members.");


    blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
    blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
    masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         

       menus_flag[1][1]=0;
      }
   if(menus_flag[1][2]==1)
      {
    global.menu_selected=12;
         create_a_form(SCREEN_W/2-380/2,SCREEN_H/2-296/2,380,296);
        textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"About Bolitaire");      
        textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"About Bolitaire");     

  color=getpixel(data[XLOGO_BW].dat,43,23);
  color2=getpixel(data[XLOGO_BW].dat,0,0);

  for(i=0;i<120;i++)
   {
    for(j=0;j<60;j++)
     {
       if(color2==getpixel(data[XLOGO_BW].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.transperent);
       if(color==getpixel(data[XLOGO_BW].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.light_grey_boundry);
     }
   }
  for(j=0;j<4;j++)
    {
   for(i=0;i<4;i++)
     {
      if(j%2==0)
        masked_blit(buffer,form1,500,300,i*130-65,30+j*70,120,60);
      if(j%2==1)
        masked_blit(buffer,form1,500,300,5+i*130,30+j*70,120,60);

     }
    }

      buttons_related(form1,14,34,136,96,605);
      blit(data[XLOGO_C].dat,form1,0,0,15,35,120,60);
        i=38;
        j=18;

      textprintf_ex(form1,data[XSANS].dat,145,i,makecol(248,96,88),-1,"Yzone Software:");
      textprintf_ex(form1,data[XSANS].dat,145+1,i,makecol(248,96,88),-1,"Yzone Software:");      
      textprintf_ex(form1,data[XSANS].dat,145+115,i,makecol(0,40,192),-1,"An identification");             
      textprintf_ex(form1,data[XSANS].dat,145,i+j,makecol(0,40,192),-1,"under which I publish my software.");  
      textprintf_ex(form1,data[XSANS].dat,145,i+2*j,makecol(0,40,192),-1,"It was founded on july 14 2003.");  
//      textprintf_ex(form1,data[XSANS].dat,145,i+3*j,makecol(248,96,88),-1,"  http://yzonesoft.buildtolearn.net");  
      j=17;
      i=115;

         textprintf_ex(form1,data[XSANS].dat,32,i,makecol(152,104,0),-1,"Bolitaire");  
         textprintf_ex(form1,data[XSANS].dat,32+1,i,makecol(152,104,0),-1,"Bolitaire");  
         textprintf_ex(form1,data[XSANS].dat,32+60,i,makecol(0,128,128),-1,"is a freecell clone made for DOS and"); 
         textprintf_ex(form1,data[XSANS].dat,32,i+j,makecol(0,128,128),-1,"ported to Linux, BeOS and Windows, it can be");
         textprintf_ex(form1,data[XSANS].dat,32,i+2*j,makecol(0,128,128),-1,"also made bootable. Version 0.62a and greater");
         textprintf_ex(form1,data[XSANS].dat,32,i+3*j,makecol(0,128,128),-1,"contains a nice mp3 player made for DOS.");           
         textprintf_ex(form1,data[XSANS].dat,32,i+4*j,makecol(0,128,128),-1,"Enjoy!");           
      j=17;
      i=i+5*j+15;

         textprintf_ex(form1,data[XSANS].dat,32,i,makecol(40,104,0),-1,"Any comments and bug reports are welcome.");
         textprintf_ex(form1,data[XSANS].dat,32,i+j,makecol(40,104,0),-1,"E-mail it to me at yzonesoft@yahoo.com");           
         textprintf_ex(form1,data[XSANS].dat,32,i+2*j,makecol(40,104,0),-1,"visit http://yzonesoft.buildtolearn.net for future");           
         textprintf_ex(form1,data[XSANS].dat,32,i+3*j,makecol(40,104,0),-1,"updates and other software.");           

    blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
    blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
    masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         
    menus_flag[1][2]=0;
      }
   if(menus_flag[1][3]==1)
      {
    global.menu_selected=14;
         create_a_form(SCREEN_W/2-420/2,SCREEN_H/2-200/2,420,200);
        textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"About Author");      
        textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"About Author");     

  color=getpixel(data[XLOGO_BW].dat,43,23);
  color2=getpixel(data[XLOGO_BW].dat,0,0);

  for(i=0;i<120;i++)
   {
    for(j=0;j<60;j++)
     {
       if(color2==getpixel(data[XLOGO_BW].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.transperent);
       if(color==getpixel(data[XLOGO_BW].dat,i,j))
           putpixel(buffer,500+i,300+j,colour.light_grey_boundry);
     }
   }
  for(j=0;j<6;j++)
    {
   for(i=0;i<4;i++)
     {
      if(j%2==0)
        masked_blit(buffer,form1,500,300,i*130-65,30+j*70,120,60);
      if(j%2==1)
        masked_blit(buffer,form1,500,300,5+i*130,30+j*70,120,60);


     }
    }
      buttons_related(form1,14,34,176,156,605);
      blit(data[YOGESH].dat,form1,0,0,15,35,160,120);
         i=38;
         j=19;
         textprintf_ex(form1,data[XSANS].dat,190,i,makecol(48,166,0),-1,"NAME:");  
             textprintf_ex(form1,data[XSANS].dat,190+60,i,makecol(248,96,88),-1,"Yogesh M");  
             textprintf_ex(form1,data[XSANS].dat,191+60,i,makecol(248,96,88),-1,"Yogesh M");  
         textprintf_ex(form1,data[XSANS].dat,190,i+j,makecol(184,128,248),-1,"SEX:");  
             textprintf_ex(form1,data[XSANS].dat,190+60,i+j,makecol(184,128,248),-1,"M");  
         textprintf_ex(form1,data[XSANS].dat,190,i+2*j,makecol(248,232,16),-1,"D.O.B:");  
             textprintf_ex(form1,data[XSANS].dat,190+60,i+2*j,makecol(248,232,16),-1,"18/08/1983");  
         textprintf_ex(form1,data[XSANS].dat,190,i+3*j,makecol(0,40,192),-1,"UG:");  
             textprintf_ex(form1,data[XSANS].dat,190+60,i+3*j,makecol(0,40,192),-1,"B.E. Elect & Instru");  
         textprintf_ex(form1,data[XSANS].dat,190,i+4*j,makecol(72,232,248),-1,"E-mail:");                    
             textprintf_ex(form1,data[XSANS].dat,190+60,i+4*j,makecol(72,232,248),-1,"yzonesoft@yahoo.com");                    
         textprintf_ex(form1,data[XSANS].dat,190,i+5*j,makecol(152,104,0),-1,"YM!:");  
             textprintf_ex(form1,data[XSANS].dat,190+60,i+5*j,makecol(152,104,0),-1,"streatcat99");  
         j=17;
         i=170;
         textprintf_ex(form1,data[XSANS].dat,32,i,makecol(0,128,128),-1,"Yep, this is me, showing my face to digital cam.");  

    blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
    blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
    masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         
    menus_flag[1][3]=0;
      }

   if(menus_flag[2][0]==1)
      {
       menus_flag[2][0]=0;
       if(global.colour_depth==2 && settings.background==1)
       {
        browser.show=1;
        browser.mode=2;
       }
       else
       mplayer.show=1;
      }
   if(menus_flag[2][1]==1)
      {
       menus_flag[2][1]=0;
       mplayer.show=1;
      }


  menu_select_F=0;
}

//=============================================================================================================
void show_card_movement_on_screen(int z,int x,int y)
{
// x,y is the destination where to put the card on the screen
int x1,y1;
int xc,yc;
int speedx; //(animation speed)
int speedy;
int i,j;
float m;
float c;
float ffx1,ffy1,ffy2,ffx2;
ffx1=x;
ffy1=y;
ffx2=form[z].x;
ffy2=form[z].y;

  form1=create_bitmap(form[z].w,form[z].h); 
  form2=create_bitmap(form[z].w,form[z].h); 
  if(global.cheat==2)
    blit(data[52].dat,form1,0,0,0,0,form[z].w,form[z].h);
   else
    blit(data[form[z].card].dat,form1,0,0,0,0,form[z].w,form[z].h);
  if(form[z].topcard==0)
    blit(background,form2,form[z].x,form[z].y,0,0,form[z].w,form[z].h);
  else
   {
    previous_card(z);
    if(Prev_card==-1)
        blit(background,form2,form[z].x,form[z].y,0,0,form[z].w,form[z].h);
    else
    {
      blit(background,form2,form[z].x,form[z].y,0,0,form[z].w,form[z].h);
      masked_blit(data[form[Prev_card].card].dat,form2,0,0,0,-18,form[z].w,form[z].h);     
    }
   }

    x1=x-form[z].x;
    if(x1<0)
      x1=-x1;
    y1=y-form[z].y;
    if(y1<0)
      y1=-y1;
    m=(ffy1-ffy2)/(ffx1-ffx2);
    c=ffy1-(m*ffx1);


    if(x1>=y1)
      {
       if(settings.animation==1)
        {
          speedx=settings.animation_speed;
        }  
        else
          speedx=800;  
       xc=form[z].x;
       x1=x-form[z].x;
       y1=y-form[z].y;

     if(x1<0)
       {
       while(xc > (x-1))
         {

          draw_mouse();
          xc=xc-speedx;
          yc=m*xc+c;  

          if(xc<x+speedx)
           {
            xc=x;
            yc=y;
          speedx=form[z].x-xc;
            }


        if(y1<=0)
          {
          speedy=form[z].y-yc;
          blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h); 
          blit(form2,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
          blit(dblbuffer,form2,xc,yc,0,0,form[z].w,form[z].h);
          masked_blit(form1,dblbuffer,0,0,xc,yc,form[z].w,form[z].h);
//           if(mouse1.x>=xc-mouse1.w && mouse1.y>=yc-mouse1.h && mouse1.x<xc+form[z].w+speedx && mouse1.y< yc+form[z].h+speedy)
              masked_blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h); 
          masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
          blit(dblbuffer,screen,xc,yc,xc,yc,form[z].w+speedx,form[z].h+speedy);         
           }
           if(y1>0)
             {
                speedy=yc-form[z].y;
                blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h); 
                blit(form2,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                blit(dblbuffer,form2,xc,yc,0,0,form[z].w,form[z].h);
                masked_blit(form1,dblbuffer,0,0,xc,yc,form[z].w,form[z].h);
//                if(mouse1.x>=xc-mouse1.w && mouse1.y>=yc-speedy-mouse1.h && mouse1.x<xc+form[z].w+speedx && mouse1.y< yc+form[z].h)
                   masked_blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h); 
                masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                blit(dblbuffer,screen,xc,yc-speedy,xc,yc-speedy,form[z].w+speedx,form[z].h+speedy);         
             }
           
         form[z].y=yc;
         form[z].x=xc;
         if(xc<=x)
           break;

          }

       }
     if(x1>0)
       {
       while(xc < x)
         {

          draw_mouse();
          xc=xc+speedx;
          yc=m*xc+c;  
          if(xc>x-speedx)
           {
            xc=x;
            yc=y;
          speedx=xc-form[z].x;
            }

     if(y1<=0)
       {
          speedy=form[z].y-yc;
                blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h); 
                blit(form2,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                blit(dblbuffer,form2,xc,yc,0,0,form[z].w,form[z].h);
                masked_blit(form1,dblbuffer,0,0,xc,yc,form[z].w,form[z].h);
//                if(mouse1.x>=xc-mouse1.w && mouse1.y>=yc-speedy-mouse1.h && mouse1.x<xc+form[z].w+speedx && mouse1.y< yc+form[z].h)
                   masked_blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h); 
                masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
          blit(dblbuffer,screen,xc-speedx,yc,xc-speedx,yc,form[z].w+speedx,form[z].h+speedy);         
           }
           if(y1>0)
            {
          speedy=yc-form[z].y;
                blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h); 
                blit(form2,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                blit(dblbuffer,form2,xc,yc,0,0,form[z].w,form[z].h);
                masked_blit(form1,dblbuffer,0,0,xc,yc,form[z].w,form[z].h);
 //               if(mouse1.x>=xc-mouse1.w && mouse1.y>=yc-speedy-mouse1.h && mouse1.x<xc+form[z].w+speedx && mouse1.y< yc+form[z].h)
                   masked_blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h); 
                masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
            blit(dblbuffer,screen,xc-speedx,yc-speedy,xc-speedx,yc-speedy,form[z].w+speedx,form[z].h+speedy);         
            }
           

         form[z].y=yc;
         form[z].x=xc;
         if(xc>=x)
           break;
         }
     }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
else if(y1>x1)
{
//textprintf_ex(screen,font,100,0,45673,-1,"%f %f %d",m,c,y);
 if(settings.animation==1)
  {
   speedy=settings.animation_speed;
  }  
 else
  speedy=800;  
 yc=form[z].y;
 x1=x-form[z].x;
 y1=y-form[z].y;
 if(y1<0)
   {
       while(yc>y)
         {

          draw_mouse();
          yc=yc-speedy;
          xc=(yc-c)/m;  

          if(yc<y+speedy)
           {
            xc=x;
            yc=y;
            speedy=form[z].y-yc;
           }


           if(x1<=0)
             {
                speedx=form[z].x-xc;
                blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h); 
                blit(form2,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                blit(dblbuffer,form2,xc,yc,0,0,form[z].w,form[z].h);
                masked_blit(form1,dblbuffer,0,0,xc,yc,form[z].w,form[z].h);
//                if(mouse1.x>=xc-mouse1.w && mouse1.y>=yc-speedy-mouse1.h && mouse1.x<xc+form[z].w+speedx && mouse1.y< yc+form[z].h)
                   masked_blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h); 
                masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                blit(dblbuffer,screen,xc,yc,xc,yc,form[z].w+speedx,form[z].h+speedy);         
             }
             
           if(x1>0)
             {             
                speedx=xc-form[z].x;
                blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h); 
                blit(form2,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                blit(dblbuffer,form2,xc,yc,0,0,form[z].w,form[z].h);
                masked_blit(form1,dblbuffer,0,0,xc,yc,form[z].w,form[z].h);
//                if(mouse1.x>=xc-mouse1.w && mouse1.y>=yc-speedy-mouse1.h && mouse1.x<xc+form[z].w+speedx && mouse1.y< yc+form[z].h)
                   masked_blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h); 
                masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                blit(dblbuffer,screen,xc-speedx,yc,xc-speedx,yc,form[z].w+speedx,form[z].h+speedy);         
              }     
         form[z].y=yc;
         form[z].x=xc;
         if(yc<=y)
           break;

         }

   }

 else if(y1>0)
   {
       while(yc < y)
         {

          draw_mouse();
          yc=yc+speedy;
          xc=(yc-c)/m;  

          if(yc>y-speedy)
           {
            xc=x;
            yc=y;                       
            speedy=yc-form[z].y;
            }
 
           if(x1>=0)
            {
            speedx=xc-form[z].x;
                blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h); 
                blit(form2,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                blit(dblbuffer,form2,xc,yc,0,0,form[z].w,form[z].h);
                masked_blit(form1,dblbuffer,0,0,xc,yc,form[z].w,form[z].h);
//                if(mouse1.x>=xc-mouse1.w && mouse1.y>=yc-speedy-mouse1.h && mouse1.x<xc+form[z].w+speedx && mouse1.y< yc+form[z].h)
                   masked_blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h); 
                masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
            blit(dblbuffer,screen,xc-speedx,yc-speedy,xc-speedx,yc-speedy,form[z].w+speedx,form[z].h+speedy);         
            }

           if(x1<0)
             {
                speedx=form[z].x-xc;
                 blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h); 
                blit(form2,dblbuffer,0,0,form[z].x,form[z].y,form[z].w,form[z].h);
                blit(dblbuffer,form2,xc,yc,0,0,form[z].w,form[z].h);
                masked_blit(form1,dblbuffer,0,0,xc,yc,form[z].w,form[z].h);
//                if(mouse1.x>=xc-mouse1.w && mouse1.y>=yc-speedy-mouse1.h && mouse1.x<xc+form[z].w+speedx && mouse1.y< yc+form[z].h)
                   masked_blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h); 
                masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
                blit(dblbuffer,screen,xc,yc-speedy,xc,yc-speedy,form[z].w+speedx,form[z].h+speedy);         
             }






            form[z].y=yc;
            form[z].x=xc;
           if(yc>=y)
             break;
       }

 


   }


}
  destroy_bitmap(form1); 
  destroy_bitmap(form2); 

}
//======================================================================================
