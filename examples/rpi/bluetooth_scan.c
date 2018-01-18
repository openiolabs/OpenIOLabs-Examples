#include <assert.h>
#include <stdio.h>
#include <scriptml/bluetooth.h>

//
// Scan for bluetooth devices. This must be done before pairing.
//

// How long to scan for - increase if device not always found
#define SCAN_TIMEOUT 20

int main()
{
    char *res = sml_bluetooth_scan( SCAN_TIMEOUT );
    printf( "Found:\n%s\n", res );
    return 0;
}