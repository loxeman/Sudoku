
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h>
#include <cmath>
#include <ctype.h>

using namespace std;

const int N=16;//the size of the game

struct player
{
	string name;
	string level;
	int score;
}p[100];

void intro();
void printline();
void printsudoku(int [N][N],int [N][N]);
bool checkbox(int [N][N],int , int , int , int , int);
bool checkrow(int [N][N],int , int , int);
bool checkcol(int [N][N],int , int , int ); 
bool findempty(int [N][N], int& , int&);
bool valid(int [N][N],int , int , int); 
void empty(int [N][N], int);
void generate_diagonal(int [N][N]);
bool generate_other(int [N][N]);
void new_game(int [N][N]);
int playerdata();
void game(int [N][N],int [N][N],int,int,int,int);
void load_game();
void score(int,int);
void leaderboard();
void mainmenu();
void instruction();
void Color(int );

ofstream outfile;
ifstream infile;

int main()
{
	intro();
    mainmenu();
	
	return 0;
}

void intro()
{
	cout << "                     -------------------------------------------------------" << endl;
	cout << "                  --------------------------WELCOME TO-------------------------" << endl;
	cout << "\n" << endl;
	cout << "                                         S  U  D  O  K  U                        " << endl;
	cout << "                                             The Game                          \n\n\n\n\n" << endl;
	cout << "                                            Created by                          \n" <<endl;
	cout << "                                      MUHAMAD LUQMANUL HAKIM                  " << endl;
	cout << "                                           FAISAL YASIER                       " << endl;
	cout << "                                           MUHAMMAD ADAM                       " << endl;
	cout << "                                           ADAM QUSYAIRI                       \n\n\n" << endl;
	cout << "                  ------------------------------------------------------------" << endl;
	Sleep(2000);
}

void mainmenu()//Function to call the main menu
{
	int sudoku[N][N]={0}, menuselect;
	char decision;
	
	system("CLS");
	cout << "                      ----------------------------------------------------------" << endl;
	cout << "                 -----------------------------MAIN MENU------------------------------" << endl;
	cout << "\n\n" << endl;
	cout << "                                           S  U  D  O  K  U                        " << endl;
	cout << "                                               The Game                              " << endl;
	cout << "                                                                                                           \n\n\n\n" << endl;
	cout << "                                            1 : NEW GAME                          " <<endl;
	cout << "                                            2 : CONTINUE                  " << endl;
	cout << "                                            3 : GAME INSTRUCTION                       " << endl;
	cout << "                                            4 : LEADERBOARD                   " << endl;
	cout << "                                            5 : EXIT GAME                       \n\n\n\n\n" << endl;
	cout << "                  -----------------""--'THE MOST POPULAR PUZZLE GAME'-----------------" << endl;
	cout << "                  ----------------""-----------ERIC BRANDON---------------------------" << endl <<endl;
	
	cout << "Enter your choice (1-5): ";
	cin >> menuselect;
	while(cin.fail()||menuselect>5 || menuselect<1)
	{ 
		cout << "Invalid key!! Please input 1 - 5 :" ;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> menuselect;
	}
	
	switch(menuselect)
	{
		case 1: new_game(sudoku);mainmenu();
		case 2: load_game();mainmenu();
		case 3: instruction();mainmenu();
		case 4: leaderboard(); mainmenu();
		case 5: do
				{cout << "Are you sure? Y/N : ";
		        cin >> decision;
		        if(decision=='Y'||decision=='y')
		        exit(1);
		        else if(decision=='N'||decision=='n')
		        mainmenu();
		        else
		        cout << "Invalid input!";
		    	}while(decision!='Y'&&decision!='y'&&decision!='N'&&decision!='n');
	}	
}

int playerdata()//Function to read the playerdata from the file
{
	int i;
	char indicator;
	infile.open("PlayerData.dat");//Open the file contain the playerdata
	if(!infile)
	{	outfile.open("PlayerData.dat");
		outfile.close();
		infile.open("PlayerData.dat");
	}
	
	for(i=0;i<100&&infile.peek()!=EOF;i++)//Collect all the player data and put into array p
	{
		getline(infile,p[i].name);
		infile >> p[i].level;
		infile >> p[i].score;
		infile.ignore();
	}
	infile.close();
	return i; //return the last position of the index
}

