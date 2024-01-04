#include<iostream>
#include<iomanip>
#include"DOIBONG.H"
#include"CAUTHU.H"
#include<string>
using namespace std;

doibong::doibong(string tenDoiBong, string diaPhuong, string huanLuyenVien,  vector<CauThu>& danhsachcauthu)
    : tenDoiBong(tenDoiBong), diaPhuong(diaPhuong), huanLuyenVien(huanLuyenVien), diem(0) {
    for (int i = 0; i < danhsachcauthu.size(); i++) {
        this->danhsachcauthu.push_back(danhsachcauthu[i]);
    }
}

void doibong::setDiem(int diem) {
    this->diem += diem;
}

void doibong::suadoibong(string ten, string diaphuong, string huanluyenvien, vector<CauThu> dsct) {
    this->tenDoiBong = ten;
    this->diaPhuong = diaphuong;
    this->huanLuyenVien = huanluyenvien;
    this->danhsachcauthu = dsct;
}

void doibong::themcauthuvaodanhsach(CauThu& t) {
    this->danhsachcauthu.push_back(t);
}

void doibong::xoacauthukhoids(string id) {
    for (auto i = this->danhsachcauthu.begin(); i != this->danhsachcauthu.end(); i++) {
        if (i->getID() == id) {
            this->danhsachcauthu.erase(i);
            break;
        }
        if (i == this->danhsachcauthu.end() - 1) {
            cout << "Khong tim thay!" << endl;
        }
    }
}


void doibong::suadanhsachcauthu(const CauThu& t, string id) {
    for (auto& CT : danhsachcauthu) {
        if (CT.getID() == id) {
            CT = t;
        }
    }
}

int doibong::getdodaidscauthu() const {
    return danhsachcauthu.size();
}

vector<CauThu> doibong::getdscauthu() const {
    return danhsachcauthu;
}

string doibong::getTenDoiBong() const { return tenDoiBong; }
string doibong::getDiaPhuong() const { return diaPhuong; }
string doibong::getHuanLuyenVien() const { return huanLuyenVien; }

void doibong::inThongTin() {
    cout << "Ten doi bong: " << this->tenDoiBong << endl;
    cout << "Dia phuong: " << this->diaPhuong << endl;
    cout << "Huan luyen vien: " << this->huanLuyenVien << endl;
    cout << "Danh sach cau thu : " << endl;
    for (int i = 0; i < this->danhsachcauthu.size(); i++) {
        this->danhsachcauthu[i].getPlayer();
        cout << "--------------------------------------" << endl;
    }

}

void doibong::inDiem() {
    cout << setw(30) << left << tenDoiBong  << diem << endl;
}