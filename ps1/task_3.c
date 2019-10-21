#include <superkarel.h>

void jump_over();
void check_line();
void turn_around();
void turn_right();
void go_down();
void check_first_line();
bool beepers_upside();
void check_helper();
void go_home();

int main() {
    turn_on("task_3.kw");
    set_step_delay(100);
    check_first_line();
    while(1){
        check_line();
    }
    go_home();
}

void go_home()
{
    turn_around();
    while (front_is_clear())
    {
        step();
    }
    turn_left();
    while (front_is_clear())
    {
        step();
    }
    turn_left();
    while (front_is_clear())
    {
        step();
    }
    turn_around();
    turn_off();
}

void check_helper()
{
    while (no_beepers_present()&&front_is_clear())
    {
        step();
        if(beepers_present())
        {
            pick_beeper();
        }
    }
    turn_around();
}

bool beepers_upside()
{
    set_step_delay(0);
    if(right_is_clear())
    {
        turn_right();
        step();
        if(beepers_present())
        {
            turn_around();
            step();
            turn_right();
            set_step_delay(100);
            return true;
        }else{
            turn_around();
            step();
            turn_right();
            set_step_delay(100);
            return false;
        }
    }else{
        set_step_delay(100);
        return false;
    }
    
}

void check_line()
{
    check_helper();
    
    while(front_is_clear()){
        while(beepers_in_bag()){
            if(beepers_upside()&&beepers_in_bag())
            {
                put_beeper();
            }
            step();
        }
        step();
    }
    
    if(left_is_clear())
    {
        go_down();
    }else{
        go_home();
    }
}

void check_first_line()
{
    check_helper();

    while(front_is_clear()){
        if(right_is_blocked()&&beepers_in_bag())
        {
            put_beeper();
        }
        step();
    }

    if(left_is_clear())
    {
        go_down();
    }
}


void go_down()
{
    turn_left();
    step();
    turn_left();
}

void turn_around()
{
    turn_left();
    turn_left();
}

void turn_right()
{
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(100);
}   
