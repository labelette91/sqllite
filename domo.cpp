#include "stdafx.h"
#include <iostream>     /* standard I/O functions                         */
#include "sqlite3.h"
#include <vector>
#include <string>
#include <sstream>     /* standard I/O functions                         */
#include <SYS\STAT.H>
#include "localtime_r.h"
#include <fstream> 

#include "RFXNames.h"


#define DB_VERSION 32






extern void Log(int error,const char * message);
extern std::vector<std::vector<std::string> > query(const std::string &szQuery) ;

//DELETE FROM DeviceStatus ;


bool QueryDelete (                   )
{
  char szTmp [1024];
  std::vector<std::vector<std::string> > result ;
		sprintf(szTmp,"DELETE FROM DeviceStatus ; " );
		result = query(szTmp);

return true;

}

bool QueryInsert ( 
			int HardwareID,
			int ID,
      int unit,
      int devType,
      int subType,
      int switchType,
			char * name 
                  )
{
  char szTmp [1024];
  std::vector<std::vector<std::string> > result ;
		sprintf(szTmp,
			"INSERT INTO DeviceStatus (HardwareID, DeviceID, Unit, Type, SubType, switchType, Name ) "
			"VALUES (%d,%d,%d,%d,%d,%d,'%s')",
			HardwareID,
			ID,
      unit,
      devType,
      subType,
      switchType,
			name );
		result = query(szTmp);

return true;

}

extern sqlite3 *m_dbase;
void CSQLClose(void);

