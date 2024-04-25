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

void create_a_form(int x,int y,int w,int h)
{

  form1=create_bitmap(w,h); 
  form2=create_bitmap(w,h); 
  global.show_king=0;
  global.show_menu=0;  

           dialog_fn=fn;
           form[fn].card=61;  // 61  means no card
           form[fn].w=w;
           form[fn].h=h;
           form[fn].x=x;
           form[fn].y=y;
           form[fn].type=11;  // Special number for forms
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           fn=fn+1; 
           

          form[fn].card=61;   // This is for EXIT BUTTON
           form[fn].w=16;
           form[fn].h=14;
           form[fn].x=x+w-20;
           form[fn].y=y+5;
           form[fn].type=-1; 
           form[fn].selected=0;
           form[fn].rselected=0;
           form[fn].can_over=0;
           fn=fn+1; 

    global.dialog_active=1;
    draw_dialog_outline(form1,form[dialog_fn].w,form[dialog_fn].h,2);

    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);
    blit(mouse_bg,form2,0,0,mouse1.x-form[dialog_fn].x,mouse1.y-form[dialog_fn].y,mouse1.w,mouse1.h); 

 if(mouse1.h!=20)
  change_mouse_cursor();
}
//================================================================================
 void form_move(int *form_x,int *form_y,int form_w,int form_h,BITMAP *fgform,BITMAP *bgform)
{
  int i;
  
  if(mouse1.changey !=0 || mouse1.changex !=0)
  {

     blit(mouse_bg,dblbuffer,0,0,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
    blit(bgform,dblbuffer,0,0,*form_x,*form_y,form_w,form_h);
    blit(dblbuffer,bgform,*form_x+mouse1.changex,*form_y+mouse1.changey,0,0,form_w,form_h);         
    blit(fgform,dblbuffer,0,0,*form_x+mouse1.changex,*form_y+mouse1.changey,form_w,form_h); 
     blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
     masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);

           if(mouse1.changey>=0)
           {
               if(mouse1.changex>=0)
                 blit(dblbuffer,screen,*form_x,*form_y,*form_x,*form_y,form_w+mouse1.changex+xtra_x,form_h+mouse1.changey);
         
               if(mouse1.changex<0)
                 blit(dblbuffer,screen,*form_x+mouse1.changex,*form_y,*form_x+mouse1.changex,*form_y,form_w+xtra_x-mouse1.changex,form_h+mouse1.changey);  
           }

  
  
           if(mouse1.changey<0)
           {
               if(mouse1.changex>=0)
                   blit(dblbuffer,screen,*form_x,*form_y+mouse1.changey,*form_x,*form_y+mouse1.changey,form_w+xtra_x+mouse1.changex,form_h-mouse1.changey);
         
               if(mouse1.changex<0)
                   blit(dblbuffer,screen,*form_x+mouse1.changex,*form_y+mouse1.changey,*form_x+mouse1.changex,*form_y+mouse1.changey,form_w+xtra_x-mouse1.changex,form_h-mouse1.changey);
       
           }
         
  }
*form_x=*form_x+mouse1.changex;
*form_y=*form_y+mouse1.changey;

if(browser.ampobe==1)
{
      browser.f_u=browser.f_u+mouse1.changey;
      browser.f_d=browser.f_d+mouse1.changey;
      browser.d_u=browser.d_u+mouse1.changey;
      browser.d_d=browser.d_d+mouse1.changey;                  
}

if(mplayer.active==1)
{
  mplayer.pl_u=mplayer.pl_u+mouse1.changey;
  mplayer.pl_d=mplayer.pl_d+mouse1.changey;

  mplayer.pv_l=mplayer.pv_l+mouse1.changex;
  mplayer.pv_r=mplayer.pv_r+mouse1.changex;
  mplayer.seeker_l=mplayer.seeker_l+mouse1.changex;
  mplayer.seeker_r=mplayer.seeker_r+mouse1.changex;
  for(i=mplayer.n-1;i>0;i--)
   {
     mpi[i].x=mpi[i].x+mouse1.changex;
     mpi[i].y=mpi[i].y+mouse1.changey;
   }
}

if(dialog_fn>0)
{
   for(i=fn-1;i>dialog_fn;i--)
   {
     form[i].x=form[i].x+mouse1.changex;
     form[i].y=form[i].y+mouse1.changey;
   }
}

if(mouse1.px != mouse1.x)
 mouse1.px = mouse1.x;

if(mouse1.py != mouse1.y)
 mouse1.py = mouse1.y;    

   }
