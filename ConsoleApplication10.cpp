#pragma warning( disable : 4996)
#define CURL_STATICLIB 
#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <filesystem>
#include "lazy_importer.hpp"
#include <random>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <Lmcons.h>
#include <Windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <urlmon.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <winternl.h>
#include <thread>
#include <fstream>
#include <cstdlib>
#include <Windows.h>
#include <filesystem>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>
#include <stdint.h>
#include <cstdio>
#include <winbase.h>
#include <stdio.h>
#include "json.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <regex>
#include <string>
#include <thread>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#pragma comment(lib,"ws2_32")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "libcurl_a.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "normaliz.lib")
using ::std::thread;
using ::std::array;
using ::std::vector;
using ::std::cout;
using ::std::regex;
using ::std::endl;
using ::std::ref;
#define MAX_THREADS 200
namespace fs = std::filesystem;
using namespace std;
bool running = true;
using json = nlohmann::json;
#include "functions.h"
//#include "settings.h"

std::string return_current_time_and_date()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%I:%M:%S");
	return ss.str();
}

void main1() {



	string version = "3";
	system("title Minecraft Sniper V3");

	//Resets Prior Logins
	//CURL* curl = curl_easy_init();
	//curl_easy_reset(curl);
	system("color 3");
	cout << "--------------------------------------\n";
	cout << "- Minecraft Snipe by Underscores v" << version << "  -\n";
	cout << "- Supports Auth Token or EMAIL:PASS  -\n";
	cout << "--------------------------------------\n";

	//Login Type for Account
	string type;
	cout << "[+] Options\n";
	cout << "[-] 1 = Email:Password Format\n";
	cout << "[-] 2 = Bearer Format\n";
	cout << "[-] Your Selection: ";
	cin >> type;
	cout << "\n";

	if (type != "1") {
		if (type != "2") {
			system("cls");
			main1();
		}
	}

	string filename1;
	cout << "[+] Enter filename for accounts: ";
	cin >> filename1;
	cout << "\n";

	cout << "[+] Enter proxy (Optional, if none enter 0): ";
	cin >> proxy;
	cout << "\n";

	string startearly;
	cout << "[+] Start snipe before release [seconds] (Optional, if none enter 0): ";
	cin >> startearly;
	cout << "\n";

	string startafter;
	cout << "[+] Start snipe after release [milliseconds] (Optional, if none enter 0): ";
	cin >> startafter;
	cout << "\n";

	//filename1 = "C:\\Users\\Grunt\\source\\repos\\ConsoleApplication10\\Release\\accounts.txt";
	string key;
	ifstream file(filename1);
	string content;
	std::vector<std::string> keys(10);
	int number = 1;
	string myusername;

	//EMAIL:PASS Format
	if (type == "1") {
		cout << "[+] Loading accounts...\n";
		while (file >> content) {

			string account = content;
			std::string delimiter = ":";
			std::string email = account.substr(0, account.find(delimiter[0])); //Grabs first half
			std::string password = account.substr(int(email.length()), account.find(delimiter[0])); //Gets length of email to remove it from the string
			password = std::regex_replace(password, std::regex(":"), ""); //Removes :

			//Login
			key = mclogin(email, password);
			if (key != "0") {

				//Checks if the account is eligble to change username
				string canwechange = canwechangename(key);
				if (canwechange != "True") {
					cout << "[!] " << email << " (" << getmyusername(key) << ") is not eligble to change username... skipping.\n";
				}
				else {

					//Grabs username
					myusername = getmyusername(key);
					keys[number] = key;
					number++;
					cout << "[-] Loaded: " << myusername << " (" << email << ")\n";
				}
			}
			else {
				cout << "[-] Invalid Login: " << account << "\n";
			}
			this_thread::sleep_for(chrono::seconds(3)); //Sleep for 2 seconds after each check
		}
		cout << "[-] Loaded " << number - 1 << " accounts!\n\n";
	}

	//AUTH TOKEN FORMAT
	if (type == "2") {
		cout << "[+] Loading accounts...\n";
		while (file >> content) {
			key = content;
			myusername = getmyusername(key);
			if (myusername == "0") {
				cout << "[-] Something is wrong with this Auth Token! Skipping...\n";
				//this_thread::sleep_for(chrono::seconds(5));
				//system("cls");
				//main1();
			}
			else {

				if (myusername != "NO USERNAME ON ACCOUNT") {
					string canwechange = canwechangename(key);
					if (canwechange != "True") {
						cout << "[!] " << myusername << " is not eligble to change username... skipping.\n";
					}
					else {
						keys[number] = key;
						number++;
						cout << "[-] Loaded: " << myusername << "\n";

					}
				}
				else {
					keys[number] = key;
					number++;
					cout << "[-] Loaded: " << myusername << "\n";
				}
			}
			this_thread::sleep_for(chrono::seconds(2)); //Sleep for 2 seconds after each check
		}
		cout << "[-] Loaded " << number - 1 << " accounts!\n\n";
	}

	//USERNAME THAT WILL BE SNIPED
	string check;
	int releaseunix;
	string username;
	int math1;
	int myunixfixed;
	while (true) {
		cout << "[+] Enter username to snipe: ";
		cin >> username;

		//My UNIX Time
		std::time_t myunix = std::time(0);
		std::string myunix1 = std::to_string(myunix);
		myunixfixed = std::stoi(myunix1);


		//Gets UNIX time for account
		check = check_release(username);
		releaseunix = std::stoi(check);

		//Calculating time
		math1 = releaseunix - myunixfixed;

		if (math1 < -10000) {
			cout << "[-] This username is not available to be sniped, try again...\n\n";
			break;

		}
		else {
			cout << "[-] Username is being released in " << math1 << " seconds\n";
			break;
		}
	}

	math1 = 5;

	//RUN MAIN PROCESS
	int times = 1;
	while (true) {
		std::time_t myunix = std::time(0);
		std::string myunix1 = std::to_string(myunix);
		int myunixfixed = std::stoi(myunix1);

		int startafter1 = stoi(startafter);
		int startearly1 = stoi(startearly);

		int secondsremaining = releaseunix - myunixfixed - startearly1;

		if (secondsremaining > 30) {
			if (times == 1) { cout << "[+] Sniping " << username << " in " << secondsremaining << " seconds...\n\n"; }
			if (0 == (secondsremaining % 100)) { //cout << "[+] Sniping " << username << " in " << secondsremaining << " seconds...\n";
				string recheck = getmyusername(key); //Rechecking auth
				if (recheck == "0") {
					system("cls");
					cout << "[!] Error upon rechecking your auth key. It might've expired! Please grab a new one.\n";
					this_thread::sleep_for(chrono::seconds(1));
					main1();
					break;
				}
				else {
					this_thread::sleep_for(chrono::seconds(1)); //cout << "[-] Rechecked Auth Key: " << recheck << "\n\n";
				}
			}
			this_thread::sleep_for(chrono::seconds(1));
			times++;
		}
		else {
			if (secondsremaining < 30 && secondsremaining > 5) {
				cout << "[-] Sniping " << username << " in " << secondsremaining << " seconds...\n";
				this_thread::sleep_for(chrono::seconds(1));
			}
			else {
				string authtoken;
				if (secondsremaining <= 1) { //Snipe!

					//Wait before sniping
					if (startafter1 >= 1) {
						this_thread::sleep_for(chrono::milliseconds(startafter1));
					}

					for (int i = 0; i < number - 1; i++) { 
						if (myusername == "NO USERNAME ON ACCOUNT") { //If username is blank (new account), use the alt sniper as it won't work on the PUT request
							authtoken = keys[i + 1];
							std::thread anti(loop2, username, authtoken);
							anti.detach();
							this_thread::sleep_for(chrono::milliseconds(200));
						}
						else {
							authtoken = keys[i + 1];
							std::thread anti(loop1, username, authtoken);
							anti.detach();
							this_thread::sleep_for(chrono::milliseconds(200));
						}
						//cout << "Executed: " << i << " -- " << authtoken << "\n\n";
					}
					break;
					/*
					if (type == "1") { //EMAIL:PASS Entered
						for (int i = 0; i < number; i++) {
							string hello = keys[i];
							std::thread anti(loop1, username, hello);
							anti.detach();
							this_thread::sleep_for(chrono::milliseconds(50));
						}
						break;
					}
					if (type == "2") { //Auth only
						for (int i = 0; i < number; i++) { //If username is blank (new account), use the other sniper as it won't work on the regular minecraft PUT request
							if (myusername == "NO USERNAME ON ACCOUNT") {
								string hello = keys[i];
								std::thread anti(loop2, username, hello);
								this_thread::sleep_for(chrono::milliseconds(50));
								anti.detach();
							}
							else { 
								string hello = keys[i];
								std::thread anti(loop1, username, hello);
								this_thread::sleep_for(chrono::milliseconds(50));
								anti.detach();
							}
						}
						break;
					}
					*/
				}
				else {
				}
			}
		}
	}


	//cout << "hi";
	string wait;
	cin >> wait;
}

int main()
{
	system("color 3");
	main1();
	system("pause");
}
