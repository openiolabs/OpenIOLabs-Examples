#include <lwm2m.h> // lwm2m.h is auto-generated

#define TRACE_I2C_REGMAP
#include <scriptml/i2c.h>
#include <scriptml/gpio.h>
#include <scriptml/lm75b.h>

#include <stdint.h>
#include <unistd.h>

#define RED_LED_GPIO_NUM "17"
#define GREEN_LED_GPIO_NUM "19"

LWM2M_IPSO_Light_Control_T LWM2M_IPSO_Light_Control[2]; // Declare an array of two LWM2M object as a ScriptML variable

int main()
{    
    /* Create the hardware devices for the LEDs */
    sml_gpio_handle_t red_led_pin = sml_gpio_open( RED_LED_GPIO_NUM ); // GPIO that the LED is wired to    
    sml_gpio_handle_t green_led_pin = sml_gpio_open( GREEN_LED_GPIO_NUM ); // GPIO that the LED is wired to    
    sml_gpio_set_direction( red_led_pin, SML_GPIO_OUT );
    sml_gpio_set_direction( green_led_pin, SML_GPIO_OUT );

    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Light_Control);

    /* Continually read the device and update the LEDs */
    while(1)
    {
        sml_gpio_set_level( red_led_pin, LWM2M_IPSO_Light_Control[0].OnOff );
        sml_gpio_set_level( green_led_pin, LWM2M_IPSO_Light_Control[1].OnOff );
        usleep(100000);
    }

    return 0;
}
