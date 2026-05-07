#include <iostream>
#include <vector>
#include <fstream> 
#include "json.hpp" //JSON parsing library for Mordern C++

using json = nlohmann::json; //For convinience

class Task{ //Task class to hold each task with given properties
public:
    int id;
    std::string description;
    std::string status;
    std::string createdAt;
    std::string updatedAt;
};


void loader(std::vector<Task>& list){ //Reads the file holding the tasks and puts it into the vector : list
    std::ifstream file("taskList.json");

    //If the file doesn't exist, stop the function
    if (!file.is_open()) {
        return; 
    }

    //Created an empty JSON-array to hold the file
    json j_array;

    //Checking if the file is empty or not and stopping the function if it is
    if (file.peek() == std::ifstream::traits_type::eof()) {
        return;
    }

    //Parsing the file into the array
    file >> j_array;
    for (int i = 0; i < j_array.size(); i++) {
        Task t;
        t.id = j_array[i]["id"];
        t.description = j_array[i]["description"];
        t.status = j_array[i]["status"];
        t.createdAt = j_array[i]["createdAt"];
        t.updatedAt = j_array[i]["updatedAt"];
        
        //pushing the Task objects to the list
        list.push_back(t);
    }
    
    file.close();
}

void saver(const std::vector<Task>& list) { //This function saves all the changes into the file
    json j_array = json::array();

    for (int i = 0; i < list.size(); i++) {
        j_array.push_back({
            {"id", list[i].id},
            {"description", list[i].description},
            {"status", list[i].status},
            {"createdAt", list[i].createdAt},
            {"updatedAt", list[i].updatedAt}
        });
    }

    std::ofstream file("taskList.json");
    file << j_array.dump(4);
    file.close();
}

void add(std::string input, int index, std::vector<Task>& list){ //Add tasks to the list & JSON file
    std::string desc;
    std::string status;
    std::string rn;
    int size = list.size();
    time_t timestamp;

    time(&timestamp);
    rn = ctime(&timestamp); //Getting the time when the task is being added

    desc = input.substr(index + 1);

    //Checking for edge case
    if (desc.empty()){
        std::cout << "No task given";
        return;
    }

    std::cout << "There are 3 status : \n1.to-do \n2. in-progress \n3. done \n\nGive a status to your task \n>>>> ";
    std::cin >> status;
    std::cin.ignore(10000, '\n'); //Tells the compiler to ignore the <Enter> key pressed by the user
                                  //while providing input

    Task task{(size + 1), desc, status, rn, rn};
    list.push_back(task);
}

void del(std::string input, int index, std::vector<Task>& list){//This function erases tasks from the list & JSON file
    if(list.empty()){
        std::cout << "Your list is empty.";
        return;
    }

    int id;
    int size = list.size();

    id = std::stoi(input.substr(index + 1));

    for(int i = 0; i < size; i++){
        if(id == (list[i].id)){
            list.erase(list.begin() + i);
            break;
        }
    }
}

void display(std::string input, int index, std::vector<Task>& list){//This function displays tasks
    if(list.empty()){
        std::cout << "Your list is empty.";
        return;
    }

    std::string status;

    status = input.substr(index + 1);
    if(!(status.empty())){//Displays only the tasks with the given status
        status.pop_back();
        for(int i = 0; i < list.size(); i++){
            if(status == list[i].status){
                std::cout << (i + 1) << ". " << list[i].description << "\n";
             }
        }
    }
    else{//If no status given then all tasks are displayed
        for(int i = 0; i < list.size(); i++){
            std::cout << (i + 1) << ". " << list[i].description << "( " << list[i].status << " )" << "\n";
        }
    }
}

void update(std::string input, int index, std::vector<Task>& list){//This upadates the status of a task
    input = input.substr(index + 1);
    index = input.find(" ");

    time_t timestamp;
    std::string rn;
    int id;
    std::string new_status;
    
    time(&timestamp);
    rn = ctime(&timestamp);

    id = std::stoi(input.substr(0, index));
    new_status = input.substr(index + 1);

    for(int i = 0; i < list.size(); i++){
        if(id == list[i].id){
            list[i].status = new_status;
            list[i].updatedAt = rn;
        }
    }
}

int main(){
    std::vector<Task> list;
    //getting the list of tasks (if exists)
    loader(list);

    bool running = true;
    std::string command;
    std::string input;
    int command_index;
    std::string commands[] = {"add", "exit", "delete", "display", "update", "help"};
    int amt_of_commands = sizeof(commands)/sizeof(commands[0]);
    int index;

    std::cout << "*******CLI To Do List*******\n";
    std::cout << "Running...\n";
    while(running){//App loop
        std::cout << ">>>> ";
        std::getline(std::cin, input);
        input += " ";
        index = input.find(" ");
        command = input.substr(0, index);
        for (int i = 0; i < amt_of_commands; i++) {
            if (commands[i] == command){
                command_index = i;
            }
        }
        switch(command_index){
            case 0:
            add(input, index, list);
            break;
            case 1:
            running = false;
            break;
            case 2:
            del(input, index, list);
            break;
            case 3:
            display(input, index, list);
            break;
            case 4:
            update(input, index, list);
            break;
            case 5:
            std::cout << "These are the commands : \n";
            for(int i = 0; i < (sizeof(commands) / sizeof(commands[0])); i++){
                std::cout << (i + 1) << ". " << commands[i] << "\n";
            }
            break;
            default:
            std::cout << "Invalid Command \nTry the command \"help\"";
        }
    }

    std::cout << "****************************";
    saver(list);

    return 0;
}