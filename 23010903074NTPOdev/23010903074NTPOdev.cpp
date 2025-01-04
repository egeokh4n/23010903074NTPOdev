#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Ana Karakter Sınıfı
class Character {
protected:
    string name; // Karakterin adı
    int health; // Karakterin sağlığı
    int attackPower; // Karakterin saldırı gücü

public:
    Character(const string& name, int health, int attackPower)
        : name(name), health(health), attackPower(attackPower) {}

    virtual void attack(Character& target) = 0; // Saldırı

    void takeDamage(int damage) {
        health -= damage; // Alınan hasar kadar sağlık azaltılır
        if (health < 0) health = 0;
    }

    bool isAlive() const {
        return health > 0; // Karakter hayatta mı?
    }

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }
};

// Oyuncu Sınıfı
class Player : public Character {
public:
    Player(const string& name, int health, int attackPower)
        : Character(name, health, attackPower) {}

    void attack(Character& target) override {
        cout << name << ", " << target.getName() << " karakterine " << attackPower << " zarar verdi!\n";
        target.takeDamage(attackPower);
    }

    void displayArt() const {
        // Karakter Görselleri
        if (name == "Kedi") {
            cout << "   (\\_/ )\n";
            cout << "   ( •_•)\n";
            cout << "  <|> <|>\n";
        }
        else if (name == "Kopek") {
            cout << "   /\\_/\\\n";
            cout << "  ( •_• )\n";
            cout << "  <|> <|>\n";
        }
        else if (name == "Tavsan") {
            cout << "   (\\_/ )\n";
            cout << "   ( o.o )\n";
            cout << "   <|> <|>\n";
        }
    }
};

// Düşman Sınıfı
class Enemy : public Character {
public:
    Enemy(const string& name, int health, int attackPower)
        : Character(name, health, attackPower) {}

    void attack(Character& target) override {
        cout << name << ", " << target.getName() << " karakterine " << attackPower << " zarar verdi!\n";
        target.takeDamage(attackPower);
    }

    void displayArt() const {
        // Düşman Görselleri
        if (name == "Cuce") {
            cout << "   (\\_/ )\n";
            cout << "   ( •_• )\n";
            cout << "   /   \\ \n";
        }
        else if (name == "Ork") {
            cout << "   /\\_/\\\n";
            cout << "  ( o.o )\n";
            cout << "   > ^ <\n";
        }
        else if (name == "Troll") {
            cout << "   (\\_/ )\n";
            cout << "   ( •_• )\n";
            cout << "   <(   )>\n";
        }
        else if (name == "Kus") {
            cout << "     \\  \\/  /\n";
            cout << "      ( o.o )\n";
            cout << "       (   ) \\\n";
            cout << "        \\ /   \\\n";
            cout << "         |     \\\n";
        }
        else if (name == "Kedi") {
            cout << "   (\\_/ )\n";
            cout << "   ( o.o )\n";
            cout << "   > ^ <\n";
        }
        else if (name == "Tavuk") {
            cout << "   (\\_/ )\n";
            cout << "   ( o.o )\n";
            cout << "   / < > \\ \n";
            cout << "   > ^ < \n";
        }
    }
};

// Oyun Sınıfı
class Game {
private:
    Player player; // Oyuncu
    vector<Enemy> enemies; // Düşman karakterlerin listesi

    void displayCharacterMenu() {
        // Karakter seçim menüsü
        cout << "Karakterini sec:\n";
        cout << "1. Kedi\n";
        cout << "   (\\_/ )\n";
        cout << "   ( •_•)\n";
        cout << "  <|> <|>\n\n";
        cout << "2. Kopek\n";
        cout << "   /\\_/\\\n";
        cout << "  ( •_• )\n";
        cout << "  <|> <|>\n\n";
        cout << "3. Tavsan\n";
        cout << "   (\\_/ )\n";
        cout << "   ( o.o )\n";
        cout << "   <|> <|>\n";
    }

    void selectCharacter() {
        int choice;
        while (true) {
            displayCharacterMenu();
            cout << "Seciminizi yapin (1, 2 veya 3): ";
            cin >> choice;

            if (choice == 1) {
                player = Player("Kedi", 80, 60); // Oyuncu karakteri oluşturma
                cout << "Kedi'yi sectiniz!\n";
                break;
            }
            else if (choice == 2) {
                player = Player("Kopek", 100, 80);
                cout << "Kopek'i sectiniz!\n";
                break;
            }
            else if (choice == 3) {
                player = Player("Tavsan", 50, 40);
                cout << "Tavsan'i sectiniz!\n";
                break;
            }
            else {
                cout << "Gecersiz secim. Lutfen tekrar deneyin.\n";
            }
        }
    }

    void clearScreen() {
        // Ekranı temizler
        cout << "\033[2J\033[1;1H";
    }

public:
    Game() : player("", 0, 0) {
        // Düşman karakterlerin oluşturulması
        enemies.push_back(Enemy("Cuce", 30, 10));
        enemies.push_back(Enemy("Ork", 40, 20));
        enemies.push_back(Enemy("Troll", 50, 15));
        enemies.push_back(Enemy("Kus", 30, 12));
        enemies.push_back(Enemy("Kedi", 40, 18));
        enemies.push_back(Enemy("Tavuk", 30, 10));
    }

    void start() {
        cout << "Oyuna hos geldiniz!\n\n";
        selectCharacter(); // Oyuncunun karakterini seçmesi

        while (player.isAlive() && !enemies.empty()) {
            displayStatus(); // Oyuncu ve düşmanların durumunu göster

            int choice = getPlayerChoice();
            if (choice > 0 && choice <= enemies.size()) {
                clearScreen();
                cout << player.getName() << ", " << enemies[choice - 1].getName() << " ile savasiyor!\n";
                displayFightArt(enemies[choice - 1]);

                player.attack(enemies[choice - 1]);

                if (!enemies[choice - 1].isAlive()) {
                    cout << enemies[choice - 1].getName() << " yenildi!\n";
                    enemies.erase(enemies.begin() + (choice - 1));
                }
            }
            else {
                cout << "Gecersiz secim.\n";
                continue;
            }

            if (!enemies.empty()) {
                Enemy& currentEnemy = enemies[rand() % enemies.size()];
                if (currentEnemy.isAlive()) {
                    currentEnemy.attack(player); // Düşman saldırısı
                }
            }
        }

        // Oyunun son durumu
        if (player.isAlive()) {
            cout << "Tebrikler, " << player.getName() << "! Tum dusmanlari yendiniz!\n";
        }
        else {
            cout << "Oyun Bitti! " << player.getName() << " yenildi.\n";
        }
    }

    void displayStatus() {
        // Oyuncu ve düşmanların durumunu ekrana yazdır
        cout << "\nOyuncu: " << player.getName() << " (Saglik: " << player.getHealth() << ")\n";
        cout << "Dusmanlar:\n";
        for (size_t i = 0; i < enemies.size(); ++i) {
            cout << i + 1 << ". " << enemies[i].getName() << " (Saglik: " << enemies[i].getHealth() << ")\n";
        }
    }

    int getPlayerChoice() {
        // Oyuncunun saldıracağı düşmanı seçmesi
        cout << "\nSaldirmak istediginiz dusmani secin (1-" << enemies.size() << "): ";
        int choice;
        cin >> choice;
        return choice;
    }

    void displayFightArt(const Enemy& enemy) {
        cout << "\n";
        player.displayArt();
        cout << "          vs          \n";
        enemy.displayArt();
        cout << "\n";
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    Game game;
    game.start(); // Oyunu başlat

    return 0;
}
