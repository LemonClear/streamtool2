#include <stdio.h>
#include "testConfig.h"
#include "table.h"

double mysqrt(double in)
{
        double result = in;

// if we have both log and exp then use them
#if defined (HAVE_LOG) && defined (HAVE_EXP)
        result = exp(log(in)*0.5);
#endif

        return result;
}