//================================================================================================   
void draw_dialog_outline(BITMAP *bitmap,int w,int h,int type)
{
  int i;
    if(global.colour_depth==2)
    {

      rectfill(bitmap,0,0,w,h,colour.surface_grey );
      rect(bitmap,0,0,w-1,h-1,colour.black);      
      for(i=3;i<22;i++)
       line(bitmap,3,i,w-3,i,makecol(240-((i)*10),240-((i)*10),240-((i)*10)) );  //upto 21
    }
    else
    {
      buttons_related(bitmap,0,0,w,h,600+1);
      rectfill(bitmap,3,3,w-3,21,colour.item_selected);
    }

    buttons_related(bitmap,w-20,5,w-4,19,600+1);
    line(bitmap,w-16,15,w-9,8,0);
    line(bitmap,w-15,15,w-8,8,0);
    line(bitmap,w-16,8,w-9,15,0);
    line(bitmap,w-15,8,w-8,15,0);
     
    if(type==1)
    {
     buttons_related(bitmap,w-38,5,w-22,19,600+1);
     buttons_related(bitmap,w-55,5,w-39,19,600+1);
    line(bitmap,w-51,14,w-44,14,0);  // minmize
    line(bitmap,w-51,15,w-44,15,0);  // minimize
    rect(bitmap,w-34,10,w-27,15,colour.white);   //restore
    rect(bitmap,w-34,9,w-26,16,colour.white);    //restore
    rect(bitmap,w-35,8,w-27,15,colour.dark_grey_boundry); //restore
    line(bitmap,w-35,9,w-27,9,colour.dark_grey_boundry);  //restore
   }
}   

