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
#include "bol.h"
#include "data.h"

   struct al_ffblk ffblk;
   char chrs[34];   
   
//   int P_y; //the previous position of mouse
   

void browser_on_screen()
{
  int i;

  browser.file_scroll=-1;
  browser.dir_scroll=-1;  
  browser.show=0;
  browser.ampobe=1;
  create_a_form(SCREEN_W/2-600/2,SCREEN_H/2-500/2,600,500);  
           textprintf_ex(form1,data[XSANS].dat,7,3,colour.white,-1,"Browser");      
           textprintf_ex(form1,data[XSANS].dat,8,3,colour.white,-1,"Browser");

  if(browser.mode==1)
   strcpy(curr_dir,mp3_path);
  else
   strcpy(curr_dir,bg_path);

 if(windows_version==1 || dos_version==1)
  {
    drive_buttons();
    browser.up_fn=fn;
    ca_things(form1,"Up",12,53,7,51,25,18,601);   //this is up button
    rectfill(form1,33,51,593,69,colour.dark_grey_boundry);
    textprintf_ex(form1,data[XSANS2].dat,42,54,colour.white,-1,"%s  %s","CWD:",curr_dir);    
      if(browser.mode==1)
      {
        browser.contain_dir=24;
        browser.contain_file=24;
        ca_things(form1,"1",0,0,8,75,289,388,611);  //this is foldor box
        ca_things(form1,"1",0,0,302,75,289,388,611);  //this is file box
        form[fn].n=41;
        ca_things(form1,"Select CWD",65,474,55,470,90,20,601); 
        form[fn].n=42;
        ca_things(form1,"Select folder",163,474,155,470,90,20,601);   
        form[fn].n=43;
        ca_things(form1,"Select file[s]",415,474,405,470,90,20,601);     
      }
      else
      {
        browser.contain_dir=25;
        browser.contain_file=17;
        ca_things(form1,"1",0,0,8,75,289,404,611);  //this is foldor box
        ca_things(form1,"1",0,0,302,75,289,276,611);  //this is file box
         rect(form1,315,361,440,486,colour.black);
        textprintf_ex(form1,data[XSANS2].dat,355,416,colour.black,-1,"Preview");
        form[fn].n=43;
         ca_things(form1,"Select background",461,417,452,413,125,20,601);     
      } 

  }
 else
  {
    browser.up_fn=fn;
    ca_things(form1,"Up",12,30,7,28,25,18,601);   //this is up button
    rectfill(form1,33,28,593,46,colour.dark_grey_boundry);
    textprintf_ex(form1,data[XSANS2].dat,42,31,colour.white,-1,"%s  %s","CWD:",curr_dir);
      if(browser.mode==1)
      {
        browser.contain_dir=25;
        browser.contain_file=25;
        ca_things(form1,"1",0,0,8,53,289,404,611);  //this is foldor box
        ca_things(form1,"1",0,0,302,53,289,404,611);  //this is file box
        form[fn].n=41;
        ca_things(form1,"Select CWD",65,472,55,468,90,20,601); 
        form[fn].n=42;
        ca_things(form1,"Select folder",163,472,155,468,90,20,601);   
        form[fn].n=43;
        ca_things(form1,"Select file[s]",415,472,405,468,90,20,601);     
      }
      else
      {
        browser.contain_dir=27;
        browser.contain_file=18;
        ca_things(form1,"1",0,0,8,53,289,436,611);  //this is foldor box
        ca_things(form1,"1",0,0,302,53,289,292,611);  //this is file box
//         rect(form1,302+81,330,591-81,455,colour.black);
         rect(form1,315,357,440,482,colour.black);
        textprintf_ex(form1,data[XSANS2].dat,355,412,colour.black,-1,"Preview");
        form[fn].n=43;
         ca_things(form1,"Select background",461,413,452,409,125,20,601);     
//        ca_things(form1,"Select background",414-18,466,405-18,462,125,20,601);     
//        ca_things(form1,"Select background",237+9,466,237,462,125,20,601);     
      } 
   
  }  

  if(browser.mode==1)
   chdir(mp3_path); 
  else
   chdir(bg_path); 


initialize_dir_file();  //this will st up the directroy.name and file.name
init_dir_files();

    blit(mouse_bg,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,form2,form[dialog_fn].x,form[dialog_fn].y,0,0,form[dialog_fn].w,form[dialog_fn].h);         
    blit(form1,dblbuffer,0,0,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h); 
    blit(dblbuffer,mouse_bg,mouse1.x,mouse1.y,0,0,mouse1.w,mouse1.h);         
    masked_blit(mouse,dblbuffer,0,0,mouse1.x,mouse1.y,mouse1.w,mouse1.h);
    blit(dblbuffer,screen,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].x,form[dialog_fn].y,form[dialog_fn].w,form[dialog_fn].h);         
