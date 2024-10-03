#pragma once
#include <iostream>

#include "DLList.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Display {
private:
	DLList<string> list;
	bool doExit = false;

	void CreateExampleList() {
		list.Append("https://theuselessweb.com");;
		list.Append("https://littlealchemy.com");
		list.Append("https://thisissand.com");
		list.Append("https://window-swap.com");
		list.Append("https://zoomquilt.org");
		list.Append("https://radio.garden");
		list.Append("https://pointerpointer.com");
		list.Append("https://weavesilk.com");
		list.Append("https://neal.fun/earth-reviews");
		list.Append("https://notpron.org");
		list.Append("https://www.sporcle.com");
		list.Append("https://flightradar24.com");
		list.Append("https://findtheinvisiblecow.com");
		list.Append("https://nooooooooooooooo.com");
		list.Append("https://play2048.co");
		list.Append("https://agar.io");
		list.Append("https://cat-bounce.com");
		list.Append("https://geoguessr.com");
		list.Append("https://incredibox.com");
		list.Append("https://koalastothemax.com");

	}
public:
	Display() {
		list = DLList<string>();
		CreateExampleList();
	}

	~Display()
	{
	}

	void MainMenu() {
		while (!doExit) {
			system("cls");//bold assumption this is running on windows
			cout << "Main Menu" << endl;
			cout << "------------------" << endl;
			cout << "0. Exit" << endl;
			cout << "1. Display List" << endl;
			cout << "2. Prepend" << endl;
			cout << "3. Append" << endl;
			cout << "4. Navigate List" << endl;
			cout << "5. Find" << endl;
			cout << "6. Reverse List" << endl;

			int choice;
			string url;
			int index;
			cin >> choice;

			switch (choice) {
			case 0:
				doExit = true;
				break;
			case 1:
				DisplayList();
				break;
			case 2:
				Prepend();
				break;
			case 3:
				Append();
				break;
			case 4:
				NavigateList();
				break;
			case 5:
				cout << "Enter URL: ";
				cin >> url;
				index = list.Find(url);
				if (index != -1) {
					cout << "Found at index: " << index << endl;
				}
				else {
					cout << "Not found" << endl;
				}
				system("pause");
				break;
			case 6:
				list.Reverse();
				break;
			default:
				break;
			}
		}
	}

	void DisplayList() {
		system("cls");
		cout << "List Contents" << endl;
		cout << "------------------" << endl;
		for (int i = 0; i < list.Count(); i++) {
			cout << i << ". " << list.At(i) << endl;
		}
		cout << "------------------" << endl;
		system("pause");//more bold windows assumptions
	}

	void Prepend() {
		system("cls");
		cout << "Prepend" << endl;
		cout << "------------------" << endl;
		cout << "Enter URL: ";
		string url;
		cin >> url;
		list.Prepend(url);
	}

	void Append() {
		system("cls");
		cout << "Append" << endl;
		cout << "------------------" << endl;
		cout << "Enter URL: ";
		string url;
		cin >> url;
		list.Append(url);
	}

	void NavigateList() {
		list.Set_Current_To_Index(0);
		while (true) {
			system("cls");
			///current node info
			cout << "Current Node" << endl;
			cout << "------------------" << endl;
			cout << "Data: " << list.Current() << endl;
			cout << "Index: " << list.Current_Index() << endl;
			if (list.Current_Index() == 0) {
				cout << "First Node" << endl;
			}
			if (list.Current_Index() == list.Count()-1) {
				cout << "Last Node" << endl;
			}

			///menu
			cout << "Navigate List" << endl;
			cout << "------------------" << endl;
			cout << "0. Exit" << endl;
			cout << "1. Previous" << endl;
			cout << "2. Next" << endl;
			cout << "3. Insert Before" << endl;
			cout << "4. Insert After" << endl;
			cout << "5. Delete" << endl;
			cout << "6. Find" << endl;

			int choice;
			string url;
			cin >> choice;
			switch (choice)
			{
			default:
				break;
			case 0:
				return;
			case 1:
				list.Back();
				break;
			case 2:
				list.Forward();
				break;
			case 3:
				cout << "Enter URL: ";
				cin >> url;
				list.Insert_Before(url);
				break;
			case 4:
				cout << "Enter URL: ";;
				cin >> url;
				list.Insert_After(url);
				break;
			case 5:
				list.Remove_Current();
				break;
			case 6:
				cout << "Enter URL: ";
				cin >> url;
				int index = list.Find(url);
				if (index != -1) {
					cout << "Found at index: " << index << endl;
				}
				else {
					cout << "Not found" << endl;
				}
				list.Set_Current_To_Index(index);
				system("pause");
				break;
			}
		}
	}
};