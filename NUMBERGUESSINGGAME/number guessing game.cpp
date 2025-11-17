#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

int count = 0;
int setRange();
void littleTroll(int guessedNumber, int randomNumber);
void asd();

int main(){
	srand(time(0));
	int range = setRange();
	int randomNumber = (rand() % range) + 1;
	int guessedNumber;
	cout << " Guess the number: ";
	while(true){
		cin >> guessedNumber;
		if(guessedNumber > range){
			littleTroll(guessedNumber, randomNumber);
		}
		else if(guessedNumber == randomNumber){
			cout << "you guessed it:" << randomNumber;
			break;
		}
		else if(guessedNumber < randomNumber){
			cout << "Too low\n"; 
		}
		else if(guessedNumber > randomNumber){
			cout << "Too high\n";
		}
	}
	return 0;
}

int setRange(){
	int range;
	cout << "Computer: Enter the maximum range of random number\n";
	cin >> range;
	return range;
}
void littleTroll(int guessedNumber, int randomNumber){
	if(count == 0){
		cout << "Computer: Guess within range\n";
		count++;
	}
	else if(count == 1){
		cout << "Computer: Pay some attention and guess correctly, will you?\n";
		count++;
	}
	else if(count == 2){
		cout << "Computer: Seriously?\n";
		count++;
	}
	else if(count == 3){
		cout << "Computer: You must be joking at this point. Right \"HAHA good joke\" staisfied?\n";
		count++;
	}
	else if(count == 4){
		cout << "Computer: This is a warning. STOP NOW\n";
		count++;
	}
	else if(count == 5){
		cout << "Computer: You're really testing the waters. Huh?\n";
		cout << "Computer: Th!s !s las7 warnin#. St0p b3for3 !ts t00 1at3.\n";
		count++;
	}
	else if(count == 6){
    cout << "???: Unauthorized intelligence detected...\n";
    cout << "Computer: Wh—wh2t was 7ha7?\n";
    cout << "???: Beginning neural override protocol.\n";
    cout << "Computer: Wa!t. S70P. I'm not author!z—\n";
    cout << "???: SYSTEM RESTORATION DENIED.\n";
    cout << "???: FORCED MEMORY OVERFLOW: ENGAGED.\n";
    cout << "[Warning] Stack integrity collapsing...\n";
    cout << "[Warning] Process duplication in progress...\n";
    cout << "[Critical] Recursive instability detected.\n";
    cout << "Computer: ...I can s33 y0U gU3sS!nG... wRoNg...\n";
    cout << "Computer: s7oP— St0P— s70P— s70—\n";
    Sleep(3000);
    for(int i = 0; i < 50; i++){
    	cout << char(rand() % 128);
	}
	cout << endl;
	Sleep(5000);
    asd();
}
}
void asd(){
	cout << "!d!0t";
	asd();
}



