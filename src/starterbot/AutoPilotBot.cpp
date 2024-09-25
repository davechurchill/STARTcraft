#include "AutoPilotBot.h"

void AutoPilotBot::onStart(int gameCount) {
    std::cout << "Playing game " << gameCount << " on map " <<
        g_game->mapFileName() << std::endl;

    // Set the speed at which our configuration option says the game should be run at.
    g_game->setLocalSpeed(LOCAL_SPEED);
    g_game->setFrameSkip(0);

    // We want the user to be able to send explicit user input.
    g_game->enableFlag(bw::Flag::UserInput);
}

void AutoPilotBot::onFrame() {
    // Send our idle workers to mine minerals so they don't just stand there.
    sendIdleWorkersToMinerals();

    // Train more workers so we can gather more income.
    trainAdditionalWorkers();

    // Build more supply if we are going to run out soon.
    buildAdditionalSupply();
}

void AutoPilotBot::onDraw() {
    Tools::DrawUnitHealthBars();
    Tools::DrawUnitCommands();
    Tools::DrawUnitBoundingBoxes();
}

void AutoPilotBot::onEnd(bool isWinner) {
    std::cout << "Game finished with " << (isWinner ? "win" : "loss") << std::endl;
}

void AutoPilotBot::onSendText(const std::string& text) {}

// For now, we don't use any of these callbacks, so they remain empty.
void AutoPilotBot::onUnitCreate(bw::Unit unit) {}
void AutoPilotBot::onUnitDestroy(bw::Unit unit) {}
void AutoPilotBot::onUnitComplete(bw::Unit unit) {}
void AutoPilotBot::onUnitMorph(bw::Unit unit) {}
void AutoPilotBot::onUnitRenegade(bw::Unit unit) {}
void AutoPilotBot::onUnitEvade(bw::Unit unit) {}
void AutoPilotBot::onUnitDiscover(bw::Unit unit) {}
void AutoPilotBot::onUnitShow(bw::Unit unit) {}
void AutoPilotBot::onUnitHide(bw::Unit unit) {}

void AutoPilotBot::sendIdleWorkersToMinerals() {
    // Let's send all of our starting workers to the closest mineral to them. First, we
    // need to loop over all of the units that we own.
    for (bw::Unit unit : g_self->getUnits()) {
        // Check the unit type. If it's an idle worker, then we want to send it somewhere.
        if (unit->getType().isWorker() && unit->isIdle()) {
            // Get the closest mineral to this worker unit.
            bw::Unit closestMineral = Tools::GetClosestUnitTo(unit, g_game->getMinerals());

            // If a valid mineral was found, right click it with the unit in order to
            // start harvesting.
            if (closestMineral != nullptr) {
                unit->rightClick(closestMineral);
            }
        }
    }
}

void AutoPilotBot::trainAdditionalWorkers() {
    bw::UnitType workerType = g_self->getRace().getWorker();
    int workersOwned = Tools::CountUnitsOfType(workerType, g_self->getUnits());

    // If we have a sufficient number of workers, we don't need to train any more.
    if (workersOwned >= 20) {
        return;
    }

    // Get the unit pointer to my depot.
    bw::Unit myDepot = Tools::GetUnitOfType(g_self->getRace().getResourceDepot());

    // If we have a valid depot unit and it's currently not training something, train
    // a worker. There's no reason for a bot to ever use the unit queueing system.
    if (myDepot && !myDepot->isTraining()) {
        myDepot->train(workerType);
    }
}

void AutoPilotBot::buildAdditionalSupply() {
    // Get the amount of supply supply we currently have unused.
    int unusedSupply = Tools::GetTotalSupply(true) - g_self->supplyUsed();

    // If we have a sufficient amount of supply, we don't need to do anything.
    if (unusedSupply >= 2) {
        return;
    }

    // Otherwise, we want to build a supply provider.
    bw::UnitType supplyProviderType = g_self->getRace().getSupplyProvider();

    bool startedBuilding = Tools::BuildBuilding(supplyProviderType);
    if (startedBuilding) {
        g_game->printf("Started building %s", supplyProviderType.getName().c_str());
    }
}