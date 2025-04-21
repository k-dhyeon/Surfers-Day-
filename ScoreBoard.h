#pragma once
#include "stdio.h"



void ScoreBoradInit(void);
void ScoreBoradUpdate(void);
void ScoreBoradExit(void);
void UpdateScoreBoardKeyInput(void);



int compareScores(const void* a, const void* b);
void saveData(FSaveData data[]);
void loadData(FSaveData data[]);

int FindScoreRank();
void GetPlayerKeyBoardInput();