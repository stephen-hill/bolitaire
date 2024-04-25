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

//====================================
int main(int argc, char *argv[])
{
 int i,j,k,l;
 char buf[256], buf2[256];

#ifdef ALLEGRO_DOS
dos_version=1;
#else
dos_version=0;
#endif

#ifdef ALLEGRO_WINDOWS
windows_version=1;
#else
windows_version=0;
#endif

#ifdef ALLEGRO_LINUX
linux_version=1;
#else
linux_version=0;
#endif

#ifdef ALLEGRO_BEOS
beos_version=1;
#else
beos_version=0;
#endif

allegro_init();

#ifdef ALLEGRO_UNIX                //this provides obsilute path under unix systems
get_executable_name(buf, 256);
(strrchr(buf, '/'))[1] = 0;
chdir(buf);
strcpy(game_path,buf);
strcpy(bg_path,game_path);
strcpy(mp3_path,game_path);
#else
getcwd(game_path,256);
strcpy(bg_path,game_path);
strcpy(mp3_path,game_path);
#endif


set_config_file("config.txt"); 

settings.fullscreen = get_config_int("bolitaire","fullscreen",0);
if(settings.fullscreen==0)
settings.status_bar = get_config_int("bolitaire","status_bar",0);
else
settings.status_bar = 1;
settings.color = get_config_int("bolitaire","color",8);
settings.mplayer = get_config_int("bolitaire","mplayer",0);
settings.background = get_config_int("bolitaire","background",0);
settings.ms_deal = get_config_int("settings","ms_deal",1);
settings.alrand_deal = get_config_int("settings","alrand_deal",0);
settings.animation = get_config_int("settings","animation",1);
settings.animation_speed = get_config_int("settings","animation_speed",20);
strcpy(settings.bg,get_config_string("bolitaire","bg","blue_angle_swirl.jpg"));
settings.custom_driver = get_config_int("bolitaire","custom_driver",0);
settings.custom_w = get_config_int("bolitaire","custom_w",648);
settings.custom_h = get_config_int("bolitaire","custom_h",520);
settings.custom_driver_name = get_config_int("bolitaire","custom_driver_name",2);

if(exists("statistics.fyl")!=0)
{
  statpack=pack_fopen("statistics.fyl",F_READ_PACKED);
  while(pack_feof(statpack)==0)
   pack_fread(&statistics, sizeof(struct statistics),statpack);
  pack_fclose(statpack);
}
else
{
  statistics.last_game_status=1;  //1 complete   0 incomplete
  statistics.total_win=0;
  statistics.total_loss=0;
  statistics.win_streak=0;
  statistics.loss_streak=0;
  statistics.curr_streak=0; 
  statistics.last_game_wl=-1;  //0 for lose  1 for win  -1 for nothing
  statpack=pack_fopen("statistics.fyl",F_WRITE_PACKED);
  pack_fwrite(&statistics,sizeof(struct statistics),statpack);
  pack_fclose(statpack);
}

if(init_driver()==0)
{
  allegro_exit();
  return 0;
}


mouse  = create_bitmap(14,27);
mouse_bg = create_bitmap(14,27);
temp=create_bitmap(800,600);
buffer=create_bitmap(800,600);
dblbuffer=create_bitmap(SCREEN_W,SCREEN_H);
background=create_bitmap(SCREEN_W,SCREEN_H); 
cardtemp=create_bitmap(71,96);
cardtemp2=create_bitmap(71,96); 
timetemp=create_bitmap(150,18); 
 
curr_win=0;
curr_loss=0;

global.animation_speed=20;
global.dialog_active=0;
global.mouse_active=1;
global.show_game_select=1;
global.show_king=1;
global.show_menu=1;
global.cheat=0;
global.redraw_screen=0;
global.xtra_menu_active=0;
 

EXIT_PROGRAM=0;
menus[0][0]="Game";
menus[0][1]="New Game";
menus[0][2]="Select Game";
menus[0][3]="Restart Game";
menus[0][4]="Statistics";
menus[0][5]="Options";
menus[0][6]="Undo";
menus[0][7]="Exit";

menus[1][0]="Help";
menus[1][1]="Help";
menus[1][2]="Credits";
menus[1][3]="About Bolitaire";
menus[1][4]="About Author";

P_menu=-1;  //Any -ive to initialize


//setting up the Extra menu
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

//initializing menu_flag to 0
for(i=0;i<3;i++)
{
  for(j=0;j<7;j++)
   menus_flag[i][j]=0;
}      


mplayer.active=0;
mplayer.play=0;
if(settings.mplayer==1)
{
  bgplayer=create_bitmap(400,500); 
  mplayer.show=0;
  mplayer.clicked=-1;
  mplayer.first_time=1; 
  mplayer.curr_media=-1;
  mplayer.song_played=-1;
  mplayer.contain_pl=20;
  mplayer.first_pl_n=0;  
}

browser.show=0;
browser.ampobe=0;

menustart=14;
overed=-1;
menuselected=0;
main_menu_sel_f=0;
do_mouse_over=0;
show_undo=0;
show_restart=0;
P_submenu=0;
menu_select_F=0;  

mouse1.w=11;
mouse1.h=20;
mouse1.clicked=0;
mouse1.released=0;

get_executable_name(buf, sizeof(buf));
replace_filename(buf2, buf, "data.dat", sizeof(buf2));
data = load_datafile(buf2);
if (!data) 
{
  printf("COULD NOT LOAD DATA FILE \n");
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  allegro_message("Error loading Datafile");
  allegro_exit();
  return 0;
}

do_it_one_time();
init_screen(0);
draw_freecell();
add_transparent();  //this adds transeperent colour to card corners
 

if(statistics.last_game_status==0)
{
  statistics.last_game_status=1;
  statistics.total_loss=statistics.total_loss+1;

  if(statistics.last_game_wl==0 || statistics.last_game_wl==-1) 
    statistics.curr_streak=statistics.curr_streak-1;
  if(statistics.last_game_wl==1)
    statistics.curr_streak=-1;    

  statistics.last_game_wl=0;

  if(-statistics.curr_streak >statistics.loss_streak)
    statistics.loss_streak=-statistics.curr_streak; 
   
  statpack=pack_fopen("statistics.fyl",F_WRITE_PACKED);
  pack_fwrite(&statistics,sizeof(struct statistics),statpack);
  pack_fclose(statpack);
}

//load_music(); 
//windows_version=0;
//settings.background=0;
//browser.show=1;
//browser.mode=2;

//this is the main loop
while(1)
{

  look_for_mouse_click(); //must be at starting
  draw_mouse();  //draws the mouse

//blit(mouse_bg,screen,0,0,0,0,11,20);
//textprintf_ex(screen,font,5,80,5674,-1,"%d %d %d",mplayer.active,mplayer.pv_l,mplayer.pv_r);
//textprintf_ex(screen,font,5,60,5674,-1,"%s %s",bg_path,mp3_path);
// cards_on_screen();

  if(mouse1.clicked)
  {
    if(mplayer.active==1)
      mplayer_click_events();
    mouse_click_events();
  }

  if(mouse1.rclicked)
  {
    if(mplayer.active==1)
      mplayer_rclick_events();
    mouse_rclick_events();
  }

  if(mouse1.pressed)
  {
    if(browser.ampobe==1 && (form[browser.file_scroll].selected==1 || form[browser.dir_scroll].selected==1) )
      do_scroll_bars();
    if(mplayer.active==1 && mplayer.clicked>=0)
      mplayer_pressed_events();
    if(dialog_fn>0 && form[dialog_fn].selected==1)
      form_move(&form[dialog_fn].x,&form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h,form1,form2);
  }

  if(mouse1.released)                  
  {
    if(mplayer.active==1 && mplayer.clicked>=0)
      mplayer_released_events();
    mouse_released_events();       
  }

  if(mouse1.rreleased)
    mouse_rrelease_events();
  if(EXIT_PROGRAM==1)
    break;

  if(menu_select_F==1)
    do_submenu_options();

  if(mplayer.show==1)
    mp3_on_screen();

  if(browser.show==1)
    browser_on_screen();

  if(global.redraw_screen==1)
    redraw_screen();

  if(mouse1.changex!=0 || mouse1.changey !=0 || do_mouse_over==1)
  {
     do_mouse_over=0;
     mouse_over_events();
  }

 if(settings.fullscreen==1 || settings.status_bar==1)
  time_disp();

 hotkeys();  //produces events for key presses

 process_mouse_click();  //must be at end

 if ((key[KEY_ALT] || key[KEY_ALTGR])&& key[KEY_X])  //HOT Key
   break;
}

 if(mplayer.play==1)
   force_destroy_mp3();
 unload_datafile(data);
 allegro_exit();
 return 0;
}
END_OF_MAIN();
//----------------------------------------


