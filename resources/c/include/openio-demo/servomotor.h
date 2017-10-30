#ifndef __SERVOMOTOR_H
#define __SERVOMOTOR_H
#include <assert.h> 

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

const int SERVO_HANDLE = 7017; 

int GetServoMotorHandle(int instID)
{
  ___Send(request:"HW_GetServoMotorHandle", client_handle:-1, str_payload:___NULL(), int_payload:___ISeq(SERVO_HANDLE, instID), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

int ServoMotorInit(int pinNum)
{
  ___Send(request:"HW_ServoMotor_Init", client_handle:-1, str_payload:___NULL(), int_payload:___ISeq(pinNum), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/** returns 0 on success, other values on error */ 
int ServoMotorStart(int ID)
{
  ___Send(request:"HW_ServoMotor_Start", client_handle:ID, str_payload:___NULL(), int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/** returns 0 on success, other values on error */ 
int ServoMotorStop(int ID)
{
  ___Send(request:"HW_ServoMotor_Stop", client_handle:ID, str_payload:___NULL(), int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}
#endif
