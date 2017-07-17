import gpio
import time

LED_0 = "17"

led = gpio.device(LED_0)
led.set_direction(gpio.OUT)

def blink(x):
    x.set_level(1)
    print ('on')
    time.sleep(1)
    x.set_level(0)
    print ('off')
    time.sleep(2)
    print ('count')
    return

for i in range(0,50):
    blink(led)
    print (i)


print ('all done')
del led







