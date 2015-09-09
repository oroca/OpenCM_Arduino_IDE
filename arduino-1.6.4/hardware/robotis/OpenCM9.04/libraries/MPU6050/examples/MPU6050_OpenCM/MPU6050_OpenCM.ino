/* MPU6050.ino
 *  Modified by SteamMaker and Baram 
 *   2015. 08. 23
 *  www.steammaker.co.kr
 */

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;



// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

//#define LED_PIN 13

bool blinkState = false;

void setup() 
{
    Wire.begin(); // Wire.begin(SDA 20, SDL 21)

    SerialUSB.begin();

    // initialize device
    SerialUSB.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    SerialUSB.println("Testing device connections...");
    SerialUSB.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // use the code below to change accel/gyro offset values
    /*
    SerialUSB.println("Updating internal sensor offsets...");
    // -76	-2359	1688	0	0	0
    SerialUSB.print(accelgyro.getXAccelOffset()); SerialUSB.print("\t"); // -76
    SerialUSB.print(accelgyro.getYAccelOffset()); SerialUSB.print("\t"); // -2359
    SerialUSB.print(accelgyro.getZAccelOffset()); SerialUSB.print("\t"); // 1688
    SerialUSB.print(accelgyro.getXGyroOffset()); SerialUSB.print("\t"); // 0
    SerialUSB.print(accelgyro.getYGyroOffset()); SerialUSB.print("\t"); // 0
    SerialUSB.print(accelgyro.getZGyroOffset()); SerialUSB.print("\t"); // 0
    SerialUSB.print("\n");
    accelgyro.setXGyroOffset(220);
    accelgyro.setYGyroOffset(76);
    accelgyro.setZGyroOffset(-85);
    SerialUSB.print(accelgyro.getXAccelOffset()); SerialUSB.print("\t"); // -76
    SerialUSB.print(accelgyro.getYAccelOffset()); SerialUSB.print("\t"); // -2359
    SerialUSB.print(accelgyro.getZAccelOffset()); SerialUSB.print("\t"); // 1688
    SerialUSB.print(accelgyro.getXGyroOffset()); SerialUSB.print("\t"); // 0
    SerialUSB.print(accelgyro.getYGyroOffset()); SerialUSB.print("\t"); // 0
    SerialUSB.print(accelgyro.getZGyroOffset()); SerialUSB.print("\t"); // 0
    SerialUSB.print("\n");
    */

    // configure Arduino LED for
    pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        SerialUSB.print("a/g:\t");
        SerialUSB.print(ax/100); SerialUSB.print("\t");
        SerialUSB.print(ay/100); SerialUSB.print("\t");
        SerialUSB.print(az/100); SerialUSB.print("\t");
        SerialUSB.print(gx); SerialUSB.print("\t");
        SerialUSB.print(gy); SerialUSB.print("\t");
        SerialUSB.println(gz);
    #endif

    #ifdef OUTPUT_BINARY_ACCELGYRO
        SerialUSB.write((uint8_t)(ax >> 8)); SerialUSB.write((uint8_t)(ax & 0xFF));
        SerialUSB.write((uint8_t)(ay >> 8)); SerialUSB.write((uint8_t)(ay & 0xFF));
        SerialUSB.write((uint8_t)(az >> 8)); SerialUSB.write((uint8_t)(az & 0xFF));
        SerialUSB.write((uint8_t)(gx >> 8)); SerialUSB.write((uint8_t)(gx & 0xFF));
        SerialUSB.write((uint8_t)(gy >> 8)); SerialUSB.write((uint8_t)(gy & 0xFF));
        SerialUSB.write((uint8_t)(gz >> 8)); SerialUSB.write((uint8_t)(gz & 0xFF));
    #endif

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(BOARD_LED_PIN, blinkState);
}

