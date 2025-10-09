#include <iostream>
#include <vector>
using namespace std;

string listMenu(string choice);
void addTask(vector<string>& list, string task);
void listOfTasks(const vector<string>& list);
void markTask(vector<string>& list, int index);
void showTasks(const vector<string>& list);


int main(){
	int index;
	string choice;
	string task;
	vector<string> list;
	while(true){
		choice = listMenu(choice);
		if(choice == "1"){
			addTask(list, task);
		}
		else if(choice == "2"){
			markTask(list, index);
		}
		else if(choice == "3"){
			showTasks(list);
		}
		else if(choice == "4"){
			break;
		}
		else{
			cout << "Invalid response, Try again.\n\n";
		}
	}
	return 0;
}


string listMenu(string choice){
	cout << "\t<======TO-DO LIST======>\n";
	cout << "1. Add a new task\n";
	cout << "2. Mark a task as completed\n";
	cout << "3. See current tasks\n";
	cout << "4. Exit\n";
	cout << "----------------------------\n";
	cout << "choose your choice:";
	cin >> choice;
	cin.ignore();
	cout << endl;
	return choice;
}
void addTask(vector<string>& list, string task){
	cout << "Enter your task:\n";
		getline(cin, task);
		list.push_back(task);
		cout << "Task successfully added\n\n";
}
void listOfTasks(const vector<string>& list){
	for(int i = 0; i < list.size(); i++){ 
	cout << i + 1 << ". " << list[i] << endl;
	}
}
void markTask(vector<string>& list, int index){
	if(list.empty()){ 
		cout << "Oops, there are no tasks to be marked\n";
		cout << endl;
	}
	else{
		listOfTasks(list);
		cout << "Choose the task to be marked:";
		cin >> index;
		cin.ignore();
		if(index < 1 || index > list.size()){
			cout << "Oops, task doesn't exist\n";
		}
		else{
			list[index-1] += ". (Done)";
			cout << "Task has been successfully marked\n\n";
		}
	}
}
void showTasks(const vector<string>& list){
	if(list.empty()){ 
		cout << "Oops, there are no tasks\n";
	}
	else{
		cout << "Following is your list of tasks:\n";
		listOfTasks(list);
	}
	cout << endl;
}