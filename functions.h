#include "settings.h"

//For CURL, ignore
size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

//List of UserAgents
string user_agent()
{
	srand(time(0));
	string choices[] = {
		"Mozilla/5.0 (Macintosh; PPC Mac OS X 10_6_8) AppleWebKit/5360 (KHTML, like Gecko) Chrome/36.0.811.0 Mobile Safari/5360",
		"Mozilla/5.0 (X11; Linux i686) AppleWebKit/5332 (KHTML, like Gecko) Chrome/37.0.859.0 Mobile Safari/5332",
		"Opera/9.28 (X11; Linux i686; en-US) Presto/2.8.300 Version/12.00",
		"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/5321 (KHTML, like Gecko) Chrome/40.0.831.0 Mobile Safari/5321",
		"Mozilla/5.0 (Windows NT 5.1) AppleWebKit/5321 (KHTML, like Gecko) Chrome/37.0.853.0 Mobile Safari/5321",
		"Opera/8.67 (X11; Linux i686; en-US) Presto/2.8.225 Version/11.00",
		"Opera/8.77 (Windows CE; en-US) Presto/2.12.326 Version/10.00",
		"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:90.0) Gecko/20100101 Firefox/90.0",
		"Mozilla/5.0 (iPhone; CPU iPhone OS 11_5_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) FxiOS/35.0 Mobile/15E148 Safari/605.1.15",
		"Mozilla/5.0 (iPad; CPU OS 11_5_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) FxiOS/35.0 Mobile/15E148 Safari/605.1.15",
		"Mozilla/5.0 (iPod touch; CPU iPhone OS 11_5_1 like Mac OS X) AppleWebKit/604.5.6 (KHTML, like Gecko) FxiOS/35.0 Mobile/15E148 Safari/605.1.15",
		"Mozilla/5.0 (Linux; Android 8.0.0; SM-G960F Build/R16NW) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.84 Mobile Safari/537.36",
		"Mozilla/5.0 (Linux; Android 7.0; SM-G892A Build/NRD90M; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/60.0.3112.107 Mobile Safari/537.36",
		"Mozilla/5.0 (iPhone; CPU iPhone OS 12_0 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) CriOS/69.0.3497.105 Mobile/15E148 Safari/605.1",
		"Mozilla/5.0 (iPhone; CPU iPhone OS 12_0 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) FxiOS/13.2b11866 Mobile/16A366 Safari/605.1.15",
		"Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1",
		"Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.34 (KHTML, like Gecko) Version/11.0 Mobile/15A5341f Safari/604.1",
		"Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A5370a Safari/604.1"
	};
	string random;
	for (int i = 0; i < 3; i++)
	{
		random = choices[rand() % 5];
	}
	return random;
}

//Check Account Status (Availbility) [Not being used]
string checkusername(string username, string auth) {
	auto curl = curl_easy_init();
	std::string response_string;
	std::string header_string;
	try {
		string url = "https://api.minecraftservices.com/minecraft/profile/name/" + username + "/available";
		if (curl) {

			struct curl_slist* slist1;
			slist1 = NULL;
			slist1 = curl_slist_append(slist1, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
			curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, auth);
			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, "8000");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

			char* url;
			double elapsed;
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
			curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;
		}

		try {
			nlohmann::json jsonData = nlohmann::json::parse(response_string);
			string status = jsonData["status"];
			return status;
		}
		catch (const std::exception& e)
		{
			return "0";
		}
	}
	catch (const std::exception& e)
	{
		return "0";
	}
}

//Check if account is eligble for name change
string canwechangename(string auth) {
	auto curl = curl_easy_init();
	std::string response_string;
	std::string header_string;
	try {
		string url = "https://api.minecraftservices.com/minecraft/profile/namechange";
		if (curl) {

			struct curl_slist* slist1;
			slist1 = NULL;
			slist1 = curl_slist_append(slist1, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
			curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, auth);
			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, "8000");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

			char* url;
			double elapsed;
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
			curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;
		}
		try {
			string status1;
			nlohmann::json jsonData = nlohmann::json::parse(response_string);
			bool status = jsonData["nameChangeAllowed"];
			if (status == true) {
				status1 = "True";
			}
			if (status == false) {
				status1 = "False";
			}
			return status1;
		}
		catch (const std::exception& e)
		{
			return "0";
		}
	}
	catch (const std::exception& e)
	{
		return "0";
	}
}

//Grab UNIX of username release
string check_release(string username) {
	auto curl = curl_easy_init();
	std::string response_string;
	std::string header_string;
	try {
		string url = "http://api.coolkidmacho.com/droptime/" + username;
		if (curl) {

			struct curl_slist* slist1;
			slist1 = NULL;
			slist1 = curl_slist_append(slist1, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, "8000");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

			char* url;
			double elapsed;
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
			curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;

			//cout << to_string(response_code);
		}

		//cout << response_string;

		try {
			nlohmann::json jsonData = nlohmann::json::parse(response_string);
			int status1 = jsonData["UNIX"];
			string status = std::to_string(status1);
			return status;
		}
		catch (const std::exception& e)
		{
			return "0";
		}
	}
	catch (const std::exception& e)
	{
		return "0";
	}
}

//Get username based off Auth Key
string getmyusername(string auth) {
	try {
		auto curl = curl_easy_init();
		std::string response_string;
		std::string header_string;
		string url = "https://api.minecraftservices.com/minecraft/profile";
		if (curl) {

			struct curl_slist* slist1;
			slist1 = NULL;
			slist1 = curl_slist_append(slist1, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
			curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, auth);
			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, "8000");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

			char* url;
			long response_code;
			double elapsed;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
			curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;
		}

		try {
			nlohmann::json jsonData = nlohmann::json::parse(response_string);
			string name = jsonData["name"];
			return name;
		}
		catch (const std::exception& e)
		{
			nlohmann::json jsonData = nlohmann::json::parse(response_string);
			string error = jsonData["error"];
			if (error == "NOT_FOUND") {
				error = "NO USERNAME ON ACCOUNT";
			}
			return error;
		}
	}
	catch (const std::exception& e)
	{
		return "0";
	}
}



