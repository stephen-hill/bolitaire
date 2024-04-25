#define MAX_FORMS 250    //maximum forms that can be created
#define MAX_ACTIVE 100   //maximum forms that can be active
#define MAX_CARD_L 21
#define MAX_FD 80  //maximum length of a file or a folder
#define MAXSONGS 400    /* maximum sons in playlist*/
#define MAXM_PATH 256/* the maximum size of the file path, used in mplayer playlist*/

char *menus[3][8];
char game_path[256];
char bg_path[256];
char mp3_path[256];
char curr_dir[256];

int dos_version;
int windows_version;
int linux_version;
int beos_version;

int get_game_number;
int cursor_pos_textbox;

int temp_background;  //to store settings.background temporarily


int menus_flag[3][8];
int menu_select_F; //if 1 then a sub_menu is clicked or entered

int menustart;
int EXIT_PROGRAM;
int curr_win;
int curr_loss;

int game_number;
int cards_left;
int main_menu_sel_f;
int do_mouse_over;
int show_undo;
int show_restart;
int P_submenu;

int xtra_x;  //the size of mouse that peeks out of the form
int dialog_fn;
int FOCUS_Y;
int card[9][MAX_CARD_L];    // current layout of cards, CARDs are ints
int freecell_top[9]; // frecell top spaces
int activeform[MAX_ACTIVE];     //active_forms_list
int active_number;    //increment or decrement  active_number,total active forums
int Prev_card;      //stores previous card form number
int Curr_card;      //stores current card form  number
int Prev_pos[2]; //stores the jth position of card[i][j]
int Curr_pos[2];  //to store current card position

int effects[13];  //here one can stor all the continous cards
int replace[12];
int replace2[10][14];
int store_rn2[10]; //stores r_n2 value for every r_n1,since r_n1 starts from 1

int mouseD_card[8];
int D_n;

int tmp_topcard;
int free_n;

int free_cell[9];    //to diff from structure
int fillcell[4];
int fillcolour[4]; //to see what cards are in fillcell 0-clubs 1-diamond 2-heart 3-spad

int change_mouse_area[4];  //0-xaxis,i-yaxis

int fn;  //form number
int overed; // to see anything in menu have been highlited
int menuselected; //ie main menu  0 for nothing, one for Game menu and 2 for Hel menu
int P_menu;  //Previous main menu selected

struct browser
{
int show; //1 or 0 to see browser have selected or not
int ampobe; //Activate MPlayer On Brower Exit
int mode; //1 for selecting song and 2 for selecting bakground
int up_fn; //that is where is that up button in form
int dir_n; //counts number of directories
int file_n; //counts number of files
int contain_dir; //number of folders that can be placed in the box
int contain_file;
int first_file_n; //first file displayed on the box
int first_dir_n;
int first_file_fn;  //stores the form number for the first file on box
int first_dir_fn;
int file_selected; //has the file_n for the single file selected
int dir_selected;  //has the dir_n for the dir selected
int file_scroll;  //contains forun number that contains scroller
int dir_scroll;
int f_u;  //upper limit of file scroller
int f_d;  //lower limit of file 
int d_u; 
int d_d;  
}browser;

struct directory
{
char name[MAX_FD];
int selected;
}directory[200];  //max directory

struct file
{
char name[MAX_FD];
long size;
int selected;
}file[400];  //max directory

struct pl
{
char s[MAXM_PATH];
char name[42];
int size_bytes; //size of mp3 in bytes
int min;  //song total time in min:sec
int sec;
int selected;
}playlist[MAXSONGS];

struct mplayer
{
int theme;
char song_played_path[MAXM_PATH];
int media_n;  //has number of songs in play list
int curr_media; //the song that need to be played
int song_played; // the song that is being played now  
int show;
int active;
int play;  //if 1 some song is playing else not
int n;          //simillar to fn
int first_time;
int clicked; // a flag to see that something is clicked
int volume;
int pan;
int run_min; //the current time of song playing
int run_sec; 
int run_size;
int seek;
int Prun_sec; 
int total_sec; //total length of the song 
 
int contain_pl;
int first_pl_n; //first file displayed in play list
int first_pl_fn;  //stores the mp number for the first file in playlist
int pl_u;  //upper limit of play list scroller
int pl_d;   

int pv_l; //for pan && volume
int pv_r;

int seeker_l;
int seeker_r;

}mplayer;
                              
struct mpi          //mplayer has its own forms
{
int type;
int h;
int w;
int x;
int y;
int selected;
int rselected;
int overed; //used in sub menus
int can_over; // 1 means an action performed on overriding, for type 3
}mpi[400];


struct freecell
{
int card_in;      //here fn is given
int type;
int x;
int y;
int w;
int h;
}freecell[8];

struct statistics
{
int last_game_status;  //1 complete   0 incomplete
int total_win;
int total_loss;
int win_streak;
int loss_streak;
int curr_streak; //0 for none, -ive for loss and =ive for win
int last_game_wl;  //0 for lose  1 for win  -1 for nothing
}statistics;

struct settings
{
char bg[80];
int custom_driver_name;
int custom_driver;
int custom_w;
int custom_h;
int color;
int fullscreen;
int status_bar;
int mplayer;
int ms_deal;  //1 true   0 false
int alrand_deal; //1 true  0 false
int animation;
int animation_speed;
int background;
}settings;


