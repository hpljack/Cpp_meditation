// chapter3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::vector;

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	string word;
	while(cin >> word){
		cout<<word<<endl;
	}
	*/

	//getline

	/*
	string line;
	while(getline(cin,line))
		cout<<line<<endl;
	*/
	
	string str("The expense of spirit\n");
	cout<<"The size of "<< str <<" is " <<str.size()
		<<" characters , includingg the newline"<<endl;


	for(string::size_type i = 0; i != str.size(); ++i)
		cout<<str[i]<<endl;

	string s = "hello world !! d  d  % $";
	string::size_type punct_cnt = 0;
	for(string::size_type i = 0; i != s.size(); ++i)
		if(ispunct(s[i]))
			++punct_cnt;
	cout<<punct_cnt
		<<" punctuation characters in "<< s << endl;


	for(string::size_type i = 0; i != s.size(); ++i)
		//s[i] = tolower(s[i]);
		s[i] = toupper(s[i]);
	cout<<s<<endl;
	
	vector_execrise();


	cin.get();
	return 0;
}


void vector_execrise(){

	string word;
	vector<string> text;
	while(cin>>word)
		text.push_back(word);

	for(vector<string>::size_type i = 0; i != text.size(); ++i)
		cout<<text[i]<<endl;
			
}