#include "player.h"
#include "cell.h"

using namespace std;

Player::Player(Colour pColour) {
    this->colour = pColour;
    this->completedCriteria[Progress::Assignment] = {};
    this->completedCriteria[Progress::Midterm] = {};
    this->completedCriteria[Progress::Exam] = {};
    this->completedGoals = {};
    this->resources[ResourceType::Caffeine] = 0;
    this->resources[ResourceType::Lab] = 0;
    this->resources[ResourceType::Lecture] = 0;
    this->resources[ResourceType::Study] = 0;
    this->resources[ResourceType::Tutorial] = 0;
}

void Player::addResources(ResourceType res, int amount) {
    auto key = resources.find(res); 
    if (key == resources.end()) {
        throw "invalid resource";
    } else {
        resources.at(res) += amount;
    }
}

void Player::removeResource(ResourceType res, int amount) {
    auto key = resources.find(res); 
    if (key == resources.end()) {
        throw "invalid resource";
    } else {
        resources.at(res) -= amount;
    }
}

// care about distrubute resources and progress
void Player::notify(Subject<Phase> &notifier) {
    Phase currPhase = notifier.getPhase();
    if (currPhase.phase == TurnPhase::DistributeResourcesPlayer) {
        Progress cellProgress = currPhase.cellProgress;
        if (cellProgress == Progress::Assignment) {
            addResources(currPhase.resource, 1);
        } else if (cellProgress == Progress::Midterm) {
            addResources(currPhase.resource, 2);
        } else if (cellProgress == Progress::Exam) {
            addResources(currPhase.resource, 3);
        }
    } else if (currPhase.phase == TurnPhase::Progress) {
        if (currPhase.cellProgress == Progress::Assignment) {
            removeResource(ResourceType::Caffeine, 1);
            removeResource(ResourceType::Lab, 1);
            removeResource(ResourceType::Lecture, 1);
            removeResource(ResourceType::Tutorial, 1);
            addCriteria(currPhase.position, Progress::Assignment);
        } else if (currPhase.cellProgress == Progress::Midterm) {
            removeResource(ResourceType::Lecture, 2);
            removeResource(ResourceType::Study, 3);
            removeCriteria(currPhase.position, Progress::Assignment);
            addCriteria(currPhase.position, Progress::Midterm);
        } else if (currPhase.cellProgress == Progress::Exam) {
            removeResource(ResourceType::Caffeine, 3);
            removeResource(ResourceType::Lab, 2);
            removeResource(ResourceType::Lecture, 2);
            removeResource(ResourceType::Tutorial, 1);
            removeResource(ResourceType::Study, 2);
            removeCriteria(currPhase.position, Progress::Midterm);
            addCriteria(currPhase.position, Progress::Exam);
        }  else if (currPhase.cellProgress == Progress::Goals) {
            removeResource(ResourceType::Study, 1);
            removeResource(ResourceType::Tutorial, 1);
            addGoals(currPhase.position);
        }
    }
}

int Player::rollDice(bool loaded) {
    if (loaded) {
        int n;
        bool roll = true;
        while (roll) {
            cout << "Input a roll between 2 and 12: ";
            cin >> n;
            if (n < 2 || n > 12) {
                cout << "Invalid roll." << endl;
            } else {
                roll = false;
                return n;
            }
        }
    } else {
        srand(time(NULL));
        int dice1 = rand() % 6 + 1;
        srand(time(NULL));
        int dice2 = rand() % 6 + 1;
        return dice1 + dice2;
    }
}

map<ResourceType, int> Player::getResources() {
    return resources;
}

void Player::addGoals(int cellToAdd) {
    completedGoals.emplace_back(cellToAdd);
}

void Player::addCriteria(int cellToAdd, Progress cellProgress) {
    completedCriteria.at(cellProgress).emplace_back(cellToAdd);
}

void Player::setResource(ResourceType res, int amount) {
    auto key = resources.find(res);
    if (key == resources.end()) {
        throw "invalid resource";
    } else {
        resources.at(res) = amount;
    }
}

map<Progress, vector<int>> Player::getCriteria() {
    return completedCriteria;
}

vector<int> Player::getGoals() {
    return completedGoals;
}

