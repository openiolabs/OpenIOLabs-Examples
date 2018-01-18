#include <assert.h>
#include <stdio.h>
#include <scriptml/bluetooth.h>

//
// Bind a bluetooth serial port. Must be paired first.
//

#define MAC_ADDRESS 34:C9:F0:80:07:51

#define XSTR(S) STR(S)
#define STR(S) #S

int main()
{
    char msg[256];
    char dev[256];
    int res = sml_bluetooth_serial_bind( XSTR(MAC_ADDRESS), dev, msg );
    if( res != 0 )
    {
        printf("%s\n", msg);
        assert(0);
    }
    printf("Bound %s\n", dev);
    return 0;
}
