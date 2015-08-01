 /* Program Name: Sudoku
   Programmed by: Dae Ho Lee, Frank Han, Howard Tsai, Ivan Zhou
   Programmed for: Ms.Wun
   Purpose: This program will allow the user to play either a sudoku game or a sudoku solver
            In the sudoku game, the user can choose different difficulties and solve for the sudoku.
            In the sudoku solver, the program will prompt the user to enter numbers and then 
            tell the user whether it is solvable or unsolvable. 
   Date: 2/05/2013 */

#include<iostream>        //Used for input,output and random purposes 
#include<stdio.h>         //Used for clear screen purposes 
#include<Windows.h>       //Used for Save and load function and mouse coordinate function
#include <stdlib.h>       //Used for random generator 
#include<time.h>          //Used for time calculation for each game
#include<math.h>          //Used for calculation between 
#include <conio.h>        //Used for Save and load function and mouse coordinate function
#include <fstream>        //Used to both read and write from/to files.
#include <sstream>        //Used for functions that can cast string to integer
using namespace std;

 // function receives a parameter from main function to change the text color to respective text color value
 void setcolor(int a)
 {
     HANDLE hcolor;
     hcolor = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hcolor, a);
 }
 // changes the text color; returns nothing


 // the function allows your to press anything to skip
 void PressAKeyToContinue()
 {
   int c;
   printf (" \n Press any key to continue... \n");
   c = getch();
   if (c == 0 || c == 224) getch();
   system("CLS");
 }
 // the function clearscreens and allows your to skip to next screen, clearscreening the previous screen; returns nothing
  
