//Valay Brahmbhatt
//Comp 271
//04-27-2016

/*Note: Tutoring with Tom Biju, Tara, and Abdul*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//Declaring my functions
int Quadratic_Probing(int the_hash_table[], int index, int max);
int Extraction_Method(int noms);


int main()
{
    ifstream thisfile;      //input file stream
    ofstream outfile;       //output file stream
    string file_name;       //a string called filename
    string file_name2;      //a string called filename2
    string cold;        //a string called cold
    int Enter_number;       //enter number for quadratic probing
    int i;

    int * thehashtable;
    thehashtable = new int [70000];     //create a hash table of 70,000

    for(i = 0; i < 70000; i++)
    {
        thehashtable[i] = 0;        //indexes of array = 0
    }

    cout << "Well hello there!" << endl;
    cout << "What is the name of the file: ";       //console output name of file
    getline(cin, file_name);         //user input the name of the file
    thisfile.open(file_name.c_str());       //c-style string, open the input file

    while(thisfile.fail())      //if the user input wrong file then
                                //console asks the user to input the correct file
    {
        cout << file_name << " " << "file not found" << endl;
        cout << "Enter in another file: ";
        getline(cin, file_name);
        thisfile.open(file_name.c_str());
    }

    vector <int> random;        //created a vector to store all number from the thisfile
    while(thisfile)     //read file line by line
    {
        getline(thisfile, file_name);
        istringstream out(file_name);
        while(getline(out, cold, ','))
        {
            random.push_back(atoi(cold.c_str()));
        }

    cout << "Enter a number between 1 and 450,000,000: ";
    cin >> Enter_number;

    Enter_number = Enter_number % 70000;

    while(!(Enter_number >= 0 && Enter_number <= 450000000))
    {
        cout << "Enter a number between 0 and 450000000: " << endl;
        cin >> Enter_number;
    }

    int the_index;
    for(i = 0; i < random.size(); i++)      //didn't cout everything, makes the console a lot cleaner
    {
        the_index = Extraction_Method(random[i]);       //storing the extracted address of number from the input file
        if(thehashtable[the_index] == 0)        //address is found, store the number
        {
            thehashtable[the_index] = random[i];
            //cout << random[i] << " No Collision " << endl;
        }
        else
        {//address isn't found, quadratic probing
            the_index = Quadratic_Probing(thehashtable, the_index, Enter_number);
            if(the_index == -1)
            {
                //cout << "Full table" << endl;
            }
            else
            {
                thehashtable[the_index] = random[i];        //quadratic probing places numbers into next index
                //cout << random[i] << "Collision!" << endl;
            }
        }
    }

    if(thisfile.is_open())      //if thisfile is open
    outfile.open("hashed_socials.txt");     //open an output text file
    for(int i = 0; i < 70000; i++)      //write out the hash table to the output file
    {
        outfile << thehashtable[i];
        if(i < 69999)
            {
                outfile << ',';
            }
    }
    thisfile.clear();       //clear the input file
    outfile.clear();        //clear the output file
	thisfile.close();       //close the input file
    outfile.close();        //close the output file


    //double checking the extraction method
    //cout<< Extraction_Method(123456789) << endl;
    }

    cout << endl;       //space
    cout << "Output file is created" << endl;       //console output, output file is created
    cout << "Done, good job!" << endl;      //words of encouragements
    return 0;
}

int Quadratic_Probing(int the_hash_table[], int index, int max)     //Quadratic Probing without replacement method
//max parameter same as to the console input in main
{
    int now, ran, i;
    now = index % 70000;      //console input determines index
    ran = 1;
    for(i = 1; i < 70000; i++)     //check to see if the index is actually 0
    {
        if(the_hash_table [(now + (max + i)*(max + i)) % 70000] == 0)
            {
                return index;
            }
    }
    return false;       //table goes crazy, overflow
}

int Extraction_Method(int noms)     //extraction method
{
    //string x = to_string(noms);
    //I have C++11 but CodeBlocks doesn't run to_string
    //hence the following few lines
    string x = "000000000";
    char *xP = new char[100];
    sprintf(xP, "%i", noms);
    string m = (string) xP;

    int j = 0;
    int i;

    for(i = 0; i < m.size(); i++)
    {
        x[i] = m[j];
        j++;
    }
    string y = "0000";      //extract from the 3th, 5th, 7th, 8th position
    y[0] = x[2];
    y[1] = x[4];
    y[2] = x[6];
    y[3] = x[7];

    return atoi(y.c_str());     //return the extracted position
}