void instruction()//Display the game instruction
{
	system("CLS");
	printline();
	cout <<"------------------"<< endl;
	printline();
	cout<<"------------------"<<endl<<endl<<"\t                              Welcome to SUDOKU The Game" <<endl
		<<"\t This is a puzzle game where you need to put number 1-16 in the box that consist value 0." <<endl<<endl
	    <<"\t There are several rules that you need to follow:" <<endl
	    <<"\t 1. Every 4x4 grid cannot have same number" << endl
	    <<"\t 2. For every row, there is only one number from 1-16" << endl
	    <<"\t 3. For every column, there is only one number from 1-16" << endl << endl << endl
	    <<"\t\t If you stuck in the game, you can ask for hint and always remember, " <<endl
		<<"\t\t\tAllah never put a burden that someone cannot bear"<<endl<<endl<<endl
	    <<"\t                              GOOD LUCK! TRY YOUR BEST!!!" <<endl<<endl;
	printline();
	cout <<"------------------"<< endl;
	system("pause");
}

void new_game(int sudoku[N][N])//start the new game & select difficulty
{
	int difficulty, sudokucopy[N][N]={0};
	system("CLS");
	
	printsudoku(sudoku,sudoku);
	srand(time(NULL)); 
	generate_diagonal(sudoku);//Generate the 16x16 sudoku
	generate_other(sudoku);
	for(int i=0; i<16; i++)
	{
		for(int j=0; j<16; j++)
		{
			sudokucopy[i][j]=sudoku[i][j];//Copy the sudoku for further use
		}
	}
	
	
	cout << endl << "Select the game difficulty:" << endl
	     << " 1 : Easy " << endl
		 << " 2 : Intermediate " << endl
		 << " 3 : Hard" << endl
		 << " 4 : Expert" << endl
		 << " 5 : Master " << endl << endl
		 << " Press 0 to return to the main menu." << endl
		 << " Your level choice (Enter the number 0-5): ";
		cin >> difficulty;
	
	while(cin.fail()||0>difficulty>5)
	{
		cout << " Invalid character entered: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> difficulty;
	}
	
	switch (difficulty)
	{
		case 0:mainmenu();break;
		case 1:game(sudoku,sudokucopy,56,5,0,1);break;
		case 2:game(sudoku,sudokucopy,104,5,0,2);break;
		case 3:game(sudoku,sudokucopy,152,5,0,3);break;
		case 4:game(sudoku,sudokucopy,152,3,0,4);break;
		case 5:game(sudoku,sudokucopy,200,3,0,5);break;
	}
	
}

