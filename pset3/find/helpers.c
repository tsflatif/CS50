/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n<0)
        return false;
        
    int start = 0;
    int end = n-1;
    
    int middle = (start + end)/2;
    
    while(start <= end){
        if(values[middle] < value)
            start = middle + 1;
        else if (values[middle] > value)
            end = middle - 1;
        else if (values[middle] == value)
            return true; 
        
        middle = (start + end)/2;          
    }
     
    return false;  
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool swapped = true;
    int j = 0;
    int temp;
    while(swapped){
        swapped = false;
        j++;
        for(int i = 0; i < n-j; i++){
            if(values[i] > values[i+1]){
                temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
                swapped = true;
            }    
        }
    }
    return;
}
