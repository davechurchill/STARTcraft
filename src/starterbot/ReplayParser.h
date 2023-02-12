#pragma once

#include <BWAPI.h>
#include <fstream>
#include <map>
#include "MapTools.h"

class ReplayParser
{
    MapTools m_map;

    std::ofstream m_fout;

    std::map<int, BWAPI::Position> m_unitCommands;

    void logUnitCommands();
    void drawUnitCommands();
    std::string getUnitString(BWAPI::Unit unit);

public:

    ReplayParser();


    // functions that are triggered by various BWAPI events from main.cpp
	void onStart();
	void onFrame();
	void onEnd(bool isWinner);
	void onUnitDestroy(BWAPI::Unit unit);
	void onUnitMorph(BWAPI::Unit unit);
	void onSendText(std::string text);
	void onUnitCreate(BWAPI::Unit unit);
	void onUnitComplete(BWAPI::Unit unit);
	void onUnitShow(BWAPI::Unit unit);
	void onUnitHide(BWAPI::Unit unit);
	void onUnitRenegade(BWAPI::Unit unit);
};