#pragma once
/////////////////////////////////////////////////////////////////////
// Publisher.h - Publish the code files in html format              //
// ver 1.0                                                          //
//-----------------------------------------------------------------//
//-----------------------------------------------------------------//
// Language:    C++, Visual Studio 2015                            //
// Platform:    Platform:      HP EliteBook, Windows 10            //
// Application: Project #3, CSE687 - Object Oriented Design, S2017 //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////
/*
/*
* Package Operations:
* -------------------
* This package defines Publish classes that convert all given pattern files
* to html format. It also displays the dependencies calculated by codeanalyser.



Public Interface:
=================
Publish class:


converthtm								//convert files to html format
replaceall								//replace one substring by another
addaccordition							//add show hide on scopes
updatefile								//update file by modified string
htmlformat								//add tags
addhtmltag								//add html tag
addheadtag								//add header tag
addbodytag								//add body tag
addpretag								//add pre tag
Indexfile								//create index file

Build Process:
==============
Required files
- CodeAnalyzer.h, DepAnal.h, TypeAnal.h, TypeTable.h, NoSqlDb.h, FileSystem.h, DepAnal.cpp, Publisher.cpp, TypeAnal.cpp
*  Build Command:
*  --------------
* devenv Project3.sln /rebuild debugs

* Maintenance History:
*---------------------
*ver 1.0 : 05 Apr 2017
* - first release
*/


/////////////////////////////////////////////////////////////////////
//Add dependencies and libraries
#include "../Analyzer/CodeAnalyzer.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "../Dep_Anal/DepAnal.h"
#include "../FileSystem/FileSystem.h"
#include <algorithm>
#include <string>
#include <fstream>

/////////////////////////////////////////////////////////////////////
//Add class Publish
using namespace NoSQLDB;
using namespace FileSystem;
class Publish
{
public:
	using Key = std::string;
	using Keys = std::vector<std::string>;
	Publish() {};
	Publish(NoSqlDb<Key> db_) : db(db_) {};
	bool converthtm(Key fileSpec, Key Htm_location);
	bool Indexfile(Keys files, Key Htm_location);
	bool replaceall(std::string &filename, const std::string& from, const std::string& to);
	std::string addaccordition(std::string filename);
	bool updatefile(std::string &filename, const std::string& strtxt);
	bool htmlformat(std::string &strtxt, Key fileSpec, Keys Dep);
	bool addhtmltag(std::string &strtxt);
	bool addheadtag(std::string &strtxt);
	bool addbodytag(std::string &strtxt, Key fileSpec, Keys Dep);
	bool addpretag(std::string &strtxt);
private:
	NoSqlDb<Key> db; // db contains dependency analysis
};
/////////////////////////////////////////////////////////////////////




