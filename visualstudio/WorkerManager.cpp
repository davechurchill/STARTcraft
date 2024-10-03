#include "WorkerManager.h"
#include <vector>
#include <iostream>

/*
* WorkerManager class tracks and manages all of the worker units
* the AI has.
*/
class WorkerManager
{
public:
	std::vector<bw::Unit> getWorkerList() {
		return workerList;
	}
private:
	std::vector<bw::Unit> workerList;
	bw::Unit getWorker();
	void addUnit(const bw::Unit unit);
	void update();
};


/*
* getWorker():
* This method will iterate through the list of all worker units in the
* class and finds a worker unit available
*
* @return - a worker unit
*/
bw::Unit WorkerManager::getWorker() {
	// Get all of the workers from self and add it to the list
	std::vector<bw::Unit> currentWorkerList = WorkerManager::getWorkerList();
	const BWAPI::UnitType workerType = bw::Broodwar->self()->getRace().getWorker();
	for (auto unit : bw::Broodwar->self()->getUnits()) {
		if (unit->getType() == workerType) {
			if (unit->isIdle()) {
				return unit;
			}
		}
	}
	//we want to return the worker
};

/*
* addUnit()
* Checks if the given unit is in the list,
* if not, then add it to list.
*
* @param
* @return
*/
void WorkerManager::addUnit(const bw::Unit unit) {
	std::vector<bw::Unit> currentWorkerList = WorkerManager::getWorkerList();
	currentWorkerList.push_back(unit);
};

/*
* update()
* Updates the current list of workers by looking
* at the current state of the game. Removes dead workers
* and checks if any workers are gathering gas. Makes sure
* that gas is collected from idle workers.
*
* @param
* @return
*/
void WorkerManager::update() {

	std::vector<bw::Unit> removeWorkerList;
	bool gatheringGas = false;
	const bw::UnitType assimilatorType = bw::UnitTypes::Protoss_Assimilator;
	int numOfAssimilator = Tools::CountUnitsOfType(assimilatorType, g_self->getUnits());

	for (auto workerUnit : WorkerManager::workerList) {
		if (workerUnit->isIdle() and workerUnit->isCompleted()) {
			//we assign a task
			// whatever the functionality of the workerunit does currently (find closest mineral from worker unit
			// and check if the closest mineral is not null
			// if it's not null, then have the worker gather that mineral
		}

		//add dead worker units to removeWorkerList
		if (!workerUnit->exists()) {
			removeWorkerList.push_back(workerUnit);
		}

		if (workerUnit->isGatheringGas()) {
			gatheringGas = true;
		}
	}

	//remove dead workers from the workerList
	for (bw::Unit deadWorker : removeWorkerList)
	{
		WorkerManager::workerList.erase(std::remove(WorkerManager::workerList.begin(),
			WorkerManager::workerList.end(), deadWorker),
			WorkerManager::workerList.end());
	}


	/*
	* We update our current workerList to be exact in the game.
	* If none of the workers are collecting gas and we have an assimilator,
	* collect gas from closest Geyser
	*/
	if (!gatheringGas and numOfAssimilator >= 1) {
		bw::Unit anyWorker = getWorker(); //get worker that is in idle
		if (anyWorker != nullptr) {
			bw::Unit closestGeyser = Tools::GetClosestUnitTo(anyWorker, g_game->getGeysers());
			if (closestGeyser != nullptr) {
				anyWorker->rightClick(closestGeyser);
			}
		}
	}
}
