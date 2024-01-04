#include <iostream>
#include <string>
#include <vector>
#include"CAUTHU.H"
using namespace std;

CauThu::CauThu(string id, string fullName, string intenational, string birth, string height, string weight, string position)
	: id(id), fullName(fullName), intenational(intenational), birth(birth), height(height), weight(weight), position(position) {}

CauThu::CauThu(string id, string fullName, string intenational, string birth, string height, string weight, string position, string doibong)
	: id(id), fullName(fullName), birth(birth), intenational(intenational), height(height), weight(weight), position(position), doibong(doibong) {}

CauThu::~CauThu() {

}

string CauThu::getID() const {
	return this->id;
}

int CauThu::AddPlayer(vector<CauThu> listPlayerCT) {
	string cccd;
	cout << "nhap CCCD : "; getline(cin, this->id);
	for (int i = 0; i < listPlayerCT.size(); i++) {
		if (listPlayerCT[i].getID() == this->id) {
			cout << "so can cuoc cong dan da ton tai!!" << endl;
			return 0;
		}
		if (i == listPlayerCT.size() - 1) {
			cout << "nhap ho va ten : ";  getline(cin, this->fullName);
			cout << "nhap quoc tich : "; getline(cin, this->intenational);
			cout << "nhap ngay thang nam sinh : "; getline(cin, this->birth);
			cout << "nhap chieu cao : "; getline(cin, this->height);
			cout << "nhap can nang : "; getline(cin, this->weight);
			cout << "nhap vi tri thi dau : "; getline(cin, this->position);
			cout << "Thuoc doi bong : "; getline(cin, this->doibong);
			return 2;
		}
	}
}

string CauThu::modifyPlayer(vector<CauThu>& listPlayerCT) {
	string CMND, select;
	cout << "vui long nhap CMND cau thu can sua : ";
	cin >> CMND;
	for (auto i = listPlayerCT.begin(); i != listPlayerCT.end(); i++) {
		if (CMND == i->getID()) {
			cout << "Sua toan bo thong tin cua cau thu (yes/no) : ";
			cin >> select;
			cin.ignore();
			if (select == "yes") {
				int selection;
				do {
					selection = i->handleModifyPlayer(listPlayerCT, i->getID());
					if (selection == 2) {
						cout << "Sua doi thanh cong!!!" << endl;
					}
				} while (selection != 2);
				
			}
			if (select == "no") {
				int choose;
				i->getPlayer();
				cout << "8. Thuoc doi bong: " << i->getTendoibong() << endl;
				cout << "Chon noi dung can sua : ";
				cin >> choose;
				cin.ignore();
				switch (choose) {
				case 1:
				{
					string _id;
					cout << i->id << " --> ";
					cin >> _id;
					for (auto j = listPlayerCT.begin(); j != listPlayerCT.end(); j++) {
						if (j->id == i->id) continue;
						if (_id == j->id) {
							cout << "Sua doi that bai! So CCCD nay da ton tai! " << endl;
							break;
						}
						if (j == listPlayerCT.end() - 1) {
							i->id = _id;
							cout << "Sua doi thanh cong !" << endl;
						}
					}
				}
				break;
				case 2:
					cout << i->fullName << " --> ";
					getline(cin, i->fullName);
					cout << "Sua doi thanh cong !" << endl;
					break;
				case 3:
					cout << i->intenational << " --> ";
					getline(cin, i->intenational);
					cout << "Sua doi thanh cong !" << endl;
					break;
				case 4:
					cout << i->birth << " --> ";
					cin >> i->birth;
					cout << "Sua doi thanh cong !" << endl;
					break;
				case 5:
					cout << i->height << " --> ";
					cin >> i->height;
					cout << "Sua doi thanh cong !" << endl;
					break;
				case 6:
					cout << i->weight << " --> ";
					cin >> i->weight;
					cout << "Sua doi thanh cong !" << endl;
					break;
				case 7:
					cout << i->position << " --> ";
					getline(cin, i->position);
					cout << "Sua doi thanh cong !" << endl;
					break;
				case 8:
					cout << i->getTendoibong() << "-->";
					getline(cin, i->doibong);
					cout << "Sua doi thanh cong !" << endl;
					break;
				default:
					cout << "Khong hop le !!" << endl;
					break;
				}
			}
			return CMND;
		}
		if (i == listPlayerCT.end() - 1) {
			cout << "khong tim thay!!!!!!!!" << endl;
		}
	}
}

