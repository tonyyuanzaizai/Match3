#ifndef __Match3_Constants_H__
#define __Match3_Constants_H__

class Constants
{

public:
    static int W;//声明静态数据成员
    static int H;
    static bool g_DEBUG;
    static char* LOAD_COMPLETE;
    static char* MOUSE_DOWN;
    static char* MOUSE_UP;
    static char* MOUSE_MOVE;
    static int CELL_SIZE;
    static int FIELD_OFFSET_X;
    static int FIELD_OFFSET_Y;
    static float EXCHANGE_TIME;
    static float MATCH_TIME;
    static int GRAVITY_ACC;
    static int ASSETS_WIDTH;
    static int ASSETS_HEIGHT;
    static int PIXEL_RATIO;
    static int SCREEN_HEIGHT;
    static int SCREEN_SCALE;
    static int DPI;
    static bool DEBUG_MODE;
    static char* COLOR_PINK;
    static char* COLOR_BLUE;
    static char* IMAGE_BUTTON_CLOSE;
    static char* IMAGE_BUTTON_SOUND_ON;
    static char* IMAGE_BUTTON_SOUND_OFF;
    static char* IMAGE_BUTTON_EXIT;
    static char* IMAGE_BUTTON_PAUSE;
    static char* IMAGE_BUTTON_RESTART;
    static char* IMAGE_BUTTON_PLAY;
    static char* IMAGE_AWESOME;
    static char* IMAGE_SUPERB;
    static char* IMAGE_SHINING;
    static char* IMAGE_DROP;
    static char* IMAGE_BACK;
    static char* IMAGE_DONUT;
    static char* IMAGE_ARROW_BONUS_VERT;
    static char* IMAGE_ARROW_BONUS_HOR;
    static char* IMAGE_BOMB;
    static char* IMAGE_MESSAGE_WINDOW;
    static char* IMAGE_HINT_ARROW;
    static char* IMAGE_GAMEOVER_CAPTION;
    static char* IMAGE_TITLE_MAIN_MENU_BACK;
    static char* IMAGE_SICKLE;
    static char* IMAGE_ROTATE;
    static char* IMAGE_BIG_SHINING;
    static char* IMAGE_POINTS_CONTROL_BIG;
    static char* IMAGE_POINTS_CONTROL_SMALL;
    static char* IMAGE_LEVEL_BUTTON;
    static char* IMAGE_DIRT;
    static char* IMAGE_GUI;
    static char* IMAGE_LOCK;
    static char* IMAGE_OUT_OF_MOVES;
    static char* IMAGE_WIN_CAPTION;
    static char* IMAGE_STONE_HEART;
    static char* IMAGE_TASK_PANEL;
    static char* IMAGE_HEART_PARTICLE;
    static char* IMAGE_WIN_STRINGS;
    static char* IMAGE_GLOBAL_MAP;
    static char* IMAGE_CELL;
    static char* IMAGE_BORDER_SIDE;
    static char* IMAGE_BORDER_CORNER;
    static char* IMAGE_SELECT_LEVEL_BACK;
    static char* IMAGE_BUTTON_MORE_GAMES;    
};


int Constants::W = 320;//定义并初始化静态数据成员
int Constants::H = 480;
bool Constants::g_DEBUG = false;
char* Constants::LOAD_COMPLETE = "LOAD_COMPLETE";
char* Constants::MOUSE_DOWN = "stagemousedown";
char* Constants::MOUSE_UP = "stagemouseup";
char* Constants::MOUSE_MOVE = "stagemousemove";
int Constants::CELL_SIZE = 85;
int Constants::FIELD_OFFSET_X = 9;
int Constants::FIELD_OFFSET_Y = 250;
float Constants::EXCHANGE_TIME = .22f;
float Constants::MATCH_TIME = .25f;
int Constants::GRAVITY_ACC = 2500;
int Constants::ASSETS_WIDTH = 700;
int Constants::ASSETS_HEIGHT = 900;
int Constants::PIXEL_RATIO = 1;
int Constants::SCREEN_HEIGHT = 900;
int Constants::SCREEN_SCALE = 1;
int Constants::DPI = -1;
bool Constants::DEBUG_MODE = false;
char* Constants::COLOR_PINK = "#ffE5E5";
char* Constants::COLOR_BLUE = "#619CC4";
char* Constants::IMAGE_BUTTON_CLOSE = "button_close";
char* Constants::IMAGE_BUTTON_SOUND_ON = "button_sound_on";
char* Constants::IMAGE_BUTTON_SOUND_OFF = "button_sound_off";
char* Constants::IMAGE_BUTTON_EXIT = "button_exit";
char* Constants::IMAGE_BUTTON_PAUSE = "button_pause";
char* Constants::IMAGE_BUTTON_RESTART = "button_restart";
char* Constants::IMAGE_BUTTON_PLAY = "button_play";
char* Constants::IMAGE_AWESOME = "awesome";
char* Constants::IMAGE_SUPERB = "superb";
char* Constants::IMAGE_SHINING = "shining";
char* Constants::IMAGE_DROP = "drop";
char* Constants::IMAGE_BACK = "back";
char* Constants::IMAGE_DONUT = "donut";
char* Constants::IMAGE_ARROW_BONUS_VERT = "arrow_bonus_vert";
char* Constants::IMAGE_ARROW_BONUS_HOR = "arrow_bonus_hor";
char* Constants::IMAGE_BOMB = "bomb_bonus";
char* Constants::IMAGE_MESSAGE_WINDOW = "message_window";
char* Constants::IMAGE_HINT_ARROW = "hint_arrow";
char* Constants::IMAGE_GAMEOVER_CAPTION = "gameover_caption";
char* Constants::IMAGE_TITLE_MAIN_MENU_BACK = "main_menu_back";
char* Constants::IMAGE_SICKLE = "sickle";
char* Constants::IMAGE_ROTATE = "rotate";
char* Constants::IMAGE_BIG_SHINING = "big_shining";
char* Constants::IMAGE_POINTS_CONTROL_BIG = "point_control_big";
char* Constants::IMAGE_POINTS_CONTROL_SMALL = "point_control_small";
char* Constants::IMAGE_LEVEL_BUTTON = "level_button";
char* Constants::IMAGE_DIRT = "dirt";
char* Constants::IMAGE_GUI = "gui";
char* Constants::IMAGE_LOCK = "lock";
char* Constants::IMAGE_OUT_OF_MOVES = "out_of_moves";
char* Constants::IMAGE_WIN_CAPTION = "win_caption";
char* Constants::IMAGE_STONE_HEART = "stone_heart";
char* Constants::IMAGE_TASK_PANEL = "task_panel";
char* Constants::IMAGE_HEART_PARTICLE = "heart_particle";
char* Constants::IMAGE_WIN_STRINGS = "win_strings";
char* Constants::IMAGE_GLOBAL_MAP = "global_map";
char* Constants::IMAGE_CELL = "cell";
char* Constants::IMAGE_BORDER_SIDE = "border_side";
char* Constants::IMAGE_BORDER_CORNER = "border_corner";
char* Constants::IMAGE_SELECT_LEVEL_BACK = "select_level_back";
char* Constants::IMAGE_BUTTON_MORE_GAMES = "button_more_games";

#endif // __Match3_Constants_H__
