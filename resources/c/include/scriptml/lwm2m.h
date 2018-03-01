/** @file
 * 
 *  @brief LWM2M object and resource definitions
 * 
 *  Auto-generated 01 March 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __LWM2M_H
#define __LWM2M_H

#include <lwm2m_core.h>

/**
 *  @brief IPSO Digital Input
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Generic digital input for non-specific sensors
 */
typedef struct
{
    /**
     *  @brief Digital Input State
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Type: boolean
     *  
     *  The current state of a digital input.
     */
    int LWM2M_RESOURCE( 5500, Digital_Input_State );
} LWM2M_IPSO_Digital_Input_T;

/**  IPSO Digital Input */
#define LWM2M_IPSO_Digital_Input LWM2M_OBJECT_ID( 3200 )

/**
 *  @brief IPSO Digital Output
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Generic digital output for non-specific actuators
 */
typedef struct
{
    /**
     *  @brief Digital Output State
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Type: boolean
     *  
     *  The current state of a digital output.
     */
    int LWM2M_RESOURCE( 5550, Digital_Output_State );
} LWM2M_IPSO_Digital_Output_T;

/**  IPSO Digital Output */
#define LWM2M_IPSO_Digital_Output LWM2M_OBJECT_ID( 3201 )

/**
 *  @brief IPSO Analog Input
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Generic analog input for non-specific sensors
 */
typedef struct
{
    /**
     *  @brief Analog Input Current Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Range: 0-1
     *  
     *  Type: float
     *  
     *  The current value of the analog input.
     */
    float LWM2M_RESOURCE( 5600, Analog_Input_Current_Value );
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
} LWM2M_IPSO_Analog_Input_T;

/**  IPSO Analog Input */
#define LWM2M_IPSO_Analog_Input LWM2M_OBJECT_ID( 3202 )

/**
 *  @brief IPSO Analog Output
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  This IPSO object is a generic object that can be used with any kind of
 *  analog output interface.
 */
typedef struct
{
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Analog Output Current Value
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Range: 0-1
     *  
     *  Type: float
     *  
     *  The current state of the analogue output.
     */
    float LWM2M_RESOURCE( 5650, Analog_Output_Current_Value );
} LWM2M_IPSO_Analog_Output_T;

/**  IPSO Analog Output */
#define LWM2M_IPSO_Analog_Output LWM2M_OBJECT_ID( 3203 )

/**
 *  @brief IPSO Generic Sensor
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  This IPSO object allow the description of a generic sensor. It is
 *  based on the description of a value and a unit according to the UCUM
 *  specification. Thus, any type of value defined within this
 *  specification can be reporting using this object.  Specific object for
 *  a given range of sensors is described later in the document, enabling
 *  to identify the type of sensors directly from its Object ID. This
 *  object may be used as a generic object if a dedicated one does not
 *  exist.
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  Measurement Units Definition e.g. 'Cel' for Temperature in Celsius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Generic_Sensor_T;

/**  IPSO Generic Sensor */
#define LWM2M_IPSO_Generic_Sensor LWM2M_OBJECT_ID( 3300 )

/**
 *  @brief IPSO Illuminance
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Illuminance sensor, example units = lx
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The current value of the luminosity sensor.
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Illuminance_T;

/**  IPSO Illuminance */
#define LWM2M_IPSO_Illuminance LWM2M_OBJECT_ID( 3301 )

/**
 *  @brief IPSO Presence
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Presence sensor with digital sensing, optional delay parameters
 */
typedef struct
{
    /**
     *  @brief Digital Input State
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Type: boolean
     *  
     *  The current state of the presence sensor
     */
    int LWM2M_RESOURCE( 5500, Digital_Input_State );
} LWM2M_IPSO_Presence_T;

/**  IPSO Presence */
#define LWM2M_IPSO_Presence LWM2M_OBJECT_ID( 3302 )

/**
 *  @brief IPSO Temperature
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This IPSO object should be used with a temperature sensor
 *  to report a temperature measurement.  It also provides resources for
 *  minimum/maximum measured values and the minimum/maximum range that can
 *  be measured by the temperature sensor. An example measurement unit is
 *  degrees Celsius (ucum:Cel).
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  Measurement Units Definition e.g. 'Cel' for Temperature in Celsius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Temperature_T;

/**  IPSO Temperature */
#define LWM2M_IPSO_Temperature LWM2M_OBJECT_ID( 3303 )

