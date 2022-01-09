#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#define _WIN32_WINNT 0x0400
#define ARROWUP 72       
#define ARROWDOWN 80    
#define ENTERKEY '\r'

#include <windows.h>

using namespace std;


int setquestion();
int wantusawa();
void randomizeq	(string cap);
void question (string question, string a, string b, string c, string d, string correct_answer);
void display();
void displayscore();
void gotoxy(int x, int y);
int primenu();
int secmenu();


//global var declaration
float wrongpoints = 0; //trig from initial value for recalc during looping wrong points
float correctpoints = 0; //trig from initial value for recalc during looping correct points
float Qtotal = 0; //trig from initial value for recalc during looping total score reset
int mode = 0; //trig from initial value for recalc during looping, trap for menu2

void gotoxy(int x, int y) //definition of gotoxy function//                                               
{
 COORD pos ={x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int setquestion() //function prototype question prep via file 
{
	HANDLE textvar = GetStdHandle(STD_OUTPUT_HANDLE); 
	int i=0,k = 0, choices, choice,j;
	char key;
	string line,path;
	string lines[100];
	srand(time(0));
	fstream myfile;
		
		do
		{
		gotoxy(1,3);
		cout << "Pakitype mo pangalan ng file. (hal. Exam.txt, TEST.TXT, Quiz1.txt):";
		gotoxy(1,4);
		cin >> path;
		myfile.open(path.c_str());
			
			if(myfile.fail())
			{
				gotoxy(1,5);
				cout<<"Sensya na ha, di ko makita yung pinapahanap mo. Paki type in ulit ng 'filename'.";
				getch();
				gotoxy(1,5);
				printf("                                                                                       ");
				gotoxy(1,4);
				printf("                                                                                       ");
			}
		}while(myfile.fail()); //loop user to type the correct filename
		
				
		while(! myfile.eof()) //read lines containing string up to the end of the line until reaching blank, stores each line in array line[i]
		{
			getline(myfile, lines[i]);
			SetConsoleTextAttribute(textvar,2+i);
			i++;
			choices = i;
			
				for(j=0; j <2 ; j++) //indicated text being read using color i.e. preloader
				{
					SetConsoleTextAttribute(textvar,2+j);
					gotoxy(1,6);
					printf("Saglit lang ha...?");
				
					if(j==2)
						{
						j=0;
						}
						Sleep(100);
				}
		}
		
	gotoxy(1,6);
	printf("                                             ");
	SetConsoleTextAttribute(textvar,2);
	gotoxy(1,6);
	cout << "May nabasa akong " << i  << " tanong sa file mo.";
	gotoxy(1,7);
		
		do
		{//<---saved instance if user would like to repeat the quiz with the same set of questions
		
		SetConsoleTextAttribute(textvar,2);
		gotoxy(1,7);
		correctpoints = 0;
		Qtotal = 0;
		wrongpoints = 0;
		
			do
			{//<---loop until valid int keyed
				if(cin.fail())
					{
				    cin.clear();
				    cin.ignore(numeric_limits<streamsize>::max(), '\n');
				    }    
				   
				cout << "Ilan bang tanong gusto mo sagutan? ";
				cin >> choice;
				
			} while(cin.fail());
			
			for (j=0; j < choice ; j++) //first shuffle choice all over total
			{
				int index = rand() % choices;
				string temp = lines[j];
				lines[j] = lines[index];
				lines[index] = temp;
			}


			for (j=0; j < choice ; j++) //second shuffle from selected
			{
				int index = rand() % choice;
				string temp = lines[j];
				lines[j] = lines[index];
				lines[index] = temp;
			}

			while (k < choice) //random questions thrown to function that will parse string of text
			{
				string set = lines[k];
				randomizeq(set);
				k++;
			}
			j=0;
			k=0;
			
			displayscore();
			secmenu();
		}while(mode!=0);
			
	myfile.close();
			
return 0;
}

//capture randomquestions for parsing
void randomizeq(string cap)
{
	int i = 0;
	string line;
	string lines[100];
	string forparsing = cap;
	stringstream readline(forparsing);
	
		while(readline.good())
		{
			string gettext;
			getline(readline, gettext, '\t'); //delimiter will be the two x's char
			lines[i]=gettext;
			i++;
		}
	
	string Question = lines[0]; //set parsed data to arrays
	string A = lines[1];
	string B = lines[2];
	string C = lines[3];
	string D = lines[4];
	string correctletter = lines[5];
	
	question(Question, A, B, C, D, correctletter);
	srand(time(NULL));
	
}

//parsed string, question randomization including choices
void question (string question, string a, string b, string c, string d, string correct_answer)
{
	system("CLS");
	display();
	int i;
	int j=0;
	int y;
	int k=0;

	char letter='A';
	char correct_letter = 'A';
	char answer;
	
	string choice[4];
		
	choice[0]= a;
	choice[1]=b;
	choice[2]=c;
	choice[3]=d;

	srand(time(0));
	
	gotoxy(0,4);
	cout<<question <<endl <<endl;
		
	for (i=0; i < 4 ; i++)
	{
		int index = rand() % 4;
		string temp = choice[i];
		choice[i] = choice[index];
		choice[index] = temp;
	}

	
	for (i = 0; i < 4 ; i++)
	{
		
		if(choice[i] == correct_answer)
		{
			y = i;
		}
		cout << letter << ".  " << choice[i] << endl;
		j = int(letter);
		j++;
		letter = char(j);
	}

	for (i = 0; i < y ; i++)
	{
		k = int(correct_letter);
		k++;
		correct_letter = char(k);
	}

	cout<< endl << endl <<"Sagot:  ";
	
	do
	{
		cin.clear();
		gotoxy(0,13);
		cout<<"                                                                  ";
		gotoxy(0,13);
		cin >> answer;
		answer = toupper(answer);
	}while(answer != 'A' && answer != 'B' && answer != 'C' && answer != 'D' );
	
	if(answer == correct_letter)
	{
		const string Magaling[10] = {"Ummm PANIS!","Hanep!","Ang galing ano po?!","Mahusay, mahusay, napakahusay!","Palakpakaaaaan!","Nice One!","Pabarger ka naman!","Pacanton ka naman!","Sabi ko nga, yan yung sagot e!","Pareho tayo ng nasa isip :D"};
  		int GalingIndex = rand() % 10;
  		cout << endl << "TAMA! " << endl << Magaling[GalingIndex] ;
		correctpoints ++;
	}
	
	else
	{
	const string Enganyo[10] = {"Tiwala lang!","Habol tayo :D","Laban!","Ay..sayang..","Kaya mo yan, may libreng barger ka mamaya :D","Uy no' ginagawa mo???!","Sus-ku-po!","Kaya pa yan :)","Naman! Naman!","Gisiiiiiiing!!!"};
  		int EnganyoIndex = rand() % 10;
  		
	cout << endl << "Di naman yan yung sagot e..." << endl << "Ang tamang sagot ay  " << correct_letter << endl << Enganyo[EnganyoIndex];
		wrongpoints++;
	}
	
	Qtotal++;
	getch();
	srand(time(0));
	system("CLS");
}


void display()
{
	HWND consoleWindow = GetConsoleWindow();
	char ascii;
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	SMALL_RECT consoleorient;
    COORD coord;
    coord.X = 100; 
    coord.Y = 17;  

    consoleorient.Top = 0;
    consoleorient.Left = 0;
    consoleorient.Bottom = coord.Y-1; // height for windows
    consoleorient.Right = coord.X-1;  // width for windows

    HANDLE windowsorient = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleScreenBufferSize(windowsorient, coord);       
    SetConsoleWindowInfo(windowsorient, TRUE, &consoleorient);     

    HANDLE textvar = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(textvar,23);
	gotoxy(0,0);
	printf("====================================================================================================");
	gotoxy(0,1);
	printf("|                                                                                                  |");
	gotoxy(0,2);
	printf("====================================================================================================");
	SetConsoleTextAttribute(textvar,1);
	SetConsoleTextAttribute(textvar,03);
	gotoxy(45,0);
	printf("  QUIZZER BOT  ");
	SetConsoleTextAttribute(textvar,18);
	gotoxy(3,1);
	printf("Quizzer Program ver. 1");
	gotoxy(82,1);
	ascii=67; cout << ascii; ascii= 67 + 37; cout << ascii; ascii = 100;
	cout << ascii; ascii = 30 + 47; cout << ascii; ascii = 50*2+1; cout << ascii;
	ascii = 360/3 - 3*5; cout << ascii;	ascii = 25*4 + 3*5; cout << ascii;
	ascii = 115+1; cout << ascii; 	ascii = 50*2+1;	cout << ascii; ascii = 114; cout << ascii; int asciii = 500*4+7*3;
	cout << asciii;
	SetConsoleTextAttribute(textvar,2);
	gotoxy(85,15);
	printf("NOT FOR SALE!");

}

void displayscore()
{
	
	system("CLS");
	display();
	gotoxy(0,3);
	cout << "Tamang Sagot: " << correctpoints << endl << "Maling Sagot: " << wrongpoints << endl << "Kabuuan: " << Qtotal << endl << endl;
	float rate =  correctpoints/Qtotal;
	
	cout << "Rating: " << setprecision(4) << rate *100 <<"%  ";
	
	int rating = rate * 100;
	if (rating <= 70)
	{
		const string Bagsak[5] = {"Prang di mo naman sineryoso e","Game ulit? :D","Nakakalito ba yung mga tanong?","Konti push pa, kaibigan...","Gusto mo ba muna magkape? Tapos game ulit?"};
  		int BagsakIndex = rand() % 5;
  		cout << endl << "Tara, game ulit!" << endl << Bagsak[BagsakIndex];
	}
	
	else if(rating >= 71)
	{
		const string Pasado[5] = {"Angas!","Congrats, ang galing mo!","Yoooown!","Yun oh!","Ang galing naman pala e :)"};
  		int PasadoIndex = rand() % 5;
  		cout << endl << "Pasado! " << endl << Pasado[PasadoIndex] ;
		
	}
	getch();
	Sleep(100);
}





int main()
{
	display();
	system("CLS");
	display();
	primenu();
	getch();
	return 0;
}



int primenu()
{
    int currentpos = 0;   
    int activechoices = 3;
    char keypress; 
    
    bool scrollthru = true;
    bool selected = false;
    
	HANDLE textvar = GetStdHandle(STD_OUTPUT_HANDLE);
    
    
	gotoxy(3,4); cout <<"-----------PILI KA DYAN-----------";
	gotoxy(3,8); cout <<"----------------------------------";
	gotoxy(3,5);
	SetConsoleTextAttribute(textvar,18);
	cout<<"    Praktis: Sagot wan to sawa    ";
	SetConsoleTextAttribute(textvar,7);
	gotoxy(3,6);
	cout<<"    Pagsubok:                     ";
	SetConsoleTextAttribute(textvar,7);
	gotoxy(3,7);
	cout<<"    Labas:                        ";
	
	
	gotoxy(3,5);
    while (scrollthru)
	{ 
        switch ((keypress = _getch()))
		{ 
            case ARROWUP:
                if (currentpos > 0)
					{ 
	                    --currentpos;
	                    selected = true;
	                }break;
	                
            case ARROWDOWN:
                if (currentpos < activechoices - 1)
					{ 
	                    ++currentpos;
	                    selected = true;
	                }break;
	                
            case ENTERKEY: scrollthru = false;
                	break;
            		default: break;
        }
        
		if (selected)
		{ 
            	if(currentpos==0)
					{
					gotoxy(3,5);
					SetConsoleTextAttribute(textvar,18);
					cout<<"    Praktis: Sagot wan to sawa    ";
					SetConsoleTextAttribute(textvar,7);
					gotoxy(3,6);
					cout<<"    Pagsubok:                     ";
					SetConsoleTextAttribute(textvar,7);
					gotoxy(3,7);
					cout<<"    Labas:                        ";
					}
				
				if(currentpos==1)
					{
					gotoxy(3,5);
					SetConsoleTextAttribute(textvar,7);
					cout<<"    Praktis:                      ";
					SetConsoleTextAttribute(textvar,18);
					gotoxy(3,6);
					cout<<"    Pagsubok: Makakaiskor ka dito ";
					SetConsoleTextAttribute(textvar,7);
					gotoxy(3,7);
					cout<<"    Labas:                        ";
					}
				
				if(currentpos==2)
					{
					gotoxy(3,5);
					SetConsoleTextAttribute(textvar,7);
					cout<<"    Praktis:                      ";
					SetConsoleTextAttribute(textvar,7);
					gotoxy(3,6);
					cout<<"    Pagsubok:                     ";
					SetConsoleTextAttribute(textvar,18);
					gotoxy(3,7);
					cout<<"    Labas: Mamaya na magreview    ";
					}
				
			selected = false;
        }
    }
    
    switch(currentpos)
	{
					
		case 0: 
		{
					
			gotoxy(3,9);
			cout << "Paki-pindot ng <ENTER> kung handa ka na. Anser ol yu kan :)" << endl << "   (Pindutin lang ang <ESC> key matapos sumagot kung gusto mo nang huminto)";
			getch();
			system("cls");
			display();
			wantusawa();
		}
					
		case 1: 
		{
			gotoxy(3,9);
			cout << "Paki-pindot ng <ENTER> kung handa ka na. Pagbutihin mo! :)";
			getch();
			system("CLS");
			display();
			setquestion();
		}
			
		case 2:
		{
			gotoxy(20,6);
			SetConsoleTextAttribute(textvar,7);
			system("CLS");
			display();
			gotoxy(35,6);
			cout << "Thank you for using Quizzer Bot Beta!!";
			getch();
			exit (0);
		}
	}
}
					
	


int secmenu()
{
	
	display();
	int currentpos = 0;   
    int activechoices = 3;
    char keypress; 
    
    bool scrollthru = true;
    bool selected = false;
    
	HANDLE textvar = GetStdHandle(STD_OUTPUT_HANDLE);


    gotoxy(3,12); cout <<"---------PILI KA ULIT DYAN---------";
	gotoxy(3,16); cout <<"-----------------------------------";
	gotoxy(3,13);
	SetConsoleTextAttribute(textvar,18);
	cout<<"    Ulitin                        ";
	SetConsoleTextAttribute(textvar,7);
	gotoxy(3,14);
	cout<<"    Magload ng Bagong File        ";
	SetConsoleTextAttribute(textvar,7);
	gotoxy(3,15);
	cout<<"    Pumunta sa Main Menu          ";
	
	
	gotoxy(3,13);
    
    while (scrollthru)
	{ 
        switch ((keypress = _getch()))
		{ 
            case ARROWUP:
                if (currentpos > 0)
				{ 
                    --currentpos;
                    selected = true;
                } break;
                
            case ARROWDOWN:
                if (currentpos < activechoices - 1)
				{ 
                    ++currentpos;
                    selected = true;
                }break;
                
            case ENTERKEY: scrollthru = false;
                break;
            	default: break;
        }
        
		if (selected)
		{ 
            	if(currentpos==0)
					{
						gotoxy(3,13);
						SetConsoleTextAttribute(textvar,18);
						cout<<"    Ulitin                        ";
						SetConsoleTextAttribute(textvar,7);
						gotoxy(3,14);
						cout<<"    Magload ng Bagong File        ";
						SetConsoleTextAttribute(textvar,7);
						gotoxy(3,15);
						cout<<"    Pumunta sa Main Menu          ";
						continue;
					}
						
				if(currentpos==1)
					{
						gotoxy(3,13);
						SetConsoleTextAttribute(textvar,7);
						cout<<"    Ulitin                        ";
						SetConsoleTextAttribute(textvar,18);
						gotoxy(3,14);
						cout<<"    Magload ng Bagong File        ";
						SetConsoleTextAttribute(textvar,7);
						gotoxy(3,15);
						cout<<"    Pumunta sa Main Menu          ";
						continue;
					}
						
				if(currentpos==2)
					{
						gotoxy(3,13);
						SetConsoleTextAttribute(textvar,7);
						cout<<"    Ulitin                        ";
						SetConsoleTextAttribute(textvar,7);
						gotoxy(3,14);
						cout<<"    Magload ng Bagong File        ";
						SetConsoleTextAttribute(textvar,18);
						gotoxy(3,15);
						cout<<"    Pumunta sa Main Menu          ";
						continue;				
					}
			
			selected = false;
        }
    }
   
    switch(currentpos)
	{
					
		case 0:
		{
			mode = 1;
			system("cls");
			display();
			return mode;
			getch();
			gotoxy(1,7);
			break;
		}
							
							
		case 1:
		{
			system("CLS");
			display();
			setquestion();
			break;
		}
							
		case 2:
		{
			SetConsoleTextAttribute(textvar,7);							
			system("cls");
			display();
			primenu();
			break;		
		}
	}
	
}

int wantusawa()
{
	
	HANDLE textvar = GetStdHandle(STD_OUTPUT_HANDLE); 
	int i=0,k = 0, choices, choice,j;
	char key;
	int labas;
	string line,path;
	string lines[100];
	srand(time(0));
	fstream myfile;
		
	
		do
		{
		gotoxy(1,3);
		cout << "Pakitype mo pangalan ng file. (hal. Exam.txt, TEST.TXT, Quiz1.txt):";
		gotoxy(1,4);
		cin >> path;
		myfile.open(path.c_str());
			
			if(myfile.fail())
			{
				gotoxy(1,5);
				cout<<"Sensya na ha, di ko makita yung pinapahanap mo. Paki type in ulit ng 'filename'.";
				getch();
				gotoxy(1,5);
				printf("                                                                                       ");
				gotoxy(1,4);
				printf("                                                                                       ");
			}
		}while(myfile.fail()); //loop user to type the correct filename
		
				
		while(! myfile.eof()) //read lines containing string up to the end of the line until reaching blank, stores each line in array line[i]
		{
			getline(myfile, lines[i]);
			SetConsoleTextAttribute(textvar,2+i);
			i++;
			choices = i;
				for(j=0; j <2 ; j++) //indicated text being read using color, works like a preloader
				{
					SetConsoleTextAttribute(textvar,2+j);
					gotoxy(1,6);
					printf("Saglit lang ha...?");
				
					if(j==2)
						{
						j=0;
						}
						Sleep(100);
				}
		}
		
		gotoxy(1,6);
		printf("                                             ");
		
		SetConsoleTextAttribute(textvar,2);
		gotoxy(1,6);
		cout << "May nabasa akong " << i  << " tanong sa file mo.";
		gotoxy(1,7);
		
			
			
	
		for(;;)
		{//<---saved instance if user would like to repeat the quiz with the same set of questions
		
			SetConsoleTextAttribute(textvar,2);
			gotoxy(1,7);
			correctpoints = 0;
			Qtotal = 0;
			wrongpoints = 0;

			
			for (j=0; j < choices ; j++) //first shuffle choice all over total
			{
				int index = rand() % choices;
				string temp = lines[j];
				lines[j] = lines[index];
				lines[index] = temp;
			}


			for (j=0; j < choices ; j++) //second shuffle from selected
			{
				int index = rand() % choices;
				string temp = lines[j];
				lines[j] = lines[index];
				lines[index] = temp;
			}

			while (k < choices) //random questions thrown to function that will parse string of text
			{
				string set = lines[k];
				randomizeq(set);
				k++;
				display();
				gotoxy(0,3);
				cout << "<ESC> kung gusto mo bumalik sa MAIN MENU" << endl << "Pindot ka kahit ano kung gusto mo pa magpatuloy.";
				labas = getch();
				if(labas == 27)
				{
					system("cls");
					display();
					primenu();
				}
			}
		j=0;
		k=0;
		}
	myfile.close();
}	
	