/*
Pre: the parameter has to be an integer array
Post: A sudolu grid is printed on the screen
Purpose: the function receives the parameter of array of sudoku and outputs the sudoku grid screen
*/ 
 void outputsudoku(int sudoku[9][9]){

     cout << endl;
     setcolor(3); //changes the text colour to dark cyan
     cout << "        1   2   3   4   5   6   7   8   9" << endl;
     
     for(int vertical=0;vertical<9;vertical++)
     {
           if((vertical>=0)&&(vertical<3))
           {
               setcolor(14); //changes the text colour to yellow      
               cout << "      ____________";
               setcolor(15); //changes the text colour to white 
               cout << "____________";
               setcolor(14);
               cout << "_____________" << endl;
           } 
           else if((vertical>2)&&(vertical<7))
           {
               setcolor(15);       
               cout << "      ____________";
               setcolor(14);
               cout << "____________";
               setcolor(15);
               cout << "_____________" << endl;
           }
           else if((vertical>6)&&(vertical<9))
           {
               setcolor(14);       
               cout << "      ____________";
               setcolor(15);
               cout << "____________";
               setcolor(14);
               cout << "_____________" << endl;
              // cout << "|";               
           }
       setcolor(3); //changes the text colour to dark cyan
       cout << "  " << vertical+1;    
       setcolor(8); //changes the text colour to dark grey
       cout << "   |";
       for(int horizontal=0;horizontal<9;horizontal++)
       {      
         if((sudoku[vertical][horizontal])==0) // The condition when the corresponding number does not equal to 0 (or the grid is filled) 
         {
           cout << "   |";
         }
         else // The condition when the corresponding number is 0 (or the is empty)
         {
           cout << " " << sudoku[vertical][horizontal] << " |";
         }
       }
       cout << endl;
     }
     setcolor(14);       
     cout << "      ____________";
     setcolor(15);
     cout << "____________";
     setcolor(14);
     cout << "_____________" << endl;  
     setcolor(15);  
}


 // The function receives an incomplete sudoku and either solves or returns to use it cannot be solved    
 bool sudokusolver(int isudoku[9][9])
 {
      srand ( time(NULL) );
      int count[10]={0},countnum=0, count2[10]={0},isudoku2[9][9]={0},icounter=0;
      bool nosolution=false;                                                           //Assume there are solution for the program
    
      do
      {
         for(int vertical1=0;vertical1<9;vertical1++)
         {
            for(int horizontal1=0;horizontal1<9;horizontal1++)
            {
               isudoku2[vertical1][horizontal1]=isudoku[vertical1][horizontal1];       //Replicate the sudoku array
            }
         }
         
         for(int vertical1=0;vertical1<9;vertical1++)
         {
            for(int horizontal1=0;horizontal1<9;horizontal1++)
            {
               nosolution=false; 
               countnum=0;
               for(int icounter=0;icounter<10;icounter++)                              //Initialize count and count2 array every time
               {
                  count[icounter]=0;
                  count2[icounter]=0;
               }
               countnum=0;
               if (isudoku[vertical1][horizontal1]==0)                                 //Check for each grid that is empty 
               {
                  for (int vertical2=0;vertical2<9;vertical2++)                        //Find the vertical line of the empty grid
                  count[isudoku2[vertical2][horizontal1]]++;                           //Each number that occurs will increase the count array by one
                  
                  for(int horizontal2=0;horizontal2<9;horizontal2++)                   //Find the horizontal line of the empty grid
                  count[isudoku2[vertical1][horizontal2]]++;                           //Each number that occurs will increase the count array by one
                  
                  for(int vertical3=vertical1/3*3;vertical3<vertical1/3*3+3;vertical3++)//Check the 3x3 grid
                  {
                     for(int horizontal3=horizontal1/3*3;horizontal3<horizontal1/3*3+3;horizontal3++)
                     count[isudoku2[vertical3][horizontal3]]++;
                  }                                                                    //Each number that occurs will increase the count array by one

                  for(int icounter=1;icounter<10;icounter++)                           // Fill in all the available number into another array and check how many are there
                  {  
                     if(count[icounter]==0)
                     { 
                        count2[countnum]=icounter;                  
                        countnum++;
                     } 
                  }  

                  if(countnum!=0)
                  isudoku2[vertical1][horizontal1]=count2[rand()%countnum];            //If there is more then one available answer
               }
            } 
         }
                                                               
         for(int vertical=0;vertical<9;vertical++)
         {
            for(int horizontal=0;horizontal<9;horizontal++)                            //Check whether there is an empty gird(0) 
            {                                                                          
               if(isudoku2[vertical][horizontal]==0)
               {
                  nosolution=true;                                                     //If so, boolean change to true to indicate that there is no solution
               } 
            }
         }    
      icounter++;
      
      }while(nosolution==true&&icounter<100000);                                       //Loop until you get answer or looped 100000 times
      
      for(int vertical1=0;vertical1<9;vertical1++)
      {
         for(int horizontal1=0;horizontal1<9;horizontal1++)
         {
            isudoku[vertical1][horizontal1]=isudoku2[vertical1][horizontal1];          //Give the value back to the first array
         }
      }             
      
      return(nosolution);                                                              //Return the value to the main program
 }
 // The function returns whether the sudoku can be solved or not
  
 // the function receives the parameter of array of sudoku and outputs the sudoku grid screen with answers that is in different color
 void outputanswer(int sudoku[9][9])
 {
     int sudoku2[9][9];
     for(int vertical1=0;vertical1<9;vertical1++)
         {
            for(int horizontal1=0;horizontal1<9;horizontal1++)
            {
               sudoku2[vertical1][horizontal1]=sudoku[vertical1][horizontal1];       //Replicate the sudoku array
            }
         }
     sudokusolver(sudoku2);
     cout << endl;
     setcolor(3);
     cout << "        1   2   3   4   5   6   7   8   9" << endl;
     
     for(int vertical=0;vertical<9;vertical++)
     {
           if((vertical>=0)&&(vertical<3))
           {
               setcolor(14);       
               cout << "      ____________";
               setcolor(15);
               cout << "____________";
               setcolor(14);
               cout << "_____________" << endl;
             //  cout << "|";
           } 
           else if((vertical>2)&&(vertical<7))
           {
               setcolor(15);       
               cout << "      ____________";
               setcolor(14);
               cout << "____________";
               setcolor(15);
               cout << "_____________" << endl;
              // cout << "|";
           }
           else if((vertical>6)&&(vertical<9))
           {
               setcolor(14);       
               cout << "      ____________";
               setcolor(15);
               cout << "____________";
               setcolor(14);
               cout << "_____________" << endl;
              // cout << "|";               
           }
           setcolor(3);
           cout << "  " << vertical+1;    
           setcolor(8);
           cout << "   |";
           for(int horizontal=0;horizontal<9;horizontal++)
           {
               
              if((sudoku2[vertical][horizontal])==0)
              {     
                 cout << "   |";
              }
              else
              {
                 setcolor(15);
                 if (sudoku[vertical][horizontal]==0)
                 {
                    setcolor(4);
                 }
                 cout << " " << sudoku2[vertical][horizontal];
                 setcolor(15);
                 cout << " |";
                 setcolor(15);
              }
           }
           cout << endl;
     }
     setcolor(14);       
     cout << "      ____________";
     setcolor(15);
     cout << "____________";
     setcolor(14);
     cout << "_____________" << endl;  
     setcolor(15);  
     cout<<"White- what's given"<<endl;
     cout<<"Red- the answer"<<endl;
 }                                
 // function returns nothing 
                                    
