#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==========================================
// 1. INVENTORY & ITEM SYSTEM (Composition)
// ==========================================
class Item {
private:
    string name;
    int healValue;
public:
    Item(string n, int h) : name(n), healValue(h) {}
    string getName() const { return name; }
    int getHealValue() const { return healValue; }
};

class Inventory {
private:
    vector<Item> items;
public:
    void addItem(const Item& item) {
        items.push_back(item);
        cout << ">> Picked up: " << item.getName() << "\n";
    }
    
    bool hasItems() const { return !items.empty(); }
    
    void showInventory() const {
        if (items.empty()) {
            cout << "[Inventory is empty]\n";
            return;
        }
        cout << "--- Your Inventory ---\n";
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i].getName() << "\n";
        }
    }

    Item useItem(int index) {
        Item selected = items[index];
        items.erase(items.begin() + index);
        return selected;
    }
    
    size_t getSize() const { return items.size(); }
};

// ==========================================
// 2. CHARACTER HIERARCHY (Inheritance & Polymorphism)
// ==========================================
class Character {
protected:
    string name;
    int health;
    int maxHealth;
    int baseDamage;
public:
    Character(string n, int hp, int dmg) : name(n), health(hp), maxHealth(hp), baseDamage(dmg) {}
    virtual ~Character() {} // Virtual destructor is critical for polymorphism

    // Pure Virtual Function - makes this class abstract
    virtual void takeTurn(Character& target) = 0; 

    void receiveDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
        cout << name << " takes " << amount << " damage! (HP: " << health << "/" << maxHealth << ")\n";
    }

    bool isAlive() const { return health > 0; }
    string getName() const { return name; }
    int getHealth() const { return health; }
    
    void heal(int amount) {
        health += amount;
        if (health > maxHealth) health = maxHealth;
        cout << name << " healed for " << amount << " HP! (HP: " << health << "/" << maxHealth << ")\n";
    }
};

// --- The Player Class ---
class Player : public Character {
private:
    Inventory inventory; // Composition
public:
    Player(string n) : Character(n, 100, 20) {
        // Start with a couple of items
        inventory.addItem(Item("Health Potion", 30));
    }

    Inventory& getInventory() { return inventory; }

    // Overriding the pure virtual function
    void takeTurn(Character& target) override {
        cout << "\n--- " << name << "'s Turn ---\n";
        cout << "1. Attack\n2. Open Inventory\nChoose action: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int dmg = baseDamage + (rand() % 10); // Random variance
            cout << name << " swings their sword!\n";
            target.receiveDamage(dmg);
        } 
        else if (choice == 2) {
            inventory.showInventory();
            if (!inventory.hasItems()) {
                cout << "You have no items! You waste your turn looking at your empty pockets.\n";
                return;
            }
            cout << "Choose item number to use (0 to cancel): ";
            int itemChoice;
            cin >> itemChoice;
            
            if (itemChoice > 0 && itemChoice <= static_cast<int>(inventory.getSize())) {
                Item used = inventory.useItem(itemChoice - 1);
                heal(used.getHealValue());
            } else {
                cout << "Invalid choice/Cancelled. You lost your opening!\n";
            }
        }
    }
};

// --- The Abstract Enemy Class ---
class Enemy : public Character {
public:
    Enemy(string n, int hp, int dmg) : Character(n, hp, dmg) {}
};

// --- Concrete Enemy Types (Polymorphic Behaviors) ---
class Goblin : public Enemy {
public:
    Goblin() : Enemy("Sneaky Goblin", 40, 10) {}
    
    void takeTurn(Character& target) override {
        cout << "\n" << name << " cackles and lunges at you!\n";
        int dmg = baseDamage + (rand() % 5);
        target.receiveDamage(dmg);
    }
};

class Sorcerer : public Enemy {
public:
    Sorcerer() : Enemy("Dark Sorcerer", 60, 15) {}
    
    void takeTurn(Character& target) override {
        cout << "\n" << name << " casts a shadow bolt!\n";
        int dmg = baseDamage + (rand() % 12);
        target.receiveDamage(dmg);
    }
};

// ==========================================
// 3. GAME ENGINE / CONTROLLER
// ==========================================
class GameEngine {
private:
    Player player;
    int roomsCleared;
public:
    GameEngine(string playerName) : player(playerName), roomsCleared(0) {}

    void startAdventure() {
        cout << "Welcome, " << player.getName() << " to the Endless Dungeon!\n";
        
        while (player.isAlive()) {
            roomsCleared++;
            cout << "\n=========================================\n";
            cout << "ENTERING ROOM NUMBER " << roomsCleared << "\n";
            cout << "=========================================\n";

            // Polymorphically spawn a random enemy
            Enemy* currentEnemy = nullptr;
            int enemyType = rand() % 2;
            if (enemyType == 0) currentEnemy = new Goblin();
            else currentEnemy = new Sorcerer();

            cout << "A wild " << currentEnemy->getName() << " blocks your path!\n";

            // Battle Loop
            while (player.isAlive() && currentEnemy->isAlive()) {
                player.takeTurn(*currentEnemy);
                if (currentEnemy->isAlive()) {
                    currentEnemy->takeTurn(player);
                }
            }

            // Post-Battle Cleanup
            if (player.isAlive()) {
                cout << "\nYou defeated the " << currentEnemy->getName() << "!\n";
                // Random item drop chance
                if (rand() % 2 == 0) {
                    player.getInventory().addItem(Item("Super Potion", 50));
                }
                delete currentEnemy; // Free memory safely
            } else {
                cout << "\nYou fell in battle... Game Over.\n";
                cout << "You cleared " << roomsCleared - 1 << " rooms.\n";
                delete currentEnemy;
                break;
            }
        }
    }
};

// ==========================================
// 4. MAIN ENTRY POINT
// ==========================================
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random numbers
    
    string name;
    cout << "Enter your hero's name: ";
    getline(cin, name);
    
    GameEngine game(name);
    game.startAdventure();
    
    return 0;
}