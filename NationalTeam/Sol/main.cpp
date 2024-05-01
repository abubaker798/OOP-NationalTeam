#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Player {
private:
    string name;
    int yearOfBirth;
    int height;
    int internationalGoals;
    string nationality;
public:

    //setters
    void setName(string name){this->name = name;}
    void setYearOfBirth(int yearOfBirth){this->yearOfBirth = yearOfBirth;}
    void setHeight(int height){this->height = height;}
    void setInternationalGoals(int internationalGoals){this->internationalGoals = internationalGoals;}
    void setNationality(string nationality){this->nationality = nationality;}

    //getters
    string getName() const { return this->name;}
    int getYearOfBirth() const  { return this->yearOfBirth;}
    int getInternationalGoals() const {return this->internationalGoals;}
    int getHeight(){return this->height;}

    string getNationality() const {return this->nationality;}
};

class NationalTeam {
private:
    string country;
    Player players[18];
    bool active[18];
    int size;
public:
    NationalTeam(string country = " ") {
        this->country = country;
        size = 0;
        for (int i = 0; i < 18; i++) active[i]=false;
    }

    bool addPlayer(const Player& player) {
        if(this->size >= 18) return false;

        this->players[this->size++] = player;
        this->active[this->size++] = true;
        return true;
    }

    bool removePlayer(string playerName) {
        for (int i = 0; i < this->size; i++) {
            if (players[i].getName() == playerName) {active[i] = false;return true;}
            return false;
        }
    }

    // to return total number of Players in the team
    int getNumOfallPlayers() const {return this->size;}

    // to return the average height of the team Players
    int avgHeight() const {
        int sum = 0;
        for (int i = 0; i < this->size; i++) {sum+=players[i].getYearOfBirth();}
        return sum/this->size;
    }

    // to return the oldest player object
    Player oldestPlayer() const {
        int oldestPlayer = players[0].getYearOfBirth();
        int i;
        for (i = 1; i < this->size; i++) {
            if (players[i].getYearOfBirth() > oldestPlayer){oldestPlayer = players[i].getYearOfBirth();}
        }return players[i];
    }

   // to return the youngest player object
   Player youngestPlayer() const {
        int youngestPlayer = players[0].getYearOfBirth();
        int i;
        for (i = 1; i < this->size; i++) {
            if (players[i].getYearOfBirth() < youngestPlayer){youngestPlayer = players[i].getYearOfBirth();}
        }return players[i];
    }

   // to return the average number of international goals per player in the team
   int avgIntGoals() const {
        int sum = 0;
        for (int i = 0; i < this->size; i++) {sum+=players[i].getInternationalGoals();}
        return sum/this->size;
    }

   // to return the player with the highest number of international goals
   Player highestIntGoals() const {
        int highestIntGoals = players[0].getInternationalGoals();
        int i = 1;
        for (i = 1; i < this->size; i++) {
            if (players[i].getInternationalGoals() > highestIntGoals){highestIntGoals = players[i].getInternationalGoals();}
        }return players[i];
    }

    string getCountry() const{return this->country;}

    // to output a team’s country and its allPlayers info.
    friend ostream &operator<<( ostream &output, NationalTeam &team) {
        output << "team’s country : " << team.getCountry();
        for (int i = 0 ; i < team.getNumOfallPlayers(); i++) {
            output << "player #" << i+1 << ": " << endl;
            output << "name: " << team.players[i].getName() << endl;
            output << "get year of birth: " << team.players[i].getYearOfBirth() << endl;
            output << "height: " << team.players[i].getHeight() << endl;
            output << "international goals: " << team.players[i].getInternationalGoals() << endl;
            output << "nationality: " << team.players[i].getNationality() << endl;
        }
        return output;
    }
};


Player* readallPlayersFromFile(ifstream& allPlayersInfo, Player *allPlayers, int size) {
    string strInfo; int intInfo, index = 0; Player player;

    allPlayers = new Player[size];

    while (getline(allPlayersInfo, strInfo)) {
        if(index >= size){break;}
        player.setName(strInfo);

        getline(allPlayersInfo, strInfo);
        intInfo = stoi(strInfo);
        player.setYearOfBirth(intInfo);

        getline(allPlayersInfo, strInfo);
        intInfo = stoi(strInfo);
        player.setHeight(intInfo);

        getline(allPlayersInfo, strInfo);
        intInfo = stoi(strInfo);
        player.setInternationalGoals(intInfo);

        getline(allPlayersInfo, strInfo);
        player.setNationality(strInfo);

        // to ignor sprated space in the file
        getline(allPlayersInfo, strInfo);

        allPlayers[index++] = player;
    }
    allPlayersInfo.close();
    return allPlayers;
}

void writeStatisticsToFile(ofstream& outFile, const NationalTeam& team) {
    outFile << "Country: " << team.getCountry() << endl;
    outFile << "# of Players: " << team.getNumOfallPlayers() << endl;
    outFile << "Avg. Height: " << team.avgHeight() << endl;
    outFile << "Oldest Player: " << team.oldestPlayer().getName() << endl;
    outFile << "Youngest Player: " << team.youngestPlayer().getName();
    outFile << "\t\tAge: " << (2024 - team.youngestPlayer().getYearOfBirth()) << endl;
    outFile << "Avg. Int. Goals: " << team.avgIntGoals() << endl;
    outFile << "Player with highest goals: " << team.highestIntGoals().getName();
    outFile << "\t\tGoals: " << team.highestIntGoals().getInternationalGoals() << endl;
    outFile.close();
}


