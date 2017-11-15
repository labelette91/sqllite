#include "stdafx.h"
#include <iostream>     /* standard I/O functions                         */
#include "sqlite3.h"
#include <vector>
#include <string>
#include <sstream>     /* standard I/O functions                         */
#include <SYS\STAT.H>
#include "localtime_r.h"
#include <fstream> 



#define DB_VERSION 32

const char *sqlCreateDeviceStatus =
"CREATE TABLE IF NOT EXISTS [DeviceStatus] ("
"[ID] INTEGER PRIMARY KEY, "
"[HardwareID] INTEGER NOT NULL, "
"[DeviceID] VARCHAR(25) NOT NULL, "
"[Unit] INTEGER DEFAULT 0, "
"[Name] VARCHAR(100) DEFAULT Unknown, "
"[Used] INTEGER DEFAULT 0, "
"[Type] INTEGER NOT NULL, "
"[SubType] INTEGER NOT NULL, "
"[SwitchType] INTEGER DEFAULT 0, "
"[Favorite] INTEGER DEFAULT 0, "
"[SignalLevel] INTEGER DEFAULT 0, "
"[BatteryLevel] INTEGER DEFAULT 0, "
"[nValue] INTEGER DEFAULT 0, "
"[sValue] VARCHAR(200) DEFAULT null, "
"[LastUpdate] DATETIME DEFAULT (datetime('now','localtime')),"
"[Order] INTEGER BIGINT(10) default 0, "
"[AddjValue] FLOAT DEFAULT 0, "
"[AddjMulti] FLOAT DEFAULT 1, "
"[AddjValue2] FLOAT DEFAULT 0, "
"[AddjMulti2] FLOAT DEFAULT 1, "
"[LastLevel] INTEGER DEFAULT 0, "
"[CustomImage] INTEGER DEFAULT 0);";


extern std::string szStartupFolder;


void Log(int error,const char * message)
{
  printf(" %s",message);
}


bool QueryInsert ( )
{
/*		sprintf(szTmp,
			"INSERT INTO DeviceStatus (HardwareID, DeviceID, Unit, Type, SubType, SignalLevel, BatteryLevel, nValue, sValue) "
			"VALUES (%d,'%s',%d,%d,%d,%d,%d,%d,'%s')",
			HardwareID,
			ID,unit,devType,subType,
			signallevel,batterylevel,
			nValue,sValue);
		result=query(szTmp);
*/
return true;

}

extern sqlite3 *m_dbase;
void CSQLClose(void);

void createDevices()
{
  std::string m_dbase_name = (".\\sql1.db") ;

  sqlite3_initialize( );

	//Open Database
	int rc = sqlite3_open(m_dbase_name.c_str(), &m_dbase);
	if (rc)
	{
		sqlite3_close(m_dbase);
		return ;
	}
  CSQLClose();
}