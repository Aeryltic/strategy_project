#include "GameInstance.h"

#include <cstdlib>
#include <ctime>

#include "MiscFunctions.h"

using namespace std;

GameInstance::GameInstance()
{
    world_ = 0;
    player_nation_ = 0;
    running_ = true;
    needs_printing_ = true;
    tick_ = 0;
    active_grid_ = 0;
    mode_ = MODE_NO_ACTION;
    round_end_=false;
}

GameInstance::~GameInstance()
{
    if (world_) delete world_;
}

void GameInstance::run()
{

    //_INITS

    initscr();
    start_color();

 //   halfdelay(2);
    noecho();

    keypad(stdscr,TRUE);
    mouse_on(ALL_MOUSE_EVENTS);

    resize_term(SCREEN_HEIGHT,SCREEN_WIDTH);

    srand(time(NULL));

    traceon();

    PDC_debug("new launch------------------------------------------------\n");

    //_COLOR_GREY_INIT

    init_color(COLOR_GREY, 250, 250, 250);

    //_COLOR_PAIRS

 //   init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(WHITE_GREY, COLOR_WHITE, COLOR_GREY);

    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(RED_GREY, COLOR_RED, COLOR_GREY);

    init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(GREEN_GREY, COLOR_GREEN, COLOR_GREY);

    init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(BLUE_GREY, COLOR_BLUE, COLOR_GREY);

    //_GAME

    newGame();

    print();
    while (running_)
    {
        update();
        if (needs_printing_)
        {
            print();
            needs_printing_ = false;
        }
    }
    endwin();
}

void GameInstance::update()
{
    mvprintw(0,0,"%d tick",tick_++);
 //   mvprintw(21,0,"%u",getmouse());
    if(!round_end_)
    {
        pressed_key_ = getch();
        if(pressed_key_ == ' ') round_end_ = true;
    //--MODE_SWITCH---------------------------------------------------------
        if(active_grid_ && active_grid_->getVisitor() &&
           (Nation*)((Group*)(active_grid_->getVisitor()))->getNation() == player_nation_)
        {
            if(pressed_key_ == 'M' || pressed_key_ == 'm')
            {
                mode_ = MODE_MOVE;
            }
            if(pressed_key_ == 'G' || pressed_key_ == 'g')
            {
                mode_ = MODE_GATHER_RESOURCES;
            }
            if(pressed_key_ == 'B' || pressed_key_ == 'b')
            {
                mode_ = MODE_BUILD_SETTLEMENT;
            }
        }
        else resetMode();
    //--MODE_HANDLE------------------------------------------------------------
        if(mode_ == MODE_GATHER_RESOURCES)
        {
            if(approveAction("Spend round on gathering?"))
            {
                ((Group*)(active_grid_->getVisitor()))->gatherResources();
                resetMode();
            }
        }
        else if(mode_ == MODE_BUILD_SETTLEMENT)
        {
            if(approveAction("Build settlement?"))
            {
                ((Group*)(active_grid_->getVisitor()))->buildSettlement();
                resetMode();
                needs_printing_ = true;
            }
        }
        if(pressed_key_ == KEY_MOUSE)
        {
            request_mouse_pos();
            int x=Mouse_status.x,
                y=Mouse_status.y;
            if(isAtMap(x,y))
            {
                convertToMapCoor(x,y);
                Grid * grid = world_->getGrid(x,y);
                if(active_grid_ && active_grid_->getVisitor() &&
                   ((Nation*)((Group*)(active_grid_->getVisitor()))->getNation()) == player_nation_ &&
                   mode_ == MODE_MOVE)
                {
                    ((Group*)(active_grid_->getVisitor()))->moveToGrid(grid);
                    resetMode();
                }
                if(active_grid_)active_grid_->setInactive();
                active_grid_ = grid;
                if(active_grid_)active_grid_->setActive();
            }

            needs_printing_ = true;
        }

        if (endingSignalSent()) running_ = false;
     }
     else
     {
         //--CPU's_TURN------------------------------------------------------------
         /*
         *
         *
         */
         for(unsigned i=0; i<nation_.size(); i++)
         {
             if(!(nation_[i] == player_nation_))
             {

             }
             //--PRINT-STATE
         }
         round_end_ = false;
     }
}

void GameInstance::print()
{
    clear();
    //-----MAP-------------------------------------------------------------------
    printMap();
   // getch();

    //-----UI--------------------------------------------------------------------
    printUI();

    refresh();
}

void GameInstance::newGame()
{
    createWorld(20,20);

    addPlayerNation();
    player_nation_->getGroup(0)->resources()->set(1000,1000,1000,1000,1000);
    addCPUNation();
    addCPUNation();

}

bool GameInstance::createWorld(int height,int width)
{
    if (world_) return false;

    world_ = new World(height,width);
    world_->build();
    return true;
}

bool GameInstance::addPlayerNation()
{
    if (player_nation_) return false;

    player_nation_ = new Nation( PLAYER_CONTROLLER, "player_nation", nextNationColor() );
    int x = rand() % world_->getWidth();
    int y = rand() % world_->getHeight();
    while ( (world_->getGrid(x,y)->getType() != LAND) || (world_->getGrid(x,y)->isOwned()) )
    {
        x = rand() % world_->getWidth();
        y = rand() % world_->getHeight();
    }
    player_nation_->getMainGroup()->moveToGrid(world_->getGrid(x,y));

    nation_.push_back(player_nation_);
    return true;
}

