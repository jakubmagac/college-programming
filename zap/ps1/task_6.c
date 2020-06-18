#include <superkarel.h>

void turn_right();
void turn();

int main() {
    turn_on("task_6.kw");
    set_step_delay(100);
    while (no_beepers_present())
    {
        step();
        if(beepers_present())
        {
            while(not_facing_north())
            {
                turn_left();
            }
            pick_beeper();
            turn_left();
            while(beepers_present()&&not_facing_north())
            {
                pick_beeper();
                turn_left();
            }
            turn_right();
        }
        if(beepers_present())
        {
            pick_beeper();
            break;
        }
    }
        
    turn_off();
    return 0;
}

void turn_right()
{
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(100);
}

