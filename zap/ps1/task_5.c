#include <superkarel.h>

void turn_right();
void find_start();
void make_frame();
void find_center();
void center_helper();
void turn_around();
void center_helper_horizontal();
void find_center_horizontal();
bool check_sides();

int main() {
    turn_on("task_5.kw");
    set_step_delay(100);
    find_start();
    make_frame();
    center_helper();
    find_center();
    turn_right();
    center_helper_horizontal();
    find_center_horizontal();
    turn_left();
    turn_off();
    return 0;
}

void center_helper_horizontal()
{
    put_beeper();
    while (front_is_clear())
    {
        put_beeper();
        step();
    }
    put_beeper();
    turn_around();
    while (front_is_clear())
    {
        step();
    }
    turn_around();
}

void find_center_horizontal()
{
    if(beepers_present())
    {
        if(beepers_present()&&front_is_clear()){
            pick_beeper();
        }  
        while(not_facing_east()&&not_facing_west())
        {
            turn_left();
        }    
        step();

        while(beepers_present()&&front_is_clear())
        {
            step();
        }
        if(beepers_present()&&!front_is_clear()){
            pick_beeper();
        }  
        turn_around();
        step();
        
        find_center_horizontal();
    }else{
        return;
    }    

}

void center_helper()
{
    turn_left();
    while (front_is_clear())
    {
        pick_beeper();
        step();
    }
    pick_beeper();
    turn_left();
    turn_left();
    while (front_is_clear())
    {
        step();
    }
    turn_left();
}

void find_center()
{
    if(no_beepers_present())
    {
        put_beeper();  
        while(not_facing_north()&&not_facing_south())
        {
            turn_left();
        }    
        step();
        while(no_beepers_present() && front_is_clear())
        {
            step();
        }
        turn_around(); 
        if(no_beepers_present()){
            put_beeper();
        }
        step(); 
        find_center();    
    }else{
        return;
    }
}

void turn_right()
{
    turn_left();
    turn_left();
    turn_left();
}
    
void turn_around()
{
    turn_left();
    turn_left();
}

void find_start()
{
    while(not_facing_south())
    {
        turn_left();
    }
    while(front_is_clear())
    {
        step();
    }
    turn_right();

    while(front_is_clear())
    {
        step();
    }
    turn_around();
}

void make_frame()
{
    while (front_is_clear() && no_beepers_present())
    {
        put_beeper();
        step();
        if(front_is_blocked())
        {
            turn_left();
        }
    }
    
}