init_scroll_bars();
update_file_scroll(0,1);
update_dir_scroll(0,1); 

}


//====================================================================
void initialize_dir_file()
{
  int done,i;
  
browser.dir_selected=-1;
browser.file_selected=-1;

browser.dir_n=0;
 done=al_findfirst("*.*",&ffblk,FA_DIREC | FA_RDONLY| FA_ARCH);
 while (!done)
 {
    if(strcmp(ffblk.name,".")!=0 && strcmp(ffblk.name,"..")!=0 &&ffblk.attrib!=0 && ffblk.attrib!=1 && ffblk.attrib!=32 && ffblk.attrib!=33)
    {
      strcpy(directory[browser.dir_n].name,ffblk.name);
      directory[browser.dir_n].selected=0;    
      browser.dir_n=browser.dir_n+1;
     }
    done = al_findnext(&ffblk);
 }
 al_findclose(&ffblk);
browser.first_dir_n=0; 

 browser.file_n=0;
if(browser.mode==2)
 done=al_findfirst("*.jpg",&ffblk,FA_ARCH|FA_RDONLY);
 else
 done=al_findfirst("*.mp3",&ffblk,FA_ARCH|FA_RDONLY); 

 while (!done)
 {
    strcpy(file[browser.file_n].name,ffblk.name);
    file[browser.file_n].selected=0;    
    file[browser.file_n].size=ffblk.size;    
    done = al_findnext(&ffblk);
//    textprintf_ex(form1,data[XSANS2].dat,350,150+i*20,colour.black,-1,"%d  %d",FA_ARCH,FA_RDONLY);
    browser.file_n=browser.file_n+1;
 }
 al_findclose(&ffblk);
browser.first_file_n=0;

}

