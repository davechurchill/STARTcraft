#pragma once

#include <BWAPI.h>

// We don't want to have to type obscenely long names like BWAPI::Broodwar all the time,
// so we make some convenience using's and global variables.
namespace bw {
    using namespace BWAPI;
}

extern bw::GameWrapper& g_game;
extern bw::Player g_self;

namespace Tools {
    BWAPI::Unit GetClosestUnitTo(BWAPI::Position p, const BWAPI::Unitset& units);
    BWAPI::Unit GetClosestUnitTo(BWAPI::Unit unit, const BWAPI::Unitset& units);

    int CountUnitsOfType(BWAPI::UnitType type, const BWAPI::Unitset& units);

    BWAPI::Unit GetUnitOfType(BWAPI::UnitType type);

    bool BuildBuilding(BWAPI::UnitType type);

    void DrawUnitBoundingBoxes();
    void DrawUnitCommands();

    int GetTotalSupply(bool inProgress = false);

    void DrawUnitHealthBars();
    void DrawHealthBar(BWAPI::Unit unit, double ratio, BWAPI::Color color, int yOffset);
}