bool Player::hasEnoughResources(Cell cell, string buildType) {
    if (buildType == "achieve") {
        if (resources.at(ResourceType::Study) >= 1 && resources.at(ResourceType::Tutorial) >= 1) {
            return true;
        } else {
            return false;
        }
    } else if (buildType == "complete") {
        if (resources.at(ResourceType::Caffeine) >= 1 && resources.at(ResourceType::Lab) >= 1 &&
            resources.at(ResourceType::Lecture) >= 1 && resources.at(ResourceType::Tutorial) >= 1) {
            return true;
        } else {
            return false;
        }
    } else if (buildType == "improve") {
        if (cell.getProgress() == Progress::Assignment) {
            if (resources.at(ResourceType::Lecture) >= 2 && resources.at(ResourceType::Study) >= 3) {
                return true;
            } else {
                return false;
            }
        } else if (cell.getProgress() == Progress::Midterm) {
            if (resources.at(ResourceType::Caffeine) >= 3 && 
                    resources.at(ResourceType::Lab) >= 2 && 
                    resources.at(ResourceType::Lecture) >= 2 && 
                    resources.at(ResourceType::Tutorial) >= 1 && 
                    resources.at(ResourceType::Study) >= 2) {
                        return true;
                    } else {
                        return false;
                    }
        } else if (cell.getProgress() == Progress::Exam) {
            throw "unupgradable";
        }
    } else {
        throw "invalid input";
    }
}

ResourceType Player::loseRandomResource(int amount) {
    vector<ResourceType> valuedResources = { ResourceType::Tutorial, ResourceType::Study, ResourceType::Caffeine, ResourceType::Lab, ResourceType::Lecture };
    vector<ResourceType> nonZeroResources = {};
    for (int i = 0; i < valuedResources.size(); i++) {
        if (resources.at(valuedResources.at(i)) > 0) {
            nonZeroResources.emplace_back(valuedResources.at(i));
        }
    }
    srand(time(NULL));
    int randRes = rand() % nonZeroResources.size();
    ResourceType resourceToRemove = nonZeroResources.at(randRes);
    removeResource(resourceToRemove, amount);
    return resourceToRemove;
}

Colour Player::getColour() { return colour; }

string Player::getColourStr() {
    if (colour == Colour::Blue) {
        return "Blue";
    } else if (colour == Colour::Red) {
        return "Red";
    } else if (colour == Colour::Orange) {
        return "Orange";
    } else if (colour == Colour::Yellow) {
        return "Yellow";
    } else if (colour == Colour::NoColour) {
        return "No Colour";
    }
}

void Player::printStatus() {
    cout << getColourStr() << " has " << to_string(getCriteriaCount()) << " course criteria, " << to_string(resources.at(ResourceType::Caffeine)) << " caffeines, " << to_string(resources.at(ResourceType::Lab)) << " labs, " << to_string(resources.at(ResourceType::Lecture)) << " lectures, " << to_string(resources.at(ResourceType::Study)) << " studies, and " << to_string(resources.at(ResourceType::Tutorial)) << " tutorials." << endl; 
}

void Player::printCompletions() {
    cout << getColourStr() << " has completed:" << endl;
    cout << completedCriteria.at(Progress::Assignment).size() << "1" << endl;
    cout << completedCriteria.at(Progress::Midterm).size() << "2" << endl;
    cout << completedCriteria.at(Progress::Exam).size() << "3" << endl;
}

string Player::getStatus() {
    string statusString = "";
    statusString = to_string(resources.at(ResourceType::Caffeine)) + " " + to_string(resources.at(ResourceType::Lab)) + " " + to_string(resources.at(ResourceType::Lecture)) + " " + to_string(resources.at(ResourceType::Study)) + " " + to_string(resources.at(ResourceType::Tutorial)) + " g " + to_string(completedGoals.size()) + " c " + getCriteriaPairs(); 
    return statusString;
}

string Player::getCriteriaPairs() {
    string critPairStr = "";
    for (auto &i : completedCriteria) {
        for (int m = 0; m < i.second.size(); m++) {
            critPairStr += i.second.at(m) + " " + progressToString(i.first);
        }
    }
    return critPairStr;
}

string Player::progressToString(Progress progress) {
    if (progress == Progress::None) {
        return "None";
    } else if (progress == Progress::Goals) {
        return "Goals";
    } else if (progress == Progress::Assignment) {
        return "Assignment";
    } else if (progress == Progress::Midterm) {
        return "Midterm";
    } else if (progress == Progress::Exam) {
        return "Exam";
    }
}

int Player::getResourceCount() {
    int sum = 0;
    for (auto &i : resources) {
        sum += i.second;
    }
    return sum;
}

int Player::getCriteriaCount() {
    vector<int> assnArr = completedCriteria.at(Progress::Assignment);
    vector<int> midArr = completedCriteria.at(Progress::Midterm);
    vector<int> examArr = completedCriteria.at(Progress::Exam);
    return assnArr.size() + midArr.size() + examArr.size();
}

void Player::removeCriteria(int criteriaToRemove, Progress progress) {
    vector<int> criteriaArr = completedCriteria.at(progress);
    for (int i = 0; i < criteriaArr.size(); i++) {
        if (criteriaArr.at(i) == criteriaToRemove) {
            criteriaArr.erase(criteriaArr.begin() + i);
        }
    }
}

