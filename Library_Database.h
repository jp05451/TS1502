#pragma once
#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<set>
#include<map>
#include<algorithm>

using namespace std;

typedef class Book
{
public:
	Book() {}
	Book(string title, string author) :title(title), author(author) {}
	Book(string title, string author, long long edition) :title(title), author(author) { Edition.push_back(edition); }
	string title="";
	string author="";
	vector<long long> Edition;
	bool operator == (const Book& b) { return title == b.title && author == b.author; }
	bool AuthorCompare(const string& str) { return str== author; }
	
}Book;

ostream& operator<<(ostream& ostr, vector<long long>& edition);


bool AuthorCompare(const Book& a, const Book& b);


bool TitleCompare(const Book& a, const Book& b);


class Library
{
public:
	int Insert(const Book& b);
	int DeleteEdition(const Book& b);
	int DeleteBook(const Book&);
	bool FindBook(const Book&);
	bool FindAuthor(const string&);
	void SortTitle();
	void SortAuthor();
	void getCommand();
private:
	vector<Book> books;
	//map<string, map<string, set<int>>> books;
	//set<Book> books;
};

void DeQuote(string& str);
