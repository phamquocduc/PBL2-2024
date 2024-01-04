#pragma once
#pragma once
#ifndef dOIBONG_H 
#define dOIBONG_H 

#include<iostream>
#include"CAUTHU.H"
#include<string>
#include<vector>
using namespace std;

class doibong {
public:
    doibong(string, string, string, vector<CauThu>& danhsachcauthu);
    void suadoibong(string, string, string, vector<CauThu>);
    void themcauthuvaodanhsach(CauThu& t);
    void xoacauthukhoids(string);
    void setDiem(int diem);
    string getTenDoiBong() const;
    string getDiaPhuong() const;
    string getHuanLuyenVien() const;
    vector<CauThu> getdscauthu() const;
    int getdodaidscauthu() const;
    void suadanhsachcauthu(const CauThu& t, string id);
    void inThongTin();
    void inDiem();

private:
    string tenDoiBong;
    string diaPhuong;
    string huanLuyenVien;
    int diem;
    vector<CauThu> danhsachcauthu;
};

#endif
