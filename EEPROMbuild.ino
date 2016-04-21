//
//    EEPROMbuild.ino  --  Install 'ReportExitStatus' translations
//

#include <EEPROM.h>

#define EEPROMSize 1024    // ATmega328

char *EEPROMtext[] = {
    "Success",                                        //  0 Success
    "Parameter error",                                //  1 ParameterError
    "Console Interrupt",                              //  2 ConsoleInterrupt
    "Upper bound check",                              //  3 UpperBound
    "Lower bound check",                              //  4 LowerBound
    "PGood bad",                                      //  5 PBad
    "Voltage too high for battery health",            //  6 PanicVoltage
    "Voltage threshold exceeded",                     //  7 MaxChargeVoltage
    "Current exceeds shunt capacity",                 //  8 MaxAmp
    "Current too low",                                //  9 MinAmp
    "Temperature too high for battery health",        // 10 PanicTemp
    "Temperature indicates full charge",              // 11 ChargeTempThreshold
    "Rate of temperature rise indicates full charge", // 12 ChargeTempRate
    "Timed out",                                      // 13 MaxTime
    "Ideal diode blocking",                           // 14 IdealDiodeStatus
    "Voltage dip indicates full charge",              // 15 DipDetected
    "No battery present",                             // 16 NoBattery
    "Battery reversed",                               // 17 ReversedBattery
    "Unknown battery type",                           // 18 UnknownBattery
    "Alkaline battery",                               // 19 Alkaline
    "Lithium battery",                                // 20 Lithium
    "Accepting substantial charge",                   // 21 Precharge rate > C/10
     NULL
};

#define Nstrings (sizeof(EEPROMtext) / sizeof(char *))

void setup (void)
{
    Serial.begin(38400);
    delay(600);

}

void loop (void)
{
    int j = 0;

    Serial.print("Zeroing EEPROM... ");
    for (int i = 0; i < EEPROMSize; i++)
        EEPROM.write(i, 0);

    Serial.print("Writing text to EEPROM... ");
    for (int i = 0; EEPROMtext[i] != NULL; i++)
        j = writeString(j, EEPROMtext[i]);

    Serial.print("Done.\nContents...\n");
    PrintContents();
    Serial.print("\n~");

    while (1)
        ;

}


int writeString (int offset, char *string)
{
    while (*string != '\0')
        if (offset < 1023)
           EEPROM.write(offset++, *string++);

    EEPROM.write(offset++, 0);
    return offset;

}


void PrintContents (void)
{
    int i;
    char c;

    for (i = 0; i < 1024; i++)
        if ((c = EEPROM.read(i)) == '\0')
            Serial.write('|');
        else
            Serial.write(c);

}
