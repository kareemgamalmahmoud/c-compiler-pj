#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class prefix
{

private:
	ifstream input;				 //This file to get data as an input.
	ofstream output;			 //This file to dispaly the data as an output.
public:
	prefix(string filename)		//A constructor to open the file .
	{
		input.open(filename);
		if (!input)				// if the name of the file does not exist this message appears.
		{
			cout << "This file does not exist !" << endl;
		}
	}

	~prefix()					//A distructor to close the file after readding from it.
	{
		input.close();
	}

	void check()				//This is the function by which we will remove common prefix.
	{
		output.open("outPut.txt");

		string s;				//A string to put data in it (line by line).
		int dash_no = 1;		//I use this counter to make any nonterminal different from the one before when i remove common prefix.

		while (getline(input, s))	//This(while loop) get data line by line to the end of the file.
		{ 

			int size = s.length();				//In this part, I divided the line into two parts, one before the (=) and one after it.
			int index_of_equal = s.find('=');

			string before_equal = s.substr(0, index_of_equal + 1);
			string after_equal = s.substr(index_of_equal + 1, size - (index_of_equal + 1));
 
			if (after_equal.find('|') == -1)	//This (if statment) check if there is a separator(|) or not
			{									//because if there is no (|) it mean this is a normal statment  
				output << s << "\n";			//and do not need to check if there is a prefix or not.
			}
			else
			{
				vector <string> vec(1);					//I use vector ,because it is easier to store and recall data.
				string sub_string_from_after_equal;

				for (int i = 0; i < after_equal.length(); i++)			//I use this (for loop) to put all the part before (|) in a Victor
				{														//and also the part after it.
					if (after_equal[i] != '|')
					{
						sub_string_from_after_equal += after_equal[i];
					}
					else
					{
						vec.push_back(sub_string_from_after_equal);
						sub_string_from_after_equal = "";
					}
				}
				vec.push_back(sub_string_from_after_equal);
 
				/*
					In this part I bring the common prefix,
					by comparing the first element in the vector with others in this vector.
					And i use this flag to make sure that the prefix i have take is a common prefix. 
				*/
				string prefix_string;
				string compare_string = vec[1];		//i put the first elemet's data in (compare_string) to don changes on it.
				bool flag = true;

				/*
				for (int i = 2; i < vec.size(); i++)				//Here it allows me to find the common prefix in all elements.
				{													//This prevents the appearance of the production rull that does not contain a common prefix.
					while (vec[i].find(compare_string) != 0)
					{
						compare_string = compare_string.substr(0, compare_string.length() - 1);
					}
				}
				*/

				while (vec[2].find(compare_string) != 0)		//so, i use this (while loop) to get the common prefix from the first two elements in the vector.
				{
					compare_string = compare_string.substr(0, compare_string.length() - 1);
				}

				prefix_string = compare_string;

				if (prefix_string.length() == 0)
					flag = false;

				
				if (!flag)							//if (flag) is false so, this statment has no common prefix
					output << s << "\n";			//And if is not so, Steps to display statment in the file start.
				else
				{	//I've set (*) in the beginnnig of each stetment have common prefix for excellence and ease of vision								
					output << " *** " << before_equal << " " << prefix_string << " <x'" << dash_no << ">";
					for (int i = 1; i < vec.size(); i++)			//This (for loop) to display the producition rull which has no common prefix.
					{
						if (vec[i].find(prefix_string) != 0)
							output << " | " << vec[i];
					}
					output<< "\n";
					//------------------(The line below)-----
					output << "   <x'" << dash_no << ">";				//As we explained above (dash_no) used to make each nonterminal different.
					output << " ::= ";
					for (int i = 1; i < vec.size(); i++)
					{
						if (vec[i].find(prefix_string) == 0)
						{
							if (vec[i].substr(prefix_string.length(), vec[i].length()).find(' ') == 0) //if the vector become empty after we take the prefix
								output << "E";														   //so, we put ("E") as an Epsilon.
							if (i > 1)
							{
								output << " | " << vec[i].substr(prefix_string.length(), vec[i].length());
							}
							else
							{
								output << vec[i].substr(prefix_string.length(), vec[i].length());
							}
						}
					}
					output << "\n";
					dash_no++;
				}

			}
		}
	}
};

void main()
{
	//I have set the option to choose between displaying an example of (mini-java-BNF-grammer) or choosing the name of the file you want.
	do {
		int choose;
		string name_of_file;

		cout << "press (1) : To run an example of (mini-java-BNF-grammer) and other exampels in output file." << endl;
		cout << "press (2) : To choose the name of the file you want!" << endl;
		cout << "press (3) : To exit!" << endl << endl;
		cin >> choose;

		if (choose == 1)
		{
			prefix x("inPut.txt");
			x.check();
			x.~prefix();
			break;
		}
		else if (choose ==2)
		{
			cout << "Enter the name of your file : ";
			cin >> name_of_file;
			prefix x(name_of_file);
			x.check();
			x.~prefix();
			break;
		}
		else if (choose == 3)
		{
			break;
		}
		else
		{
			cout << "Unknown selection, try again!" << endl;
		}

	} while (true);

	system("pause");
}