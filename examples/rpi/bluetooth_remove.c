#include <scriptml/bluetooth.h>

//
// Remove (un-scan and un-pair) a bluetooth device.
//

#define MAC_ADDRESS 34:C9:F0:80:07:51

#define XSTR(S) STR(S)
#define STR(S) #S

int main()
{
    sml_bluetooth_remove(XSTR(MAC_ADDRESS));
    return 0;
}
