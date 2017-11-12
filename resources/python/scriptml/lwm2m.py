## @file
#  @package lwm2m
# 
#  @brief LWM2M object and resource definitions
# 
#  Auto-generated 12 November 2017; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from lwm2m_core import *

IPSO_Digital_Input_Digital_Input_State = 5500
##
#  @brief IPSO Digital Input
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Generic digital input for non-specific sensors
# 
def create_IPSO_Digital_Input():
    return {
        IPSO_Digital_Input_Digital_Input_State: bool(), ##< Digital Input State; R; boolean
    }

##  IPSO Digital Input
id_IPSO_Digital_Input = 3200

IPSO_Digital_Output_Digital_Output_State = 5550
##
#  @brief IPSO Digital Output
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Generic digital output for non-specific actuators
# 
def create_IPSO_Digital_Output():
    return {
        IPSO_Digital_Output_Digital_Output_State: bool(), ##< Digital Output State; RW; boolean
    }

##  IPSO Digital Output
id_IPSO_Digital_Output = 3201

IPSO_Analog_Input_Analog_Input_Current_Value = 5600
IPSO_Analog_Input_Min_Measured_Value = 5601
IPSO_Analog_Input_Max_Measured_Value = 5602
IPSO_Analog_Input_Min_Range_Value = 5603
IPSO_Analog_Input_Max_Range_Value = 5604
##
#  @brief IPSO Analog Input
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Generic analog input for non-specific sensors
# 
def create_IPSO_Analog_Input():
    return {
        IPSO_Analog_Input_Analog_Input_Current_Value: float(), ##< Analog Input Current Value; R; float; 0-1
        IPSO_Analog_Input_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Analog_Input_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Analog_Input_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Analog_Input_Max_Range_Value: float(), ##< Max Range Value; R; float
    }

##  IPSO Analog Input
id_IPSO_Analog_Input = 3202

IPSO_Analog_Output_Min_Range_Value = 5603
IPSO_Analog_Output_Max_Range_Value = 5604
IPSO_Analog_Output_Analog_Output_Current_Value = 5650
##
#  @brief IPSO Analog Output
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  This IPSO object is a generic object that can be used with any kind of
#  analog output interface.
# 
def create_IPSO_Analog_Output():
    return {
        IPSO_Analog_Output_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Analog_Output_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Analog_Output_Analog_Output_Current_Value: float(), ##< Analog Output Current Value; RW; float; 0-1
    }

##  IPSO Analog Output
id_IPSO_Analog_Output = 3203

