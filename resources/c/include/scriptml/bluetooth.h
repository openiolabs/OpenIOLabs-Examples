/** @file
 * 
 *  @brief ScriptML bluetooth support
 *
 * API functions for scanning and pairing bluetooth devices.
 * 
 * API functions for binding bluetooth serial ports
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

#include <assert.h>
#include <string.h>
#include <stdio.h>

/**
 *  @brief Determine which bluetooth devices are paired
 *
 * This is the list of configured paired devices regardless of whether they are detectable or not.
 * Output format is
 * 
 * <mac address>[/<channel>],<mac address>[/<channel>]...
 * 
 * Where a device has been bound as a serial port, the channel number is given after a forward slash.
 * 
 *  @return A string continaing the devices
 */
char *sml_bluetooth_get_paired()
{
    ___Send(request:"Bluetooth_GetPaired", client_handle:-1, str_payload:"", int_payload:___ISeq(), float_payload:___ISeq()); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	assert( l[0]=="Value" ); 
    return l[1];
}


/**
 *  @brief Scan for bluetooth devices
 *
 * Checks for devices that can be detected by the bluetooth hardware
 * Output format is
 * 
 * <mac address>/<description>,<mac address>/<description>...
 * 
 * A 20s timeout is usually sufficient.
 * 
 *  @param timeout The amount of time to spend scanning, in seconds. 
 *  @return A string continaing the devices
 */
char *sml_bluetooth_scan( int timeout )
{
    ___Send(request:"Bluetooth_Scan", client_handle:-1, str_payload:"", int_payload:___ISeq(timeout), float_payload:___ISeq()); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	assert( l[0]=="Value" ); 
    return l[1];
}


/**
 *  @brief Pair a bluetooth device
 *
 * Pair the device. This is a configuration change that persists across power cycles.
 * Note that the device must have been found by a scan operation since the last power cycle or remove operation.
 * 
 * Mac address is of the form xx:xx:xx:xx:xx:xx
 * 
 *  @param mac_address MAC address of the bluetooth device to pair
 *  @param pin_code PIN code of the device or "" id none required
 *  @param error_message Optional buffer to receive the text of any error messages
 *  @return 0 if successful
 */
int sml_bluetooth_pair( char *mac_address, char *pin_code, char *error_message )
{
    char buf[200];
    sprintf(buf, "%s/%s", mac_address, pin_code);
    ___Send(request:"Bluetooth_Pair", client_handle:-1, str_payload:buf, int_payload:___ISeq(), float_payload:___ISeq()); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	if( l[0]=="Fail" )
    {
        if( error_message )
            strcpy( error_message, l[2] ); // failure
        return -1;
    }
    return 0;
}


/**
 *  @brief Remove a bluetooth device
 *
 * Undoes the action of scan and pair (i.e. unpair and forget).
 * 
 * Mac address is of the form xx:xx:xx:xx:xx:xx
 * 
 *  @param mac_address MAC address of the bluetooth device to remove
 */
void sml_bluetooth_remove(char *mac_address)
{
    ___Send(request:"Bluetooth_Remove", client_handle:-1, str_payload:mac_address, int_payload:___ISeq(), float_payload:___ISeq()); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	assert( l[0]=="OK" ); 
}


/**
 *  @brief Bind a bluetooth serial port
 *
 * Bind the bluetooth serial port to a node in /dev so that it can be used for serial communications. This does not persist across power cycles.
 * Note that the device must have been successfully paired and be detectable.
 * 
 * Mac address is of the form xx:xx:xx:xx:xx:xx
 * 
 * Device path is of the form /dev/<device>
 * 
 *  @param mac_address MAC address of the bluetooth serial port to bind
 *  @param device Optional buffer to receive the device path
 *  @param error_message Optional buffer to receive the text of any error messages
 *  @return 0 if successful
 */
int sml_bluetooth_serial_bind( char *mac_address, char *device, char *error_message )
{
    ___Send(request:"Bluetooth_Bind", client_handle:-1, str_payload:mac_address, int_payload:___ISeq(), float_payload:___ISeq()); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	if( l[0]=="Fail" )
    {
        if( error_message )
            strcpy( error_message, l[2] ); 
        return -1;
    }
    if( device )
        sprintf( device, "/dev/rfcomm%d", l[1] ); 
    return 0;
}


/**
 *  @brief Release a bluetooth serial port
 *
 * Undoes the action of bind (i.e. unbind).
 * 
 * Mac address is of the form xx:xx:xx:xx:xx:xx
 * 
 *  @param mac_address MAC address of the bluetooth device to release
 */
void sml_bluetooth_serial_release( char *mac_address )
{
    ___Send(request:"Bluetooth_Release", client_handle:-1, str_payload:mac_address, int_payload:___ISeq(), float_payload:___ISeq()); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	assert( l[0]=="OK" ); 
}

#endif
