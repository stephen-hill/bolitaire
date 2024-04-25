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

/*
This software is a work from yzonesoft, you are allowed to modify it and distribute it.
The things you are not allowed to do are the following
1) Removing my credits
2) making money with it 

   __  __
  \  \/ / 
   \ / /   ___   __     __    __      ___   __  ___  __          __    __   __
    | |      /  |  |  |/  |  |_      \__   |  |  |  |_   |   |  /__\  |__| |_
    |_|    /__  |__|  |   |  |__      __/  |__|  |  |    \/\/   |  |  | \  |__

                                                                  by Yogesh M     

for more info read readme.txt
for compiling this software read readme.txt
*/

#include"allegro.h"
#include "jpgalleg.h"
#include "bol.h"

int init_driver(void)
{
int retrn=1;
int tmp;
jpgalleg_init();   
install_keyboard();
install_timer();
srand(time(0));

 printf("Bolitaire 0.62a (c) 2005 Yogesh \n");
 printf("covered by GNU GPL licence \n"); 
 if(settings.mplayer==1)
 {
   if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0 )
   {
     printf("ERROR INITIALIZING SOUND \n");
     printf("Damn! you cannot use mp3 player. Hidding mp3 player. \n");        
     settings.mplayer=0;
     //install_sound (DIGI_NONE, MIDI_NONE, NULL);
   }
   else
     printf("SOUND INITIALIZED SUCCESSFULLY \n");
 }                   

 if(settings.custom_driver==1)
 {
   set_color_depth(settings.color);
   if(set_gfx_mode(settings.custom_driver_name, settings.custom_w,settings.custom_h, 0, 0) >= 0)
    printf("%d %s",tmp,"BIT GRAPHICS INITIALIZED SUCCESSFULLY\n");
   else
    printf("%s","GRAPHICS INITIALIZATION UNSUCCESSFULL, TRY DIFFERENT GRAPHICS DRIVER, COLOR DEPTH, SCREEN WIDTH AND HEIGHT\n");      
 }

if(windows_version==1 && settings.custom_driver==0)
{
 tmp=settings.color;
 if(settings.fullscreen==1)
 {
   while(tmp>=8)
   {
     set_color_depth(tmp);
     if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 800,600, 0, 0) >= 0)
     {
       if(tmp>8)
       {
         if(tmp==settings.color)
          printf("%d %s",tmp,"BIT GRAPHICS INITIALIZED SUCCESSFULLY\n");
         else
          printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY\n");        
         global.colour_depth=2;
       }
       else
       {
         if(tmp==settings.color)
          printf("%d %s",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION. \n");
         else
          printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION.\n");                
         settings.background=0;
         global.colour_depth=1;        
       }
       break;
     }
     tmp=tmp-8;
   }

   if(tmp<8)
   {
     retrn=0;
     printf("%s","N0 SUPPORTED GRAPHICS MODE FOUND. QUITTING\n");
   } 
 }

 if(settings.fullscreen==0)
 {
  tmp=settings.color;
  while(tmp>=8)
  {
    set_color_depth(tmp);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 648,520, 0, 0) >= 0)
    {
      if(tmp>8)
      {
        if(tmp==settings.color)
         printf("%d %s",tmp,"BIT GRAPHICS INITIALIZED SUCCESSFULLY\n");
        else
         printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY\n");        
        global.colour_depth=2;
      }
      else
      {
        if(tmp==settings.color)
         printf("%d %s",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION. \n");
        else
         printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION.\n");                
        settings.background=0;
        global.colour_depth=1;        
      }
      break;
    }
    tmp=tmp-8;
  }
  if(tmp<8)
  {
   retrn=0;
   printf("%s","N0 SUPPORTED GRAPHICS MODE FOUND. QUITTING\n");
  } 

 }
}


if(linux_version==1  && settings.custom_driver==0)
{
tmp=settings.color;
while(tmp>=8)
{
  set_color_depth(tmp);
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 648,520, 0, 0) >= 0)
  {
     if(tmp>8)
     {
       if(tmp==settings.color)
         printf("%d %s",tmp,"BIT GRAPHICS INITIALIZED SUCCESSFULLY\n");
        else
         printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY\n");        
       global.colour_depth=2;
     }
     else
     {
       if(tmp==settings.color)
         printf("%d %s",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION. \n");
        else
         printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION.\n");                
       settings.background=0;
       global.colour_depth=1;        
     }
    break;
  }
  tmp=tmp-8;
}
if(tmp<8)
 {
 retrn=0;
 printf("%s","N0 SUPPORTED GRAPHICS MODE FOUND. QUITTING\n");
 } 
}


if(beos_version==1  && settings.custom_driver==0)
{
tmp=settings.color;
while(tmp>=8)
{
  set_color_depth(tmp);
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 648,520, 0, 0) >= 0)
  {
     if(tmp>8)
     {
       if(tmp==settings.color)
         printf("%d %s",tmp,"BIT GRAPHICS INITIALIZED SUCCESSFULLY\n");
        else
         printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY\n");        
       global.colour_depth=2;
     }
     else
     {
       if(tmp==settings.color)
         printf("%d %s",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION. \n");
        else
         printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION.\n");                
       settings.background=0;
       global.colour_depth=1;        
     }
    break;
  }
  tmp=tmp-8;
}
if(tmp<8)
 {
 retrn=0;
 printf("%s","N0 SUPPORTED GRAPHICS MODE FOUND. QUITTING\n");
 } 
}



if(dos_version==1  && settings.custom_driver==0)
{
tmp=settings.color;
while(tmp>=8)
{
  set_color_depth(tmp);
  if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 800,600, 0, 0) >= 0)
  {
     if(tmp>8)
     {
       if(tmp==settings.color)
         printf("%d %s",tmp,"BIT GRAPHICS INITIALIZED SUCCESSFULLY\n");
        else
         printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY\n");        
       global.colour_depth=2;
     }
     else
     {
       if(tmp==settings.color)
         printf("%d %s",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION. \n");
        else
         printf("%s %d %s %d %s","SORRY!",settings.color,"BIT COLOR NOT AVAILABLE, ",tmp,"BIT COLOR INITIALIZED SUCCESSFULLY, BUT THE BACKGROUND SELECTION IS ONLY AVAILABLE AT HIGHER COLOR RESOLUTION.\n");                
       settings.background=0;
       global.colour_depth=1;        
     }
    break;
  }
  tmp=tmp-8;
}
if(tmp<8)
 {
 retrn=0;
 printf("%s","N0 SUPPORTED GRAPHICS MODE FOUND. QUITTING\n");
 } 
}


 if (install_mouse() < 0)
 {
   printf("NO MOUSE DETECTED BUT YOU NEED ONE. QUITTING.");
   //set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
   //allegro_message("NO MOUSE DETECTED BUT YOU NEED ONE. QUITTING.");        
   retrn=0;
 }
 else
   printf("MOUSE DETECTED \n");

 return (retrn);

}
