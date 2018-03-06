#
# SICM Client Script API
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

##
#  @file
#  @brief SICM FPGA API header
#  @addtogroup sicm-api-fpga
#
#  The SICM FPGA API provides functions for setting and getting the SICM FPGA
#  registers. The FPGA provides control of the instrument piezo motors and
#  detection head.
#
#

## @cond INTERNAL 

_FPGA_Config_NC                 = 0
_FPGA_Config_Manual_Zp          = 1
_FPGA_Config_Manual_Zs          = 2
_FPGA_Config_Manual_Xs          = 3
_FPGA_Config_Manual_Ys          = 4
_FPGA_Config_Ion_Amplifier      = 5
_FPGA_Config_Z_Control_Mode     = 6
_FPGA_Config_Ion_Current_Out    = 7
_FPGA_Config_Z_Sense            = 8
_FPGA_Config_Hop_Samples_Eol    = 9
_FPGA_Config_Hop_Samples        = 10
_FPGA_Config_Rise_Increment     = 11
_FPGA_Config_Fall_Increment     = 12
_FPGA_Config_Measure_Samples    = 13
_FPGA_Config_Threshold          = 14
_FPGA_Config_ZP_Min             = 15
_FPGA_Config_ZP_Max             = 16
_FPGA_Config_Ion_Filter         = 17
_FPGA_Config_Eol_Repeat_Count   = 18
_FPGA_Config_XY_Samples         = 19
_FPGA_Config_V_BIAS             = 20
_FPGA_Config_Scan_Index         = 21
_FPGA_Config_Xs                 = 22
_FPGA_Config_Ys                 = 23
_FPGA_Long_Jump_Indicator       = 24
_FPGA_Status_NC                 = 96
_FPGA_Status_Z_State            = 97
_FPGA_Status_IO_Error_Counter   = 98
_FPGA_Control_NC                = 128
_FPGA_Reset_All                 = 129
_FPGA_Start                     = 130
_FPGA_Stop                      = 131
_FPGA_Pause                     = 132
_FPGA_ConfigDone                = 133
_FPGA_Reconfig                  = 134
_FPGA_DATA_NC                   = 192
_FPGA_DATA_ReportType1          = 193
_FPGA_Measured_Xs               = 194
_FPGA_Measured_Ys               = 195
_FPGA_Measured_Zs               = 196
_FPGA_Measured_Zp               = 197
_FPGA_Measured_Imean            = 198
_FPGA_Measured_Aux1in           = 199
_FPGA_Measured_Aux2in           = 200

def _SICM_FPGA_SetFloatRegister(r, v):      
    ___Send(request="SICM_FPGA_SetFloatRegister", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(r), float_payload=___ISeq(v))
    l = ___Receive()
    assert l[0]=="APIResult" 
    return l[1]
      
def _SICM_FPGA_GetFloatRegister(r):      
    ___Send(request="SICM_FPGA_GetFloatRegister", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(r), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="APIResult" 
    return l[2]
      
def _SICM_FPGA_SetIntegerRegister(r, v):      
    ___Send(request="SICM_FPGA_SetIntegerRegister", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(r, v), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="APIResult" 
    return l[1]
      
def _SICM_FPGA_GetIntegerRegister(r):      
    ___Send(request="SICM_FPGA_GetIntegerRegister", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(r), float_payload=___ISeq())
    l = ___Receive()
    assert l[0]=="APIResult" 
    return l[2]
      
## @endcond 

## Z axis states enumeration 
Undefined   = 0
NotImmersed = 1
Immersing   = 2
Retracting  = 3
Immersed    = 4
Approaching = 5
Withdrawing = 6
InControl   = 7

## Amplifier type enumeration     
Internal            = 0
External            = 1

## Scan head type enumeration      
ICNanoS2            = 0
ICNano2043          = 1
ICNano2223          = 2
ICNano2243          = 3
Manual              = 4

## Measurement mode enumeration 
UniDirectionalHopping   = 0
BiDirectionalHopping    = 1

## Z Sense invert mode enumeration 
ZSenseInvert_Normal     = 0
ZSenseInvert_Inverted   = 1

##
#  @brief Set Manual Zp register
#
#  @param manualZp New Manual Zp value
#  @return true on success, false on failure
#
def FPGA_SetManualZp(manualZp):
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Manual_Zp, manualZp)
      
##
#  @brief Get Manual Zp register
#
#  @param manualZp Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetManualZp():
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Manual_Zp, manualZp)
      
##
#  @brief Set Manual Zs register
#
#  @param manualZs New Manual Zs value
#  @return true on success, false on failure
#
def FPGA_SetManualZs(manualZs):
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Manual_Zs, manualZs)
      
##
#  @brief Get Manual Zs register
#
#  @param manualZs Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetManualZs():
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Manual_Zs, manualZs)
      
##
#  @brief Set Manual Xs register
#
#  @param manualXs New Manual Xs value
#  @return true on success, false on failure
#
def FPGA_SetManualXs(manualXs):
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Manual_Xs, manualXs)
      
