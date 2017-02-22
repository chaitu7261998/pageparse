#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

string preparse(string);

void pretest(string problem, string temp);

int main()
{

	string page_url = "curl http://codeforces.com/problemset/problem/";

	string problem_code;

	cout << "Enter the problem code" << endl;
	cin >> problem_code ;

	string problem = problem_code;

	problem_code.insert(3, 1, '/');

	cout << problem_code << endl;

	page_url = page_url + problem_code + " > source.txt";

	char page_url_char[70];

	for(int i=0; i < page_url.size() ; i++) page_url_char[i] = page_url[i];

	page_url_char[page_url.size()] = '\0';	

	//system(page_url_char);

	//system("subl source.txt");

	ifstream source_of_page("source.txt");

	string lines;

	string inputs;

	size_t pos, endpos;
	while(source_of_page.good())
  	{
      	getline(source_of_page,lines); // get line from file
      	pos=lines.find("<pre>"); // search
      	if(pos!=string::npos) // string::npos is returned if string is not found
        {
        	endpos = lines.rfind("</pre>");
        	inputs = lines.substr(pos, endpos-pos+6);
            cout <<"Found!\n";
            cout << pos << endl;
            break;
        }
 	}

 	cout << inputs << endl;

 	ofstream outputs("new_source.txt");

 	outputs << inputs;

 	outputs.close();
 	source_of_page.close();
 	
 	

	ifstream source_text("new_source.txt");

	string inputs2;

	getline(source_text, inputs2);

	source_text.close();

	//cout << inputs << endl;

	string temp;

	int pos2=0, endpos2=0;
	int binar=0; //For writing "Input" & "Output"

	ofstream ioputs("ioputs.txt");

	while(true)
	{
		pos2 = inputs2.find("<pre>", pos2) + 5;
		endpos2 = inputs2.find("</pre>", endpos2+1);
		if(endpos2 == string::npos) break;

		temp = inputs2.substr(pos2, endpos2-pos2);

		//cout << temp << endl;
		
		temp = preparse(temp);
		if(binar%2 == 0 ) 
		{
			ioputs << "Input\n";

			ofstream test_input("testcase.txt");
			test_input << temp;
		}
		else 
		{
			ioputs << "Output\n";
			pretest(problem,temp);
		}
		binar++;

		ioputs << temp;
	}

	//pretest(problem);


	

	return 0;
}


string preparse(string temp)
{
	int pos, endpos;

	while(true)
	{
		pos = temp.find("<br />");
		if(pos == string::npos) break;

		temp.replace(pos, 6, "\n");
	}

	cout << temp << endl;

	return temp;

}

void pretest(string problem, string temp)
{
	problem = "g++ " + problem + ".cpp";

	char prob[12];
	for(int i=0; i<problem.size(); i++) prob[i] = problem[i]; 
	prob[problem.size()] = '\0';	

	system(prob);
	
	system("./a.out < testcase.txt > test_result.txt");  //send input from textcase.txt to ./a.out 

 	ifstream test_result("test_result.txt");		     //and saving ouput in test_result.txt

 	string output;
 	getline(test_result, output);

 	temp.pop_back();

 	cout << output.size() << endl;
 	cout << temp.size() << endl;

 	if(output.compare(temp) == 0) cout << "PASSED!" << endl;
 	else cout << "FAILED!" << endl;

}