//=========================================================================
void drive_buttons()
{
   int i,j;
   char s[3];
       s[0]=99;
       s[1]=':';
       s[2]='/';    
// textprintf_ex(form1,data[XSANS2].dat,50,100,colour.black,-1,"%s",s);       
    j=0;
    for(i=0;i<24;i++)
     {
       s[0]=67+i;

       if( chdir(s) ==0)
       {
           s[2]='\\';
           form[fn].n=s[0];
           ca_things(form1,s,11+j*29,29,7+j*29,26,25,18,601); 
           s[2]='/';
         j=j+1;
       }
     }

}
//========================================
void update_file_scroll(int n,int type)
{
  int fs,i,j,k;
    fs=browser.file_scroll;
    j=browser.first_file_fn;
    for(i=n;i<n+browser.contain_file;i++)
     {
       if(file[i].selected==1)
        {
                     for(k=0;k<34;k++)
                       chrs[k]=file[i].name[k];
                     chrs[k]='\0';  

        rectfill(form1,form[j].x-form[dialog_fn].x,form[j].y+1-form[dialog_fn].y,form[j].x+form[j].w-form[dialog_fn].x,form[j].y+form[j].h-form[dialog_fn].y-2,colour.item_selected);  
        textprintf_ex(form1,data[XSANS2].dat,form[j].x+2-form[dialog_fn].x,form[j].y+2-form[dialog_fn].y,colour.white,-1,"%s",chrs);
        form[j].selected=1;
        }
        else
        {
                     for(k=0;k<34;k++)
                       chrs[k]=file[i].name[k];
                     chrs[k]='\0';  

        rectfill(form1,form[j].x-form[dialog_fn].x,form[j].y+1-form[dialog_fn].y,form[j].x+form[j].w-form[dialog_fn].x,form[j].y+form[j].h-form[dialog_fn].y-2,colour.white);  
        if(i<browser.file_n) //this is to redraw the file on new directory selection
        textprintf_ex(form1,data[XSANS2].dat,form[j].x+2-form[dialog_fn].x,form[j].y+2-form[dialog_fn].y,colour.black,-1,"%s",chrs);
        form[j].selected=0;
//        blit(form1,screen,0,0,0,0,form[dialog_fn].w,form[dialog_fn].h);
//        readkey();
        }
        j=j+1;     
     }

if(type==1)
{
 rectfill(form1,form[fs].x-form[dialog_fn].x,browser.f_u-form[dialog_fn].y,form[fs].x+form[fs].w-form[dialog_fn].x,browser.f_d-form[dialog_fn].y,colour.white);
 for(i=browser.f_u-form[dialog_fn].y;i<=browser.f_d-form[dialog_fn].y;i++)
 {
  if(i%2)
  {
   for(j=form[fs].x-form[dialog_fn].x;j<form[fs].x+form[fs].w+1-form[dialog_fn].x;j=j+2)
   putpixel(form1,j,i,colour.surface_grey);
  }
 else
  {
   for(j=form[fs].x+1-form[dialog_fn].x;j<form[fs].x+form[fs].w+1-form[dialog_fn].x;j=j+2)
   putpixel(form1,j,i,colour.surface_grey);
  }
 }
j=n*17;
form[fs].y=( (j*((browser.f_d-browser.f_u)-form[fs].h)/(( (browser.file_n-1)*17) - (browser.f_d-browser.f_u+30)))+browser.f_u);
if( n+browser.contain_file==browser.file_n)
  form[fs].y=browser.f_d-form[fs].h;
buttons_related(form1,form[fs].x-form[dialog_fn].x,form[fs].y-form[dialog_fn].y,form[fs].x+form[fs].w-form[dialog_fn].x,form[fs].y+form[fs].h-form[dialog_fn].y,630);           

     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
blit(form1,dblbuffer,form[fs].x-form[dialog_fn].x,browser.f_u-form[dialog_fn].y,form[fs].x,browser.f_u,form[fs].w+1,browser.f_d+1-browser.f_u);  
     blit(form1,dblbuffer,form[browser.first_file_fn].x-form[dialog_fn].x,form[browser.first_file_fn].y-form[dialog_fn].y,form[browser.first_file_fn].x,form[browser.first_file_fn].y,form[browser.first_file_fn].w+1,form[browser.first_file_fn].h*browser.contain_file);
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,form[browser.first_file_fn].x,form[browser.first_file_fn].y,form[browser.first_file_fn].x,form[browser.first_file_fn].y,form[browser.first_file_fn].w+36,form[browser.first_file_fn].h*browser.contain_file);
     browser.first_file_n=n;

}

else
{
     blit(form1,dblbuffer,form[browser.first_file_fn].x-form[dialog_fn].x,form[browser.first_file_fn].y-form[dialog_fn].y,form[browser.first_file_fn].x,form[browser.first_file_fn].y,form[browser.first_file_fn].w+1,form[browser.first_file_fn].h*browser.contain_file);
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,form[browser.first_file_fn].x,form[browser.first_file_fn].y,form[browser.first_file_fn].x,form[browser.first_file_fn].y,form[browser.first_file_fn].w+1,form[browser.first_file_fn].h*browser.contain_file);
     browser.first_file_n=n;
}

}

