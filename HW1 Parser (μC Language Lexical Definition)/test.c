// c program to demonstrate
// example of strupr() function.
#include<stdio.h>
#include<string.h>
  
int main()
{
    char str[ ] = "geeksforgeeks is the best";
    //converting the given string into uppercase.
    printf("%s\n", strupr (str));
    return  0;
}