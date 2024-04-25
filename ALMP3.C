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
#include "almp3.h"
#include "bol.h"
#include "data.h"
#include "mplayer.h"
#define DATASZ  (1<<15) /* (32768) amount of data to read from disk each time */
#define BUFSZ   (1<<16) /* (65536) size of audiostream buffer */

 DATAFILE *mpdata;
 PACKFILE *m_playlist; 
 int ft=1;
 int make_update=0; //this is for play list
 
typedef struct {
  PACKFILE *f;
  ALMP3_MP3STREAM *s;
} MP3FILE;
MP3FILE *music,*music2;

MP3FILE *open_mp3_file(char *filename) {
  MP3FILE *p = NULL;
  PACKFILE *f = NULL;
  ALMP3_MP3STREAM *s = NULL;
  char data[DATASZ];
  int len;

  if (!(p = (MP3FILE *)malloc(sizeof(MP3FILE))))
    goto error;
  if (!(f = pack_fopen(filename, F_READ)))
    goto error;
  if ((len = pack_fread(data, DATASZ, f)) <= 0)
    goto error;
  if (len < DATASZ) {
    if (!(s = almp3_create_mp3stream(data, len, TRUE)))
      goto error;
  }
  else {
    if (!(s = almp3_create_mp3stream(data, DATASZ, FALSE)))
      goto error;
  }
  p->f = f;
  p->s = s;
  return p;

  error:
  pack_fclose(f);
  free(p);
  return NULL;
}
  
  int play_mp3_file(MP3FILE *mp3, int buflen, int vol, int pan) {
    return almp3_play_mp3stream(mp3->s, buflen, vol, pan);
    }

    void pause_mp3(MP3FILE *mp3) 
    {
     almp3_stop_mp3stream(mp3->s);
    }
    void close_mp3_file(MP3FILE *mp3) {
      if (mp3) {    
      pack_fclose(mp3->f);    
      almp3_destroy_mp3stream(mp3->s);    
      free(mp3);  
      }
      }
      
      int poll_mp3_file(MP3FILE *mp3) {
        char *data;  
        long len;  
        data = (char *)almp3_get_mp3stream_buffer(mp3->s);
          if(mplayer.seek!=0)
          {
           make_custom_changes(mp3->s,mplayer.seek);
           pack_fclose(mp3->f);
           mp3->f = pack_fopen(mplayer.song_played_path, F_READ);
           pack_fseek(mp3->f,mplayer.seek);
           mplayer.seek=0;
          }

          if (data) {    
          len = pack_fread(data, DATASZ, mp3->f);    
          if (len < DATASZ)      
          almp3_free_mp3stream_buffer(mp3->s, len);    
          else      
          almp3_free_mp3stream_buffer(mp3->s, -1);  
          }  
          return almp3_poll_mp3stream(mp3->s);
          }

get_song_length(int size)
{
   int x;
   music2 = open_mp3_file(playlist[mplayer.media_n].s);
   if(music2!=NULL)
   {
   x=almp3_get_length_secs_mp3stream(music2->s,size);
   playlist[mplayer.media_n].min=x/60;
   playlist[mplayer.media_n].sec=x%60; 
   almp3_destroy_mp3stream(music2->s);
   }
   else
   {
     playlist[mplayer.media_n].min=0;  
     playlist[mplayer.media_n].sec=0;
   }    

}
display_curr_time()
{

  blit(mpdata[mplayer.theme].dat,player,10,19,10,19,133-10,107-19);
  textprintf_ex(player,data[XSANS].dat,58,56,colour.black,-1,"%d:%02d",mplayer.run_min,mplayer.run_sec);

  if(mplayer.active==1)
  {
  blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
  blit(player,dblbuffer,10,19,mpi[0].x+10,mpi[0].y+19,133-10,107-19);
  blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
  masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
  blit(dblbuffer,screen,mpi[0].x+10,mpi[0].y+19,mpi[0].x+10,mpi[0].y+19,133-10,107-19);
  }
}
get_curr_time()
{
   int x;
   mplayer.Prun_sec=mplayer.run_sec;
   x=almp3_get_pos_secs_mp3stream(music->s);
   mplayer.run_min=x/60;
   mplayer.run_sec=x%60;   
}

void force_destroy_mp3()
{
  close_mp3_file(music);
}

