#include <iostream>
#include <string>
#include "chess.h"
#include "chess.cpp"
#include<string>

using namespace std;

int main()
{
    system("color E");
    system("chcp 65001");
	bool newgame = true;
	string choice;

	cout << "   ___          __  ____  __    __  __    __   _____     " << endl;
	cout << "  |___   |__|  |__|  |   |__| /|   |__|  |  |    |       " << endl;
	cout << "   ___|  |  |  |  |  |   |  |  |   |  |  |  | |__|       " << endl<<endl;


	cout<<"VIRENDRA JANGIR AND HIMANSHU JHAWAR"<<endl;
    cout<<"Enter the names of the player playing white and the player playing black"<<endl;
    string s1,s2;
    cin>>s1>>s2;
    match Match;
    player p1(s1,WHITE);
    player p2(s2,BLACK);
	while(newgame){
		Board b;
		while (b.Game(p1,p2));
		Match.display_result(p1,p2);
		cout << "Do you want to play again? Press y for yes ";
		cin >> choice;
		if (choice != "y")
			newgame = false;
	}

}
