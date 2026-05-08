**CLI-Task-Tracker**
A fast ahh CLI tool to keep track of all your tasks.

"Never forget any task ever again !!!"

This tool is built entirely in C++ (My first project in this language), using JSON library for Mordern C++

*Start up the tool :*
```bash
g++ app.cpp -o app
./app
```

*Commands :*
`add <description>` : This will add a task of the given description.

`display` : This will display all the tasks in the list preceeded by their ID number.

`display <status>` : This will display all the tasks of the given status.

`delete <ID>` : This will delete the tasks of the given ID number.

`update <ID> <status>` : This will update the status of the given ID number task to the given status.