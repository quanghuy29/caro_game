#include "server.h"
#include "database.h"

bool connectDB() {
	SQLHANDLE SQLEnvHandle = NULL;
	SQLHANDLE SQLConnectionHandle = NULL;
	SQLHANDLE SQLStatementHandle = NULL;
	SQLRETURN retCode = 0;

	//char* sql = const_cast<char*>(SQLQuery.c_str());

	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[SQL_RETURN_CODE_LEN]; // Conection string
		//int retur = SQLDriverConnect(SQLConnectionHandle, NULL,
		//	(SQLCHAR*)"DRIVER={SQL Server}; SERVER=HANGVT, 1433; DATABASE=GameCaro; UID=sa; PWD=Meobeo145;",
		//	SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT);
		switch (SQLDriverConnect(SQLConnectionHandle, NULL,
			(SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=GameCaro; UID=sa; PWD=Meobeo145;",
			SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			retCode = 1;
			break;
		case SQL_SUCCESS_WITH_INFO:
			retCode = 1;
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		//if (retCode == -1)
		//	break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		/*
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)"SELECT * FROM table information;", SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			//break;
			return false;
		}
		else {
			return true;
		}*/
		

	} while (FALSE);

	// Frees the resources and disconnects
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	return true;
}

bool isUserExist(char *username);
bool getUser(char * username, char * password, playerInfo* user);
bool setUser(playerInfo* user);
void getUserByUserID(int userID, playerInfo* user);
bool getUserBySock(int sockUser, playerInfo* user);
void updateUserStatus(playerInfo* user);
void updateSockUser(playerInfo* user);

void getPlayerByUserID(int userID, Player* player);
void setPlayerByUserID(int userID, Player* player);

void updateWinOfPlayer(Player* player);
void updateLoseOfPlayer(Player* player);
void updateDrawOfPlayer(Player* player);

int getAllPlayer(Player* allPlayer);
void showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		// Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information
		cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << endl;
}