##
#  @brief Get Manual Xs register
#
#  @param manualXs Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetManualXs():
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Manual_Xs, manualXs)
      
##
#  @brief Set Manual Ys register
#
#  @param manualYs New Manual Ys value
#  @return true on success, false on failure
#
def FPGA_SetManualYs(manualYs):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Manual_Ys, manualYs)
      
##
#  @brief Get Manual Ys register
#
#  @param manualYs Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetManualYs():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Manual_Ys, manualYs)
      
##
#  @brief Set Ion Current Out register
#
#  @param manualYs New Ion Current Out value
#  @return true on success, false on failure
#
def FPGA_SetIonCurrentOut(ionCurrentOut):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Ion_Current_Out, ionCurrentOut)
      
##
#  @brief Get Ion Current Out register
#
#  @param ionCurrentOut Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetIonCurrentOut():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Ion_Current_Out, ionCurrentOut)
      
##
#  @brief Set Rise Increment register
#
#  @param riseIncrement New Rise Increment value
#  @return true on success, false on failure
#
def FPGA_SetRiseIncrement(riseIncrement):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Rise_Increment, riseIncrement)
      
##
#  @brief Get Rise Increment register
#
#  @param riseIncrement Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetRiseIncrement():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Rise_Increment, riseIncrement)
      
##
#  @brief Set Fall Increment register
#
#  @param fallIncrement New Fall Increment value
#  @return true on success, false on failure
#
def FPGA_SetFallIncrement(fallIncrement):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Fall_Increment, fallIncrement)
      
##
#  @brief Get Fall Increment register
#
#  @param fallIncrement Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetFallIncrement():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Fall_Increment, fallIncrement)
      
##
#  @brief Set Threshold register
#
#  @param threshold New Threshold value
#  @return true on success, false on failure
#
def FPGA_SetThreshold(threshold):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Threshold, threshold)
      
##
#  @brief Get Threshold register
#
#  @param threshold Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetThreshold():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Threshold, threshold)
      
##
#  @brief Set Zp Min register
#
#  @param zpMin Value to set
#  @return true on success, false on failure
#
def FPGA_SetZpMin(zpMin):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_ZP_Min, zpMin)
      
##
#  @brief Get Zp Min register
#
#  @param zpMin Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetZpMin():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_ZP_Min, zpMin)
      
##
#  @brief Set Zp Max register
#
#  @param zpMax Value to set
#  @return true on success, false on failure
#
def FPGA_SetZpMax(zpMax):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_ZP_Max, zpMax)
      
##
#  @brief Get Zp Max register
#
#  @param zpMax Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetZpMax():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_ZP_Max, zpMax)
      
##
#  @brief Set V Bias register
#
#  @param VBias Value to set
#  @return true on success, false on failure
#
def FPGA_SetVbias(VBias):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_V_BIAS, VBias)
      
##
#  @brief Get V Bias register
#
#  @param VBias Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetVbias():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_V_BIAS, VBias)
      
##
#  @brief Set Xs register
#
#  @param xs Value to set
#  @return true on success, false on failure
#
def FPGA_SetXs(xs):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Xs, xs)
      
##
#  @brief Get Xs register
#
#  @param xs Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetXs():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Xs, xs)
      
##
#  @brief Set Ys register
#
#  @param ys Value to set
#  @return true on success, false on failure
#
def FPGA_SetYs(ys):      
    return _SICM_FPGA_SetFloatRegister(_FPGA_Config_Ys, ys)
      
##
#  @brief Get Ys register
#
#  @param ys Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetYs():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Config_Ys, ys)
      
##
#  @brief Set Re-Config register
#
#  @param reconfig Value to set
#  @return true on success, false on failure
#
def FPGA_SetReConfig(reconfig):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Reconfig, reconfig)
      
##
#  @brief Get Re-config register
#
#  @param reconfig Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetReConfig():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Reconfig, reconfig)
      
##
#  @brief Set Config Done register
#
#  @param configDone Value to set
#  @return true on success, false on failure
#
def FPGA_SetConfigDone(configDone):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_ConfigDone, configDone)
      
##
#  @brief Get Config Done register
#
#  @param configDone Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetConfigDone():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_ConfigDone, configDone)
      
##
#  @brief Set Start Scan register
#
#  @param startScan Value to set
#  @return true on success, false on failure
#
def FPGA_SetStartScan(startScan):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Start, startScan)
      
##
#  @brief Get Start Scan register
#
#  @param startScan Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetStartScan():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Start, startScan)
      
##
#  @brief Set Stop Scan register
#
#  @param stopScan Value to set
#  @return true on success, false on failure
#
def FPGA_SetStopScan(stopScan):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Stop, stopScan)
      
##
#  @brief Get Stop Scan register
#
#  @param stopScan Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetStopScan():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Stop, stopScan)
      
##
#  @brief Set Reset All register
#
#  @param resetAll Value to set
#  @return true on success, false on failure
#
def FPGA_SetResetAll(resetAll):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Reset_All, resetAll)
      
##
#  @brief Get Reset All register
#
#  @param resetAll Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetResetAll():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Reset_All, resetAll)
      
