/////////////////////////////////////////////////////////////////////
//  DepAnal.cpp -    Dependency analysis for code analser          //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP EliteBook, Windows 10                        //
//  Application:   Dependency check, CSE 687- Sp17	    		   //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////
#include "DepAnal.h"

/////////////////////////////////////////////////////////////////////
//define namespace definations.
namespace CodeAnalysis
{
	/////////////////////////////////////////////////////////////////
	//Constructor and initialization
	DepAnal::DepAnal() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack()),
		toker_(*(Repository::getInstance()->Toker()))
	{
		std::function<void()> test = [] { int x; };  
	}
	using Key = std::string;
	using Keys = std::vector<std::string>;
	/////////////////////////////////////////////////////////////////
	//Create list of namespace
	std::vector<std::string>DepAnal::namespacelist(TypeTable TT)
	{
		std::vector<std::string> NS_list;

		std::vector<std::string> keys = TT.Keys();
		for (std::string k : keys)
		{
			std::vector<TTElement> NS_map = TT.value(k);
			for (size_t t = 0; t < NS_map.size(); t++)
			{
				NS_list.push_back(NS_map[t].getnamespace());
			}
		}
		return NS_list;

	}
	/////////////////////////////////////////////////////////////////
	//check token in typetable
	void CodeAnalysis::DepAnal::dep_iftok(std::string fileSpec, std::vector<TTElement> Values, std::vector<std::string> NS)
	{
		Element<Key> newElemDb = name_DbElem(fileSpec);
		for (size_t i = 0; i < Values.size(); i++)
		{
			bool NS_flag = false;
			std::string depFile = Values[i].getfilename();
			std::vector<std::string> deps = newElemDb.children;
			for (std::string k : NS)
			{
				if (k == Values[i].getnamespace())
					NS_flag = true;
			}
			if (depFile == fileSpec || hasdependency(deps, depFile))
				continue;
			else if (!NS_flag)
				continue;
			else
			{
				depAnal.addchildren(fileSpec, depFile);
				//NS_flag = false;
			}
		}
	}

	/////////////////////////////////////////////////////////////////
	//Check header file dependency
	void CodeAnalysis::DepAnal::dep_forh(Key fileSpec, std::vector<TTElement> Values, std::vector<std::string> NS)
	{
		for (size_t i = 0; i < Values.size(); i++)
		{
			bool NS_flag = false;
			std::string depFile = Values[i].getfilename();
			Element<Key> newElemDbh = name_DbElem(depFile);
			std::vector<std::string> deps = newElemDbh.children;
			for (std::string k : NS)
			{
				if (k == Values[i].getnamespace())
					NS_flag = true;
			}
			if (depFile == fileSpec || hasdependency(deps, fileSpec))
				continue;
			else if (!NS_flag)
				continue;
			else
			{
				depAnal.addchildren(depFile, fileSpec);
				//NS_flag = false;
			}
		}
	}

	/////////////////////////////////////////////////////////////////
	//Elemenet in Nosql
	Element<std::string> DepAnal::name_DbElem(std::string fileSpec)
	{
		Element<std::string> newElemDb;
		if (depAnal.hasKey(fileSpec))
			newElemDb = depAnal.value(fileSpec);
		else
		{
			newElemDb.name = fileSpec;
			depAnal.saveRecord(fileSpec, newElemDb);
		}
		return newElemDb;
	}
	/////////////////////////////////////////////////////////////////////
	//Do type analysis
	bool DepAnal::doDepAnal(TypeTable TT, std::string fileSpec){
		try{
			std::ifstream in(fileSpec);
			if (!in.good()){
					std::cout << "\n  can't open " << fileSpec << "\n\n";
					return false;
			}
			Toker toker;
			toker.returnComments();
			toker.attach(&in);
			std::string prevTok;
			std::vector<std::string> NS, NS_list;
			NS.push_back("Global Namespace");
			bool NS_flag = false;
			bool NS_check= false;
			bool NS_direct = false;
			std::vector<std::string> keys = TT.Keys();
			NS_list = namespacelist(TT);
			do{
				std::string tok = toker.getTok();
				if (NS_check){
					NS.push_back(tok);
					NS_check = false;
				}
				if (tok == "namespace")
					NS_check = true;
				if (std::find(keys.begin(), keys.end(), tok) != keys.end()||NS_direct){
					std::vector<TTElement> Values = TT.value(tok);
					dep_iftok(fileSpec, Values, NS );
					NS_direct = false;
				}
				if (tok == "::" && std::find(NS_list.begin(), NS_list.end(), prevTok) != NS_list.end())
					NS_direct = true;
				if (tok == "::" && std::find(keys.begin(), keys.end(), prevTok) != keys.end() && !NS_direct){
					//if(std::find(NS_list.begin(), NS_list.end(), prevTok)!= NS_list.end()){
					std::vector<TTElement> Values = TT.value(prevTok);
					dep_forh(fileSpec, Values, NS);
				}
				prevTok = tok;
			} while (in.good());
		}
		catch (std::exception& ex){
			std::cout << "\n  Exception: " << ex.what() << "\n";
		}
		return true;
	}
	/////////////////////////////////////////////////////////////////
	//Check substring
	bool DepAnal::checksubstring(std::string sub_filename)
	{
		std::string path;
		std::size_t found = path.find(sub_filename);
		if (found != std::string::npos)
			return true;
		else
			return false;
	}
	/////////////////////////////////////////////////////////////////
	//check dependency
	bool DepAnal::hasdependency(std::vector<std::string> childrens, std::string filename)
	{
		std::vector<std::string>::iterator it;

		it = find(childrens.begin(), childrens.end(), filename);
		if (it != childrens.end())
			return true;
		else
			return false;
	}
	/////////////////////////////////////////////////////////////////
	//return dependency
	NoSqlDb<std::string> DepAnal::getdepanal()
	{
		return depAnal;
	}
}

/////////////////////////////////////////////////////////////////
//test stub

#ifdef TEST_DEPANAL

int main()
{
	using Key = std::string;
	using Keys = std::vector<std::string>;

	TypeAnal ta;
	ta.doTypeAnal();
	
	TypeTable TT = ta.getTT();
	files.push_back("..//test path")

	DepAnal da;

	//for loop for all files use filemanager for file name

	for (size_t t = 0; t<files_.size(); t++)
	{
		da.doDepAnal(TT, files_[t]);
	}

}
#endif