struct mouse1
{
int px;   //will be previous x and y for just a moment
int py;
int h;
int w;
int x;
int y;
int Fx;
int Fy;    //F - focus distance + mousex
int clicked;
int released;
int pressed;
int rclicked;
int rreleased;
int rpressed;

int changex;
int changey;
}mouse1;


struct form
{
int type;    //1 if card   2  for empty card   3 for normal form  21 for button
int card;  // the card number
int topcard;  //true or false
int n;         //tos store identity number
int w;
int h;
int x;
int y;
int Focus_y;  //extending the focus range
int selected;
int rselected;
int overed; //used in sub menus
int can_over; // 1 means an action performed on overriding, for type 3
}form[MAX_FORMS];


struct colour
{
int blue;
int black;
int white;
int surface_grey;
int dark_grey_boundry;
int light_grey_boundry;
int item_selected;
int transperent;
int bg_green_dark;
int bg_green_light;
}colour;


struct flag
{
int calc;
int check_mouse; //flag to run the function(to check mouse for change cursor only once
int change_mouse;  //flag to enable the function in draw_mouse to change cursor
int frees;  //if clicked a card then need to check freecells for free space only once
int dnb_lclick;  // do not bother about left click to check card clicks
int prob_click_events;
}flag;

struct global
{
int colour_depth;
int dialog_active;
int mouse_active;
int rselected;
int Fcardselected;
int cardselected;  //0 has form number; 1 has card
int r_clicked_form;  //here a single form number can be stored   right_clicked_form
int cell_num;        //can strore 1 cell number
int form_num;        //can store 1 form number
int free_ca;        //total free cells available
int free_fca;       //free cells available
int free_columns;     // free columns available;
int animation_speed;
int show_game_select;  //when 1 displays select game dialog
int menu_selected;
int show_king;    //When 1 enables king_move
int show_menu;
int restart_same_game;
int cheat;  //this is for easter egg
int redraw_screen;
int exit_program;
int xtra_menu_active;
int num_xtra_submenu; //number of extra submenu;
int exit_fn;
}global;


DATAFILE *data;

BITMAP *mouse;
BITMAP *mouse_bg;
BITMAP *temp;
BITMAP *buffer;
BITMAP *dblbuffer;
BITMAP *background;
BITMAP *cardtemp;    
BITMAP *cardtemp2;
BITMAP *timetemp;

BITMAP *form1;
BITMAP *form2;
  
BITMAP *bgsample; //to show the background preview

BITMAP *player;   
BITMAP *bgplayer;   


PACKFILE *statpack;


//In driver
int init_driver(void);

//in main
void cards_on_screen();
void special_game1(void);
void special_game2(void);

// In functions
void do_it_one_time();
void init_screen(int type);
void time_disp();
void ca_things(BITMAP *bitmap,char *s,int x,int y,int x1,int y1,int w,int h,int type);
void init_dir_files();
void buttons_related(BITMAP *bitmap,int x1,int y1,int x2,int y2,int button_type);
void draw_mouse();
void mouse_null(BITMAP *bitmap,int x,int y,int w,int h);
void mouse_screen(BITMAP *bitmap,int x,int y,int w,int h);
void apply_tranparent(BITMAP *bitmap,int type);
void add_transparent();
void look_for_mouse_click(void);
void process_mouse_click(void);
void alrand_deals(int gamenumber);
void ms_deals(int gamenumber);
int my_rand();
void my_srand(long s); 
void main_menu_selection();
void mouse_released_events();

//In functions 2
void init_freecell();
void place_cards();
void king_move();
void invert_card_color(BITMAP *bitmap);
void mouse_click_events();
void mouse_rclick_events();
void mouse_rrelease_events();
void mouse_over_events();
void calc_free_spaces();
void previous_card(int j);     //j is form number
void card_position(int c);      // c is card
int check_comptable(int card1,int card2);
int check_cell_cards(int card1);
void delete_form(int form_number_n,int form_number_fn);
void hotkeys();

//In function 3
void draw_submenu(int j);
void draw_submenu_pictures(int bg_color,int textcolor,int j);
void do_submenu_options();
void show_card_movement_on_screen(int z,int x,int y);

//In functions 4
void create_a_form(int x,int y,int w,int h);
void draw_dialog_outline(BITMAP *bitmap,int w,int h,int type);  //type 1 for full form(with close button...)  type 2 for simple dialog
void form_move(int *form_x,int *form_y,int form_w,int form_h,BITMAP *fgform,BITMAP *bgform);
void remove_dialog(void);
void do_statistics(void);
void stretch_image();  //stretches the king to 310x310
void draw_freecell();
long darken_pixel(long colour);
long lighten_pixel(long colour);
void change_mouse_cursor();
void shift_card(int up_down,int cell_form_num,int z);
void replace_cards();


//In almp3.c
void load_music();
void poll_music();
void mp3_on_screen();
void mplayer_click_events();
void mplayer_pressed_events();
void mplayer_released_events();
void list_pl(int n);
void do_pl_scrolls();
void do_pv_scrolls(int n,int *pan_vol);
void do_seeker_scrolls();
void init_pl_scroll_bars();
void update_pl_scroll(int n,int type);

//In browser.c
void browser_on_screen();
void initialize_dir_file();
void drive_buttons();
void update_file_scroll(int n,int type);
void update_dir_scroll(int n,int type);
void init_scroll_bars();
void do_scroll_bars();





