#pragma once
#pragma once
#ifndef TRANDAU_H 
#define TRANDAU_H 

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class TranDau {
private:
	int ngay;
	int thang;
	int nam;
	string santhidau;
	string team1;
	string team2;
	string tyso;
public:
	TranDau(int, int, int, string, string, string, string);
	~TranDau();
	int getNgaythidau() const { return ngay; }
	int getThangthidau() const { return thang; }
	int getNamthidau() const { return nam; }
	string getTyso() const { return tyso; }
	string getTeam1() const { return team1; }
	string getTeam2() const { return team2; }
	string getSandau() const { return santhidau; }
	void inThongtin();
};

#endif