//================================================================================================
void update_dir_scroll(int n,int type)
{
  int ds,i,j,k;
    ds=browser.dir_scroll;
    j=browser.first_dir_fn;
    for(i=n;i<n+browser.contain_dir;i++)
     {
       if(directory[i].selected==1)
        {
                     for(k=0;k<34;k++)
                       chrs[k]=directory[i].name[k];
                     chrs[k]='\0';  

        rectfill(form1,form[j].x-form[dialog_fn].x,form[j].y+1-form[dialog_fn].y,form[j].x+form[j].w-form[dialog_fn].x,form[j].y+form[j].h-form[dialog_fn].y-2,colour.item_selected);  
        textprintf_ex(form1,data[XSANS2].dat,form[j].x+2-form[dialog_fn].x,form[j].y+2-form[dialog_fn].y,colour.white,-1,"%s",chrs);
        form[j].selected=1;
        }
        else
        {
                     for(k=0;k<34;k++)
                       chrs[k]=directory[i].name[k];
                     chrs[k]='\0';  

        rectfill(form1,form[j].x-form[dialog_fn].x,form[j].y+1-form[dialog_fn].y,form[j].x+form[j].w-form[dialog_fn].x,form[j].y+form[j].h-form[dialog_fn].y-2,colour.white);  
        if(i<browser.dir_n) //this is to redraw the dir on new directory selection
        textprintf_ex(form1,data[XSANS2].dat,form[j].x+2-form[dialog_fn].x,form[j].y+2-form[dialog_fn].y,colour.black,-1,"%s",chrs);
        form[j].selected=0;
//        blit(form1,screen,0,0,0,0,form[dialog_fn].w,form[dialog_fn].h);
//        readkey();
        }
        j=j+1;     
     }

if(type==1)
{
 rectfill(form1,form[ds].x-form[dialog_fn].x,browser.d_u-form[dialog_fn].y,form[ds].x+form[ds].w-form[dialog_fn].x,browser.d_d-form[dialog_fn].y,colour.white);
 for(i=browser.d_u-form[dialog_fn].y;i<=browser.d_d-form[dialog_fn].y;i++)
 {
  if(i%2)
  {
   for(j=form[ds].x-form[dialog_fn].x;j<form[ds].x+form[ds].w+1-form[dialog_fn].x;j=j+2)
   putpixel(form1,j,i,colour.surface_grey);
  }
 else
  {
   for(j=form[ds].x+1-form[dialog_fn].x;j<form[ds].x+form[ds].w+1-form[dialog_fn].x;j=j+2)
   putpixel(form1,j,i,colour.surface_grey);
  }
 }
j=n*17;
form[ds].y=( (j*((browser.d_d-browser.d_u)-form[ds].h)/(( (browser.dir_n-1)*17) - (browser.d_d-browser.d_u+30)))+browser.d_u);
if( n+browser.contain_dir==browser.dir_n)
  form[ds].y=browser.d_d-form[ds].h;
buttons_related(form1,form[ds].x-form[dialog_fn].x,form[ds].y-form[dialog_fn].y,form[ds].x+form[ds].w-form[dialog_fn].x,form[ds].y+form[ds].h-form[dialog_fn].y,630);           

     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
blit(form1,dblbuffer,form[ds].x-form[dialog_fn].x,browser.f_u-form[dialog_fn].y,form[ds].x,browser.f_u,form[ds].w+1,browser.f_d+1-browser.f_u);  
     blit(form1,dblbuffer,form[browser.first_dir_fn].x-form[dialog_fn].x,form[browser.first_dir_fn].y-form[dialog_fn].y,form[browser.first_dir_fn].x,form[browser.first_dir_fn].y,form[browser.first_dir_fn].w+1,form[browser.first_dir_fn].h*browser.contain_dir);
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,form[browser.first_dir_fn].x,form[browser.first_dir_fn].y,form[browser.first_dir_fn].x,form[browser.first_dir_fn].y,form[browser.first_dir_fn].w+36,form[browser.first_dir_fn].h*browser.contain_dir);
     browser.first_dir_n=n;

}

