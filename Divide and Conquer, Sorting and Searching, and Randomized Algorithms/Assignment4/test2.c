/* log10 example */
#include <stdio.h>      /* printf */
#include <math.h>       /* log10 */

int main ()
{
  int row = 1;
  int result;
  for(row = 1; row < 110; row += 9){
  	result = log10 (row);
  	printf ("log10(%d) = %d\n", row, result);
  }
  return 0;
}