void load_music()
{
  int i,tmp;
   if(mplayer.media_n !=0)
   {
      if(mplayer.play==1)
      {
      almp3_destroy_mp3stream(music->s);
      ft=1;
         tmp=mplayer.song_played;
         i=mplayer.song_played-mplayer.first_pl_n+mplayer.first_pl_fn;
         if(mplayer.song_played-mplayer.first_pl_n< mplayer.contain_pl && mplayer.song_played-mplayer.first_pl_n>=0)
         {

         rectfill(player,mpi[i].x-mpi[0].x,mpi[i].y+1-mpi[0].y,mpi[i].x+mpi[i].w-mpi[0].x,mpi[i].y+mpi[i].h-mpi[0].y-2,colour.white);
         textprintf_ex(player,data[XSANS2].dat,mpi[i].x+2-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%d",tmp+1);
         if(i<99)
          textprintf_ex(player,data[XSANS2].dat,mpi[i].x+21-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%s",playlist[tmp].name);
         else
          textprintf_ex(player,data[XSANS2].dat,mpi[i].x+27-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%s",playlist[tmp].name);
         textprintf_ex(player,data[XSANS2].dat,mpi[i].x+332-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%d:%02d",playlist[tmp].min,playlist[tmp].sec);
    if(mplayer.active==1)
    {
    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
    blit(player,dblbuffer,mpi[i].x-mpi[0].x,mpi[i].y-mpi[0].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
    blit(dblbuffer,screen,mpi[i].x,mpi[i].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    }
    }  
      }

      if(ft==1 || almp3_is_playing_mp3stream(music->s)==1)
      {
         ft=0;
         if(mplayer.song_played !=-1 && mplayer.curr_media==-1)
         {
         mplayer.curr_media=mplayer.song_played+1;
         if(mplayer.curr_media>=mplayer.media_n)
         mplayer.curr_media=-1;
         }
         if(mplayer.curr_media==-1)
           mplayer.curr_media=0;
         music = open_mp3_file(playlist[mplayer.curr_media].s);
         mplayer.song_played=mplayer.curr_media;
         mplayer.curr_media=-1;
         tmp=mplayer.song_played;                                 
         i=mplayer.song_played-mplayer.first_pl_n+mplayer.first_pl_fn;
         mplayer.total_sec=(playlist[tmp].min*60)+playlist[tmp].sec;  
         mplayer.run_size=playlist[tmp].size_bytes;  
         strcpy(mplayer.song_played_path,playlist[tmp].s);

         if(mplayer.song_played-mplayer.first_pl_n< mplayer.contain_pl && mplayer.song_played-mplayer.first_pl_n>=0)
         {
          blit(mpdata[mplayer.theme].dat,player,140,17,140,17,389-140,112-17);
          textprintf_ex(player,data[XSANS2].dat,155,26,makecol(56,56,56),-1,"%s","Details on song being played:");
          textprintf_ex(player,data[XSANS2].dat,155,52,colour.black,-1,"%s",playlist[tmp].name);
          textprintf_ex(player,data[XSANS2].dat,155,68,colour.black,-1,"%s %d:%02d","Length:",playlist[tmp].min,playlist[tmp].sec);
          textprintf_ex(player,data[XSANS2].dat,155,84,colour.black,-1,"%s %d %s","Bitrate:",almp3_get_bitrate_mp3stream(music->s)/1000,"Kbits");          
         rectfill(player,mpi[i].x-mpi[0].x,mpi[i].y+1-mpi[0].y,mpi[i].x+mpi[i].w-mpi[0].x,mpi[i].y+mpi[i].h-mpi[0].y-2,makecol(255,125,0));
         textprintf_ex(player,data[XSANS2].dat,mpi[i].x+2-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%d",tmp+1);
         if(i<99)
          textprintf_ex(player,data[XSANS2].dat,mpi[i].x+21-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%s",playlist[tmp].name);
         else
          textprintf_ex(player,data[XSANS2].dat,mpi[i].x+27-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%s",playlist[tmp].name);
         textprintf_ex(player,data[XSANS2].dat,mpi[i].x+332-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%d:%02d",playlist[tmp].min,playlist[tmp].sec);
    if(mplayer.active==1)
    {
    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
    blit(player,dblbuffer,140,17,mpi[0].x+140,mpi[0].y+17,389-140,112-17);
    blit(player,dblbuffer,mpi[i].x-mpi[0].x,mpi[i].y-mpi[0].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
    blit(dblbuffer,screen,mpi[0].x+140,mpi[0].y+17,mpi[0].x+140,mpi[0].y+17,389-140,112-17);
    blit(dblbuffer,screen,mpi[i].x,mpi[i].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    }
    }
      }
   mplayer.play=1;
   play_mp3_file(music,BUFSZ,mplayer.volume,mplayer.pan); 
  }
}
void poll_music()
{
 int x;
 x=poll_mp3_file(music);
 if(x==ALMP3_POLL_NOTPLAYING || x==ALMP3_POLL_FRAMECORRUPT || x==ALMP3_POLL_INTERNALERROR)
  load_music();   
}

void mp3_on_screen()
{
 char buf[256], buf2[256]; 
 int i;
 if(mplayer.first_time==1)
 {
  mplayer.media_n=get_config_int("player","media_n",0); //this is just test need to calculate from previous blah
  mplayer.volume=get_config_int("player","volume",255);
  mplayer.pan=get_config_int("player","pan",128);
  mplayer.first_time=0;
  chdir("mplayer");
   mpdata = load_datafile("mpdata.dat");
  if(global.colour_depth==2)
  mplayer.theme=0;
  else
  mplayer.theme=1;
  
  player=create_bitmap(400,500);
  bgplayer=create_bitmap(400,500); 

  blit(mpdata[mplayer.theme].dat,player,0,0,0,0,400,500);
  textprintf_ex(player,data[XSANS].dat,58,56,colour.black,-1,"%d:%d",0,0);


   mplayer.n=0;                          //0 this is the player
   mpi[mplayer.n].w=400;
   mpi[mplayer.n].h=500;
   mpi[mplayer.n].x=(SCREEN_W/2-400/2);
   mpi[mplayer.n].y=(SCREEN_H/2-500/2);
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 

   mpi[mplayer.n].w=10;                 //1 this is hide button
   mpi[mplayer.n].h=10;
   mpi[mplayer.n].x=mpi[0].x+385;
   mpi[mplayer.n].y=mpi[0].y+4;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 

   mpi[mplayer.n].w=21;                 //2 this is Add button
   mpi[mplayer.n].h=19;
   mpi[mplayer.n].x=mpi[0].x+14;
   mpi[mplayer.n].y=mpi[0].y+147;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   blit(mpdata[mplayer.theme].dat,player,6,505,14,147,mpi[2].w,mpi[2].h);

   mpi[mplayer.n].w=21;                 //3 this is Sub button
   mpi[mplayer.n].h=19;
   mpi[mplayer.n].x=mpi[0].x+40;
   mpi[mplayer.n].y=mpi[0].y+147;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   blit(mpdata[mplayer.theme].dat,player,32,505,40,147,mpi[3].w,mpi[3].h);


   mpi[mplayer.n].w=25;                 //4 this is play button
   mpi[mplayer.n].h=23;
   mpi[mplayer.n].x=mpi[0].x+80;
   mpi[mplayer.n].y=mpi[0].y+143;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   blit(mpdata[mplayer.theme].dat,player,60,503,mpi[4].x-mpi[0].x,mpi[4].y-mpi[0].y,mpi[4].w,mpi[4].h);

   mpi[mplayer.n].w=25;                 //5 this is PAUSE button
   mpi[mplayer.n].h=23;
   mpi[mplayer.n].x=mpi[0].x+111;
   mpi[mplayer.n].y=mpi[0].y+143;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   blit(mpdata[mplayer.theme].dat,player,91,503,mpi[5].x-mpi[0].x,mpi[5].y-mpi[0].y,mpi[5].w,mpi[5].h);

   mpi[mplayer.n].w=25;                 //6 this is STOP button
   mpi[mplayer.n].h=23;
   mpi[mplayer.n].x=mpi[0].x+142;
   mpi[mplayer.n].y=mpi[0].y+143;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   blit(mpdata[mplayer.theme].dat,player,122,503,mpi[6].x-mpi[0].x,mpi[6].y-mpi[0].y,mpi[6].w,mpi[6].h);

   mpi[mplayer.n].w=10;                 //7 this is seeker scrll
   mpi[mplayer.n].h=16;
   mpi[mplayer.n].x=mpi[0].x+7;
   mpi[mplayer.n].y=mpi[0].y+117;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   blit(mpdata[mplayer.theme].dat,player,168,503,mpi[7].x-mpi[0].x,mpi[7].y-mpi[0].y,mpi[7].w,mpi[7].h);

   mplayer.seeker_l=mpi[0].x+7;
   mplayer.seeker_r=mpi[0].x+392;

   mpi[mplayer.n].w=7;                 //8 this is volume scroll
   mpi[mplayer.n].h=12;
//   mpi[mplayer.n].x=mpi[0].x+177;
   mpi[mplayer.n].y=mpi[0].y+140;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 

   mplayer.pv_l=mpi[0].x+177;
   mplayer.pv_r=mpi[0].x+364;

   mpi[8].x=(mplayer.volume*((mplayer.pv_r-mplayer.pv_l)-mpi[8].w)/255)+mplayer.pv_l;
   if(mplayer.volume==128)
   blit(mpdata[mplayer.theme].dat,player,154,524,mpi[8].x-mpi[0].x,mpi[8].y-mpi[0].y,mpi[8].w,mpi[8].h);
   else
   blit(mpdata[mplayer.theme].dat,player,154,505,mpi[8].x-mpi[0].x,mpi[8].y-mpi[0].y,mpi[8].w,mpi[8].h);


   mpi[mplayer.n].w=7;                 //9 this is pan scroll
   mpi[mplayer.n].h=12;
   mpi[mplayer.n].x=mpi[0].x+177;
   mpi[mplayer.n].y=mpi[0].y+153;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 

   mpi[9].x=(mplayer.pan*((mplayer.pv_r-mplayer.pv_l)-mpi[9].w)/255)+mplayer.pv_l;
   if(mplayer.pan==128)
   blit(mpdata[mplayer.theme].dat,player,154,524,mpi[9].x-mpi[0].x,mpi[9].y-mpi[0].y,mpi[9].w,mpi[9].h);
   else
   blit(mpdata[mplayer.theme].dat,player,154,505,mpi[9].x-mpi[0].x,mpi[9].y-mpi[0].y,mpi[9].w,mpi[9].h);

   mpi[mplayer.n].w=16;             //this is up scroll button
   mpi[mplayer.n].h=16;
   mpi[mplayer.n].x=mpi[0].x+376;
   mpi[mplayer.n].y=mpi[0].y+170;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   mplayer.pl_u=mpi[0].y+186;

   mpi[mplayer.n].w=16;             //this is down scroll button
   mpi[mplayer.n].h=16;
   mpi[mplayer.n].x=mpi[0].x+376;
   mpi[mplayer.n].y=mpi[0].y+475;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   mplayer.pl_d=mpi[0].y+474;


   mpi[mplayer.n].w=0;           //this is scroller
   mpi[mplayer.n].h=0;
   mpi[mplayer.n].x=mpi[0].x+376;
   mpi[mplayer.n].y=0;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 


  mplayer.first_pl_n=0;
  mplayer.first_pl_fn=mplayer.n;  //this is for the play list 
   for(i=0;i<mplayer.contain_pl;i++)
   {
   mpi[mplayer.n].w=364; 
   mpi[mplayer.n].h=17;
   mpi[mplayer.n].x=mpi[0].x+8;
   mpi[mplayer.n].y=mpi[0].y+170+i*16;
   mpi[mplayer.n].selected=0;
   mpi[mplayer.n].rselected=0;
   mpi[mplayer.n].can_over=0;
   mplayer.n=mplayer.n+1; 
   }

 if(exists("playlist.als")!=0 && mplayer.media_n!=0)
{
   m_playlist=pack_fopen("playlist.als",F_READ);
   while(pack_feof(m_playlist)==0)
     pack_fread(&playlist, sizeof(struct pl[mplayer.media_n]),m_playlist);
   pack_fclose(m_playlist);
   make_update=1;
}
  chdir(game_path);

 }

 mplayer.show=0;  //a flag so not to continously show player
 mplayer.active=1; 
 global.show_king=0;
 global.show_menu=0;  
 global.dialog_active=1; 

 if(mouse1.h!=20)
  change_mouse_cursor();
 blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
 blit(dblbuffer,bgplayer,mpi[0].x,mpi[0].y,0,0,400,500);
 blit(player,dblbuffer,0,0,mpi[0].x,mpi[0].y,400,500);
 blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
 masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
 blit(dblbuffer,screen,mpi[0].x,mpi[0].y,mpi[0].x,mpi[0].y,400,500);

 if(make_update==1)
 {
  make_update=0;
  init_pl_scroll_bars();
  update_pl_scroll(0,1);
 }
}


void mplayer_rclick_events()
{
 int i,tmp;
 for(i=mplayer.first_pl_fn;i<mplayer.first_pl_fn+mplayer.contain_pl;i++)
 {
    if(mouse1.Fx>mpi[i].x && mouse1.Fx<mpi[i].x+mpi[i].w && mouse1.Fy>mpi[i].y && mouse1.Fy<mpi[i].y+mpi[i].h  && mplayer.first_pl_n+i-mplayer.first_pl_fn<mplayer.media_n )
     {
    tmp=mplayer.first_pl_n+i-mplayer.first_pl_fn;
    if(playlist[tmp].selected==0)
     {
    if(mplayer.curr_media==tmp)
      mplayer.curr_media=-1;
    playlist[tmp].selected=1;
    rectfill(player,mpi[i].x-mpi[0].x,mpi[i].y+1-mpi[0].y,mpi[i].x+mpi[i].w-mpi[0].x,mpi[i].y+mpi[i].h-mpi[0].y-2,makecol(190,255,0));
     textprintf_ex(player,data[XSANS2].dat,mpi[i].x+2-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%d",tmp+1);
      if(tmp<99)
       textprintf_ex(player,data[XSANS2].dat,mpi[i].x+21-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%s",playlist[tmp].name);
      else
       textprintf_ex(player,data[XSANS2].dat,mpi[i].x+27-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%s",playlist[tmp].name);
     textprintf_ex(player,data[XSANS2].dat,mpi[i].x+332-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%d:%02d",playlist[tmp].min,playlist[tmp].sec);
     }
   else
     {
    playlist[tmp].selected=0;
    if(mplayer.song_played==tmp)
    {
      rectfill(player,mpi[i].x-mpi[0].x,mpi[i].y+1-mpi[0].y,mpi[i].x+mpi[i].w-mpi[0].x,mpi[i].y+mpi[i].h-mpi[0].y-2,makecol(255,125,0) );
      textprintf_ex(player,data[XSANS2].dat,mpi[i].x+2-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%d",tmp+1);
      if(tmp<99)
       textprintf_ex(player,data[XSANS2].dat,mpi[i].x+21-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%s",playlist[tmp].name);
      else
       textprintf_ex(player,data[XSANS2].dat,mpi[i].x+27-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%s",playlist[tmp].name);
     textprintf_ex(player,data[XSANS2].dat,mpi[i].x+332-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%d:%02d",playlist[tmp].min,playlist[tmp].sec);
     }
     else
     {
    rectfill(player,mpi[i].x-mpi[0].x,mpi[i].y+1-mpi[0].y,mpi[i].x+mpi[i].w-mpi[0].x,mpi[i].y+mpi[i].h-mpi[0].y-2,colour.white);
     textprintf_ex(player,data[XSANS2].dat,mpi[i].x+2-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%d",tmp+1);
      if(tmp<99)
       textprintf_ex(player,data[XSANS2].dat,mpi[i].x+21-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%s",playlist[tmp].name);
      else
       textprintf_ex(player,data[XSANS2].dat,mpi[i].x+27-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%s",playlist[tmp].name);
     textprintf_ex(player,data[XSANS2].dat,mpi[i].x+332-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.black,-1,"%d:%02d",playlist[tmp].min,playlist[tmp].sec);
     }

     }



    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
    blit(player,dblbuffer,mpi[i].x-mpi[0].x,mpi[i].y-mpi[0].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
    blit(dblbuffer,screen,mpi[i].x,mpi[i].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    break;
     }
   
 }


}


void mplayer_click_events()
{
 int i,j,tmp;

  for(i=mplayer.n-1;i>=0;i--)
   {
    if(mouse1.Fx>mpi[i].x && mouse1.Fx<mpi[i].x+mpi[i].w && mouse1.Fy>mpi[i].y && mouse1.Fy<mpi[i].y+mpi[i].h  )
    {
    mpi[i].selected=1;
    mplayer.clicked=i;    
    break;
    }
   }

  if(mpi[2].selected==1)
  {
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,6,530,mpi[2].x,mpi[2].y,mpi[2].w,mpi[2].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[2].x,mpi[2].y,mpi[2].x,mpi[2].y,mpi[2].w,mpi[2].h);
  }

  if(mpi[3].selected==1)
  {
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,32,530,mpi[3].x,mpi[3].y,mpi[3].w,mpi[3].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[3].x,mpi[3].y,mpi[3].x,mpi[3].y,mpi[3].w,mpi[3].h);
  }


  if(mpi[4].selected==1)
  {
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,60,529,mpi[4].x,mpi[4].y,mpi[4].w,mpi[4].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[4].x,mpi[4].y,mpi[4].x,mpi[4].y,mpi[4].w,mpi[4].h);
  }

  if(mpi[5].selected==1)
  {
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,91,529,mpi[5].x,mpi[5].y,mpi[5].w,mpi[5].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[5].x,mpi[5].y,mpi[5].x,mpi[5].y,mpi[5].w,mpi[5].h);
  }

  if(mpi[6].selected==1)
  {
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,122,529,mpi[6].x,mpi[6].y,mpi[6].w,mpi[6].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[6].x,mpi[6].y,mpi[6].x,mpi[6].y,mpi[6].w,mpi[6].h);
  }

  if(mpi[mplayer.first_pl_fn-3].selected==1)   //up scroll button
   {
     tmp=mplayer.first_pl_fn-3;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,184,504,mpi[tmp].x,mpi[tmp].y,mpi[tmp].w,mpi[tmp].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[tmp].x,mpi[tmp].y,mpi[tmp].x,mpi[tmp].y,mpi[tmp].w,mpi[tmp].h);
     if(mplayer.first_pl_n!=0)
       update_pl_scroll(mplayer.first_pl_n-1,1);
   }

  if(mpi[mplayer.first_pl_fn-2].selected==1)   //down scroll button
   {
     tmp=mplayer.first_pl_fn-2;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,184,525,mpi[tmp].x,mpi[tmp].y,mpi[tmp].w,mpi[tmp].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[tmp].x,mpi[tmp].y,mpi[tmp].x,mpi[tmp].y,mpi[tmp].w,mpi[tmp].h);
     if(mplayer.first_pl_n+mplayer.contain_pl<mplayer.media_n)
       update_pl_scroll(mplayer.first_pl_n+1,1);
   }




  if(mpi[i].selected==1 && i>=mplayer.first_pl_fn && i<mplayer.first_pl_fn+mplayer.contain_pl && mplayer.first_pl_n+i-mplayer.first_pl_fn<mplayer.media_n)
  {
    tmp=mplayer.first_pl_n+i-mplayer.first_pl_fn;
    playlist[tmp].selected=0;

    if(mplayer.curr_media == tmp)
       load_music();

    if(mplayer.curr_media != tmp && mplayer.song_played != tmp)
    {
      if(mplayer.curr_media-mplayer.first_pl_n< mplayer.contain_pl && mplayer.curr_media-mplayer.first_pl_n>=0)
      {
        j=mplayer.first_pl_fn+mplayer.curr_media-mplayer.first_pl_n;
        rectfill(player,mpi[j].x-mpi[0].x,mpi[j].y+1-mpi[0].y,mpi[j].x+mpi[j].w-mpi[0].x,mpi[j].y+mpi[j].h-mpi[0].y-2,colour.white);
        textprintf_ex(player,data[XSANS2].dat,mpi[j].x+2-mpi[0].x,mpi[j].y+2-mpi[0].y,colour.black,-1,"%d",mplayer.curr_media+1);
        if(mplayer.curr_media<99)
          textprintf_ex(player,data[XSANS2].dat,mpi[j].x+21-mpi[0].x,mpi[j].y+2-mpi[0].y,colour.black,-1,"%s",playlist[mplayer.curr_media].name);
        else
          textprintf_ex(player,data[XSANS2].dat,mpi[j].x+27-mpi[0].x,mpi[j].y+2-mpi[0].y,colour.black,-1,"%s",playlist[mplayer.curr_media].name);
        textprintf_ex(player,data[XSANS2].dat,mpi[j].x+332-mpi[0].x,mpi[j].y+2-mpi[0].y,colour.black,-1,"%d:%02d",playlist[mplayer.curr_media].min,playlist[mplayer.curr_media].sec);

       blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
       blit(player,dblbuffer,mpi[j].x-mpi[0].x,mpi[j].y-mpi[0].y,mpi[j].x,mpi[j].y,mpi[j].w+1,mpi[j].h+1);
       blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
       masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
       blit(dblbuffer,screen,mpi[j].x,mpi[j].y,mpi[j].x,mpi[j].y,mpi[j].w+1,mpi[j].h+1);
     }

    mplayer.curr_media=tmp;
    rectfill(player,mpi[i].x-mpi[0].x,mpi[i].y+1-mpi[0].y,mpi[i].x+mpi[i].w-mpi[0].x,mpi[i].y+mpi[i].h-mpi[0].y-2,colour.item_selected);
     textprintf_ex(player,data[XSANS2].dat,mpi[i].x+2-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%d",tmp+1);
      if(tmp<99)
       textprintf_ex(player,data[XSANS2].dat,mpi[i].x+21-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%s",playlist[tmp].name);
      else
       textprintf_ex(player,data[XSANS2].dat,mpi[i].x+27-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%s",playlist[tmp].name);
     textprintf_ex(player,data[XSANS2].dat,mpi[i].x+332-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%d:%02d",playlist[tmp].min,playlist[tmp].sec);

    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
    blit(player,dblbuffer,mpi[i].x-mpi[0].x,mpi[i].y-mpi[0].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
    blit(dblbuffer,screen,mpi[i].x,mpi[i].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    }
    mpi[i].selected=0;
  }



}
//==========
void mplayer_pressed_events()
{
  if(mpi[mplayer.first_pl_fn-1].selected==1)
    do_pl_scrolls();

  if(mpi[7].selected==1)
    do_seeker_scrolls();

  if(mpi[8].selected==1)
    do_pv_scrolls(8,&mplayer.volume);

  if(mpi[9].selected==1)
    do_pv_scrolls(9,&mplayer.pan);



  if(mpi[0].selected==1)
     form_move(&mpi[0].x,&mpi[0].y,mpi[0].w,mpi[0].h,player,bgplayer);
}

void mplayer_released_events()
{
  int tmp,i,j;
  int delete_all_flag,forward;
  long s_r,s_l,w,c_run,t_run;  
  mplayer.clicked=-1;

  if(mpi[mplayer.first_pl_fn-1].selected==1)
    mpi[mplayer.first_pl_fn-1].selected=0;


  if(mpi[0].selected==1)
    mpi[0].selected=0;
    
  if(mpi[7].selected==1)
   {
    s_r=mplayer.seeker_r;
    s_l=mplayer.seeker_l;
    w=mpi[7].w;
//    c_run=(mplayer.run_min*60)+mplayer.run_sec;
    t_run=mplayer.total_sec;
//    mpi[n].x=( ((s_r-s_l-w)*c_run )/t_run)+s_l;
    c_run= ((mpi[7].x-s_l)*t_run)/(s_r-s_l-w);
   mplayer.seek=almp3_seek_abs_secs_mp3stream(music->s,c_run,mplayer.run_size);    
//   poll_to_new_position(music);
//   textprintf_ex(screen,font,5,80,5674,-1,"%d %d",seek,c_run);
    mpi[7].selected=0;
   } 

  if(mpi[8].selected==1)
    mpi[8].selected=0;

  if(mpi[9].selected==1)
    mpi[9].selected=0;

  if(mpi[1].selected==1)
   {
    if(mouse1.Fx>mpi[1].x && mouse1.Fx<mpi[1].x+mpi[1].w && mouse1.Fy>mpi[1].y && mouse1.Fy<mpi[1].y+mpi[1].h  )
    {
    mpi[1].selected=0;
    mplayer.active=0;
    global.show_king=1;
    global.show_menu=1;  
    global.dialog_active=0; 

    chdir("mplayer");
    m_playlist=pack_fopen("playlist.als",F_WRITE);
    pack_fwrite(&playlist,sizeof(struct pl[mplayer.media_n]),m_playlist);
    pack_fclose(m_playlist);
    chdir(game_path);
    set_config_int("player","media_n",mplayer.media_n);
    set_config_int("player","volume",mplayer.volume);
    set_config_int("player","pan",mplayer.pan);        
    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
    blit(bgplayer,dblbuffer,0,0,mpi[0].x,mpi[0].y,mpi[0].w,mpi[0].h);
    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
    blit(dblbuffer,screen,mpi[0].x,mpi[0].y,mpi[0].x,mpi[0].y,mpi[0].w,mpi[0].h);
    }
   }

  if(mpi[2].selected==1)      // Add button
   {
     mpi[2].selected=0;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,6,505,mpi[2].x,mpi[2].y,mpi[2].w,mpi[2].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[2].x,mpi[2].y,mpi[2].x,mpi[2].y,mpi[2].w,mpi[2].h);
    if(mouse1.Fx>mpi[2].x && mouse1.Fx<mpi[2].x+mpi[2].w && mouse1.Fy>mpi[2].y && mouse1.Fy<mpi[2].y+mpi[2].h  )
    {
    mplayer.active=0;
    browser.show=1;
    browser.mode=1;    
    }

   }

  if(mpi[3].selected==1)      //remove button
   {
     mpi[3].selected=0;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,32,505,mpi[3].x,mpi[3].y,mpi[3].w,mpi[3].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[3].x,mpi[3].y,mpi[3].x,mpi[3].y,mpi[3].w,mpi[3].h);
    if(mplayer.media_n !=0 && mouse1.Fx>mpi[3].x && mouse1.Fx<mpi[3].x+mpi[3].w && mouse1.Fy>mpi[3].y && mouse1.Fy<mpi[3].y+mpi[3].h  )
    {
        delete_all_flag=1;
        for(i=mplayer.media_n-1;i>=0;i--)
        {
          if(playlist[i].selected==1)
           {
            playlist[i].selected=-1;
            delete_all_flag=0;
           }
        }
        if(delete_all_flag==1)
         {
              blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
              blit(mpdata[mplayer.theme].dat,player,6,169,6,169,386,324);  
              blit(mpdata[mplayer.theme].dat,dblbuffer,6,169,mpi[0].x+6,mpi[0].y+169,386,324);  
              blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
              masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
              blit(dblbuffer,screen,mpi[mplayer.first_pl_fn].x,mpi[mplayer.first_pl_fn].y,mpi[mplayer.first_pl_fn].x,mpi[mplayer.first_pl_fn].y,mpi[mplayer.first_pl_fn].w+36,mpi[mplayer.first_pl_fn].h*mplayer.contain_pl);
              mplayer.media_n=0;
              mplayer.curr_media=-1;
              mplayer.song_played=-1;
         }
         else  //this is for delete_all_flag==0
         {
            forward=0;
            for(i=0;i<mplayer.media_n;i++)
            {
             if(playlist[i].selected==-1)
              {
                  forward=forward+1;
               if(mplayer.song_played==i)
                 mplayer.song_played=-1;
               if(mplayer.curr_media==i)
                 mplayer.curr_media=-1;
              }
             if(i != i-forward && playlist[i].selected != -1)
             {
               strcpy(playlist[i-forward].s,playlist[i].s);
               strcpy(playlist[i-forward].name,playlist[i].name);               
               playlist[i-forward].min=playlist[i].min;
               playlist[i-forward].sec=playlist[i].sec;
               playlist[i-forward].selected=playlist[i].selected;               
               if(mplayer.song_played==i)
                 mplayer.song_played=i-forward;
               if(mplayer.curr_media==i)
                 mplayer.curr_media=i-forward;
             }
            }
            mplayer.media_n=mplayer.media_n-forward;
            if(mplayer.first_pl_n+mplayer.contain_pl>mplayer.media_n)
              mplayer.first_pl_n=mplayer.media_n-mplayer.contain_pl;
            if(mplayer.media_n<=mplayer.contain_pl)
//            {
//              readkey();
              mplayer.first_pl_n=0; 
//            }  
//            if(mplayer.media_n>mplayer.contain_pl)
//              mplayer.first_pl_n=mplayer.media_n-mplayer.contain_pl;
//             else
//              mplayer.first_pl_n=0; 
            init_pl_scroll_bars();
            update_pl_scroll(mplayer.first_pl_n,3);


         }
    }
   }
   
  if(mpi[4].selected==1)       //play button
   {
     mpi[4].selected=0;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,60,503,mpi[4].x,mpi[4].y,mpi[4].w,mpi[4].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[4].x,mpi[4].y,mpi[4].x,mpi[4].y,mpi[4].w,mpi[4].h);
     if(mouse1.Fx>mpi[4].x && mouse1.Fx<mpi[4].x+mpi[4].w && mouse1.Fy>mpi[4].y && mouse1.Fy<mpi[4].y+mpi[4].h  )
       load_music();

   }

  if(mpi[5].selected==1)      //pause
   {
     mpi[5].selected=0;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,91,503,mpi[5].x,mpi[5].y,mpi[5].w,mpi[5].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[5].x,mpi[5].y,mpi[5].x,mpi[5].y,mpi[5].w,mpi[5].h);
    if(mouse1.Fx>mpi[5].x && mouse1.Fx<mpi[5].x+mpi[5].w && mouse1.Fy>mpi[5].y && mouse1.Fy<mpi[5].y+mpi[5].h && mplayer.play==1)
    {
      mplayer.play=0;
      pause_mp3(music);
    }

   }

  if(mpi[6].selected==1)       //stop
   {
     mpi[6].selected=0;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,122,503,mpi[6].x,mpi[6].y,mpi[6].w,mpi[6].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[6].x,mpi[6].y,mpi[6].x,mpi[6].y,mpi[6].w,mpi[6].h);
    if(mouse1.Fx>mpi[6].x && mouse1.Fx<mpi[6].x+mpi[6].w && mouse1.Fy>mpi[6].y && mouse1.Fy<mpi[6].y+mpi[6].h && mplayer.play==1 )
    {
     blit(mpdata[mplayer.theme].dat,player,140,17,140,17,389-140,112-17);
     blit(player,dblbuffer,140,17,mpi[0].x+140,mpi[0].y+17,389-140,112-17);
     blit(dblbuffer,screen,mpi[0].x+140,mpi[0].y+17,mpi[0].x+140,mpi[0].y+17,389-140,112-17);
     mplayer.play=0;
     ft=1;
      mplayer.run_min=0;
      mplayer.run_sec=0;
      display_curr_time();
      mplayer.curr_media=mplayer.song_played;
      mplayer.song_played=-1;
      if(mplayer.curr_media-mplayer.first_pl_n< mplayer.contain_pl && mplayer.curr_media-mplayer.first_pl_n>=0)
       {
         i=mplayer.curr_media-mplayer.first_pl_n+mplayer.first_pl_fn;
         rectfill(player,mpi[i].x-mpi[0].x,mpi[i].y+1-mpi[0].y,mpi[i].x+mpi[i].w-mpi[0].x,mpi[i].y+mpi[i].h-mpi[0].y-2,colour.item_selected);
         textprintf_ex(player,data[XSANS2].dat,mpi[i].x+2-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%d",mplayer.curr_media+1);
         if(i<99)
          textprintf_ex(player,data[XSANS2].dat,mpi[i].x+21-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%s",playlist[mplayer.curr_media].name);
         else
          textprintf_ex(player,data[XSANS2].dat,mpi[i].x+27-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%s",playlist[mplayer.curr_media].name);
         textprintf_ex(player,data[XSANS2].dat,mpi[i].x+332-mpi[0].x,mpi[i].y+2-mpi[0].y,colour.white,-1,"%d:%02d",playlist[tmp].min,playlist[mplayer.curr_media].sec);
    blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
    blit(player,dblbuffer,mpi[i].x-mpi[0].x,mpi[i].y-mpi[0].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);
    blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
    masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
    blit(dblbuffer,screen,mpi[i].x,mpi[i].y,mpi[i].x,mpi[i].y,mpi[i].w+1,mpi[i].h+1);

       }

      blit(mpdata[mplayer.theme].dat,player,7,117,7,117,392-7+1,132-117+1);
      blit(player,dblbuffer,7,117,mpi[0].x+7,mpi[0].y+117,392-7+1,132-117+1);  
      blit(dblbuffer,screen,mpi[0].x+7,mpi[0].y+117,mpi[0].x+7,mpi[0].y+117,392-7+1,132-117+1);  
      almp3_destroy_mp3stream(music->s);
    }

   }


  if(mpi[mplayer.first_pl_fn-3].selected==1)   //up scroll button
   {
     tmp=mplayer.first_pl_fn-3;
     mpi[tmp].selected=0;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,376,170,mpi[tmp].x,mpi[tmp].y,mpi[tmp].w,mpi[tmp].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[tmp].x,mpi[tmp].y,mpi[tmp].x,mpi[tmp].y,mpi[tmp].w,mpi[tmp].h);
   }

  if(mpi[mplayer.first_pl_fn-2].selected==1)   //down scroll button
   {
     tmp=mplayer.first_pl_fn-2;
     mpi[tmp].selected=0;
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(mpdata[mplayer.theme].dat,dblbuffer,376,475,mpi[tmp].x,mpi[tmp].y,mpi[tmp].w,mpi[tmp].h);  
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[tmp].x,mpi[tmp].y,mpi[tmp].x,mpi[tmp].y,mpi[tmp].w,mpi[tmp].h);
   }



}

//==============================================================================================
void init_pl_scroll_bars()
{
 int i,j,pls;
 pls= mplayer.first_pl_fn-1;
 
 if(mplayer.media_n>mplayer.contain_pl)
 {
   mpi[pls].w=15;
   mpi[pls].h=( ((mplayer.pl_d-mplayer.pl_u) *(mplayer.pl_d-mplayer.pl_u+30)) /(mplayer.media_n*17) );
   mpi[pls].y=mplayer.pl_u;
 }
 else
 {
   mpi[pls].w=15; //this is needed for displaying empty scroll bar
   mpi[pls].h=0;  //this will eliminate scroll bar
   mpi[pls].y=0;
 }

}
//========================================================================================

void do_pl_scrolls()
{
 int pls,i,j;

   pls=mplayer.first_pl_fn-1;
  if(mpi[pls].selected==1)
   {
   if(mpi[pls].selected==1 && mouse1.changey!=0)
    {
      mpi[pls].y=mpi[pls].y+mouse1.changey;
      if(mpi[pls].y>mplayer.pl_d-mpi[pls].h)
         mpi[pls].y=mplayer.pl_d-mpi[pls].h;
      if(mpi[pls].y<mplayer.pl_u)
         mpi[pls].y=mplayer.pl_u;

 rectfill(player,mpi[pls].x-mpi[0].x,mplayer.pl_u-mpi[0].y,mpi[pls].x+mpi[pls].w-mpi[0].x,mplayer.pl_d-mpi[0].y,colour.white);
 for(i=mplayer.pl_u-mpi[0].y;i<=mplayer.pl_d-mpi[0].y;i++)
 {
  if(i%2)
  {
   for(j=mpi[pls].x-mpi[0].x;j<mpi[pls].x+mpi[pls].w+1-mpi[0].x;j=j+2)
   putpixel(player,j,i,colour.surface_grey);
  }
 else
  {
   for(j=mpi[pls].x+1-mpi[0].x;j<mpi[pls].x+mpi[pls].w+1-mpi[0].x;j=j+2)
   putpixel(player,j,i,colour.surface_grey);
  }
 }
         

buttons_related(player,mpi[pls].x-mpi[0].x,mpi[pls].y-mpi[0].y,mpi[pls].x+mpi[pls].w-mpi[0].x,mpi[pls].y+mpi[pls].h-mpi[0].y,630);           
blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
if(mouse1.changey>0)
  blit(player,dblbuffer,mpi[pls].x-mpi[0].x,mpi[pls].y-mouse1.changey-mpi[0].y,mpi[pls].x,mpi[pls].y-mouse1.changey,mpi[pls].w+1,mpi[pls].h+1+mouse1.changey);  
 else
  blit(player,dblbuffer,mpi[pls].x-mpi[0].x,mpi[pls].y-mpi[0].y,mpi[pls].x,mpi[pls].y,mpi[pls].w+1,mpi[pls].h+1-mouse1.changey);  

blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  

if(mouse1.changey>0)
  blit(dblbuffer,screen,mpi[pls].x,mpi[pls].y-mouse1.changey,mpi[pls].x,mpi[pls].y-mouse1.changey,mpi[pls].w+1,mpi[pls].h+1+mouse1.changey);
 else   
  blit(dblbuffer,screen,mpi[pls].x,mpi[pls].y,mpi[pls].x,mpi[pls].y,mpi[pls].w+1,mpi[pls].h+1-mouse1.changey);

   
 j = ( ((mpi[pls].y-mplayer.pl_u) * (( (mplayer.media_n-1)*17) - (mplayer.pl_d-mplayer.pl_u+30))) /((mplayer.pl_d-mplayer.pl_u)-mpi[pls].h) );
 j=j/17;
 if(j+mplayer.contain_pl<=mplayer.media_n)
 update_pl_scroll(j,2);

   
    }   
  }
}  

//=====================================================================================
void update_pl_scroll(int n,int type)
{
  int pls,i,j,k;
    pls=mplayer.first_pl_fn-1;
    j=mplayer.first_pl_fn;
  if(type==3)
  {
   type=1;
   rectfill(player,8,170,375,490,colour.white);     
  }
  for(i=n;i<n+mplayer.contain_pl;i++)
  {
    if(i<mplayer.media_n)
    {

    if(mplayer.song_played==i || mplayer.curr_media==i)
    {
      if(mplayer.song_played==i)
       rectfill(player,mpi[j].x-mpi[0].x,mpi[j].y+1-mpi[0].y,mpi[j].x+mpi[j].w-mpi[0].x,mpi[j].y+mpi[j].h-mpi[0].y-2,makecol(255,125,0) );
      else
       rectfill(player,mpi[j].x-mpi[0].x,mpi[j].y+1-mpi[0].y,mpi[j].x+mpi[j].w-mpi[0].x,mpi[j].y+mpi[j].h-mpi[0].y-2,colour.item_selected);      
     textprintf_ex(player,data[XSANS2].dat,10,mpi[j].y+2-mpi[0].y,colour.white,-1,"%d",i+1);
      if(i<99)
       textprintf_ex(player,data[XSANS2].dat,29,mpi[j].y+2-mpi[0].y,colour.white,-1,"%s",playlist[i].name);
      else
       textprintf_ex(player,data[XSANS2].dat,35,mpi[j].y+2-mpi[0].y,colour.white,-1,"%s",playlist[i].name);
      textprintf_ex(player,data[XSANS2].dat,340,mpi[j].y+2-mpi[0].y,colour.white,-1,"%d:%02d",playlist[i].min,playlist[i].sec);
    }
   else
   {
   if(playlist[i].selected==1)
    rectfill(player,mpi[j].x-mpi[0].x,mpi[j].y+1-mpi[0].y,mpi[j].x+mpi[j].w-mpi[0].x,mpi[j].y+mpi[j].h-mpi[0].y-2,makecol(190,255,0) );
   else
    rectfill(player,mpi[j].x-mpi[0].x,mpi[j].y+1-mpi[0].y,mpi[j].x+mpi[j].w-mpi[0].x,mpi[j].y+mpi[j].h-mpi[0].y-2,colour.white);   
     textprintf_ex(player,data[XSANS2].dat,10,mpi[j].y+2-mpi[0].y,colour.black,-1,"%d",i+1);
      if(i<99)
       textprintf_ex(player,data[XSANS2].dat,29,mpi[j].y+2-mpi[0].y,colour.black,-1,"%s",playlist[i].name);
      else
       textprintf_ex(player,data[XSANS2].dat,35,mpi[j].y+2-mpi[0].y,colour.black,-1,"%s",playlist[i].name);
     textprintf_ex(player,data[XSANS2].dat,340,mpi[j].y+2-mpi[0].y,colour.black,-1,"%d:%02d",playlist[i].min,playlist[i].sec);
   }
   j=j+1;
    }

  } 

if(type==1)
{
 rectfill(player,mpi[pls].x-mpi[0].x,mplayer.pl_u-mpi[0].y,mpi[pls].x+mpi[pls].w-mpi[0].x,mplayer.pl_d-mpi[0].y,colour.white);
 for(i=mplayer.pl_u-mpi[0].y;i<=mplayer.pl_d-mpi[0].y;i++)
 {
  if(i%2)
  {
   for(j=mpi[pls].x-mpi[0].x;j<mpi[pls].x+mpi[pls].w+1-mpi[0].x;j=j+2)
   putpixel(player,j,i,colour.surface_grey);
  }
 else
  {
   for(j=mpi[pls].x+1-mpi[0].x;j<mpi[pls].x+mpi[pls].w+1-mpi[0].x;j=j+2)
   putpixel(player,j,i,colour.surface_grey);
  }
 }
if(mpi[pls].h !=0)
{
j=n*17;
mpi[pls].y=( (j*((mplayer.pl_d-mplayer.pl_u)-mpi[pls].h)/(( (mplayer.media_n-1)*17) - (mplayer.pl_d-mplayer.pl_u+30)))+mplayer.pl_u);
if( n+mplayer.contain_pl==mplayer.media_n)
  mpi[pls].y=mplayer.pl_d-mpi[pls].h;
buttons_related(player,mpi[pls].x-mpi[0].x,mpi[pls].y-mpi[0].y,mpi[pls].x+mpi[pls].w-mpi[0].x,mpi[pls].y+mpi[pls].h-mpi[0].y,630);           
}
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(player,dblbuffer,mpi[pls].x-mpi[0].x,mplayer.pl_u-mpi[0].y,mpi[pls].x,mplayer.pl_u,mpi[pls].w+1,mplayer.pl_d+1-mplayer.pl_u);  
     blit(player,dblbuffer,mpi[mplayer.first_pl_fn].x-mpi[0].x,mpi[mplayer.first_pl_fn].y-mpi[0].y,mpi[mplayer.first_pl_fn].x,mpi[mplayer.first_pl_fn].y,mpi[mplayer.first_pl_fn].w+1,mpi[mplayer.first_pl_fn].h*mplayer.contain_pl);
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[mplayer.first_pl_fn].x,mpi[mplayer.first_pl_fn].y,mpi[mplayer.first_pl_fn].x,mpi[mplayer.first_pl_fn].y,mpi[mplayer.first_pl_fn].w+36,mpi[mplayer.first_pl_fn].h*mplayer.contain_pl);
     mplayer.first_pl_n=n;

}

else
{
     blit(player,dblbuffer,mpi[mplayer.first_pl_fn].x-mpi[0].x,mpi[mplayer.first_pl_fn].y-mpi[0].y,mpi[mplayer.first_pl_fn].x,mpi[mplayer.first_pl_fn].y,mpi[mplayer.first_pl_fn].w+1,mpi[mplayer.first_pl_fn].h*mplayer.contain_pl);
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,mpi[mplayer.first_pl_fn].x,mpi[mplayer.first_pl_fn].y,mpi[mplayer.first_pl_fn].x,mpi[mplayer.first_pl_fn].y,mpi[mplayer.first_pl_fn].w+1,mpi[mplayer.first_pl_fn].h*mplayer.contain_pl);
     mplayer.first_pl_n=n;
}

}
//======================================










//                      EMPTY








//======================================

void do_pv_scrolls(int n, int *pan_vol)
{
 int i,j;
 if(mpi[n].selected==1 && mouse1.changex!=0)
 {
      mpi[n].x=mpi[n].x+mouse1.changex;
      if(mpi[n].x>mplayer.pv_r-mpi[n].w)
         mpi[n].x=mplayer.pv_r-mpi[n].w;
      if(mpi[n].x<mplayer.pv_l)
         mpi[n].x=mplayer.pv_l;
 if(mpi[n].y-mpi[0].y<150)
  blit(mpdata[mplayer.theme].dat,player,177,140,177,140,364-177+1,151-140+1);
 else
  blit(mpdata[mplayer.theme].dat,player,177,153,177,153,364-177+1,12);

 if(((mpi[n].x-mplayer.pv_l)*255 )/((mplayer.pv_r-mplayer.pv_l)-mpi[n].w)!=128)
   blit(mpdata[mplayer.theme].dat,player,154,505,mpi[n].x-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].w,mpi[n].h);
 else
   blit(mpdata[mplayer.theme].dat,player,154,524,mpi[n].x-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].w,mpi[n].h);
      
blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
if(mouse1.changex>0)
  blit(player,dblbuffer,mpi[n].x-mouse1.changex-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].x-mouse1.changex,mpi[n].y,mpi[n].w+1+mouse1.changex,mpi[n].h+1);  
 else
  blit(player,dblbuffer,mpi[n].x-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].x,mpi[n].y,mpi[n].w+1-mouse1.changex,mpi[n].h+1);  

blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  

if(mouse1.changex>0)
  blit(dblbuffer,screen,mpi[n].x-mouse1.changex,mpi[n].y,mpi[n].x-mouse1.changex,mpi[n].y,mpi[n].w+1+mouse1.changex,mpi[n].h+1);
 else   
  blit(dblbuffer,screen,mpi[n].x,mpi[n].y,mpi[n].x,mpi[n].y,mpi[n].w+1-mouse1.changex,mpi[n].h+1);


*pan_vol=((mpi[n].x-mplayer.pv_l)*255 )/((mplayer.pv_r-mplayer.pv_l)-mpi[n].w);   
if(mplayer.play==1)
  almp3_adjust_mp3stream(music->s,mplayer.volume,mplayer.pan,1000);
   
  }
}  

//======================================================================
void do_seeker_scrolls()
{
 int n,i,j;
 n=7;
 if(mpi[n].selected==1 && mouse1.changex!=0)
 {
      mpi[n].x=mpi[n].x+mouse1.changex;
      if(mpi[n].x>mplayer.seeker_r-mpi[n].w)
         mpi[n].x=mplayer.seeker_r-mpi[n].w;
      if(mpi[n].x<mplayer.seeker_l)
         mpi[n].x=mplayer.seeker_l;

  blit(mpdata[mplayer.theme].dat,player,7,117,7,117,392-7+1,132-117+1);
  blit(mpdata[mplayer.theme].dat,player,168,503,mpi[n].x-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].w,mpi[n].h);

blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
if(mouse1.changex>0)
  blit(player,dblbuffer,mpi[n].x-mouse1.changex-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].x-mouse1.changex,mpi[n].y,mpi[n].w+1+mouse1.changex,mpi[n].h+1);  
 else
  blit(player,dblbuffer,mpi[n].x-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].x,mpi[n].y,mpi[n].w+1-mouse1.changex,mpi[n].h+1);  

blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  

if(mouse1.changex>0)
  blit(dblbuffer,screen,mpi[n].x-mouse1.changex,mpi[n].y,mpi[n].x-mouse1.changex,mpi[n].y,mpi[n].w+1+mouse1.changex,mpi[n].h+1);
 else   
  blit(dblbuffer,screen,mpi[n].x,mpi[n].y,mpi[n].x,mpi[n].y,mpi[n].w+1-mouse1.changex,mpi[n].h+1);

   
// j = ( ((mpi[n].y-mplayer.pl_u) * (( (mplayer.media_n-1)*17) - (mplayer.pl_d-mplayer.pl_u+30))) /((mplayer.pl_d-mplayer.pl_u)-mpi[n].h) );
// j=j/17;
// if(j+mplayer.contain_pl<=mplayer.media_n)
// update_pl_scroll(j,2);

   
  }
}  



//==========================================================================================
void update_seeker_scroll()
{
 int n,x2;
 long s_r,s_l,w,c_run,t_run;
 n=7;
//j = ( ((mpi[pls].y-mplayer.pl_u) * (( (mplayer.media_n-1)*17) - (mplayer.pl_d-mplayer.pl_u+30))) /((mplayer.pl_d-mplayer.pl_u)-mpi[pls].h) );
//mpi[pls].y=( (j*((mplayer.pl_d-mplayer.pl_u)-mpi[pls].h)/(( (mplayer.media_n-1)*17) - (mplayer.pl_d-mplayer.pl_u+30)))+mplayer.pl_u);
//*pan_vol=((mpi[n].x-mplayer.pv_l)*255 )/((mplayer.pv_r-mplayer.pv_l)-mpi[n].w);   
s_r=mplayer.seeker_r;
s_l=mplayer.seeker_l;
w=mpi[n].w;
c_run=(mplayer.run_min*60)+mplayer.run_sec;
t_run=mplayer.total_sec;
//textprintf_ex(screen,font,5,60,5674,-1,"%d %d",c_run,t_run);
//readkey();


x2=mpi[n].x;
mpi[n].x=( ((s_r-s_l-w)*c_run )/t_run)+s_l;
x2=mpi[n].x-x2;
  blit(mpdata[mplayer.theme].dat,player,7,117,7,117,392-7+1,132-117+1);
  blit(mpdata[mplayer.theme].dat,player,168,503,mpi[n].x-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].w,mpi[n].h);

if(mplayer.active==1)
{
blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
if(x2>0)
  blit(player,dblbuffer,mpi[n].x-x2-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].x-x2,mpi[n].y,mpi[n].w+1+x2,mpi[n].h+1);  
 else
  blit(player,dblbuffer,mpi[n].x-mpi[0].x,mpi[n].y-mpi[0].y,mpi[n].x,mpi[n].y,mpi[n].w+1-x2,mpi[n].h+1);  

blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  

if(x2>0)
  blit(dblbuffer,screen,mpi[n].x-x2,mpi[n].y,mpi[n].x-x2,mpi[n].y,mpi[n].w+1+x2,mpi[n].h+1);
 else   
  blit(dblbuffer,screen,mpi[n].x,mpi[n].y,mpi[n].x,mpi[n].y,mpi[n].w+1-x2,mpi[n].h+1);
}

}