void game(int sudoku[N][N],int sudokucopy[N][N],int remove,int hint, int attempt, int level)//The game structure
{
	int option,col,check,i,j, sudokuunsolve[N][N];
	char row,choice;
	string secnum;
	bool checksave=false;
	
	if(remove==-1)//Check either the game is load_game or new_game
	{
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
			sudokuunsolve[i][j]=sudokucopy[i][j];
		}
		generate_other(sudokucopy);//Generate answer from the saved unsolve sudoku
	}
	else//if new game, remove certain part of the sudoku
	{
	empty(sudoku,remove);
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		sudokuunsolve[i][j]=sudoku[i][j];//Copy the sudoku with removed part
	}
	}
	do
	{
		system("CLS");
		printsudoku(sudoku,sudokuunsolve);
		cout << endl;
		cout << "What your next move?"<<endl		//User option in the game
		     << "1. Fill the missing number"<<endl
		     << "2. Submit the sudoku"<<endl
			 << "3. Other option" << endl 
			 << "Enter your option: " ;
		cin >> option;
		while(cin.fail()||option!=1&&option!=2&&option!=3)
		{
			cout << "Invalid option!" << endl;
			cout << "Please re-enter: ";
			cin.clear();
		    cin.ignore(256, '\n');
			cin >> option;
		}	 
		switch (option)
		{
			case 1: cout << "Enter the tile coordinate (eg: L16): "; //Locate the index that user want to modify
					cin >> row >> col;
					if(sudokuunsolve[static_cast<int>(toupper(row)-65)][col-1]!=0)
					{
						cout << "Cannot select the assigned number tile" << endl; //Restrict user from modify the index that had been set
						system("pause");
						break;
					}
					cout << "Enter the number: ";
					cin.ignore();
					cin >> sudoku[static_cast<int>(toupper(row)-65)][col-1];
					while(1>sudoku[static_cast<int>(toupper(row)-65)][col-1]||sudoku[static_cast<int>(toupper(row)-65)][col-1]>16)
					{
						cout << "Cannot assign number other than 1-16!" << endl;
						cout << "Enter the number: ";
						cin.ignore();
						cin >> sudoku[static_cast<int>(toupper(row)-65)][col-1];
					}
					attempt++;
					break;
			case 2: if (findempty(sudoku,i,j)) //Check if there is empty space left
					{
						cout << "Your sudoku is incomplete" << endl;
						system("pause");
						for(int i=0; i<16; i++)
						{
							for(int j=0; j<16; j++)
							{
								if(sudokuunsolve[i][j]!=0)
								continue;	
								
								else if(!valid(sudoku,i,j,sudoku[i][j]))//Check other number that have been place if it not meet the rules
								sudoku[i][j]=0;						   //Assign zero to violated number placement
							}
						}
						if(level<=3)
						break;
						else
						{
							game(sudokuunsolve,sudokucopy,0,hint,attempt,level);//Make all the unassign tile become zero back for higher level
							break;
						}
					}
					else
					{
						check=0;
						for(int i=0; i<16; i++)
						{
							for(int j=0; j<16; j++)
							{
								if(sudokuunsolve[i][j]!=0)
								continue;
								if(!valid(sudoku,i,j,sudoku[i][j]))//The same rule check but for completed sudoku
								{
									check=1;
									sudoku[i][j]=0;
								}
							}
						}
							if(check==1)//Indicator for invalid number placement
							{
								cout << "Your sudoku have invalid number placement." << endl
								     << "Do you want to retry? (Y/N) : " ;
								cin >> choice;
								while(cin.fail()||choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
								{
									cout << "Invalid input! Please re-enter: " ;
									cin.clear();
									cin.ignore(256, '\n');
									cin >> choice;	
								}
								if(choice=='y'||choice=='Y')
								{
									if(level>3)//Make all the unassign tile become zero back for higher level
									game(sudokuunsolve,sudokucopy,0,hint,attempt,level);
								}	
								else
								mainmenu();	 
							}
							else
							{
								score(attempt,level);//If the sudoku completed without error calculate the score
								mainmenu();
							}
				
					} break;
			case 3: cout << endl << "Other option:" <<endl
					     << "1. Save game" << endl
					     << "2. Hint" << endl
			 			 << "3. Game instruction" << endl
			 			 << "4. Give up" << endl
			             << "99. Terminate game" << endl
			             << "Enter your option: ";
			             cin >> option;
			             while(cin.fail()||1>option&&3<option&&option!=1)
			             {
					            cout << "Invalid option!" << endl;
								cout << "Please re-enter: ";
								cin.clear();
		                        cin.ignore(256, '\n');
								cin >> option;	
						 }
			             if(option==1)//Save the game 
			             {
			             	cout << "Enter your secret number: ";
			             	cin >> secnum;
			             	secnum+=".dat";
			             	infile.open(secnum.c_str());
			             	while(infile)//Check if there is file with same name
							{
			             		cout << "The secret number had been taken," << endl
			             		     << "Do you want to overwrite? (Y/N): ";//Give option if a same user using the same secret number to overwrite the file
			             		cin >> choice;
			             		while(cin.fail()||choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
								{
									cout << "Invalid input! Please re-enter: " ;
									cin.clear();
									cin.ignore(256, '\n');
									cin >> choice;	
								}
								if(choice=='y'||choice=='Y')
								break;
								
			             		cout << "Enter another secret number: ";
			             		cin >> secnum;
								infile.close();
								infile.clear();
								secnum+=".dat";
			             		infile.open(secnum.c_str());	
							}
							infile.close();
							infile.clear();
			             	outfile.open(secnum.c_str());//Write the save file with all neccessary data
			             	outfile << attempt << " " << hint << " " << level << endl;
			             	for(i=0;i<N;i++)
			             	{
			             		for(j=0;j<N;j++)
			             		{
			             			outfile << sudoku[i][j] << " ";
								}
								outfile << endl;
							}
			             	for(i=0;i<N;i++)
			             	{
			             		for(j=0;j<N;j++)
			             		{
			             			outfile << sudokuunsolve[i][j] << " ";
								}
								outfile << endl;
							}
							outfile.close();
							checksave=true;
							break;
						 }
						 
						 else if(option==2)//If user want to use hint
						 {
						 	if(hint==0)//Check if user have hint left
						 	{
							 	cout << "You do have any hint left!" << endl;
							 	system("pause");
							}
						 	else if(!findempty(sudoku,i,j))//Check if there is no more place to put a number
						 	{
								cout << "There is no empty place left" << endl;
								system("pause");
							}
							else
							{
								cout << "Caution: using hint will reduce the possibility of the answer" << endl
									 << "Hint left: " << hint << endl
								     << "Proceed? (Y/N)";
								cin >> choice;
								while(cin.fail()||choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
								{
									cout << "Invalid input! Please re-enter: " ;
									cin.clear();
									cin.ignore(256, '\n');
									cin >> choice;	
								}
								if(choice=='y'||choice=='Y')
								{
									sudoku[i][j]=sudokucopy[i][j];
									hint--;
									attempt+=10;
								}	
								else
								mainmenu();
							}
						 }
						else if(option==3)//Open instruction function
						instruction();
						
						else if(option==4)//Print sudoku that had been copy earlier
						{
						system("CLS");
						cout << "The solution is: " << endl << endl;
						printsudoku(sudokucopy,sudokuunsolve);
						system("pause");
						mainmenu();
						}
						
						else if(option==99)//Terminate the game and back to main menu
						{
					 	if(!checksave)//Check if the user already save their game or not
						{
						cout << "Are you sure want to terminate the game without saving? (Y/N) : " ;
						cin >> choice;
						while(cin.fail()&&choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
						{
							cout << "Invalid input! Please re-enter: " ;
							cin.clear();
							cin.ignore(256, '\n');
							cin >> choice;	
						}
						if(choice=='y'||choice=='Y')
						mainmenu();	
						else
						option=0;	 
						}
						} break; 
		}
	}while(option!=99);
}

void load_game()//Continue previous game
{
	int sudoku[N][N], sudokuunsolve[N][N], hint, attempt, level, check;
	string secnum;
	
	cout << "Enter your secret number: ";
	cin >> secnum;
	cout << endl;
	secnum+=".dat";
	infile.open(secnum.c_str());
	if(!infile)//Check if the save data exist
	{
		cout << "There is no save data for that secret number" << endl
			 << "Returning to main menu...." <<endl;
		Sleep(2000);
		infile.close();
		infile.clear();
		mainmenu();
	}
	
	else//Get all neccessary data to start the game
	{
		infile >> attempt >> hint >> level;
		infile.ignore(256, '\n');
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			infile >> sudoku[i][j];
		}
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			infile >> sudokuunsolve[i][j];
		}
	}
	infile.close();
	game(sudoku,sudokuunsolve,-1,hint,attempt,level);//Start the game for the loaded save data
	
}

void score(int attempt, int level)//Store score for 100 highest score player
{
	int position, score;
	string name, glevel;
	
	switch (level)//The score calculation for each level
	{
		case 1: score=attempt*(250-(50*(round(attempt/56)-1)));glevel="Easy";break;
		case 2: score=attempt*(250-(50*(round(attempt/104)-1)));glevel="Intermediate";break;
		case 3: score=attempt*(250-(50*(round(attempt/152)-1)));glevel="Hard";break;
		case 4: score=attempt*(500-(50*(round(attempt/152)-1)));glevel="Expert";break;
		case 5: score=attempt*(500-(50*(round(attempt/200)-1)));glevel="Master";break;
	}
	position=playerdata();//Find the position for the player in the array p
	if(position==100)
	{
		if(p[99].score<score)//If player data is already 100, check if the player score than 100th place player, if yes overwrite
		{
			cout << "Enter yor name: ";
			cin.clear();
		    cin.ignore(256, '\n');
			getline(cin,name);
			p[99].name=name;
			p[99].level=glevel;
			p[99].score=score;
		}
	}
	else
	{
		cout << "Enter yor name: ";
		cin.clear();
		cin.ignore(256, '\n');
		getline(cin,name);
		p[position].name=name;
		p[position].level=glevel;
		p[position].score=score;
	}
	for(int i=0;i<100;i++)//Sort the player position according score 
	{
		for(int j=0;j<99;j++)
		{
			if(p[j].score<p[j+1].score)
			swap(p[j],p[j+1]);
		}
	}
	outfile.open("PlayerData.dat");//print all player data to a file
	for(int i=0;i<position+1;i++)
	{
		outfile << p[i].name << endl
		        << p[i].level << endl
		        << p[i].score << endl;
	}outfile.close();
	
	//Celebration!!!
	system("CLS");
	cout << "============================== CONGRATULATION ==============================" << endl;
	cout << "                              YOU WIN THE GAME                              " << endl << endl << endl;
	cout << "                           Your score is: " << score << "                    " << endl << endl;
	system("pause");
	
}

void leaderboard()//Display top 10 player placement
{
	system("CLS");
	playerdata();
	for(int i=0;i<100;i++)//Sort the player position according score 
	{
		for(int j=0;j<99;j++)
		{
			if(p[j].score<p[j+1].score)
			swap(p[j],p[j+1]);
		}
	}
	cout << left << "|" << setw(30) <<"Player Name" << " | " << setw(13) << "Difficulty" << " | " << setw(6) << "Score " << " |" << endl
	     << "----------------------------------------------------------" << endl;
	for(int i=0;i<10;i++)
	{
		cout << left << "|" << setw(30) <<p[i].name << " | " << setw(13) << p[i].level << " | " << setw(6) <<right << p[i].score << " |"<< endl
		     << "----------------------------------------------------------" << endl;
	} 
	system("pause");
	
}

void generate_diagonal(int sudoku[N][N])//Generate random number for diagonal boxes
{
	int i,j,temp,box,boxcol;
	for(box=0;box<16;box+=4)
	{
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
			{
				do
				{
					temp=(rand()%16) + 1;
				}while(!checkbox(sudoku,i,j,temp,box,box));
				
				sudoku[i+box][j+box]=temp;
			}	
		}
	}
}