//========================================
//this function is for debugging
void cards_on_screen()
{
int i,j,k,l;
l=300;
rectfill(temp,300,310,800,600,colour.bg_green_dark);

  for(i=1;i<9;i++)
  {
    if(i<5)
    {
      k=310;
      for(j=0;j<MAX_CARD_L;j++)
      {
        card_position(card[i][j]);
        //textprintf_ex(screen,data[XSANS].dat,l,k,colour.white,-1,"%d",form[Curr_card].card);
        //textprintf_ex(screen,data[XSANS].dat,l,k,colour.white,-1,"%d %d",card[i][j],form[Curr_card].card);
        textprintf_ex(temp,data[XSANS].dat,l,k,colour.white,-1,"%d %d",card[i][j],Curr_card);
        //textprintf_ex(temp,data[XSANS].dat,l,k,colour.white,-1,"%d",form[Curr_card].topcard);
        k=k+20;
      }
    }

    if(i>4)
    {
      k=310;
      for(j=0;j<MAX_CARD_L;j++)
      {
        card_position(card[i][j]);
        //textprintf_ex(screen,data[XSANS].dat,l,k,colour.white,-1,"%d",form[Curr_card].card);
        //textprintf_ex(screen,data[XSANS].dat,l,k,colour.white,-1,"%d %d",card[i][j],form[Curr_card].card);
        textprintf_ex(temp,data[XSANS].dat,l,k,colour.white,-1,"%d",card[i][j]);
        //textprintf_ex(temp,data[XSANS].dat,l,k,colour.white,-1,"%d",form[Curr_card].topcard);
        k=k+20;
      }
    }
    l=l+40;
  }

blit(temp,screen,300,310,0,350,500,290);
rectfill(temp,0,0,100,600,colour.bg_green_dark);
//for(i=0;i<8;i++)
//textprintf_ex(screen,data[XSANS].dat,20+(i*20),410,colour.white,-1,"%d",freecell[i].card_in);

 for(j=1;j<active_number;j++)
 {
   //z=activeform[j];
   textprintf_ex(temp,font,0,j*20,colour.black,-1,"%d %d",activeform[j],form[activeform[j]].card);
   //if(form[activeform[j]].card==form[global.cardselected].card)
   //textprintf_ex(screen,data[XSANS].dat,460,410,9567,-1,"%d  %d %d",activeform[j],global.form_num,D_n);
 }

textprintf_ex(temp,font,6,j*20,colour.white,-1,"%d",D_n); 
//blit(temp,screen,0,0,600,20,100,600);
//for(j=1;j<=D_n;j++)
//{
//card_position(form[mouseD_card[j]].card);
//textprintf_ex(screen,font,20,290+(j*20),colour.white,-1,"%d %d %d %d //%d",mouseD_card[j],Curr_pos[0],Curr_pos[1],form[mouseD_card[j]].x,form[mouseD_card[j]].y);
//}

//textprintf_ex(screen,data[XSANS].dat,60,410,1111,-1,"%d  %d %d //%d",Prev_card,form[global.cardselected].topcard,Prev_pos[0],Prev_pos[1]);
//textprintf_ex(screen,data[XSANS].dat,460,410,9567,-1,"%d  %d //%d",global.cardselected,global.animation_speed,form[global.cardselected].card);
//textprintf_ex(screen,data[XSANS].dat,460,410,9567,-1,"%d %s%d",fn,"Cards_left=",cards_left);

}
//--------------------------------------------

//these functions are for easter egg :-)
void special_game1(void)
{
int i,j,k;
i=52;

 for (j=0;j<9;j++)          // clear the deck
   for (k=0; k<21;k++)
     card[j][k]=99;

 for(j=1;j<9;j++)
 {
   if(j<5)
   {
     for(k=0;k<7;k++)
     {
       i=i-1;
       if(i==-1)
         break;
       card[j][k]=i;
     }
   }

   if(j>4)
   {
     for(k=0;k<6;k++)
     {
       i=i-1;
       if(i==-1)
         break;
       card[j][k]=i;
     }
   }
 } 

}

//================
void special_game2(void)
{
int i,j,k,l;
i=51;
l=0;

 for (j=0;j<9;j++)          // clear the deck
   for (k=0; k<21;k++)
     card[j][k]=99;

 for(k=0;k<7;k++)
 {
   for(j=1;j<9;j++)
   {
     card[j][k]=i;
     i=i-1;
     if(i==-1)
     {
       l=1;
       break;
     }
   }

   if(l==1)
     break;
 }

}




