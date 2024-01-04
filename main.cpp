#include <SDL.h>
#include<iostream>
#include<stdio.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include<fstream>
#include <sstream>
#include"CAUTHU.H"
#include"TRANDAU.H"
#include"DOIBONG.H"
#include<vector>
#include<iomanip>

using namespace std;

#define NUM_BUTTONS 5
#define NUM_BUTTONS0 5
#define NUM_BUTTONS1 8
#define NUM_BUTTONS2 5
#define NUM_BUTTONSBACK 15
#define BUTTON_WIDTH 430
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 15
#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 700

typedef struct {
	SDL_Rect rect;
	SDL_Texture* texture;
} Button;

Button *buttons = new Button[NUM_BUTTONS];
Button *buttons0 = new Button[NUM_BUTTONS0];
Button *buttons1 = new Button[NUM_BUTTONS1];
Button *buttons2 = new Button[NUM_BUTTONS2];
Button *buttonsBack = new Button[NUM_BUTTONSBACK];

void renderButton(SDL_Renderer* renderer, Button* button) {
	SDL_RenderCopy(renderer, button->texture, NULL, &button->rect);
}

bool isPointInRect(int x, int y, SDL_Rect* rect) {
	return (x >= rect->x && x <= rect->x + rect->w && y >= rect->y && y <= rect->y + rect->h);
}

void setDataCTFromdataDb(vector<CauThu>& listPlayerCT, const vector<doibong>& danhsachdoibong) {
	listPlayerCT.clear();
	for (const auto& doibong : danhsachdoibong) {
		for (const auto& cauthu : doibong.getdscauthu()) {
			listPlayerCT.push_back(cauthu);
		}
	}
}

void setCTvaoDB(const CauThu& t, vector<CauThu>& danhsachcauthu) {
	danhsachcauthu.push_back(t);
}

void setDatDBFromFile(vector<doibong>& danhSachDoiBong) {
	ifstream file("doibong.txt");
	if (file.is_open()) {
		int sl = 0;
		string line;
		string tenDoiBong, diaPhuong, huanLuyenVien;
		string id, fn, it, bi, he, we, po;
		while (getline(file, line)) {
			if (line.find("Ten doi bong: ") != string::npos) {
				tenDoiBong = line.substr(14);
			}
			else if (line.find("Dia phuong: ") != string::npos) {
				diaPhuong = line.substr(12);
			}
			else if (line.find("Huan luyen vien: ") != string::npos) {
				huanLuyenVien = line.substr(17);
			}
			vector<CauThu> danhsachcauthu;
			if (line.find("Danh sach cau thu: ") != string::npos) {
				sl = stoi(line.substr(19));
				getline(file, line);
				for (int i = 0; i < sl; i++) {
					for (int j = 0; j < 7; j++) {
						if (line.find("So CMND: ") != string::npos) {
							id = line.substr(9);
							getline(file, line);
						}
						else if (line.find("Ho ten: ") != string::npos) {
							fn = line.substr(8);
							getline(file, line);
						}
						else if (line.find("Quoc tich: ") != string::npos) {
							it = line.substr(11);
							getline(file, line);
						}
						else if (line.find("Ngay sinh: ") != string::npos) {
							bi = line.substr(11);
							getline(file, line);
						}
						else if (line.find("Chieu cao: ") != string::npos) {
							he = line.substr(11);
							getline(file, line);
						}
						else if (line.find("Can nang: ") != string::npos) {
							we = line.substr(10);
							getline(file, line);
						}
						else if (line.find("Vi tri thi dau: ") != string::npos) {
							po = line.substr(16);
							getline(file, line);
							getline(file, line);
							CauThu T(id, fn, it, bi, he, we, po, tenDoiBong);
							danhsachcauthu.push_back(T);
						}
					}
				}
				doibong doibong1(tenDoiBong, diaPhuong, huanLuyenVien, danhsachcauthu);
				danhSachDoiBong.push_back(doibong1);
			}
		}
		file.close();
	}
	else {
		cout << "Khong the mo tep tin doibong.txt." << endl;
	}
}

void setDataTrandauFromFile(vector<TranDau>& danhsachtrandau) {
	ifstream file("trandau.txt");
	if (file.is_open()) {
		int d, m, y;
		string sandau, t1, t2, tyso, line;
		while (getline(file, line)) {
			if (line.find("ngay : ") != string::npos) {
				d = stoi(line.substr(7));
			}
			else if (line.find("thang : ") != string::npos) {
				m = stoi(line.substr(8));
			}
			else if (line.find("nam : ") != string::npos) {
				y = stoi(line.substr(6));
			}
			else if (line.find("san dau : ") != string::npos) {
				sandau = line.substr(10);
			}
			else if (line.find("team 1 : ") != string::npos) {
				t1 = line.substr(9);
			}
			else if (line.find("team 2 : ") != string::npos) {
				t2 = line.substr(9);
			}
			else if (line.find("ty so : ") != string::npos) {
				tyso = line.substr(8);
				danhsachtrandau.push_back(TranDau(d, m, y, sandau, t1, t2, tyso));
			}
		}
		file.close();
	}
	else {
		cout << "Khong the mo tep tin doibong.txt." << endl;
	}
}

void luuThongTinDoiBong(const vector<doibong>& danhSachDoiBong) {
	ofstream file("doibong.txt");
	if (file.is_open() && danhSachDoiBong.size()>0) {
		danhSachDoiBong.begin()->getdscauthu();
		for (const auto& doiBong : danhSachDoiBong) {
			file << "Ten doi bong: " << doiBong.getTenDoiBong() << endl;
			file << "Dia phuong: " << doiBong.getDiaPhuong() << endl;
			file << "Huan luyen vien: " << doiBong.getHuanLuyenVien() << endl;
			file << "Danh sach cau thu: " << doiBong.getdodaidscauthu() << endl;
			if (doiBong.getdodaidscauthu() == 0) {
				file << "--------------------------" << endl;
			}
			else {
				for (const auto& cauThu : doiBong.getdscauthu()) {
					file << "So CMND: " << cauThu.getID() << endl;
					file << "Ho ten: " << cauThu.getFullname() << endl;
					file << "Quoc tich: " << cauThu.getInternational() << endl;
					file << "Ngay sinh: " << cauThu.getBirth() << endl;
					file << "Chieu cao: " << cauThu.getHeight() << endl;
					file << "Can nang: " << cauThu.getWeight() << endl;
					file << "Vi tri thi dau: " << cauThu.getPosition() << endl;
					file << "--------------------------" << endl;
				}
			}
			file << "--------------------------" << endl;
		}
		file.close();
	}
	else if (danhSachDoiBong.size() == 0) {
		file << "";
	}
	else {
		cout << "Khong the mo tep tin doibong.txt." << endl;
	}
}

void luuThongTinCauThu(const vector<CauThu>& listPlayerCT) {
	ofstream file("dsplayer.txt");
	if (file.is_open() && listPlayerCT.size() > 0) {
		for (const auto& cauThu : listPlayerCT) {
			file << "So CMND: " << cauThu.getID() << endl;
			file << "Ho ten: " << cauThu.getFullname() << endl;
			file << "Quoc tich: " << cauThu.getInternational() << endl;
			file << "Ngay sinh: " << cauThu.getBirth() << endl;
			file << "Chieu cao: " << cauThu.getHeight() << endl;
			file << "Can nang: " << cauThu.getWeight() << endl;
			file << "Vi tri thi dau: " << cauThu.getPosition() << endl;
			file << "Thuoc doi bong: " << cauThu.getTendoibong() << endl;
			file << "--------------------------" << endl;
		}
		file.close();
	}
	else if (listPlayerCT.size() == 0) {
		file << "";
	}
	else {
		cout << "Khong the mo tep tin doibong.txt." << endl;
	}
}