//=====================================================================================================
void remove_dialog(void)
{
  int i; 

              if(global.menu_selected==5)    //Options
              {
                 if(settings.animation_speed==0)
                   settings.animation_speed=60;
                 set_config_int( "settings", "animation_speed", settings.animation_speed );
                 if(settings.background!=temp_background)
                 {
                   set_config_int( "bolitaire", "background", settings.background);
                   if( (global.colour_depth==2 && settings.background==1) || settings.mplayer==1)
                   {
                     i=1;
                     menus[2][0]="Extra's";
                     if(global.colour_depth==2 && settings.background==1)
                     {
                       menus[2][i]="Change Background";
                       if(settings.mplayer==1)
                         i=i+1;
                     }

                     if(settings.mplayer==1)
                       menus[2][i]="AL-AMP";
                     global.xtra_menu_active=1; 
                     global.num_xtra_submenu=i;
                   }
                }
              }
  if(browser.ampobe==1)
  {
    if(browser.mode==1)
    {
     strcpy(mp3_path,curr_dir);
     chdir(game_path);
     browser.ampobe=0;
     mplayer.active=1;                  
    }
    else
    {
      strcpy(bg_path,curr_dir);
      chdir(game_path);    
      browser.ampobe=0;
      global.show_king=1;
      global.show_menu=1;    
      global.dialog_active=0;               
      global.menu_selected=0;               
    }

  }
  else
  {
    browser.ampobe=0;
    global.show_king=1;
    global.show_menu=1;    
    global.dialog_active=0;               
    global.menu_selected=0;               
  }


               blit(form2,mouse_bg,mouse1.Fx-form[dialog_fn].x,mouse1.Fy-form[dialog_fn].y,0,0,mouse1.w,mouse1.h); 
               masked_blit(mouse,form2,0,0,mouse1.Fx-form[dialog_fn].x,mouse1.Fy-form[dialog_fn].y,mouse1.w,mouse1.h); 
              blit(form2,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
              blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
              destroy_bitmap(form1); 
              destroy_bitmap(form2); 
               for(i=fn-1;i>=dialog_fn;i--)
                  delete_form(-1,i); 
               fn=dialog_fn;
               dialog_fn=-1;
}      

//=============================================================================================
void do_statistics(void)
{
  if(cards_left>0)
    {
      statistics.last_game_status=1;
      if(statistics.last_game_wl==1)
        statistics.curr_streak=-1;        
      if(statistics.last_game_wl==0 || statistics.last_game_wl==-1)
           statistics.curr_streak=statistics.curr_streak-1;              
     statistics.total_loss=statistics.total_loss+1;
     curr_loss=curr_loss+1;
      statistics.last_game_wl=0;
      if(-statistics.curr_streak > statistics.loss_streak)
         statistics.loss_streak=-statistics.curr_streak; 

    }

  if(cards_left==0)
    {
      if(statistics.last_game_wl==1 || statistics.last_game_wl==-1)
          statistics.curr_streak=statistics.curr_streak+1;              
      if(statistics.last_game_wl==0)
           statistics.curr_streak=1;        
      statistics.last_game_wl=1;

     statistics.total_win=statistics.total_win+1;
     curr_win=curr_win+1;
      if(statistics.curr_streak > statistics.win_streak)
         statistics.win_streak=statistics.curr_streak; 
    }

  statpack=pack_fopen("statistics.fyl",F_WRITE_PACKED);
  pack_fwrite(&statistics,sizeof(struct statistics),statpack);
  pack_fclose(statpack);


}

//===============================================================================================
void stretch_image()
{
 int color;
 int i,j,k,l;

  rectfill(buffer,320,0,320+20,320,colour.transperent);
  rectfill(buffer,0,320,320,320+27,colour.transperent);

  for(i=0;i<32;i++)
   {
     for(j=0;j<32;j++)
       {
          color=getpixel(data[XKING_W].dat,i,j);
        
             for(k=0;k<10;k++)
               {
                  for(l=0;l<10;l++)
                     putpixel(buffer,(i*10)+k,(j*10)+l,color);
               }


        }
    }
}
//===============================================================================================
void stretch_image2(void)
{
 int color;
 int i,j,k,l;

  rectfill(buffer,300,0,300+30,80,colour.transperent);
  rectfill(buffer,0,300,80,300+30,colour.transperent);

  for(i=0;i<100;i++)
   {
     for(j=0;j<16;j++)
       {
          color=getpixel(temp,i,j);
        
             for(k=0;k<3;k++)
               {
                  for(l=0;l<5;l++)
                     putpixel(buffer,(i*3)+k,(j*5)+l,color);
               }


        }
    }
}


//=============================================================================================
void draw_freecell()
{
 int i,j,k;
 int m,n;
 int x,y;
 int x1,y1;
 int a,r,g,b;
 long color; 
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
        buttons_related(background,i,y,i+71,y+96,700);

      if(settings.fullscreen==1)
      {
         buttons_related(background,i+20,y+26,i+57,y+25+38,701);
         i=i+78;
      }
      else   
      {
         buttons_related(background,i+14,y+26,i+51,y+25+38,701);
         i=i+65;
      }

      for(i;i<(x+69*9);i=i+72)
         buttons_related(background,i,y,i+71,y+96,700);
if(settings.fullscreen==1)
i=i-40;
blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,11,20);
  blit(background,dblbuffer,x,y,x,y,i,100);

  if(settings.fullscreen==1)
    masked_blit(data[XKING_L].dat,dblbuffer,0,0,380,y+29,38,38);
  else
    masked_blit(data[XKING_L].dat,dblbuffer,0,0,309,y+29,38,38); 

   blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
   masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
   blit(dblbuffer,screen,x,y,x,y,i,97);
  }