#include "RFXNames.h"
#include "RFXtrx.h"
#include "hardwaretypes.h"

	 const STR_TABLE_ID1_ID2	T_RFX_Type_SubType_Desc[] =
	{
		{ pTypeTEMP, sTypeTEMP1, "THR128/138, THC138" },
//		{ pTypeTEMP, sTypeTEMP2, "THC238/268, THN132, THWR288, THRN122, THN122, AW129/131" },
//		{ pTypeTEMP, sTypeTEMP3, "THWR800" },
//		{ pTypeTEMP, sTypeTEMP4, "RTHN318" },
//		{ pTypeTEMP, sTypeTEMP5, "LaCrosse TX3" },
//		{ pTypeTEMP, sTypeTEMP6, "TS15C" },
//		{ pTypeTEMP, sTypeTEMP7, "Viking 02811/02813, Proove TSS330" },
//		{ pTypeTEMP, sTypeTEMP8, "LaCrosse WS2300" },
//		{ pTypeTEMP, sTypeTEMP9, "RUBiCSON" },
//		{ pTypeTEMP, sTypeTEMP10, "TFA 30.3133" },
//		{ pTypeTEMP, sTypeTEMP11, "WT0122 Pool sensor" },
//		{ pTypeTEMP, sTypeTEMP_SYSTEM, "System" },

		{ pTypeHUM, sTypeHUM1, "LaCrosse TX3" },
////		{ pTypeHUM, sTypeHUM2, "LaCrosse WS2300" },
//
//		{ pTypeTEMP_HUM, sTypeTH1, "THGN122/123, THGN132, THGR122/228/238/268" },
//		{ pTypeTEMP_HUM, sTypeTH2, "THGR810, THGN800" },
//		{ pTypeTEMP_HUM, sTypeTH3, "RTGR328" },
//		{ pTypeTEMP_HUM, sTypeTH4, "THGR328" },
//		{ pTypeTEMP_HUM, sTypeTH5, "WTGR800" },
//		{ pTypeTEMP_HUM, sTypeTH6, "THGR918, THGRN228, THGN500" },
//		{ pTypeTEMP_HUM, sTypeTH7, "Cresta, TFA TS34C" },
//		{ pTypeTEMP_HUM, sTypeTH8, "WT450H" },
//		{ pTypeTEMP_HUM, sTypeTH9, "Viking 02035, 02038, TSS320" },
//		{ pTypeTEMP_HUM, sTypeTH10, "Rubicson/IW008T/TX95" },
//		{ pTypeTEMP_HUM, sTypeTH11, "Oregon EW109" },
//		{ pTypeTEMP_HUM, sTypeTH12, "Imagintronix" },
//		{ pTypeTEMP_HUM, sTypeTH13, "Alecto WS1700" },
//		{ pTypeTEMP_HUM, sTypeTH14, "Alecto" },
//		{ pTypeTEMP_HUM, sTypeTH_LC_TC, "LaCrosse TX3" },


//		{ pTypeTEMP_HUM_BARO, sTypeTHB1, "THB1 - BTHR918, BTHGN129" },
//		{ pTypeTEMP_HUM_BARO, sTypeTHB2, "THB2 - BTHR918N, BTHR968" },
//		{ pTypeTEMP_HUM_BARO, sTypeTHBFloat, "Weather Station" },

		{ pTypeRAIN, sTypeRAIN1, "RGR126/682/918/928" },
//		{ pTypeRAIN, sTypeRAIN2, "PCR800" },
//		{ pTypeRAIN, sTypeRAIN3, "TFA" },
//		{ pTypeRAIN, sTypeRAIN4, "UPM RG700" },
//		{ pTypeRAIN, sTypeRAIN5, "LaCrosse WS2300" },
//		{ pTypeRAIN, sTypeRAIN6, "LaCrosse TX5" },
//		{ pTypeRAIN, sTypeRAINWU, "WWW" },

		{ pTypeWIND, sTypeWIND1, "WTGR800" },
//		{ pTypeWIND, sTypeWIND2, "WGR800" },
//		{ pTypeWIND, sTypeWIND3, "STR918/928, WGR918" },
//		{ pTypeWIND, sTypeWIND4, "TFA" },
//		{ pTypeWIND, sTypeWIND5, "UPM WDS500" },
//		{ pTypeWIND, sTypeWIND6, "LaCrosse WS2300" },
//		{ pTypeWIND, sTypeWIND7, "Alecto WS4500" },
//		{ pTypeWIND, sTypeWINDNoTemp, "Weather Station" },

		{ pTypeUV, sTypeUV1, "UVN128,UV138" },
//		{ pTypeUV, sTypeUV2, "UVN800" },
//		{ pTypeUV, sTypeUV3, "TFA" },

		{ pTypeLighting1, sTypeX10, "X10" },
//		{ pTypeLighting1, sTypeARC, "ARC" },
//		{ pTypeLighting1, sTypeAB400D, "ELRO AB400" },
//		{ pTypeLighting1, sTypeWaveman, "Waveman" },
//		{ pTypeLighting1, sTypeEMW200, "EMW200" },
//		{ pTypeLighting1, sTypeIMPULS, "Impuls" },
//		{ pTypeLighting1, sTypeRisingSun, "RisingSun" },
//		{ pTypeLighting1, sTypePhilips, "Philips" },
//		{ pTypeLighting1, sTypeEnergenie, "Energenie" },
//		{ pTypeLighting1, sTypeEnergenie5, "Energenie 5-gang" },
//		{ pTypeLighting1, sTypeGDR2, "COCO GDR2" },
//		{ pTypeLighting1, sTypeHQ, "HQ COCO-20" },

		{ pTypeLighting2, sTypeAC, "AC" },
//		{ pTypeLighting2, sTypeHEU, "HomeEasy EU" },
//		{ pTypeLighting2, sTypeANSLUT, "Anslut" },

		{ pTypeLighting3, sTypeKoppla, "Ikea Koppla" },

//		{ pTypeLighting4, sTypePT2262, "PT2262" },

		{ pTypeLighting5, sTypeLightwaveRF, "LightwaveRF" },
//		{ pTypeLighting5, sTypeEMW100, "EMW100" },
//		{ pTypeLighting5, sTypeBBSB, "BBSB new" },
//		{ pTypeLighting5, sTypeMDREMOTE, "MDRemote" },
//		{ pTypeLighting5, sTypeRSL, "Conrad RSL" },
//		{ pTypeLighting5, sTypeLivolo, "Livolo" },
//		{ pTypeLighting5, sTypeTRC02, "TRC02 (RGB)" },
//		{ pTypeLighting5, sTypeTRC02_2, "TRC02_2 (RGB)" },
//		{ pTypeLighting5, sTypeAoke, "Aoke" },
//		{ pTypeLighting5, sTypeEurodomest, "Eurodomest" },
//		{ pTypeLighting5, sTypeLivoloAppliance, "Livolo Appliance" },
//		{ pTypeLighting5, sTypeRGB432W, "RGB432W" },
//		{ pTypeLighting5, sTypeMDREMOTE107, "MDRemote 107" },
//		{ pTypeLighting5, sTypeLegrandCAD, "Legrand CAD" },
//		{ pTypeLighting5, sTypeAvantek, "Avantek" },
//		{ pTypeLighting5, sTypeIT, "Intertek,FA500,PROmax" },
//		{ pTypeLighting5, sTypeMDREMOTE108, "MDRemote 108" },
//		{ pTypeLighting5, sTypeKangtai, "Kangtai / Cotech" },

		{ pTypeLighting6, sTypeBlyss, "Blyss" },

		{ pTypeHomeConfort, sTypeHomeConfortTEL010 , "TEL-010" },

		{ pTypeCurtain, sTypeHarrison, "Harrison" },

		{ pTypeBlinds, sTypeBlindsT0, "RollerTrol, Hasta new" },
//		{ pTypeBlinds, sTypeBlindsT1, "Hasta old" },
//		{ pTypeBlinds, sTypeBlindsT2, "A-OK RF01" },
//		{ pTypeBlinds, sTypeBlindsT3, "A-OK AC114" },
//		{ pTypeBlinds, sTypeBlindsT4, "RAEX" },
//		{ pTypeBlinds, sTypeBlindsT5, "Media Mount" },
//		{ pTypeBlinds, sTypeBlindsT6, "DC106" },
//		{ pTypeBlinds, sTypeBlindsT7, "Forest" },
//		{ pTypeBlinds, sTypeBlindsT8, "Chamberlain CS4330CN" },
//		{ pTypeBlinds, sTypeBlindsT9, "Sunpery" },
//		{ pTypeBlinds, sTypeBlindsT10, "Dolat DLM-1" },
//		{ pTypeBlinds, sTypeBlindsT11, "ASP" },
//		{ pTypeBlinds, sTypeBlindsT12, "Confexx" },
//		{ pTypeBlinds, sTypeBlindsT13, "Screenline" },

		{ pTypeSecurity1, sTypeSecX10, "X10 security" },
//		{ pTypeSecurity1, sTypeSecX10M, "X10 security motion" },
//		{ pTypeSecurity1, sTypeSecX10R, "X10 security remote" },
//		{ pTypeSecurity1, sTypeKD101, "KD101 smoke detector" },
//		{ pTypeSecurity1, sTypePowercodeSensor, "Visonic PowerCode sensor - primary contact" },
//		{ pTypeSecurity1, sTypePowercodeMotion, "Visonic PowerCode motion" },
//		{ pTypeSecurity1, sTypeCodesecure, "Visonic CodeSecure" },
//		{ pTypeSecurity1, sTypePowercodeAux, "Visonic PowerCode sensor - auxiliary contact" },
//		{ pTypeSecurity1, sTypeMeiantech, "Meiantech/Atlantic/Aidebao" },
//		{ pTypeSecurity1, sTypeSA30, "Alecto SA30 smoke detector" },
//		{ pTypeSecurity1, sTypeDomoticzSecurity, "Security Panel" },

		{ pTypeSecurity2, sTypeSec2Classic, "KeeLoq" },

		{ pTypeCamera, sTypeNinja, "Meiantech" },

		{ pTypeRemote, sTypeATI, "ATI Remote Wonder" },
//		{ pTypeRemote, sTypeATIplus, "ATI Remote Wonder Plus" },
//		{ pTypeRemote, sTypeMedion, "Medion Remote" },
//		{ pTypeRemote, sTypePCremote, "PC Remote" },
//		{ pTypeRemote, sTypeATIrw2, "ATI Remote Wonder II" },

		{ pTypeThermostat1, sTypeDigimax, "Digimax" },
//		{ pTypeThermostat1, sTypeDigimaxShort, "Digimax with short format" },

		{ pTypeThermostat2, sTypeHE105, "HE105" },
//		{ pTypeThermostat2, sTypeRTS10, "RTS10" },

		{ pTypeThermostat3, sTypeMertikG6RH4T1, "Mertik G6R-H4T1" },
//		{ pTypeThermostat3, sTypeMertikG6RH4TB, "Mertik G6R-H4TB" },
//		{ pTypeThermostat3, sTypeMertikG6RH4TD, "Mertik G6R-H4TD" },
//		{ pTypeThermostat3, sTypeMertikG6RH4S, "Mertik G6R-H4S" },

		{ pTypeThermostat4, sTypeMCZ1, "MCZ 1 fan model" },
//		{ pTypeThermostat4, sTypeMCZ2, "MCZ 2 fan model" },
//		{ pTypeThermostat4, sTypeMCZ3, "MCZ 3 fan model" },

		{ pTypeRadiator1, sTypeSmartwares, "Smartwares" },
//		{ pTypeRadiator1, sTypeSmartwaresSwitchRadiator, "Smartwares Mode" },

		{ pTypeDT, sTypeDT1, "RTGR328N" },

		{ pTypeCURRENT, sTypeELEC1, "CM113, Electrisave" },

		{ pTypeENERGY, sTypeELEC2, "CM119 / CM160" },
//		{ pTypeENERGY, sTypeELEC3, "CM180" },

		{ pTypeCURRENTENERGY, sTypeELEC4, "CM180i" },

		{ pTypeWEIGHT, sTypeWEIGHT1, "BWR102" },
//		{ pTypeWEIGHT, sTypeWEIGHT2, "GR101" },

		{ pTypeRFXSensor, sTypeRFXSensorTemp, "Temperature" },
//		{ pTypeRFXSensor, sTypeRFXSensorAD, "A/D" },
//		{ pTypeRFXSensor, sTypeRFXSensorVolt, "Voltage" },

		{ pTypeRFXMeter, sTypeRFXMeterCount, "RFXMeter counter" },

		{ pTypeP1Power, sTypeP1Power, "Energy" },
		{ pTypeP1Gas, sTypeP1Gas, "Gas" },

		{ pTypeYouLess, sTypeYouLess, "YouLess counter" },

		{ pTypeRego6XXTemp, sTypeRego6XXTemp, "Rego 6XX" },
		{ pTypeRego6XXValue, sTypeRego6XXStatus, "Rego 6XX" },
//		{ pTypeRego6XXValue, sTypeRego6XXCounter, "Rego 6XX" },

		{ pTypeAirQuality, sTypeVoltcraft, "Voltcraft CO-20" },

		{ pTypeUsage, sTypeElectric, "Electric" },

		{ pTypeTEMP_BARO, sTypeBMP085, "BMP085 I2C" },

		{ pTypeLux, sTypeLux, "Lux" },

		{ pTypeGeneral, sTypeVisibility, "Visibility" },
		{ pTypeGeneral, sTypeSolarRadiation, "Solar Radiation" },
		{ pTypeGeneral, sTypeSoilMoisture, "Soil Moisture" },
		{ pTypeGeneral, sTypeLeafWetness, "Leaf Wetness" },
		{ pTypeGeneral, sTypeSystemTemp, "System temperature" },
		{ pTypeGeneral, sTypePercentage, "Percentage" },
		{ pTypeGeneral, sTypeFan, "Fan" },
		{ pTypeGeneral, sTypeVoltage, "Voltage" },
		{ pTypeGeneral, sTypeCurrent, "Current" },
		{ pTypeGeneral, sTypePressure, "Pressure" },
		{ pTypeGeneral, sTypeBaro, "Barometer" },
		{ pTypeGeneral, sTypeSetPoint, "Setpoint" },
		{ pTypeGeneral, sTypeTemperature, "Temperature" },
		{ pTypeGeneral, sTypeZWaveClock, "Thermostat Clock" },
		{ pTypeGeneral, sTypeTextStatus, "Text" },
		{ pTypeGeneral, sTypeZWaveThermostatMode, "Thermostat Mode" },
		{ pTypeGeneral, sTypeZWaveThermostatFanMode, "Thermostat Fan Mode" },
		{ pTypeGeneral, sTypeAlert, "Alert" },
		{ pTypeGeneral, sTypeSoundLevel, "Sound Level" },
		{ pTypeGeneral, sTypeUV, "UV" },
		{ pTypeGeneral, sTypeDistance, "Distance" },
		{ pTypeGeneral, sTypeCounterIncremental, "Counter Incremental" },
		{ pTypeGeneral, sTypeKwh, "kWh" },
		{ pTypeGeneral, sTypeWaterflow, "Waterflow" },
		{ pTypeGeneral, sTypeCustom, "Custom Sensor" },
		{ pTypeGeneral, sTypeZWaveAlarm, "Alarm" },

		{ pTypeThermostat, sTypeThermSetpoint, "SetPoint" },
		{ pTypeThermostat, sTypeThermTemperature, "Temperature" },

		{ pTypeChime, sTypeByronSX, "ByronSX" },
//		{ pTypeChime, sTypeByronMP001, "Byron MP001" },
//		{ pTypeChime, sTypeSelectPlus, "SelectPlus" },
//		{ pTypeChime, sTypeSelectPlus3, "SelectPlus3" },
//		{ pTypeChime, sTypeEnvivo, "Envivo" },

		{ pTypeFan, sTypeSiemensSF01 , "Siemens SF01" },
//		{ pTypeFan, sTypeItho , "Itho CVE RFT" },
//		{ pTypeFan, sTypeLucciAir, "Lucci Air" },

		{ pTypeTEMP_RAIN, sTypeTR1, "Alecto WS1200" },

		{ pTypeBBQ, sTypeBBQ1, "Maverick ET-732" },

		{ pTypePOWER, sTypeELEC5, "Revolt" },

		{ pTypeLimitlessLights, sTypeLimitlessRGBW, "RGBW" },
//		{ pTypeLimitlessLights, sTypeLimitlessRGB, "RGB" },
//		{ pTypeLimitlessLights, sTypeLimitlessWhite, "White" },
//		{ pTypeLimitlessLights, sTypeLimitlessRGBWW, "RGBWW" },

		{ pTypeRFY, sTypeRFY, "RFY" },
//		{ pTypeRFY, sTypeRFY2, "RFY2" },
//		{ pTypeRFY, sTypeRFYext, "RFY-Ext" },
//		{ pTypeRFY, sTypeASA, "ASA" },

		{ pTypeEvohome, sTypeEvohome, "Evohome" },
		{ pTypeEvohomeZone, sTypeEvohomeZone, "Zone" },
		{ pTypeEvohomeWater, sTypeEvohomeWater, "Hot Water" },
		{ pTypeEvohomeRelay, sTypeEvohomeRelay, "Relay" },
		{ pTypeGeneralSwitch, sSwitchTypeX10, "X10" },
//		{ pTypeGeneralSwitch, sSwitchTypeARC, "ARC" },
//		{ pTypeGeneralSwitch, sSwitchTypeAB400D, "ELRO AB400" },
//		{ pTypeGeneralSwitch, sSwitchTypeWaveman, "Waveman" },
//		{ pTypeGeneralSwitch, sSwitchTypeEMW200, "EMW200" },
//		{ pTypeGeneralSwitch, sSwitchTypeIMPULS, "Impuls" },
//		{ pTypeGeneralSwitch, sSwitchTypeRisingSun, "RisingSun" },
//		{ pTypeGeneralSwitch, sSwitchTypePhilips, "Philips" },
//		{ pTypeGeneralSwitch, sSwitchTypeEnergenie, "Energenie" },
//		{ pTypeGeneralSwitch, sSwitchTypeEnergenie5, "Energenie 5-gang" },
//		{ pTypeGeneralSwitch, sSwitchTypeGDR2, "COCO GDR2" },
//		{ pTypeGeneralSwitch, sSwitchTypeAC, "AC" },
//		{ pTypeGeneralSwitch, sSwitchTypeHEU, "HomeEasy EU" },
//		{ pTypeGeneralSwitch, sSwitchTypeANSLUT, "Anslut" },
//		{ pTypeGeneralSwitch, sSwitchTypeKoppla, "Ikea Koppla" },
//		{ pTypeGeneralSwitch, sSwitchTypePT2262, "PT2262" },
//		{ pTypeGeneralSwitch, sSwitchTypeLightwaveRF, "LightwaveRF" },
//		{ pTypeGeneralSwitch, sSwitchTypeEMW100, "EMW100" },
//		{ pTypeGeneralSwitch, sSwitchTypeBBSB, "BBSB new" },
//		{ pTypeGeneralSwitch, sSwitchTypeMDREMOTE, "MDRemote" },
//		{ pTypeGeneralSwitch, sSwitchTypeRSL, "Conrad RSL" },
//		{ pTypeGeneralSwitch, sSwitchTypeLivolo, "Livolo" },
//		{ pTypeGeneralSwitch, sSwitchTypeTRC02, "TRC02 (RGB)" },
//		{ pTypeGeneralSwitch, sSwitchTypeTRC02_2, "TRC02_2 (RGB)" },
//		{ pTypeGeneralSwitch, sSwitchTypeAoke, "Aoke" },
//		{ pTypeGeneralSwitch, sSwitchTypeEurodomest, "Eurodomest" },
//		{ pTypeGeneralSwitch, sSwitchTypeLivoloAppliance, "Livolo Appliance" },
//		{ pTypeGeneralSwitch, sSwitchTypeBlyss, "Blyss" },
//		{ pTypeGeneralSwitch, sSwitchTypeByronSX, "ByronSX" },
//		{ pTypeGeneralSwitch, sSwitchTypeByronMP001, "Byron MP001" },
//		{ pTypeGeneralSwitch, sSwitchTypeSelectPlus, "SelectPlus" },
//		{ pTypeGeneralSwitch, sSwitchTypeSelectPlus3, "SelectPlus3" },
//		{ pTypeGeneralSwitch, sSwitchTypeFA20, "FA20RF" },
//		{ pTypeGeneralSwitch, sSwitchTypeChuango, "Chuango" },
//		{ pTypeGeneralSwitch, sSwitchTypePlieger, "Plieger" },
//		{ pTypeGeneralSwitch, sSwitchTypeSilvercrest, "SilverCrest" },
//		{ pTypeGeneralSwitch, sSwitchTypeMertik, "Mertik" },
//		{ pTypeGeneralSwitch, sSwitchTypeHomeConfort, "HomeConfort" },
//		{ pTypeGeneralSwitch, sSwitchTypePowerfix, "Powerfix" },
//		{ pTypeGeneralSwitch, sSwitchTypeTriState, "TriState" },
//		{ pTypeGeneralSwitch, sSwitchTypeDeltronic, "Deltronic" },
//		{ pTypeGeneralSwitch, sSwitchTypeFA500, "FA500" },
//		{ pTypeGeneralSwitch, sSwitchTypeHT12E, "HT12E" },
//		{ pTypeGeneralSwitch, sSwitchTypeEV1527, "EV1527" },
//		{ pTypeGeneralSwitch, sSwitchTypeElmes, "Elmes" },
//		{ pTypeGeneralSwitch, sSwitchTypeAster, "Aster" },
//		{ pTypeGeneralSwitch, sSwitchTypeSartano, "Sartano" },
//		{ pTypeGeneralSwitch, sSwitchTypeEurope, "Europe" },
//		{ pTypeGeneralSwitch, sSwitchTypeAvidsen, "Avidsen" },
//		{ pTypeGeneralSwitch, sSwitchTypeBofu, "BofuMotor" },
//		{ pTypeGeneralSwitch, sSwitchTypeBrel, "BrelMotor" },
//		{ pTypeGeneralSwitch, sSwitchTypeRTS, "RTS" },
//		{ pTypeGeneralSwitch, sSwitchTypeElroDB, "ElroDB" },
//		{ pTypeGeneralSwitch, sSwitchTypeDooya, "Dooya" },
//		{ pTypeGeneralSwitch, sSwitchTypeUnitec, "Unitec" },
//		{ pTypeGeneralSwitch, sSwitchTypeSelector, "Selector Switch" },
//		{ pTypeGeneralSwitch, sSwitchTypeMaclean, "Maclean" },
//		{ pTypeGeneralSwitch, sSwitchTypeR546, "R546" },
//		{ pTypeGeneralSwitch, sSwitchTypeDiya, "Diya" },
//		{ pTypeGeneralSwitch, sSwitchTypeX10secu, "X10Secure" },
//		{ pTypeGeneralSwitch, sSwitchTypeAtlantic, "Atlantic" },
//		{ pTypeGeneralSwitch, sSwitchTypeSilvercrestDB, "SilvercrestDB" },
//		{ pTypeGeneralSwitch, sSwitchTypeMedionDB, "MedionDB" },
//		{ pTypeGeneralSwitch, sSwitchTypeVMC, "VMC" },
//		{ pTypeGeneralSwitch, sSwitchTypeKeeloq, "Keeloq" },
//		{ pTypeGeneralSwitch, sSwitchCustomSwitch, "CustomSwitch" },
//		{ pTypeGeneralSwitch, sSwitchGeneralSwitch, "Switch" },
//		{ pTypeGeneralSwitch, sSwitchTypeKoch, "Koch" },
//		{ pTypeGeneralSwitch, sSwitchTypeKingpin, "Kingpin" },
//		{ pTypeGeneralSwitch, sSwitchTypeFunkbus, "Funkbus" },
//		{ pTypeGeneralSwitch, sSwitchTypeNice, "Nice" },
//		{ pTypeGeneralSwitch, sSwitchTypeForest, "Forest" },
//		{ pTypeGeneralSwitch, sSwitchBlindsT1, "Legrand MyHome Blind Bus" },
//		{ pTypeGeneralSwitch, sSwitchLightT1, "Legrand MyHome Light Bus" },
//		{ pTypeGeneralSwitch, sSwitchAuxiliaryT1, "Legrand MyHome Auxiliary Bus" },
//		{ pTypeGeneralSwitch, sSwitchContactT1, "Legrand MyHome DryContact/IRdetec" },
//		{ pTypeGeneralSwitch, sSwitchMC145026, "MC145026" },
//		{ pTypeGeneralSwitch, sSwitchLobeco, "Lobeco" },
//		{ pTypeGeneralSwitch, sSwitchFriedland, "Friedland" },
//		{ pTypeGeneralSwitch, sSwitchBFT, "BFT" },
//		{ pTypeGeneralSwitch, sSwitchNovatys, "Novatys" },
//		{ pTypeGeneralSwitch, sSwitchHalemeier, "Halemeier" },
//		{ pTypeGeneralSwitch, sSwitchGaposa, "Gaposa" },
//		{ pTypeGeneralSwitch, sSwitchMiLightv1, "MiLightv1" },
//		{ pTypeGeneralSwitch, sSwitchMiLightv2, "MiLightv2" },
//		{ pTypeGeneralSwitch, sSwitchHT6P20, "HT6P20" },
//		{ pTypeGeneralSwitch, sSwitchTypeDoitrand, "Doitrand" },
//		{ pTypeGeneralSwitch, sSwitchTypeWarema, "Warema" },
//		{ pTypeGeneralSwitch, sSwitchTypeAnsluta, "Ansluta" },
//		{ pTypeGeneralSwitch, sSwitchTypeLivcol, "Livcol" },
//		{ pTypeGeneralSwitch, sSwitchTypeBosch, "Bosch" },
//		{ pTypeGeneralSwitch, sSwitchTypeNingbo, "Ningbo" },
//		{ pTypeGeneralSwitch, sSwitchTypeDitec, "Ditec" },
//		{ pTypeGeneralSwitch, sSwitchTypeSteffen, "Steffen" },
//		{ pTypeGeneralSwitch, sSwitchTypeAlectoSA, "AlectoSA" },
//		{ pTypeGeneralSwitch, sSwitchTypeGPIOset, "GPIOset" },
//		{ pTypeGeneralSwitch, sSwitchTypeKonigSec, "KonigSec" },
//		{ pTypeGeneralSwitch, sSwitchTypeRM174RF, "RM174RF" },
//		{ pTypeGeneralSwitch, sSwitchTypeLiwin, "Liwin" },
//		{ pTypeGeneralSwitch, sSwitchBlindsT2, "Legrand MyHome Blind Zigbee" },
//		{ pTypeGeneralSwitch, sSwitchLightT2, "Legrand MyHome Light Zigbee" },
//		{ pTypeGeneralSwitch, sSwitchTypeYW_Secu, "YW_Secu" },
//		{ pTypeGeneralSwitch, sSwitchTypeMertik_GV60, "Mertik_GV60" },
//		{ pTypeGeneralSwitch, sSwitchTypeNingbo64, "Ningbo64"},
//		{ pTypeGeneralSwitch, sSwitchTypeX2D, "X2D" },
//		{ pTypeGeneralSwitch, sSwitchTypeHRCMotor, "HRCMotor" },
//		{ pTypeGeneralSwitch, sSwitchTypeVelleman, "Velleman" },
//		{ pTypeGeneralSwitch, sSwitchTypeRFCustom, "RFCustom" },
//		{ pTypeGeneralSwitch, sSwitchTypeYW_Sensor, "YW_Sensor" },
//		{ pTypeGeneralSwitch, sSwitchTypeLegrandcad, "LEGRANDCAD" },
//		{ pTypeGeneralSwitch, sSwitchTypeSysfsGpio, "SysfsGpio" },
		{  0,0,NULL }
	};

  
	static const STR_TABLE_SINGLE	Switch_Type_DescTable[] =
	{
		{ STYPE_OnOff, "On/Off" },
		{ STYPE_Doorbell, "Doorbell" },
		{ STYPE_Contact, "Contact" },
		{ STYPE_Blinds, "Blinds" },
		{ STYPE_X10Siren, "X10 Siren" },
		{ STYPE_SMOKEDETECTOR, "Smoke Detector" },
		{ STYPE_BlindsInverted, "Blinds Inverted" },
		{ STYPE_Dimmer, "Dimmer" },
		{ STYPE_Motion, "Motion Sensor" },
		{ STYPE_PushOn, "Push On Button" },
		{ STYPE_PushOff, "Push Off Button" },
		{ STYPE_DoorContact, "Door Contact" },
		{ STYPE_Dusk, "Dusk Sensor" },
		{ STYPE_BlindsPercentage, "Blinds Percentage" },
		{ STYPE_VenetianBlindsUS, "Venetian Blinds US" },
		{ STYPE_VenetianBlindsEU, "Venetian Blinds EU" },
		{ STYPE_BlindsPercentageInverted, "Blinds Percentage Inverted" },
		{ STYPE_Media, "Media Player" },
		{ STYPE_Selector, "Selector" },
		{ STYPE_DoorLock, "Door Lock" },
		{ 0, NULL, NULL }
	};
  
