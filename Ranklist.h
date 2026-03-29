#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <graphics.h>
using namespace std;
struct Ranknode {
	string username;
	int score;
	Ranknode* next;
	Ranknode(string name,int s):username(name),score(s),next(nullptr){}
};
class Ranklist {
private:
	Ranknode* head;
	const string filename = "rank.txt";
	void loadfromfile();
	void savetofile();
public:
	Ranklist();
	~Ranklist();
	void interorupdata(string name, int score);
	void deleteuser(string name);
	void showrank();
	friend class Tetris;
};