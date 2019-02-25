/*
#
# Copyright LemonClear
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
// A simple program that builds a sqrt table 
int main(int argc, char *argv[])
{
        int i;
        double result;

        // make sure we have enough arguments
        if (argc < 2)
        {
                return 1;
        }

        // open the output file
        FILE *fout = fopen(argv[1],"w");
        if (!fout)
        {
                return 1;
        }

        // create a source file with a table of square roots
        fprintf(fout,"/*this file is auto generated and do not modify!*/\n");
        fprintf(fout,"double sqrtTable[] = {\n");
        for (i = 0; i < 10; ++i)
        {
                result = (double)i;
                fprintf(fout,"%g,\n",result);
        }

        // close the table with a zero
        fprintf(fout,"0};\n");
        fclose(fout);
        return 0;
}
