#include <assert.h>
#include <stdio.h>
#include <scriptml/bluetooth.h>

//
// Report which devices have been paired in the past
//

int main()
{
    char *res = sml_bluetooth_get_paired();
    printf( "Paired:\n%s\n", res );
    return 0;
}