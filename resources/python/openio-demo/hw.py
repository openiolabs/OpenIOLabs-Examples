def LEDInit(pinNum):
  ___Send(request="HW_LED_Init", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(pinNum), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]

# returns 0 on success, other values on error 
def LEDTurnON(ID):
  ___Send(request="HW_LED_TurnON", client_handle=ID, str_payload=___NULL(), int_payload=___ISeq(), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]

# returns 0 on success, other values on error 
def LEDTurnOFF(ID):
  ___Send(request="HW_LED_TurnOFF", client_handle=ID, str_payload=___NULL(), int_payload=___ISeq(), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]
 
def GetTemp(ID):
    ___Send(request="HW_Temp_GetValue", client_handle=ID, str_payload=___NULL(),
            int_payload=___ISeq(), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="Value"
    return l[1]

def GetHumid(ID):
    ___Send(request="HW_Humid_GetValue", client_handle=ID, str_payload=___NULL(),
            int_payload=___ISeq(), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="Value"
    return l[1]

def GetLux(ID):
    ___Send(request="HW_LightSensor_GetValue", client_handle=ID, str_payload=___NULL(),
            int_payload=___ISeq(), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="Value"
    return l[2]

def MotorON(motorId):
    ___Send(request="HW_Motor_ON", client_handle=motorId, str_payload=___NULL(),
            int_payload=___ISeq(), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="Value"
    return l[1]

def MotorOFF(motorId):
    ___Send(request="HW_Motor_OFF", client_handle=motorId, str_payload=___NULL(),
            int_payload=___ISeq(), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="Value"
    return l[1]

def MotorSetSpeed(motorId, speed):
    ___Send(request="HW_Motor_SetSpeed", client_handle=motorId, str_payload=___NULL(),
            int_payload=___ISeq(speed), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="Value"
    return l[1]

def MotorToggleDirection(motorId):
    ___Send(request="HW_Motor_ToggleDirection", client_handle=motorId, str_payload=___NULL(),
            int_payload=___ISeq(), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="Value"
    return l[1]