if(settings.background==1)
{
  for(i=x;i<(x+69*4);i=i+73)
  {
     for(j=i;j<i+71;j++)
     {
       for(k=y;k<y+96;k++)
       {
         color=getpixel(background,j,k);
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

            if( (r-35<100 && g-35<100 && b-35<100))
            {
               r=r+35;
               g=g+35;
               b=b+35;
            }
            else
            {
                r=r-35;
                g=g-35;
                b=b-35;
            }
         } 
         putpixel(background,j,k,makecol(r,g,b));
                
       }
     }  
  }

  if(settings.fullscreen==1)
  {
    x1=i+18;        //position of king box
    y1=y+26;
  }
  else
  { 
    x1=i+9;        //position of king box
    y1=y+26;
  }

  for(j=x1;j<x1+37;j++)
  {
    for(k=y1;k<y1+37;k++)
    {
       color=getpixel(background,j,k);

       if(global.colour_depth==2)
       {
         r=getr24(color);
         g=getg24(color);
         b=getb24(color);

        if( (r-35<100 && g-35<100 && b-35<100))
        {
          r=r+20;
          g=g+20;
          b=b+20;
        }
        else
        {
          r=r-20;
          g=g-20;
          b=b-20;
        }
       } 
       putpixel(background,j,k,makecol(r,g,b));
    }
  }

  for(m=x1;m<=x1+37;m++)
  {
    color=getpixel(background,m,y1+37);
    color=darken_pixel(color);
    putpixel(background,m,y1+37,color);
  }

  for(m=y1;m<=y1+37;m++)
  {
    color=getpixel(background,x1+37,m);
    color=darken_pixel(color);
    putpixel(background,x1+37,m,color);
  }

  for(m=x1;m<x1+37;m++)
  {
    color=getpixel(background,m,y1);
    color=lighten_pixel(color);
    putpixel(background,m,y1,color);
  }

  for(m=y1;m<=y1+37;m++)
  {
    color=getpixel(background,x1,m);
    color=lighten_pixel(color);
    putpixel(background,x1,m,color);
  }


  if(settings.fullscreen==1)
   i=i+78;
  else
   i=i+58;


  for(i;i<(x+69*9);i=i+73)
  {
    for(j=i;j<i+71;j++)
    {
       for(k=y;k<y+96;k++)
       {
         color=getpixel(background,j,k);
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
         
           if( (r-35<100 && g-35<100 && b-35<100))
           {
              r=r+35;
              g=g+35;
              b=b+35;
           }
           else
           {
              r=r-35;
              g=g-35;
              b=b-35;
           }
         } 
         putpixel(background,j,k,makecol(r,g,b));
       }
    }  
  }

if(settings.fullscreen==1)
i=i-40;
blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,11,20);
  blit(background,dblbuffer,x,y,x,y,i,100);
if(settings.fullscreen==1)
   masked_blit(data[XKING_L].dat,dblbuffer,0,0,382,y+29,38,38);
  else
   masked_blit(data[XKING_L].dat,dblbuffer,0,0,308,y+29,38,38); 
blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
blit(dblbuffer,screen,x,y,x,y,i,97);
//blit(mouse_bg,screen,0,0,0,0,11,20);
}



}

//=====================================================================================
long darken_pixel(long colour)
{
  int r,g,b;
  r=getr24(colour);
  g=getg24(colour);
  b=getb24(colour);

  r=r-60;
  g=g-60;
  b=b-60;
  return(makecol(r,g,b));
}
long lighten_pixel(long colour)
{
   int r,g,b;
  r=getr24(colour);
  g=getg24(colour);
  b=getb24(colour);

  r=r+35;
  g=g+35;
  b=b+35;

  if(r>255)
    r=255;
  if(g>255)
    g=255;
  if(g>255)
    g=255;


  return(makecol(r,g,b));

}



