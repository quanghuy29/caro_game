#ifndef _DATABASE_
#define _DATABASE_

//#pragma once
#include "server.h"
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

using namespace std;
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000
#define SCORE 3

struct userScore{
	char username[30];
	int score;

	userScore(char name[30], int scoreUser) {
		strcpy_s(username,name);
		score = scoreUser;
	}
};

bool connectDB();
void disconnectDB();

void updateUserIsFree(char *username, int isFree);
void updateUserChallenge(char *username, char *usernameChallenge);
string getUserChallenge(char *username);
int getRank(char *username);
int getStatusFree(char *username);
int getScore(char *username);
//bool setUser(playerInfo* user);
void updateUserStatus(char *username, int status);
void updateRank();
void updateScoreOfPlayer(char *username, int win);
int userLogin(char *username, char *password);

string getAllPlayer(char *);
void showSQLError(unsigned int handleType, const SQLHANDLE& handle);

#endif