// Stack and Queue
// Uğurcan ERDOĞAN 21827373

#include <iostream>     // Importing the necessary library files
#include "string"
#include <sstream>
#include <bits/stdc++.h>
#include "Stack.h"
#include "Queue.h"
#include "Package.h"
#include "Truck.h"
#include "LinkedList.h"

ifstream destFileObj;   // Creating input and output object
ifstream packageFileObj;
ifstream truckFileObj;
ifstream missionFileObj;
ofstream resultFileObj;

struct City {
    string cityName;
    Stack<Package> packageStack;
    Queue<Package> truckQueue;

    void setCityName(const string& name){
        cityName = name;
    }
    void setPackageStack(const Stack<Package>& stack){
        packageStack = stack;
    }
    void setTruckQueue(const Queue<Package>& queue){
        truckQueue = queue;
    }
    string getCityName(){
        return cityName;
    }
    Stack<Package>& getPackageStack(){
        return packageStack;
    }
    Queue<Package>& getTruckQueue(){
        return truckQueue;
    }
};

// Split function to split command line according to given delimeter
vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

// Read commands method to read all files and execute the operations
void readCommands(){
    vector<City> destinations;
    string destLine;
    string packageLine;
    string truckLine;
    string missionsLine;

    while (getline(destFileObj,destLine)){  // Reading destinations file
        struct City p1;
        p1.setCityName(destLine);
        destinations.push_back(p1);
    }
    while (getline(packageFileObj,packageLine)){    // Reading packages file
        vector<string> dests;
        istringstream iss(packageLine);
        string token;
        while(getline(iss, token, ' ')){
            dests.push_back(token);
        }
        for(auto &i:destinations){
            if (i.getCityName() == dests.at(1)){        // Pushing packages to specific city stack
                Package package;
                package.setName(dests.at(0));
                i.packageStack.push(package);
            }
        }
    }
    while (getline(truckFileObj,truckLine)){        // Reading trucks file
        vector<string> trucks;
        istringstream iss(truckLine);
        string token;
        while(getline(iss, token, ' ')){
            trucks.push_back(token);
        }
        for(auto &i:destinations){
            if (i.getCityName() == trucks.at(1)){       // Enqueuing trucks to specific city queue
                Truck truck;
                truck.setName(trucks.at(0));
                truck.setPower(stod(trucks.at(2)));
                i.truckQueue.enqueue(truck);
            }
        }
    }
    while (getline(missionFileObj,missionsLine)){   // Reading missions file
        LinkedList<Package> linkedlist;
        vector<string> missions;
        istringstream iss(missionsLine);
        string token;
        string indexes;
        string indec;

        while(getline(iss, token, '-')){    // Splitting all strings in the mission line
            missions.push_back(token);
        }
        for (auto & destination : destinations){                // Operations of starting city
            if(destination.cityName == missions.at(0)){
                Truck truck;
                destination.truckQueue.getFront(truck);
                linkedlist.insert(truck);
                destination.truckQueue.dequeue();
                for (int i = 0; i < stoi(missions.at(3)); i++){
                    Package temp;
                    destination.packageStack.getTop(temp);
                    linkedlist.insert(temp);
                    destination.packageStack.pop();
                }
            }
        }
        for (auto & destination : destinations){                // Operations of midway city
            if (destination.getCityName() == missions.at(1)){
                for (int i = 0; i < stoi(missions.at(4)); i++){
                    Package temp;
                    destination.packageStack.getTop(temp);
                    linkedlist.insert(temp);
                    destination.packageStack.pop();
                }
                indexes = missions.at(5);
                vector<string> indices = split(indexes, ',');
                vector<string> unsortedInd = split(indexes, ',');
                sort(indices.begin(),indices.end());
                map<int,Package> paketler;
                for (int i = indices.size()-1;i>=0;i--){
                    Package temp;
                    temp = linkedlist.getItem(stoi(indices.at(i)));
                    paketler[stoi(indices.at(i))] = temp;
                }
                for (int i = 0; i < unsortedInd.size(); i++) {
                    destination.packageStack.push(paketler[stoi(unsortedInd.at(i))]);
                }
            }
        }
        for (auto & destination : destinations){                // Operations of target city
            if (destination.getCityName() == missions.at(2)){
                vector<string> indices;
                for (int i = linkedlist.size()-2;i >=0;i--) {
                    Package temp;
                    temp = linkedlist.getItem(0);
                    destination.packageStack.push(temp);
                }
                Package truck;
                truck = linkedlist.getTruck();
                destination.truckQueue.enqueue(truck);
            }
        }
    }
    for (auto & destination : destinations){            // Writing to result file
        cout << destination.getCityName() << endl;
        int size = destination.packageStack.size();
        int truckSize = destination.truckQueue.size();
        cout << "Packages:" << endl;
        for(int i = size; i > 0;i--){
            Package temp;
            destination.packageStack.getTop(temp);
            cout << temp.getName() << endl;
            destination.packageStack.pop();
        }
        cout << "Trucks:" << endl;
        for(int i = truckSize; i > 0; i--){
            Truck temp;
            destination.truckQueue.getFront(temp);
            cout << temp.getName() << endl;
            destination.truckQueue.dequeue();
        }
        cout << "-------------" << endl;
    }

}

int main(int argc, char** argv) {
    freopen("result.txt","w",stdout);   // method for writing to output file.
    destFileObj.open(argv[1]);                      // opening destination file.
    packageFileObj.open(argv[2]);                   // opening packages file.
    truckFileObj.open(argv[3]);                     // opening trucks file.
    missionFileObj.open(argv[4]);                   // opening missions file.
    resultFileObj.open(argv[5],ios::out);

    readCommands();                         // MAIN FUNCTION

    destFileObj.close();                  //
    packageFileObj.close();               //
    truckFileObj.close();                 //  Closing all files.
    missionFileObj.close();               //
    resultFileObj.close();                //
    return 0;
}