IPSO_Generic_Sensor_Min_Measured_Value = 5601
IPSO_Generic_Sensor_Max_Measured_Value = 5602
IPSO_Generic_Sensor_Min_Range_Value = 5603
IPSO_Generic_Sensor_Max_Range_Value = 5604
IPSO_Generic_Sensor_Sensor_Value = 5700
IPSO_Generic_Sensor_Sensor_Units = 5701
##
#  @brief IPSO Generic Sensor
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  This IPSO object allow the description of a generic sensor. It is
#  based on the description of a value and a unit according to the UCUM
#  specification. Thus, any type of value defined within this
#  specification can be reporting using this object.  Specific object for
#  a given range of sensors is described later in the document, enabling
#  to identify the type of sensors directly from its Object ID. This
#  object may be used as a generic object if a dedicated one does not
#  exist.
# 
def create_IPSO_Generic_Sensor():
    return {
        IPSO_Generic_Sensor_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Generic_Sensor_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Generic_Sensor_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Generic_Sensor_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Generic_Sensor_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Generic_Sensor_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Generic Sensor
id_IPSO_Generic_Sensor = 3300

IPSO_Illuminance_Min_Measured_Value = 5601
IPSO_Illuminance_Max_Measured_Value = 5602
IPSO_Illuminance_Min_Range_Value = 5603
IPSO_Illuminance_Max_Range_Value = 5604
IPSO_Illuminance_Sensor_Value = 5700
IPSO_Illuminance_Sensor_Units = 5701
##
#  @brief IPSO Illuminance
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Illuminance sensor, example units = lx
# 
def create_IPSO_Illuminance():
    return {
        IPSO_Illuminance_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Illuminance_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Illuminance_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Illuminance_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Illuminance_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Illuminance_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Illuminance
id_IPSO_Illuminance = 3301

IPSO_Presence_Digital_Input_State = 5500
##
#  @brief IPSO Presence
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Presence sensor with digital sensing, optional delay parameters
# 
def create_IPSO_Presence():
    return {
        IPSO_Presence_Digital_Input_State: bool(), ##< Digital Input State; R; boolean
    }

##  IPSO Presence
id_IPSO_Presence = 3302

IPSO_Temperature_Min_Measured_Value = 5601
IPSO_Temperature_Max_Measured_Value = 5602
IPSO_Temperature_Min_Range_Value = 5603
IPSO_Temperature_Max_Range_Value = 5604
IPSO_Temperature_Sensor_Value = 5700
IPSO_Temperature_Sensor_Units = 5701
##
#  @brief IPSO Temperature
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This IPSO object should be used with a temperature sensor
#  to report a temperature measurement.  It also provides resources for
#  minimum/maximum measured values and the minimum/maximum range that can
#  be measured by the temperature sensor. An example measurement unit is
#  degrees Celsius (ucum:Cel).
# 
def create_IPSO_Temperature():
    return {
        IPSO_Temperature_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Temperature_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Temperature_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Temperature_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Temperature_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Temperature_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Temperature
id_IPSO_Temperature = 3303

IPSO_Humidity_Min_Measured_Value = 5601
IPSO_Humidity_Max_Measured_Value = 5602
IPSO_Humidity_Min_Range_Value = 5603
IPSO_Humidity_Max_Range_Value = 5604
IPSO_Humidity_Sensor_Value = 5700
IPSO_Humidity_Sensor_Units = 5701
##
#  @brief IPSO Humidity
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This IPSO object should be used with a humidity sensor to
#  report a humidity measurement.  It also provides resources for
#  minimum/maximum measured values and the minimum/maximum range that can
#  be measured by the humidity sensor. An example measurement unit is
#  relative humidity as a percentage (ucum:%).
# 
def create_IPSO_Humidity():
    return {
        IPSO_Humidity_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Humidity_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Humidity_Min_Range_Value: str(), ##< Min Range Value; R; string
        IPSO_Humidity_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Humidity_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Humidity_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Humidity
id_IPSO_Humidity = 3304

IPSO_Power_Measurement_Instantaneous_active_power = 5800
IPSO_Power_Measurement_Min_Measured_active_power = 5801
IPSO_Power_Measurement_Max_Measured_active_power = 5802
IPSO_Power_Measurement_Min_Range_active_power = 5803
IPSO_Power_Measurement_Max_Range_active_power = 5804
##
#  @brief IPSO Power Measurement
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  This IPSO object should be used over a power measurement sensor to
#  report a remote power measurement.  It also provides resources for
#  minimum/maximum measured values and the minimum/maximum range for both
#  active and reactive power. Il also provides resources for cumulative
#  energy, calibration, and the power factor.
# 
def create_IPSO_Power_Measurement():
    return {
        IPSO_Power_Measurement_Instantaneous_active_power: float(), ##< Instantaneous active power; R; float; W
        IPSO_Power_Measurement_Min_Measured_active_power: float(), ##< Min Measured active power; R; float; W
        IPSO_Power_Measurement_Max_Measured_active_power: float(), ##< Max Measured  active power; R; float; W
        IPSO_Power_Measurement_Min_Range_active_power: float(), ##< Min  Range  active power; R; float; W
        IPSO_Power_Measurement_Max_Range_active_power: float(), ##< Max Range active power; R; float; W
    }

##  IPSO Power Measurement
id_IPSO_Power_Measurement = 3305

IPSO_Actuation_OnOff = 5850
##
#  @brief IPSO Actuation
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  This IPSO object is dedicated to remote actuation such as ON/OFF
#  action or dimming. A multi-state output can also be described as a
#  string. This is useful to send pilot wire orders for instance. It also
#  provides a resource to reflect the time that the device has been
#  switched on.
# 
def create_IPSO_Actuation():
    return {
        IPSO_Actuation_OnOff: bool(), ##< On/Off; RW; boolean
    }

##  IPSO Actuation
id_IPSO_Actuation = 3306

IPSO_Set_Point_Units = 5701
IPSO_Set_Point_Set_Point_Value = 5900
##
#  @brief IPSO Set Point
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This IPSO object should be used to set a desired value to
#  a controller, such as a thermostat. This object enables a setpoint to
#  be expressed units defined in the UCUM specification, to match an
#  associated sensor or measurement value. A special resource is added to
#  set the colour of an object.
# 
def create_IPSO_Set_Point():
    return {
        IPSO_Set_Point_Units: str(), ##< Units; R; string
        IPSO_Set_Point_Set_Point_Value: float(), ##< Set Point Value; RW; float
    }

##  IPSO Set Point
id_IPSO_Set_Point = 3308

IPSO_Light_Control_OnOff = 5850
IPSO_Light_Control_Dimmer = 5851
##
#  @brief IPSO Light Control
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This Object is used to control a light source, such as a
#  LED or other light.  It allows a light to be turned on or off and its
#  dimmer setting to be control as a % between 0 and 100. An optional
#  colour setting enables a string to be used to indicate the desired
#  colour.
# 
def create_IPSO_Light_Control():
    return {
        IPSO_Light_Control_OnOff: bool(), ##< On/Off; RW; boolean
        IPSO_Light_Control_Dimmer: int(), ##< Dimmer; RW; integer; 0-100; %
    }

##  IPSO Light Control
id_IPSO_Light_Control = 3311

IPSO_Power_Control_OnOff = 5850
##
#  @brief IPSO Power Control
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This Object is used to control a power source, such as a
#  Smart Plug.  It allows a power relay to be turned on or off and its
#  dimmer setting to be control as a % between 0 and 100.
# 
def create_IPSO_Power_Control():
    return {
        IPSO_Power_Control_OnOff: bool(), ##< On/Off; RW; boolean
    }

##  IPSO Power Control
id_IPSO_Power_Control = 3312

IPSO_Accelerometer_Min_Range_Value = 5603
IPSO_Accelerometer_Max_Range_Value = 5604
IPSO_Accelerometer_Sensor_Units = 5701
IPSO_Accelerometer_X_Value = 5702
IPSO_Accelerometer_Y_Value = 5703
IPSO_Accelerometer_Z_Value = 5704
##
#  @brief IPSO Accelerometer
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This IPSO object can be used to represent a 1-3 axis
#  accelerometer.
# 
def create_IPSO_Accelerometer():
    return {
        IPSO_Accelerometer_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Accelerometer_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Accelerometer_Sensor_Units: str(), ##< Sensor Units; R; string
        IPSO_Accelerometer_X_Value: float(), ##< X Value; R; float
        IPSO_Accelerometer_Y_Value: float(), ##< Y Value; R; float
        IPSO_Accelerometer_Z_Value: float(), ##< Z Value; R; float
    }

##  IPSO Accelerometer
id_IPSO_Accelerometer = 3313

IPSO_Magnetometer_Sensor_Units = 5701
IPSO_Magnetometer_X_Value = 5702
IPSO_Magnetometer_Y_Value = 5703
IPSO_Magnetometer_Z_Value = 5704
IPSO_Magnetometer_Compass_Direction = 5705
##
#  @brief IPSO Magnetometer
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This IPSO object can be used to represent a 1-3 axis
#  magnetometer with optional compass direction.
# 
def create_IPSO_Magnetometer():
    return {
        IPSO_Magnetometer_Sensor_Units: str(), ##< Sensor Units; R; string
        IPSO_Magnetometer_X_Value: float(), ##< X Value; R; float
        IPSO_Magnetometer_Y_Value: float(), ##< Y Value; R; float
        IPSO_Magnetometer_Z_Value: float(), ##< Z Value; R; float
        IPSO_Magnetometer_Compass_Direction: float(), ##< Compass Direction; R; float; 0-360; Deg
    }

##  IPSO Magnetometer
id_IPSO_Magnetometer = 3314

IPSO_Barometer_Min_Measured_Value = 5601
IPSO_Barometer_Max_Measured_Value = 5602
IPSO_Barometer_Min_Range_Value = 5603
IPSO_Barometer_Max_Range_Value = 5604
IPSO_Barometer_Sensor_Value = 5700
IPSO_Barometer_Sensor_Units = 5701
##
#  @brief IPSO Barometer
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This IPSO object should be used with an air pressure
#  sensor to report a barometer measurement.  It also provides resources
#  for minimum/maximum measured values and the minimum/maximum range that
#  can be measured by the barometer sensor. An example measurement unit
#  is kPa (ucum:kPa).
# 
def create_IPSO_Barometer():
    return {
        IPSO_Barometer_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Barometer_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Barometer_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Barometer_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Barometer_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Barometer_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Barometer
id_IPSO_Barometer = 3315

IPSO_Voltage_Min_Measured_Value = 5601
IPSO_Voltage_Max_Measured_Value = 5602
IPSO_Voltage_Min_Range_Value = 5603
IPSO_Voltage_Max_Range_Value = 5604
IPSO_Voltage_Sensor_Value = 5700
IPSO_Voltage_Sensor_Units = 5701
##
#  @brief IPSO Voltage
# 
#  @return new LWM2M object
# 
#  This IPSO object should be used with voltmeter sensor to report
#  measured voltage between two points.  It also provides resources for
#  minimum and maximum measured values, as well as the minimum and
#  maximum range that can be measured by the sensor. An example
#  measurement unit is volts (ucum: V).
#  
#  Instance type: multiple
# 
def create_IPSO_Voltage():
    return {
        IPSO_Voltage_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Voltage_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Voltage_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Voltage_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Voltage_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Voltage_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Voltage
id_IPSO_Voltage = 3316

IPSO_Current_Min_Measured_Value = 5601
IPSO_Current_Max_Measured_Value = 5602
IPSO_Current_Min_Range_Value = 5603
IPSO_Current_Max_Range_Value = 5604
IPSO_Current_Sensor_Value = 5700
IPSO_Current_Sensor_Units = 5701
##
#  @brief IPSO Current
# 
#  @return new LWM2M object
# 
#  This IPSO object should be used with an ammeter to report measured
#  electric current in amperes. It also provides resources for minimum
#  and maximum measured values, as well as the minimum and maximum range
#  that can be measured by the sensor. An example measurement unit is
#  volts (ucum: A).
#  
#  Instance type: multiple
# 
def create_IPSO_Current():
    return {
        IPSO_Current_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Current_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Current_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Current_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Current_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Current_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Current
id_IPSO_Current = 3317

IPSO_Frequency_Min_Measured_Value = 5601
IPSO_Frequency_Max_Measured_Value = 5602
IPSO_Frequency_Min_Range_Value = 5603
IPSO_Frequency_Max_Range_Value = 5604
IPSO_Frequency_Sensor_Value = 5700
IPSO_Frequency_Sensor_Units = 5701
##
#  @brief IPSO Frequency
# 
#  @return new LWM2M object
# 
#  This IPSO object should be used to report frequency measurements. It
#  also provides resources for minimum and maximum measured values, as
#  well as the minimum and maximum range that can be measured by the
#  sensor. An example measurement unit is volts (ucum: Hz).
#  
#  Instance type: multiple
# 
def create_IPSO_Frequency():
    return {
        IPSO_Frequency_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Frequency_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Frequency_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Frequency_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Frequency_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Frequency_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Frequency
id_IPSO_Frequency = 3318

IPSO_Depth_Min_Measured_Value = 5601
IPSO_Depth_Max_Measured_Value = 5602
IPSO_Depth_Min_Range_Value = 5603
IPSO_Depth_Max_Range_Value = 5604
IPSO_Depth_Sensor_Value = 5700
IPSO_Depth_Sensor_Units = 5701
##
#  @brief IPSO Depth
# 
#  @return new LWM2M object
# 
#  This IPSO object should be used to report depth measurements. It can,
#  for example, be used to describe a generic rain gauge that measures
#  the accumulated rainfall in millimetres (mm) or in fathoms (fth)
#  
#  Instance type: multiple
# 
def create_IPSO_Depth():
    return {
        IPSO_Depth_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Depth_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Depth_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Depth_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Depth_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Depth_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Depth
id_IPSO_Depth = 3319

IPSO_Percentage_Min_Measured_Value = 5601
IPSO_Percentage_Max_Measured_Value = 5602
IPSO_Percentage_Min_Range_Value = 5603
IPSO_Percentage_Max_Range_Value = 5604
IPSO_Percentage_Sensor_Value = 5700
IPSO_Percentage_Sensor_Units = 5701
##
#  @brief IPSO Percentage
# 
#  @return new LWM2M object
# 
#  This IPSO object should can be used to report measurements relative to
#  a 0-100% scale. For example it could be used to measure the level of a
#  liquid in a vessel or container in units of %.
#  
#  Instance type: multiple
# 
def create_IPSO_Percentage():
    return {
        IPSO_Percentage_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Percentage_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Percentage_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Percentage_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Percentage_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Percentage_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Percentage
id_IPSO_Percentage = 3320

IPSO_Altitude_Min_Measured_Value = 5601
IPSO_Altitude_Max_Measured_Value = 5602
IPSO_Altitude_Min_Range_Value = 5603
IPSO_Altitude_Max_Range_Value = 5604
IPSO_Altitude_Sensor_Value = 5700
IPSO_Altitude_Sensor_Units = 5701
##
#  @brief IPSO Altitude
# 
#  @return new LWM2M object
# 
#  This IPSO object should be used with an altitude sensor to report
#  altitude above sea level in meters. Note that Altitude can be
#  calculated from the measured pressure given the local sea level
#  pressure. It also provides resources for minimum and maximum measured
#  values, as well as the minimum and maximum range that can be measured
#  by the sensor. An example measurement unit is meters (ucum: m).
#  
#  Instance type: multiple
# 
def create_IPSO_Altitude():
    return {
        IPSO_Altitude_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Altitude_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Altitude_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Altitude_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Altitude_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Altitude_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Altitude
id_IPSO_Altitude = 3321

IPSO_Load_Min_Measured_Value = 5601
IPSO_Load_Max_Measured_Value = 5602
IPSO_Load_Min_Range_Value = 5603
IPSO_Load_Max_Range_Value = 5604
IPSO_Load_Sensor_Value = 5700
IPSO_Load_Sensor_Units = 5701
##
#  @brief IPSO Load
# 
#  @return new LWM2M object
# 
#  This IPSO object should be used with a load sensor (as in a scale) to
#  report the applied weight or force. It also provides resources for
#  minimum and maximum measured values, as well as the minimum and
#  maximum range that can be measured by the sensor. An example
#  measurement unit is kilograms (ucum: Kg).
#  
#  Instance type: multiple
# 
def create_IPSO_Load():
    return {
        IPSO_Load_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Load_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Load_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Load_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Load_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Load_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Load
id_IPSO_Load = 3322

IPSO_Pressure_Min_Measured_Value = 5601
IPSO_Pressure_Max_Measured_Value = 5602
IPSO_Pressure_Min_Range_Value = 5603
IPSO_Pressure_Max_Range_Value = 5604
IPSO_Pressure_Sensor_Value = 5700
IPSO_Pressure_Sensor_Units = 5701
##
#  @brief IPSO Pressure
# 
#  @return new LWM2M object
# 
#  This IPSO object should be used to report pressure measurements. It
#  also provides resources for minimum and maximum measured values, as
#  well as the minimum and maximum range that can be measured by the
#  sensor. An example measurement unit is pascals (ucum: Pa).
#  
#  Instance type: multiple
# 
def create_IPSO_Pressure():
    return {
        IPSO_Pressure_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Pressure_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Pressure_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Pressure_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Pressure_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Pressure_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Pressure
id_IPSO_Pressure = 3323

IPSO_Loudness_Min_Measured_Value = 5601
IPSO_Loudness_Max_Measured_Value = 5602
IPSO_Loudness_Min_Range_Value = 5603
IPSO_Loudness_Max_Range_Value = 5604
IPSO_Loudness_Sensor_Value = 5700
IPSO_Loudness_Sensor_Units = 5701
##
#  @brief IPSO Loudness
# 
#  @return new LWM2M object
# 
#  This IPSO object should be used to report loudness or noise level
#  measurements. It also provides resources for minimum and maximum
#  measured values, as well as the minimum and maximum range that can be
#  measured by the sensor. An example measurement unit is decibels (ucum:
#  dB).
#  
#  Instance type: multiple
# 
def create_IPSO_Loudness():
    return {
        IPSO_Loudness_Min_Measured_Value: float(), ##< Min Measured Value; R; float
        IPSO_Loudness_Max_Measured_Value: float(), ##< Max Measured Value; R; float
        IPSO_Loudness_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Loudness_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Loudness_Sensor_Value: float(), ##< Sensor Value; R; float
        IPSO_Loudness_Sensor_Units: str(), ##< Sensor Units; R; string
    }

##  IPSO Loudness
id_IPSO_Loudness = 3324

IPSO_Gyrometer_Min_Range_Value = 5603
IPSO_Gyrometer_Max_Range_Value = 5604
IPSO_Gyrometer_Sensor_Units = 5701
IPSO_Gyrometer_X_Value = 5702
IPSO_Gyrometer_Y_Value = 5703
IPSO_Gyrometer_Z_Value = 5704
IPSO_Gyrometer_Min_X_Value = 5708
IPSO_Gyrometer_Max_X_Value = 5709
IPSO_Gyrometer_Min_Y_Value = 5710
IPSO_Gyrometer_Max_Y_Value = 5711
IPSO_Gyrometer_Min_Z_Value = 5712
IPSO_Gyrometer_Max_Z_Value = 5713
##
#  @brief IPSO Gyrometer
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Description: This IPSO Object is used to report the current reading of
#  a gyrometer sensor in 3 axes. It provides tracking of the minimum and
#  maximum angular rate in all 3 axes. An example unit of measure is
#  radians per second (ucum:rad/s).
# 
def create_IPSO_Gyrometer():
    return {
        IPSO_Gyrometer_Min_Range_Value: float(), ##< Min Range Value; R; float
        IPSO_Gyrometer_Max_Range_Value: float(), ##< Max Range Value; R; float
        IPSO_Gyrometer_Sensor_Units: str(), ##< Sensor Units; R; string
        IPSO_Gyrometer_X_Value: float(), ##< X Value; R; float
        IPSO_Gyrometer_Y_Value: float(), ##< Y Value; R; float
        IPSO_Gyrometer_Z_Value: float(), ##< Z Value; R; float
        IPSO_Gyrometer_Min_X_Value: float(), ##< Min X Value; R; float
        IPSO_Gyrometer_Max_X_Value: float(), ##< Max X Value; R; float
        IPSO_Gyrometer_Min_Y_Value: float(), ##< Min Y Value; R; float
        IPSO_Gyrometer_Max_Y_Value: float(), ##< Max Y Value; R; float
        IPSO_Gyrometer_Min_Z_Value: float(), ##< Min Z Value; R; float
        IPSO_Gyrometer_Max_Z_Value: float(), ##< Max Z Value; R; float
    }

##  IPSO Gyrometer
id_IPSO_Gyrometer = 3334

IPSO_Loudness_Text = 5527
##
#  @brief IPSO Addressable Text Display
# 
#  @return new LWM2M object
# 
#  This IPSO object is used to send text to a text-only or text mode
#  graphics display. POSTing a string of text to the text resource causes
#  it to be displayed at the selected X and Y locations on the display.
#  If X or Y are set to a value greater than the size of the display, the
#  position wraps around to the modulus of the setting and the display
#  size. Likewise, if the text string overflows the display size, the
#  text wraps around and displays on the next line down or, if the last
#  line has been written, wraps around to the top of the display.
#  Brightness and Contrast controls are provided to allow control of
#  various display types including STN and DSTN type LCD character
#  displays. POSTing an empty payload to the Clear Display resource
#  causes the display to be erased.
#  
#  Instance type: multiple
# 
def create_IPSO_Loudness():
    return {
        IPSO_Loudness_Text: str(), ##< Text; RW; string
    }

##  IPSO Addressable Text Display
id_IPSO_Loudness = 3324

OpenIO_Camera_Interface_Upload_URL = 0
OpenIO_Camera_Interface_Image_object = 1
##
#  @brief OpenIO Camera Interface
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Provides an interface for OpenIO devices to send still images to the
#  server
# 
def create_OpenIO_Camera_Interface():
    return {
        OpenIO_Camera_Interface_Upload_URL: str(), ##< Upload URL; W; string
        OpenIO_Camera_Interface_Image_object: str(), ##< Image object; R; string
    }

##  OpenIO Camera Interface
id_OpenIO_Camera_Interface = 7011

OpenIO_I2C_Interface_Object_Type = 0
##
#  @brief OpenIO I2C Interface
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Provides an interface for OpenIO devices to present I2C-connected
#  objects
# 
def create_OpenIO_I2C_Interface():
    return {
        OpenIO_I2C_Interface_Object_Type: int(), ##< Object Type; RW; integer
    }

##  OpenIO I2C Interface
id_OpenIO_I2C_Interface = 7012

OpenIO_SPI_Interface_Object_Type = 0
##
#  @brief OpenIO SPI Interface
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Provides an interface for OpenIO devices to present SPI-connected
#  objects
# 
def create_OpenIO_SPI_Interface():
    return {
        OpenIO_SPI_Interface_Object_Type: int(), ##< Object Type; RW; integer
    }

##  OpenIO SPI Interface
id_OpenIO_SPI_Interface = 7013

OpenIO_UART_Interface_Object_Type = 0
##
#  @brief OpenIO UART Interface
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Provides an interface for OpenIO devices to present UART-connected
#  objects
# 
def create_OpenIO_UART_Interface():
    return {
        OpenIO_UART_Interface_Object_Type: int(), ##< Object Type; RW; integer
    }

##  OpenIO UART Interface
id_OpenIO_UART_Interface = 7014

OpenIO_Surface_Plotter_Upload_URL = 0
OpenIO_Surface_Plotter_Surface_data = 1
##
#  @brief OpenIO Surface Plotter
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Provides an interface for OpenIO devices to send 3D data to the server
# 
def create_OpenIO_Surface_Plotter():
    return {
        OpenIO_Surface_Plotter_Upload_URL: str(), ##< Upload URL; W; string
        OpenIO_Surface_Plotter_Surface_data: str(), ##< Surface data; W; string
    }

##  OpenIO Surface Plotter
id_OpenIO_Surface_Plotter = 7015

OpenIO_Motor_Control_Velocity = 0
OpenIO_Motor_Control_State = 1
OpenIO_Motor_Control_Direction = 2
##
#  @brief OpenIO Motor Control
# 
#  @return new LWM2M object
# 
#  Not mandatory
#  
#  Instance type: multiple
#  
#  Actuator object to control a motor
# 
def create_OpenIO_Motor_Control():
    return {
        OpenIO_Motor_Control_Velocity: int(), ##< Velocity; RW; integer
        OpenIO_Motor_Control_State: bool(), ##< State; RW; boolean
        OpenIO_Motor_Control_Direction: bool(), ##< Direction; RW; boolean
    }

##  OpenIO Motor Control
id_OpenIO_Motor_Control = 7017

OpenIO_Clientpushed_text_object_Object = 0
OpenIO_Clientpushed_text_object_ObjectID = 1
##
#  @brief OpenIO Client-pushed text object
# 
#  @return new LWM2M object
# 
#  Mandatory
#  
#  Instance type: single
#  
#  Allows the client to push text objects to the server, and optionally,
#  to the UI
# 
def create_OpenIO_Clientpushed_text_object():
    return {
        OpenIO_Clientpushed_text_object_Object: str(), ##< Object; RW; string
        OpenIO_Clientpushed_text_object_ObjectID: str(), ##< ObjectID; W; string
    }

##  OpenIO Client-pushed text object
id_OpenIO_Clientpushed_text_object = 7019

