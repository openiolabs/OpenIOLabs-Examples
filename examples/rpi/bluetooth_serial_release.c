#include <scriptml/bluetooth.h>

//
// Remove (un-bind) a bluetooth serial port.
//

#define MAC_ADDRESS 34:C9:F0:80:07:51

#define XSTR(S) STR(S)
#define STR(S) #S

int main()
{
    sml_bluetooth_serial_release(XSTR(MAC_ADDRESS));
    return 0;
}
