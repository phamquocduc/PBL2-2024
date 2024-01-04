#include<iostream>
#include"TRANDAU.H"

TranDau::TranDau(int d, int m, int y, string sandau, string t1 ,string t2, string tyso)
	: ngay(d), thang(m), nam(y), santhidau(sandau), team1(t1), team2(t2), tyso(tyso){}

TranDau::~TranDau(){}

void TranDau::inThongtin(){
	cout << "Ngay thi dau : " << ngay << "/" << thang << "/" << nam << endl;
	cout << "San thi dau : " << santhidau << endl;
	cout << "Ty so : " << team1 << " " << tyso << " " << team2 << endl;
	cout << "------------------------" << endl;
}