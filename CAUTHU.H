#pragma once

#ifndef CAUTHU_H 
#define CAUTHU_H 

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class CauThu {
private:
	string id;
	string fullName;
	string intenational;
	string birth;
	string height;
	string weight;
	string position;
	string doibong;
public:
	CauThu(string, string, string, string, string, string, string);

	CauThu(string, string, string, string, string, string, string, string);

	CauThu() {};

	~CauThu();

	string getID() const;
	string getFullname() const { return this->fullName; }
	string getInternational() const { return this->intenational; }
	string getBirth() const { return this->birth; }
	string getHeight() const { return this->height; }
	string getWeight() const { return this->weight; }
	string getPosition() const { return this->position; }
	string getTendoibong() const { return this->doibong; }

	int AddPlayer(vector<CauThu> listPlayerCT);

	string modifyPlayer(vector<CauThu>& listPlayerCT);

	void listingPlayer(vector<CauThu> listPlayerCT);

	void getYoungestPlayer(vector<CauThu>& listPlayerCT);

	void getTallestPlayer(vector<CauThu>& listPlayerCT);

	void getShortestPlayer(vector<CauThu>& listPlayerCT);

	int handleModifyPlayer(vector<CauThu>& listPlayerCT, string ID);

	void getPlayer() const;

};

#endif