#include "mbed.h"
#include "mbed_bme680.h"

using namespace mbed_nuvoton;

#if TARGET_NUMAKER_IOT_M263A
BME680 bme680(PD_4, PD_5, 0x76 << 1);
#else
BME680 bme680(I2C_SDA, I2C_SCL, 0x76 << 1);
#endif

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

        ThisThread::sleep_for(1000ms);
    }
}