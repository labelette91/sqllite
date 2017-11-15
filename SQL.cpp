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

sqlite3 *m_dbase;
std::string m_dbase_name;

#define LOG_ERROR 1

std::vector<std::vector<std::string> > query(const std::string &szQuery);


class TSQL {
public:
static std::vector<std::vector<std::string> > Query( char * fmt , ... );
};

TSQL m_sql;

bool GetLastValue(  const char* DeviceID, int &nValue, std::string &sValue, struct tm &LastUpdateTime)
{
    bool result=false;
    std::vector<std::vector<std::string> > sqlresult;
	char szTmp[400];
	std::string sLastUpdate;
	//std::string sValue;
	//struct tm LastUpdateTime;
	time_t now = mytime(NULL);
	struct tm tm1;
	localtime_r(&now,&tm1);
		
	sprintf(szTmp,"SELECT nValue,sValue,LastUpdate FROM DeviceStatus WHERE ( Name='%s' ) ",DeviceID );
	sqlresult=query(szTmp);
	
	if (sqlresult.size()!=0)
	{
		nValue=(int)atoi(sqlresult[0][0].c_str());
		sValue=sqlresult[0][1];
	    sLastUpdate=sqlresult[0][2];
		
		LastUpdateTime.tm_isdst=tm1.tm_isdst;
		LastUpdateTime.tm_year=atoi(sLastUpdate.substr(0,4).c_str())-1900;
		LastUpdateTime.tm_mon=atoi(sLastUpdate.substr(5,2).c_str())-1;
		LastUpdateTime.tm_mday=atoi(sLastUpdate.substr(8,2).c_str());
		LastUpdateTime.tm_hour=atoi(sLastUpdate.substr(11,2).c_str());
		LastUpdateTime.tm_min=atoi(sLastUpdate.substr(14,2).c_str());
		LastUpdateTime.tm_sec=atoi(sLastUpdate.substr(17,2).c_str());
	
		result=true;
	}
	
	return result;
}



void UpdateTempVar(const char *Key, const char* sValue)
{
	if (!m_dbase)
		return;

	char szTmp[600];

	unsigned long long ID=0;

	std::vector<std::vector<std::string> > result;
	sprintf(szTmp,"SELECT ROWID FROM TempVars WHERE (Key='%s')",Key);
	result=query(szTmp);
	if (result.size()==0)
	{
		//Insert
		sprintf(szTmp,
			"INSERT INTO TempVars (Key, sValue) VALUES ('%s','%s')",
			Key,sValue);
		result=query(szTmp);
	}
	else
	{
		//Update
		std::stringstream s_str( result[0][0] );
		s_str >> ID;
		sprintf(szTmp,"UPDATE TempVars SET sValue='%s' WHERE (ROWID = %llu)",sValue,ID);
		result = query(szTmp);
	}
}

bool GetTempVar(const char *Key, int &nValue, std::string &sValue)
{
	if (!m_dbase)
		return false;

	char szTmp[100];

	std::vector<std::vector<std::string> > result;
	sprintf(szTmp,"SELECT nValue,sValue FROM TempVars WHERE (Key='%s')",Key);
	result=query(szTmp);
	if (result.size()<1)
		return false;
	std::vector<std::string> sd=result[0];
	nValue=atoi(sd[0].c_str());
	sValue=sd[1];
	return true;
}


void Log(int error,const char * message)
{
  printf(" %s",message);
}


void SetDatabaseName(const std::string &DBName)
{
	m_dbase_name=DBName;
}

void CSQLInit(void)
{
	m_dbase=NULL;

	SetDatabaseName(".\\sql1.db");
}

void CSQLClose(void)
{
	if (m_dbase!=NULL)
	{
		sqlite3_close(m_dbase);
		m_dbase=NULL;
	}
}

std::vector<std::vector<std::string> > query(const std::string &szQuery)
{
	if (!m_dbase)
	{
		Log(LOG_ERROR,"Database not open!!...Check your user rights!..");
		std::vector<std::vector<std::string> > results;
		return results;
	}
//	boost::lock_guard<boost::mutex> l(m_sqlQueryMutex);
	
	sqlite3_stmt *statement;
	std::vector<std::vector<std::string> > results;

	if(sqlite3_prepare_v2(m_dbase, szQuery.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);

			if(result == SQLITE_ROW)
			{
				std::vector<std::string> values;
				for(int col = 0; col < cols; col++)
				{
					char* value = (char*)sqlite3_column_text(statement, col);
					if (value == 0)
						break;
					values.push_back(value);
				}
				if (values.size()>0)
					results.push_back(values);
			}
			else
			{
				break;  
			}
		}
		sqlite3_finalize(statement);
	}

	std::string error = sqlite3_errmsg(m_dbase);
	if(error != "not an error") 
		Log(LOG_ERROR,error.c_str());
	return results; 
}


