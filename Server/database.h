#ifndef _DATABASE_
#define _DATABASE_

#pragma once
#include "server.h"
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

using namespace std;
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

bool connectDB();
void disconnectDB();

void isUserExist(Player* player);
bool getUser(char *username, char *password, playerInfo* user);
bool setUser(playerInfo* user);
void getUserByUsername(char *username);
void updateUserStatus(char *username);
void updateScoreOfPlayer(Player* player, int win);

string getAllPlayer();
void showSQLError(unsigned int handleType, const SQLHANDLE& handle);

#endif