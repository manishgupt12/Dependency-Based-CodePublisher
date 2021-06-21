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


#include "Publisher.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

/////////////////////////////////////////////////////////////////////
// Aliases for files
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
//Convert to html
bool Publish::converthtm(Key fileSpec, Key Htm_location)
{
	try {
		std::ifstream in(fileSpec);
		if (!in.good()) {
			std::cout << "\n  can't open " << fileSpec << "\n\n";
			return false;
		}
		FileSystem::Path filename;				
		std::string file_name =filename.getName(fileSpec)+".html"; //get name and add .html
		Keys dependencies = db.value(fileSpec).children;   //get dependency
		std::string final_path = Htm_location+"\\"+file_name; //new location for the modified file
		FileSystem::File copyfile(fileSpec);
		copyfile.copy(fileSpec, final_path);   //copy at new location
		FileSystem::File readfile(final_path); //read file as string
		readfile.open(File::in, File::text);
		bool keepnewline = true;
		std::string filestr = readfile.readAll(keepnewline);
		readfile.close();                     //close file
		replaceall(filestr, "<", "&lt");	//replace all "<" and ">"
		replaceall(filestr, ">", "&gt");	
		htmlformat(filestr, fileSpec, dependencies);  //do other formatting
		updatefile(final_path, filestr);			//update file with new format
		std::string returnstr = addaccordition(final_path);  //accodition with file scope
		replaceall(returnstr, "}</div>;", "};</div>");
		updatefile(final_path, returnstr);					//update with accordition
	}
	catch (std::exception& ex) {
		std::cout << "\n  Exception: " << ex.what() << "\n";
	}
	return true;
}

/////////////////////////////////////////////////////////////////////
//Replace all substr with other substr
bool Publish::replaceall(std::string & filename, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;
	while ((start_pos = filename.find(from, start_pos)) != std::string::npos) {
		filename.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return true;
}

/////////////////////////////////////////////////////////////////////
//Add acordtion
std::string Publish::addaccordition(std::string filename)
{
	std::string accodion_top = "<button class = \"accordion\"> </button>";
	accodion_top += "<div class = \"panel\">{";
	std::string accodion_btm = "}</div>";
	std::ifstream in(filename);
	std::string line;
	std::string returnstr;
	while (getline(in, line))
	{
		bool firstcheck = line.find("{") != std::string::npos;		//If "{" and "}" lies
		bool secondcheck = line.find("}") != std::string::npos;		// on same line
		bool finalcheck = firstcheck && secondcheck;				//dont add accordition
		if (!finalcheck)
		{
			replaceall(line, "{", accodion_top);
			replaceall(line, "}", accodion_btm);
		}
		returnstr += line + "\n";
	}
	return returnstr;
}

/////////////////////////////////////////////////////////////////////
//Update file with string
bool Publish::updatefile(std::string & filename, const std::string & strtxt)
{
	std::ofstream out(filename);
	out << strtxt;
	out.close();
	return true;
}

/////////////////////////////////////////////////////////////////////
//Html formating
bool Publish::htmlformat(std::string & strtxt, Key fileSpec, Keys Dep)
{
	addpretag(strtxt);			//pre tag
	addbodytag(strtxt, fileSpec, Dep);		//body tag
	addheadtag(strtxt);				//header tag
	addhtmltag(strtxt);				//html tag
	return true;
}

/////////////////////////////////////////////////////////////////////
//html tag
bool Publish::addhtmltag(std::string & strtxt)
{
	strtxt = "<html>\n" + strtxt + "\n"  +"</html>";
	return true;
}
/////////////////////////////////////////////////////////////////////
//header tag
bool Publish::addheadtag(std::string & strtxt)
{
	std::string header;
	header += "<head>";
	header += "\n<link rel=\"stylesheet\" type=\"text/css\" href=\"../header.css\">"; //add css file link
	header += "\n</head>";
	strtxt = header + strtxt;
	return true;
}

/////////////////////////////////////////////////////////////////////
//body tag
bool Publish::addbodytag(std::string & strtxt, Key fileSpec, Keys Dep)
{
	std::string body = "\n<body>";
	FileSystem::Path filename;
	bool withoutext = false;
	std::string file_name = filename.getName(fileSpec);
	body += "\n<h3>"+ file_name+"</h3>";
	body += "\n<hr/>";
	body += "\n<div class = \"indent\">";
	body += "\n<h4>Dependencies:</h4>";
	for (size_t t = 0; t < Dep.size(); t++)  //add dependencies to file
	{
		std::string file_name = filename.getName(Dep[t]);
		body += "\n<a href = " + file_name + ".html>" + Dep[t] + "</a>" +"\n";
	}
	body += "\n</div>";
	body += "\n<hr/>";
	std::string myscript = "\n<script type = \"text/javascript\" src = \"../exp_coll.js\"></script>"; //add javascript
	strtxt = body+"\n" + strtxt + "\n" + myscript + "\n"+"</body>";
	return true;
}

/////////////////////////////////////////////////////////////////////
//add pre tag for formating
bool Publish::addpretag(std::string & strtxt)
{
	strtxt = "<pre>\n" + strtxt + "\n" + "</pre>";
	return true;
}

/////////////////////////////////////////////////////////////////////
//test stub for publisher
#ifdef TEST_Publish
int main(int argc, char* argv[])
{
	CodeAnalysisExecutive exec;
	try {
		bool succeeded = exec.ProcessCommandLine(argc, argv);
		if (!succeeded)
			return 1;
		exec.getSourceFiles();  //get all files
		exec.processSourceCode(true); //process files
		exec.flushLogger();
		Filepaths files_ = exec.allFiles();
		std::string html_filename = exec.gethtml_filename(); //get command lines for xml path
		TypeAnal ta;
		ta.doTypeAnal();
		TypeTable TT = ta.getTT();
		DepAnal da;
		for (size_t t = 0; t < files_.size(); t++)
			da.doDepAnal(TT, files_[t]);
		NoSqlDb<std::string> depanal = da.getdepanal();
		const std::string htmlocationDir = "Htm_file";
		Publish publish(depanal);
		Directory htmDir;
		htmDir.create(htmlocationDir);
		for (size_t t = 0; t < files_.size(); t++)
				publish.converthtm(files_[t], htmlocationDir);
		std::string currentdir = htmDir.getCurrentDirectory();
		html_filename = currentdir + html_filename;
		std::wstring temp = std::wstring(html_filename.begin(), html_filename.end());
		ShellExecute(NULL,L"open", temp.c_str(), NULL, NULL, SW_SHOWNORMAL);
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

#endif // !TEST_Publish