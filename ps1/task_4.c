#include <superkarel.h>

void turn_right();
bool check_column();
void come_back();
void repair();

int main() {
    turn_on("task_4.kw");
    set_step_delay(100);
    
    while(front_is_clear())
    {
        if (check_column())
        {
            come_back();
            repair();
            come_back();
            step();
        }else{
            come_back();
            step();
        }
    }

    if (check_column())
    {
        come_back();
        repair();
        come_back();
    }else{
        come_back();
    }
    
    
    turn_off();

}

void repair()
{
    turn_left();
    while(front_is_clear())
    {
        if(no_beepers_present()){
            put_beeper();
        }
        step();
    }
    if(no_beepers_present()){
            put_beeper();
    }
}

void come_back()
{
    set_step_delay(0);
    turn_left();
    turn_left();
    while (front_is_clear())
    {
        step();
    }
    turn_left();
    set_step_delay(100);
}

bool check_column()
{
    set_step_delay(0);
    turn_left();
    while(front_is_clear())
    {
        if(beepers_present())
        {
            return true;
        }else
        {
            step();
        }
        
    }
    return false;
}

void turn_right()
{
    turn_left();
    turn_left();
    turn_left();
}   
