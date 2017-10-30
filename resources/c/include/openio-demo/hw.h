#ifndef __HW_H
#define __HW_H

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

#include <assert.h>

/** client returns the handle to the requested object, or -1 if not exists */
int HW_GetObjecHandle(int objID, int instID) {
  ___Send(request:"HW_GetObjecHandle", client_handle:-1, str_payload:___NULL(),
    int_payload:___ISeq(objID, instID), float_payload:___ISeq());

  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}
// =======================================================================================
// =======================================================================================
// =======================================================================================

int LEDInit(int pinNum) {
  ___Send(request:"HW_LED_Init", client_handle:-1, str_payload:___NULL(),
    int_payload:___ISeq(pinNum), float_payload:___ISeq());

  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/** returns 0 on success, other values on error */
int LEDTurnON(int ID) {
  ___Send(request:"HW_LED_TurnON", client_handle:ID, str_payload:___NULL(),
    int_payload:___ISeq(), float_payload:___ISeq());

  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/** returns 0 on success, other values on error */
int LEDTurnOFF(int ID) {
  ___Send(request:"HW_LED_TurnOFF", client_handle:ID, str_payload:___NULL(),
    int_payload:___ISeq(), float_payload:___ISeq());

  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

// =======================================================================================
// =======================================================================================
// =======================================================================================

/** returns 0 on success, other values on error */
int ADCGetValue(int ID) {
    ___Send(request:"HW_ADC_GetValue", client_handle:ID, str_payload:___NULL(),
            int_payload:___ISeq(), float_payload:___ISeq());

  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

float GetTemp(int ID) {
 ___Send(request:"HW_Temp_GetValue", client_handle:ID, str_payload:___NULL(),
         int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

float GetHumid(int ID) {
 ___Send(request:"HW_Humid_GetValue", client_handle:ID, str_payload:___NULL(),
         int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[2];
}

/* @param ID the instance ID of the SensorObj */ 
float GetLux(int ID) {
 ___Send(request:"HW_LightSensor_GetValue", client_handle:ID, str_payload:___NULL(),
         int_payload:___ISeq(), float_payload:___ISeq());

  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[2];
}
// =======================================================================================
// =======================================================================================
// =======================================================================================
// Motor

int MotorON(int motorId) {
  ___Send(request:"HW_Motor_ON", client_handle:motorId, str_payload:___NULL(),
    int_payload:___ISeq(), float_payload:___ISeq());

  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

int MotorOFF(int motorId) {
  ___Send(request:"HW_Motor_OFF", client_handle:motorId, str_payload:___NULL(),
    int_payload:___ISeq(), float_payload:___ISeq());

  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/**
 * @brief sets the motor speed (in %)
 * @return 0 if failed, 1 otherwise
 */
int MotorSetSpeed(int motorId, int speed) {
  ___Send(request:"HW_Motor_SetSpeed", client_handle:motorId, str_payload:___NULL(),
    int_payload:___ISeq(speed), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

/**
 * @brief change the direction of the motor
 * @return 0 if failed, 1 otherwise
 */
int MotorToggleDirection(int motorId) {
  ___Send(request:"HW_Motor_ToggleDirection", client_handle:motorId, str_payload:___NULL(),
    int_payload:___ISeq(), float_payload:___ISeq());
  ___ListType_T(element_type:___NULL(), size:4) l = ___Receive();
  assert( l[0]=="Value" );
  return l[1];
}

#endif
