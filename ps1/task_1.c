#include <superkarel.h>

void jump_over();
void turn_right();
void jump_over_back();

int main() {
    turn_on("task_1.kw");
    set_step_delay(100);

    put_beeper();

    do 
    {
        while (front_is_clear())
        {
            step();
        }
        jump_over();
        
    }while(no_beepers_present());

    pick_beeper();

    turn_left();
    turn_left();

    do 
    {
        while (front_is_clear())
        {
            step();
        }
        jump_over_back();
        
    }while(no_beepers_present());
    
    turn_off();

}

void jump_over_back()
{
    turn_right();
    while(left_is_blocked())
    {
        step();
    }
    
    turn_left();
    do {
        step();

    }while(left_is_blocked());
    turn_left();
    while(front_is_clear())
    {
        step();
    }
    turn_right();
}


void jump_over()
{
    turn_left();
    while(right_is_blocked())
    {
        step();
    }
    
    turn_right();
    do {
        step();

    }while(right_is_blocked());
    turn_right();
    while(front_is_clear())
    {
        step();
    }
    turn_left();
}

void turn_right()
{
    turn_left();
    turn_left();
    turn_left();
}   