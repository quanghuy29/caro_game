#include "server.h"
#include "database.h"

SQLHANDLE SQLEnvHandle = NULL;
SQLHANDLE SQLConnectionHandle = NULL;
SQLHANDLE SQLStatementHandle = NULL;

bool connectDB() {
	SQLRETURN retCode = 0;
	bool rsConn = false;

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
		switch (SQLDriverConnect(SQLConnectionHandle, NULL,
			(SQLCHAR*)"DRIVER={SQL Server}; SERVER=HANGVT, 1433; DATABASE=GameCaro; UID=sa; PWD=Meobeo145;",
			SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			rsConn = true;
			break;
		case SQL_SUCCESS_WITH_INFO:
			rsConn = true;
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

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;
		
	} while (FALSE);
	return rsConn;
}

void disconnectDB() {
	// Frees the resources and disconnects
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
}

int userLogin(char *username, char *password) {
	string SQLQuery = "SELECT password, status FROM information WHERE username='" + string(username) + "'";
	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			disconnectDB();
			return 400;
		}
		else
		{
			char pass[30];
			int status;
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &pass, sizeof(pass), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_ULONG, &status, 0, NULL);
			}
			int ret = strcmp(pass, "");
			if (strcmp(pass, "") == 0) {
				disconnectDB();
				return 11;
			}
			if (strcmp(pass, password) != 0) {
				disconnectDB();
				return 14;
			}
			else {
				if (status == 1) {
					disconnectDB();
					return 12;
				}
				else {
					updateUserStatus(username, 1);
					disconnectDB();
					return 10;
				}
			}
		}
	}
	
}

void updateUserIsFree(char *username, int isFree) {
	string SQLQuery = "UPDATE information SET isFree=" + to_string(isFree) + " WHERE username='" + string(username) + "'";
	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			disconnectDB();
		}
	}
	disconnectDB();
}

void updateUserChallenge(char *username, char *usernameChallenge) {
	string SQLQuery;
	if (strlen(usernameChallenge) > 0) {
		SQLQuery = "UPDATE information SET userChallenge='" + string(usernameChallenge) + "' WHERE username='" + string(username) + "'";
	}
	else
	{
		SQLQuery = "UPDATE information SET userChallenge=NULL WHERE username='" + string(username) + "'";
	}
	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			disconnectDB();
		}
	}
	disconnectDB();
}

string getUserChallenge(char *username) {
	char userChallenge[30];
	string resutlUserChallenge = "";
	string SQLQuery = "SELECT userChallenge FROM information WHERE username='" + string(username) + "'";
	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			disconnectDB();
			return 0;
		}
		else
		{
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &userChallenge, sizeof(userChallenge), NULL);
				resutlUserChallenge = resutlUserChallenge + userChallenge;
			}
		}
	}
	disconnectDB();
	return resutlUserChallenge;
}

int getRank(char *username) {
	int rank;
	string SQLQuery = "SELECT rank FROM information WHERE username='" + string(username) + "'";
	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			disconnectDB();
			return 0;
		}
		else
		{
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_ULONG, &rank, 0, NULL);
			}
		}
	}
	disconnectDB();
	return rank;
}

int getStatusFree(char *username) {
	int isFree, status;
	string SQLQuery = "SELECT isFree, status FROM information WHERE username='" + string(username) + "'";
	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			disconnectDB();
			return 0;
		}
		else
		{
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_ULONG, &isFree, 0, NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_ULONG, &status, 0, NULL);
			}
		}
	}
	disconnectDB();
	return (isFree && status);
}

int getScore(char *username) {
	int score;
	string SQLQuery = "SELECT score FROM information WHERE username='" + string(username) + "'";
	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			disconnectDB();
			return 0;
		}
		else
		{
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_ULONG, &score, 0, NULL);
			}
		}
	}
	disconnectDB();
	return (score);
}

//bool setUser(playerInfo* user) {}

void updateUserStatus(char *username, int status) {
	string SQLQuery = "UPDATE information SET status=" + to_string(status) + " WHERE username='" + string(username) + "'";
	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		}
	}
	disconnectDB();
}

void updateScoreOfPlayer(char *username, int win) {
	int score = getScore(username);
	if (win < 2) {
		if (win) {
			score += SCORE;
		}
		else 
		{
			score -= SCORE;
			if (score < 0) score = 0;
		}

		string SQLQuery = "UPDATE information SET score=" + to_string(score) + " WHERE username='" + username + "'";
		if (connectDB()) {
			if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
			{
				// Executes a preparable statement
				showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			}
		}
		disconnectDB();
	}
}

void updateRank() {
	int rank = 1;
	int scoreUser = -1;
	char username[30];
	int score;
	vector<userScore> listUserScore;
	string SQLQuery1 = "SELECT username, score FROM information ORDER BY score DESC";

	if (connectDB()) {
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery1.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		}
		else
		{
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &username, sizeof(username), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_ULONG, &score, 0, NULL);
				listUserScore.push_back(userScore(username, score));
			}
		}
	}
	disconnectDB();
	if (connectDB()) {
		scoreUser = listUserScore[0].score;
		string SQLQuery2 = "UPDATE information SET rank=" + to_string(rank) + " WHERE username='" + string(listUserScore[0].username) + "'";

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery2.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		}
		for (int i = 1; i < listUserScore.size(); i++) {
			if (scoreUser != listUserScore[i].score) {
				rank++;
				scoreUser = listUserScore[i].score;
			}
			string SQLQuery2 = "UPDATE information SET rank=" + to_string(rank) + " WHERE username='" + string(listUserScore[i].username) + "'";

			if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery2.c_str(), SQL_NTS))
			{
				// Executes a preparable statement
				showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			}
		}
	}
	disconnectDB();
}

string getAllPlayer(char *username) {
	string resutlAllPlayer = "";
	string SQLQuery = "SELECT username FROM information WHERE status=1 AND isFree=1 AND username NOT IN ('" + string(username) + "')";
	if (connectDB()) {
		char user[30];
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
		{
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		}
		else
		{
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &user, sizeof(user), NULL);
				resutlAllPlayer = resutlAllPlayer + user + " ";
			}
		}
	}
	disconnectDB();
	return resutlAllPlayer;
}

void showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		// Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information
		cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << endl;
}