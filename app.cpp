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

int add(std::string input, int index, std::vector<Task>& list){
    std::string desc;
    std::string status;
    std::string rn;
    int size = list.size();
    time_t timestamp;

    time(&timestamp);
    rn = ctime(&timestamp);

    desc = input.substr(index + 1);
    if (desc.empty()){
        std::cout << "No task given";
        return 0;
    }

    std::cout << "There are 3 status : \n1.to-do \n2. in-progress \n3. done \n\nGive a status to your task \n>>>> ";
    std::cin >> status;
    std::cin.ignore(10000, '\n');

    Task task{(size + 1), desc, rn, rn};
    std::cout << task.id;
    list.push_back(task);
    return 0;
}

void del(std::string input, int index, std::vector<Task>& list){
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

int main(){

    std::vector<Task> list;
    bool running = true;
    std::string command;
    std::string input;
    int command_index;
    std::string commands[] = {"add", "exit", "delete"};
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
            case 1:
            running = false;
            break;
            case 2:
            del(input, index, list);
            break;
            default:
            std::cout << "Invalid Command\n";
        }
    }

    std::cout << "****************************";

    return 0;
}