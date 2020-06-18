#include <superkarel.h>

void turn_around();
void turn_right();
void mark_line();
void check_room();
void come_home();

int main() {
    turn_on("task_7.kw");
    set_step_delay(100);
    mark_line();
    come_home();

    while(front_is_clear())
    {
        if(left_is_clear())
        {
            check_room();
        }
        if(front_is_clear())
        {
            step();
        }
    }
    turn_around();
    while(front_is_clear())
    {
        if(beepers_present())
        {
            pick_beeper();
        }
        step();
    }
    if(beepers_present())
    {
        pick_beeper();
    }
    come_home();
    turn_around();
    turn_off();
}

void come_home()
{
    turn_around();
    while(front_is_clear())
    {
        step();
    }
    turn_around();
}

void check_room()
{
    pick_beeper();
    turn_left();
    step();
    put_beeper();
    do{
        if(right_is_blocked())
        {
            while(front_is_blocked())
            {
                turn_left();
            }
            step();
        }else{
            turn_right();
            step();
        }
    }while(no_beepers_present());

    if(front_is_clear())
    {
        pick_beeper();
        step();
        turn_left();
    }else{
        pick_beeper();
        turn_around();
        step();
        put_beeper();
        turn_around();
        step();
        turn_left();
    }

}

void mark_line()
{
    while(front_is_clear())
    {
        put_beeper();
        step();
    }
    put_beeper();
    
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
