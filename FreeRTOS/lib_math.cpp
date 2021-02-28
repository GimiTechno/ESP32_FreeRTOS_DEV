#include "lib_math.h"
#include "lib_mcu.h"

volatile const double g_a = 355.;
volatile const double g_b = 226.;

void lib_math_accuracy( void )
{
    double tmp_sin, tmp_cos, tmp_tan;

    tmp_sin = sin(g_a / g_b);
    tmp_cos = 1. * (1. / cos(g_a / g_b));
    tmp_tan = tan(g_a / g_b);

    printf("sin(355/226)    = %.10f \n",tmp_sin);
    printf("cos(355/226)^-1 = %.10f \n",tmp_cos);
    printf("tan(355/226)    = %.10f \n",tmp_tan);
}