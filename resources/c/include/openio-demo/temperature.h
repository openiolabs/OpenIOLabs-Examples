#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H
#include <assert.h> 

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

/// At the moment of writing this handles the TMP36GZ sensor
/// not that it should matter in the future 
const int TEMPERATURE_HANDLE = 3303; 

int GetTemperatureHandle(int instID)
{
  ___Send(request:"GetTempHandle", client_handle:-1, str_payload:___NULL(), int_payload:___ISeq(TEMPERATURE_HANDLE, instID), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}


int TempInit(int pinNum)
{
  ___Send(request:"HW_Temp_Init", client_handle:-1, str_payload:___NULL(), int_payload:___ISeq(pinNum), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}


/** returns 0 on success, other values on error */ 
int TempRead(int ID)
{
  ___Send(request:"HW_Temp_Read", client_handle:ID, str_payload:___NULL(), int_payload:___ISeq(1), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

#endif