else
{
     blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
     blit(form1,dblbuffer,form[browser.first_dir_fn].x-form[dialog_fn].x,form[browser.first_dir_fn].y-form[dialog_fn].y,form[browser.first_dir_fn].x,form[browser.first_dir_fn].y,form[browser.first_dir_fn].w+1,form[browser.first_dir_fn].h*browser.contain_dir);
     blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
     masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  
     blit(dblbuffer,screen,form[browser.first_dir_fn].x,form[browser.first_dir_fn].y,form[browser.first_dir_fn].x,form[browser.first_dir_fn].y,form[browser.first_dir_fn].w+1,form[browser.first_dir_fn].h*browser.contain_dir);
     browser.first_dir_n=n;
}

}


//=====================================================================================
void init_scroll_bars()
{
 int i,j,fs,ds;
 fs=browser.file_scroll;
 ds=browser.dir_scroll;
 
 if(browser.file_n>browser.contain_file)
 {
   form[browser.file_scroll].w=15;
   form[browser.file_scroll].h=( ((browser.f_d-browser.f_u) *(browser.f_d-browser.f_u+30)) /(browser.file_n*17) );
   form[browser.file_scroll].y=browser.f_u;
 }
else
 {
   form[browser.file_scroll].w=0;
   form[browser.file_scroll].h=0;
   form[browser.file_scroll].y=0;
 }



 if(browser.dir_n>browser.contain_dir)
 {
   form[browser.dir_scroll].w=15;
   form[browser.dir_scroll].h=( ((browser.d_d-browser.d_u) *(browser.d_d-browser.d_u+30)) /(browser.dir_n*17) );
   form[browser.dir_scroll].y=browser.d_u;
 }
else
 {
   form[browser.dir_scroll].w=0;
   form[browser.dir_scroll].h=0;
   form[browser.dir_scroll].y=0;
 }



}

