// ProiectDeExamenFinal.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // biblioteca pt a genera numere aleatori
#include <ctime> // pt date 
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

// Clasa de Bază pentru Personaj
class Character
{
public:
    std::string name;
    std::string characterClass;
    int health;
    int attackPower;
    std::vector<std::string> inventory;

    Character(std::string name, std::string characterClass, int health, int attackPower)
        : name(name), characterClass(characterClass), health(health), attackPower(attackPower) {}

    void addToInventory(std::string item) {
        inventory.push_back(item);
        std::cout << "Ai obținut: " << item << std::endl;
    }

    void displayInventory() {
        std::cout << "Inventar: ";
        for (const auto& item : inventory) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Functii pentru Scenarii
void introScene() {
    
    PlaySound(TEXT("C:/Users/mm/OneDrive/Desktop/IT Scool/ProiectDeExamenFinal/ProiectDeExamenFinal/x64/Debug/Main_Menu.wav"), NULL, SND_FILENAME | SND_ASYNC);

    std::cout << "Bine ai venit in lumea Gothic!" << std::endl;
    std::cout << "Esti gata sa incepi aventura? (da/nu): ";
}

Character setupPlayer() {

    std::string name;
    std::string characterClass;
    std::cout << "Introdu numele jucatorului: ";
    std::cin >> name;

    std::cout << "Alege clasa: (vrajitor/luptator/bandit): ";
    std::cin >> characterClass;

    if (characterClass == "vrajitor") {
        std::cout << "Ai ales sa fii un puternic vrajitor!" << std::endl;
        return Character(name, characterClass, 100, 65);
    }
    else if (characterClass == "luptator") {
        std::cout << "Ai ales sa fii un curajos luptator!" << std::endl;
        return Character(name, characterClass, 150, 55);
    }
    else if (characterClass == "bandit") {
        std::cout << "Ai ales sa fii un agil bandit!" << std::endl;
        return Character(name, characterClass, 120, 50);
    }
    else {
        std::cout << "Alegere invalida. Vei fi setat automat ca bandit." << std::endl;
        return Character(name, "bandit", 120, 50);
    }

    PlaySound(NULL, 0, 0);
   
}

void crossRoadsScene() 
{

    PlaySound(TEXT("C:/Users/mm/OneDrive/Desktop/IT Scool/ProiectDeExamenFinal/ProiectDeExamenFinal/x64/Debug/Exploring.wav"), NULL, SND_FILENAME | SND_ASYNC);

    std::cout << "Te afli la o rascruce de drumuri. Poti alege sa mergi spre:\n";
    std::cout << "1. Padure\n";
    std::cout << "2. Pestera\n";
    std::cout << "3. Sat\n";
    std::cout << "Alege un drum (1/2/3): ";

}

void chestScene(Character& player) {
    std::string choice;
    std::cout << "Ai gasit un cufar pe drum. Vrei sa-l deschizi? (da/nu): ";
    std::cin >> choice;

    if (choice == "da") {
        if (player.characterClass == "vrajitor") {
            player.addToInventory("Toiag Magic");
        }
        else if (player.characterClass == "luptator") {
            player.addToInventory("Sabie");
        }
        else if (player.characterClass == "bandit") {
            player.addToInventory("Pumnal");
        }
    }

    PlaySound(NULL, 0, 0);

    
}


void battleScene(Character& player) 
{
    
    PlaySound(TEXT("C:/Users/mm/OneDrive/Desktop/IT Scool/ProiectDeExamenFinal/ProiectDeExamenFinal/x64/Debug/BattleFinal.wav"), NULL, SND_FILENAME | SND_ASYNC);


    std::string enemies[] = { "Orc", "Goblin", "Troll" };
    std::string enemy = enemies[rand() % 3];
    int enemyHealth = 110;
    int enemyAttack = 40;

    std::cout << "Ai intalnit un " << enemy << "! Pregateste-te de lupta!\n";

    while (player.health > 0 && enemyHealth > 0) {
        std::cout << "Ataci " << enemy << " cu " << player.attackPower << " putere.\n";
        enemyHealth -= player.attackPower;
        if (enemyHealth <= 0) {
            std::cout << "Ai invins " << enemy << "!\n";
            return;
        }

        std::cout << enemy << " te ataca cu " << enemyAttack << " putere.\n";
        player.health -= enemyAttack;
        if (player.health <= 0) {
            std::cout << "Ai fost invins de " << enemy << ". Joc terminat.\n";
            exit(0);
        }
    }


    
    PlaySound(NULL, 0, 0);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::string choice;
    introScene();
    std::cin >> choice;

    if (choice != "da") {
        std::cout << "Poate altadata! La revedere!\n";
        return 0;
    }

    Character player = setupPlayer();
    crossRoadsScene();
    int path;
    std::cin >> path;

    switch (path) {
    case 1:
        std::cout << "Ai ales sa mergi spre Padure.\n";
        break;
    case 2:
        std::cout << "Ai ales sa mergi spre Pestera.\n";
        break;
    case 3:
        std::cout << "Ai ales sa mergi spre Sat.\n";
        break;
    default:
        std::cout << "Alegere invalida. Vei merge automat spre Padure.\n";
        path = 1;
        break;
    }

    chestScene(player);
    player.displayInventory();


    battleScene(player);
    std::cout << "Ai ajuns la destinatie. Felicitari!\n";
    int exit;
    std::cout << "Pentru iesire introduceti o cifra de la tastatura si apasati enter \n";
    std::cin >> exit;

    return 0;
}