//======================================================================================
void change_mouse_cursor()
{
      if(mouse1.h==19)
       {
         blit(dblbuffer,mouse_bg,mouse1.px+9,mouse1.py,9,0,2,20);
         blit(dblbuffer,mouse_bg,mouse1.px,mouse1.py+19,0,19,11,1);
 
       }
      if(mouse1.h==27)
       {
       blit(mouse_bg,dblbuffer,0,0,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
       blit(dblbuffer,screen,mouse1.px,mouse1.py,mouse1.px,mouse1.py,mouse1.w,mouse1.h);
       }
         mouse1.h=20;
         mouse1.w=11;

         blit(data[XMOUSE].dat,mouse,0,0,0,0,mouse1.w,mouse1.h);
         set_mouse_sprite_focus(0,0);
         flag.frees=1;
         flag.prob_click_events=0;
         flag.change_mouse=0;
         draw_mouse();    
         global.Fcardselected=0;    




}

//===========================================================================================================
void shift_card(int up_down,int cell_form_num,int z)
{
int c,n;
int i,j,k;
int temp2;
int z2;

if(up_down==1)
 {
   n=cell_form_num;
    Curr_pos[0]=form[z].x;
    Curr_pos[1]=form[z].y;

   if(form[n].card!=98)
      show_card_movement_on_screen(z,form[n].x,form[n].y+18);
    else
      show_card_movement_on_screen(z,form[n].x,form[n].y);    
    
      if(form[z].topcard==0)
        {

              if(form[n].card==98)
                temp2=form[n].y;
              else
                temp2=form[n].y+18;

               form[z].x=form[n].x;
               form[z].y=temp2;
               form[z].selected=0;
               form[z].topcard=1;
               form[z].Focus_y=FOCUS_Y;
               form[n].topcard=0;

               card_position(form[n].card);

                if(form[n].card==98)
                  {
                     card[Curr_pos[0]][Curr_pos[1]]=form[z].card;
                                  for(j=n;j<fn;j++)
                                      {
                                          form[j].type=form[j+1].type;
                                          form[j].card=form[j+1].card;
                                          form[j].topcard=form[j+1].topcard;
                                          form[j].n=form[j+1].n;
                                          form[j].h=form[j+1].h;
                                          form[j].w=form[j+1].w;
                                          form[j].x=form[j+1].x;
                                          form[j].y=form[j+1].y;
                                          form[j].Focus_y=form[j+1].Focus_y;
                                          form[j].selected=form[j+1].selected;
                                          form[j].rselected=form[j+1].rselected;
                                          form[j].n=form[j+1].n;
                                          form[j].can_over=form[j+1].can_over;
                                          for(k=1;k<active_number;k++)
                                            {
                                              if( (j+1) == activeform[k])
                                                 activeform[k]=j;
                                            }

                                        }
                                     fn=fn-1;
                 }           
              else
                 card[Curr_pos[0]][Curr_pos[1]+1]=form[z].card;

              for(i=1;i<active_number+1;i++)
                {
                  z2=activeform[i];
                  if(n==z2)
                    {
                       for(j=i;j<active_number+1;j++)
                          activeform[j]=activeform[j+1];
                       active_number=active_number-1;
                       break;
                     }
                  }
          
               for(i=0;i<8;i++)
                {
                  if(freecell[i].card_in==form[z].card)
                      freecell[i].card_in=99;
                }

      }
     else if(form[z].topcard==1)
        {
          previous_card(z);
          if(form[n].card==98)
            temp2=form[n].y;
           else
            temp2=form[n].y+18;

           form[z].x=form[n].x;
           form[z].y=temp2;
           form[z].selected=0;
           form[z].topcard=1;
           form[z].Focus_y=FOCUS_Y;
           form[n].topcard=0;

               for(j=1;j<active_number;j++)
                 {
                   z2=activeform[j];
                   if(n==z2)
                     {
                      previous_card(z);
                      if(Prev_card>=0)
                        {
                          activeform[j]=Prev_card;
                          card[Prev_pos[0]][Prev_pos[1]+1]=99;
                          form[Prev_card].topcard=1;
                        }
                      if(Prev_card<0)
                        {
                          card[Prev_pos[0]][Prev_pos[1]+1]=98;
                          form[fn].w=71;
                          form[fn].h=96;
                          form[fn].x=Curr_pos[0];
                          form[fn].y=Curr_pos[1];
                          card_position(form[z].card);
                          form[fn].type=2;
                          form[fn].selected=0;
                          form[fn].rselected=0;
                          form[fn].Focus_y=form[fn].y;
                          activeform[active_number]=fn;
                          form[fn].topcard=0;
                          form[fn].card=98;
                          form[fn].can_over=2;            
                          form[fn].n=0;                   
                          active_number=active_number+1;
                          fn=fn+1;
                             for(i=j;i<active_number+1;i++)
                                activeform[i]=activeform[i+1];
                          active_number=active_number-1;
                          break;
                         }
                      }
                  }    

              previous_card(n);
            if(form[n].card==98)
              {
                     card[Prev_pos[0]][Prev_pos[1]+1]=form[z].card;
                                 for(j=n;j<fn;j++)
                                    {
                                      form[j].type=form[j+1].type;
                                      form[j].card=form[j+1].card;
                                      form[j].topcard=form[j+1].topcard;
                                      form[j].n=form[j+1].n;
                                      form[j].h=form[j+1].h;
                                      form[j].w=form[j+1].w;
                                      form[j].x=form[j+1].x;
                                      form[j].y=form[j+1].y;
                                      form[j].Focus_y=form[j+1].Focus_y;
                                      form[j].selected=form[j+1].selected;
                                      form[j].rselected=form[j+1].rselected;
                                      form[j].n=form[j+1].n;
                                      form[j].can_over=form[j+1].can_over;
                                        for(k=1;k<active_number;k++)
                                          {
                                            if( (j+1) == activeform[k])
                                              activeform[k]=j;
                                          }
                                    }
                                fn=fn-1;
              }
            else
              card[Prev_pos[0]][Prev_pos[1]+2]=form[z].card;

        }

 }
//------------------------------------------------------------------------------
if(up_down==2)
 {
   c=cell_form_num;
       Curr_pos[0]=form[z].x;
       Curr_pos[1]=form[z].y;

   show_card_movement_on_screen(z,freecell[c].x+1,freecell[c].y+1);

      if(form[z].topcard==0)
         {
          for(i=0;i<8;i++)
           {
            if(freecell[i].card_in==form[z].card)
                freecell[i].card_in=99;
            }
          }

       if(freecell[c].type==0)
        {
         form[z].x=freecell[c].x+1;
         form[z].y=freecell[c].y+1;
         form[z].Focus_y=freecell[c].y+1;
        }
       if(freecell[c].type==1)
        {
          for(i=1;i<active_number+1;i++)
           {
             if(form[activeform[i]].card==form[z].card)
               {
                  for(j=i;j<active_number+1;j++)
                     activeform[j]=activeform[j+1];
                  active_number=active_number-1;
                  fillcell[c-4]=form[z].card;
                  cards_left=cards_left-1;
                  form[z].type=3;
                  break;
               }
            }
         }
        form[z].selected=0;
        freecell[c].card_in=form[z].card;
        previous_card(z);        
        if(form[z].topcard==1)
        {
            if(Prev_card>=0)
            {
              card[Prev_pos[0]][Prev_pos[1]+1]=99;
               form[Prev_card].topcard=1;
               activeform[active_number]=Prev_card;
               active_number=active_number+1;
               form[z].topcard=0;          
             }
            if(Prev_card<0)
            {
             card[Prev_pos[0]][Prev_pos[1]+1]=98;
             form[fn].w=71;
             form[fn].h=96;
             form[fn].x=Curr_pos[0];
             form[fn].y=Curr_pos[1];
             form[fn].type=2;
             form[fn].selected=0;
             form[fn].rselected=0;
             form[fn].Focus_y=form[fn].y;
             activeform[active_number]=fn;
             form[fn].topcard=0;
             form[fn].card=98;
             form[fn].can_over=2;          
             form[fn].n=0;                 
             active_number=active_number+1;
             form[z].topcard=0;
             fn=fn+1;
            }

           }   
 }

}


//===================================================================================
void redraw_screen()
{
global.redraw_screen=0;
file[browser.file_selected].selected=0;
set_config_string("bolitaire","bg",file[browser.file_selected].name);
strcpy(settings.bg,get_config_string("bolitaire","bg","NONE"));
init_screen(1);
blit(dblbuffer,screen,0,0,0,0,800,600);
 draw_freecell();
 if(cards_left!=0)
   replace_cards();


}

//==============================================
void replace_cards()
{
  int placex,placey;
  int i,j;
 if(settings.fullscreen==1 || settings.status_bar==1)
      placey=30;
     else
      placey=3;      

    if(settings.ms_deal==1)
      textprintf_ex(dblbuffer,data[XSANS].dat,SCREEN_W-100,placey,0,-1,"%s%d","#MS ",game_number);
    if(settings.alrand_deal==1)
      textprintf_ex(dblbuffer,data[XSANS].dat,SCREEN_W-100,placey,0,-1,"%s%d","#AL ",game_number);

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
      for(j=0;j<MAX_CARD_L;j++)
       {
        if(card[i][j]==99 || card[i][j]==98)
          break;
        if(global.cheat==2)
        masked_blit(data[52].dat,dblbuffer,0,0,placex,placey,71,96);
        else
        masked_blit(data[card[i][j]].dat,dblbuffer,0,0,placex,placey,71,96);
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
      for(j=0;j<MAX_CARD_L;j++)
       {
          if(card[i][j]==99 || card[i][j]==98)
            break;
           if(global.cheat==2)
           masked_blit(data[52].dat,dblbuffer,0,0,placex,placey,71,96);
           else
           masked_blit(data[card[i][j]].dat,dblbuffer,0,0,placex,placey,71,96);
           blit(dblbuffer,screen,placex,placey,placex,placey,71,96);
        placey=placey+18;
       }
     }
if(settings.fullscreen==1)
  placex=placex+71+9;
 else
  placex=placex+71+8;
  }

  for(i=0;i<8;i++)
  {
   if(freecell[i].card_in!=99)
   {
      masked_blit(data[freecell[i].card_in].dat,dblbuffer,0,0,freecell[i].x+1,freecell[i].y+1,71,96);
      blit(dblbuffer,screen,freecell[i].x+1,freecell[i].y+1,freecell[i].x+1,freecell[i].y+1,71,96);
   
   
   }
  
  }


}