std::vector<std::vector<std::string> > TSQL::Query( char * fmt , ... )
{

    va_list argptr;
    va_start(argptr, fmt);  

    char szTmp[400];
    vsnprintf(szTmp,sizeof(szTmp), fmt, argptr) ;
	return query( std::string(szTmp)) ;
}


void printQuery ( std::vector<std::vector<std::string> > &result )
{
  for (unsigned int i=0;i<result.size();i++)
    {
      for (unsigned j=0;j<result[i].size();j++)
        Log ( 0,result[i][j].c_str() );
      Log(0,"\n");
    }
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


void StringSplit(std::string str, const std::string &delim, std::vector<std::string> &results)
{
	size_t cutAt;
	while( (cutAt = str.find_first_of(delim)) != str.npos )
	{
		if(cutAt > 0)
		{
			results.push_back(str.substr(0,cutAt));
		}
        else
			results.push_back("");

		str = str.substr(cutAt+1);
	}
	if(str.length() > 0)
	{
		results.push_back(str);
	}
}

std::string getTemperature(const char * sValue)
{
	std::vector<std::string> splitresults;
	StringSplit(sValue, ";", splitresults);
	if (splitresults.size()<1)
      return "";
    else
      return splitresults[0];
}
std::string getHumidity(char * sValue)
{
	std::vector<std::string> splitresults;
	StringSplit(sValue, ";", splitresults);
	if (splitresults.size()>=1)
      return splitresults[1];
    else
      return "";
}

int create_csv_table( char * csvFileName , sqlite3 *db , std::string  TableName )
{
        std::ifstream fs;
        std::string Ligne;
        fs.open(csvFileName);
        std::string szTmp ;
        // lecture du fichier

        // lit la ligne de valeur a envoyer
        std::getline(fs, Ligne) ;
        fs.close();
        std::vector<std::string> splitresults;
        StringSplit(Ligne, ";", splitresults);
        if (splitresults.size()<1)
            return 0 ;
        szTmp =      "CREATE TABLE IF NOT EXISTS ["+ TableName +"] (";


        for (unsigned int i=0;i<splitresults.size();i++)
        {
        szTmp +=  "[" + splitresults[i] + "] VARCHAR DEFAULT '' "  ; 
        if (i!=splitresults.size()-1)
          szTmp += ",";
        }
        szTmp +=");"  ; 

        query(szTmp) ;
        return (splitresults.size());

}


void import_csv( char * csvFileName , sqlite3 *db , std::string  TableName , int nbColumns )
{
        std::ifstream fs;
        std::string Ligne;
        fs.open(csvFileName);
        std::string szTmp ;
        // lecture du fichier

        // lit la ligne de valeur a envoyer
        while  ( std::getline(fs, Ligne) )
        {
	      std::vector<std::string> splitresults;
	      StringSplit(Ligne, ";", splitresults);
	      if (splitresults.size()<1)
            break ;
          for (int i=splitresults.size();i<nbColumns;i++)
            splitresults.push_back("");

	//sprintf(szTmp,"SELECT ID,Name FROM DeviceStatus WHERE (HardwareID=%d AND DeviceID='%s' AND Unit=%d AND Type=%d AND SubType=%d)",HardwareID, ID, unit, devType, subType);
        szTmp = "INSERT INTO " + TableName+ " VALUES ( " ;
        szTmp +=  "'" + splitresults[0] + "'"  ; 
        for (unsigned int i=1;i<splitresults.size();i++)
        {
        szTmp +=  ",'" + splitresults [i] + "'"  ; 
        }
        szTmp +=")"  ; 

        query(szTmp) ;


        }
        fs.close();


}

typedef   std::vector<std::string> RowQuery ;


void testImport()
{
     sqlite3_initialize( );

	//Open Database
//	int rc = sqlite3_open("test.db", &m_dbase);
	int rc = sqlite3_open(":memory:", &m_dbase);
	if (rc)	{
		sqlite3_close(m_dbase);
		return ;
	}

	rc=sqlite3_exec(m_dbase, "PRAGMA synchronous = NORMAL", NULL, NULL, NULL);

    //4000 page cache of 1024
	rc=sqlite3_exec(m_dbase, "PRAGMA cache_size = 4000", NULL, NULL, NULL);

    printQuery(query( 
"CREATE TABLE IF NOT EXISTS  user ("
"id integer,"
"nom text,"
"prenom text,"
"datnais text);"
)) ;


    import_csv( "users.csv" , m_dbase , "user" ,0 );

    printQuery(query("select * from user limit 100 ") );


    sqlite3_close( m_dbase );
    sqlite3_shutdown( );

}


void testImportParameterCsv()
{
     sqlite3_initialize( );

	//Open Database
	int rc = sqlite3_open("test.db", &m_dbase);
//	int rc = sqlite3_open(":memory:", &m_dbase);
	if (rc)	{
		sqlite3_close(m_dbase);
		return ;
	}

	rc=sqlite3_exec(m_dbase, "PRAGMA synchronous = NORMAL", NULL, NULL, NULL);

    //4000 page cache of 1024
	rc=sqlite3_exec(m_dbase, "PRAGMA cache_size = 4000", NULL, NULL, NULL);

    int nbCols = create_csv_table( "test2.csv" , m_dbase , "parameter"  ) ;

    import_csv( "test2.csv" , m_dbase , "parameter" ,nbCols);

    printQuery(query("select * from parameter limit 100 ") );


    sqlite3_close( m_dbase );
    sqlite3_shutdown( );

}






const char *sqlCreateTimers =
"CREATE TABLE IF NOT EXISTS [Timers] ("
"[ID] INTEGER PRIMARY KEY, "
"[Active] BOOLEAN DEFAULT true, "
"[DeviceRowID] BIGINT(10) NOT NULL, "
"[Time] TIME NOT NULL, "
"[Type] INTEGER NOT NULL, "
"[Cmd] INTEGER NOT NULL, "
"[Level] INTEGER DEFAULT 15, "
"[Hue] INTEGER DEFAULT 0, "
"[UseRandomness] INTEGER DEFAULT 0, "
"[Days] INTEGER NOT NULL);";

//row result for an sql query : string Vector
typedef   std::vector<std::string> TSqlRowQuery ;

// result for an sql query : Vector of TSqlRowQuery
typedef   std::vector<TSqlRowQuery> TSqlQueryResult ;


//return previous  thermostat target temperature before Time
int getPrevThermostatProg ( char * devID , char * CurrentTime , std::string &Time )
{
  int TargetTemp=0;
    TSqlQueryResult result = m_sql.Query("SELECT Time,Level FROM timers where (DeviceRowID==%s) and ( Time < '%s' ) order by time desc limit 1" ,devID, CurrentTime  ) ;
    if (result.size() ){
      Time       = result[0][0];
      TargetTemp =atoi(result[0][1].c_str());
    }
return TargetTemp;
}

//return next  thermostat target temperature after Time
int getNextThermostatProg ( char * devID , char * CurrentTime , std::string &Time )
{
  int TargetTemp=0;
    TSqlQueryResult result = m_sql.Query("SELECT Time,Level FROM timers where (DeviceRowID==%s) and ( Time > '%s' ) order by time asc limit 1" ,devID, CurrentTime  ) ;
    if (result.size() ){
      Time       = result[0][0];
      TargetTemp =atoi(result[0][1].c_str());
    }
return TargetTemp;
}


//force : toggle the thermostat temperature state to ECO / CONFORT mode
//algo  if current target temperature = minimum values in Timers table content  then
//      next Target = Maximum values in Timers table content 
//algo  if current target temperature = Maximum values in Timers table content  then
//      next Target = minimum values in Timers table content 

int ThermostatToggleEcoConfort (char * devID , int CurrentTargetTemp , char * Duration)
{
  int NextTargetTemp,PrevTargetTemp,MinTemp,MaxTemp;
  TSqlQueryResult result;
  
  //get last target temperature  
//  TSqlQueryResult result=m_sql.Query("SELECT TargetTemp FROM DeviceStatus where ID==%s", devID) ;
//  if (result.size()) CurrentTargetTemp=atoi(result[0][0].c_str());

  //get  max temperature  from timers
  result=m_sql.Query("SELECT MAX(Level) FROM timers where DeviceRowID==%s" , devID) ;
  if (result.size()) MaxTemp=atoi(result[0][0].c_str());else MaxTemp=20;

  //get min temperature  from timers
  result=m_sql.Query("SELECT MIN(Level) FROM timers where DeviceRowID==%s" , devID) ;
  if (result.size()) MinTemp=atoi(result[0][0].c_str());else MinTemp=16;

//    printQuery(query("SELECT Time,Level FROM timers where (DeviceRowID==%s) and ( Time < '%s' ) order by time desc limit 1" ,"1" , "11:00" ) ) ;
//    printQuery(query("SELECT Time,Level FROM timers where (DeviceRowID==%s) and ( Time > '%s' ) order by time asc  limit 1" ,"1" , "11:00" ) ) ;

  NextTargetTemp=CurrentTargetTemp;
  if (CurrentTargetTemp<=MinTemp)  NextTargetTemp = MaxTemp ;
  if (CurrentTargetTemp>=MaxTemp)  NextTargetTemp = MinTemp ;

  return NextTargetTemp;
 
}

int ThermostatToggleEcoConfort (char * devID , char * Duration)
{
  int CurrentTargetTemp =0 ;
  TSqlQueryResult result;
  
  //get last target temperature  from db
  result=m_sql.Query("SELECT TargetTemp FROM DeviceStatus where ID==%s", devID) ;
  if (result.size()) CurrentTargetTemp=atoi(result[0][0].c_str());
  return ThermostatToggleEcoConfort (devID , CurrentTargetTemp , Duration) ;
}


void TestThermostat ( int cTemp ) 
{
    printf ( "Current Target:%d Next Target:%d\n",cTemp, ThermostatToggleEcoConfort("1" , cTemp , "2" ) );
}

void testTimers()
{
	//Open Database
	int rc = sqlite3_open("domoticz.db", &m_dbase);
	if (rc)
	{
		sqlite3_close(m_dbase);
		return ;
	}
    std::string time;
    int t ;
    t=getPrevThermostatProg ( "1"  , "09:00" , time ) ; printf ("Tepm:%d Time:%s\n",t,time.c_str() );
    t=getPrevThermostatProg ( "1"  , "11:00" , time ) ;printf ("Tepm:%d Time:%s\n",t,time.c_str() );
    t=getPrevThermostatProg ( "1"  , "13:00" , time ) ;printf ("Tepm:%d Time:%s\n",t,time.c_str() );
    t=getPrevThermostatProg ( "1"  , "15:00" , time ) ;printf ("Tepm:%d Time:%s\n",t,time.c_str() );

    t=getNextThermostatProg ( "1"  , "09:00" , time ) ; printf ("Tepm:%d Time:%s\n",t,time.c_str() );
    t=getNextThermostatProg ( "1"  , "11:00" , time ) ;printf ("Tepm:%d Time:%s\n",t,time.c_str() );
    t=getNextThermostatProg ( "1"  , "13:00" , time ) ;printf ("Tepm:%d Time:%s\n",t,time.c_str() );
    t=getNextThermostatProg ( "1"  , "15:00" , time ) ;printf ("Tepm:%d Time:%s\n",t,time.c_str() );

/*
    printQuery(query("SELECT Time,Level FROM timers where DeviceRowID==%s","1" ) ) ;
    printQuery(query("SELECT MAX(Level) FROM timers where DeviceRowID==%s","1" ) ) ;
    printQuery(query("SELECT MIN(Level) FROM timers where DeviceRowID==%s","1" ) ) ;
    printQuery(query("SELECT Time,Level FROM timers where (DeviceRowID==%s) and ( Time < '%s' ) order by time desc limit 1" ,"1" , "11:00" ) ) ;
    printQuery(query("SELECT Time,Level FROM timers where (DeviceRowID==%s) and ( Time > '%s' ) order by time asc  limit 1" ,"1" , "11:00" ) ) ;
*/

TestThermostat ( 20 ) ;
TestThermostat ( 20 ) ;
TestThermostat ( 16 ) ;
TestThermostat ( 16 ) ;
TestThermostat ( 20 ) ;
TestThermostat ( 21 ) ;
TestThermostat ( 15 ) ;


    sqlite3_close( m_dbase );

    
}

bool OpenDatabase()
{
//  testImport();
//testTimers();
  testImportParameterCsv();
    return true;


char *errmsg  ;
    sqlite3_initialize( );

	//Open Database
	int rc = sqlite3_open(m_dbase_name.c_str(), &m_dbase);
	if (rc)
	{
		sqlite3_close(m_dbase);
		return false;
	}
#ifndef WIN32
	//test, this could improve performance
	rc=sqlite3_exec(m_dbase, "PRAGMA synchronous = NORMAL", NULL, NULL, NULL);
	rc=sqlite3_exec(m_dbase, "PRAGMA journal_mode = WAL", NULL, NULL, NULL);
#else
	rc=sqlite3_exec(m_dbase, "PRAGMA journal_mode=DELETE", NULL, NULL, NULL);
#endif
    rc=sqlite3_exec(m_dbase, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
	bool bNewInstall=false;
	std::vector<std::vector<std::string> > result=query("SELECT name FROM sqlite_master WHERE type='table' AND name='DeviceStatus'");
	bNewInstall=(result.size()==0);

	//create database (if not exists)
//	query(sqlCreateDeviceStatus);
    
//    char szTmp[400];
	//sprintf(szTmp,"SELECT ID,Name FROM DeviceStatus WHERE (HardwareID=%d AND DeviceID='%s' AND Unit=%d AND Type=%d AND SubType=%d)",HardwareID, ID, unit, devType, subType);
/*	sprintf(szTmp,"SELECT * FROM DeviceStatus" );
	result=query(szTmp) ;
  	if (result.size()==0)
	{
		Log(LOG_ERROR,"Serious database error, problem getting ID from DeviceStatus!");
		return false;
	}
*/
//    printQuery(result);

//    printQuery(query("SELECT * FROM DeviceStatus" ) ) ;

//    printQuery(query("SELECT DeviceID FROM DeviceStatus" ) ) ;
    
//    printQuery(query("SELECT %s,%s FROM DeviceStatus" ,"DeviceID","ID") ) ;

    printQuery(query( 
"CREATE TABLE IF NOT EXISTS  user ("
"id integer,"
"nom text,"
"prenom text,"
"datnais text);"
)) ;


import_csv( "users.csv" , m_dbase , "user" ,0);

//query("INSERT INTO TempVars (Key, nValue, sValue) VALUES ('%s',%d,'%s')","DummyDimmer",0,"Tremp");


    
    result=query("SELECT Name,SwitchType,nValue,sValue FROM DeviceStatus where SwitchType = 7" ) ;
    printQuery(result);

    sqlite3 *db = m_dbase;
    int             idx = -1;
    char            *data = "*"; /* default to empty string */


sqlite3_stmt    *stmt = NULL;

rc = sqlite3_prepare_v2( m_dbase, "SELECT :str FROM user ", -1, &stmt, NULL );
  

    if ( rc != SQLITE_OK) exit( -1 );

    idx = sqlite3_bind_parameter_index( stmt, ":str" );
    sqlite3_bind_text( stmt, idx, data, -1, SQLITE_STATIC );

    rc = sqlite3_step( stmt );
    if (( rc != SQLITE_DONE )&&( rc != SQLITE_ROW )) exit ( -1 );
    
    sqlite3_finalize( stmt );




   rc=sqlite3_exec(m_dbase, ".separator \";\"", NULL, NULL, &errmsg);
//   rc=sqlite3_exec(m_dbase, ".import users.csv test", NULL, NULL, NULL);

    sqlite3_close( db );
       sqlite3_shutdown( );


    return true;
}

bool Execute(char *  DbName , char SqlReq[] )
{
	sqlite3_initialize( );

	m_dbase_name = DbName ;
	std::string req = SqlReq;
	//Open Database
	int rc = sqlite3_open(m_dbase_name.c_str(), &m_dbase);
	if (rc)
	{
		sqlite3_close(m_dbase);
		return false;
	}
#ifndef WIN32
	//test, this could improve performance
	rc=sqlite3_exec(m_dbase, "PRAGMA synchronous = NORMAL", NULL, NULL, NULL);
	rc=sqlite3_exec(m_dbase, "PRAGMA journal_mode = WAL", NULL, NULL, NULL);
#else
	rc=sqlite3_exec(m_dbase, "PRAGMA journal_mode=DELETE", NULL, NULL, NULL);
#endif
    rc=sqlite3_exec(m_dbase, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
	bool bNewInstall=false;
	std::vector<std::vector<std::string> > result=query("SELECT name FROM sqlite_master WHERE type='table' AND name='DeviceStatus'");
	bNewInstall=(result.size()==0);

	if (strstr(SqlReq,"select") ){
		result=query(SqlReq) ;
		printQuery(result);
	}
	 sqlite3_close( m_dbase );
       sqlite3_shutdown( );


    return true;

}
