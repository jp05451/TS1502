#include"Library_Database.h"
#pragma once


void Library::getCommand()
{
	string command;
	string line;
	while (cin>>command)
	{
		//cin.ignore();
		stringstream ss;
		getline(cin, line);
		ss.str("");
		ss.clear();
		ss << line;
		if (command == "Insert")
		{
			string title = "";
			string author = "";
			long long edition = -1;

			//ss >> title >> author >> edition;
			size_t pos = line.find('"');
			ss.seekg(pos+1);
			getline(ss, title, '"');
			ss.seekg(pos + 1 + title.length() + 3);
			getline(ss, author, '"');
			ss >> edition;
			if (title != "" && author != "" && edition >=0)
			{
				title.erase(remove(title.begin(), title.end(), '\"'), title.end());
				author.erase(remove(author.begin(), author.end(), '\"'), author.end());
				Book temp(title, author, edition);
				Insert(temp);
			}
			else
			{
				cout << "Incomplete Command." << endl;
			}
		}
		else if (command == "Delete")
		{
			string label="";
			string author="";
			string title="";
			long long edition=-1;
			ss >> label;
			if (label == "Edition")
			{
				//ss >> title >> author >> edition;
				size_t pos = line.find('"');
				ss.seekg(pos + 1);
				getline(ss, title, '"');
				ss.seekg(pos + 1 + title.length() + 3);
				getline(ss, author, '"');
				ss >> edition;
				//DeQuote(title);
				//DeQuote(author);
				if (title == "" || author == "" || edition < 0)
				{
					cout << "Incomplete Command." << endl;
					continue;
				}
				Book temp(title, author, edition);
				if (!DeleteEdition(temp))
				{
					cout << "Datum doesn't exist." << endl;
				}
			}
			else if (label == "Book")
			{
				//ss >> title >> author;
				size_t pos = line.find('"');
				ss.seekg(pos + 1);
				getline(ss, title, '"');
				ss.seekg(pos + 1 + title.length() + 3);
				getline(ss, author, '"');
				if (title == "" || author == "" )
				{
					cout << "Incomplete Command." << endl;
					continue;
				}
				//DeQuote(title);
				//DeQuote(author);
				Book temp(title, author);
				if(!DeleteBook(temp))
				{
					cout << "Book doesn't exist." << endl;
				}
			}
			else
			{
				cout << "Incomplete Command." << endl;
			}
		}
		else if (command == "Find")
		{
			string label = "";
			string author = "";
			string title="";
			ss >> label;
			if (label == "Book")
			{
				//ss >> title >> author;
				size_t pos = line.find('"');
				ss.seekg(pos + 1);
				getline(ss, title, '"');
				ss.seekg(pos + 1 + title.length() + 3);
				getline(ss, author, '"');
				if (title == "" || author == "")
				{
					cout << "Incomplete Command." << endl;
					continue;
				}
				//DeQuote(title);
				//DeQuote(author);
				Book temp(title, author);
				if (!FindBook(temp))
				{
					cout << "No book found.";
				}
			}
			else if (label == "Author" )
			{
				//ss >> author;
				size_t pos = line.find('"');
				ss.seekg(pos + 1);
				getline(ss, author, '"');
				
				if (author == "")
				{
					cout << "Incomplete Command." << endl;
					continue;
				}
				//DeQuote(author);
				if (!FindAuthor(author))
				{
					cout << "No book found." << endl;
				}
			}
			else
			{
				cout << "Incomplete Command." << endl;
			}
		}
		else if (command == "Sort")
		{
			string way;
			string by;
			ss >> by >> way;
			if (way == "Title"&&by=="by")
			{
				SortTitle();
			}
			else if (way == "Author" && by == "by")
			{
				SortAuthor();
			}
			else
			{
				cout << "Incomplete Command." << endl;
			}
		}
		else
		{
			cout << "Unknown Command." << endl;
		}
	}
}