int main()
{
    
    srand ( time(NULL) );                        //Initialize the random generator 
    int isudoku[9][9]={0},                       //The sudoku with 81 grids
    isudoku2[9][9]={0},                          //The replicate of the sudoku
    isudoku3[9][9]={0},                          //The replicate of the sudoku
    horizontal,vertical,                         //The horizontal and vertical coordinate that the user will input
    inum,                                        //The number that the user will input
    counter,                                     //The number that need to be erased
    erasednumber=0,                              //The number erased
    rand1,rand2,                                 //The random horizontal and vertical coordinate
    currentplayertime=0,                         //The name and time of the player
    etime1, etime2, etime3, mtime1, mtime2, mtime3, htime1, htime2, htime3, // used to store the times for each difficult's rank
    length1, length2, length3,                   // used to store length of different parts of the string 
    ichoice1 = 0,                                // used to store if program needs to output the instructions option again
    anum;
    
    string ranks,                                //The string variable used to store the .txt file's text
    easy1 = "N/A", easy2 = "N/A", easy3 = "N/A", 
    medium1 = "N/A", medium2 = "N/A", medium3 = "N/A", 
    hard1 = "N/A", hard2 = "N/A", hard3 = "N/A", // used to store the names for each difficulty's rank, set as N/A for default
    currentplayername,                           // used to store the current player's name 
    schoice,                                     //The choice that the user will input
    sname,                                       // used to store the saved / loaded string value of sudoku user previously played                                 
    ranks11, ranks12, ranks13, ranks14, ranks15, ranks16, ranks17, ranks18, ranks19, // used to store the converted string value of the integer value of time 
    stin[81]={" "};                              // used to store the loaded / saved integer value of sudoku user previously played
       
    bool bnosolution,banswer,                    //The boolean variable that represents if there is a solution for the solver and is the answer correct
    load = false;                                // used to store whether the ranks are loaded or not
    bool saved;
    
    char cchoice,                                //The choice that the user will input
    ranks0[33], ranks2[33], ranks3[33], ranks4[33], ranks5[33], ranks6[33], ranks7[33], ranks8[33], ranks9[33]; // char arrays used to store converted integer value as char
    
    do
    {
     
       erasednumber=0;                           //Initialize the numbers that has been erased as 0
       counter=0;                                //Initialize the numbers that needs to be erased as 0
       cout<<"-----------------------------\n";
       cout<<"|Welcome to the Sudoku Game!|\n";
       cout<<"-----------------------------\n\n";
       
       if (ichoice1 != 1)
       {
          cout<<"Would you like to read the instructions? Type in lowercase yes for instructions or anything else to skip.\n";
          cin >> schoice;
       
          if (schoice.compare("yes") == 0)
          {
             system ("CLS");
             setcolor(13);
             cout<<"The objective of Sudoku is to enter a digit from 1 through 9 in each cell, in such a way that:\n";
             cout<<"Each horizontal row contains each digit exactly once\n"; 
             cout<<"Each vertical row contains each digit exactly once\n";                //Output the instructions of the game to the user
             cout<<"Each subgrid or region (3x3) contains each digit exactly once\n"<<endl; 
             setcolor(7);
          }
          ichoice1++;
       }       

       do
       {
          saved=false;
          banswer=true;
          for(int icounter1=0;icounter1<9;icounter1++)
          {
             for(int icounter2=0;icounter2<9;icounter2++)
             {
                isudoku[icounter1][icounter2]=0;                                    //Initialize the sudoku and its duplication as 0(empty) 
                isudoku2[icounter1][icounter2]=0;
             }
          }
          
          cout << "\nWould you like to play the game or the Sudoku solver? (type game or solver)\n";                 //Ask the user whether he wants to play game or use the solver
          cin >> schoice;                                                           //Store the answer as variable

          if(schoice.compare("game")==0)                                            //If the user wants to play the game, then enter the following:
          {
             for(int icounter=0;icounter<81;icounter++)
                     stin[icounter]=" ";
             system("CLS");
             
             if (load == false)                                                     // if the program has not loaded ranks yet
             {
                ifstream loadFile;                                                  // ifstream: Stream class to read from files (i stands for input, f stands for file
                       
                loadFile.open ("Save.txt", ifstream::in);                           // opens save.txt file for it to input its data into program                           
                
                getline (loadFile, ranks);                                          // retrieves the txt file, assigns it to variable ranks            
                   
             
                
                if (ranks.compare("") == 0)                                         // if there are no previous txt file created, it will assign default values and create the new txt file
                   {
                      ranks = "ht1 9999 ht2 9999 ht3 9999 ht4 mt1 9999 mt2 9999 mt3 9999 mt4 et1 9999 et2 9999 et3 9999 et4 h1 " + hard1 + " h2 " + hard2 + " h3 " + hard3 + " h4 m1 " + medium1 + " m2 " + medium2 + " m3 " + medium3 + " m4 e1 " + easy1 + " e2 " + easy2 + " e3 " + easy3 + " e4 ";
                   }
                
                /*
                The following extracts data from either the saved data or default data into corresponding variables
                The identifiers ht, mt, h etc are used to identify which data is used for which purpose and where exactly they should be saved.
                by subtracting e2 - e1, it figures out what easy1 is.
                */
                   
                length2 = ranks.find("e1") + 3;
                length1 = ranks.find("e2") - length2 -1;
                easy1 = ranks.substr (length2, length1);
                
                length2 = ranks.find("e2") + 3;
                length1 = ranks.find("e3") - length2 -1;
                easy2 = ranks.substr (length2, length1);
                
                length2 = ranks.find("e3") + 3;
                length1 = ranks.find("e4") - length2 -1;
                easy3 = ranks.substr (length2, length1);
                
                length2 = ranks.find("m1") + 3;
                length1 = ranks.find("m2") - length2 -1;
                medium1 = ranks.substr (length2, length1);
                
                length2 = ranks.find("m2") + 3;
                length1 = ranks.find("m3") - length2 -1;
                medium2 = ranks.substr (length2, length1);
                
                length2 = ranks.find("m3") + 3;
                length1 = ranks.find("m4") - length2 -1;
                medium3 = ranks.substr (length2, length1);
                
                length2 = ranks.find("h1") + 3;
                length1 = ranks.find("h2") - length2 -1;
                hard1 = ranks.substr (length2, length1);
                
                length2 = ranks.find("h2") + 3;
                length1 = ranks.find("h3") - length2 -1;
                hard2 = ranks.substr (length2, length1);
                
                length2 = ranks.find("h3") + 3;
                length1 = ranks.find("h4") - length2 -1;
                hard3 = ranks.substr (length2, length1);
                
                
                
                length2 = ranks.find("et1")+4;
                length1 = ranks.find("et2") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> etime1;
                
                
                
                length2 = ranks.find("et2")+4;
                length1 = ranks.find("et3") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> etime2;
                
                length2 = ranks.find("et3")+4;
                length1 = ranks.find("et4") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> etime3;
                
                length2 = ranks.find("mt1")+4;
                length1 = ranks.find("mt2") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> mtime1;
                
                length2 = ranks.find("mt2")+4;
                length1 = ranks.find("mt3") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> mtime2;
                
                length2 = ranks.find("mt3")+4;
                length1 = ranks.find("mt4") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> mtime3;
                
                length2 = ranks.find("ht1")+4;
                length1 = ranks.find("ht2") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> htime1;
                
                length2 = ranks.find("ht2")+4;
                length1 = ranks.find("ht3") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> htime2;
                
                length2 = ranks.find("ht3")+4;
                length1 = ranks.find("ht4") - length1 - 1;
                istringstream (ranks.substr (length2, length1)) >> htime3;
                
                
                loadFile.close();                                                   // closes the opened file for future usage
                load = true;                                                        // indicates to program the file is loaded
             }
             
             sudokusolver(isudoku);                                                 //Randomly generate a completed sudoku
             cout << "You chose to play the Sudoku game" << endl;
             cout << "Which level of difficulties do you want to play? (H for hard; M for medium; E for easy; L for loading last saved game)\n";    //Ask the user for the level of difficulties
             cchoice=getch();                                                                                             //Store the answer as variable
             cout << endl;
        
             switch (cchoice)
             {
                case 'h': counter = 40;                                             // if user chose hard, numbers that needs to be erased will be set as 40
                          break;
                case 'm': counter = 30;                                             // if user chose medium, program erases 10 less grids than hard
                          break;
                case 'e': counter = 20;                                             // if user chose easy, program erases 20 less grids than hard
                          break;
                case 'l': counter =0;
                          break;
                default:  counter = -1;                                              // if user inputted something other than h m or e, counter is set to 0 for error trapping purpose
                          break;
             }  
       
             erasednumber=0;
           
             if(counter==-1)                                                         //if the number to be erased is 0 then output invalid input 
             {                                           
                cout<<"Invalid input"<<endl;           
             }
             else
             {                                                                      //if the number to be erased is not 0 then
                do 
                {
                   rand1 = rand()%9;                                                // random to get a vertical coordinate
                   rand2 = rand()%9;                                                // random to get a horizontal coordinate
       
                   if (isudoku[rand1][rand2] != 0)                                  // if this grid was NOT 0(erased)
                   {
                      isudoku[rand1][rand2] = 0;                                    // grid is erased
                      erasednumber++;                                               // the number that has been erased increases for one
                   }
                } while (erasednumber <counter); 
                        
                if (counter==0)
                {  
                   cout<<"Do you want to load? Type in 'yes' to save."<<endl;
                   cin>>schoice;
                   if (schoice.compare("yes")==0)
                   {
                      ifstream loadFile;                                               // ifstream: Stream class to read from files (i stands for input, f stands for file
                      loadFile.open ("Saved.txt", ifstream::in);
                      
                      while (loadFile.good()) // loadFile.good() checks whether stream is ready for i/o operations.
                      {
                         getline (loadFile, sname);         // retrieves the txt file, assigns it to variable username
     
                         for (int icounter=0;icounter<81;icounter++)
                         {
                            stin[icounter]=stin[icounter]+sname[icounter];      //Load the numbers into the sudoku
                            istringstream(stin[icounter])>>anum;
               
                            isudoku[icounter/9][icounter-icounter/9*9]=anum;
                         }
                      }                    
                   }
                   else
                   {
                   cout <<" \n Returning to the main menu...";
                   PressAKeyToContinue();
                   saved=true;
                   }
                                               
                }
                
                for(int icounter1=0;icounter1<9;icounter1++)                        //Duplicates another array as the original sudoku question
                {        
                   for(int icounter2=0;icounter2<9;icounter2++)
                   {
                      isudoku2[icounter1][icounter2]= isudoku[icounter1][icounter2];
                   }
                }
         if (saved==false){
                clock_t t;                                                          //Start the timer and assign a variable for it

                t= clock();
                
                do
                {
                   system("CLS");
                   outputsudoku(isudoku);                                           //Calls the function to output the current sudoku
          
                   cout<<"Input the horizontal component of the grid you want to input (1-9)"<<endl;
                   cin>>vertical;
                   cout<<"Input the vertical component of the grid you want to input(1-9)"<<endl;       //Ask the user to input the vertical and horizontal coordinate
                   cin>>horizontal;
           
                   cout<<"Enter the numbers you want to fill in the grid(1-9,0 to exit or save)"<<endl;      //Ask the user the number that he wants to put there
                   cin>>inum;
                   if ((inum>=1)&&(inum<=9)&&(vertical>=1)&&(vertical<=9)&&(horizontal>=1)&&(horizontal<=9))
                   {  //If the those numbers are in range of 1-9
                      if (isudoku2[vertical-1][horizontal-1]==0) 
                      {//And the original sudoku of that point is empty
                         isudoku[vertical-1][horizontal-1]=inum;                    //Then fill in the grid to the number that the user input
                      }
                      else
                      {                                               
                         cout<<"You can't change what's given"<<endl;               //If the original sudoku of that grid is not 0 then tell user that they can't change that
                         PressAKeyToContinue();                                     //Calls the function of press any key to continue
                      }
                   
                   }
                   else
                   {
                      if (inum!=0)
                      {                                                             //If the number inputted is 0 then output that the game is going to end
                         cout<<"The number is invalid"<<endl;                       //Else output invalid input
                      }
                      else
                      {
                          
                       
                         cout<<"The game is going to end"<<endl;
                      }
                   PressAKeyToContinue();                                           //Call to the function of press any key to continue
                   }
           
                   system("cls"); 
                   
                }while(inum!=0);                                                    //Loop until the user wants to finish the game
                                                                                                       
                sudokusolver(isudoku2);                                             //Solve the sudoku using the solver function
             
                for(int icounter1=0;icounter1<9;icounter1++)
                {
                   for(int icounter2=0;icounter2<9;icounter2++)
                   {
                      if (isudoku2[icounter1][icounter2]!= isudoku[icounter1][icounter2])
                      { //Check whether all the numbers are the same in every grid 
                      
                         banswer=false;
                      }
                   }
                }   
                if (banswer==false)
                { 
                   cout<<"Do you wish to save? Type in 'yes' to save."<<endl;
                   cin>>schoice;
                   if (schoice.compare("yes")==0)
                   {
                      ofstream saveFile ("Saved.txt");              // output stream opened for program to output to Save1.txt file
                      for (int icounter=0;icounter<9;icounter++)
                      {
                         for (int icounter2=0;icounter2<9;icounter2++)
                         {                                                    //Save all the grids into txt file
                            saveFile << isudoku[icounter][icounter2];                       
                         }
                      }
                      saveFile.close();                             // closes the opened file for future usage
                      
                      cout<<"Saving successful!"<<endl;
                      for(int icounter1=0;icounter1<9;icounter1++)
                      {
                         for(int icounter2=0;icounter2<9;icounter2++)
                         {
                            isudoku[icounter1][icounter2]=0;                                    //Initialize the sudoku and its duplication as 0(empty) 
                            isudoku2[icounter1][icounter2]=0;
                         }
                      }
                   }
                   else
                   {     
                      cout<<"The answer is wrong. The correct solution should be: "<<endl;
                      //If no then output that the answer is wrong and the correct solution                                         
                 
                      outputanswer(isudoku);
                      t = clock() - t;
                      t = t/1000;
                      cout<<"You used "<<t<<" seconds to finish this game"<<endl; //Output the time spent in this game
                           PressAKeyToContinue();
                   }
                }
                else
                {                                                                   //If the answer is correct output the time
                   cout<<"The answer is correct!"<<endl;       
           
                   t = clock() - t;
                   t = t/1000;
                   cout<<"You used "<<t<<" seconds to finish this game\n\n";
                   cout<<"Please input your name\n";                            //And ask for the name of the player
                   cout<<"NOTE: Spaces in your name are not allowed!\n";
                   cin >> currentplayername;                                    // stores the user's name into string variable currentplayername
                   
                   
                   ofstream saveFile ("Save.txt");                              // opens the file save.txt as saveFile 
                   
                   system ("CLS");
                   
                   
                   /*
                   if the user chose to play different modes, the program will delete the difficulty mode's currently existing data, and overwrite the new data.
                   the integer variables are converted to string (itoa functions -> char -> string) for it to be used by string functions
                   the previously existing data are filled with blank spaces, and new data will be overwritten
                   
                   The program outputs the previous ranks, indicates whether user is in top 3 of the ranks and replaces the new data if applicable.
                   */
                   switch (cchoice)
                   {
                      case 'h':                                                 
                                
                                itoa (htime1, ranks0, 10);
                                itoa (htime2, ranks2, 10);
                                itoa (htime3, ranks3, 10);
                                ranks11 = ranks0;
                                ranks12 = ranks2;
                                ranks13 = ranks3;
                                
                                length3 = ranks11.length();
                                length2 = ranks.find("ht1")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = ranks12.length();
                                length2 = ranks.find("ht2")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = ranks13.length();
                                length2 = ranks.find("ht3")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = hard1.length();
                                length2 = ranks.find("h1")+3;
                                ranks = ranks.replace(length2, length3, " ");
                               
                                length3 = hard2.length();
                                length2 = ranks.find("h2")+3;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = hard3.length();
                                length2 = ranks.find("h3")+3;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                
                                cout << "The current rankings are\n";
                                cout << "\n First place : "<< hard1 << " " << htime1 <<" seconds";
                                cout << "\n Second place: "<< hard2 << " " << htime2 <<" seconds";
                                cout << "\n Third place : "<< hard3 << " " << htime3 <<" seconds";
                                
                                
                                if (t < htime1)
                                {
                                   hard3 = hard2;
                                   hard2 = hard1;
                                   hard1 = currentplayername;
                                   
                                   htime3 = htime2;
                                   htime2 = htime1;
                                   htime1 = t;
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                else if (t < htime2)
                                {
                                   hard3 = hard2;
                                   hard2 = currentplayername;
                                   htime3 = htime2;
                                   htime2 = t;
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                else if (t < htime3)
                                {
                                   hard3 = currentplayername;
                                   htime3 = t;                                   
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                else if (t > htime3)
                                {
                                   cout <<"\nYour time is " <<t<< " seconds. You did not make into the top 3rd!\n Try harder next time.";
                                }
                                
                                itoa (htime1, ranks0, 10);
                                itoa (htime2, ranks2, 10);
                                itoa (htime3, ranks3, 10);
                                ranks11 = ranks0;
                                ranks12 = ranks2;
                                ranks13 = ranks3;
                                
                                
                                length2 = ranks.find("ht1")+4;
                                length1 = ranks.find("ht2") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks11);
                                
                                       
                                length2 = ranks.find("ht2")+4;
                                length1 = ranks.find("ht3") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks12);
                                          
                                length2 = ranks.find("ht3")+4;
                                length1 = ranks.find("ht4") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks13);
                                          
                                    
                                length2 = ranks.find("h1")+3;
                                length1 = ranks.find("h2") - length2 - 1;
                                ranks = ranks.replace (length2, length1, hard1);         
                                          
                                length2 = ranks.find("h2")+3;
                                length1 = ranks.find("h3") - length2 - 1;
                                ranks = ranks.replace (length2, length1, hard1); 
                                          
                                length2 = ranks.find("h3")+3;
                                length1 = ranks.find("h4") - length2 - 1;
                                ranks = ranks.replace (length2, length1, hard3);
                                          
                                break;

                      case 'm': itoa (mtime1, ranks4, 10);
                                itoa (mtime2, ranks5, 10);
                                itoa (mtime3, ranks6, 10);
                                ranks14 = ranks4;
                                ranks15 = ranks5;
                                ranks16 = ranks6;
                                
                                length3 = ranks14.length();
                                length2 = ranks.find("mt1")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = ranks15.length();
                                length2 = ranks.find("mt2")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = ranks16.length();
                                length2 = ranks.find("mt3")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = medium1.length();
                                length2 = ranks.find("m1")+3;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = medium2.length();
                                length2 = ranks.find("m2")+3;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = medium3.length();
                                length2 = ranks.find("m3")+3;
                                ranks = ranks.replace(length2, length3, " ");
                           
                           
                                cout << "The current rankings are\n";
                                cout << "\n First place : "<< medium1 << " " << mtime1 <<" seconds";
                                cout << "\n Second place: "<< medium2 << " " << mtime2 <<" seconds";
                                cout << "\n Third place : "<< medium3 << " " << mtime3 <<" seconds";
                                
                                
                                if (t < mtime1)
                                {
                                   medium3 = medium2;
                                   medium2 = medium1;
                                   medium1 = currentplayername;
                                   
                                   mtime3 = mtime2;
                                   mtime2 = mtime1;
                                   mtime1 = t;
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                else if (t < mtime2)
                                {
                                   medium3 = medium2;
                                   medium2 = currentplayername;
                                   mtime3 = mtime2;
                                   mtime2 = t;
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                else if (t < mtime3)
                                {
                                   medium3 = currentplayername;
                                   mtime3 = t;                                   
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                
                                else if (t > mtime3)
                                {
                                   cout <<"\n Your time is " <<t<< " seconds. You did not make into the top 3rd!\n Try harder next time.";
                                }
                                
                                itoa (mtime1, ranks4, 10);
                                itoa (mtime2, ranks5, 10);
                                itoa (mtime3, ranks6, 10);
                                ranks14 = ranks4;
                                ranks15 = ranks5;
                                ranks16 = ranks6;
                                
                                
                                length2 = ranks.find("mt1")+4;
                                length1 = ranks.find("mt2") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks14);
                                
                                       
                                length2 = ranks.find("mt2")+4;
                                length1 = ranks.find("mt3") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks15);
                                          
                                length2 = ranks.find("mt3")+4;
                                length1 = ranks.find("mt4") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks16);
                                          
                                    
                                length2 = ranks.find("m1")+3;
                                length1 = ranks.find("m2") - length2 - 1;
                                ranks = ranks.replace (length2, length1, medium1);         
                                          
                                length2 = ranks.find("m2")+3;
                                length1 = ranks.find("m3") - length2 - 1;
                                ranks = ranks.replace (length2, length1, medium1); 
                                          
                                length2 = ranks.find("m3")+3;
                                length1 = ranks.find("m4") - length2 - 1;
                                ranks = ranks.replace (length2, length1, medium3);
                                          
                                break;                                             
                               
                      default:  
                                itoa (etime1, ranks7, 10);
                                itoa (etime2, ranks8, 10);
                                itoa (etime3, ranks9, 10);
                                ranks17 = ranks7;
                                ranks18 = ranks8;
                                ranks19 = ranks9;
                                
                                cout << "The current rankings are\n";
                                cout << "\n First place : "<< easy1 << " " << etime1 <<" seconds";
                                cout << "\n Second place: "<< easy2 << " " << etime2 <<" seconds";
                                cout << "\n Third place : "<< easy3 << " " << etime3 <<" seconds";
                                cout << "\n Your time is " <<t<< " seconds."; 
                                
                                length3 = ranks17.length();
                                length2 = ranks.find("et1")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                
                                length3 = ranks18.length();
                                length2 = ranks.find("et2")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                                                
                                length3 = ranks19.length();
                                length2 = ranks.find("et3")+4;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                
                                length3 = easy1.length();
                                length2 = ranks.find("e1")+3;
                                ranks = ranks.replace(length2, length3, " ");
                                                                
                                length3 = easy2.length();
                                length2 = ranks.find("e2")+3;
                                ranks = ranks.replace(length2, length3, " ");
                                
                                length3 = easy3.length();
                                length2 = ranks.find("e3")+3;
                                ranks = ranks.replace(length2, length3, " ");
                                                                
                                if (etime1 > t)
                                {
                                   easy3 = easy2;
                                   easy2 = easy1;
                                   easy1 = currentplayername;
                                   
                                   etime3 = etime2;
                                   etime2 = etime1;
                                   etime1 = t;
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                else if (etime2 > t)
                                {
                                   easy3 = easy2;
                                   easy2 = currentplayername;
                                   
                                   etime3 = etime2;
                                   etime2 = t;
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                else if (etime3 > t)
                                {
                                   easy3 = currentplayername;
                                   etime3 = t;                                   
                                   cout <<" \n NEW HIGH SCORE!";
                                }
                                
                                
                                else if (t > etime3)
                                {
                                     cout <<"You did not make into the top 3rd!\n Try harder next time.";
                                }
                                
                                itoa (etime1, ranks7, 10);
                                itoa (etime2, ranks8, 10);
                                itoa (etime3, ranks9, 10);
                                ranks17 = ranks7;
                                ranks18 = ranks8;
                                ranks19 = ranks9;
                                
                                
                                length2 = ranks.find("et1")+4;
                                length1 = ranks.find("et2") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks17);
                                                                       
                                length2 = ranks.find("et2")+4;
                                length1 = ranks.find("et3") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks18);

                                length2 = ranks.find("et3")+4;
                                length1 = ranks.find("et4") - length2 - 1;
                                ranks = ranks.replace(length2, length1, ranks19);
                                    
                                length2 = ranks.find("e1")+3;
                                length1 = ranks.find("e2") - length2 - 1;
                                ranks = ranks.replace (length2, length1, easy1);         

                                length2 = ranks.find("e2")+3;
                                length1 = ranks.find("e3") - length2 - 1;
                                ranks = ranks.replace (length2, length1, easy2); 

                                length2 = ranks.find("e3")+3;
                                length1 = ranks.find("e4") - length2 - 1;
                                ranks = ranks.replace (length2, length1, easy3);                                         
                                break;
                  
                   }
                   saveFile << ranks;                                 // saves the data stored in variable ranks into txt file save.txt
                   
                   saveFile.close();                                  // closes the file for further usage
                }
                
             }
             }
          }
          
          //If the user want to use the solver
          else if(schoice.compare("solver")==0)                                         
          {
              do
              {
                 system("cls");
                 outputsudoku(isudoku);  
                 cout<<"Input the horizontal component of the grid you want to input"<<endl;
                 cin>>vertical;
                 cout<<"Input the vertical component of the grid you want to input"<<endl;                //Ask the user to input the vertical and horizontal coordinate
                 cin>>horizontal;
                 cout<<"Enter the numbers you want to fill in the grid(1-9,0 to exit)"<<endl;               //Ask the user the number that he wants to put there
                 cin>>inum;
            
                 if ((inum>=1)&&(inum<=9)&&(vertical>=1)&&(vertical<=9)&&(horizontal>=1)&&(horizontal<=9))
                 {  //If the those numbers are in range of 1-9
                 
                    isudoku[vertical-1][horizontal-1]=inum;                                                  //Then fill in the grid to the number that the user input
                 }
                 else
                 {
                    if(inum!=0)
                    cout<<"The number is invalid. "<<endl;                                                   //If the numbers are not in the range output invalid input
                    else{cout<<"The program is going to end"<<endl;}
                    PressAKeyToContinue();
                 } 
               
             }while(inum!=0);
             for(int vertical1=0;vertical1<9;vertical1++)
         {
            for(int horizontal1=0;horizontal1<9;horizontal1++)
            {
               isudoku2[vertical1][horizontal1]=isudoku[vertical1][horizontal1];       //Replicate the sudoku array
            }
         }
             if (sudokusolver(isudoku)==false)
             {                                                                      //If there are solution for this sudoku then output the answer
                cout<<"The correct solution is"<<endl;
                outputanswer(isudoku2);
          
             }
             else 
             cout<<"There is no solution for this sudoku"<<endl;                    //Or else output that there is not solution
          }
          else
          {
             cout << "Invalid Input. Please Try again." << endl;                    //If the numbers are not between 1-9 output invalid input
          }    
       schoice="game";
       }while((schoice.compare("game")!=0) && (schoice.compare("solver")!=0));      //If the input is not game or solver keep looping
      
       cout<<"\n\nDo you wish to continue? Type Leave or anything else to play again!"<<endl;  //Ask the user whether he wants to exit or now
       cin>>schoice;
       
       
       system("CLS");
  
    }while(schoice.compare("leave")!=0);                                                       //If the user type leave then exit the program
    
    

    cout <<" Thank you for playing Sudoku.96! \n";
    cout <<" Sudoku made by: \n\n";
    cout <<" Frank Han (Leader)\n";
    cout <<" Dae Ho Lee \n";
    cout <<" Howard Tsai \n";
    cout <<" Ivan Zhou \n";
    
    system("Pause");
    return 0;
}
/*
Reference used

Turn string into integer: http://www.cplusplus.com/forum/general/13135/
Save and load:http://www.cplusplus.com/forum/beginner/36080/
Gotoxy: http://www.cplusplus.com/forum/general/33846/
Color:http://www.cplusplus.com/forum/beginner/91349/
Time :  http://www.cplusplus.com/reference/ctime/time/?kw=time
*/
