#pragma once
/////////////////////////////////////////////////////////////////////
//  DepAnal.h -    Dependency analysis for code analser            //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP EliteBook, Windows 10                        //
//  Application:   Dependency check, CSE 687- Sp17	    		    //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This package containes a class for dependency analysis. It store the outout in NoSql data base. Where the childrens 
represents the files on which "key" file depends on.

Public Interface:
=================
class: DepAnal

doDepAnal                                     //Does dependency analysis               
checksubstring                                //check if a string is a part of otherstring
hasdependency                                 //if file is dependent on other
NoSqlDb < std::string> getdepanal             //return dependency analysis.
dep_iftok                                    //check token in typetable
dep_forh                                     // check header file dependency

Build Process:
==============
Required files
- NoSqlDb.h; ActionaAndRules.h; Tokenizer; TypeAnal.h;
*  Build Command:
*  --------------
* devenv Project3.sln /rebuild debug

Maintenance History:
====================
ver 1.0

*/


/////////////////////////////////////////////////////////////////////
//Include dependency and c++ libraries
#include "../Parser/ActionsAndRules.h"
#include <iostream>
#include <functional>
#include <string>
#include <stack>
#include "../NoSqlDb/NoSqlDb.h"
#include "../Tokenizer/Tokenizer.h"
#include "../TypeTable/TypeAnal.h"



#pragma warning (disable : 4101)  // disable warning re unused variable x, below
using namespace NoSQLDB;
using namespace Scanner;
/////////////////////////////////////////////////////////////////////
//Namespace defination
namespace CodeAnalysis
{
/////////////////////////////////////////////////////////////////////
//Class defination
  class DepAnal
  {
  public:
    using SPtr = std::shared_ptr<ASTNode*>;
    DepAnal();
    bool doDepAnal(TypeTable TT, std::string);
	bool checksubstring(std::string sub_filename);
	bool hasdependency(std::vector<std::string> childrens,std::string filename);
	std::vector<std::string> namespacelist(TypeTable TT);
	Element<std::string> name_DbElem(std::string fileSpec);
	void dep_iftok(std::string fileSpec, std::vector<TTElement> Values, std::vector<std::string> NS);
	void dep_forh(Key fileSpec, std::vector<TTElement> Values, std::vector<std::string> NS);
	NoSqlDb < std::string> getdepanal();
  private:
    AbstrSynTree& ASTref_;
    ScopeStack<ASTNode*> scopeStack_;
    Scanner::Toker& toker_;
	NoSqlDb<std::string> depAnal;
  };
}