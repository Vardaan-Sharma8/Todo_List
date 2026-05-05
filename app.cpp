#include <iostream>
#include <vector>

class Task{
public:
    int id;
    std::string description;
    std::string status;
    std::string createdAt;
    std::string updatedAt;
};

void add(std::string input, int index, std::vector<Task>& list){
    std::string desc;
    std::string status;
    std::string rn;
    time_t timestamp;
    time(&timestamp);
    rn = ctime(&timestamp);
    desc = input.substr(index + 1);
    int size = list.size();
    std::cout << "There are 3 status : \n1.to-do \n2. in-progress \n3. done \n\nGive a status to your task \n>>>> ";
    std::cin >> status;
    std::cin.ignore(10000, '\n');
    Task task{(size + 1), desc, rn, rn};
    list.push_back(task);
}

int main(){

    std::vector<Task> list;
    bool running = true;
    std::string command;
    std::string input;
    int command_index;
    std::string commands[] = {"add"};
    int amt_of_commands = sizeof(commands)/sizeof(commands[0]);
    int index;

    std::cout << "*******CLI To Do List*******\n";
    std::cout << "Running...\n";
    while(running){
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
            default:
            std::cout << "Invalid Command\n";
        }
    }

    std::cout << "*****************************************";

    return 0;
}