bool generate_other(int sudoku[N][N])//Generate number for remaining boxes
{
	
	int i, j, temp;
	
	if(!findempty(sudoku,i,j))
		return true;
	else
	{
		for(temp=1;temp<=N;temp++)
		{	
			if(valid(sudoku,i,j,temp))
			{
			sudoku[i][j]=temp;
			if(generate_other(sudoku))	
			return true;
			sudoku[i][j]=0;
			}
		}
	}
	return false;
}

void printline()
{
	for(int i=0;i<84;i++)
	cout << "-";
}

void printsudoku(int sudoku[N][N], int sudokuunsolve[N][N])//Function to printout the sudoku
{
	int row,col;
	char ch;
	cout << "  ";
	for(int i=1; i<=16; i++)
	{
		cout << setw(3) << i << "  " ;
		if (i==4||i==8||i==12)
			cout << " " ;
	}
	cout << endl << " ";
	printline();
	cout << endl;
	
	for(row=0, ch='A';row<16;row++, ch++)
	{
		cout << ch << "|";
		for(col=0;col<16;col++)
		{
			if(sudokuunsolve[row][col]==0)
			{
				Color(4);
				cout << setw(3) << sudoku[row][col]; 
			}
			else
			{
				Color(15);
				cout << setw(3) << sudoku[row][col];
			}
			Color(15);
			cout << " |" ;
			if (col==3||col==7||col==11)
			cout << "|" ;
		}
		
		cout << endl;
		if (row==3||row==7||row==11||row==15)
		{
			cout << " ";
			printline();
			cout << endl;
		}
	}
	Color(15);
}