/**
 *  @brief IPSO Humidity
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This IPSO object should be used with a humidity sensor to
 *  report a humidity measurement.  It also provides resources for
 *  minimum/maximum measured values and the minimum/maximum range that can
 *  be measured by the humidity sensor. An example measurement unit is
 *  relative humidity as a percentage (ucum:%).
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: string
     *  
     *  The minimum value that can be measured by the sensor
     */
    char * LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  Measurement Units Definition e.g. 'Cel' for Temperature in Celsius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Humidity_T;

/**  IPSO Humidity */
#define LWM2M_IPSO_Humidity LWM2M_OBJECT_ID( 3304 )

/**
 *  @brief IPSO Power Measurement
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  This IPSO object should be used over a power measurement sensor to
 *  report a remote power measurement.  It also provides resources for
 *  minimum/maximum measured values and the minimum/maximum range for both
 *  active and reactive power. Il also provides resources for cumulative
 *  energy, calibration, and the power factor.
 */
typedef struct
{
    /**
     *  @brief Instantaneous active power
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: w
     *  
     *  Type: float
     *  
     *  The current active power
     */
    float LWM2M_RESOURCE( 5800, Instantaneous_active_power );
    /**
     *  @brief Min Measured active power
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: w
     *  
     *  Type: float
     *  
     *  The minimum active power measured by the sensor since it is ON
     */
    float LWM2M_RESOURCE( 5801, Min_Measured_active_power );
    /**
     *  @brief Max Measured  active power
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: w
     *  
     *  Type: float
     *  
     *  The maximum active power measured by the sensor since it is ON
     */
    float LWM2M_RESOURCE( 5802, Max_Measured_active_power );
    /**
     *  @brief Min  Range  active power
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: w
     *  
     *  Type: float
     *  
     *  The minimum active power that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5803, Min_Range_active_power );
    /**
     *  @brief Max Range active power
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: w
     *  
     *  Type: float
     *  
     *  The maximum active power that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5804, Max_Range_active_power );
} LWM2M_IPSO_Power_Measurement_T;

/**  IPSO Power Measurement */
#define LWM2M_IPSO_Power_Measurement LWM2M_OBJECT_ID( 3305 )

/**
 *  @brief IPSO Actuation
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  This IPSO object is dedicated to remote actuation such as ON/OFF
 *  action or dimming. A multi-state output can also be described as a
 *  string. This is useful to send pilot wire orders for instance. It also
 *  provides a resource to reflect the time that the device has been
 *  switched on.
 */
typedef struct
{
    /**
     *  @brief On/Off
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Type: boolean
     *  
     *  On/Off
     */
    int LWM2M_RESOURCE( 5850, OnOff );
} LWM2M_IPSO_Actuation_T;

/**  IPSO Actuation */
#define LWM2M_IPSO_Actuation LWM2M_OBJECT_ID( 3306 )

/**
 *  @brief IPSO Set Point
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This IPSO object should be used to set a desired value to
 *  a controller, such as a thermostat. This object enables a setpoint to
 *  be expressed units defined in the UCUM specification, to match an
 *  associated sensor or measurement value. A special resource is added to
 *  set the colour of an object.
 */
typedef struct
{
    /**
     *  @brief Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Units );
    /**
     *  @brief Set Point Value
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The setpoint value.
     */
    float LWM2M_RESOURCE( 5900, Set_Point_Value );
} LWM2M_IPSO_Set_Point_T;

/**  IPSO Set Point */
#define LWM2M_IPSO_Set_Point LWM2M_OBJECT_ID( 3308 )

/**
 *  @brief IPSO Light Control
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This Object is used to control a light source, such as a
 *  LED or other light.  It allows a light to be turned on or off and its
 *  dimmer setting to be control as a % between 0 and 100. An optional
 *  colour setting enables a string to be used to indicate the desired
 *  colour.
 */
typedef struct
{
    /**
     *  @brief On/Off
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Type: boolean
     *  
     *  This resource represents a light, which can be controlled, the setting
     *  of which is a Boolean value (1,0) where 1 is on and 0 is off.
     */
    int LWM2M_RESOURCE( 5850, OnOff );
    /**
     *  @brief Dimmer
     * 
     *  Operations: read, write
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Range: 0-100
     *  
     *  Units: %
     *  
     *  Type: integer
     *  
     *  This resource represents a light dimmer setting, which has an Integer
     *  value between 0 and 100 as a percentage.
     */
    int LWM2M_RESOURCE( 5851, Dimmer );
} LWM2M_IPSO_Light_Control_T;

/**  IPSO Light Control */
#define LWM2M_IPSO_Light_Control LWM2M_OBJECT_ID( 3311 )

/**
 *  @brief IPSO Power Control
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This Object is used to control a power source, such as a
 *  Smart Plug.  It allows a power relay to be turned on or off and its
 *  dimmer setting to be control as a % between 0 and 100.
 */
typedef struct
{
    /**
     *  @brief On/Off
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Type: boolean
     *  
     *  This resource represents a power relay, which can be controlled, the
     *  setting of which is a Boolean value (1,0) where 1 is on and 0 is off.
     */
    int LWM2M_RESOURCE( 5850, OnOff );
} LWM2M_IPSO_Power_Control_T;

/**  IPSO Power Control */
#define LWM2M_IPSO_Power_Control LWM2M_OBJECT_ID( 3312 )

/**
 *  @brief IPSO Accelerometer
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This IPSO object can be used to represent a 1-3 axis
 *  accelerometer.
 */
typedef struct
{
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  Measurement Units Definition e.g. 'Cel' for Temperature in Celsius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
    /**
     *  @brief X Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the X axis.
     */
    float LWM2M_RESOURCE( 5702, X_Value );
    /**
     *  @brief Y Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the Y axis.
     */
    float LWM2M_RESOURCE( 5703, Y_Value );
    /**
     *  @brief Z Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the Z axis.
     */
    float LWM2M_RESOURCE( 5704, Z_Value );
} LWM2M_IPSO_Accelerometer_T;

/**  IPSO Accelerometer */
#define LWM2M_IPSO_Accelerometer LWM2M_OBJECT_ID( 3313 )

/**
 *  @brief IPSO Magnetometer
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This IPSO object can be used to represent a 1-3 axis
 *  magnetometer with optional compass direction.
 */
typedef struct
{
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  Measurement Units Definition e.g. 'Cel' for Temperature in Celsius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
    /**
     *  @brief X Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the X axis.
     */
    float LWM2M_RESOURCE( 5702, X_Value );
    /**
     *  @brief Y Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the Y axis.
     */
    float LWM2M_RESOURCE( 5703, Y_Value );
    /**
     *  @brief Z Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the Z axis.
     */
    float LWM2M_RESOURCE( 5704, Z_Value );
    /**
     *  @brief Compass Direction
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Range: 0-360
     *  
     *  Units: deg
     *  
     *  Type: float
     *  
     *  The compass direction
     */
    float LWM2M_RESOURCE( 5705, Compass_Direction );
} LWM2M_IPSO_Magnetometer_T;

/**  IPSO Magnetometer */
#define LWM2M_IPSO_Magnetometer LWM2M_OBJECT_ID( 3314 )

/**
 *  @brief IPSO Barometer
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This IPSO object should be used with an air pressure
 *  sensor to report a barometer measurement.  It also provides resources
 *  for minimum/maximum measured values and the minimum/maximum range that
 *  can be measured by the barometer sensor. An example measurement unit
 *  is kPa (ucum:kPa).
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Barometer_T;

/**  IPSO Barometer */
#define LWM2M_IPSO_Barometer LWM2M_OBJECT_ID( 3315 )

/**
 *  @brief IPSO Voltage
 * 
 *  This IPSO object should be used with voltmeter sensor to report
 *  measured voltage between two points.  It also provides resources for
 *  minimum and maximum measured values, as well as the minimum and
 *  maximum range that can be measured by the sensor. An example
 *  measurement unit is volts (ucum: V).
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Voltage_T;

/**  IPSO Voltage */
#define LWM2M_IPSO_Voltage LWM2M_OBJECT_ID( 3316 )

/**
 *  @brief IPSO Current
 * 
 *  This IPSO object should be used with an ammeter to report measured
 *  electric current in amperes. It also provides resources for minimum
 *  and maximum measured values, as well as the minimum and maximum range
 *  that can be measured by the sensor. An example measurement unit is
 *  volts (ucum: A).
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Current_T;

/**  IPSO Current */
#define LWM2M_IPSO_Current LWM2M_OBJECT_ID( 3317 )

/**
 *  @brief IPSO Frequency
 * 
 *  This IPSO object should be used to report frequency measurements. It
 *  also provides resources for minimum and maximum measured values, as
 *  well as the minimum and maximum range that can be measured by the
 *  sensor. An example measurement unit is volts (ucum: Hz).
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Frequency_T;

/**  IPSO Frequency */
#define LWM2M_IPSO_Frequency LWM2M_OBJECT_ID( 3318 )

/**
 *  @brief IPSO Depth
 * 
 *  This IPSO object should be used to report depth measurements. It can,
 *  for example, be used to describe a generic rain gauge that measures
 *  the accumulated rainfall in millimetres (mm) or in fathoms (fth)
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Depth_T;

/**  IPSO Depth */
#define LWM2M_IPSO_Depth LWM2M_OBJECT_ID( 3319 )

/**
 *  @brief IPSO Percentage
 * 
 *  This IPSO object should can be used to report measurements relative to
 *  a 0-100% scale. For example it could be used to measure the level of a
 *  liquid in a vessel or container in units of %.
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Percentage_T;

/**  IPSO Percentage */
#define LWM2M_IPSO_Percentage LWM2M_OBJECT_ID( 3320 )

/**
 *  @brief IPSO Altitude
 * 
 *  This IPSO object should be used with an altitude sensor to report
 *  altitude above sea level in meters. Note that Altitude can be
 *  calculated from the measured pressure given the local sea level
 *  pressure. It also provides resources for minimum and maximum measured
 *  values, as well as the minimum and maximum range that can be measured
 *  by the sensor. An example measurement unit is meters (ucum: m).
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Altitude_T;

/**  IPSO Altitude */
#define LWM2M_IPSO_Altitude LWM2M_OBJECT_ID( 3321 )

/**
 *  @brief IPSO Load
 * 
 *  This IPSO object should be used with a load sensor (as in a scale) to
 *  report the applied weight or force. It also provides resources for
 *  minimum and maximum measured values, as well as the minimum and
 *  maximum range that can be measured by the sensor. An example
 *  measurement unit is kilograms (ucum: Kg).
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Load_T;

/**  IPSO Load */
#define LWM2M_IPSO_Load LWM2M_OBJECT_ID( 3322 )

/**
 *  @brief IPSO Pressure
 * 
 *  This IPSO object should be used to report pressure measurements. It
 *  also provides resources for minimum and maximum measured values, as
 *  well as the minimum and maximum range that can be measured by the
 *  sensor. An example measurement unit is pascals (ucum: Pa).
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Pressure_T;

/**  IPSO Pressure */
#define LWM2M_IPSO_Pressure LWM2M_OBJECT_ID( 3323 )

/**
 *  @brief IPSO Loudness
 * 
 *  This IPSO object should be used to report loudness or noise level
 *  measurements. It also provides resources for minimum and maximum
 *  measured values, as well as the minimum and maximum range that can be
 *  measured by the sensor. An example measurement unit is decibels (ucum:
 *  dB).
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Min Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5601, Min_Measured_Value );
    /**
     *  @brief Max Measured Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value measured by the sensor since power ON or reset
     */
    float LWM2M_RESOURCE( 5602, Max_Measured_Value );
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  Last or Current Measured Value from the Sensor
     */
    float LWM2M_RESOURCE( 5700, Sensor_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  If present, the type of sensor defined as the UCUM Unit Definition
     *  e.g. 'Cel' for Temperature in Celcius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
} LWM2M_IPSO_Loudness_T;

/**  IPSO Loudness */
#define LWM2M_IPSO_Loudness LWM2M_OBJECT_ID( 3324 )

/**
 *  @brief IPSO Gyrometer
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Description: This IPSO Object is used to report the current reading of
 *  a gyrometer sensor in 3 axes. It provides tracking of the minimum and
 *  maximum angular rate in all 3 axes. An example unit of measure is
 *  radians per second (ucum:rad/s).
 */
typedef struct
{
    /**
     *  @brief Min Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: float
     *  
     *  The minimum value that can be measured by the sensor.
     */
    float LWM2M_RESOURCE( 5603, Min_Range_Value );
    /**
     *  @brief Max Range Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: float
     *  
     *  The maximum value that can be measured by the sensor.
     */
    float LWM2M_RESOURCE( 5604, Max_Range_Value );
    /**
     *  @brief Sensor Units
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Type: string
     *  
     *  Measurement Units Definition e.g. Cel for Temperature in Celsius.
     */
    char * LWM2M_RESOURCE( 5701, Sensor_Units );
    /**
     *  @brief X Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the X axis.
     */
    float LWM2M_RESOURCE( 5702, X_Value );
    /**
     *  @brief Y Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the Y axis.
     */
    float LWM2M_RESOURCE( 5703, Y_Value );
    /**
     *  @brief Z Value
     * 
     *  Operations: read
     *  
     *  Mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The measured value along the Z axis.
     */
    float LWM2M_RESOURCE( 5704, Z_Value );
    /**
     *  @brief Min X Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum measured value along the X axis.
     */
    float LWM2M_RESOURCE( 5708, Min_X_Value );
    /**
     *  @brief Max X Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum measured value along the X axis.
     */
    float LWM2M_RESOURCE( 5709, Max_X_Value );
    /**
     *  @brief Min Y Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum measured value along the Y axis.
     */
    float LWM2M_RESOURCE( 5710, Min_Y_Value );
    /**
     *  @brief Max Y Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum measured value along the Y axis.
     */
    float LWM2M_RESOURCE( 5711, Max_Y_Value );
    /**
     *  @brief Min Z Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The minimum measured value along the Z axis.
     */
    float LWM2M_RESOURCE( 5712, Min_Z_Value );
    /**
     *  @brief Max Z Value
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Instance type: single
     *  
     *  Units: defined by 'units' resource.
     *  
     *  Type: float
     *  
     *  The maximum measured value along the Z axis.
     */
    float LWM2M_RESOURCE( 5713, Max_Z_Value );
} LWM2M_IPSO_Gyrometer_T;

/**  IPSO Gyrometer */
#define LWM2M_IPSO_Gyrometer LWM2M_OBJECT_ID( 3334 )

/**
 *  @brief IPSO Addressable Text Display
 * 
 *  This IPSO object is used to send text to a text-only or text mode
 *  graphics display. POSTing a string of text to the text resource causes
 *  it to be displayed at the selected X and Y locations on the display.
 *  If X or Y are set to a value greater than the size of the display, the
 *  position wraps around to the modulus of the setting and the display
 *  size. Likewise, if the text string overflows the display size, the
 *  text wraps around and displays on the next line down or, if the last
 *  line has been written, wraps around to the top of the display.
 *  Brightness and Contrast controls are provided to allow control of
 *  various display types including STN and DSTN type LCD character
 *  displays. POSTing an empty payload to the Clear Display resource
 *  causes the display to be erased.
 *  
 *  Instance type: multiple
 */
typedef struct
{
    /**
     *  @brief Text
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  A string of text
     *  
     *  Type: string
     */
    char * LWM2M_RESOURCE( 5527, Text );
} LWM2M_IPSO_Loudness_T;

/**  IPSO Addressable Text Display */
#define LWM2M_IPSO_Loudness LWM2M_OBJECT_ID( 3324 )

/**
 *  @brief OpenIO Camera Interface
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Provides an interface for OpenIO devices to send still images to the
 *  server
 */
typedef struct
{
    /**
     *  @brief Upload URL
     * 
     *  Operations: write
     *  
     *  Mandatory
     *  
     *  Type: string
     *  
     *  Instance type: single
     *  
     *  The image upload URL. The client will submit images to this URL via
     *  HTTP POST. The URL would normally contain a unique identifier for the
     *  device. Example: /uploadImage/1e76775d642bcd2081c4ca197e3d0d05
     */
    char * LWM2M_RESOURCE( 0, Upload_URL );
    /**
     *  @brief Image object
     * 
     *  Operations: read
     *  
     *  Not mandatory
     *  
     *  Type: string
     *  
     *  Instance type: single
     *  
     *  A virtual resource which is used to refer to uploaded images. The
     *  presence of this resource allows capture sessions to tag images.
     */
    char * LWM2M_RESOURCE( 1, Image_object );
} LWM2M_OpenIO_Camera_Interface_T;

/**  OpenIO Camera Interface */
#define LWM2M_OpenIO_Camera_Interface LWM2M_OBJECT_ID( 7011 )

/**
 *  @brief OpenIO I2C Interface
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Provides an interface for OpenIO devices to present I2C-connected
 *  objects
 */
typedef struct
{
    /**
     *  @brief Object Type
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Type: integer
     *  
     *  Instance type: single
     *  
     *  The object type which is connected to the I2C interface. If 0, nothing
     *  is connected.
     */
    int LWM2M_RESOURCE( 0, Object_Type );
} LWM2M_OpenIO_I2C_Interface_T;

/**  OpenIO I2C Interface */
#define LWM2M_OpenIO_I2C_Interface LWM2M_OBJECT_ID( 7012 )

/**
 *  @brief OpenIO SPI Interface
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Provides an interface for OpenIO devices to present SPI-connected
 *  objects
 */
typedef struct
{
    /**
     *  @brief Object Type
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Type: integer
     *  
     *  Instance type: single
     *  
     *  The object type which is connected to the SPI interface. If 0, nothing
     *  is connected.
     */
    int LWM2M_RESOURCE( 0, Object_Type );
} LWM2M_OpenIO_SPI_Interface_T;

/**  OpenIO SPI Interface */
#define LWM2M_OpenIO_SPI_Interface LWM2M_OBJECT_ID( 7013 )

/**
 *  @brief OpenIO UART Interface
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Provides an interface for OpenIO devices to present UART-connected
 *  objects
 */
typedef struct
{
    /**
     *  @brief Object Type
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Type: integer
     *  
     *  Instance type: single
     *  
     *  The object type which is connected to the UART interface. If 0,
     *  nothing is connected.
     */
    int LWM2M_RESOURCE( 0, Object_Type );
} LWM2M_OpenIO_UART_Interface_T;

/**  OpenIO UART Interface */
#define LWM2M_OpenIO_UART_Interface LWM2M_OBJECT_ID( 7014 )

/**
 *  @brief OpenIO Surface Plotter
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Provides an interface for OpenIO devices to send 3D data to the server
 */
typedef struct
{
    /**
     *  @brief Upload URL
     * 
     *  Operations: write
     *  
     *  Mandatory
     *  
     *  Type: string
     *  
     *  Instance type: single
     *  
     *  The data upload URL. The client will submit JSON encoded data to this
     *  URL.
     */
    char * LWM2M_RESOURCE( 0, Upload_URL );
    /**
     *  @brief Surface data
     * 
     *  Operations: write
     *  
     *  Used internally by the UI to represent captured surface data. Not used
     *  by LWM2M.
     *  
     *  Type: string
     *  
     *  Instance type: single
     */
    char * LWM2M_RESOURCE( 1, Surface_data );
} LWM2M_OpenIO_Surface_Plotter_T;

/**  OpenIO Surface Plotter */
#define LWM2M_OpenIO_Surface_Plotter LWM2M_OBJECT_ID( 7015 )

/**
 *  @brief OpenIO Motor Control
 * 
 *  Not mandatory
 *  
 *  Instance type: multiple
 *  
 *  Actuator object to control a motor
 */
typedef struct
{
    /**
     *  @brief Velocity
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Type: integer
     *  
     *  Instance type: single
     *  
     *  Motor velocity
     */
    int LWM2M_RESOURCE( 0, Velocity );
    /**
     *  @brief State
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Type: boolean
     *  
     *  Instance type: single
     *  
     *  Motor state (on/off)
     */
    int LWM2M_RESOURCE( 1, State );
    /**
     *  @brief Direction
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Type: boolean
     *  
     *  Instance type: single
     *  
     *  Direction (true == clockwise)
     */
    int LWM2M_RESOURCE( 2, Direction );
} LWM2M_OpenIO_Motor_Control_T;

/**  OpenIO Motor Control */
#define LWM2M_OpenIO_Motor_Control LWM2M_OBJECT_ID( 7017 )

/**
 *  @brief OpenIO Client-pushed text object
 * 
 *  Mandatory
 *  
 *  Instance type: single
 *  
 *  Allows the client to push text objects to the server, and optionally,
 *  to the UI
 */
typedef struct
{
    /**
     *  @brief Object
     * 
     *  Operations: read, write
     *  
     *  Mandatory
     *  
     *  Type: string
     *  
     *  Instance type: single
     *  
     *  A JSON-blob, with the following parameters: {objectName: "A name for
     *  the object", objectID: "Only used when OVERWRITING an existing object,
     *  see resource 1.", objectText: "The content", tags:
     *  ["a","list","of","tags"], pushToUI: true}
     */
    char * LWM2M_RESOURCE( 0, Object );
    /**
     *  @brief ObjectID
     * 
     *  Operations: write
     *  
     *  Not mandatory
     *  
     *  Type: string
     *  
     *  Instance type: single
     *  
     *  This is the text object ID which is written back immediately after the
     *  client pushes a text object. This allows the client to overwrite a
     *  text object if necessary.
     */
    char * LWM2M_RESOURCE( 1, ObjectID );
} LWM2M_OpenIO_Clientpushed_text_object_T;

/**  OpenIO Client-pushed text object */
#define LWM2M_OpenIO_Clientpushed_text_object LWM2M_OBJECT_ID( 7019 )

#endif
