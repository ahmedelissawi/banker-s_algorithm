#include<iostream>
#include<vector>
#include<string>


using namespace std;

int no_of_processes, no_of_resources;
string* names_of_processes, * names_of_resources;


// the allocated matrix

//for 2d dynamic array

int** allocated;


// the maximum matrix
int** Max;

//the available vector
int* available;

//the work vector
int* work;

// Need matrix = Max - allocated
int** Need;

bool* finish;


int cnt, cnt2 = 0;
bool flag, what_to_print;

vector<string> output;

int* request;


bool safety_algorithm()
{
	for (int i = 0; i < no_of_resources; i++)
		work[i] = available[i];
	//low feh lafa matl3tsh proccess f l vector yb2a khalas false 3shan kol lafa bttl3 process

	for (int i = 0; i < no_of_processes; i++)
		finish[i] = false;
	for (int k = 0; k < no_of_processes; k++)
	{

		flag = false;

		for (int i = 0; i < no_of_processes; i++)
		{
			if (finish[i] == false)
			{
				cnt = 0;
				for (int j = 0; j < no_of_resources; j++)
				{
					if (Need[i][j] <= work[j])
						cnt++;
				}
				if (cnt == no_of_resources)
				{
					output.push_back(names_of_processes[i]);
					finish[i] = true;
					flag = true;
					// need to put work += allocated
					for (int k = 0; k < no_of_resources; k++)
					{
						work[k] += allocated[i][k];
					}
				}
			}
		}
		if (flag == false && output.size() != no_of_processes)
		{
			return false;
		}
	}
	return true;
}

void banker_algorithm_repeated()
{
	cout << "please enter the process name you want to request the resouces for" << endl;
	string s;
	cin >> s;
	int process_index = 0;
	cout << "please enter the request vector you want " << endl;

	int* request;
	request = new int[no_of_resources];

	for (int i = 0; i < no_of_resources; i++)
		cin >> request[i];

	for (int i = 0; i < no_of_processes; i++)
	{
		if (names_of_processes[i] == s)
		{
			process_index = i;
			break;
		}
	}
	int cnt1 = 0;
	for (int i = 0; i < no_of_processes; i++)
	{
		if (i == process_index)
		{
			for (int j = 0; j < no_of_resources; j++)
			{
				if (request[j] <= Need[i][j])
					cnt1++;
			}
		}
	}


	if (cnt1 < no_of_resources)
	{
		cout << "an error happened because the process has exceeded its maximum claim" << endl;
		return;
	}


	//hena na b3dl f l need matrix f lazem arg3ha
	else if (cnt1 == no_of_resources)
	{

		for (int i = 0; i < no_of_resources; i++)
			available[i] -= request[i];

		for (int i = 0; i < no_of_processes; i++)
		{
			if (i == process_index)
			{
				for (int j = 0; j < no_of_resources; j++)
				{
					allocated[i][j] += request[j];
					Need[i][j] -= request[j];
				}
			}
		}
	}

	what_to_print = safety_algorithm();

	if (what_to_print == true)
	{
		cout << "The System is in a safe state and to achieve that the sequence must be: " << endl;
		for (int i = 0; i < output.size(); i++)
		{
			if (i == output.size() - 1)
				cout << output[i] << ". ";
			else
				cout << output[i] << ", ";
		}
		cout << endl;
		output.clear();
	}
	else if (what_to_print == false)
	{
		for (int i = 0; i < cnt2; i++)
			available[i] += request[i];

		for (int i = 0; i < no_of_processes; i++)
		{
			if (i == process_index)
			{
				for (int j = 0; j < no_of_resources; j++)
				{
					allocated[i][j] -= request[j];
					Need[i][j] += request[j];
				}
			}
		}
		what_to_print = safety_algorithm();

		cout << "The resource requested denied because the state isn't safe" << endl;
		cout << "state is restored and the old safe state is:" << endl;
		for (int i = 0; i < output.size(); i++)
		{
			if (i == output.size() - 1)
				cout << output[i] << ". ";
			else
				cout << output[i] << ", ";
		}
		cout << endl;
	}
}

int main()
{


	cout << "please enter the number of processes: ";
	cin >> no_of_processes;

	names_of_processes = new string[no_of_processes];

	cout << "please enter the processes names seperated by spaces: ";
	for (int i = 0; i < no_of_processes; i++)
		cin >> names_of_processes[i];

	cout << "please enter the number of resouces: ";
	cin >> no_of_resources;

	names_of_resources = new string[no_of_resources];

	cout << "please enter the resources names seperated by spaces: ";
	for (int i = 0; i < no_of_resources; i++)
		cin >> names_of_resources[i];






	Need = new int* [no_of_processes];
	for (int i = 0; i < no_of_processes; i++)
		Need[i] = new int[no_of_resources];




	finish = new bool[no_of_processes];



	allocated = new int* [no_of_processes];
	for (int i = 0; i < no_of_processes; i++)
		allocated[i] = new int[no_of_resources];

	cout << "please enter the allocation Matrix," << endl << "(every row seperated by new line and the elements of the same row seperated by spaces): " << endl;
	for (int i = 0; i < no_of_processes; i++)
		for (int j = 0; j < no_of_resources; j++)
			cin >> allocated[i][j];

	Max = new int* [no_of_processes];
	for (int i = 0; i < no_of_processes; i++)
		Max[i] = new int[no_of_resources];

	cout << "please enter the Maximum Matrix," << endl << "(every row seperated by new line and the elements of the same row seperated by spaces): " << endl;
	for (int i = 0; i < no_of_processes; i++)
		for (int j = 0; j < no_of_resources; j++)
			cin >> Max[i][j];

	for (int i = 0; i < no_of_processes; i++)
		for (int j = 0; j < no_of_resources; j++)
			Need[i][j] = Max[i][j] - allocated[i][j];

	available = new int[no_of_resources];
	cout << "please enter the available vector (the elements of the vector seperated by space)" << endl;
	for (int i = 0; i < no_of_resources; i++)
		cin >> available[i];

	work = new int[no_of_resources];
	
	what_to_print = safety_algorithm();
	if (what_to_print)
	{
		cout << "The System is in a safe state and to achieve that the sequence must be: " << endl;
		for (int i = 0; i < output.size(); i++)
		{
			if (i == output.size() - 1)
				cout << output[i] << ". ";
			else
				cout << output[i] << ", ";
		}
		cout << endl;
		output.clear();
	}
	else
	{
		cout << "Not Safe" << endl;
		output.clear();
	}
	while (true)
	{
	
		cout << "do you want to enter a resource request vector for any process?" << endl << "(type 'true' if yes or 'false' if no)" << endl;
		string answer;
		cin >> answer;
		if (answer == "false")
		{
			cout << "Good Bye" << endl;
			system("pause");
			return 0;
		}
		else if (answer == "true")
		{
			banker_algorithm_repeated();
		}
	}
	system("pause");
	return 0;
}