//====================================================================================
void do_scroll_bars()
{
 int fs,ds,i,j;

  if(form[browser.file_scroll].selected==1)
   {
   fs=browser.file_scroll;
   if(form[browser.file_scroll].selected==1 && mouse1.changey!=0)
    {
      form[fs].y=form[fs].y+mouse1.changey;
      if(form[fs].y>browser.f_d-form[fs].h)
         form[fs].y=browser.f_d-form[fs].h;
      if(form[fs].y<browser.f_u)
         form[fs].y=browser.f_u;

 rectfill(form1,form[fs].x-form[dialog_fn].x,browser.f_u-form[dialog_fn].y,form[fs].x+form[fs].w-form[dialog_fn].x,browser.f_d-form[dialog_fn].y,colour.white);
 for(i=browser.f_u-form[dialog_fn].y;i<=browser.f_d-form[dialog_fn].y;i++)
 {
  if(i%2)
  {
   for(j=form[fs].x-form[dialog_fn].x;j<form[fs].x+form[fs].w+1-form[dialog_fn].x;j=j+2)
   putpixel(form1,j,i,colour.surface_grey);
  }
 else
  {
   for(j=form[fs].x+1-form[dialog_fn].x;j<form[fs].x+form[fs].w+1-form[dialog_fn].x;j=j+2)
   putpixel(form1,j,i,colour.surface_grey);
  }
 }
         

buttons_related(form1,form[fs].x-form[dialog_fn].x,form[fs].y-form[dialog_fn].y,form[fs].x+form[fs].w-form[dialog_fn].x,form[fs].y+form[fs].h-form[dialog_fn].y,630);           
blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
if(mouse1.changey>0)
  blit(form1,dblbuffer,form[fs].x-form[dialog_fn].x,form[fs].y-mouse1.changey-form[dialog_fn].y,form[fs].x,form[fs].y-mouse1.changey,form[fs].w+1,form[fs].h+1+mouse1.changey);  
 else
  blit(form1,dblbuffer,form[fs].x-form[dialog_fn].x,form[fs].y-form[dialog_fn].y,form[fs].x,form[fs].y,form[fs].w+1,form[fs].h+1-mouse1.changey);  

blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  

if(mouse1.changey>0)
  blit(dblbuffer,screen,form[fs].x,form[fs].y-mouse1.changey,form[fs].x,form[fs].y-mouse1.changey,form[fs].w+1,form[fs].h+1+mouse1.changey);
 else   
  blit(dblbuffer,screen,form[fs].x,form[fs].y,form[fs].x,form[fs].y,form[fs].w+1,form[fs].h+1-mouse1.changey);

   
 j = ( ((form[fs].y-browser.f_u) * (( (browser.file_n-1)*17) - (browser.f_d-browser.f_u+30))) /((browser.f_d-browser.f_u)-form[fs].h) );
 j=j/17;
 if(j+browser.contain_file<=browser.file_n)
 update_file_scroll(j,2);

   
    }   
  }


  if(form[browser.dir_scroll].selected==1)
   {
   ds=browser.dir_scroll;
   if(form[browser.dir_scroll].selected==1 && mouse1.changey!=0)
    {
      form[ds].y=form[ds].y+mouse1.changey;
      if(form[ds].y>browser.d_d-form[ds].h)
         form[ds].y=browser.d_d-form[ds].h;
      if(form[ds].y<browser.d_u)
         form[ds].y=browser.d_u;

 rectfill(form1,form[ds].x-form[dialog_fn].x,browser.d_u-form[dialog_fn].y,form[ds].x+form[ds].w-form[dialog_fn].x,browser.d_d-form[dialog_fn].y,colour.white);
 for(i=browser.d_u-form[dialog_fn].y;i<=browser.d_d-form[dialog_fn].y;i++)
 {
  if(i%2)
  {
   for(j=form[ds].x-form[dialog_fn].x;j<form[ds].x+form[ds].w+1-form[dialog_fn].x;j=j+2)
   putpixel(form1,j,i,colour.surface_grey);
  }
 else
  {
   for(j=form[ds].x+1-form[dialog_fn].x;j<form[ds].x+form[ds].w+1-form[dialog_fn].x;j=j+2)
   putpixel(form1,j,i,colour.surface_grey);
  }
 }
         

buttons_related(form1,form[ds].x-form[dialog_fn].x,form[ds].y-form[dialog_fn].y,form[ds].x+form[ds].w-form[dialog_fn].x,form[ds].y+form[ds].h-form[dialog_fn].y,630);           
blit(mouse_bg,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h); 
if(mouse1.changey>0)
  blit(form1,dblbuffer,form[ds].x-form[dialog_fn].x,form[ds].y-mouse1.changey-form[dialog_fn].y,form[ds].x,form[ds].y-mouse1.changey,form[ds].w+1,form[ds].h+1+mouse1.changey);  
 else
  blit(form1,dblbuffer,form[ds].x-form[dialog_fn].x,form[ds].y-form[dialog_fn].y,form[ds].x,form[ds].y,form[ds].w+1,form[ds].h+1-mouse1.changey);  

blit(dblbuffer,mouse_bg,mouse1.Fx,mouse1.Fy,0,0,mouse1.w,mouse1.h); 
masked_blit(mouse,dblbuffer,0,0,mouse1.Fx,mouse1.Fy,mouse1.w,mouse1.h);  

if(mouse1.changey>0)
  blit(dblbuffer,screen,form[ds].x,form[ds].y-mouse1.changey,form[ds].x,form[ds].y-mouse1.changey,form[ds].w+1,form[ds].h+1+mouse1.changey);
 else   
  blit(dblbuffer,screen,form[ds].x,form[ds].y,form[ds].x,form[ds].y,form[ds].w+1,form[ds].h+1-mouse1.changey);

   
 j = ( ((form[ds].y-browser.d_u) * (( (browser.dir_n-1)*17) - (browser.d_d-browser.d_u+30))) /((browser.d_d-browser.d_u)-form[ds].h) );
 j=j/17;
 if(j+browser.contain_dir<=browser.dir_n)
 update_dir_scroll(j,2);

   
    }   
  }


}
