#include <superkarel.h>

void jump_over();
void turn_right();
void jump_over_back();

int main() {
    turn_on("task_1.kw");
    set_step_delay(100);

    put_beeper();
    if(front_is_blocked())
    {
        jump_over();
    }  

    do 
    {
        while(front_is_clear())
        {
            step();
        }
        if(no_beepers_present())
        {
            jump_over();
        }
        
    }while(no_beepers_present());

    pick_beeper();

    turn_left();
    turn_left();

    while(no_beepers_present())
    {
        while (front_is_clear())
        {
            if(no_beepers_present()){
                step();
            }else{
                break;
            }
        }
        jump_over_back();  
    };
    pick_beeper();
    turn_off();

}

void jump_over_back()
{   
    if(no_beepers_present()){
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

