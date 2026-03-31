// ============================================================
// Project: Text Adventure Game
// Author: Silas Chalwe
// Compile: g++ -std=c++17 -Wall -o adventure main.cpp && ./adventure
// ============================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

struct Item {
    std::string name;
    std::string description;
    int power; // weapon power, 0 for non-weapons
};

struct Room {
    std::string name;
    std::string description;
    std::map<std::string, std::string> exits; // direction → room name
    std::vector<Item> items;
    bool hasEnemy;
    std::string enemyName;
};

class Player {
public:
    std::string name;
    int hp;
    int maxHp;
    int attack;
    std::vector<Item> inventory;

    Player(const std::string& n) : name(n), hp(100), maxHp(100), attack(10) {}

    void pickUp(Item item) {
        attack += item.power;
        inventory.push_back(item);
        std::cout << "Picked up: " << item.name << std::endl;
        if (item.power > 0) std::cout << "Attack power increased to " << attack << "!" << std::endl;
    }

    void showInventory() const {
        if (inventory.empty()) { std::cout << "Inventory is empty.\n"; return; }
        std::cout << "Inventory:\n";
        for (const auto& item : inventory) std::cout << "  - " << item.name << ": " << item.description << "\n";
    }

    void showStatus() const {
        std::cout << "HP: " << hp << "/" << maxHp << "  Attack: " << attack << "\n";
    }
};

class Game {
    std::map<std::string, Room> rooms;
    std::string currentRoom;
    Player player;
    bool running;

public:
    Game() : player("Hero"), running(true) {
        buildWorld();
        currentRoom = "Entrance";
    }

    void buildWorld() {
        rooms["Entrance"] = {
            "Entrance Hall",
            "You stand in a dimly lit entrance. Doors lead north and east.",
            {{"north", "Library"}, {"east", "Armory"}},
            {{  "torch", "A flickering torch", 0  }},
            false, ""
        };
        rooms["Library"] = {
            "Ancient Library",
            "Rows of dusty bookshelves. A scroll glows on a table.",
            {{"south", "Entrance"}, {"east", "Boss Room"}},
            {{"magic scroll", "A scroll of power", 5}},
            false, ""
        };
        rooms["Armory"] = {
            "Armory",
            "Weapon racks line the walls. A sword catches your eye.",
            {{"west", "Entrance"}},
            {{"iron sword", "A sharp iron sword", 20}},
            false, ""
        };
        rooms["Boss Room"] = {
            "Boss Chamber",
            "A dark chamber. The Dragon awaits!",
            {{"west", "Library"}},
            {},
            true, "Dragon"
        };
    }

    void look() const {
        const Room& room = rooms.at(currentRoom);
        std::cout << "\n--- " << room.name << " ---\n";
        std::cout << room.description << "\n";
        if (!room.items.empty()) {
            std::cout << "Items here: ";
            for (const auto& item : room.items) std::cout << item.name << " ";
            std::cout << "\n";
        }
        std::cout << "Exits: ";
        for (const auto& [dir, dest] : room.exits) std::cout << dir << " ";
        std::cout << "\n";
    }

    void go(const std::string& direction) {
        Room& room = rooms[currentRoom];
        auto it = room.exits.find(direction);
        if (it == room.exits.end()) { std::cout << "Can't go that way.\n"; return; }
        currentRoom = it->second;
        look();
        checkRoom();
    }

    void take(const std::string& itemName) {
        Room& room = rooms[currentRoom];
        auto it = std::find_if(room.items.begin(), room.items.end(),
            [&](const Item& i){ return i.name == itemName; });
        if (it == room.items.end()) { std::cout << "No such item here.\n"; return; }
        player.pickUp(*it);
        room.items.erase(it);
    }

    void checkRoom() {
        Room& room = rooms[currentRoom];
        if (room.hasEnemy) {
            std::cout << "\nA wild " << room.enemyName << " appears! (HP: 50)\n";
            int enemyHp = 50;
            while (enemyHp > 0 && player.hp > 0) {
                std::cout << "Attack? (y/n): ";
                char ch; std::cin >> ch;
                if (ch == 'y' || ch == 'Y') {
                    enemyHp -= player.attack;
                    player.hp -= 15;
                    std::cout << "You deal " << player.attack << " damage. "
                              << room.enemyName << " HP: " << std::max(0, enemyHp) << "\n";
                    std::cout << "Enemy hits you for 15. Your HP: " << player.hp << "\n";
                } else { std::cout << "You hesitate...\n"; }
            }
            if (player.hp <= 0) { std::cout << "You were defeated! Game over.\n"; running = false; }
            else { std::cout << "You defeated the " << room.enemyName << "! You win!\n"; running = false; }
            room.hasEnemy = false;
        }
    }

    void processCommand(const std::string& cmd) {
        std::istringstream iss(cmd);
        std::string verb; iss >> verb;
        if (verb == "look" || verb == "l")      { look(); }
        else if (verb == "go")   { std::string dir; iss >> dir; go(dir); }
        else if (verb == "take") { std::string rest; std::getline(iss >> std::ws, rest); take(rest); }
        else if (verb == "inv" || verb == "inventory") { player.showInventory(); }
        else if (verb == "status") { player.showStatus(); }
        else if (verb == "help")  {
            std::cout << "Commands: look, go <dir>, take <item>, inv, status, quit\n";
        }
        else if (verb == "quit" || verb == "exit") { running = false; }
        else { std::cout << "Unknown command. Type 'help' for commands.\n"; }
    }

    void run() {
        std::cout << "=====================================\n";
        std::cout << "   C++ Text Adventure by Silas Chalwe\n";
        std::cout << "=====================================\n";
        std::string playerName;
        std::cout << "Enter your name: ";
        std::cin >> playerName;
        std::cin.ignore();
        player.name = playerName;
        std::cout << "Welcome, " << player.name << "! Type 'help' for commands.\n";
        look();
        while (running) {
            std::cout << "\n> ";
            std::string cmd;
            if (!std::getline(std::cin, cmd)) break;
            if (!cmd.empty()) processCommand(cmd);
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
