#include <stdio.h>

/*
*   float -> float
*   round to 2 decimal places*/
float round_decimal(float result)
{
    float helper = result * 1000;
    int reminder = (int)helper % 10;
    if(reminder >= 5)
    {
        helper /= 10;
        helper += 1;
    }
    else{
        helper /= 10;
    }
    result = (int)helper / 100.0;
    return result;
}


/*
*   int, int, int -> float on 2 decimal places
*   return distance where you have to put flucrum for lever */
float lift_a_car(const int stick_length, const int human_weight, const int car_weight)
{
    float result = (float)(stick_length * human_weight) / (float)(human_weight + car_weight);
    return round_decimal(result);
}

/*
*   
*/
float unit_price(const float pack_price, const int rolls_count, const int pieces_count) 
{
    float result = ((pack_price / rolls_count) / pieces_count) * 100;
    return round_decimal(result);    
}

int main()
{  
    printf("%.4f\n", unit_price(4.79, 16, 150));
    // prints: 0.2000
    printf("%.4f\n", unit_price(5.63, 20, 200));
    // prints: 0.1400
    
    return 0;
}