##
#  @brief Set Long Jump Indicator register
#
#  @param longJumpInd Value to set
#  @return true on success, false on failure
#
def FPGA_SetLongJumpIndicator(longJumpInd):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Long_Jump_Indicator, longJumpInd)
      
##
#  @brief Get Long Jump Indicator register
#
#  @param longJumpInd Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetLongJumpIndicator():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Long_Jump_Indicator, longJumpInd)
      
##
#  @brief Set Ion Amplifier register
#
#  @param ionAmplifier Value to set
#  @return true on success, false on failure
#
def FPGA_SetIonAmplifier(ionAmplifier):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_Ion_Amplifier, ionAmplifier)
      
##
#  @brief Get Ion Amplifier register
#
#  @param ionAmplifier Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetIonAmplifier():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_Ion_Amplifier, ionAmplifier)
      
##
#  @brief Set Z Control Mode register
#
#  @param zControlMode Value to set
#  @return true on success, false on failure
#
def FPGA_SetZControlMode(zControlMode):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_Z_Control_Mode, zControlMode)
      
##
#  @brief Get Z Control Mode register
#
#  @param zControlMode Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetZControlMode():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_Z_Control_Mode, zControlMode)
      
##
#  @brief Set Z Sense register
#
#  @param ZSense Value to set
#  @return true on success, false on failure
#
def FPGA_SetZSense(ZSense):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_Z_Sense, ZSense)
      
##
#  @brief Get Z Sense register
#
#  @param ZSense Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetZSense():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_Z_Sense, ZSense)
      
##
#  @brief Set Hop Samples EOL register
#
#  @param hopSamplesEol Value to set
#  @return true on success, false on failure
#
def FPGA_SetHopSamplesEol(hopSamplesEol):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_Hop_Samples_Eol, hopSamplesEol)
      
##
#  @brief Get Hop Samples EOL register
#
#  @param hopSamplesEol Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetHopSamplesEol():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_Hop_Samples_Eol, hopSamplesEol)
      
##
#  @brief Set Hop Samples register
#
#  @param hopSamples Value to set
#  @return true on success, false on failure
#
def FPGA_SetHopSamples(hopSamples):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_Hop_Samples, hopSamples)
      
##
#  @brief Get Hop Samples register
#
#  @param hopSamples Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetHopSamples():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_Hop_Samples, hopSamples)
      
##
#  @brief Set Measure Samples register
#
#  @param measureSamples Value to set
#  @return true on success, false on failure
#
def FPGA_SetMeasureSamples(measureSamples):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_Measure_Samples, measureSamples)
      
##
#  @brief Get Measure Samples register
#
#  @param measureSamples Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetMeasureSamples():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_Measure_Samples, measureSamples)
      
##
#  @brief Set Ion Filter register
#
#  @param ionFilter Value to set
#  @return true on success, false on failure
#
def FPGA_SetIonFilter(ionFilter):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_Ion_Filter, ionFilter)
      
##
#  @brief Get Ion Filter All register
#
#  @param resetAll Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetIonFilter():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_Ion_Filter, ionFilter)
      
##
#  @brief Set EOL Repeat Count register
#
#  @param eolRepeatCount Value to set
#  @return true on success, false on failure
#
def FPGA_SetEolRepeatCount(eolRepeatCount):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_Eol_Repeat_Count, eolRepeatCount)
      
##
#  @brief Get EOL Repeat Count register
#
#  @param eolRepeatCount Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetEolRepeatCount():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_Eol_Repeat_Count, eolRepeatCount)
      
##
#  @brief Set X/Y Samples register
#
#  @param xySamples Value to set
#  @return true on success, false on failure
#
def FPGA_SetXYSamples(xySamples):      
    return _SICM_FPGA_SetIntegerRegister(_FPGA_Config_XY_Samples, xySamples)
      
##
#  @brief Get X/Y Samples register
#
#  @param xySamples Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetXySamples():      
    return _SICM_FPGA_GetIntegerRegister(_FPGA_Config_XY_Samples, xySamples)
      
##
#  @brief Get Measured Xs register
#
#  @param measured_xs Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetMeasured_Xs():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Measured_Xs, measured_xs)
      
##
#  @brief Get Measured Ys register
#
#  @param measured_ys Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetMeasured_Ys():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Measured_Ys, measured_ys)
      
##
#  @brief Get Measured Zp register
#
#  @param measured_zp Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetMeasured_Zp():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Measured_Zp, measured_zp)
      
##
#  @brief Get Measured I Mean register
#
#  @param imean Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetMeasured_iMean():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Measured_Imean, imean)
      
##
#  @brief Get Measured Aux 1 In register
#
#  @param measured_aux1in Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetMeasured_Aux1in():      
    return _SICM_FPGA_GetFloatRegister(_FPGA_Measured_Aux1in, measured_aux1in)
      
##
#  @brief Get Measured Aux 2 In register
#
#  @param measured_aux2in Pointer into which to get value
#  @return true on success, false on failure
#
def FPGA_GetMeasured_Aux2in():
    return _SICM_FPGA_GetFloatRegister(_FPGA_Measured_Aux2in, measured_aux2in)
      