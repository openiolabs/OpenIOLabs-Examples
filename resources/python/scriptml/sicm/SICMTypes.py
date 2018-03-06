#
# SICM Client
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

##
#  @file
#  @brief SICM application type definitions
#
# @{
#

## Sampling rate (samples per millisecond) 
SICM_SAMPLING_RATE = 50

## What to do with read back data from FPGA 
RA_NONE=0          # no action
RA_START=1         # start a new report
RA_SAMPLE=2        # add data to the report (average of current as well as previously accumulated)
RA_SUB_SAMPLE=3    # accumulate data for averaging calc, but don't report
RA_COMPLETE=4      # end the report

## Scanning mode enumeration (matches server) 
HOPPING_SCAN_MODE   = 0
APPROACH_CURVE_MODE = 1
MANUAL_MODE         = 2
 
## Z Control mode enumeration (matches FPGA) 
ZCONTROL_HOPPING_MODE              = 1
ZCONTROL_MANUAL_MODE               = 2
ZCONTROL_ALTERNATING_CURRENT_MODE  = 3 # Not approach curve!!!!!!!!!!1
ZCONTROL_FAST_HOPPING              = 4
ZCONTROL_SICM_SEC_MODE             = 5

## Measurement states enumeration 
HS_STOPPED              = 0
HS_STARTING             = 1
HS_START_REQUESTED      = 2
HS_MEASURING            = 3
HS_COMPLETE             = 4

## Manual mode states enumeration 
M_STOPPED               = 0
M_START_REQUESTED       = 1
M_TO_SAFE_HEIGHT        = 2
M_TO_XY_POSITION        = 3
M_UP_DOWN_CONTROL       = 4

## Approach curve mode states enumeration 
AC_STOPPED             = 0
AC_START_REQUESTED     = 1
AC_TO_SAFE_HEIGHT      = 2
AC_TO_XY_POSITION      = 3
AC_APPROACH_DOWN       = 4
AC_APPROACH_UP         = 5
AC_COMPLETE            = 6


class Range:
    def __init__():
        min = 0.0
        max = 0.0
        
class FPGALimits:
    def __init__():
        volts = Range()
        microns = Range()
        

# SICM instrument status 
class SICMStatus:
    def __init__():    
        self.acceptedScanMode = HOPPING_SCAN_MODE          ##< SICM scan mode (used by system) 

        self.xPos = 0.0                       ##< X position 
        self.yPos = 0.0                         ##< Y position 

        self.scanIndex = 0                  ##< Used during a scan to count the number of points scanned 

        self.hoppingState = HS_STOPPED         ##< Hopping scan mode state 

        self.manualState = M_STOPPED           ##< Manual mode state 
        self.manualStep = 0                ##< Manual mode step number 

        self.approachCurveState = AC_STOPPED      ##< APPROACH curve mode state 
        self.ZOfs = 0.0;
        self.stateCounter = 0;


## SICM instrument configuration 
class SICMConfig:
    def __init__():
        self.scanMode = HOPPING_SCAN_MODE                 ##< SICM scan mode (at UI) 
        
        #  Pipette Bias
        self.vBias = 0.0                  ##< Pipette bias voltage 
        self.vOffset = 0.0                ##< Pipette offset voltage 
        
        #  Positioning Settings
        self.zApproachSpeed = 0             ##< Speed of pipette while approaching 
        self.zImmerseSpeed = 0              ##< Speed of pipette immersion 
        self.xySpeed = 0                    ##< Speed at which X/Y coarse motors will move 
        self.zWithdrawSpeed = 0             ##< Speed of pippette when withdrawing 
        self.immerseThreshold = 0.0             ##< Immersion detection threshold 
        self.immerseDepth = 0.0                  ##< Immersion depth 
        self.zPiezoStopCriteria = 0.0            ##< ZP piezo stop criteria 
        self.coarseMotorsStopCriteria = 0.0       ##< Coarse Motors stop criteria 
        self.joystickEnable = False               ##< Joystick positioning enabled when true 

        #  Hopping Parameters
        self.hopHeight = 0                 ##< Minimum hop height 
        self.detectThreshold = 0           ##< Detection threshold 
        self.fallRate = 0                  ##< Fall rate 
        self.riseRate = 0                  ##< Rise rate 
        self.xyDelay = 0.0                      ##< Pre-measurement pause 
        self.measureDelay = 0              ##< Ion current measurement time 
        self.zBrakeOffset = 0.0                 ##< Z brake retract 
        self.zHoppingLimits = Range()             ##< Z hopping distance limits 
        self.xIdlePos = 0.0                     ##< Idling X position 
        self.yIdlePos = 0.0                     ##< Idling Y position 

        #  Scan Area
        self.xOrigin = 0.0                       ##< Scan X origin 
        self.yOrigin = 0.0                       ##< Scan Y origin 
        self.scanWidth = 0.0                     ##< Scan area width 
        self.scanHeight = 0.0                    ##< Scan area height 
        self.widthPix = 0                   ##< Number of X measurement points 
        self.heightPix = 0                  ##< Number of Y measurement points 
        self.scanAngle = 0.0                     ##< Scan angle 
        self.pipetteLengthFactor = 0.0           ##< Pipette length ratio 

        # Manual Control Parameters 
        self.manualXPos = 0.0                    ##< Manual mode X position 
        self.manualYPos = 0.0                    ##< Manual mode Y position 
        self.manualZInit = 0.0                   ##< Manual mode start height 
        self.manualZOfs = 0.0                    ##< Manual mode Z height 
        self.manualZInc = 0.0                    ##< Manual mode Z step size 
        self.manualZRef = 0.0                    ##< Manual mode Zp-reference 
        self.manualActive = True                 ##< Enable manual mode 

        # APPROACH Curve Control Parameters 
        self.approachIMin = 0.0 
        self.approachZMin = 0.0 
        self.approachSamples = 0

        self.hasChanged = False                ##< Set true after a config change 

## @}
