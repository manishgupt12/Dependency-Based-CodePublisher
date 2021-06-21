#pragma once
#pragma once
/////////////////////////////////////////////////////////////////////
// Executive.cpp - Test executive for project 3, CSE689, S17       //
// ver 1.0                                                          //
//-----------------------------------------------------------------//
//-----------------------------------------------------------------//
// Language:    C++, Visual Studio 2015                            //
// Platform:    Platform:      HP EliteBook, Windows 10            //
// Application: Project #3, CSE687 - Object Oriented Design, S2016 //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////
/*
/*
* Package Operations:
* -------------------
* This package gives an executive showing all requirements met in project 3



Public Interface:
=================
converthtm								//convert files to html format
replaceall								//replace one substring by another
addaccordition							//add show hide on scopes
updatefile								//update file by modified string
htmlformat								//add tags
addhtmltag								//add html tag
addheadtag								//add header tag
addbodytag								//add body tag
addpretag								//add pre tag


Build Process:
==============
Required files
- CodeAnalyzer.h, DepAnal.h, TypeAnal.h, TypeTable.h, NoSqlDb.h, FileSystem.h, DepAnal.cpp, Publisher.cpp, TypeAnal.cpp
- Publisher.cpp, Publisher.h
*  Build Command:
*  --------------
* devenv Project3.sln /rebuild debugs

* Maintenance History:
*---------------------
*ver 1.0 : 05 Apr 2017
* - first release
*/


#include "../Code_Publisher/Publisher.h"
#include "../Analyzer/CodeAnalyzer.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

/////////////////////////////////////////////////////////////////////
//using aliases and namespaces
using Path = std::string;
using Pattern = std::string;
using Patterns = std::vector<Pattern>;
using Filepath = std::string;
using Filepaths = std::vector<Filepath>;
using Ext = std::string;
using FileMap = std::unordered_map<Pattern, Filepaths>;
using namespace CodeAnalysis;
using namespace FileSystem;

/////////////////////////////////////////////////////////////////////
//Requirement 1
void requirement1()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Submitted by: Manish Gupta\n";
	std::cout << "Requirement 1:\n";
	std::cout << " Used Visual Studio 2015 and its C++ Windows Console \n Projects, as provided in the ECS computer labs.";
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Requirement 2
void requirement2()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 2:\n";
	std::cout << " using the C++ standard library's streams for all I/O and \n new and delete for all heap-based memory management";
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Requirement 3
std::string requirement3(NoSqlDb<std::string> depanal, Filepaths files_ )
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 3:\n";
	std::cout << " Uses publisher packages to create html for all pattern\n given in command line. \n";
	const std::string htmlocationDir = "../../Htm_file";  //html file will be created on this location
	Publish publish(depanal);
	Directory htmDir;
	if (htmDir.exists(htmlocationDir))
		htmDir.remove(htmlocationDir);
	htmDir.create(htmlocationDir);
	publish.Indexfile(files_, htmlocationDir);
	for (size_t t = 0; t < files_.size(); t++)
		publish.converthtm(files_[t], htmlocationDir);
	std::string currentdir = htmDir.getCurrentDirectory();
	return currentdir;
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Tytable and typeanalysis
TypeTable typetable_()
{
	TypeAnal ta;
	ta.doTypeAnal();
	TypeTable TT = ta.getTT();
	return TT;
}
/////////////////////////////////////////////////////////////////////
//dependency analysis
NoSqlDb<std::string>depanal_(TypeTable TT, Filepaths files_)
{
	DepAnal da;
	for (size_t t = 0; t < files_.size(); t++)
		da.doDepAnal(TT, files_[t]);
	NoSqlDb<std::string> depanal = da.getdepanal();
	return depanal;
}
/////////////////////////////////////////////////////////////////////
//Requirement 4
void requirement4()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 4:\n";
	std::cout << " Provides the facility to expand and collapse for all\n scopes in program. ";
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Requirement 5
void requirement5()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 5:\n";
	std::cout << "CSS style sheet - header.css and JavaScript - exp_coll.js \n available in the current directory ";
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Requirement 6
void requirement6()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 6:\n";
	std::cout << "CSS and JavaScript are linked to html files. ";
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Requirement 7
void requirement7()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 7:\n";
	std::cout << "Uses functionality from project 2 and shows dependencies at the top ";
	std::cout << "for clearity, full path of the dependent file is shown in header";
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Requirement 8
void requirement8(std::string currentdir, std::string html_filename)
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 8:\n";
	std::cout << "Uses command line argument for:\n ";
	std::cout << "1. Input directory, which contains the files of interest.\n ";
	std::cout << "2. File Patterns of interest.\n ";
	std::cout << "3. Name of index.html file, which will automatically open in the end.\n ";
	std::wstring temp = std::wstring(html_filename.begin(), html_filename.end());
	std::wstring temp_path = std::wstring(currentdir.begin(), currentdir.end());
	ShellExecute(NULL, L"open", temp.c_str(), NULL, temp_path.c_str(), SW_SHOWNORMAL);
	std::cout << "Index file contains link of all files.";
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Requirement 9
void requirement9()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 9:\n";
	std::cout << "\"Test_Important\" folder contains important packages in this project. ";
	std::cout << "\n---------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Requirement 10
void requirement10()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Requirement 10:\n";
	std::cout << " This is an automated unit test for codepublisher.  ";
	std::cout << " Function exceeding public data and Metric limits are in the\n files given by Professor which are not modified \n  ";
	std::cout << "\nThank you";
	std::cout << "\n---------------------------------------------------------\n";
}

/////////////////////////////////////////////////////////////////////
//Main test executive function
int main(int argc, char* argv[])
{
	CodeAnalysisExecutive exec;
	requirement1();
	requirement2();
	try {
		bool succeeded = exec.ProcessCommandLine(argc, argv);
		if (!succeeded)
			return 1;
		exec.getSourceFiles();  //get all files
		exec.processSourceCode(true); //process files
		exec.flushLogger();
		Filepaths files_ = exec.allFiles();
		TypeTable TT = typetable_();
		NoSqlDb<std::string> depanal = depanal_(TT, files_);
		std::string currentdir = requirement3(depanal, files_);
		std::string html_filename = exec.gethtml_filename(); //get command lines for html index name
		//html_filename = currentdir + html_filename;
		requirement4();
		requirement5();
		requirement6();
		requirement7();
		requirement8(currentdir, html_filename);
		requirement9();
		requirement10();		
	}
	catch (std::exception& except)
	{
		exec.flushLogger();
		std::cout << "\n\n  caught exception in Executive::main: " + std::string(except.what()) + "\n\n";
		exec.stopLogger();
		return 1;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////
//End functions