void CauThu::listingPlayer(vector<CauThu> listPlayerCT) {
	cout << "Liet ke danh sach cau thu theo nam sinh chon 1. " << endl;
	cout << "Liet ke danh sach cau thu theo vi tri thi dau chon 2. " << endl;
	int select;
	cout << "vui long chon : ";
	cin >> select;
	cin.ignore();
	switch (select) {
	case 1:
	{
		string yearSelect;
		int count = 0;
		cout << "Nhap nam sinh : "; cin >> yearSelect;
		for (auto i = listPlayerCT.begin(); i != listPlayerCT.end(); i++) {
			if (i->birth.find(yearSelect) != -1) {
				i->getPlayer();
				cout << "--------------------------------------" << endl;
				count++;
			}
			if (count == 0 && i == listPlayerCT.end() - 1) {
				cout << "Khong tim thay!!" << endl;
			}
		}
	}
	break;
	case 2:
	{
		string positionSelect;
		cout << "Nhap vi tri thi dau : ";
		getline(cin, positionSelect);
		for (auto i = listPlayerCT.begin(); i != listPlayerCT.end(); i++) {
			if (i->position == positionSelect) {
				i->getPlayer();
				cout << "--------------------------------------" << endl;
			}
			if (i->position != positionSelect && i == listPlayerCT.end() - 1) {
				cout << "Khong tim thay!!" << endl;
			}
		}
	}
	break;
	}
}

void CauThu::getYoungestPlayer(vector<CauThu>& listPlayerCT) {

	CauThu min = listPlayerCT[0];
	for (int i = 1; i < listPlayerCT.size(); i++) {
		int count1 = 0;
		int count2 = 0;
		for (int j = 0; j < listPlayerCT[i].birth.length(); j++) {
			if (min.birth[j] == '/') count2++;
			if (count2 == 2) {
				count2 = j + 1;
			}
			if (listPlayerCT[i].birth[j] == '/') count1++;
			if (count1 == 2) {
				count1 = j + 1;
			}
		}
		if (stoi(min.birth.substr(count1)) < stoi(listPlayerCT[i].birth.substr(count2))) {
			min = listPlayerCT[i];
		}
	}
	min.getPlayer();
}

void CauThu::getTallestPlayer(vector<CauThu>& listPlayerCT) {
	CauThu max = listPlayerCT[0];
	for (int i = 1; i < listPlayerCT.size(); i++) {

		if (stoi(max.height) < stoi(listPlayerCT[i].height)) {
			max = listPlayerCT[i];
		}
	}
	max.getPlayer();
}

void CauThu::getShortestPlayer(vector<CauThu>& listPlayerCT) {
	CauThu min = listPlayerCT[0];
	for (int i = 1; i < listPlayerCT.size(); i++) {

		if (stoi(min.height) > stoi(listPlayerCT[i].height)) {
			min = listPlayerCT[i];
		}
	}
	min.getPlayer();
}

int CauThu::handleModifyPlayer(vector<CauThu>& listPlayerCT, string ID){
	string cccd;
	cout << "nhap CCCD : "; getline(cin, cccd);
	for (int i = 0; i < listPlayerCT.size(); i++) {
		if (listPlayerCT[i].getID() == ID) {
			continue;
		}
		if (listPlayerCT[i].getID() == cccd) {
			cout << "so can cuoc cong dan da ton tai!!" << endl;
			return 0;
		}
		if (i == listPlayerCT.size() - 1) {
			this->id = cccd;
			cout << "nhap ho va ten : ";  getline(cin, this->fullName);
			cout << "nhap quoc tich : "; getline(cin, this->intenational);
			cout << "nhap ngay thang nam sinh : "; getline(cin, this->birth);
			cout << "nhap chieu cao : "; getline(cin, this->height);
			cout << "nhap can nang : "; getline(cin, this->weight);
			cout << "nhap vi tri thi dau : "; getline(cin, this->position);
			cout << "Thuoc doi bong : "; getline(cin, this->doibong);
			return 2;
		}
	}
}

void CauThu::getPlayer() const{
	cout << "1. " << "So CCCD : " << this->id << endl;
	cout << "2. " << "Ho va ten : " << this->fullName << endl;
	cout << "3. " << "Quoc tich : " << this->intenational << endl;
	cout << "4. " << "Ngay/Thang/Nam sinh : " << this->birth << endl;
	cout << "5. " << "Chieu cao : " << this->height << endl;
	cout << "6. " << "Can nang : " << this->weight << endl;
	cout << "7. " << "Vi ti thi dau : " << this->position << endl;
}
