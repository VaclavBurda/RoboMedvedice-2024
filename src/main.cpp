// #include "BluetoothSerial.h"
//#include "WiFi.h"

/*

void setup() {
    rkConfig cfg;
    //cfg.owner = "vasek"; // Ujistěte se, že v aplikace RBController máte nastavené stejné
    //cfg.name = "SokolSus";
    cfg.motor_max_power_pct = 100; // limit výkonu motorů na xx %

    cfg.motor_enable_failsafe = false;
    cfg.rbcontroller_app_enable = false; // nepoužívám mobilní aplikaci (lze ji vypnout - kód se zrychlí, ale nelze ji odstranit z kódu -> kód se nezmenší)
    rkSetup(cfg);

rkPinsConfig

    Serial.begin(115200);  // COM port 25 pocitac Burda

    //printf("Zapnute DUP:%d\n", udp.begin(88));

    //int count = 0;

}

int main() {
    int levy_m = 30;
    int pravy_m = 30;

    rkMotorsSetPower(levy_m, pravy_m);

    rkMotorsSetSpeed(levy_m, pravy_m);

    delay(10000);
}
*/

#include "BluetoothSerial.h"
#include "WiFi.h"
#include "robotka.h"
#include <thread>
#include "SmartServoBus.hpp"
#include "arm_commands.h"

#define DELAY 50
#define DELAY_BLINK 250
#define LED_COUNT 8

constexpr std::size_t bufferSize = 64;

constexpr size_t axisOpCode = 0x80;
constexpr size_t axisCount = 5;
// cislo os je o dve vyssi, nez pise Lorris, protoze prvni byte je hlavicka a druhy je pocet os a az potom jsou hodnoty os
constexpr size_t xAxisPosition = 2; // pravy nahoru dolu
constexpr size_t yAxisPosition = 4; // levy doprava doleva

constexpr size_t armAxisPosition = 5;

constexpr size_t buttonOpCode = 0x81;
constexpr size_t buttonCount = 14;
constexpr size_t buttonIdPosition = 1;
constexpr size_t buttonStatePosition = 2;

void handleAxes(const char buffer[bufferSize]);
void handleButton(const char buffer[bufferSize]);

void setup() {
    rkConfig cfg;
    // Upravte nastavení, například:
    cfg.motor_max_power_pct = 100;
    cfg.motor_max_power_pct = 30; // limit výkonu motorů na 30%
    Serial.begin(115200);
    cfg.motor_enable_failsafe = false;
    cfg.rbcontroller_app_enable = false;

    cfg.owner = "vasek"; // Ujistěte se, že v aplikace RBController máte nastavené stejné
    cfg.name = "SokolSus";

    WiFi.softAP("vasek", "sokolska");
    WiFiUDP udp;
    udp.begin(80);

    //std::thread t1(print);

    rkSetup(cfg);

    // Sem patří váš kód

    rkLedBlue();


    

    while (true) {
        delay(2000);
        rkLedRed(true);

        // Dopředu na 100%
        rkMotorsSetSpeed(100, 100);
        delay(2000);

        rkMotorsSetPower(100, 100);
        delay(2000);

        printf("jede to");
        Serial.print("jede to");
        
    }
}



/*


void handleAxes(const char buffer[bufferSize]) {
    // auto& man = rb::Manager::get();
    // printf("orig x: %i\ty: %i\n", buffer[xAxisPosition], buffer[yAxisPosition]);
    //int x = static_cast<int8_t>(buffer[xAxisPosition]);
    //int y = -static_cast<int8_t>(buffer[yAxisPosition]);

    int levy_m = 30;
    int pravy_m = 30;

    rkMotorsSetPower(levy_m, pravy_m); //rkMotorsSetSpeed jede sotva polovicni rychlosti !!
}

void handleButton(const char buffer[bufferSize], WiFiUDP &udp) {
    size_t id = buffer[buttonIdPosition];
    uint8_t state = buffer[buttonStatePosition];

    if (id >= buttonCount) {
        ESP_LOGE("UDP Parser", "Button id out of bounds");
    }

    // ESP_LOGI("UDP Parser", "Button %u changed to %u\n", id, state);
    udp.printf("Button %u changed to %u\n", id, state);
    printf("Button %u changed to %u\n", id, state);

    btn[id] = (bool)state;

    servoBus.set(1, Angle::deg(Servo_Hodnota_Jedna));
    servoBus.set(2, Angle::deg(Servo_Hodnota_Dva));

}
*/

/*
    servoBus.set(1, Angle::deg(Servo_Hodnota_Jedna));
    servoBus.set(2, Angle::deg(Servo_Hodnota_Dva));

*/