void luuThongTintrandau(const vector<TranDau>& danhsachtrandau) {
	ofstream file("trandau.txt");
	if (file.is_open() && danhsachtrandau.size() > 0 ) {
		for (const auto& td : danhsachtrandau) {
			file << "ngay : " << td.getNgaythidau() << endl;
			file << "thang : " << td.getThangthidau() << endl;
			file << "nam : " << td.getNamthidau() << endl;
			file << "san dau : " << td.getSandau() << endl;
			file << "team 1 : " << td.getTeam1() << endl;
			file << "team 2 : " << td.getTeam2() << endl;
			file << "ty so : " << td.getTyso() << endl;
			file << "--------------------------" << endl;
		}
		file.close();
	}
	else if (danhsachtrandau.size() == 0) {
		file << "";
	}
	else {
		cout << "Khong the mo tep tin trandau.txt." << endl;
	}
}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("Chuong trinh quan ly ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	TTF_Font* font = TTF_OpenFont("VeraMoBd.ttf", 24);
	TTF_Font* font2 = TTF_OpenFont("VeraMoBd.ttf", 19);
	TTF_Font* font3 = TTF_OpenFont("VeraMoBd.ttf", 16);
	SDL_Color color = { 255, 255, 255 };

	const char* labels[NUM_BUTTONS] = { "Quan ly cau thu", "Quan ly doi bong", "Quan ly tran dau", "Tinh diem cho cac doi bong", "Thoat" };
	const char* labels0[NUM_BUTTONS0] = { "Them doi bong", "Sua doi bong", "Xoa doi bong", "Hien thi thong tin doi bong", "Quay lai" };
	const char* labels1[NUM_BUTTONS1] = { "Xem thong tin cau thu", "Them moi cau thu","Sua cau thu", "Xoa cau thu", "Hien thi cau thu tre tuoi nhat","Hien thi cau thu cao nhat", "Hien thi cau thu thap nhat", "Quay lai" };
	const char* labels2[NUM_BUTTONS2] = { "Them tran dau", "Xem tran dau trong ngay", "Xem tran dau trong thang", "Xem tat ca tran dau", "Quay lai" };
	const char* labelsBack[NUM_BUTTONSBACK] = { "Quay lai, Quay lai, Quay lai" };
	const char* labelsTTcauThu[8] = { "So CCCD", "Ten", "Ngay Sinh", "Quoc Tich", "Chieu cao", "Can nang", "Vi tri thi dau", "Thuoc doi bong" };
	const char* labelsTTDoiBong[3] = { "Ten doi bong", "Ten dia phuong", "Huan luyen vien" };
	const char* labelsTTTD[5] = { "Ngay thi dau", "San thi dau", "Team1", "Team2", "Ty so" };


	for (int i = 0; i < NUM_BUTTONS; i++) {
		buttons[i].rect.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2; 
		buttons[i].rect.y = (SCREEN_HEIGHT - NUM_BUTTONS * BUTTON_HEIGHT - (NUM_BUTTONS - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING); 
		buttons[i].rect.w = BUTTON_WIDTH;
		buttons[i].rect.h = BUTTON_HEIGHT;
	}
	for (int i = 0; i < NUM_BUTTONS0; i++) {
		buttons0[i].rect.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2; 
		buttons0[i].rect.y = (SCREEN_HEIGHT - NUM_BUTTONS0 * BUTTON_HEIGHT - (NUM_BUTTONS0 - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING); 
		buttons0[i].rect.w = BUTTON_WIDTH;
		buttons0[i].rect.h = BUTTON_HEIGHT;
	}
	for (int i = 0; i < NUM_BUTTONS1; i++) {
		buttons1[i].rect.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
		buttons1[i].rect.y = (SCREEN_HEIGHT - NUM_BUTTONS1 * BUTTON_HEIGHT - (NUM_BUTTONS1 - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING); 
		buttons1[i].rect.w = BUTTON_WIDTH;
		buttons1[i].rect.h = BUTTON_HEIGHT;
	}
	for (int i = 0; i < NUM_BUTTONS2; i++) {
		buttons2[i].rect.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2; 
		buttons2[i].rect.y = (SCREEN_HEIGHT - NUM_BUTTONS2 * BUTTON_HEIGHT - (NUM_BUTTONS2 - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING); 
		buttons2[i].rect.w = BUTTON_WIDTH;
		buttons2[i].rect.h = BUTTON_HEIGHT;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int i = 0; i < NUM_BUTTONSBACK; i++) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, "Quay lai", { 0,0,0,255 });
		buttonsBack[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
		buttonsBack[i].rect.x = (SCREEN_WIDTH / 2) - 150 / 2; 
		buttonsBack[i].rect.y = 635;
		buttonsBack[i].rect.w = 150;
		buttonsBack[i].rect.h = 50;
		SDL_FreeSurface(surface);
	}
	Button inputTimcauthu = { (SCREEN_WIDTH / 2) - 400 / 2 , 100, 400, 50 };
	Button them = { (SCREEN_WIDTH / 2) + 400 / 2 + 80, 563, 4 * 14 + 40, 50 };
	Button themtrandau = { (SCREEN_WIDTH / 2) + 400 / 2 + 80, ((SCREEN_HEIGHT - 5 * BUTTON_HEIGHT - (5 - 1) * 30) / 2 + 4 * (BUTTON_HEIGHT + 30)) - 10, 225 , 50 };
	Button themvaodanhsach = { (SCREEN_WIDTH / 2) - 320 / 2, 500, 320, 50 };
	Button luuvaodanhsach = { (SCREEN_WIDTH / 2) - 150 / 2, 500, 150, 50 };
	Button hoantat = { (SCREEN_WIDTH / 2) - 320 / 2, 565, 320, 50 };

	Button *inputThemcauthu = new Button[8];
	Button *_inputThemcauthu = new Button[8];
	Button *inputThemvaodanhsachcauthu = new Button[11];
	Button *_inputThemvaodanhsachcauthu = new Button[11];
	Button *inputThemtrandau = new Button[5];
	Button *_inputThemtrandau = new Button[5];
	Button *inputSuacauthu = new Button[9];
	Button* _inputSuacauthu = new Button[9];

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	_inputThemvaodanhsachcauthu[0] = { 100 + 0 * 400, 5, 400, 50 };
	inputThemvaodanhsachcauthu[0] = { 100 + 0 * 400, 40, 400, 50 };
	_inputThemvaodanhsachcauthu[1] = { 100 + 1 * 400 + 50, 5, 400, 50 };
	inputThemvaodanhsachcauthu[1] = { 100 + 1 * 400 + 50, 40, 400, 50 };
	_inputThemvaodanhsachcauthu[2] = { 100 + 2 * 400 + 100, 5, 400, 50 };
	inputThemvaodanhsachcauthu[2] = { 100 + 2 * 400 + 100, 40, 400, 50 };
	for (int i = 0; i < 8; i++) {
		inputThemcauthu[i] = { (SCREEN_WIDTH - 400) / 2, ((SCREEN_HEIGHT - 8 * BUTTON_HEIGHT - (8 - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING)) + 10, 400, 50 };
		_inputThemcauthu[i] = { 350, ((SCREEN_HEIGHT - 8 * BUTTON_HEIGHT - (8 - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING)) + 10, 400, 50 };
	}
	for (int i = 3; i < 11; i++) {
		if (i < 7) {
			inputThemvaodanhsachcauthu[i] = { (SCREEN_WIDTH / 4) - (400 / 2), 170 + (i-3) * 90, 400, 50 };
			_inputThemvaodanhsachcauthu[i] = { 50, 170 + (i-3) * 90, 200, 50 };
		}
		else {
			inputThemvaodanhsachcauthu[i] = { ((SCREEN_WIDTH * 3) / 4) - (400 / 2), 170 + (i - 7) * 90, 400, 50 };
			_inputThemvaodanhsachcauthu[i] = { 750, 170 + (i-7) * 90, 200, 50 };
		}
	}
	inputSuacauthu[0] = { (SCREEN_WIDTH / 2) - 400 / 2 , 40, 400, 50 };

	for (int i = 1; i < 9; i++) {
		if (i < 5) {
			inputSuacauthu[i] = { (SCREEN_WIDTH / 4) - (400 / 2), 170 + (i - 1) * 90, 400, 50 };
			_inputSuacauthu[i] = { 50, 170 + (i - 1) * 90, 200, 50 };
		}
		else {
			inputSuacauthu[i] = { ((SCREEN_WIDTH * 3) / 4) - (400 / 2), 170 + (i - 5) * 90, 400, 50 };
			_inputSuacauthu[i] = { 750, 170 + (i - 5) * 90, 200, 50 };
		}
	}
	for (int i = 0; i < 5; i++) {
		inputThemtrandau[i] = { (SCREEN_WIDTH - 400) / 2, ((SCREEN_HEIGHT - 5 * BUTTON_HEIGHT - (5 - 1) * 30) / 2 + i * (BUTTON_HEIGHT + 30)) - 10, 400, 50 };
		_inputThemtrandau[i] = { 350, ((SCREEN_HEIGHT - 5 * BUTTON_HEIGHT - (5 - 1) * 30) / 2 + i * (BUTTON_HEIGHT + 30)) -10, 400, 50 };
	}
	Button buttonback{};
	buttonback.rect.x = (SCREEN_WIDTH / 2) - 150 / 2;
	buttonback.rect.y = 625;
	buttonback.rect.w = 150;
	buttonback.rect.h = 50;

	vector<TranDau> danhsachtrandau;
	vector<doibong> danhSachDoiBong;
	vector<CauThu> listPlayerCT;
	setDatDBFromFile(danhSachDoiBong);
	setDataCTFromdataDb(listPlayerCT, danhSachDoiBong);
	setDataTrandauFromFile(danhsachtrandau);
	luuThongTinCauThu(listPlayerCT);

	bool running = true;
	bool running2 = true;
	bool running3 = true;
	bool running4 = true;
	bool running5 = true;
	bool running6 = true;
	bool running7 = true;
	bool running8 = true;
	bool running9 = true;
	bool running10 = true;
	bool running11 = true;
	bool running12 = true;
	bool running13 = true;
	bool running14 = true;
	bool running15 = true;
	bool running16 = true;
	bool running17 = true;
	bool running18 = true;
	bool running19 = true;
	bool running20 = true;
	bool running21 = true;

	SDL_Rect viewportMainMenu = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	Uint32 mainCurentTime = SDL_GetTicks();
	cout << listPlayerCT.size();

	while (running) {
		SDL_Event event;
		int x, y;
		SDL_GetMouseState(&x, &y);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			SDL_RenderSetViewport(renderer, &viewportMainMenu);
			for (int i = 0; i < NUM_BUTTONS; i++) {
				SDL_Color textColor = { 0, 0, 0, 255 }; 
				SDL_Surface* surface = TTF_RenderText_Solid(font, labels[i], textColor);
				buttons[i].texture = SDL_CreateTextureFromSurface(renderer, surface);

				SDL_Rect textRect;
				textRect.x = buttons[i].rect.x + (BUTTON_WIDTH - surface->w) / 2; 
				textRect.y = buttons[i].rect.y + 10;
				textRect.w = surface->w; 
				textRect.h = surface->h;

				if (isPointInRect(x, y, &buttons[i].rect)) {
					SDL_SetRenderDrawColor(renderer, 225, 240, 255, 0); 
				}
				else {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
				}

				SDL_RenderFillRect(renderer, &buttons[i].rect);
				SDL_RenderCopy(renderer, buttons[i].texture, NULL, &textRect);

				SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
				SDL_RenderDrawRect(renderer, &buttons[i].rect);

				SDL_FreeSurface(surface);
			}
			for (int i = 0; i < NUM_BUTTONS; i++) {
				if (isPointInRect(x, y, &buttons[i].rect)) {
					if (event.type == SDL_MOUSEBUTTONDOWN) {
						cout << "button press " << i + 1 << endl;
						switch (i) {
						case 1:
						{
							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
							SDL_RenderClear(renderer);
							while (running3) {
								SDL_Event event;
								int x, y;
								SDL_GetMouseState(&x, &y);
								while (SDL_PollEvent(&event)) {
									SDL_RenderSetViewport(renderer, &viewportMainMenu);
									if (event.type == SDL_QUIT) {
										return 0;
									}
									for (int i = 0; i < NUM_BUTTONS0; i++) {
										SDL_Color textColor = { 0, 0, 0, 255 }; 
										SDL_Surface* surface = TTF_RenderText_Solid(font, labels0[i], textColor);
										buttons0[i].texture = SDL_CreateTextureFromSurface(renderer, surface);

										SDL_Rect textRect;
										textRect.x = buttons0[i].rect.x + (BUTTON_WIDTH - surface->w) / 2;
										textRect.y = buttons0[i].rect.y + 10;
										textRect.w = surface->w; 
										textRect.h = surface->h;

										if (isPointInRect(x, y, &buttons0[i].rect)) {
											SDL_SetRenderDrawColor(renderer, 225, 240, 255, 0); // Màu cam khi hover
										}
										else {
											SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng khi không hover
										}

										SDL_RenderFillRect(renderer, &buttons0[i].rect);
										SDL_RenderCopy(renderer, buttons0[i].texture, NULL, &textRect);

										SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
										SDL_RenderDrawRect(renderer, &buttons0[i].rect);

										SDL_FreeSurface(surface);
									}
									for (int i = 0; i < NUM_BUTTONS0; i++) {
										if (isPointInRect(x, y, &buttons0[i].rect)) {
											//cout << "is hover" << endl;
											if (event.type == SDL_MOUSEBUTTONDOWN) {
												cout << "button press " << i + 1 << endl;
												switch (i) {
												case 0:
												{
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);

													SDL_Surface* textSurface;
													SDL_Texture* textTexture;

													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;

													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;

													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;

													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;

													SDL_Surface* textSurface6;
													SDL_Texture* textTexture6;

													SDL_Surface* textSurface7;
													SDL_Texture* textTexture7;

													SDL_Surface* textSurface8;
													SDL_Texture* textTexture8;

													SDL_Surface* textSurface9;
													SDL_Texture* textTexture9;

													SDL_Surface* textSurface10;
													SDL_Texture* textTexture10;

													SDL_Surface* textSurface11;
													SDL_Texture* textTexture11;

													SDL_Surface* textSurface12;
													SDL_Texture* textTexture12;

													SDL_Surface* textSurface13;
													SDL_Texture* textTexture13;

													SDL_Surface* textSurface14;
													SDL_Texture* textTexture14;

													string* labelInput = new string[11];
													string* _labelInput = new string[11];
													for (int i = 0; i < 11; i++) {
														labelInput[i] = " ";
													}
													
													int n = 3;
													vector<CauThu> dsct;
													SDL_Color textColor = { 0, 0, 0, 255 };
													bool inValidct = false;
													bool susscesct = false;
													bool susscesdb = false;
													bool checkDB = false;

													Uint32 lastCursorToggleTime = 0;
													int ispointerInputTimcauthu = -1;

													for (int i = 3; i < 10; i++) {
														SDL_Surface* surface = TTF_RenderText_Solid(font2, labelsTTcauThu[i-3], { 0,0,0,255 });
														_inputThemvaodanhsachcauthu[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
														SDL_Rect textRect = { _inputThemvaodanhsachcauthu[i].rect.x + 10, _inputThemvaodanhsachcauthu[i].rect.y + 10, surface->w, surface->h };
														SDL_RenderCopy(renderer, _inputThemvaodanhsachcauthu[i].texture, NULL, &textRect);
														SDL_FreeSurface(surface);
													}
													for (int i = 0; i < 3; i++) {
														SDL_Surface* surface = TTF_RenderText_Solid(font2, labelsTTDoiBong[i], { 0,0,0,255 });
														_inputThemvaodanhsachcauthu[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
														SDL_Rect textRect = { _inputThemvaodanhsachcauthu[i].rect.x + 10, _inputThemvaodanhsachcauthu[i].rect.y + 3, surface->w, surface->h };
														SDL_RenderCopy(renderer, _inputThemvaodanhsachcauthu[i].texture, NULL, &textRect);
														SDL_FreeSurface(surface);
													}
													SDL_Surface* surfaceThem = TTF_RenderText_Solid(font2, "Them cau thu vao danh sach", { 0,0,0,255 });
													themvaodanhsach.texture = SDL_CreateTextureFromSurface(renderer, surfaceThem);
													SDL_Rect textRectThem = { themvaodanhsach.rect.x + 17, themvaodanhsach.rect.y + 12, surfaceThem->w, surfaceThem->h };
													SDL_RenderCopy(renderer, themvaodanhsach.texture, NULL, &textRectThem);
													SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Màu do
													SDL_RenderDrawRect(renderer, &themvaodanhsach.rect);
													SDL_FreeSurface(surfaceThem);

													SDL_Surface* surfaceThem2 = TTF_RenderText_Solid(font2, "THEM DOI BONG VAO DANH SACH", { 0, 128, 0, 255 });
													hoantat.texture = SDL_CreateTextureFromSurface(renderer, surfaceThem2);
													SDL_Rect textRectThem2 = { hoantat.rect.x + 10, hoantat.rect.y + 12, surfaceThem2->w, surfaceThem2->h };
													SDL_RenderCopy(renderer, hoantat.texture, NULL, &textRectThem2);
													SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Màu do
													SDL_RenderDrawRect(renderer, &hoantat.rect);
													SDL_FreeSurface(surfaceThem2);

													SDL_RenderPresent(renderer);

													while (running17) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														for (int i = 3; i < 10; i++) {

															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &inputThemvaodanhsachcauthu[i].rect);

															// Vẽ viền cam cho nút
															SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
															SDL_RenderDrawRect(renderer, &inputThemvaodanhsachcauthu[i].rect);
														}
														for (int i = 0; i < 3; i++) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &inputThemvaodanhsachcauthu[i].rect);

															// Vẽ viền cam cho nút
															SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
															SDL_RenderDrawRect(renderer, &inputThemvaodanhsachcauthu[i].rect);
														}
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &buttonsBack[8].rect)) {
																	if (susscesdb == false && dsct.size() > 0) {
																		for (int i = 0; i < dsct.size(); i++) {
																			listPlayerCT.pop_back();
																		}
																	}
																	running17 = false;
																}
																if (isPointInRect(x, y, &themvaodanhsach.rect)
																	&& labelInput[0].length() > 1
																	&& labelInput[1].length() > 1
																	&& labelInput[2].length() > 1
																	&& labelInput[3].length() > 1 
																	&& labelInput[4].length() > 1 
																	&& labelInput[5].length() > 1 
																	&& labelInput[6].length() > 1
																	&& labelInput[7].length() > 1
																	&& labelInput[8].length() > 1 
																	&& labelInput[9].length() > 1) {
																	for (int i = 0; i < 10; i++) {
																		_labelInput[i] = labelInput[i];
																		_labelInput[i].erase(0, 1);
																	}
																	for (int i = 0; i < danhSachDoiBong.size(); i++) {
																	
																		if (danhSachDoiBong[i].getTenDoiBong() == _labelInput[0]) {
																			cout << "ten doi bong da ton tai" << endl;
																			checkDB = true;
																			break;
																		}
																		if (i == danhSachDoiBong.size() - 1) {

																			for (int i = 0; i < listPlayerCT.size(); i++) {
																				if (listPlayerCT[i].getID() == _labelInput[3]) {
																					cout << "-.-" << endl;
																					cout << "so can cuoc cong dan da ton tai!!" << endl;
																					inValidct = true;
																					break;
																				}
																				else {
																					inValidct = false;
																				}
																				if (i == listPlayerCT.size() - 1) {
																					CauThu t(CauThu(_labelInput[3], _labelInput[4], _labelInput[6], _labelInput[5], _labelInput[7], _labelInput[8], _labelInput[9], _labelInput[0]));
																					inValidct = false;
																					susscesct = true;
																					dsct.push_back(t);
																					listPlayerCT.push_back(t);
																					break;
																				}
																			}
																			break;
																		}
																	}
																	if (danhSachDoiBong.size() == 0) {
																		if (dsct.size() == 0) {
																			CauThu t(CauThu(_labelInput[3], _labelInput[4], _labelInput[6], _labelInput[5], _labelInput[7], _labelInput[8], _labelInput[9], _labelInput[0]));
																			inValidct = false;
																			susscesct = true;
																			dsct.push_back(t);
																			listPlayerCT.push_back(t);
																		}
																		else {
																			for (int i = 0; i < dsct.size(); i++) {
																				if (dsct[i].getID() == _labelInput[3]) {
																					cout << "-.-" << endl;
																					cout << "so can cuoc cong dan da ton tai!!" << endl;
																					inValidct = true;
																					break;
																				}
																				else {
																					inValidct = false;
																				}
																				if (i == dsct.size() - 1) {
																					CauThu t(CauThu(_labelInput[3], _labelInput[4], _labelInput[6], _labelInput[5], _labelInput[7], _labelInput[8], _labelInput[9], _labelInput[0]));
																					inValidct = false;
																					susscesct = true;
																					dsct.push_back(t);
																					listPlayerCT.push_back(t);
																					break;
																				}
																			}
																		}
																	}
																}
																if (isPointInRect(x, y, &hoantat.rect)
																	&& labelInput[0].length() > 1
																	&& labelInput[1].length() > 1
																	&& labelInput[2].length() > 1
																	) {
																	for (int i = 0; i < 3; i++) {
																		_labelInput[i] = labelInput[i];
																		_labelInput[i].erase(0, 1);
																	}
																	
																	for (int i = 0; i < danhSachDoiBong.size(); i++) {
																		if (danhSachDoiBong[i].getTenDoiBong() == _labelInput[0]) {
																			cout << "ten doi bong da ton tai" << endl;
																			susscesdb = false;
																			checkDB = true;
																			break;
																		}
																		if (i == danhSachDoiBong.size() - 1) {
																			susscesdb = true;
																			checkDB = false;
																			inValidct = false;
																			susscesct = false;
																			
																			danhSachDoiBong.push_back(doibong(_labelInput[0], _labelInput[1], _labelInput[2], dsct));
																			dsct.clear();
																			break;
																		}
																	}
																	if (danhSachDoiBong.size() == 0) {
																		susscesdb = true;
																		checkDB = false;
																		inValidct = false;
																		susscesct = false;

																		danhSachDoiBong.push_back(doibong(_labelInput[0], _labelInput[1], _labelInput[2], dsct));
																		dsct.clear();
																	}
																}

															}
															
															for (int i = 0; i < n; i++) {
																if (event.type == SDL_MOUSEBUTTONDOWN) {
																	if (labelInput[0].length() == 1 || labelInput[1].length() == 1 || labelInput[2].length() == 1) {
																		n = 3;
																	}
																	if (labelInput[0].length() > 1 && labelInput[1].length() > 1 && labelInput[2].length() > 1) {
																		n = 10;
																	}
																	if (isPointInRect(x, y, &inputThemvaodanhsachcauthu[i].rect)) {
																		lastCursorToggleTime = mainCurentTime - 1000;
																		ispointerInputTimcauthu = i;
																		checkDB = false;
																		inValidct = false;
																		susscesct = false;
																		susscesdb = false;
																	}
																	if (!isPointInRect(x, y, &inputThemvaodanhsachcauthu[0].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[1].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[2].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[3].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[4].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[5].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[6].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[7].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[8].rect)
																		&& !isPointInRect(x, y, &inputThemvaodanhsachcauthu[9].rect)
																		) {
																		ispointerInputTimcauthu = -1;
																	}
																}
															}
															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu != -1) {
																if (event.key.keysym.sym == 9) {
																	if (ispointerInputTimcauthu < 9 && ispointerInputTimcauthu != -1 ) {
																		if (labelInput[0].length() > 1 && labelInput[1].length() > 1 && labelInput[2].length() > 1) {
																			ispointerInputTimcauthu++;
																		}
																		if (ispointerInputTimcauthu < 2 && labelInput[0].length() >= 1 && labelInput[1].length() >= 1 && labelInput[2].length() >= 1) {
																			ispointerInputTimcauthu++;
																		}
																	}
																}

																if (event.key.keysym.sym == SDLK_BACKSPACE && labelInput[ispointerInputTimcauthu].length() > 1) {
																	labelInput[ispointerInputTimcauthu].pop_back();
																}
															}
															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu != -1) {
																labelInput[ispointerInputTimcauthu] += event.text.text;
															}

														}

														textSurface11 = TTF_RenderText_Solid(font2, "Them cau thu thanh cong!!", { 0, 128, 0, 255 });
														textTexture11 = SDL_CreateTextureFromSurface(renderer, textSurface11);
														SDL_Rect textRect11 = { inputThemvaodanhsachcauthu[6].rect.x + 435, inputThemvaodanhsachcauthu[6].rect.y + 10, textSurface11->w, textSurface11->h };

														textSurface12 = TTF_RenderText_Solid(font, "Them doi bong thanh cong!!", { 0, 128, 0, 255 });
														textTexture12 = SDL_CreateTextureFromSurface(renderer, textSurface12);
														SDL_Rect textRect12 = { inputThemvaodanhsachcauthu[1].rect.x + 10, inputThemvaodanhsachcauthu[1].rect.y + 60, textSurface12->w, textSurface12->h };

														textSurface13 = TTF_RenderText_Solid(font2, "Doi bong da ton tai!!", { 255, 0, 0, 0 });
														textTexture13 = SDL_CreateTextureFromSurface(renderer, textSurface13);
														SDL_Rect textRect13 = { inputThemvaodanhsachcauthu[0].rect.x + 25, inputThemvaodanhsachcauthu[0].rect.y + 55, textSurface13->w, textSurface13->h };

														textSurface14 = TTF_RenderText_Solid(font2, "So CCCD da ton tai!!", { 255, 0, 0, 0 });
														textTexture14 = SDL_CreateTextureFromSurface(renderer, textSurface14);
														SDL_Rect textRect14 = { inputThemvaodanhsachcauthu[3].rect.x + 10, inputThemvaodanhsachcauthu[3].rect.y + 55, textSurface14->w, textSurface14->h };

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														if (susscesdb) {
															SDL_RenderFillRect(renderer, &textRect12);
															SDL_RenderCopy(renderer, textTexture12, NULL, &textRect12);
															SDL_Rect white3 = { inputThemvaodanhsachcauthu[3].rect.x + 10, inputThemvaodanhsachcauthu[3].rect.y + 55, 400, 30 };
															SDL_RenderFillRect(renderer, &white3);
															SDL_Rect white4 = { inputThemvaodanhsachcauthu[0].rect.x + 25, inputThemvaodanhsachcauthu[0].rect.y + 55, 300, 30 };
															SDL_RenderFillRect(renderer, &white4);
															SDL_Rect white2 = { inputThemvaodanhsachcauthu[6].rect.x + 435, inputThemvaodanhsachcauthu[6].rect.y + 10, 400, 30 };
															SDL_RenderFillRect(renderer, &white2);
														}
														if (ispointerInputTimcauthu >= 3 && ispointerInputTimcauthu <= 9) {
															SDL_Rect white3 = { inputThemvaodanhsachcauthu[3].rect.x + 10, inputThemvaodanhsachcauthu[3].rect.y + 55, 400, 30 };
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &white3);
															
														}
														if (ispointerInputTimcauthu != -1) {
															SDL_Rect white2 = { inputThemvaodanhsachcauthu[6].rect.x + 435, inputThemvaodanhsachcauthu[6].rect.y + 10, 400, 30 };
															SDL_Rect white = { inputThemvaodanhsachcauthu[1].rect.x , inputThemvaodanhsachcauthu[1].rect.y + 60, 400, 70 };
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &white2);
															SDL_RenderFillRect(renderer, &white);
														}
														if (ispointerInputTimcauthu == 0) {
															SDL_Rect white4 = { inputThemvaodanhsachcauthu[0].rect.x + 25, inputThemvaodanhsachcauthu[0].rect.y + 55, 300, 30 }; 
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &white4);
														}
														if (susscesct) {
															SDL_RenderFillRect(renderer, &textRect11);
															SDL_RenderCopy(renderer, textTexture11, NULL, &textRect11);
															SDL_Rect white3 = { inputThemvaodanhsachcauthu[3].rect.x + 10, inputThemvaodanhsachcauthu[3].rect.y + 55, 400, 30 };
															SDL_RenderFillRect(renderer, &white3);
															susscesct = false;
														}
														if (checkDB) {
															SDL_RenderFillRect(renderer, &textRect13);
															SDL_RenderCopy(renderer, textTexture13, NULL, &textRect13);
															SDL_Rect white2 = { inputThemvaodanhsachcauthu[6].rect.x + 435, inputThemvaodanhsachcauthu[6].rect.y + 10, 400, 30 };
															SDL_RenderFillRect(renderer, &white2);
															SDL_Rect white = { inputThemvaodanhsachcauthu[1].rect.x , inputThemvaodanhsachcauthu[1].rect.y + 60, 400, 70 };
															SDL_RenderFillRect(renderer, &white);
															checkDB = false;
														}
														if (inValidct) {
															SDL_RenderFillRect(renderer, &textRect14);
															SDL_RenderCopy(renderer, textTexture14, NULL, &textRect14);
															SDL_Rect white2 = { inputThemvaodanhsachcauthu[6].rect.x + 435, inputThemvaodanhsachcauthu[6].rect.y + 10, 400, 30 };
															SDL_RenderFillRect(renderer, &white2);
															SDL_Rect white = { inputThemvaodanhsachcauthu[1].rect.x , inputThemvaodanhsachcauthu[1].rect.y + 60, 400, 70 };
															SDL_RenderFillRect(renderer, &white);
															inValidct = false;
														}
														//1
														textSurface = TTF_RenderText_Solid(font, labelInput[0].c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputThemvaodanhsachcauthu[0].rect.x + 10, inputThemvaodanhsachcauthu[0].rect.y + 10, textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														//2
														textSurface2 = TTF_RenderText_Solid(font, labelInput[1].c_str(), textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { inputThemvaodanhsachcauthu[1].rect.x + 10, inputThemvaodanhsachcauthu[1].rect.y + 10, textSurface2->w, textSurface2->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														//3
														textSurface3 = TTF_RenderText_Solid(font, labelInput[2].c_str(), textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { inputThemvaodanhsachcauthu[2].rect.x + 10, inputThemvaodanhsachcauthu[2].rect.y + 10, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														//4
														textSurface4 = TTF_RenderText_Solid(font, labelInput[3].c_str(), textColor);
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { inputThemvaodanhsachcauthu[3].rect.x + 10, inputThemvaodanhsachcauthu[3].rect.y + 10, textSurface4->w, textSurface4->h };
														SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);

														//5
														textSurface5 = TTF_RenderText_Solid(font, labelInput[4].c_str(), textColor);
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { inputThemvaodanhsachcauthu[4].rect.x + 10, inputThemvaodanhsachcauthu[4].rect.y + 10, textSurface5->w, textSurface5->h };
														SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);

														//6
														textSurface6 = TTF_RenderText_Solid(font, labelInput[5].c_str(), textColor);
														textTexture6 = SDL_CreateTextureFromSurface(renderer, textSurface6);
														SDL_Rect textRect6 = { inputThemvaodanhsachcauthu[5].rect.x + 10, inputThemvaodanhsachcauthu[5].rect.y + 10, textSurface6->w, textSurface6->h };
														SDL_RenderCopy(renderer, textTexture6, NULL, &textRect6);

														//7
														textSurface7 = TTF_RenderText_Solid(font, labelInput[6].c_str(), textColor);
														textTexture7 = SDL_CreateTextureFromSurface(renderer, textSurface7);
														SDL_Rect textRect7 = { inputThemvaodanhsachcauthu[6].rect.x + 10, inputThemvaodanhsachcauthu[6].rect.y + 10, textSurface7->w, textSurface7->h };
														SDL_RenderCopy(renderer, textTexture7, NULL, &textRect7);

														//8
														textSurface8 = TTF_RenderText_Solid(font, labelInput[7].c_str(), textColor);
														textTexture8 = SDL_CreateTextureFromSurface(renderer, textSurface8);
														SDL_Rect textRect8 = { inputThemvaodanhsachcauthu[7].rect.x + 10, inputThemvaodanhsachcauthu[7].rect.y + 10, textSurface8->w, textSurface8->h };
														SDL_RenderCopy(renderer, textTexture8, NULL, &textRect8);
														//9
														textSurface9 = TTF_RenderText_Solid(font, labelInput[8].c_str(), textColor);
														textTexture9 = SDL_CreateTextureFromSurface(renderer, textSurface9);
														SDL_Rect textRect9 = { inputThemvaodanhsachcauthu[8].rect.x + 10, inputThemvaodanhsachcauthu[8].rect.y + 10, textSurface9->w, textSurface9->h };
														SDL_RenderCopy(renderer, textTexture9, NULL, &textRect9);
														//10
														textSurface10 = TTF_RenderText_Solid(font, labelInput[9].c_str(), textColor);
														textTexture10 = SDL_CreateTextureFromSurface(renderer, textSurface10);
														SDL_Rect textRect10 = { inputThemvaodanhsachcauthu[9].rect.x + 10, inputThemvaodanhsachcauthu[9].rect.y + 10, textSurface10->w, textSurface10->h };
														SDL_RenderCopy(renderer, textTexture10, NULL, &textRect10);
													
														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}

														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu != -1) {
															// Vẽ con trỏ văn bản
															SDL_Rect cursorRect = { inputThemvaodanhsachcauthu[ispointerInputTimcauthu].rect.x + ((labelInput[ispointerInputTimcauthu].length() + 0.7) * (70 / 5)), inputThemvaodanhsachcauthu[ispointerInputTimcauthu].rect.y + 10, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &buttonsBack[8].rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &buttonsBack[8].rect);
														SDL_Rect textRectBack0 = { buttonsBack[8].rect.x + 10, buttonsBack[8].rect.y + 10, buttonsBack[8].rect.w - 20, buttonsBack[8].rect.h - 20 };
														SDL_RenderCopy(renderer, buttonsBack[8].texture, NULL, &textRectBack0);

														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);
														SDL_DestroyTexture(textTexture6);
														SDL_FreeSurface(textSurface6);
														SDL_DestroyTexture(textTexture7);
														SDL_FreeSurface(textSurface7);
														SDL_DestroyTexture(textTexture8);
														SDL_FreeSurface(textSurface8);
														SDL_DestroyTexture(textTexture9);
														SDL_FreeSurface(textSurface9);
														SDL_DestroyTexture(textTexture10);
														SDL_FreeSurface(textSurface10);
														SDL_DestroyTexture(textTexture11);
														SDL_FreeSurface(textSurface11);
														SDL_DestroyTexture(textTexture12);
														SDL_FreeSurface(textSurface12);
														SDL_DestroyTexture(textTexture13);
														SDL_FreeSurface(textSurface13);
														SDL_DestroyTexture(textTexture14);
														SDL_FreeSurface(textSurface14);

														SDL_RenderPresent(renderer);
													}
													luuThongTinCauThu(listPlayerCT);
													luuThongTinDoiBong(danhSachDoiBong);
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													running17 = true;
													delete[] labelInput;
													delete[] _labelInput;
													break;
												}
												case 1:
												{
													const int NUM_ROWS = 2;
													const int NUM_COLS = 3;
													const int NUM_COLSCT = 8;
													const int CELL_WIDTH = ((SCREEN_WIDTH) / NUM_COLS);
													const int CELL_WIDTHCT = ((SCREEN_WIDTH) / NUM_COLSCT)-6;
													const int CELL_HEIGHT = 60;

													SDL_Surface* textSurface;
													SDL_Texture* textTexture;

													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;

													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;

													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;

													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;

													SDL_Surface* textSurface6;
													SDL_Texture* textTexture6;

													SDL_Surface* textSurface7;
													SDL_Texture* textTexture7;

													SDL_Surface* textSurface8;
													SDL_Texture* textTexture8;

													Button* inputSuadoibong = new Button[4];
													Button* _inputSuadoibong = new Button[4];

													string* lableTTDB = new string[4];
													string* _lableTTDB = new string[4];
													string* lableTTCT = new string[8];
													Button* buttonsBackk = new Button;
													Button *buttonsBackkluu = new Button;
													
													for (int i = 0; i < 4; i++) {
														lableTTDB[i] = " ";
													}

													SDL_Rect viewport = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT - 110 };
													SDL_Rect content = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

													SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
													SDL_RenderClear(renderer); // Xóa màn hình

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_Surface* t = TTF_RenderText_Solid(font2, "Quay lai", { 0,0,0,255 });
													buttonsBackk->rect = { buttonsBack[4].rect.x, buttonsBack[4].rect.y + 15, buttonsBack[4].rect.w , buttonsBack[4].rect.h - 10 };
													SDL_RenderFillRect(renderer, &buttonsBackk->rect);
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBackk->rect);
													buttonsBackk->texture = SDL_CreateTextureFromSurface(renderer, t);
													SDL_Rect textRectBack0 = { buttonsBackk->rect.x + buttonsBackk->rect.w/2 - t->w/2 , buttonsBackk->rect.y + 10, t->w, buttonsBackk->rect.h - 20 };
													SDL_RenderCopy(renderer, buttonsBackk->texture, NULL, &textRectBack0);
													SDL_DestroyTexture(buttonsBackk->texture);
													SDL_FreeSurface(t);

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_Surface* t2 = TTF_RenderText_Solid(font2, "-Luu-", { 0,0,255,0 });
													buttonsBackkluu->rect = { buttonsBack[4].rect.x, buttonsBack[4].rect.y - 32, buttonsBack[4].rect.w , buttonsBack[4].rect.h - 10 };
													SDL_RenderFillRect(renderer, &buttonsBackkluu->rect);
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBackkluu->rect);
													buttonsBackkluu->texture = SDL_CreateTextureFromSurface(renderer, t2);
													SDL_Rect textRectBack2 = { buttonsBackkluu->rect.x + buttonsBackkluu->rect.w / 2 - t->w / 2 , buttonsBackkluu->rect.y + 10, t->w, buttonsBackkluu->rect.h - 20 };
													SDL_RenderCopy(renderer, buttonsBackkluu->texture, NULL, &textRectBack2);
													SDL_FreeSurface(t);
													SDL_DestroyTexture(buttonsBackkluu->texture);
													SDL_RenderPresent(renderer);

													int renDer = 0;
													int _renDer = 0;
													int check = 0;
													int sussces = 0;
													int* n = new int;
													*n = 1;
													vector<CauThu> dsct;
													vector<Button> buttonXoa;
													int scrollY = 0;
													int index;
													
													int ispointerInputTimDoiBong = -1;
													Uint32 lastCursorToggleTime = 0;
													while (running20) {

														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderSetViewport(renderer, &viewport);

														SDL_RenderFillRect(renderer, &content);

														for (int i = 0; i < 4; i++) {
															if (i == 0) {
																inputSuadoibong[i] = { (SCREEN_WIDTH / 2) - 400 / 2, 40-scrollY , 400, 50 };
															}
															else {
																inputSuadoibong[i] = { 100 + ((i - 1) * 400) + ((i - 1) * 50), 150 - scrollY, 400, 50 };
																_inputSuadoibong[i] = { 100 + ((i - 1) * 400) + ((i - 1) * 50), 115 - scrollY, 400, 50 };
															}
														}
														for (int i = 0; i < 4; i++) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &inputSuadoibong[i].rect);
															SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
															SDL_RenderDrawRect(renderer, &inputSuadoibong[i].rect);
														}
														for (int i = 0; i < 3; i++) {
															SDL_Surface* surface = TTF_RenderText_Solid(font2, labelsTTDoiBong[i], { 0,0,0,255 });
															_inputSuadoibong[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
															SDL_Rect text = { _inputSuadoibong[i+1].rect.x + _inputSuadoibong[i + 1].rect.w/2 - surface->w/2 , _inputSuadoibong[i+1].rect.y + 8, surface->w, surface->h };
															SDL_RenderCopy(renderer, _inputSuadoibong[i].texture, NULL, &text);
															SDL_FreeSurface(surface);
														}
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEWHEEL) {
																if (event.wheel.y >= 0) {
																	if (scrollY >= 0) {
																		scrollY -= 15;
																	}
																}
																else if (event.wheel.y < 0) {
																	if (300 + ((dsct.size() + 1) * CELL_HEIGHT) > SCREEN_HEIGHT - 100) {
																		scrollY += 15;
																	}
																}
															}

															if (event.type == SDL_MOUSEBUTTONDOWN) {
																for (int i = 0; i < *n; i++) {
																	if (lableTTDB[0].length() > 1 && _renDer == 1) {
																		*n = 4;
																	}
																	else *n = 1;
																	if (isPointInRect(x, y, &inputSuadoibong[i].rect)) {
																		if (i == 0) renDer = 1;
																		cout << "ispointer" << endl;
																		lastCursorToggleTime = mainCurentTime - 1000;
																		ispointerInputTimDoiBong = i;
																	}
																}
																for (int i = 0; i < buttonXoa.size(); i++) {
																	if (isPointInRect(x, y, &buttonXoa[i].rect)) {
																		if (dsct.size() > 0) {
																			dsct.erase(dsct.begin() + static_cast<vector<int>::size_type>(i));
																			buttonXoa.erase(buttonXoa.begin() + static_cast<vector<int>::size_type>(i));
																		}
																	}
																}
																if (isPointInRect(x, y, &buttonsBackk->rect)) {
																	running20 = false;
																}
																if (isPointInRect(x, y, &buttonsBackkluu->rect) 
																	&& lableTTDB[0].length() > 1
																	&& lableTTDB[1].length() > 1
																	&& lableTTDB[2].length() > 1
																	&& lableTTDB[3].length() > 1) {
																	ispointerInputTimDoiBong = -1;
																	for (int i = 0; i < 4; i++) {
																		_lableTTDB[i] = lableTTDB[i];
																		_lableTTDB[i].erase(0, 1);
																	}
																	for (int i = 0; i < danhSachDoiBong.size(); i++) {
																		if (i != index) {
																			if (_lableTTDB[1] == danhSachDoiBong[i].getTenDoiBong()) {
																				check = 1;
																				cout << "ton tai" << endl;
																				break;
																			}
																		}
																		if (i == danhSachDoiBong.size() - 1) {
																			sussces = 1;
																			danhSachDoiBong[index].suadoibong(_lableTTDB[1], _lableTTDB[2], _lableTTDB[3], dsct);
																			setDataCTFromdataDb(listPlayerCT, danhSachDoiBong);
																		}
																	}
																}
															}

															if (event.type == SDL_KEYDOWN && ispointerInputTimDoiBong != -1) {
																if (ispointerInputTimDoiBong < 3 && renDer) {
																	if (event.key.keysym.sym == 9 && lableTTDB[ispointerInputTimDoiBong].length() > 1) {
																		ispointerInputTimDoiBong++;
																	}
																}

																if (event.key.keysym.sym == SDLK_RETURN && lableTTDB[0].length() > 1 && ispointerInputTimDoiBong == 0) {
																	
																	/*inputText2 = inputText;
																	inputText2.erase(0, 1);*/
																	//for (int i = 0; i < 4; i++) {
																		_lableTTDB[0] = lableTTDB[0];
																		_lableTTDB[0].erase(0, 1);
																	//}
																	for (int i = 1; i < 4; i++) {
																		lableTTDB[i] = " ";
																	}
																	for (int i = 0; i < danhSachDoiBong.size(); i++) {
																		if (_lableTTDB[0] == danhSachDoiBong[i].getTenDoiBong()) {
																			lableTTDB[1] += danhSachDoiBong[i].getTenDoiBong();
																			lableTTDB[2] += danhSachDoiBong[i].getDiaPhuong();
																			lableTTDB[3] += danhSachDoiBong[i].getHuanLuyenVien();
																			dsct = danhSachDoiBong[i].getdscauthu();
																			renDer = 1;
																			_renDer = 1;
																			buttonXoa.clear();
																			for (int i = 0; i < dsct.size(); i++) {
																				Button* t = new Button;
																				t->rect = { SCREEN_WIDTH-50, 250 + i * CELL_HEIGHT + 10 , 40, 30 };
																				buttonXoa.push_back(*t);
																				delete t;
																			}
																			index = i;
																			cout << buttonXoa.size() << endl;
																			break;
																		}
																		if (i == danhSachDoiBong.size() - 1) {
																			buttonXoa.clear();
																			for (int i = 1; i < 4; i++) {
																				lableTTDB[i] = " ";
																			}
																			renDer = 0;
																			_renDer = 0;
																		}
																	}
																	if (danhSachDoiBong.size() == 0) {
																		renDer = 0;
																	}

																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && lableTTDB[ispointerInputTimDoiBong].length() > 1 && ispointerInputTimDoiBong != -1) {
																	//inputText.pop_back();
																	lableTTDB[ispointerInputTimDoiBong].pop_back();
																}
															}

															if (event.type == SDL_TEXTINPUT && ispointerInputTimDoiBong != -1) {
																//inputText += event.text.text;
																lableTTDB[ispointerInputTimDoiBong] += event.text.text;

															}
														}
														//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														//SDL_RenderFillRect(renderer, &inputTimDoiBong.rect);
														//SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														//SDL_RenderDrawRect(renderer, &inputTimDoiBong.rect);

														SDL_Color textColor = { 0, 0, 0, 255 };
														textSurface = TTF_RenderText_Solid(font, lableTTDB[0].c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputSuadoibong[0].rect.x + 10, inputSuadoibong[0].rect.y + 10 , textSurface->w, textSurface->h};
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														textSurface2 = TTF_RenderText_Solid(font, lableTTDB[1].c_str(), textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { inputSuadoibong[1].rect.x + 10, inputSuadoibong[1].rect.y + 10 , textSurface2->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														textSurface4 = TTF_RenderText_Solid(font, lableTTDB[2].c_str(), textColor);
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { inputSuadoibong[2].rect.x + 10, inputSuadoibong[2].rect.y + 10 , textSurface4->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);

														textSurface6 = TTF_RenderText_Solid(font, lableTTDB[3].c_str(), textColor);
														textTexture6 = SDL_CreateTextureFromSurface(renderer, textSurface6);
														SDL_Rect textRect6 = { inputSuadoibong[3].rect.x + 10, inputSuadoibong[3].rect.y + 10 , textSurface6->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture6, NULL, &textRect6);

														textSurface3 = TTF_RenderText_Solid(font, "NHAP TEN DOI BONG CAN SUA", textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { (SCREEN_WIDTH / 2) - (textSurface3->w / 2) , 10 - scrollY, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														textSurface5 = TTF_RenderText_Solid(font, "KHONG TIM THAY !!!!", {255,0,0,0});
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { (SCREEN_WIDTH / 2) - (textSurface5->w / 2) , SCREEN_HEIGHT / 2, textSurface5->w, textSurface5->h };

														textSurface7 = TTF_RenderText_Solid(font2, "Doi bong da ton tai!!!!", { 255,0,0,0 });
														textTexture7 = SDL_CreateTextureFromSurface(renderer, textSurface7);
														SDL_Rect textRect7 = { inputSuadoibong[1].rect.x + 20 , inputSuadoibong[1].rect.y + 53, textSurface7->w, textSurface7->h};

														textSurface8 = TTF_RenderText_Solid(font2, "LUU THANH CONG !!!!", { 0,128,0,0 });
														textTexture8 = SDL_CreateTextureFromSurface(renderer, textSurface8);
														SDL_Rect textRect8 = { inputSuadoibong[0].rect.x + inputSuadoibong[0].rect.w/2 - textSurface8->w/2 , inputSuadoibong[0].rect.y + 53, textSurface8->w, textSurface8->h };
														if (check) {
															SDL_RenderCopy(renderer, textTexture7, NULL, &textRect7);
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white2 = { inputSuadoibong[0].rect.x + 20 , inputSuadoibong[0].rect.y + 53, 400, 30 };
															SDL_RenderFillRect(renderer, &white2);
														}
														if (sussces) {
															SDL_RenderCopy(renderer, textTexture8, NULL, &textRect8);
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white = { inputSuadoibong[1].rect.x + 20 , inputSuadoibong[1].rect.y + 53, 400, 30 };
															SDL_RenderFillRect(renderer, &white);
														}
														if (renDer == 0 && ispointerInputTimDoiBong != -1) {
															SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);
														}
														if (ispointerInputTimDoiBong == 1 ) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white = { inputSuadoibong[1].rect.x + 20 , inputSuadoibong[1].rect.y + 53, 400, 30 };
															SDL_RenderFillRect(renderer, &white);
														}
														if (ispointerInputTimDoiBong == 0) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white2 = { inputSuadoibong[0].rect.x + 20 , inputSuadoibong[0].rect.y + 53, 400, 30 };
															SDL_RenderFillRect(renderer, &white2);
														}
														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}

														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimDoiBong != -1) {
															SDL_Rect cursorRect = { inputSuadoibong[ispointerInputTimDoiBong].rect.x + ((lableTTDB[ispointerInputTimDoiBong].length() + 0.7) * (70 / 5)), inputSuadoibong[ispointerInputTimDoiBong].rect.y + 10, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														if (_lableTTDB[0].length() > 0 && renDer) {
															int k = 0;
															string lableTTct[8];

															if (dsct.size() > 0) {
																for (int i = 0; i < dsct.size() + 1; i++) {

																	if (i > 0) {
																		buttonXoa[i - 1].rect.y = 250 + i * CELL_HEIGHT + 13 - scrollY;
																		SDL_Surface* text = TTF_RenderText_Solid(font3, "xoa", {255, 0, 0, 0});
																		buttonXoa[i - 1].texture = SDL_CreateTextureFromSurface(renderer, text);
																		SDL_Rect textRectXoa = { buttonXoa[i - 1].rect.x+5, buttonXoa[i - 1].rect.y+5, text->w, text->h };
																		SDL_RenderDrawRect(renderer, &buttonXoa[i-1].rect);
																		SDL_RenderCopy(renderer, buttonXoa[i - 1].texture, NULL, &textRectXoa);
																		SDL_FreeSurface(text);
																	}

																	for (int col = 0; col < NUM_COLSCT; col++) {
																		SDL_Rect cellRect = { col * CELL_WIDTHCT, 250 + i * CELL_HEIGHT - scrollY, CELL_WIDTHCT, CELL_HEIGHT };
																		SDL_RenderDrawRect(renderer, &cellRect);
																		string text;

																		if (i == 0) {
																			text = labelsTTcauThu[col];
																		}
																		else if (i != 0) {

																			text = lableTTct[col];
																		}
																		SDL_Surface* textSurfaceTable = TTF_RenderText_Solid(font3, text.c_str(), { 0, 0, 0, 255 });
																		SDL_Texture* textTextureTable = SDL_CreateTextureFromSurface(renderer, textSurfaceTable);

																		int textWidth = textSurfaceTable->w;
																		int textHeight = textSurfaceTable->h;

																		SDL_Rect textRectTable = { col * CELL_WIDTHCT + (CELL_WIDTHCT - textWidth) / 2,
																							 i * CELL_HEIGHT + 250 + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																							 textWidth ,
																							 textHeight };

																		SDL_RenderCopy(renderer, textTextureTable, NULL, &textRectTable);

																		SDL_FreeSurface(textSurfaceTable);
																		SDL_DestroyTexture(textTextureTable);
																	}
																	lableTTct[0] = dsct[k].getID();
																	lableTTct[1] = dsct[k].getFullname();
																	lableTTct[2] = dsct[k].getBirth();
																	lableTTct[3] = dsct[k].getInternational();
																	lableTTct[4] = dsct[k].getHeight();
																	lableTTct[5] = dsct[k].getWeight();
																	lableTTct[6] = dsct[k].getPosition();
																	lableTTct[7] = dsct[k].getTendoibong();
																	if (k < dsct.size() - 1) {
																		k++;
																	}
																}
															}
														}

														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);
														SDL_DestroyTexture(textTexture6);
														SDL_FreeSurface(textSurface6);
														SDL_DestroyTexture(textTexture7);
														SDL_FreeSurface(textSurface7);
														SDL_DestroyTexture(textTexture8);
														SDL_FreeSurface(textSurface8);

														SDL_RenderPresent(renderer);
													}

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													if (buttonXoa.size() > 0) {
														for (int i = 0; i < buttonXoa.size(); i++) {
															SDL_DestroyTexture(buttonXoa[i].texture);
														}
													}
													delete[] inputSuadoibong;
													delete[] _inputSuadoibong;
													delete[] lableTTDB;
													delete[] _lableTTDB;
													delete[] lableTTCT;
													delete n;
													delete buttonsBackk;
													delete buttonsBackkluu;
													luuThongTinCauThu(listPlayerCT);
													luuThongTinDoiBong(danhSachDoiBong);
													running20 = true;
													break;
												}
												case 2:
												{
													SDL_Surface* textSurface;
													SDL_Texture* textTexture;

													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;

													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;

													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;

													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;

													string inputText = " ";
													string inputText2;

													string *lableTTCT = new string[8];

													int success = 0;
													int NoSuccess = 1;

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);

													bool ispointerInputTimcauthu = false;
													Uint32 lastCursorToggleTime = 0;
													while (running15) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &inputTimcauthu.rect)) {
																	cout << "ispointer" << endl;
																	lastCursorToggleTime = mainCurentTime - 1000;
																	ispointerInputTimcauthu = true;
																	success = 0;
																	NoSuccess = 0;
																}
																else {
																	ispointerInputTimcauthu = false;
																}
																if (isPointInRect(x, y, &buttonsBack[8].rect)) {
																	running15 = false;
																}
															}

															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu) {

																if (event.key.keysym.sym == SDLK_RETURN && inputText.length() > 1) {
																	ispointerInputTimcauthu = false;
																	inputText2 = inputText;
																	inputText2.erase(0, 1);
																	if (danhSachDoiBong.size() > 0) {
																		for (auto i = danhSachDoiBong.begin(); i != danhSachDoiBong.end(); i++) {
																			if (inputText2 == i->getTenDoiBong()) {
																				danhSachDoiBong.erase(i);
																				success = 1;
																				break;
																			}
																			if (i == danhSachDoiBong.end() - 1) {
																				NoSuccess = 1;
																				cout << "khong tim thay!!!!!!!!" << endl;
																			}
																		}
																		setDataCTFromdataDb(listPlayerCT, danhSachDoiBong);
																	}
																	else {
																		NoSuccess = 1;
																	}
																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 1) {
																	inputText.pop_back();
																}
															}

															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu) {
																inputText += event.text.text;

															}
														}
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderClear(renderer);
														SDL_RenderFillRect(renderer, &inputTimcauthu.rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &inputTimcauthu.rect);

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &buttonsBack[8].rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &buttonsBack[8].rect);
														SDL_Rect textRectBack0 = { buttonsBack[8].rect.x + 10, buttonsBack[8].rect.y + 10, buttonsBack[8].rect.w - 20, buttonsBack[8].rect.h - 20 };
														SDL_RenderCopy(renderer, buttonsBack[8].texture, NULL, &textRectBack0);

														SDL_Color textColor = { 0, 0, 0, 255 };
														textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputTimcauthu.rect.x + 10, 110, textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														textSurface2 = TTF_RenderText_Solid(font, "Ten doi bong", textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { textRect.x - textSurface2->w - 40 , 110, textSurface2->w, textSurface2->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														textSurface3 = TTF_RenderText_Solid(font, "NHAP TEN DOI BONG CAN XOA", textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { (SCREEN_WIDTH / 2) - (textSurface3->w / 2) , 50, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														textSurface4 = TTF_RenderText_Solid(font, "XOA THANH CONG !!!!", {0,128,0,0});
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { (SCREEN_WIDTH / 2) - (textSurface4->w / 2) , SCREEN_HEIGHT / 2, textSurface4->w, textSurface4->h };

														textSurface5 = TTF_RenderText_Solid(font, "KHONG TIM THAY !!!!", {255,0,0,0});
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { (SCREEN_WIDTH / 2) - (textSurface5->w / 2) , SCREEN_HEIGHT / 2, textSurface5->w, textSurface5->h };

														if (success == 1) {
															SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);
														}

														if (NoSuccess == 1 && inputText2.length() > 0) {
															SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);
														}
														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}

														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu) {
															SDL_Rect cursorRect = { textSurface->w + (textRect.x), 110, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}

														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);

														SDL_RenderPresent(renderer);
													}
													luuThongTinDoiBong(danhSachDoiBong);
													luuThongTinCauThu(listPlayerCT);
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													delete[] lableTTCT;
													break;
												}
												case 3:
												{
													const int NUM_ROWS = 2;
													const int NUM_COLS = 3;
													const int NUM_COLSCT = 8;
													const int CELL_WIDTH = ((SCREEN_WIDTH) / NUM_COLS);
													const int CELL_WIDTHCT = ((SCREEN_WIDTH) / NUM_COLSCT);
													const int CELL_HEIGHT = 60;

													SDL_Surface* textSurface;
													SDL_Texture* textTexture;

													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;

													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;

													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;

													string inputText = " ";
													string inputText2;

													string *lableTTDB = new string[3];
													string *lableTTCT = new string[8];

													SDL_Rect viewport = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT - 100 };
													SDL_Rect content = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

													SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
													SDL_RenderClear(renderer); // Xóa màn hình

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer, &buttonsBack[4].rect);
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBack[4].rect);
													SDL_Rect textRectBack0 = { buttonsBack[4].rect.x + 10, buttonsBack[4].rect.y + 10, buttonsBack[4].rect.w - 20, buttonsBack[4].rect.h - 20 };
													SDL_RenderCopy(renderer, buttonsBack[4].texture, NULL, &textRectBack0);
													SDL_RenderPresent(renderer);

													int renDer = 0;
													vector<CauThu> dsct;
													int scrollY = 0;

													bool ispointerInputTimDoiBong = false;
													Uint32 lastCursorToggleTime = 0;
													while (running10) {

														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderSetViewport(renderer, &viewport);

														SDL_RenderFillRect(renderer, &content);
														Button inputTimDoiBong = { (SCREEN_WIDTH / 2) - 400 / 2 , 60 - scrollY, 400, 50 };
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEWHEEL) {
																if (event.wheel.y >= 0) {
																	if (scrollY >= 0) {
																		scrollY -= 15;
																	}
																}
																else if (event.wheel.y < 0) {
																	if (300 + ((dsct.size() + 1) * CELL_HEIGHT) > SCREEN_HEIGHT - 100) {
																		scrollY += 15;
																	}
																}
															}

															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &inputTimDoiBong.rect)) {
																	cout << "ispointer" << endl;
																	lastCursorToggleTime = mainCurentTime - 1000;
																	ispointerInputTimDoiBong = true;
																}
																else {
																	ispointerInputTimDoiBong = false;
																}
																if (isPointInRect(x, y, &buttonsBack[4].rect)) {
																	running10 = false;
																}
															}

															if (event.type == SDL_KEYDOWN && ispointerInputTimDoiBong) {

																if (event.key.keysym.sym == SDLK_RETURN && inputText.length() > 1) {
																	ispointerInputTimDoiBong = false;
																	inputText2 = inputText;
																	inputText2.erase(0, 1);
																	for (int i = 0; i < danhSachDoiBong.size(); i++) {
																		if (inputText2 == danhSachDoiBong[i].getTenDoiBong()) {
																			lableTTDB[0] = danhSachDoiBong[i].getTenDoiBong();
																			lableTTDB[1] = danhSachDoiBong[i].getDiaPhuong();
																			lableTTDB[2] = danhSachDoiBong[i].getHuanLuyenVien();
																			dsct = danhSachDoiBong[i].getdscauthu();
																			renDer = 1;
																			break;
																		}
																		if (i == danhSachDoiBong.size() - 1) {
																			renDer = 0;
																		}
																	}

																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 1) {
																	inputText.pop_back();
																}
															}

															if (event.type == SDL_TEXTINPUT && ispointerInputTimDoiBong) {
																inputText += event.text.text;

															}
														}
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &inputTimDoiBong.rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &inputTimDoiBong.rect);

														SDL_Color textColor = { 0, 0, 0, 255 };
														textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputTimDoiBong.rect.x + 10, 70 - scrollY, textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														textSurface2 = TTF_RenderText_Solid(font, "Ten doi bong", textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { textRect.x - 215, 70 - scrollY, 175, textSurface->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														textSurface3 = TTF_RenderText_Solid(font, "NHAP TEN DOI BONG CAN TIM", textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { (SCREEN_WIDTH / 2) - (textSurface3->w / 2) , 10 - scrollY, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														textSurface5 = TTF_RenderText_Solid(font, "KHONG TIM THAY !!!!", {255,0,0,0});
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { (SCREEN_WIDTH / 2) - (textSurface5->w / 2) , SCREEN_HEIGHT / 2, textSurface5->w, textSurface5->h };

														if (renDer == 0 && inputText2.length() > 0) {
															SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);
														}
														if (ispointerInputTimDoiBong) {
															SDL_Rect white = { (SCREEN_WIDTH / 2) - (textSurface5->w / 2) , SCREEN_HEIGHT / 2, 400, 150 };
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &white);
														}
														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}

														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimDoiBong) {
															SDL_Rect cursorRect = { textSurface->w + (textRect.x), 70 - scrollY, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														if (inputText2.length() > 0 && ispointerInputTimDoiBong == false && renDer == 1 && danhSachDoiBong.size() > 0) {
															int k = 0;
															string lableTTct[8];

															if (dsct.size() > 0) {
																for (int i = 0; i < dsct.size() + 1; i++) {

																	for (int col = 0; col < NUM_COLSCT; col++) {
																		SDL_Rect cellRect = { col * CELL_WIDTHCT, 300 + i * CELL_HEIGHT - scrollY, CELL_WIDTHCT, CELL_HEIGHT };
																		SDL_RenderDrawRect(renderer, &cellRect);
																		string text;

																		if (i == 0) {
																			text = labelsTTcauThu[col];
																		}
																		else if (i != 0) {

																			text = lableTTct[col];
																		}
																		SDL_Surface* textSurfaceTable = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																		SDL_Texture* textTextureTable = SDL_CreateTextureFromSurface(renderer, textSurfaceTable);

																		int textWidth = textSurfaceTable->w;
																		int textHeight = textSurfaceTable->h;

																		SDL_Rect textRectTable = { col * CELL_WIDTHCT + (CELL_WIDTHCT - textWidth) / 2,
																							 i * CELL_HEIGHT + 300 + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																							 textWidth ,
																							 textHeight };

																		SDL_RenderCopy(renderer, textTextureTable, NULL, &textRectTable);

																		SDL_FreeSurface(textSurfaceTable);
																		SDL_DestroyTexture(textTextureTable);
																	}
																	lableTTct[0] = dsct[k].getID();
																	lableTTct[1] = dsct[k].getFullname();
																	lableTTct[2] = dsct[k].getBirth();
																	lableTTct[3] = dsct[k].getInternational();
																	lableTTct[4] = dsct[k].getHeight();
																	lableTTct[5] = dsct[k].getWeight();
																	lableTTct[6] = dsct[k].getPosition();
																	lableTTct[7] = dsct[k].getTendoibong();
																	if (k < dsct.size() - 1) {
																		k++;
																	}
																}
															}

															for (int i = 0; i < NUM_ROWS; i++) {

																for (int col = 0; col < NUM_COLS; col++) {
																	SDL_Rect cellRect = { col * CELL_WIDTH, 150 + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																	SDL_RenderDrawRect(renderer, &cellRect);
																	string text;

																	if (i == 0) {
																		text = labelsTTDoiBong[col];
																	}
																	else if (i == 1) {

																		text = lableTTDB[col];
																	}

																	SDL_Surface* textSurfaceTable = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																	SDL_Texture* textTextureTable = SDL_CreateTextureFromSurface(renderer, textSurfaceTable);

																	int textWidth = textSurfaceTable->w;
																	int textHeight = textSurfaceTable->h;

																	SDL_Rect textRectTable = { col * CELL_WIDTH + (CELL_WIDTH - textWidth) / 2,
																						 i * CELL_HEIGHT + 150 + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																						 textWidth ,
																						 textHeight };

																	SDL_RenderCopy(renderer, textTextureTable, NULL, &textRectTable);

																	SDL_FreeSurface(textSurfaceTable);
																	SDL_DestroyTexture(textTextureTable);
																}
															}
														}

														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);

														SDL_RenderPresent(renderer);
													}

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													delete[] lableTTDB;
													delete[] lableTTCT;
													break;
												}
												case 4:
													running3 = false;
													break;
												}
											}
										}
									}
									SDL_RenderPresent(renderer);
								}
								running15 = true;
								running10 = true;
							}
							break;
						}
						case 0:
						{
							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đặt màu vẽ thành màu trang
							SDL_RenderClear(renderer); // Xóa màn hình
							while (running4) {
								SDL_Event event;
								int x, y;
								SDL_GetMouseState(&x, &y);
								SDL_RenderSetViewport(renderer, &viewportMainMenu);

								while (SDL_PollEvent(&event)) {
									if (event.type == SDL_QUIT) {
										return 0;
									}
									for (int i = 0; i < NUM_BUTTONS1; i++) {
										SDL_Color textColor = { 0, 0, 0, 255 };
										SDL_Surface* surface = TTF_RenderText_Solid(font, labels1[i], textColor);
										buttons1[i].texture = SDL_CreateTextureFromSurface(renderer, surface);

										SDL_Rect textRect;
										textRect.x = buttons1[i].rect.x + (BUTTON_WIDTH - surface->w) / 2;
										textRect.y = buttons1[i].rect.y + 10;
										textRect.w = surface->w;
										textRect.h = surface->h;

										if (isPointInRect(x, y, &buttons1[i].rect)) {
											SDL_SetRenderDrawColor(renderer, 225, 240, 255, 0);
										}
										else {
											SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
										}
										SDL_RenderFillRect(renderer, &buttons1[i].rect);
										SDL_RenderCopy(renderer, buttons1[i].texture, NULL, &textRect);
										SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
										SDL_RenderDrawRect(renderer, &buttons1[i].rect);
										SDL_FreeSurface(surface);
									}
									for (int i = 0; i < NUM_BUTTONS1; i++) {
										if (isPointInRect(x, y, &buttons1[i].rect)) {
											if (event.type == SDL_MOUSEBUTTONDOWN) {
												cout << "button press " << i + 1 << endl;
												switch (i) {
												case 0:
												{
													const int NUM_ROWS = 2;
													const int NUM_COLS = 8;
													const int CELL_WIDTH = ((SCREEN_WIDTH) / NUM_COLS);
													const int CELL_HEIGHT = (SCREEN_HEIGHT / 2) / (NUM_ROWS * 2);
													SDL_Surface* textSurface;
													SDL_Texture* textTexture;

													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;

													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;

													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;

													string inputText = " ";
													string inputText2;

													string *lableTTCT = new string[8];

													int renDer = 0;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													bool ispointerInputTimcauthu = false;
													Uint32 lastCursorToggleTime = 0;
													while (running6) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &inputTimcauthu.rect)) {
																	cout << "ispointer" << endl;
																	lastCursorToggleTime = mainCurentTime - 1000;
																	ispointerInputTimcauthu = true;
																}
																else {
																	ispointerInputTimcauthu = false;
																}
																if (isPointInRect(x, y, &buttonsBack[0].rect)) {
																	running6 = false;
																}
															}
															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu) {

																if (event.key.keysym.sym == SDLK_RETURN && inputText.length() > 1) {
																	ispointerInputTimcauthu = false;
																	inputText2 = inputText;
																	inputText2.erase(0, 1);
																	for (int i = 0; i < listPlayerCT.size(); i++) {
																		if (inputText2 == listPlayerCT[i].getID()) {
																			lableTTCT[0] = listPlayerCT[i].getID();
																			lableTTCT[1] = listPlayerCT[i].getFullname();
																			lableTTCT[2] = listPlayerCT[i].getBirth();
																			lableTTCT[3] = listPlayerCT[i].getInternational();
																			lableTTCT[4] = listPlayerCT[i].getHeight();
																			lableTTCT[5] = listPlayerCT[i].getWeight();
																			lableTTCT[6] = listPlayerCT[i].getPosition();
																			lableTTCT[7] = listPlayerCT[i].getTendoibong();
																			renDer = 1;
																			break;
																		}
																		if (i == danhSachDoiBong.size() - 1) {
																			renDer = 0;
																		}
																	}
																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 1) {
																	inputText.pop_back();
																}
															}
															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu) {
																inputText += event.text.text;

															}
														}
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderClear(renderer);
														SDL_RenderFillRect(renderer, &inputTimcauthu.rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &inputTimcauthu.rect);

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &buttonsBack[0].rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &buttonsBack[0].rect);
														SDL_Rect textRectBack0 = { buttonsBack[0].rect.x + 10, buttonsBack[0].rect.y + 10, buttonsBack[0].rect.w - 20, buttonsBack[0].rect.h - 20 };
														SDL_RenderCopy(renderer, buttonsBack[0].texture, NULL, &textRectBack0);

														SDL_Color textColor = { 0, 0, 0, 255 };
														textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputTimcauthu.rect.x + 10, 110, textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														textSurface2 = TTF_RenderText_Solid(font, "So CCCD", textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { textRect.x - 140, 110, 100, textSurface->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														textSurface3 = TTF_RenderText_Solid(font, "NHAP CCCD CAN TIM", textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { (SCREEN_WIDTH / 2) - (textSurface3->w / 2) , 50, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														textSurface5 = TTF_RenderText_Solid(font, "KHONG TIM THAY !!!!", {255,0,0,0});
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { (SCREEN_WIDTH / 2) - (textSurface5->w / 2) , SCREEN_HEIGHT / 2, textSurface5->w, textSurface5->h };

														if (renDer == 0 && inputText2.length()>0) {
															SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);
														}
														if (ispointerInputTimcauthu) {
															SDL_Rect white = { (SCREEN_WIDTH / 2) - (textSurface5->w / 2) , SCREEN_HEIGHT / 2, 400, 150 };
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &white);
														}

														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}

														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu) {
															SDL_Rect cursorRect = { textSurface->w + (textRect.x), 110, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														if (inputText2.length() > 0 && ispointerInputTimcauthu == false && renDer == 1 ) {

															for (int i = 0; i < NUM_ROWS; i++) {

																for (int col = 0; col < NUM_COLS; col++) {
																	SDL_Rect cellRect = { col * CELL_WIDTH, (SCREEN_HEIGHT / 2 - 50) + i * CELL_HEIGHT , CELL_WIDTH, CELL_HEIGHT };									SDL_RenderDrawRect(renderer, &cellRect);
																	SDL_RenderDrawRect(renderer, &cellRect);
																	string text;

																	if (i == 0) {
																		text = labelsTTcauThu[col];
																	}
																	else if (i == 1) {

																		text = lableTTCT[col];
																	}
																	SDL_Surface* textSurfaceTable = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																	SDL_Texture* textTextureTable = SDL_CreateTextureFromSurface(renderer, textSurfaceTable);

																	int textWidth = textSurfaceTable->w;
																	int textHeight = textSurfaceTable->h;

																	SDL_Rect textRectTable = { col * CELL_WIDTH + (CELL_WIDTH - textWidth) / 2,
																						 i * CELL_HEIGHT + (SCREEN_HEIGHT / 2 - 50) + (CELL_HEIGHT - textHeight) / 2,
																						 textWidth ,
																						 textHeight };

																	SDL_RenderCopy(renderer, textTextureTable, NULL, &textRectTable);

																	SDL_FreeSurface(textSurfaceTable);
																	SDL_DestroyTexture(textTextureTable);
																}
															}
														}

														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);

														SDL_RenderPresent(renderer);
													}
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													delete[] lableTTCT;
													break;
												}
												case 1:
												{
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);

													SDL_Surface* textSurface;
													SDL_Texture* textTexture;
													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;
													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;
													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;
													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;
													SDL_Surface* textSurface6;
													SDL_Texture* textTexture6;
													SDL_Surface* textSurface7;
													SDL_Texture* textTexture7;
													SDL_Surface* textSurface8;
													SDL_Texture* textTexture8;
													SDL_Surface* textSurface9;
													SDL_Texture* textTexture9;
													SDL_Surface* textSurface10;
													SDL_Texture* textTexture10;
													SDL_Surface* textSurface11;
													SDL_Texture* textTexture11;
													string* labelInput = new string[8];
													string* _labelInput = new string[8];
													for (int i = 0; i < 8; i++) {
														labelInput[i] = " ";
													}
													
													string inputText = " ";
													string inputText2;
													SDL_Color textColor = { 0, 0, 0, 255 };
													bool inValid = false;
													bool sussces = false;
													bool checkDB = false;
													bool clear = false;
													Uint32 lastCursorToggleTime = 0;
													int ispointerInputTimcauthu = -1;

													for (int i = 0; i < 8; i++) {
														SDL_Surface* surface = TTF_RenderText_Solid(font2, labelsTTcauThu[i], { 0,0,0,255 });
														_inputThemcauthu[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
														SDL_Rect textRect = { _inputThemcauthu[i].rect.x + 10, _inputThemcauthu[i].rect.y + 10, surface->w, surface->h };
														SDL_RenderCopy(renderer, _inputThemcauthu[i].texture, NULL, &textRect);
														SDL_FreeSurface(surface);
													}
													SDL_Surface* surfaceThem = TTF_RenderText_Solid(font, "Them", { 0,0,0,255 });
													them.texture = SDL_CreateTextureFromSurface(renderer, surfaceThem);
													SDL_Rect textRectThem = { them.rect.x + 20, them.rect.y + 10, surfaceThem->w, surfaceThem->h };
													SDL_RenderCopy(renderer, them.texture, NULL, &textRectThem);
													SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Màu do
													SDL_RenderDrawRect(renderer, &them.rect);
													SDL_FreeSurface(surfaceThem);
													SDL_RenderPresent(renderer);
													while (running16) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														for (int i = 0; i < 8; i++) {

															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &inputThemcauthu[i].rect);
															SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
															SDL_RenderDrawRect(renderer, &inputThemcauthu[i].rect);
														}
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &buttonsBack[8].rect)) {
																	running16 = false;
																}
																if (isPointInRect(x, y, &them.rect) && labelInput[0].length() > 1 && labelInput[1].length() > 1 && labelInput[2].length() > 1 && labelInput[3].length() > 1 && labelInput[4].length() > 1 && labelInput[5].length() > 1 && labelInput[6].length() > 1 && labelInput[7].length() > 1) {
																	clear = true;
																	for (int i = 0; i < 8; i++) {
																		if (labelInput[i].length() > 1) {
																			_labelInput[i] = labelInput[i];
																			_labelInput[i].erase(0, 1);
																		}
																	}
																	for (int i = 0; i < listPlayerCT.size(); i++) {
																		if (listPlayerCT[i].getID() == _labelInput[0]) {
																			cout << "-.-" << endl;
																			cout << "so can cuoc cong dan da ton tai!!" << endl;
																			inValid = true;
																			break;
																		}
																		else {
																			inValid = false;
																		}
																		if (i == listPlayerCT.size() - 1) {

																			checkDB = true;
																			CauThu t(CauThu(_labelInput[0], _labelInput[1], _labelInput[3], _labelInput[2], _labelInput[4], _labelInput[5], _labelInput[6], _labelInput[7]));
																			for (auto& db : danhSachDoiBong) {
																				if (_labelInput[7] == db.getTenDoiBong()) {

																					sussces = true;
																					checkDB = false;
																					listPlayerCT.push_back(t);
																					db.themcauthuvaodanhsach(t);

																					break;
																				}
																			}
																			break;
																		}
																	}
																	if (danhSachDoiBong.size() == 0) {
																		checkDB = true;
																	}
																}
															}
															for (int i = 0; i < 8; i++) {
																if (event.type == SDL_MOUSEBUTTONDOWN) {

																	if (isPointInRect(x, y, &inputThemcauthu[i].rect)) {
																		cout << "ispointer" << i << endl;
																		lastCursorToggleTime = mainCurentTime - 1000;
																		ispointerInputTimcauthu = i;
																		checkDB = false;
																		inValid = false;
																		sussces = false;
																	}
																	if (!isPointInRect(x, y, &inputThemcauthu[0].rect)
																		&& !isPointInRect(x, y, &inputThemcauthu[1].rect)
																		&& !isPointInRect(x, y, &inputThemcauthu[2].rect)
																		&& !isPointInRect(x, y, &inputThemcauthu[3].rect)
																		&& !isPointInRect(x, y, &inputThemcauthu[4].rect)
																		&& !isPointInRect(x, y, &inputThemcauthu[5].rect)
																		&& !isPointInRect(x, y, &inputThemcauthu[6].rect)
																		&& !isPointInRect(x, y, &inputThemcauthu[7].rect)) {
																		ispointerInputTimcauthu = -1;
																	}
																}
															}
															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu != -1) {
																if (event.key.keysym.sym == 9) {
																	if (ispointerInputTimcauthu < 7 && ispointerInputTimcauthu != -1) {
																		ispointerInputTimcauthu++;
																	}
																}

																if (event.key.keysym.sym == SDLK_BACKSPACE && labelInput[ispointerInputTimcauthu].length() > 1) {
																	labelInput[ispointerInputTimcauthu].pop_back();
																}
															}
															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu != -1) {
																inputText += event.text.text;
																labelInput[ispointerInputTimcauthu] += event.text.text;
															}

														}
														textSurface9 = TTF_RenderText_Solid(font, "Them thanh cong!!", { 0, 128, 0, 255 });
														textTexture9 = SDL_CreateTextureFromSurface(renderer, textSurface9);
														SDL_Rect textRect9 = { inputThemcauthu[0].rect.x + 10, 17, textSurface9->w, textSurface9->h };

														textSurface10 = TTF_RenderText_Solid(font, "So CCCD da ton tai!!", { 255, 0, 0, 0 });
														textTexture10 = SDL_CreateTextureFromSurface(renderer, textSurface10);
														SDL_Rect textRect10 = { inputThemcauthu[0].rect.x + 10, 17, textSurface10->w, textSurface10->h };

														textSurface11 = TTF_RenderText_Solid(font, "Doi bong khong ton tai!!", { 255, 0, 0, 0 });
														textTexture11 = SDL_CreateTextureFromSurface(renderer, textSurface11);
														SDL_Rect textRect11 = { inputThemcauthu[0].rect.x + 10, 17, textSurface11->w, textSurface11->h };
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														if (sussces) {
															SDL_RenderFillRect(renderer, &textRect9);
															SDL_RenderCopy(renderer, textTexture9, NULL, &textRect9);
															sussces = false;
														}
														if (ispointerInputTimcauthu != -1) {
															SDL_Rect white = { inputThemcauthu[0].rect.x + 10, 10, 400, 70 };
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &white);
														}

														if (checkDB) {
															SDL_RenderFillRect(renderer, &textRect11);
															SDL_RenderCopy(renderer, textTexture11, NULL, &textRect11);
															checkDB = false;
														}
														if (inValid) {
															SDL_RenderFillRect(renderer, &textRect10);
															SDL_RenderCopy(renderer, textTexture10, NULL, &textRect10);
															inValid = false;
														}
														//1
														textSurface = TTF_RenderText_Solid(font, labelInput[0].c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputThemcauthu[0].rect.x + 10, inputThemcauthu[0].rect.y + 10, textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														//2
														textSurface2 = TTF_RenderText_Solid(font, labelInput[1].c_str(), textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { inputThemcauthu[1].rect.x + 10, inputThemcauthu[1].rect.y + 10, textSurface2->w, textSurface2->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														//3
														textSurface3 = TTF_RenderText_Solid(font, labelInput[2].c_str(), textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { inputThemcauthu[2].rect.x + 10, inputThemcauthu[2].rect.y + 10, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														//4
														textSurface4 = TTF_RenderText_Solid(font, labelInput[3].c_str(), textColor);
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { inputThemcauthu[3].rect.x + 10, inputThemcauthu[3].rect.y + 10, textSurface4->w, textSurface4->h };
														SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);

														//5
														textSurface5 = TTF_RenderText_Solid(font, labelInput[4].c_str(), textColor);
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { inputThemcauthu[4].rect.x + 10, inputThemcauthu[4].rect.y + 10, textSurface5->w, textSurface5->h };
														SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);

														//6
														textSurface6 = TTF_RenderText_Solid(font, labelInput[5].c_str(), textColor);
														textTexture6 = SDL_CreateTextureFromSurface(renderer, textSurface6);
														SDL_Rect textRect6 = { inputThemcauthu[5].rect.x + 10, inputThemcauthu[5].rect.y + 10, textSurface6->w, textSurface6->h };
														SDL_RenderCopy(renderer, textTexture6, NULL, &textRect6);

														//7
														textSurface7 = TTF_RenderText_Solid(font, labelInput[6].c_str(), textColor);
														textTexture7 = SDL_CreateTextureFromSurface(renderer, textSurface7);
														SDL_Rect textRect7 = { inputThemcauthu[6].rect.x + 10, inputThemcauthu[6].rect.y + 10, textSurface7->w, textSurface7->h };
														SDL_RenderCopy(renderer, textTexture7, NULL, &textRect7);

														//8
														textSurface8 = TTF_RenderText_Solid(font, labelInput[7].c_str(), textColor);
														textTexture8 = SDL_CreateTextureFromSurface(renderer, textSurface8);
														SDL_Rect textRect8 = { inputThemcauthu[7].rect.x + 10, inputThemcauthu[7].rect.y + 10, textSurface8->w, textSurface8->h };
														SDL_RenderCopy(renderer, textTexture8, NULL, &textRect8);

														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}
														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu != -1) {
															SDL_Rect cursorRect = { inputThemcauthu[ispointerInputTimcauthu].rect.x + ((labelInput[ispointerInputTimcauthu].length() + 0.7) * (70 / 5)), inputThemcauthu[ispointerInputTimcauthu].rect.y + 10, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &buttonsBack[8].rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &buttonsBack[8].rect);
														SDL_Rect textRectBack0 = { buttonsBack[8].rect.x + 10, buttonsBack[8].rect.y + 10, buttonsBack[8].rect.w - 20, buttonsBack[8].rect.h - 20 };
														SDL_RenderCopy(renderer, buttonsBack[8].texture, NULL, &textRectBack0);
														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);
														SDL_DestroyTexture(textTexture6);
														SDL_FreeSurface(textSurface6);
														SDL_DestroyTexture(textTexture7);
														SDL_FreeSurface(textSurface7);
														SDL_DestroyTexture(textTexture8);
														SDL_FreeSurface(textSurface8);
														SDL_DestroyTexture(textTexture9);
														SDL_FreeSurface(textSurface9);
														SDL_DestroyTexture(textTexture10);
														SDL_FreeSurface(textSurface10);
														SDL_DestroyTexture(textTexture11);
														SDL_FreeSurface(textSurface11);

														SDL_RenderPresent(renderer);
													}
													luuThongTinCauThu(listPlayerCT);
													luuThongTinDoiBong(danhSachDoiBong);
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													delete[] labelInput;
													delete[] _labelInput;
													running16 = true;
													break;
												}
												case 2:
												{
													SDL_Surface* TextSurface;
													SDL_Texture* TextTexture;
													/*SDL_Surface* TextSurface2;
													SDL_Texture* TextTexture2;*/
													SDL_Surface* TextSurface3;
													SDL_Texture* TextTexture3;
													SDL_Surface* TextSurface4;
													SDL_Texture* TextTexture4;
													SDL_Surface* TextSurface5;
													SDL_Texture* TextTexture5;
													SDL_Surface* TextSurface6;
													SDL_Texture* TextTexture6;
													SDL_Surface* TextSurface7;
													SDL_Texture* TextTexture7;

													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;

													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;

													SDL_Surface* textSurface6;
													SDL_Texture* textTexture6;

													SDL_Surface* textSurface7;
													SDL_Texture* textTexture7;

													SDL_Surface* textSurface8;
													SDL_Texture* textTexture8;

													SDL_Surface* textSurface9;
													SDL_Texture* textTexture9;

													SDL_Surface* textSurface10;
													SDL_Texture* textTexture10;

													SDL_Surface* textSurface11;
													SDL_Texture* textTexture11;
													SDL_Color textColor = { 0, 0, 0, 255 };
													string inputText = " ";
													string inputText2;
													string* labelInput = new string[9];
													string* _labelInput = new string[9];

													for (int i = 0; i < 9; i++) {
														labelInput[i] = " ";
													}

													int success = 0;
													int NoSuccess = -1;
													int checkct = 0;
													int checkdb = 0;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													int ispointerInputTimcauthu = -1;
													int n = 1;
													int *posit = new int;
													Uint32 lastCursorToggleTime = 0;

													TextSurface3 = TTF_RenderText_Solid(font, "NHAP CCCD CAN SUA", textColor);
													TextTexture3 = SDL_CreateTextureFromSurface(renderer, TextSurface3);
													SDL_Rect TextRect3 = { (SCREEN_WIDTH / 2) - (TextSurface3->w / 2) , 5, TextSurface3->w, TextSurface3->h };
													SDL_RenderCopy(renderer, TextTexture3, NULL, &TextRect3);
													for (int i = 1; i < 9; i++) {
														SDL_Surface* surface = TTF_RenderText_Solid(font2, labelsTTcauThu[i - 1], { 0,0,0,255 });
														_inputSuacauthu[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
														SDL_Rect textRect = { _inputSuacauthu[i].rect.x + 10, _inputSuacauthu[i].rect.y + 10, surface->w, surface->h };
														SDL_RenderCopy(renderer, _inputSuacauthu[i].texture, NULL, &textRect);
														SDL_FreeSurface(surface);
													}
													SDL_Surface* surfaceThem = TTF_RenderText_Solid(font, "-Luu-", { 0,0,255,0 });
													luuvaodanhsach.texture = SDL_CreateTextureFromSurface(renderer, surfaceThem);
													SDL_Rect textRectThem = { SCREEN_WIDTH/2 - 35, luuvaodanhsach.rect.y + 10, surfaceThem->w, surfaceThem->h };
													SDL_RenderCopy(renderer, luuvaodanhsach.texture, NULL, &textRectThem);
													SDL_SetRenderDrawColor(renderer,  0,0,255,0 ); // Màu do
													SDL_RenderDrawRect(renderer, &luuvaodanhsach.rect);
													SDL_FreeSurface(surfaceThem);
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer, &buttonsBack[7].rect);
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBack[7].rect);
													SDL_Rect textRectBack0 = { buttonsBack[7].rect.x + 10, buttonsBack[7].rect.y + 10, buttonsBack[7].rect.w - 20, buttonsBack[7].rect.h - 20 };
													SDL_RenderCopy(renderer, buttonsBack[7].texture, NULL, &textRectBack0);
													SDL_RenderPresent(renderer);
													while (running19) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														for (int i = 0; i < 9; i++) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &inputSuacauthu[i].rect);
															SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
															SDL_RenderDrawRect(renderer, &inputSuacauthu[i].rect);
														}
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &buttonsBack[7].rect)) {
																	running19 = false;
																}
																if (isPointInRect(x, y, &luuvaodanhsach.rect)
																	&& labelInput[0].length()>1
																	&& labelInput[1].length() > 1
																	&& labelInput[2].length() > 1
																	&& labelInput[3].length() > 1
																	&& labelInput[4].length() > 1
																	&& labelInput[5].length() > 1
																	&& labelInput[6].length() > 1
																	&& labelInput[7].length() > 1
																	&& labelInput[8].length() > 1) {
																	ispointerInputTimcauthu = -1;
																	for (int i = 1; i < 9; i++) {
																		_labelInput[i] = labelInput[i];
																		_labelInput[i].erase(0, 1);
																	}
																	for (int i = 0; i < listPlayerCT.size(); i++) {
																		if (i != *posit) {
																			if (listPlayerCT[i].getID() == _labelInput[1]) {
																				cout << "da ton tai" << endl;
																				checkct = 1;
																				break;
																			}
																		}
																		else {
																			listPlayerCT[*posit].getPlayer();
																		}
																		if (i == listPlayerCT.size() - 1) {
																			checkct = 0;
																			CauThu t(CauThu(_labelInput[1], _labelInput[2], _labelInput[4], _labelInput[3], _labelInput[5], _labelInput[6], _labelInput[7], _labelInput[8]));
																			for (int j = 0; j < danhSachDoiBong.size(); j++) {
																				if (_labelInput[8] == danhSachDoiBong[j].getTenDoiBong()) {
																					checkdb = 0;
																					break;
																				}
																				if(j == danhSachDoiBong.size()-1) {
																					checkdb = 1;
																				}
																			}
																			for (auto& db : danhSachDoiBong) {
																				if (_labelInput[8] == db.getTenDoiBong()) {

																					success = 1;
																					//checkDB = false;*/
																					listPlayerCT[*posit] = t;
																					db.suadanhsachcauthu(t, _labelInput[0]);
																					break;
																				}
																			
																			}
																		}
																	}
																}
																for (int i = 0; i < n; i++) {
																	if (isPointInRect(x, y, &inputSuacauthu[i].rect)) {
																		cout << "ispointer" << endl;
																		lastCursorToggleTime = mainCurentTime - 1000;
																		ispointerInputTimcauthu = i;
																		success = 0;
																		NoSuccess = 0;
																	}
																}
															}
															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu != -1) {
																if (ispointerInputTimcauthu < 8 && ispointerInputTimcauthu >= 1) {
																	ispointerInputTimcauthu++;
																}

																if (event.key.keysym.sym == SDLK_RETURN && labelInput[0].length() > 1) {
																	for (int i = 1; i < 9; i++) {
																		labelInput[i] = " ";
																	}
																	_labelInput[0] = labelInput[0];
																	_labelInput[0].erase(0, 1);
																	for (int i = 0; i < listPlayerCT.size(); i++) {
																		if (_labelInput[0] == listPlayerCT[i].getID()) {
																			n = 9;
																			ispointerInputTimcauthu = 1;
																			*posit = i;
																			labelInput[1] += listPlayerCT[i].getID();
																			labelInput[2] += listPlayerCT[i].getFullname();
																			labelInput[3] += listPlayerCT[i].getBirth();
																			labelInput[4] += listPlayerCT[i].getInternational();
																			labelInput[5] += listPlayerCT[i].getHeight();
																			labelInput[6] += listPlayerCT[i].getWeight();
																			labelInput[7] += listPlayerCT[i].getPosition();
																			labelInput[8] += listPlayerCT[i].getTendoibong();
																			NoSuccess = 0;
																			break;
																		}
																		if (i == listPlayerCT.size()-1) {
																			NoSuccess = 1;
																			ispointerInputTimcauthu = 0;
																			cout << "khong tim thay!!!!!!!!" << endl;
																		}
																	}
																	if (listPlayerCT.size() == 0) {
																		NoSuccess = 1;
																	}
																	/*luuThongTinDoiBong(danhSachDoiBong);
																	luuThongTinCauThu(listPlayerCT);*/

																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && ispointerInputTimcauthu != -1 && labelInput[ispointerInputTimcauthu].length() > 1) {
																	inputText.pop_back();
																	labelInput[ispointerInputTimcauthu].pop_back();
																}
															}
															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu != -1) {
																inputText += event.text.text;
																labelInput[ispointerInputTimcauthu] += event.text.text;
															}
														}
														/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderClear(renderer);*/
														TextSurface = TTF_RenderText_Solid(font, labelInput[0].c_str(), textColor);
														TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
														SDL_Rect TextRect = { inputSuacauthu[0].rect.x + 10, inputSuacauthu[0].rect.y + 10, TextSurface->w, TextSurface->h};
														SDL_RenderCopy(renderer, TextTexture, NULL, &TextRect);

														/*TextSurface2 = TTF_RenderText_Solid(font, "So CCCD", textColor);
														TextTexture2 = SDL_CreateTextureFromSurface(renderer, TextSurface2);
														SDL_Rect TextRect2 = { TextRect.x - 140, 110, 40, TextSurface->h };
														SDL_RenderCopy(renderer, TextTexture2, NULL, &TextRect2);*/

														TextSurface4 = TTF_RenderText_Solid(font, "LUU THANH CONG !!!!", {0, 128, 0 ,0});
														TextTexture4 = SDL_CreateTextureFromSurface(renderer, TextSurface4);
														SDL_Rect TextRect4 = { (SCREEN_WIDTH / 2) - (TextSurface4->w / 2) , inputSuacauthu[0].rect.y + 58, TextSurface4->w, TextSurface4->h };

														TextSurface5 = TTF_RenderText_Solid(font, "KHONG TIM THAY !!!!", { 255, 0, 0, 0 });
														TextTexture5 = SDL_CreateTextureFromSurface(renderer, TextSurface5);
														SDL_Rect TextRect5 = { (SCREEN_WIDTH / 2) - (TextSurface5->w / 2) , inputSuacauthu[0].rect.y + 58, TextSurface5->w, TextSurface5->h};

														TextSurface6 = TTF_RenderText_Solid(font2, "So CCCD da ton tai !!!!", { 255, 0, 0, 0 });
														TextTexture6 = SDL_CreateTextureFromSurface(renderer, TextSurface6);
														SDL_Rect TextRect6 = { inputSuacauthu[1].rect.x + 20 , inputSuacauthu[1].rect.y + 53, TextSurface6->w, TextSurface6->h };

														TextSurface7 = TTF_RenderText_Solid(font2, "Doi bong khong ton tai !!!!", { 255, 0, 0, 0 });
														TextTexture7 = SDL_CreateTextureFromSurface(renderer, TextSurface7);
														SDL_Rect TextRect7 = { inputSuacauthu[8].rect.x + 20 , inputSuacauthu[8].rect.y + 53, TextSurface7->w, TextSurface7->h };

														//4
														textSurface4 = TTF_RenderText_Solid(font, labelInput[1].c_str(), textColor);
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { inputSuacauthu[1].rect.x + 10, inputSuacauthu[1].rect.y + 10, textSurface4->w, textSurface4->h };
														SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);

														//5
														textSurface5 = TTF_RenderText_Solid(font, labelInput[2].c_str(), textColor);
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { inputSuacauthu[2].rect.x + 10, inputSuacauthu[2].rect.y + 10, textSurface5->w, textSurface5->h };
														SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);

														//6
														textSurface6 = TTF_RenderText_Solid(font, labelInput[3].c_str(), textColor);
														textTexture6 = SDL_CreateTextureFromSurface(renderer, textSurface6);
														SDL_Rect textRect6 = { inputSuacauthu[3].rect.x + 10, inputSuacauthu[3].rect.y + 10, textSurface6->w, textSurface6->h };
														SDL_RenderCopy(renderer, textTexture6, NULL, &textRect6);

														//7
														textSurface7 = TTF_RenderText_Solid(font, labelInput[4].c_str(), textColor);
														textTexture7 = SDL_CreateTextureFromSurface(renderer, textSurface7);
														SDL_Rect textRect7 = { inputSuacauthu[4].rect.x + 10, inputSuacauthu[4].rect.y + 10, textSurface7->w, textSurface7->h };
														SDL_RenderCopy(renderer, textTexture7, NULL, &textRect7);

														//8
														textSurface8 = TTF_RenderText_Solid(font, labelInput[5].c_str(), textColor);
														textTexture8 = SDL_CreateTextureFromSurface(renderer, textSurface8);
														SDL_Rect textRect8 = { inputSuacauthu[5].rect.x + 10, inputSuacauthu[5].rect.y + 10, textSurface8->w, textSurface8->h };
														SDL_RenderCopy(renderer, textTexture8, NULL, &textRect8);
														//9
														textSurface9 = TTF_RenderText_Solid(font, labelInput[6].c_str(), textColor);
														textTexture9 = SDL_CreateTextureFromSurface(renderer, textSurface9);
														SDL_Rect textRect9 = { inputSuacauthu[6].rect.x + 10, inputSuacauthu[6].rect.y + 10, textSurface9->w, textSurface9->h };
														SDL_RenderCopy(renderer, textTexture9, NULL, &textRect9);
														//10
														textSurface10 = TTF_RenderText_Solid(font, labelInput[7].c_str(), textColor);
														textTexture10 = SDL_CreateTextureFromSurface(renderer, textSurface10);
														SDL_Rect textRect10 = { inputSuacauthu[7].rect.x + 10, inputSuacauthu[7].rect.y + 10, textSurface10->w, textSurface10->h };
														SDL_RenderCopy(renderer, textTexture10, NULL, &textRect10);

														textSurface11 = TTF_RenderText_Solid(font, labelInput[8].c_str(), textColor);
														textTexture11 = SDL_CreateTextureFromSurface(renderer, textSurface11);
														SDL_Rect textRect11 = { inputSuacauthu[8].rect.x + 10, inputSuacauthu[8].rect.y + 10, textSurface11->w, textSurface11->h };
														SDL_RenderCopy(renderer, textTexture11, NULL, &textRect11);

														if (success == 1) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white = { inputSuacauthu[0].rect.x , inputSuacauthu[0].rect.y + 58, 400, 50 };
															SDL_RenderFillRect(renderer, &white);
															SDL_RenderCopy(renderer, TextTexture4, NULL, &TextRect4);
															SDL_Rect white2 = { inputSuacauthu[1].rect.x , inputSuacauthu[1].rect.y + 53, 400, 35 };
															SDL_RenderFillRect(renderer, &white2);
															SDL_Rect white3 = { inputSuacauthu[8].rect.x , inputSuacauthu[8].rect.y + 53, 400, 35 };
															SDL_RenderFillRect(renderer, &white3);
														}
														if (checkct) {
															SDL_RenderCopy(renderer, TextTexture6, NULL, &TextRect6);
															checkct = 0;
														}
														if (checkdb) {
															SDL_RenderCopy(renderer, TextTexture7, NULL, &TextRect7);
															checkdb = 0;
														}
														if (NoSuccess == 1) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white = { inputSuacauthu[0].rect.x , inputSuacauthu[0].rect.y + 58, 400, 50 };
															SDL_RenderFillRect(renderer, &white);
															SDL_RenderCopy(renderer, TextTexture5, NULL, &TextRect5);
															SDL_Rect white2 = { inputSuacauthu[1].rect.x , inputSuacauthu[1].rect.y + 53, 400, 35 };
															SDL_RenderFillRect(renderer, &white2);
															SDL_Rect white3 = { inputSuacauthu[8].rect.x , inputSuacauthu[8].rect.y + 53, 400, 35 };
															SDL_RenderFillRect(renderer, &white3);
														}
														if (NoSuccess == 0 && success == 0) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white = { inputSuacauthu[0].rect.x , inputSuacauthu[0].rect.y + 58, 400, 50 };
															SDL_RenderFillRect(renderer, &white);

														}
														/*if (success == 0) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white = { inputSuacauthu[0].rect.x , inputSuacauthu[0].rect.y + 58, 400, 50 };
															SDL_RenderFillRect(renderer, &white);

														}*/
														if (ispointerInputTimcauthu == 1) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white = { inputSuacauthu[1].rect.x , inputSuacauthu[1].rect.y + 53, 400, 35 };
															SDL_RenderFillRect(renderer, &white);
														}
														if (ispointerInputTimcauthu == 8) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_Rect white = { inputSuacauthu[8].rect.x , inputSuacauthu[8].rect.y + 53, 400, 35 };
															SDL_RenderFillRect(renderer, &white);
														}
														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}
														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu != -1) {
															// Vẽ con trỏ văn bản
															SDL_Rect cursorRect = { inputSuacauthu[ispointerInputTimcauthu].rect.x + ((labelInput[ispointerInputTimcauthu].length() + 0.7) * (70 / 5)), inputSuacauthu[ispointerInputTimcauthu].rect.y + 10, 2, TextSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}
														SDL_DestroyTexture(TextTexture);
														SDL_FreeSurface(TextSurface);
														/*SDL_DestroyTexture(TextTexture2);
														SDL_FreeSurface(TextSurface2);*/
														
														SDL_DestroyTexture(TextTexture4);
														SDL_FreeSurface(TextSurface4);
														SDL_DestroyTexture(TextTexture5);
														SDL_FreeSurface(TextSurface5);
														SDL_DestroyTexture(TextTexture6);
														SDL_FreeSurface(TextSurface6);
														SDL_DestroyTexture(TextTexture7);
														SDL_FreeSurface(TextSurface7);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);
														SDL_DestroyTexture(textTexture6);
														SDL_FreeSurface(textSurface6);
														SDL_DestroyTexture(textTexture7);
														SDL_FreeSurface(textSurface7);
														SDL_DestroyTexture(textTexture8);
														SDL_FreeSurface(textSurface8);
														SDL_DestroyTexture(textTexture9);
														SDL_FreeSurface(textSurface9);
														SDL_DestroyTexture(textTexture10);
														SDL_FreeSurface(textSurface10);
														SDL_DestroyTexture(textTexture11);
														SDL_FreeSurface(textSurface11);

														SDL_RenderPresent(renderer);
													}
													luuThongTinCauThu(listPlayerCT);
													luuThongTinDoiBong(danhSachDoiBong);
													SDL_DestroyTexture(TextTexture3);
													SDL_FreeSurface(TextSurface3);
													SDL_DestroyTexture(luuvaodanhsach.texture);
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													delete[] labelInput;
													delete[] _labelInput;
													delete posit;
													running19 = true;
													break;
												}
												case 3:
												{
													SDL_Surface* textSurface;
													SDL_Texture* textTexture;
													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;
													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;
													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;
													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;
													string inputText = " ";
													string inputText2;
													string *lableTTCT = new string[8];
													int success = 0;
													int NoSuccess = 0;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													bool ispointerInputTimcauthu = false;
													Uint32 lastCursorToggleTime = 0;
													while (running14) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &inputTimcauthu.rect)) {
																	cout << "ispointer" << endl;
																	lastCursorToggleTime = mainCurentTime - 1000;
																	ispointerInputTimcauthu = true;
																	success = 0;
																	NoSuccess = 0;
																}
																else {
																	ispointerInputTimcauthu = false;
																}
																if (isPointInRect(x, y, &buttonsBack[7].rect)) {
																	running14 = false;
																}
															}
															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu) {

																if (event.key.keysym.sym == SDLK_RETURN && inputText.length() > 1) {
																	ispointerInputTimcauthu = false;
																	inputText2 = inputText;
																	inputText2.erase(0, 1);
																	for (auto i = listPlayerCT.begin(); i != listPlayerCT.end(); i++) {
																		if (inputText2 == i->getID()) {
																			for (auto& db : danhSachDoiBong) {
																				if (db.getTenDoiBong() == i->getTendoibong()) {
																					db.xoacauthukhoids(inputText2);
																				}
																			}
																			listPlayerCT.erase(i);
																			cout << "Xoa thanh cong !" << endl;
																			success = 1;
																			break;
																		}
																		if (i == listPlayerCT.end() - 1) {
																			NoSuccess = 1;
																			cout << "khong tim thay!!!!!!!!" << endl;
																		}
																	}
																	if (listPlayerCT.size() == 0) {
																		NoSuccess = 1;
																	}
																	luuThongTinDoiBong(danhSachDoiBong);
																	luuThongTinCauThu(listPlayerCT);

																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 1) {
																	inputText.pop_back();
																}
															}
															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu) {
																inputText += event.text.text;

															}
														}
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderClear(renderer);
														SDL_RenderFillRect(renderer, &inputTimcauthu.rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &inputTimcauthu.rect);

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &buttonsBack[7].rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &buttonsBack[7].rect);
														SDL_Rect textRectBack0 = { buttonsBack[7].rect.x + 10, buttonsBack[7].rect.y + 10, buttonsBack[7].rect.w - 20, buttonsBack[7].rect.h - 20 };
														SDL_RenderCopy(renderer, buttonsBack[7].texture, NULL, &textRectBack0);

														SDL_Color textColor = { 0, 0, 0, 255 };
														textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputTimcauthu.rect.x + 10, 110, textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														textSurface2 = TTF_RenderText_Solid(font, "So CCCD", textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { textRect.x - 140, 110, 100, textSurface->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														textSurface3 = TTF_RenderText_Solid(font, "NHAP CCCD CAN XOA", textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { (SCREEN_WIDTH / 2) - (textSurface3->w / 2) , 50, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														textSurface4 = TTF_RenderText_Solid(font, "XOA THANH CONG !!!!", { 0, 128, 0, 255 });
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { (SCREEN_WIDTH / 2) - (textSurface4->w / 2) , SCREEN_HEIGHT / 2, textSurface4->w, textSurface4->h };

														textSurface5 = TTF_RenderText_Solid(font, "KHONG TIM THAY !!!!", {255,0,0,0});
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { (SCREEN_WIDTH / 2) - (textSurface5->w / 2) , SCREEN_HEIGHT / 2, textSurface5->w, textSurface5->h };

														if (success == 1) {
															SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);
														}
														if (NoSuccess == 1) {
															SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);
														}
														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}
														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu) {
															// Vẽ con trỏ văn bản
															SDL_Rect cursorRect = { textSurface->w + (textRect.x), 110, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}
														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);

														SDL_RenderPresent(renderer);
													}
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													delete[] lableTTCT;
													break;
												}
												case 4:
												{
													int count = 0;
													int countMin = 0;
													string year;
													vector<CauThu> CT;
													if (listPlayerCT.size() > 0) {
														CauThu min = listPlayerCT[0];
													
														for (int i = 1; i < listPlayerCT.size(); i++) {
															int count1 = 0;
															int count2 = 0;
															for (int j = 0; j < listPlayerCT[i].getBirth().length(); j++) {
																if (min.getBirth()[j] == '/') count2++;
																if (count2 == 2) {
																	count2 = j + 1;
																}
																if (listPlayerCT[i].getBirth()[j] == '/') count1++;
																if (count1 == 2) {
																	count1 = j + 1;
																}
															}
															if (stoi(min.getBirth().substr(count2)) < stoi(listPlayerCT[i].getBirth().substr(count1))) {
																min = listPlayerCT[i];
															}
														}
														//cout << listPlayerCT[min].getBirth();
														for (int j = 0; j < min.getBirth().length(); j++) {
															if (min.getBirth()[j] == '/') countMin++;
															if (countMin == 2) {
																countMin = j + 1;
															}
														}
														cout << min.getBirth().substr(countMin) << endl;
														for (int i = 0; i < listPlayerCT.size(); i++) {
															int Count = 0;
															for (int j = 0; j < listPlayerCT[i].getBirth().length(); j++) {
																if (listPlayerCT[i].getBirth()[j] == '/') {
																	Count++;
																}
																if (Count == 2) {
																	Count = j + 1;
																}
															}
															if (stoi(listPlayerCT[i].getBirth().substr(Count)) == stoi(min.getBirth().substr(countMin))) {
																CT.push_back(listPlayerCT[i]);
																count++;
															}
														}
													}
													SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
													SDL_RenderClear(renderer); // Xóa màn hình
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													const int NUM_ROWS = count + 1;
													const int NUM_COLS = 8;
													const int CELL_WIDTH = ((SCREEN_WIDTH - 15) / NUM_COLS);
													const int CELL_HEIGHT = (SCREEN_HEIGHT - 150) / 4;

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer, &buttonsBack[1].rect);
													SDL_Surface* surface = TTF_RenderText_Solid(font, "Quay lai", { 0,0,0,255 });
													buttonsBack[1].texture = SDL_CreateTextureFromSurface(renderer, surface);

													SDL_Rect textRect;
													textRect.x = buttonsBack[1].rect.x + (buttonsBack[1].rect.w - surface->w) / 2; // Thêm một lề 10 pixel
													textRect.y = buttonsBack[1].rect.y + 10;
													textRect.w = surface->w; // Sử dụng chiều rộng và chiều cao của surface
													textRect.h = surface->h;
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBack[1].rect);
													SDL_RenderCopy(renderer, buttonsBack[1].texture, NULL, &textRect);
													SDL_FreeSurface(surface);
													SDL_Rect viewport = { 0, 0, SCREEN_WIDTH - 9.9, SCREEN_HEIGHT - 100 };
													SDL_Rect content = { 10, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
													int scrollY = 0;
													while (running7) {
														int x, y;
														SDL_GetMouseState(&x, &y);
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEWHEEL) {
																if (event.wheel.y >= 0) {
																	if (scrollY >= 0) {
																		scrollY -= 15;
																	}
																}
																else if (event.wheel.y < 0) {
																	if ((count + 1) * CELL_HEIGHT > viewport.h) {
																		scrollY += 15;
																	}
																}
															}
															if (isPointInRect(x, y, &buttonsBack[1].rect)) {
																if (event.type == SDL_MOUSEBUTTONDOWN) {
																	running7 = false;
																	cout << "is back " << endl;
																}
															}
														}
														SDL_RenderSetViewport(renderer, &viewport);

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &content);

														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam

														for (int i = 0; i < 1; i++) {

															for (int col = 0; col < NUM_COLS; col++) {
																SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																SDL_RenderDrawRect(renderer, &cellRect);
																string text;
																if (i == 0) {
																	text = labelsTTcauThu[col];
																}
																
																SDL_Surface* textSurface = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

																int textWidth = textSurface->w;
																int textHeight = textSurface->h;

																SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
																					 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																					 textWidth,
																					 textHeight };

																SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
																SDL_FreeSurface(textSurface);
																SDL_DestroyTexture(textTexture);
															}
														}

														if (CT.size() > 0) {
															for (int i = 1; i < CT.size() + 1; i++) {

																for (int col = 0; col < NUM_COLS; col++) {
																	SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																	SDL_RenderDrawRect(renderer, &cellRect);
																	string text;
																	if (i == 0) {
																		text = labelsTTcauThu[col];
																	}
																	else {
																		string lableTTCT[8] = { CT[i - 1].getID(), CT[i - 1].getFullname(), CT[i - 1].getBirth(), CT[i - 1].getInternational(), CT[i - 1].getHeight(), CT[i - 1].getWeight(), CT[i - 1].getPosition(), CT[i - 1].getTendoibong() };
																		text = lableTTCT[col];

																	}
																	SDL_Surface* textSurface = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

																	int textWidth = textSurface->w;
																	int textHeight = textSurface->h;

																	SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
																						 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																						 textWidth,
																						 textHeight };

																	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
																	SDL_FreeSurface(textSurface);
																	SDL_DestroyTexture(textTexture);
																}
															}
														}
														SDL_RenderPresent(renderer);
													}
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													break;
												}
												case 5:
												{
													int count = 0;
													vector<CauThu> CT;
													if (listPlayerCT.size() > 0) {
														CauThu max = listPlayerCT[0];
														for (int i = 1; i < listPlayerCT.size(); i++) {

															if (stoi(max.getHeight()) < stoi(listPlayerCT[i].getHeight())) {
																max = listPlayerCT[i];
															}
														}
														for (int i = 0; i < listPlayerCT.size(); i++) {
															if (stof(listPlayerCT[i].getHeight()) == stof(max.getHeight())) {

																CT.push_back(listPlayerCT[i]);
																count++;
															}
														}
													}
													SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
													SDL_RenderClear(renderer); // Xóa màn hình
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													const int NUM_ROWS = count + 1;
													const int NUM_COLS = 8;
													const int CELL_WIDTH = ((SCREEN_WIDTH - 15) / NUM_COLS);
													const int CELL_HEIGHT = (SCREEN_HEIGHT - 150) / 4;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer, &buttonsBack[2].rect);
													SDL_Surface* surface = TTF_RenderText_Solid(font, "Quay lai", { 0,0,0,255 });
													buttonsBack[2].texture = SDL_CreateTextureFromSurface(renderer, surface);
													SDL_Rect textRect;
													textRect.x = buttonsBack[2].rect.x + (buttonsBack[2].rect.w - surface->w) / 2; // Thêm một lề 10 pixel
													textRect.y = buttonsBack[2].rect.y + 10;
													textRect.w = surface->w; // Sử dụng chiều rộng và chiều cao của surface
													textRect.h = surface->h;
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBack[2].rect);
													SDL_RenderCopy(renderer, buttonsBack[2].texture, NULL, &textRect);
													SDL_FreeSurface(surface);
													SDL_Rect viewport = { 0, 0, SCREEN_WIDTH - 9.9, SCREEN_HEIGHT - 100 };
													SDL_Rect content = { 10, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
													int scrollY = 0;
													while (running8) {
														int x, y;
														SDL_GetMouseState(&x, &y);
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEWHEEL) {
																if (event.wheel.y >= 0) {
																	if (scrollY >= 0) {
																		scrollY -= 15;
																	}
																}
																else if (event.wheel.y < 0) {
																	if ((count + 1) * CELL_HEIGHT > viewport.h) {
																		scrollY += 15;
																	}
																}
															}
															if (isPointInRect(x, y, &buttonsBack[2].rect)) {
																if (event.type == SDL_MOUSEBUTTONDOWN) {
																	running8 = false;
																	cout << "is back " << endl;
																}
															}
														}
														SDL_RenderSetViewport(renderer, &viewport);
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &content);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam

														for (int i = 0; i < 1; i++) {
															for (int col = 0; col < NUM_COLS; col++) {
																SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																SDL_RenderDrawRect(renderer, &cellRect);
																string text;
																if (i == 0) {
																	text = labelsTTcauThu[col];
																}
																
																SDL_Surface* textSurface = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

																int textWidth = textSurface->w;
																int textHeight = textSurface->h;

																SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
																					 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																					 textWidth,
																					 textHeight };

																SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
																SDL_FreeSurface(textSurface);
																SDL_DestroyTexture(textTexture);
															}
														}

														if (CT.size() > 0) {
															for (int i = 0; i < CT.size() + 1; i++) {
																for (int col = 0; col < NUM_COLS; col++) {
																	SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																	SDL_RenderDrawRect(renderer, &cellRect);
																	string text;
																	if (i == 0) {
																		text = labelsTTcauThu[col];
																	}
																	else {
																		string lableTTCT[8] = { CT[i - 1].getID(), CT[i - 1].getFullname(), CT[i - 1].getBirth(), CT[i - 1].getInternational(), CT[i - 1].getHeight(), CT[i - 1].getWeight(), CT[i - 1].getPosition(), CT[i - 1].getTendoibong() };
																		text = lableTTCT[col];

																	}
																	SDL_Surface* textSurface = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

																	int textWidth = textSurface->w;
																	int textHeight = textSurface->h;

																	SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
																						 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																						 textWidth,
																						 textHeight };

																	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
																	SDL_FreeSurface(textSurface);
																	SDL_DestroyTexture(textTexture);
																}
															}
														}
														SDL_RenderPresent(renderer);

													}
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													break;
												}
												case 6:
												{
													int count = 0;
													vector<CauThu> CT;
													if (listPlayerCT.size() > 0) {
														CauThu max = listPlayerCT[0];
														for (int i = 1; i < listPlayerCT.size(); i++) {
															if (stoi(max.getHeight()) > stoi(listPlayerCT[i].getHeight())) {
																max = listPlayerCT[i];
															}
														}
														for (int i = 0; i < listPlayerCT.size(); i++) {
															if (stof(listPlayerCT[i].getHeight()) == stof(max.getHeight())) {

																CT.push_back(listPlayerCT[i]);
																count++;
															}
														}
													}
													cout << count;
													SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
													SDL_RenderClear(renderer); // Xóa màn hình
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													const int NUM_ROWS = count + 1;
													const int NUM_COLS = 8;
													const int CELL_WIDTH = ((SCREEN_WIDTH - 15) / NUM_COLS);
													const int CELL_HEIGHT = (SCREEN_HEIGHT - 150) / 4;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer, &buttonsBack[3].rect);
													SDL_Surface* surface = TTF_RenderText_Solid(font, "Quay lai", { 0,0,0,255 });
													buttonsBack[3].texture = SDL_CreateTextureFromSurface(renderer, surface);
													SDL_Rect textRect;
													textRect.x = buttonsBack[3].rect.x + (buttonsBack[3].rect.w - surface->w) / 2; // Thêm một lề 10 pixel
													textRect.y = buttonsBack[3].rect.y + 10;
													textRect.w = surface->w; // Sử dụng chiều rộng và chiều cao của surface
													textRect.h = surface->h;
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBack[3].rect);
													SDL_RenderCopy(renderer, buttonsBack[3].texture, NULL, &textRect);
													SDL_FreeSurface(surface);
													SDL_Rect viewport = { 0, 0, SCREEN_WIDTH - 9.9, SCREEN_HEIGHT - 100 };
													SDL_Rect content = { 10, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
													int scrollX = 0;
													int scrollY = 0;
													while (running9) {
														int x, y;
														SDL_GetMouseState(&x, &y);
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEWHEEL) {
																if (event.wheel.y >= 0) {
																	if (scrollY >= 0) {
																		scrollY -= 15;
																	}
																}
																else if (event.wheel.y < 0) {
																	if ((count + 1) * CELL_HEIGHT > viewport.h) {
																		scrollY += 15;
																	}
																}
															}
															if (isPointInRect(x, y, &buttonsBack[3].rect)) {
																if (event.type == SDL_MOUSEBUTTONDOWN) {
																	running9 = false;
																	cout << "is back " << endl;
																}
															}
														}
														SDL_RenderSetViewport(renderer, &viewport);
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &content);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														for (int i = 0; i < 1; i++) {
															for (int col = 0; col < NUM_COLS; col++) {
																SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																SDL_RenderDrawRect(renderer, &cellRect);
																string text;
																if (i == 0) {
																	text = labelsTTcauThu[col];
																}
																SDL_Surface* textSurface = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
																int textWidth = textSurface->w;
																int textHeight = textSurface->h;
																SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
																					 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																					 textWidth,
																					 textHeight };

																SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
																SDL_FreeSurface(textSurface);
																SDL_DestroyTexture(textTexture);
															}
														}

														if (CT.size() > 0) {
															for (int i = 0; i < CT.size() + 1; i++) {
																for (int col = 0; col < NUM_COLS; col++) {
																	SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																	SDL_RenderDrawRect(renderer, &cellRect);
																	string text;
																	if (i == 0) {
																		text = labelsTTcauThu[col];
																	}
																	else {
																		string lableTTCT[8] = { CT[i - 1].getID(), CT[i - 1].getFullname(), CT[i - 1].getBirth(), CT[i - 1].getInternational(), CT[i - 1].getHeight(), CT[i - 1].getWeight(), CT[i - 1].getPosition(), CT[i - 1].getTendoibong() };
																		text = lableTTCT[col];
																	}
																	SDL_Surface* textSurface = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
																	int textWidth = textSurface->w;
																	int textHeight = textSurface->h;
																	SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
																						 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																						 textWidth,
																						 textHeight };

																	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
																	SDL_FreeSurface(textSurface);
																	SDL_DestroyTexture(textTexture);
																}
															}
														}
														SDL_RenderPresent(renderer);
													}
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													break;
												}
												case 7:
												{
													running4 = false;
													break;
												}
												}
											}
										}
									}
									SDL_RenderPresent(renderer);
								}
								running6 = true;
								running7 = true;
								running8 = true;
								running9 = true;
								running14 = true;
							}
							break;
						}
						case 2:
						{
							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
							SDL_RenderClear(renderer); 
							while (running5) {
								SDL_Event event;
								int x, y;
								SDL_GetMouseState(&x, &y);
								SDL_RenderSetViewport(renderer, &viewportMainMenu);

								while (SDL_PollEvent(&event)) {
									if (event.type == SDL_QUIT) {
										return 0;
									}
									for (int i = 0; i < NUM_BUTTONS2; i++) {
										SDL_Color textColor = { 0, 0, 0, 255 }; 
										SDL_Surface* surface = TTF_RenderText_Solid(font, labels2[i], textColor);
										buttons2[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
										SDL_Rect textRect;
										textRect.x = buttons2[i].rect.x + (BUTTON_WIDTH - surface->w) / 2; 
										textRect.y = buttons2[i].rect.y + 10;
										textRect.w = surface->w; 
										textRect.h = surface->h;
										if (isPointInRect(x, y, &buttons2[i].rect)) {
											SDL_SetRenderDrawColor(renderer, 225, 240, 255, 0);
										}
										else {
											SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
										}
										SDL_RenderFillRect(renderer, &buttons2[i].rect);
										SDL_RenderCopy(renderer, buttons2[i].texture, NULL, &textRect);
										SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);  
										SDL_RenderDrawRect(renderer, &buttons2[i].rect);
										SDL_FreeSurface(surface);
									}
									for (int i = 0; i < NUM_BUTTONS2; i++) {
										if (isPointInRect(x, y, &buttons2[i].rect)) {
											//cout << "is hover" << endl;
											if (event.type == SDL_MOUSEBUTTONDOWN) {
												cout << "button press " << i + 1 << endl;
												switch (i) {
												case 0:
												{
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);

													SDL_Surface* textSurface;
													SDL_Texture* textTexture;
													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;
													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;
													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;
													SDL_Surface* textSurface5;
													SDL_Texture* textTexture5;
													SDL_Surface* textSurface6;
													SDL_Texture* textTexture6;
													SDL_Surface* textSurface7;
													SDL_Texture* textTexture7;
													SDL_Surface* textSurface8;
													SDL_Texture* textTexture8;
													
													string* labelInput = new string[5];
													string* _labelInput = new string[5];
													for (int i = 0; i < 5; i++) {
														labelInput[i] = " ";
													}
													string inputText = " ";
													string inputText2;
													SDL_Color textColor = { 0, 0, 0, 255 };
													bool sussces = false;
													bool sussces2 = false;
													bool sussces3 = false;
													bool checkDB2 = false;
													bool checkDB3 = false;
													bool clear = false;
													Uint32 lastCursorToggleTime = 0;
													int ispointerInputTimcauthu = -1;
													string day, month, year;

													for (int i = 0; i < 5; i++) {
														SDL_Surface* surface = TTF_RenderText_Solid(font2, labelsTTTD[i], { 0,0,0,255 });
														_inputThemtrandau[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
														SDL_Rect textRect = { _inputThemtrandau[i].rect.x + 10, _inputThemtrandau[i].rect.y + 10, surface->w, surface->h };
														SDL_RenderCopy(renderer, _inputThemtrandau[i].texture, NULL, &textRect);
														SDL_FreeSurface(surface);
													}
													SDL_Surface* surfaceThem = TTF_RenderText_Solid(font, "Them tran dau", { 0,0,0,255 });
													themtrandau.texture = SDL_CreateTextureFromSurface(renderer, surfaceThem);
													SDL_Rect textRectThem = { themtrandau.rect.x + 20, themtrandau.rect.y + 10, surfaceThem->w, surfaceThem->h };
													SDL_RenderCopy(renderer, themtrandau.texture, NULL, &textRectThem);
													SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Màu do
													SDL_RenderDrawRect(renderer, &themtrandau.rect);
													SDL_FreeSurface(surfaceThem);
													SDL_RenderPresent(renderer);
													while (running18) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														for (int i = 0; i < 5; i++) {

															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &inputThemtrandau[i].rect);
															SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
															SDL_RenderDrawRect(renderer, &inputThemtrandau[i].rect);
														}
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &buttonsBack[8].rect)) {
																	running18 = false;
																}
																if (isPointInRect(x, y, &themtrandau.rect)
																	&& labelInput[0].length() >= 5
																	&& labelInput[1].length() > 1
																	&& labelInput[2].length() > 1
																	&& labelInput[3].length() > 1
																	&& labelInput[4].length() > 1
																	) {
																	clear = true;
																	for (int i = 0; i < 5; i++) {
																		_labelInput[i] = labelInput[i];
																		_labelInput[i].erase(0, 1);
																	}
																	cout << _labelInput[0].length() << endl;
																	int count = 0;
																	for (int i = 0; i < _labelInput[0].length(); i++) {
																		if (labelInput[0][i] == '/') {
																			++count;
																		}
																		if (count == 0) {
																			day += _labelInput[0][i];
																		}
																		else if (count == 1) {
																			month += _labelInput[0][i];
																		}
																		else if (count == 2) {
																			year += _labelInput[0][i];
																		}
																	}
																	for (int i = 0; i < danhSachDoiBong.size(); i++) {
																		if (danhSachDoiBong[i].getTenDoiBong() == _labelInput[2]) {
																			sussces2 = true;
																			break;
																		}
																		if (i == danhSachDoiBong.size() - 1) {
																			cout << "==";
																			checkDB2 = true;
																		}
																	}
																	for (int i = 0; i < danhSachDoiBong.size(); i++) {
																		if (danhSachDoiBong[i].getTenDoiBong() == _labelInput[3]) {
																			sussces3 = true;
																			break;
																		}
																		if (i == danhSachDoiBong.size() - 1) {
																			cout << "==";
																			checkDB3 = true;
																		}
																	}
																	if (sussces2 && sussces3) {
																		sussces = true;
																		danhsachtrandau.push_back(TranDau(stoi(day.erase(day.length() - 1)), stoi(month.erase(day.length() - 1)), stoi(year), _labelInput[1], _labelInput[2], _labelInput[3], _labelInput[4]));
																	}
																}
															}
															for (int i = 0; i < 5; i++) {
																if (event.type == SDL_MOUSEBUTTONDOWN) {

																	if (isPointInRect(x, y, &inputThemtrandau[i].rect)) {
																		cout << "ispointer" << i << endl;
																		lastCursorToggleTime = mainCurentTime - 1000;
																		ispointerInputTimcauthu = i;
																		sussces = false;
																	}
																	if (!isPointInRect(x, y, &inputThemtrandau[0].rect)
																		&& !isPointInRect(x, y, &inputThemtrandau[1].rect)
																		&& !isPointInRect(x, y, &inputThemtrandau[2].rect)
																		&& !isPointInRect(x, y, &inputThemtrandau[3].rect)
																		&& !isPointInRect(x, y, &inputThemtrandau[4].rect)
																		) {
																		ispointerInputTimcauthu = -1;
																	}
																}
															}

															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu != -1) {

																if (event.key.keysym.sym == 9) {
																	if (ispointerInputTimcauthu < 4 && ispointerInputTimcauthu != -1) {
																		ispointerInputTimcauthu++;
																	}
																}

																if (event.key.keysym.sym == SDLK_BACKSPACE && labelInput[ispointerInputTimcauthu].length() > 1) {
																	labelInput[ispointerInputTimcauthu].pop_back();
																}
															}
															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu != -1) {
																inputText += event.text.text;
																labelInput[ispointerInputTimcauthu] += event.text.text;
															}

														}
														textSurface6 = TTF_RenderText_Solid(font, "Them thanh tran dau thanh cong!!", { 0, 128, 0, 255 });
														textTexture6 = SDL_CreateTextureFromSurface(renderer, textSurface6);
														SDL_Rect textRect6 = { inputThemtrandau[0].rect.x + 10, 60, textSurface6->w, textSurface6->h };

														textSurface7 = TTF_RenderText_Solid(font2, "Doi bong khong ton tai!!", { 255, 0, 0, 0 });
														textTexture7 = SDL_CreateTextureFromSurface(renderer, textSurface7);
														SDL_Rect textRect7 = { inputThemtrandau[2].rect.x + 10, inputThemtrandau[2].rect.y + 52, textSurface7->w, textSurface7->h };

														textSurface8 = TTF_RenderText_Solid(font2, "Doi bong khong ton tai!!", { 255, 0, 0, 0 });
														textTexture8 = SDL_CreateTextureFromSurface(renderer, textSurface8);
														SDL_Rect textRect8 = { inputThemtrandau[3].rect.x + 10, inputThemtrandau[3].rect.y + 52, textSurface8->w, textSurface8->h };

														
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														if (sussces) {
															SDL_RenderFillRect(renderer, &textRect6);
															SDL_RenderCopy(renderer, textTexture6, NULL, &textRect6);
															SDL_Rect white2 = { inputThemtrandau[2].rect.x + 10, inputThemtrandau[2].rect.y + 52, 400, 25 };
															SDL_RenderFillRect(renderer, &white2);
															SDL_Rect white3 = { inputThemtrandau[3].rect.x + 10, inputThemtrandau[3].rect.y + 52, 400, 25 };
															SDL_RenderFillRect(renderer, &white3);
															sussces = false;
														}
														if (checkDB2) {
															SDL_RenderFillRect(renderer, &textRect7);
															SDL_RenderCopy(renderer, textTexture7, NULL, &textRect7);
															SDL_Rect white = { inputThemtrandau[0].rect.x + 10, 60, 500, 70 };
															SDL_RenderFillRect(renderer, &white);
															checkDB2 = false;
														}
														if (checkDB3) {
															SDL_RenderFillRect(renderer, &textRect8);
															SDL_RenderCopy(renderer, textTexture8, NULL, &textRect8);
															checkDB3 = false; 
															SDL_Rect white = { inputThemtrandau[0].rect.x + 10, 60, 500, 70 };
															SDL_RenderFillRect(renderer, &white);
														}
														if (ispointerInputTimcauthu != -1) {
															SDL_Rect white = { inputThemtrandau[0].rect.x + 10, 60, 500, 70 };
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &white);
														}
														if (ispointerInputTimcauthu == 2) {
															SDL_Rect white2 = { inputThemtrandau[2].rect.x + 10, inputThemtrandau[2].rect.y + 52, 400, 25 };
															SDL_RenderFillRect(renderer, &white2);
															checkDB2 = false;
														}
														if (ispointerInputTimcauthu == 3) {
															SDL_Rect white3 = { inputThemtrandau[3].rect.x + 10, inputThemtrandau[3].rect.y + 52, 400, 25 };
															SDL_RenderFillRect(renderer, &white3);
															checkDB3 = false;
														}
														//1
														textSurface = TTF_RenderText_Solid(font, labelInput[0].c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputThemtrandau[0].rect.x + 10, inputThemtrandau[0].rect.y + 10, textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														//2
														textSurface2 = TTF_RenderText_Solid(font, labelInput[1].c_str(), textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { inputThemtrandau[1].rect.x + 10, inputThemtrandau[1].rect.y + 10, textSurface2->w, textSurface2->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														//3
														textSurface3 = TTF_RenderText_Solid(font, labelInput[2].c_str(), textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { inputThemtrandau[2].rect.x + 10, inputThemtrandau[2].rect.y + 10, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														//4
														textSurface4 = TTF_RenderText_Solid(font, labelInput[3].c_str(), textColor);
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { inputThemtrandau[3].rect.x + 10, inputThemtrandau[3].rect.y + 10, textSurface4->w, textSurface4->h };
														SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);

														//5
														textSurface5 = TTF_RenderText_Solid(font, labelInput[4].c_str(), textColor);
														textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
														SDL_Rect textRect5 = { inputThemtrandau[4].rect.x + 10, inputThemtrandau[4].rect.y + 10, textSurface5->w, textSurface5->h };
														SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);

														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}
														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu != -1) {
															SDL_Rect cursorRect = { inputThemtrandau[ispointerInputTimcauthu].rect.x + ((labelInput[ispointerInputTimcauthu].length() + 0.7) * (70 / 5)), inputThemtrandau[ispointerInputTimcauthu].rect.y + 10, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &buttonsBack[8].rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &buttonsBack[8].rect);
														SDL_Rect textRectBack0 = { buttonsBack[8].rect.x + 10, buttonsBack[8].rect.y + 10, buttonsBack[8].rect.w - 20, buttonsBack[8].rect.h - 20 };
														SDL_RenderCopy(renderer, buttonsBack[8].texture, NULL, &textRectBack0);
														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_DestroyTexture(textTexture5);
														SDL_FreeSurface(textSurface5);
														SDL_DestroyTexture(textTexture6);
														SDL_FreeSurface(textSurface6);
														SDL_DestroyTexture(textTexture7);
														SDL_FreeSurface(textSurface7);
														SDL_DestroyTexture(textTexture8);
														SDL_FreeSurface(textSurface8);

														SDL_RenderPresent(renderer);
													}
													luuThongTintrandau(danhsachtrandau);
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													delete[] labelInput;
													delete[] _labelInput;
													running18 = true;
													break;
												}
												case 1:
												{
													int NUM_ROWS, count;
													const int NUM_COLS = 5;
													const int CELL_WIDTH = ((SCREEN_WIDTH) / NUM_COLS);
													const int CELL_HEIGHT = 80;
													SDL_Surface* textSurface;
													SDL_Texture* textTexture;
													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;
													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;
													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;
													string inputText = " ";
													string inputText2;
													SDL_Rect viewport = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT - 100 };
													SDL_Rect content = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
													vector<TranDau> TD;
													int renDer = 1;
													int kotimthay = 0;
													SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
													SDL_RenderClear(renderer); // Xóa màn hình
													int scrollY = 0;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer, &buttonsBack[5].rect);
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBack[5].rect);
													SDL_Rect textRectBack0 = { buttonsBack[5].rect.x + 10, buttonsBack[5].rect.y + 10, buttonsBack[5].rect.w - 20, buttonsBack[5].rect.h - 20 };
													SDL_RenderCopy(renderer, buttonsBack[5].texture, NULL, &textRectBack0);
													SDL_RenderPresent(renderer);

													bool ispointerInputTimcauthu = false;
													Uint32 lastCursorToggleTime = 0;
													while (running12) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderSetViewport(renderer, &viewport);
														SDL_RenderFillRect(renderer, &content);
														Button inputTimTDtheongay = { (SCREEN_WIDTH / 2) - 400 / 2 , 60 - scrollY, 400, 50 };
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &inputTimTDtheongay.rect)) {
																	cout << "ispointer" << endl;
																	lastCursorToggleTime = mainCurentTime - 1000;
																	ispointerInputTimcauthu = true;
																	TD.clear();
																}
																else {
																	ispointerInputTimcauthu = false;
																}
																if (isPointInRect(x, y, &buttonsBack[5].rect)) {
																	running12 = false;
																}
															}
															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu) {

																if (event.key.keysym.sym == SDLK_RETURN && inputText.length() > 1) {
																	ispointerInputTimcauthu = false;
																	inputText2 = inputText;
																	inputText2.erase(0, 1);

																	for (int i = 0; i < danhsachtrandau.size(); i++) {

																		if (inputText2 == to_string(danhsachtrandau[i].getNgaythidau())) {
																			TD.push_back(danhsachtrandau[i]);
																		}
																	}
																	if (TD.size() > 0) {
																		renDer = 1;
																	}
																	else {
																		kotimthay = 1;
																		renDer = 0;
																	}
																	NUM_ROWS = TD.size() + 1;
																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 1) {
																	inputText.pop_back();
																}
															}
															if (event.type == SDL_MOUSEWHEEL) {
																if (event.wheel.y >= 0) {
																	if (scrollY >= 0) {
																		scrollY -= 15;
																	}
																}
																else if (event.wheel.y < 0) {
																	if (150 + ((TD.size() + 1) * CELL_HEIGHT) > SCREEN_HEIGHT - 100) {
																		scrollY += 15;
																	}
																}
															}
															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu) {
																inputText += event.text.text;

															}
														}
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &inputTimTDtheongay.rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); 
														SDL_RenderDrawRect(renderer, &inputTimTDtheongay.rect);
														SDL_Color textColor = { 0, 0, 0, 255 };
														textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputTimTDtheongay.rect.x + 10, 70 - scrollY , textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														textSurface2 = TTF_RenderText_Solid(font, "Ngay thi dau", textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { textRect.x - textSurface2->w - 50, 70 - scrollY, textSurface2->w, textSurface2->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														textSurface3 = TTF_RenderText_Solid(font, "NHAP NGAY THI DAU CAN TIM", textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { (SCREEN_WIDTH / 2) - (textSurface3->w / 2) ,10 - scrollY , textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														textSurface4 = TTF_RenderText_Solid(font, "KHONG TIM THAY!!!", { 255,0,0,0 });
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { SCREEN_WIDTH / 2 - textSurface4->w / 2, SCREEN_HEIGHT / 2 - textSurface4->h / 2, textSurface4->w, textSurface4->h };

														if (kotimthay == 1) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &textRect4);
															SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);
														}

														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}
														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu) {
															SDL_Rect cursorRect = { textSurface->w + (textRect.x), 70 - scrollY , 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); 
														if (inputText2.length() > 0 && ispointerInputTimcauthu == false && renDer) {
															int k = 0;
															string lableTTtd[5];
															for (int i = 0; i < NUM_ROWS; i++) {

																for (int col = 0; col < NUM_COLS; col++) {
																	SDL_Rect cellRect = { col * CELL_WIDTH, 150 + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																	SDL_RenderDrawRect(renderer, &cellRect);
																	string text;
																	if (i == 0) {
																		text = labelsTTTD[col];
																	}
																	else {
																		text = lableTTtd[col];
																	}
																	SDL_Surface* textSurfaceTable = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																	SDL_Texture* textTextureTable = SDL_CreateTextureFromSurface(renderer, textSurfaceTable);
																	int textWidth = textSurfaceTable->w;
																	int textHeight = textSurfaceTable->h;

																	SDL_Rect textRectTable = { col * CELL_WIDTH + (CELL_WIDTH - textWidth) / 2,
																						 i * CELL_HEIGHT + 150 + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																						 textWidth ,
																						 textHeight };
																	SDL_RenderCopy(renderer, textTextureTable, NULL, &textRectTable);
																	SDL_FreeSurface(textSurfaceTable);
																	SDL_DestroyTexture(textTextureTable);
																}
																lableTTtd[0] = to_string(TD[k].getNgaythidau()) + "/" + to_string(TD[k].getThangthidau()) + "/" + to_string(TD[k].getNamthidau());
																lableTTtd[1] = TD[k].getSandau();
																lableTTtd[2] = TD[k].getTeam1();
																lableTTtd[3] = TD[k].getTeam2();
																lableTTtd[4] = TD[k].getTyso();
																if (k < NUM_ROWS - 2) {
																	k++;
																}
															}
														}
														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_RenderPresent(renderer);
													}

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													running12 = true;
													break;
												}
												case 2:
												{
													int NUM_ROWS, count;
													const int NUM_COLS = 5;
													const int CELL_WIDTH = ((SCREEN_WIDTH) / NUM_COLS);
													const int CELL_HEIGHT = 80;
													SDL_Surface* textSurface;
													SDL_Texture* textTexture;
													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;
													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;
													SDL_Surface* textSurface4;
													SDL_Texture* textTexture4;
													string inputText = " ";
													string inputText2;
													SDL_Rect viewport = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT - 100 };
													SDL_Rect content = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
													vector<TranDau> TD;
													int renDer = 1;
													int kotimthay = 0;
													SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
													SDL_RenderClear(renderer); 
													int scrollY = 0;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer, &buttonsBack[6].rect);
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonsBack[6].rect);
													SDL_Rect textRectBack0 = { buttonsBack[6].rect.x + 10, buttonsBack[6].rect.y + 10, buttonsBack[6].rect.w - 20, buttonsBack[6].rect.h - 20 };
													SDL_RenderCopy(renderer, buttonsBack[6].texture, NULL, &textRectBack0);
													SDL_RenderPresent(renderer);
													bool ispointerInputTimcauthu = false;
													Uint32 lastCursorToggleTime = 0;
													while (running13) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderSetViewport(renderer, &viewport);
														SDL_RenderFillRect(renderer, &content);
														Button inputTimTDtheongay = { (SCREEN_WIDTH / 2) - 400 / 2 , 60 - scrollY, 400, 50 };
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &inputTimTDtheongay.rect)) {
																	cout << "ispointer" << endl;
																	lastCursorToggleTime = mainCurentTime - 1000;
																	ispointerInputTimcauthu = true;
																	TD.clear();
																}
																else {
																	ispointerInputTimcauthu = false;
																}
																if (isPointInRect(x, y, &buttonsBack[6].rect)) {
																	running13 = false;
																}
															}
															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu) {

																if (event.key.keysym.sym == SDLK_RETURN && inputText.length() > 1) {
																	ispointerInputTimcauthu = false;
																	inputText2 = inputText;
																	inputText2.erase(0, 1);
																	for (int i = 0; i < danhsachtrandau.size(); i++) {

																		if (inputText2 == to_string(danhsachtrandau[i].getThangthidau())) {
																			TD.push_back(danhsachtrandau[i]);
																		}
																	}
																	if (TD.size() > 0) {
																		renDer = 1;
																	}
																	if(TD.size() == 0) {
																		kotimthay = 1;
																		renDer = 0;
																	}
																	NUM_ROWS = TD.size() + 1;
																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 1) {
																	inputText.pop_back();
																}
															}
															if (event.type == SDL_MOUSEWHEEL) {
																if (event.wheel.y >= 0) {
																	if (scrollY >= 0) {
																		scrollY -= 15;
																	}
																}
																else if (event.wheel.y < 0) {
																	if (150 + ((TD.size() + 1) * CELL_HEIGHT) > SCREEN_HEIGHT - 100) {
																		scrollY += 15;
																	}
																}
															}
															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu) {
																inputText += event.text.text;

															}
														}
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &inputTimTDtheongay.rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &inputTimTDtheongay.rect);
														SDL_Color textColor = { 0, 0, 0, 255 };
														textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputTimTDtheongay.rect.x + 10, 70 - scrollY , textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														textSurface2 = TTF_RenderText_Solid(font, "Thang thi dau", textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { textRect.x - textSurface2->w - 50, 70 - scrollY, textSurface2->w, textSurface2->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														textSurface3 = TTF_RenderText_Solid(font, "NHAP THANG THI DAU CAN TIM", textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { (SCREEN_WIDTH / 2) - (textSurface3->w / 2) ,10 - scrollY , textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

														textSurface4 = TTF_RenderText_Solid(font, "KHONG TIM THAY!!!", {255,0,0,0});
														textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
														SDL_Rect textRect4 = { SCREEN_WIDTH/2 - textSurface4->w/2, SCREEN_HEIGHT / 2 - textSurface4->h / 2, textSurface4->w, textSurface4->h };

														if (kotimthay == 1) {
															SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
															SDL_RenderFillRect(renderer, &textRect4);
															SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);
														}

														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}
														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu) {
															SDL_Rect cursorRect = { textSurface->w + (textRect.x), 70 - scrollY , 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														if (inputText2.length() > 0 && ispointerInputTimcauthu == false && renDer) {
															int k = 0;
															string lableTTtd[5];
															for (int i = 0; i < NUM_ROWS; i++) {
																for (int col = 0; col < NUM_COLS; col++) {
																	SDL_Rect cellRect = { col * CELL_WIDTH, 150 + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																	SDL_RenderDrawRect(renderer, &cellRect);
																	string text;
																	if (i == 0) {
																		text = labelsTTTD[col];
																	}
																	else {
																		text = lableTTtd[col];
																	}
																	SDL_Surface* textSurfaceTable = TTF_RenderText_Solid(font2, text.c_str(), { 0, 0, 0, 255 });
																	SDL_Texture* textTextureTable = SDL_CreateTextureFromSurface(renderer, textSurfaceTable);
																	int textWidth = textSurfaceTable->w;
																	int textHeight = textSurfaceTable->h;
																	SDL_Rect textRectTable = { col * CELL_WIDTH + (CELL_WIDTH - textWidth) / 2,
																						 i * CELL_HEIGHT + 150 + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																						 textWidth ,
																						 textHeight };
																	SDL_RenderCopy(renderer, textTextureTable, NULL, &textRectTable);

																	SDL_FreeSurface(textSurfaceTable);
																	SDL_DestroyTexture(textTextureTable);
																}
																lableTTtd[0] = to_string(TD[k].getNgaythidau()) + "/" + to_string(TD[k].getThangthidau()) + "/" + to_string(TD[k].getNamthidau());
																lableTTtd[1] = TD[k].getSandau();
																lableTTtd[2] = TD[k].getTeam1();
																lableTTtd[3] = TD[k].getTeam2();
																lableTTtd[4] = TD[k].getTyso();
																if (k < NUM_ROWS - 2) {
																	k++;
																}
															}
														}
														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);
														SDL_DestroyTexture(textTexture4);
														SDL_FreeSurface(textSurface4);
														SDL_RenderPresent(renderer);
													}
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													running13 = true;
													break;
												}
												case 3:
												{
													SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
													SDL_RenderClear(renderer); 
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); 
													const int NUM_ROWS = danhsachtrandau.size();
													const int NUM_COLS = 5;
													const int CELL_WIDTH = ((SCREEN_WIDTH - 19.9) / NUM_COLS)-10;
													const int CELL_HEIGHT = 80;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer, &buttonback.rect);
													SDL_Surface* surface = TTF_RenderText_Solid(font, "Quay lai", { 0,0,0,255 });
													buttonback.texture = SDL_CreateTextureFromSurface(renderer, surface);
													SDL_Rect textRect;
													textRect.x = buttonback.rect.x + (buttonback.rect.w - surface->w) / 2; 
													textRect.y = buttonback.rect.y + 10;
													textRect.w = surface->w; 
													textRect.h = surface->h;
													SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
													SDL_RenderDrawRect(renderer, &buttonback.rect);
													SDL_RenderCopy(renderer, buttonback.texture, NULL, &textRect);
													SDL_FreeSurface(surface);
													SDL_Rect viewport = { 0, 0, SCREEN_WIDTH - 9.9, SCREEN_HEIGHT - 100 };
													SDL_Rect content = { 10, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
													vector<Button> buttonXoa;
													for (int i = 0; i < danhsachtrandau.size(); i++) {
														Button* t = new Button;
														t->rect = { SCREEN_WIDTH - 55, 150 + i * CELL_HEIGHT + 10 , 40, 40 };
														buttonXoa.push_back(*t);
														delete t;
													}
													int scrollX = 0;
													int scrollY = 0;
													while (running11) {
														int x, y;
														SDL_GetMouseState(&x, &y);
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEWHEEL) {
																if (event.wheel.y >= 0) {
																	if (scrollY >= 0) {
																		scrollY -= 15;
																	}
																}
																else if (event.wheel.y < 0) {
																	if ((danhsachtrandau.size() + 1) * CELL_HEIGHT > SCREEN_HEIGHT) {
																		scrollY += 15;
																	}
																}
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &buttonback.rect)) {
																	running11 = false;
																	cout << "is back " << endl;
																}
																for (int i = 0; i < buttonXoa.size(); i++) {
																	if (isPointInRect(x, y, &buttonXoa[i].rect)) {
																		if (danhsachtrandau.size() > 0) {
																			danhsachtrandau.erase(danhsachtrandau.begin() + static_cast<vector<int>::size_type>(i));
																			buttonXoa.erase(buttonXoa.begin() + static_cast<vector<int>::size_type>(i));
																		}
																	}
																}
															}
															

														}
														SDL_RenderSetViewport(renderer, &viewport);
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &content);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); 
														for (int i = 0; i < NUM_COLS; i++) {
															SDL_Rect cellRect = { content.x + i * CELL_WIDTH, content.y + 0 * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
															SDL_RenderDrawRect(renderer, &cellRect);
															string text = labelsTTTD[i];
															SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });
															SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
															int textWidth = textSurface->w;
															int textHeight = textSurface->h;
															SDL_Rect textRect = { i * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
																					 0 * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																					 textWidth,
																					 textHeight };

															SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

															SDL_FreeSurface(textSurface);
															SDL_DestroyTexture(textTexture);
														}

														for (int i = 1; i < danhsachtrandau.size() + 1; i++) {
															buttonXoa[i - 1].rect.y = 90 + (i-1)*CELL_HEIGHT + 13 - scrollY;
																SDL_Surface* text = TTF_RenderText_Solid(font3, "xoa", { 255, 0, 0, 0 });
																buttonXoa[i - 1].texture = SDL_CreateTextureFromSurface(renderer, text);
																SDL_Rect textRectXoa = { buttonXoa[i - 1].rect.x + 5, buttonXoa[i - 1].rect.y + 8, text->w, text->h };
																SDL_RenderDrawRect(renderer, &buttonXoa[i - 1].rect);
																SDL_RenderCopy(renderer, buttonXoa[i - 1].texture, NULL, &textRectXoa);
																SDL_FreeSurface(text);
															
															string lableTD[5] = { to_string(danhsachtrandau[i - 1].getNgaythidau()) + "/" + to_string(danhsachtrandau[i - 1].getThangthidau()) + "/" + to_string(danhsachtrandau[i - 1].getNamthidau()), danhsachtrandau[i - 1].getSandau(), danhsachtrandau[i - 1].getTeam1(), danhsachtrandau[i - 1].getTeam2(), danhsachtrandau[i - 1].getTyso() };
															for (int col = 0; col < NUM_COLS; col++) {
																SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };
																SDL_RenderDrawRect(renderer, &cellRect);
																string text = lableTD[col];
																SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });
																SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
																int textWidth = textSurface->w;
																int textHeight = textSurface->h;
																SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
																					 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
																					 textWidth,
																					 textHeight };

																SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

																SDL_FreeSurface(textSurface);
																SDL_DestroyTexture(textTexture);
															}
														}
														SDL_RenderPresent(renderer);
													}
													if (buttonXoa.size() > 0) {
														for (int i = 0; i < buttonXoa.size(); i++) {
															SDL_DestroyTexture(buttonXoa[i].texture);
														}
													}
													running11 = true;
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
													SDL_RenderClear(renderer); 
													luuThongTintrandau(danhsachtrandau);
													break;
												}
												case 4:
												{
													running5 = false;
													break;
												}
												}
											}
										}
									}
									SDL_RenderPresent(renderer);
								}
							}
							break;
						}
						case 3:
						{
							struct dsdb {
								string ten;
								int diem;
							};
							vector<dsdb> _danhsachdoibong;
							for (auto& db : danhSachDoiBong) {
								dsdb t;
								t.ten = db.getTenDoiBong();
								t.diem = 0;
								_danhsachdoibong.push_back(t);
							}
							for (auto& td : danhsachtrandau) {
								int t1, t2;
								t1 = stoi(td.getTyso().substr(0));
								t2 = stoi(td.getTyso().substr(2));
								if (t1 > t2) {
									for (auto& db : _danhsachdoibong) {
										if (td.getTeam1() == db.ten) {
											db.diem += 3;
										}
									}
								}
								else if (t1 < t2) {
									for (auto& db : _danhsachdoibong) {
										if (td.getTeam2() == db.ten) {
											db.diem += 3;
										}
									}
								}
								else {
									for (auto& db : _danhsachdoibong) {
										if (td.getTeam1() == db.ten) {
											db.diem += 1;
										}
									}
									for (auto& db : _danhsachdoibong) {
										if (td.getTeam2() == db.ten) {
											db.diem += 1;
										}
									}
								}
							}
							SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
							SDL_RenderClear(renderer); 
							SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
							const int NUM_ROWS = _danhsachdoibong.size();
							const int NUM_COLS = 2;
							const int CELL_WIDTH = ((SCREEN_WIDTH) / NUM_COLS) - 10;
							const int CELL_HEIGHT = 80;

							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
							SDL_RenderFillRect(renderer, &buttonback.rect);
							SDL_Surface* surface = TTF_RenderText_Solid(font, "Quay lai", { 0,0,0,255 });
							buttonback.texture = SDL_CreateTextureFromSurface(renderer, surface);
							SDL_Rect textRect;
							textRect.x = buttonback.rect.x + (buttonback.rect.w - surface->w) / 2; 
							textRect.y = buttonback.rect.y + 10;
							textRect.w = surface->w; 
							textRect.h = surface->h;
							SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
							SDL_RenderDrawRect(renderer, &buttonback.rect);
							SDL_RenderCopy(renderer, buttonback.texture, NULL, &textRect);
							SDL_FreeSurface(surface);
							SDL_Rect viewport = { 0, 0, SCREEN_WIDTH - 9.9, SCREEN_HEIGHT - 100 };
							SDL_Rect content = { 10, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
							int scrollX = 0;
							int scrollY = 0;
							while (running2) {
								int x, y;
								SDL_GetMouseState(&x, &y);
								while (SDL_PollEvent(&event)) {
									if (event.type == SDL_QUIT) {
										return 0;
									}
									if (event.type == SDL_MOUSEWHEEL) {
										if (event.wheel.y >= 0) {
											if (scrollY >= 0) {
												scrollY -= 15;
											}
										}
										else if (event.wheel.y < 0) {
											if ((_danhsachdoibong.size() + 1) * CELL_HEIGHT > SCREEN_HEIGHT) {
												scrollY += 15;
											}
										}
									}
									if (isPointInRect(x, y, &buttonback.rect)) {
										if (event.type == SDL_MOUSEBUTTONDOWN) {
											running2 = false;
											cout << "is back " << endl;
										}
									}
								}
								SDL_RenderSetViewport(renderer, &viewport);
								SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderFillRect(renderer, &content);
								SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); 
								for (int i = 0; i < 2; i++) {
									SDL_Rect cellRect = { content.x + i * CELL_WIDTH, content.y + 0 * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };									
									SDL_RenderDrawRect(renderer, &cellRect);
									string text;
									if (i == 0) {
										text = "Ten doi bong";
									}
									else if (i == 1) {
										text = "Diem";
									}
									SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });
									SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
									int textWidth = textSurface->w;
									int textHeight = textSurface->h;
									SDL_Rect textRect = { i * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
															 0 * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
															 textWidth,
															 textHeight };
									SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
									SDL_FreeSurface(textSurface);
									SDL_DestroyTexture(textTexture);
								}
								for (int i = 1; i < _danhsachdoibong.size() + 1; i++) {
									for (int col = 0; col < NUM_COLS; col++) {
										SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };	
										SDL_RenderDrawRect(renderer, &cellRect);
										string text;
										if (col == 0) {
											int t = i - 1;
											text = _danhsachdoibong[t].ten;
										}
										else if (col == 1) {
											int t = i - 1;
											text = to_string(_danhsachdoibong[t].diem);

										}
										SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });
										SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
										int textWidth = textSurface->w;
										int textHeight = textSurface->h;
										SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
															 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
															 textWidth,
															 textHeight };
										SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
										SDL_FreeSurface(textSurface);
										SDL_DestroyTexture(textTexture);
									}
								}
								SDL_RenderPresent(renderer);
							}
							break;
						}
						case 4:
						{
							return 0;
							break;
						}
						}
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
		running2 = true;
		running3 = true;
		running4 = true;
		running5 = true;
	}
	
	delete[] inputThemcauthu;
	delete[] _inputThemcauthu;
	delete[] inputThemvaodanhsachcauthu;
	delete[] _inputThemvaodanhsachcauthu;
	delete[] inputThemtrandau;
	delete[] _inputThemtrandau;
	delete[] inputSuacauthu;
	delete[] _inputSuacauthu;
	delete[] buttons;
	delete[] buttons0;
	delete[] buttons1;
	delete[] buttons2;
	delete[] buttonsBack;
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}