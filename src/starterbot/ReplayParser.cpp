#include "ReplayParser.h"
#include "Tools.h"

#include <sstream>

ReplayParser::ReplayParser()
{
    
}

// Called when the bot starts!
void ReplayParser::onStart()
{
    // Set the game to run at super speed so we can parse the replay faster
	//BWAPI::Broodwar->setLocalSpeed(0);
    //BWAPI::Broodwar->setFrameSkip(1024);

    // set up a file to write the output to
    m_fout = std::ofstream("ReplayData.txt");
}
    
void ReplayParser::onFrame()
{
    // Draw all unit commands and target positions
    for (auto unit : BWAPI::Broodwar->getAllUnits())
    {
        if (!unit->getPlayer()->isNeutral())
        {
            BWAPI::Position p1 = unit->getPosition();
            BWAPI::Position p2 = unit->getOrderTargetPosition();

            if (p2 != BWAPI::Position(0, 0))
            {
                BWAPI::Broodwar->drawLineMap(p1, p2, BWAPI::Colors::White);
            }

            BWAPI::Broodwar->drawTextMap(p1, unit->getOrder().getName().c_str());
        }
    }

    // Draw unit health bars, which brood war unfortunately does not do
    Tools::DrawUnitHealthBars();
}

void ReplayParser::onEnd(bool isWinner) 
{
    
}

// Called whenever a unit is destroyed, with a pointer to the unit
void ReplayParser::onUnitDestroy(BWAPI::Unit unit)
{
    const BWAPI::UnitType type = unit->getType();
    if (type.isBuilding() && !unit->getPlayer()->isNeutral())
    {
        m_fout << BWAPI::Broodwar->getFrameCount() << " destroy " << getUnitString(unit) << "\n";
    }
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void ReplayParser::onUnitMorph(BWAPI::Unit unit)
{
    const BWAPI::UnitType type = unit->getType();
    if (type.isBuilding() && !unit->getPlayer()->isNeutral())
    {
        m_fout << BWAPI::Broodwar->getFrameCount() << " create " << getUnitString(unit) << "\n";
    }
}

// Called whenever a text is sent to the game by a user
void ReplayParser::onSendText(std::string text) 
{ 

}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void ReplayParser::onUnitCreate(BWAPI::Unit unit)
{ 
    const BWAPI::UnitType type = unit->getType();
    if (type.isBuilding() && !unit->getPlayer()->isNeutral())
    {
        m_fout << BWAPI::Broodwar->getFrameCount() << " create " << getUnitString(unit) << "\n";
    }
}

// Called whenever a unit finished construction, with a pointer to the unit
void ReplayParser::onUnitComplete(BWAPI::Unit unit)
{
	
}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void ReplayParser::onUnitShow(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void ReplayParser::onUnitHide(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void ReplayParser::onUnitRenegade(BWAPI::Unit unit)
{ 
	
}

std::string ReplayParser::getUnitString(BWAPI::Unit unit)
{
    const BWAPI::UnitType type = unit->getType();
    BWAPI::Position tl(unit->getPosition().x - type.dimensionLeft(), unit->getPosition().y - type.dimensionUp());
    BWAPI::Position br(unit->getPosition().x + type.dimensionRight(), unit->getPosition().y + type.dimensionDown());

    std::stringstream ss;
    ss << unit->getPlayer()->getID() << " " << unit->getID() << " " << type.getName();
    ss << " " << tl.x << " " << tl.y << " " << br.x << " " << br.y;
    return ss.str();
}