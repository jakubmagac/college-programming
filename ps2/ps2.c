#include <stdio.h>

float round_decimal(float result);
float lift_a_car(const int stick_length, const int human_weight, const int car_weight);
float unit_price(const float pack_price, const int rolls_count, const int pieces_count);
int collatz(const int number); 
int opposite_number(const int n, const int number);
void counter(const int input_array[], const int array_size, int result_array[2]);
/*PASCALOV TROJUHOLNIK**/
int array_min(const int input_array[], const int array_size);
int array_max(const int input_array[], const int array_size);
unsigned long special_counter(const int input_array[], const int array_size);

int main()
{  
    //CODE
    int input_array[] = {11,12,13,14,15};
    printf("%lu\n", special_counter(input_array, 5));
    // prints: 379
    return 0;
}

/**
 * float -> float
 * round to 2 decimal places
*/  
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

/**
 * int, int, int -> float on 2 decimal places
 * return distance where you have to put flucrum for lever 
*/
float lift_a_car(const int stick_length, const int human_weight, const int car_weight)
{
    float result = (float)(stick_length * human_weight) / (float)(human_weight + car_weight);
    return round_decimal(result);
}

/**
 * float, inn, int -> float
 * return unit price of toilete paper
*/
float unit_price(const float pack_price, const int rolls_count, const int pieces_count) 
{
    float result = ((pack_price / rolls_count) / pieces_count) * 100;
    return round_decimal(result);    
}

/**
 * int -> int
 * Collatz problem
 * return the number of numbers in collatz problem
*/
int collatz(const int number)
{
    int count = 1;
    int helper = number;
    while(helper != 1)
    {
        if(helper % 2 == 0)
        {
            helper /= 2;
        }else{
            helper = (helper * 3) + 1;
        }
        count++;
    }
    return count;
}

/**
 * int, int -> int
 * return opposte number in the circle
*/
int opposite_number(const int n, const int number)
{
    int shift = n / 2;
    if(number == shift)
    {
        return shift;
    }
    if(number < shift)
    {
        return number  + shift;
    }
    if(number > shift)
    {
        return number - shift;
    }
}

/**
 * int array, int, int array -> int array
 * sum the odd and even number in result array
*/
void counter(const int input_array[], const int array_size, int result_array[2])
{
    for(int i=0;i<array_size;i++)
    {
        if(i%2 == 0)
        {
            result_array[0] += input_array[i];
        }else{
            result_array[1] += input_array[i];
        }
    }
}

/**
 * int array, int, -> int
 * return smallest value in the array
*/
int array_min(const int input_array[], const int array_size)
{
    if(input_array == NULL) return -1;
    int min = input_array[0];
    for(int i=0;i<array_size;i++)
    {
        if(input_array[i]<min)
        {
            min = input_array[i];
        }
    }
    return min;
}

/**
 * int array, int, -> int
 * return largest value in the array
*/
int array_max(const int input_array[], const int array_size)
{
    if(input_array == NULL) return -1;
    int max = input_array[0];
    for(int i=0;i<array_size;i++)
    {
        if(input_array[i]>max)
        {
            max = input_array[i];
        }
    }
    return max;
}

/**
 * int array, int, -> int
 * return sum of all numbers in array, even number are squared and then summed
*/
unsigned long special_counter(const int input_array[], const int array_size)
{
    int sum = 0;
    for(int i=0;i<array_size;i++)
    {
        if(i%2 == 0)
        {
            sum += input_array[i];
        }else{
            sum += input_array[i] * input_array[i];
        }
    }
    return sum;
}