const char *RFX_Type_Desc(const unsigned char i, const unsigned char snum) ;
  
  void createDevices()
{
  std::string m_dbase_name = (".\\domoticz.db") ;

  sqlite3_initialize( );

	//Open Database
	int rc = sqlite3_open(m_dbase_name.c_str(), &m_dbase);
	if (rc)
	{
		sqlite3_close(m_dbase);
		return ;
	}

  QueryDelete();

  int i=0 ;

  while (T_RFX_Type_SubType_Desc[i].id1)
  {
			int HardwareID = 2 ;
			int ID = i+1 ;
      int unit = 1 ;
      int devType = T_RFX_Type_SubType_Desc[i].id1 ;
      int subType = T_RFX_Type_SubType_Desc[i].id2 ;
      int switchType = 0 ;
//			char * name = (char *)T_RFX_Type_SubType_Desc[i].str1 ;

			char * name = (char *)RFX_Type_Desc(devType,1);

      QueryInsert ( 			HardwareID,
			 ID,
       unit,
       devType,
       subType,
       switchType,
			 name 
                  );

    i++;
  }


  i=0 ;
  while (Switch_Type_DescTable[i].str1)
  {
			int HardwareID = 2 ;
			int ID = i+1 ;
      int unit = 1 ;
      int devType = pTypeLighting2    ;
      int subType = sTypeAC ;
      int switchType = Switch_Type_DescTable[i].id  ;
			char * name = (char *)Switch_Type_DescTable[i].str1 ;

      QueryInsert ( 			HardwareID,
			 ID,
       unit,
       devType,
       subType,
       switchType,
			 name 
                  );

    i++;
  }


  CSQLClose();
}