int Library::Insert(const Book& b)
{
	//cout << "Insert" << endl;
	long long edition = b.Edition[0];
	vector<Book>::iterator it = find(books.begin(), books.end(), b);
	if (it != books.end())
	//if the book exist
	{
		vector<long long>::iterator edit = find((*it).Edition.begin(), (*it).Edition.end(), edition);
		if (edit == (*it).Edition.end())
		//if the edition dosn't exist
		{
			(*it).Edition.push_back(edition);
			sort((*it).Edition.begin(), (*it).Edition.end());
		}
		else
		{
			cout << "Datum already exist." << endl;
			return 0;
		}
	}
	else//the book doen't exist
	{
		books.push_back(b);
	}
	cout << "Insert " << b.author << "'s " << b.title << ", Edition: " << *(b.Edition.begin()) << "." << endl;
	return 1;
}
int Library::DeleteEdition(const Book& b)
{
	//cout << "DeleteEdition" << endl;
	vector<Book>::iterator  it = find(books.begin(), books.end(), b);
	if (it == books.end())
	{
		cout << "Datum doesn't exist." << endl;
		return 0;
	}
	vector<long long>::iterator edit = find((*it).Edition.begin(), (*it).Edition.end(), b.Edition[0]);
	if (edit == (*it).Edition.end())
	{
		
		return 0;
	}
	(*it).Edition.erase(edit);
	cout << "Delete " << b.author << "'s " << b.title << ", Edition: " << *(b.Edition.begin()) <<"." << endl;
	return 1;
}
int Library::DeleteBook(const Book& b)
{
	//cout << "DeleteBook" << endl;
	vector<Book>::iterator it = find(books.begin(), books.end(), b);
	if (it == books.end())
	{
		return 0;
	}
	books.erase(it);
	cout << "Delete " << b.author << "'s " << b.title << "." << endl;
}
bool Library::FindBook(const Book& b)
{
	vector<Book>::iterator it = find(books.begin(), books.end(), b);
	if (it == books.end())
	{
		return 0;
	}
	cout << "Title: " << (*it).title << "\tAuthor: " << (*it).author <<"\tEdition: " << (*it).Edition << endl;
	return 1;
}
bool Library::FindAuthor(const string& author)
{
	int i;
	for (i = 0; i < books.size(); i++)
	{
		if (books[i].AuthorCompare(author))
		{
			break;
		}
	}
	if (i == books.size())
	{
		return 0;
	}
	sort(books.begin(), books.end(), TitleCompare);
	cout << author << "'s Books: ";
	bool flag = 0;
	for (i = 0; i < books.size(); i++)
	{
		if (books[i].AuthorCompare(author))
		{
			if (flag)
			{
				cout << ", ";
			}
			flag = 1;
			cout << books[i].title;
		}
	}
	cout << endl;
	return 1;
}
void Library::SortTitle()
{
	sort(books.begin(), books.end(), TitleCompare);
	for (int i = 0; i < books.size(); i++)
	{
		cout << "Title: " << books[i].title << "\tAuthor: " << books[i].author << "\tEdition: ";
		for (int edit = 0; edit < books[i].Edition.size(); edit++)
		{
			cout << books[i].Edition[edit];
			if (edit < books[i].Edition.size() - 1)
			{
				cout << ", ";
			}
		}
		cout << endl;
	}
}
void Library::SortAuthor()
{
	//cout << "SortAuthor" << endl;
	//return ;
	sort(books.begin(), books.end(), AuthorCompare);
	for (int i = 0; i < books.size(); i++)
	{
		cout << "Title: " << books[i].title << "\tAuthor: " << books[i].author << "\tEdition: ";
		for (int edit = 0; edit < books[i].Edition.size(); edit++)
		{
			cout << books[i].Edition[edit];
			if (edit < books[i].Edition.size() - 1)
			{
				cout << ", ";
			}
		}
		cout << endl;
	}
}

void DeQuote(string& str)
{
	str.erase(remove(str.begin(), str.end(), '\"'), str.end());
}

bool AuthorCompare(const Book& a, const Book& b)
{
	
	if (a.author == b.author)
	{
		return a.title < b.title;
	}
	if (a.author < b.author)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
bool TitleCompare(const Book& a, const Book& b)
{
	if (a.title == b.title)
	{
		return a.author < b.author;
	}
	if (a.title < b.title)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

ostream& operator<<(ostream& ostr, vector<long long>& edition)
{
	for (int i = 0; i < edition.size(); i++)
	{
		cout << edition[i];
		if (i < edition.size() - 1)
		{
			cout << ", ";
		}
	}
	return ostr;
}