//Snipe Account
string getusername(string username, string auth) {
	auto curl = curl_easy_init();
	std::string response_string;
	std::string header_string;
	//      agent: { name: "Minecraft", version: 1 }, username: email, password: password
	std::string jsonstr = "{\"profileName\":\"" + username + "\"}";
	try {
		string url = "https://api.minecraftservices.com/minecraft/profile";
		if (curl) {

			struct curl_slist* slist1;
			slist1 = NULL;
			slist1 = curl_slist_append(slist1, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
			if (proxy != "0") { curl_easy_setopt(curl, CURLOPT_PROXY, proxy); }
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonstr.c_str());
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
			curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, auth);
			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

			char* url;
			double elapsed;
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
			curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;

			//cout << to_string(response_code);
		}

		//cout << response_string;

		try {
			nlohmann::json jsonData = nlohmann::json::parse(response_string);
			if (jsonData["name"] == username) {
				cout << "[-] Sniped!\n";
			}
			else {
				if (jsonData["details"]["status"] == "DUPLICATE") {
					cout << "[-] Duplicate\n";
				}
				else {
					if (jsonData["path"] == "/minecraft/profile/name/" + username) {
						cout << "[-] Rate Limited!\n";
					}
					else {
						cout << "[-] Unkown Response: " << response_string << "\n";
					}
				}
			}
		}
		catch (const std::exception& e)
		{
			return "0";
		}
	}
	catch (const std::exception& e)
	{
		return "0";
	}
}

//Loop 2 (This one is for Berar auth key)
void loop2(string username, string auth) {

	for (int i = 0; i < requests; i++) {
		try {
			string claim = getusername(username, auth);
			if (claim == "1" || claim == "rate") {
				break;
			}
			this_thread::sleep_for(chrono::milliseconds(delayperrequest)); //Delay per request
		}
		catch (const std::exception& e)
		{

		}
	}

	try {
		//Check if we successfully sniped username
		string check = getmyusername(auth);
		if (check == username) {
			cout << "\n[-] Successfully sniped " << username << " :)\n";
		}
		else {
			cout << "\n[-] Could not snipe " << username << " :(\n";
		}
		system("pause");
	}
	catch (const std::exception& e)
	{

	}
}



//Login to Minecraft Account (Get Auth)
string mclogin(string username, string password) {
	auto curl = curl_easy_init();
	std::string response_string;
	std::string header_string;

	std::string jsonstr = "{\"agent\": {\"name\": \"Minecraft\", \"version\": 1}, \"username\": \"" + username + "\", \"password\": \"" + password + "\", \"requestUser\": true}";

	try {
		string url = "https://authserver.mojang.com/authenticate";
		if (curl) {

			struct curl_slist* slist1;
			slist1 = NULL;
			slist1 = curl_slist_append(slist1, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonstr.c_str());
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, "8000");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

			char* url;
			double elapsed;
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
			curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;

			try {
				nlohmann::json jsonData = nlohmann::json::parse(response_string);
				string key = jsonData["accessToken"];
				return key;
			}
			catch (const std::exception& e)
			{
				return "0";
			}
		}
	}
	catch (const std::exception& e)
	{
		return "0";
	}
}

//Snipe Account
string mcsnipe(string username, string auth) {
	auto curl = curl_easy_init();
	std::string response_string;
	std::string header_string;
	try {
		string url = "https://api.minecraftservices.com/minecraft/profile/name/" + username;
		if (curl) {

			struct curl_slist* slist1;
			slist1 = NULL;
			//slist1 = curl_slist_append(slist1, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
			if (proxy != "0") { curl_easy_setopt(curl, CURLOPT_PROXY, proxy); }
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent());
			curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, auth);
			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

			char* url;
			double elapsed;
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
			curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;
			//cout << to_string(response_code);
		}
		//cout << response_string;
		try {
			nlohmann::json jsonData = nlohmann::json::parse(response_string);
			if (jsonData["name"] == username) {
				cout << "[-] Sniped!\n";
			}
			else {
				if (jsonData["details"]["status"] == "DUPLICATE") {
					cout << "[-] Duplicate\n";
				}
				else {
					if (jsonData["path"] == "/minecraft/profile/name/" + username) {
						cout << "[-] Rate Limited!\n";
					}
					else {
						cout << "[-] Unkown Response: " << response_string << "\n";
					}
				}
			}
		}
		catch (const std::exception& e)
		{
			return "0";
		}
	}
	catch (const std::exception& e)
	{
		return "0";
	}
}

//Loop 1 (This one is for EMAIL:PASS)
void loop1(string username, string auth) {


	for (int i = 0; i < requests; i++) {
		try {
			string claim = mcsnipe(username, auth);
			//cout << "[-] Sent request to MC!\n";
			if (claim == "1" || claim == "rate") {
				break;
			}
			this_thread::sleep_for(chrono::milliseconds(delayperrequest)); //Delay per request
		}
		catch (const std::exception& e)
		{
			
		}
	}

	//Check if we successfully sniped username
	string check = getmyusername(auth);
	if (check == username) {
		//sniped = "true";
		cout << "\n[-] Successfully sniped " << username << " :)\n";
	}
	else {
		cout << "\n[-] Could not snipe " << username << " :(\n";
	}
}