bool GameInstance::addCPUNation()
{
    if ( nation_.size() >= MAX_NATIONS ) return false;

    string name = string("cpu_nation_#") + to_string(nation_.size());

    Nation * nation = new Nation( CPU_CONTROLLER, name, nextNationColor() );

    int x = rand() % world_->getWidth();
    int y = rand() % world_->getHeight();
    while ( (world_->getGrid(x,y)->getType() != LAND) || (world_->getGrid(x,y)->isOwned()) )
    {
        x = rand() % world_->getWidth();
        y = rand() % world_->getHeight();
    }
    nation->getMainGroup()->moveToGrid(world_->getGrid(x,y));

    nation_.push_back(nation);
    return true;
}

void GameInstance::updatePointer()
{
    pointer_.x = 0;//mouse
    pointer_.y = 0;
}

bool GameInstance::endingSignalSent()
{
    if (pressed_key_ == 27) return true;
    return false;
}

string GameInstance::info()
{
    string str;
    str += world_->info();
    return str;
}

int GameInstance::nextNationColor(){return (nation_.size()+1)*2+WHITE_BLACK;}

void GameInstance::printMap()
{
    for(unsigned i=0; i < world_->getHeight(); i++)
    {
        for(unsigned j=0; j < world_->getWidth(); j++)
        {
            Grid * grid = world_->getGrid(j,i);

            int x = grid->posX(); //j
            int y = grid->posY(); //i
            convertToAbsoluteCoor(x,y);

            char * t="  ",
                 * d="  ";
            if (grid->getSettlement())
            {
                t = (char*)"HH";
                d = (char*)"HH";
            }
            else if (grid->hasVisitor())
            {
                t = (char*)"U#";
                d = (char*)"I#";
            }
            else if (grid->getType() == LAND)
            {
                t = (char*)"##";
                d = (char*)"##";
            }

            int color= grid->isActive() ? grid->activeColor() : grid->inactiveColor();
            attron(COLOR_PAIR(color));

            mvprintw(y,x,t);
            mvprintw(y+1,x,d);

            attroff(COLOR_PAIR(color));
        }
    }
}

void GameInstance::printUI()
{
    int width = (world_->getWidth()*2)+2,
        height = (world_->getHeight()*2+1)+2;
    for (unsigned i=0; i<height; i++)
    {
        for (unsigned j=0; j<width; j++)
        {
            if(i==0 || i==height-1)
            {
                mvprintw(MAPY-1+i,MAPX-1+j,"-");
            }
            if(j==0 || j==width-1)
            {
                mvprintw(MAPY-1+i,MAPX-1+j,"|");
            }
            if((i==0 || i==height-1) && (j==0 || j==width-1))
            {
                if(i==0)
                {
                    if(j==0) mvprintw(MAPY-1+i,MAPX-1+j,"/");
                    else mvprintw(MAPY-1+i,MAPX-1+j,"\\");
                }
                else
                {
                    if(j==width-1) mvprintw(MAPY-1+i,MAPX-1+j,"/");
                    else mvprintw(MAPY-1+i,MAPX-1+j,"\\");
                }
            }
        }
    }
    if (active_grid_)
    {
        int x = 3,
            y = MAPY + height + 5;
        fprintw(y,x,active_grid_->info());

        x+=15;
        if(active_grid_->getVisitor())
        {
            //-GROUP_INFO-----------------------------------------------------
            Group * group = (Group*)active_grid_->getVisitor();
            Nation * nation = ((Nation*)(group->getNation()));
            fprintw(y,x,"NATION: "+nation->getName()+"\n"+group->info());
            if(nation == player_nation_)
            {
                int temp = y+10;
                //-CONTROL BUTTONS---------------------------------------------------
                if(mode_ == MODE_MOVE) attron(COLOR_PAIR(WHITE_GREY));
                    mvprintw(temp++,x,"M) move");
                if(mode_ == MODE_MOVE)attroff(COLOR_PAIR(WHITE_GREY));

                if(mode_ == MODE_GATHER_RESOURCES) attron(COLOR_PAIR(WHITE_GREY));
                mvprintw(temp++,x,"G) gather resources");
                if(mode_ == MODE_GATHER_RESOURCES)attroff(COLOR_PAIR(WHITE_GREY));

                if(active_grid_->getSettlement() == 0)
                {
                    if(mode_ == MODE_BUILD_SETTLEMENT) attron(COLOR_PAIR(WHITE_GREY));
                    mvprintw(temp++,x,"B) build settlement");
                    if(mode_ == MODE_BUILD_SETTLEMENT) attroff(COLOR_PAIR(WHITE_GREY));
                }

            }
        }
        x+=15;
        if(active_grid_->getSettlement())
        {
            Settlement * settlement = active_grid_->getSettlement();
            fprintw(y,x,settlement->info());
        }
    }
}

 bool GameInstance::approveAction(char * str)
 {
     unsigned str_len=0;
     while(str[str_len])str_len++;

     mvprintw(SCREEN_HEIGHT/2,SCREEN_WIDTH/2,"%s",str);
     mvprintw(SCREEN_HEIGHT/2+1,SCREEN_WIDTH/2,"y) yes, n) no");
     int c = getch();
     while( c!='y' && c!='n' && c!='Y' && c!='N' )c = getch();
     return (c=='y' || c=='Y');
 }













void GameInstance::fprintw(int y,int x,string str)
{
    if(str.size())
    {
        int line = 0;
        size_t i = 0;
        do
        {
            size_t j = str.find('\n',i);
            if (j == string::npos) j = str.size();
            mvprintw(y+line++, x, str.substr(i,j-i).c_str());
            i=j+1;
        }while (i<str.size()-1);
    }
}
//void
