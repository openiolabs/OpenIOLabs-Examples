#ifndef __LED_H
#define __LED_H
#include <assert.h> 

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

int LEDInit(int pinNum)
{
  ___Send(request:"HW_LED_Init", client_handle:-1, str_payload:___NULL(), int_payload:___ISeq(pinNum), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/** returns 0 on success, other values on error */ 
int LEDTurnON(int ID)
{
  ___Send(request:"HW_LED_TurnON", client_handle:ID, str_payload:___NULL(), int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/** returns 0 on success, other values on error */ 
int LEDTurnOFF(int ID)
{
  ___Send(request:"HW_LED_TurnOFF", client_handle:ID, str_payload:___NULL(), int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}
#endif
