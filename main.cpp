#include "mbed.h"
#include "mbed_bme680.h"

#if TARGET_NUMAKER_IOT_M263A
I2C sensor_i2c(PD_4, PD_5);
#else
I2C sensor_i2c(I2C_SDA, I2C_SCL);  // Used inside the BME680 Mbed Lib.
#endif

BME680 bme680(0x76 << 1);

int main()
{
    int count = 10;
    
    if (!bme680.begin()) {
        printf("BME680 Begin failed \r\n");
        return 1;
    }

    while (true) {
        if (++count >= 10)
        {
            count = 0;
            printf("\r\nTemperature  Humidity  Pressure    VOC\r\n"
                   "    degC        %%        hPa      KOhms\r\n"
                   "------------------------------------------\r\n");
        }

        if (bme680.performReading())
        {
            printf("   %.2f      ", bme680.getTemperature());
            printf("%.2f    ", bme680.getHumidity());
            printf("%.2f    ", bme680.getPressure() / 100.0);
            printf("%0.2f\r\n", bme680.getGasResistance() / 1000.0);
        }

        thread_sleep_for(1000);
    }
}