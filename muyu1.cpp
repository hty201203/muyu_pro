#include<cstdio>
#include<algorithm>
#include<iomanip>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include <map>
#include<vector>
#include<iostream>
#include<queue>
#include <windows.h>
#include<cstdlib>
#include <time.h>
#include <thread>
#include <fstream>
#include <chrono>
#include <ctime>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
//#include<conio.h>
#define CJLEN 10
#define CJSTARTLINE 10
using namespace std;
long long ans,old;
int c[100] = {};
bool f = 0;
const bool SHOWCJ = 0;
string convertUnixTime(time_t unix_time) {
    std::tm* ptm = std::localtime(&unix_time); // 转换为本地时间
    char buffer[80];
    // 格式化日期和时间
    if (strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ptm) != 0) {
        return std::string(buffer);
    }
    return "Invalid Date";
}
void hidden(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=0;
	SetConsoleCursorInfo(hOut,&cci);
}
void move(int x,int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);
}
void test(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int cursorX = csbi.dwCursorPosition.X;
    int cursorY = csbi.dwCursorPosition.Y;

    std::cout << "NOWPOS: (" <<cursorY << "行," << cursorX << "列)"  << std::endl;
}
void load(){
	ifstream f1("save.txt");
	f1>>ans;
}
void save(){
	//system("del save.txt");
	ofstream f1("save.txt");
	f1<<ans;
}
void loadcj(){
	ifstream f2("cj.txt");
	for(int i = 0;i<CJLEN;i++) f2>>c[i];
}
void savecj(){
	ofstream f2("cj.txt");
	for(int i = 0;i<CJLEN;i++) f2<<c[i]<<" ";
}
void printcj(){
	if(!SHOWCJ) return;
	string s[10] = {"GOLD","DIAMOND","IRON","DIRT","狗屎"
	,"CANDY","SWEET","APPLE","BANANA","WOOD"};
	for(int i = 0;i<CJLEN;i++){
		if(c[i]>0){
			printf("ID.%3d NUM.%5d ",i,c[i]);
			cout<<s[i];
		}
		cout<<"\n";
	}
}
void getcj(int a){
	int b = rand()%1000;
	if(1>0){
		if(b<5) c[0]++;
		else if(b<20) c[1]++;
		else if(b<50) c[2]++;
		else if(b<100) c[3]++;
		else if(b<150) c[4]++;
		else if(b<250) c[5]++;
		else if(b<400) c[6]++;
		else if(b<420) c[7]++;
		else if(b<600) c[8]++;
		else if(b<800) c[9]++;
	}
	move(0,CJSTARTLINE);
	printcj();
}
void sysinfo(){
	OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
        std::cout << "Operating System Version: " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << std::endl;
    }
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::cout << "Processor Architecture: ";
    switch (sysInfo.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
        std::cout << "AMD64" << std::endl;
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        std::cout << "IA64" << std::endl;
        break;
    case PROCESSOR_ARCHITECTURE_INTEL:
        std::cout << "x86" << std::endl;
        break;
    default:
        std::cout << "Unknown" << std::endl;
        break;
    }
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);

    std::cout << "Total physical memory: "
              << statex.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
    std::cout << "Available physical memory: "
              << statex.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;
	//
	DWORD bufferSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
    if (bufferSize > 0) {
        BYTE* buffer = new BYTE[bufferSize];
        if (GetSystemFirmwareTable('RSMB', 0, buffer, bufferSize) != 0) {
            std::string serialNumber(reinterpret_cast<const char*>(buffer + 8)); // 前8个字节是长度信息，直接跳过
            std::cout << "主板序列号：" << (string)serialNumber << std::endl;
        }
        delete[] buffer;
    }
    int coreCount = std::thread::hardware_concurrency();
    std::cout << "CPU核心数为：" << coreCount << std::endl;
    /*
    const char* env_var = std::getenv("PATH");
    if (env_var != nullptr) {
        std::cout << "PATH: " << env_var << std::endl;
    } else {
        std::cout << "PATH not found." << std::endl;
    }*///path
    cout<<"SYSTEM:";
    #ifdef _WIN32
        std::cout << "Windows";
        system("ver");
    #elif __APPLE__
        std::cout << "macOS" << std::endl;
    #elif __linux__
        std::cout << "Linux" << std::endl;
    #elif __FreeBSD__
        std::cout << "FreeBSD" << std::endl;
    #endif
    /*
    HDC screen_dc = GetDC(NULL);
    int width = GetDeviceCaps(screen_dc, DESKTOPHORZRES);
    int height = GetDeviceCaps(screen_dc, DESKTOPVERTRES);
    ReleaseDC(NULL, screen_dc);
    std::cout << "Screen Resolution: " << width << "x" << height << std::endl;
	*///screen
	int screenx=GetSystemMetrics(SM_CXSCREEN);
    int screeny=GetSystemMetrics(SM_CYSCREEN);
    printf("Your screen resolution is: %d*%d",screenx,screeny);
    //UINT dpi = GetDpiForSystem();
    //std::cout << "The system DPI is: " << dpi << std::endl;
    cout<<"\n";
    HDC hdc = GetDC(NULL);
    if (hdc) {
        DEVMODE devmode = {};
        devmode.dmSize = sizeof(DEVMODE);
        if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode)) {
            int frequency = devmode.dmDisplayFrequency;
            std::cout << "Current screen refresh rate: " << frequency << " Hz" << std::endl;
        } else {
            std::cout << "Failed to get screen refresh rate." << std::endl;
        }
        ReleaseDC(NULL, hdc);
    } else {
        std::cout << "Failed to get device context." << std::endl;
    }
    system("wmic cpu get CurrentClockSpeed");
    cout<<"\033[1A";
    system("wmic cpu get Caption");
}
int main(){
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	system("title 木鱼");
	system("echo off & cls");
	test();
	hidden();
	srand(time(0));
	load();
	loadcj();
	move(0,CJSTARTLINE);
	printcj();
	move(0,4);printf("======SYSINFO======\n");
	sysinfo();
	while(!KEY_DOWN('Q')){
		//hidden();
		if(KEY_DOWN(' ')){
			ans++;
			while(KEY_DOWN(' ')){
				cout<<"";
			}
		}
		int nt = time(0);
		move(0,0);
		printf("CNT:%10lld TIME:%10lld     ",ans,nt);
		if(nt%5==0 && f==0){
			move(0,1);
			f = 1;
			printf("SPD:%10.2llf                                      ",(double)(ans-old)/5.0);
			old = ans;
			if(ans%50>5 && rand()%3==1){
				getcj(nt);
				savecj();
			}
		}
		else if(nt%5!=0){
			if(f==1) f = 0;
			time_t ut = time(0);
			string s = convertUnixTime(ut);
			move(0,2);
			cout<<s;
		}
		if(nt%10==0) save();
	}
	system("pause &cls");
	return 0;
}

