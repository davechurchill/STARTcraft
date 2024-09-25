#include "AutoPilotBot.h"
#include "Tools.h"

#include <BWAPI/Client.h>

#include <iostream>
#include <thread>
#include <chrono>

bw::Client& g_client = bw::BWAPIClient;
int g_gameCount = 0;

static void handleEvents(AutoPilotBot& bot) {
    for (const bw::Event& e : g_game->getEvents()) {
        switch (e.getType()) {
        case bw::EventType::MatchStart:
            bot.onStart(g_gameCount);
            break;
        case bw::EventType::MatchFrame:
            bot.onFrame();
            bot.onDraw();
            break;
        case bw::EventType::MatchEnd:
            bot.onEnd(e.isWinner());
            break;
        case bw::EventType::SendText:
            bot.onSendText(e.getText());
            break;
        case bw::EventType::UnitCreate:
            bot.onUnitCreate(e.getUnit());
            break;
        case bw::EventType::UnitDestroy:
            bot.onUnitDestroy(e.getUnit());
            break;
        case bw::EventType::UnitComplete:
            bot.onUnitComplete(e.getUnit());
            break;
        case bw::EventType::UnitMorph:
            bot.onUnitMorph(e.getUnit());
            break;
        case bw::EventType::UnitRenegade:
            bot.onUnitRenegade(e.getUnit());
            break;
        case bw::EventType::UnitEvade:
            bot.onUnitEvade(e.getUnit());
            break;
        case bw::EventType::UnitDiscover:
            bot.onUnitDiscover(e.getUnit());
            break;
        case bw::EventType::UnitHide:
            bot.onUnitHide(e.getUnit());
            break;
        case bw::EventType::UnitShow:
            bot.onUnitShow(e.getUnit());
            break;
        }
    }
}

static void playGame(AutoPilotBot& bot) {
    std::cout << "\n### Waiting for game" << std::endl;

    // While there's no game playing, just keep updating the client and looping. If we
    // disconnect at any point, return.
    while (!g_game->isInGame()) {
        if (!g_client.isConnected()) {
            return;
        }

        g_client.update();
    }

    // The game has started, so initialize our global player variable.
    std::cout << "### Game started" << std::endl;
    g_self = g_game->self();

    // Now we have the main bot loop: repeatedly handle any events that come our way and
    // update the client. Again, if we disconnect at any point, return.
    while (g_game->isInGame()) {
        if (!g_client.isConnected()) {
            break;
        }

        handleEvents(bot);
        g_client.update();
    }

    // Now that the game has finished, increase game count.
    std::cout << "### Game completed" << std::endl;
    g_gameCount++;
}

int main() {
    std::cout << "AutoPilot Bot - University of Portland" << std::endl;
    std::cout << "https://github.com/v-rob/AutoPilot" << std::endl;

    // Try to connect to StarCraft. If it fails, wait a second and try again.
    while (!g_client.connect()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "### Connected" << std::endl;

    // As long as we're connected to StarCraft, keep playing games.
    AutoPilotBot bot;

    while (g_client.isConnected()) {
        playGame(bot);
    }

    std::cout << "\n### Disconnected" << std::endl;
    return 0;
}