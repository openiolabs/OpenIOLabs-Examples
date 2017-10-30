#ifndef __STEPPERMOTOR_H
#define __STEPPERMOTOR_H
#include <assert.h> 

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

const int STEPPER_HANDLE = 7017; 

int GetStepperMotorHandle(int instID)
{
  ___Send(request:"HW_GetStepperMotorHandle", client_handle:-1, str_payload:___NULL(), int_payload:___ISeq(STEPPER_HANDLE, instID), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

int StepperMotorInit(int pinNum)
{
  ___Send(request:"HW_StepperMotor_Init", client_handle:-1, str_payload:___NULL(), int_payload:___ISeq(pinNum), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/** returns 0 on success, other values on error */ 
int StepperMotorStart(int ID)
{
  ___Send(request:"HW_StepperMotor_Start", client_handle:ID, str_payload:___NULL(), int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/** returns 0 on success, other values on error */ 
int StepperMotorStop(int ID)
{
  ___Send(request:"HW_StepperMotor_Stop", client_handle:ID, str_payload:___NULL(), int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:3) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}
#endif
