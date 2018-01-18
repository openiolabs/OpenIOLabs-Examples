#include <assert.h>
#include <stdio.h>
#include <scriptml/bluetooth.h>

//
// Pair a bluetooth device. Scan must be performed first.
//

#define MAC_ADDRESS 34:C9:F0:80:07:51
#define PIN_CODE 1234

#define XSTR(S) STR(S)
#define STR(S) #S

int main()
{
    char msg[256];
    int res = sml_bluetooth_pair(XSTR(MAC_ADDRESS), XSTR(PIN_CODE), msg);
    if( res==-1 )
    {
        printf("%s\n", msg);
        assert(0);
    }
    printf("Paired ok\n");
    return 0;
}
