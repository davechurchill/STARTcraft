#pragma once

#include "Tools.h"

// Chooses the frame time in milliseconds that the game should be run at.
constexpr int LOCAL_SPEED = 10;

// This class is the primary class that governs the entire bot. It receives events about
// when each game starts and ends, plus whatever actions happen during the game. The
// primary job of this class is to give the various manager classes the information they
// need to know to do their jobs.
class AutoPilotBot {
public:
	// Called whenever a game starts with the number of the current game. The AutoPilotBot
	// object is created once and reused for every match, so initialization for each game
	// should happen here rather than in the constructor.
	void onStart(int gameCount);

	// Called for every frame of the game. Much of the main bot logic occurs here.
	void onFrame();

	// Like onFrame(), this is called for every frame of the game. However, drawing code
	// should be placed here rather than in onFrame().
	void onDraw();

	// Called whenever the game ends, plus information about whether the bot won or lost.
	void onEnd(bool isWinner);

	// Called whenever the user sends a chat message. This can be used to catch control
	// messages to control bot functionality or enable debugging features.
	void onSendText(const std::string& text);

	void onUnitCreate(bw::Unit unit);
	void onUnitDestroy(bw::Unit unit);
	void onUnitComplete(bw::Unit unit);
	void onUnitMorph(bw::Unit unit);
	void onUnitRenegade(bw::Unit unit);
	void onUnitEvade(bw::Unit unit);
	void onUnitDiscover(bw::Unit unit);
	void onUnitShow(bw::Unit unit);
	void onUnitHide(bw::Unit unit);

private:
	void sendIdleWorkersToMinerals();
	void trainAdditionalWorkers();
	void buildAdditionalSupply();
};