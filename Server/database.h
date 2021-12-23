#pragma once
#include "server.h"
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

using namespace std;
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

typedef struct {
	SQLHANDLE SQLEnvHandle;
	SQLHANDLE SQLConnectionHandle;
	SQLHANDLE SQLStatementHandle;
	SQLRETURN retCode;
} Database;

bool connectDB();
void disconnectDB();

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
void showSQLError(unsigned int handleType, const SQLHANDLE& handle);