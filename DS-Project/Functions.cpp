/*	Functions implementation file	*/
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<Windows.h>
#include<map>
#include"Functions.h"
using namespace std;
map < string, vector<string>> Dictionary;
map< string, vector<string>>::iterator it;
void Word_filtration(string &str)
{
	for (unsigned i = 0; i < str.size(); i++)
	{
		if (i == 0)
			str[i] = toupper(str[i]);
		else
			str[i] = tolower(str[i]);
	}

}
void Load_File()
{
	ifstream myfile("Diction_File.txt", ios::in);

	string Word; int Number_Of_Meanings;
	while (myfile >> Word >> Number_Of_Meanings)
	{
		Word_filtration(Word);
		myfile.ignore();
		for (int i = 0; i < Number_Of_Meanings; i++)
		{
			string Meaning; getline(myfile, Meaning);
			Dictionary[Word].push_back(Meaning);
		}
	}
}
void Save_File()
{
	ofstream myfile("Diction_File.txt", ios::out);
	for (it = Dictionary.begin(); it != Dictionary.end(); it++)
	{
		myfile << it->first << "\t" << it->second.size() << "\n";
		for (unsigned i = 0; i < it->second.size(); i++)
			myfile << it->second[i] << endl;
	}
}
void Add_Word()
{
	system("cls");
	cout << "Enter Number of Words: "; int Number_Of_Words; cin >> Number_Of_Words;
	while (Number_Of_Words--)
	{
		cout << "Insert The Word: "; string Word; cin >> Word; Word_filtration(Word);
		cout << "Number of Meanings: ";	int Number_Of_Meanings; cin >> Number_Of_Meanings, cin.ignore();
		for (int i = 0; i < Number_Of_Meanings; i++)
		{
			cout << i + 1 << "->";
			string Meaning; getline(cin, Meaning);	Dictionary[Word].push_back(Meaning);
		}
		cout << "Done!\n\n";
		Display_Word(Dictionary.find(Word));
	}
	Save_File();
	system("pause");
}
void Display_Word(map< string, vector<string>>::iterator iT)
{
	cout << "\"" + iT->first + "\"";
	for (unsigned i = 0; i < iT->second.size(); i++){
		if (i)
		for (unsigned j = 0; j < iT->first.size() + 2; j++){ cout << " "; }
		cout << "\t: " + iT->second[i] + "\n";
	}
	cout << "-------------------------------------------------------------------------\n";
}
double Correct_prob(string Tool, string Original)
{
	double sum = 0;
	for (int i = 0; i < (int)Tool.size(); i++){
		if (i == Original.size()){
			if (Tool[i] == Original[i - 1])
				sum += 0.5;
			break;
		}
		if (Tool[i] == Original[i])
			sum++;
		else if (Tool[i] == Original[i + 1] || Tool[i] == Original[abs(i - 1)])
			sum += 0.5;
	}
	return(sum / max(Tool.size(), Original.size()));
}
bool Exist(string str)
{
	return !((Dictionary.find(str) == Dictionary.end()));
}
void Search_Word()
{
	system("cls");
	cout << "Insert The Word to search: "; string Word; cin >> Word; Word_filtration(Word);
	if (Exist(Word))
		Display_Word(Dictionary.find(Word));
	else{
		cout << "It's not exist to edit!\n\n";
		map< string, vector<string>>::iterator mx_it = Dictionary.end(); double mx_value = 0;
		for (it = Dictionary.begin(); it != Dictionary.end(); it++){
			if (Correct_prob(Word, it->first) >= 0.5&&mx_value < Correct_prob(Word, it->first)){
				mx_it = it;
				mx_value = Correct_prob(Word, it->first);
			}
		}
		if (mx_it != Dictionary.end()){
			cout << "Do You Mean : " + mx_it->first + "?\n";
			char ch; cin >> ch;
			if (ch == 'Y' || ch == 'y')
				Display_Word(mx_it);
		}
	}
	system("pause");
}
void Edit()
{
	system("cls");
	cout << "Insert The Word to modify:";
	string Word; cin >> Word; Word_filtration(Word); cout << "\n\n";
START:it = Dictionary.find(Word);
	if (Exist(Word))
	{
		cout << "\"" + it->first << "\"";
		for (unsigned i = 0; i < it->second.size(); i++)
		{
			if (i)
			for (unsigned j = 0; j < it->first.size() + 2; j++){ cout << " "; }
			cout << ":  " << i + 1 << "-> " << it->second[i];
			if (i != it->second.size() - 1)
				cout << "\n";
			else
				cout << "\n\n";
		}
	CHOOSE:cout << "To Edit All Meanings Press 1\nTo Edit A Certain Meaning Press 2\n" <<
		"To Delete A Certain Meaning Press 3\nTo Add A new Meaning Press 4\n"; int ch; cin >> ch, cout << "\n";
		   if (ch == 1)
		   {
			   cin.ignore();
			   for (unsigned i = 0; i < it->second.size(); i++)
			   {
				   cout << "Change the Meaning\"" << Dictionary[Word][i] << "\"\n";
				   cout << "The New is :  " << i + 1 << "->"; string Meaning; getline(cin, Meaning); Dictionary[Word][i] = Meaning;
			   }
		   }
		   else if (ch == 2)
		   {
			   cout << "Enter ID Of the Meaning You Want to modify:"; int index; cin >> index, cin.ignore();
			   cout << "Change the Meaning\"" << Dictionary[Word][index - 1] << "\"\n";
			   cout << "The New is :" << index << "->"; string Meaning; getline(cin, Meaning); Dictionary[Word][index - 1] = Meaning;
		   }
		   else if (ch == 3)
		   {
			   cout << "Enter ID Of the Meaning You Want to delete:"; int index; cin >> index;
			   Dictionary[Word].erase(Dictionary[Word].begin() + index - 1);
		   }
		   else if (ch == 4)
		   {
			   cout << "The New Meaning is :  " << Dictionary[Word].size() + 1 << "->";
			   cin.ignore(); string Meaning; getline(cin, Meaning); Dictionary[Word].push_back(Meaning);
		   }
		   else
		   {
			   cout << "Enter a correct choice: \n\n";
			   goto CHOOSE;
		   }
		   Save_File();
		   cout << "Done!\n\n";
		   Display_Word(Dictionary.find(Word));
		   system("pause");
	}
	else
	{
		cout << "It's not exist to edit!\n\n";
		map< string, vector<string>>::iterator mx_it = Dictionary.end(); double mx_value = 0;
		for (it = Dictionary.begin(); it != Dictionary.end(); it++){
			if (Correct_prob(Word, it->first) >= 0.5&&mx_value < Correct_prob(Word, it->first)){
				mx_it = it;
				mx_value = Correct_prob(Word, it->first);
			}
		}
		if (mx_it != Dictionary.end()){
			cout << "Do You Mean : " + mx_it->first + "?\n";
			char ch; cin >> ch;
			if (ch == 'Y' || ch == 'y'){
				Word = mx_it->first;
				goto START;
			}
		}
		system("pause");
	}
}
void Display_All()
{
	system("cls");
	for (it = Dictionary.begin(); it != Dictionary.end(); it++){
		Display_Word(it);
	}
	system("pause");
}
void MAIN_FUNCTION()
{
	system("cls");
	cout << "Choose Operation:" << endl;
	cout << "1-Add New Words." << endl;
	cout << "2-Display All Words." << endl;
	cout << "3-Edit Meaning of Word." << endl;
	cout << "4-Search For A Meaning Of Certain Word." << endl;
	cout << "5-Exit." << endl;
	cout << "Enter Your Choice: "; int x; cin >> x;
	if (x == 1)
		Add_Word();
	else if (x == 2)
		Display_All();
	else if (x == 3)
		Edit();
	else if (x == 4)
		Search_Word();
	else if (x == 5)
	{
		cout << "System Exited..." << endl;
		Sleep(800);
		return;
	}
	MAIN_FUNCTION();
}