bool checkbox(int sudoku[N][N],int i, int j, int temp, int boxrow, int boxcol)//Check if the number already in the box; if yes return false and vice versa
{
	int row, col;

	for(row=0; row<4; row++)
	{
		for(col=0; col<4; col++)
		{
			if(row!=i||col!=j)
			{
				if(sudoku[row+boxrow][col+boxcol]==temp)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool checkrow(int sudoku[N][N],int i, int j, int temp) //Check if the number already in the row; if yes return false and vice versa
{
	int col;
	
	for(col=0;col<16;col++)
	{
		if(col!=j)
		{
			if(sudoku[i][col]==temp)
			{
				return false;
			}
		}
	}
	return true;

}

bool checkcol(int sudoku[N][N],int i, int j, int temp) //Check if the number already in the column; if yes return false and vice versa
{
	int row;
	
	for(row=0;row<16;row++)
	{
		if(row!=i)
		{
			if(sudoku[row][j]==temp)
			{
				return false;
			}
		}
	}
	return true;
}

bool findempty(int sudoku[N][N], int &i, int &j)//Find the empty place in the sudoku
{
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(sudoku[i][j]==0)
			return true;
		}
	}
	return false;
}

bool valid(int sudoku[N][N],int i, int j, int temp) //Check wheter the selected number valid for the location
{
	
	return checkbox(sudoku,i%4,j%4,temp,i-i%4,j-j%4)&&checkrow(sudoku,i,j,temp)&&checkcol(sudoku,i,j,temp);
}

void empty(int sudoku[N][N],int remove)//Function to empty back the whole sudoku/a part of it
{
	int usedrow[remove], usedcol[remove], row, col, zero=0;
	bool check;
	if (remove==0)//terminate the function if no remove is needed
	return;
	for(int i=0; zero<=remove;)
	{
		check=false;
		for(int j=0;j<remove;j++)
		{
			row=(rand()%15)+0;
			col=(rand()%15)+0;
			
			if(row!=usedrow[j]&&col!=usedcol[j])
			check=true;
	
		}
		if(check)
		{
			sudoku[row][col]=0;
			usedrow[i]=row;
			usedcol[i]=col;
			zero++;
			i++;
		}
	}
						
}

void Color(int color)//Function to change the colour
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
