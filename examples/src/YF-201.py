#!/usr/bin/env python

import gpio
import time

FLOW_SENSOR = "23"

flow_sensor = gpio.device(FLOW_SENSOR)
flow_sensor.set_direction(gpio.IN)

global count
count = 0

def countPulse(channel):
   global count
   count = count+1
   print count

flow_sensor.set_callback(gpio.FALLING, countPulse)

while True:
    try:
        time.sleep(1)
    except KeyboardInterrupt:
        print '\ncaught keyboard interrupt!, bye'
        del flow_sensor

