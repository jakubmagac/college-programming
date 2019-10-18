#include <superkarel.h>

void jump_over();
void inside();
void out();
void turn_around();
void turn_right();

int main() {
    turn_on("task_2.kw");
    set_step_delay(100);

    inside();
    out();
    
    turn_off();

}

void turn_around()
{
    turn_left();
    turn_left();
}

void out()
{
    turn_around();
    while(!(right_is_blocked()&&left_is_blocked()&&front_is_blocked()))
    {
        if(right_is_blocked()&&front_is_clear())
        {
            step();
        }else{
            turn_right();
            step();
        }
    }
}


void inside()
{
    while (no_beepers_present())
    {
        if(right_is_blocked()&&front_is_clear())
        {
            step();
        }else{
            turn_left();
            step();
        }
    }
    pick_beeper();
}

void turn_right()
{
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(100);
}   