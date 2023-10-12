#include "helper_function.h"

double map(double in,double min1,double max1,double min2,double max2)
{
        double output;

  output= (((in-min1 )/( max1-min1)) *(max2-min2 ))+min2 ;

  return output;
    
}
