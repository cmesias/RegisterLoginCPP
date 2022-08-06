#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Users {

public:
	string username;
	string password;

};

vector<Users> users;

// Register: Check if username and password matches an existing user, if so prompt again
bool CheckIfRegisterInputMatchesDatabase(stringstream userNamePassword) {

	cout << endl;
	cout << "-----------------------------------------" << endl;
	cout << "            REGISTER: ENTERED            " << endl;
	cout << "-----------------------------------------" << endl;

	// Create temporary variables to store registered info
	vector<Users> buffer;
	string usernameTemp;
	string passwordTemp;

	userNamePassword >> usernameTemp >> passwordTemp;

	// Set path file to open
	{
	    std::ifstream file( "./users.txt" );
	    Users temp;

	    // Loop through each line from file and save to vector of users for processing below
	    while ( file >>  temp.username >> temp.password)
	    {
	    	buffer.push_back(temp);
	    }
	}

	// Print out database of users from vector
	//cout << endl;
	//cout << "-----------------------------------------" << endl;
	//cout << "   REGISTER: SHOW DATABASE FROM VECTOR   " << endl;
	//cout << "-----------------------------------------" << endl;

	// Check if username and password matches an existing user
	for (unsigned int i = 0; i < buffer.size(); i++) {
		//cout << "i: " << i << ", Username: " << buffer[i].username << ", Password: " << buffer[i].password << endl;

		// Compare input username and password with database of users if it exists

		// Username matches existing username in database
		if (usernameTemp == buffer[i].username) {

			// Return that user exists already in database
			return true;
		}
	}

	// If we were not able to return from the above code, that means username & password inputted does not match our records, create new user
	{
		cout << "-----------------------------------------" << endl;
		cout << "       REGISTER: CREATING NEW USER       " << endl;
		cout << "-----------------------------------------" << endl;
		// Open file, and get previous High Score
		{
			std::stringstream filePath;
			filePath << "./users.txt";

			std::fstream fileOpen(filePath.str().c_str());

			// If a file exist
			if (fileOpen.is_open())
			{
				std::ofstream fileSave;
				fileSave.open(filePath.str().c_str(), std::ios::app);
				fileSave << usernameTemp << " " << passwordTemp << "\n";
				fileSave.close();
			}

			// If no file exists, create new highscore
			else {

				std::cout<< "File does not exist, creating new user with file with data.\n";
				{
					std::stringstream filePath;
					filePath << "./users.txt";

					std::ofstream fileSave;
					fileSave.open(filePath.str().c_str());
					fileSave << usernameTemp << " " << passwordTemp << "\n";
					fileSave.close();
				}
			}
			fileOpen.close();

			// Return that user did not exist, so we created a new user
			return false;
		}
	}
	cout << "-----------------------------------------" << endl;
	cout << "            REGISTER: EXITING            " << endl;
	cout << "-----------------------------------------" << endl;
}

// Login: Check if username and password matches an existing user
bool CheckIfLoginMatchesDatabase(stringstream userNamePassword) {
	cout << endl;
	cout << endl;
	cout << "-----------------------------------------" << endl;
	cout << "              LOGIN: ENTERED             " << endl;
	cout << "-----------------------------------------" << endl;

	bool userExists = false;

	// Create temporary variables to store ogin info
	string usernameTemp;
	string passwordTemp;

	userNamePassword >> usernameTemp >> passwordTemp;

	// Set path file to open
	{
	    std::ifstream file( "./users.txt" );
	    Users temp;

	    // Loop through each line from file and save to vector of users for processing below
	    while ( file >>  temp.username >> temp.password)
	    {
	    	users.push_back(temp);
	    }
	}

	// Print out database of users from vector
	//cout << endl;
	//cout << "-----------------------------------------" << endl;
	//cout << "    LOGIN: SHOW DATABASE FROM VECTOR     " << endl;
	//cout << "-----------------------------------------" << endl;

	// Check if username and password matches an existing user
	for (unsigned int i = 0; i < users.size(); i++) {
		//cout << "i: " << i << ", Username: " << users[i].username << ", Password: " << users[i].password << endl;

		// Compare input username and password with database of users if it exists

		// Username matches existing username in database
		if (usernameTemp == users[i].username) {

			// Password also matches existing username in database, stop looping and return true statement
			if (passwordTemp == users[i].password) {
				userExists = true;

				// Return that user exists in database
				return userExists;
			}
		}
	}

	// If we were not able to return from the above code, that means username & password inputted does not match our records, return false
	return userExists;
	cout << "-----------------------------------------" << endl;
	cout << "              LOGIN: EXITING             " << endl;
	cout << "-----------------------------------------" << endl;
}

// Prompt user to select an option from the menu
int promptMenuSelection() {

	int option = 4;

	// Dispaly options for user to choose from
	cout << "-----------------------------------------" << endl;
	cout << "                   MENU                  " << endl;
	cout << "-----------------------------------------" << endl;
	cout << "0. Login "									<< endl;
	cout << "1. Register" 								<< endl;
	cout << "2. Forgot password" 						<< endl;
	cout << "3. Quit" 									<< endl;
	cout << endl;

	// Get user input
	cin >> option;

	// Return selected option
	return option;
}

// Login: get user input for username and password
stringstream getLoginUsernameAndPassword() {

	// Return user ogin info
	stringstream usernamePasswordLogin;

	cout << "-----------------------------------------" << endl;
	cout << "                   LOGIN                 " << endl;
	cout << "-----------------------------------------" << endl;
	// Get username
	string username;
	cout << "Enter your username: "; cin >> username;

	// Get password
	string password;
	cout << "Enter your password: "; cin >> password;

	// Store usernme and password input into stringstream for return
	usernamePasswordLogin << username + " " + password;

	// Show user their username and password
	cout << endl;
	cout << "Login info: " << usernamePasswordLogin.str().c_str() << endl;

	return usernamePasswordLogin;
}

// Register: get user input for username and password
stringstream getRegisterUsernameAndPassword() {

	// Return user registered info
	stringstream usernamePasswordRegister;

	cout << "-----------------------------------------" << endl;
	cout << "                 REGISTER                " << endl;
	cout << "-----------------------------------------" << endl;

	// Get username
	string username;
	cout << "Enter your username: "; cin >> username;

	// Get password
	string password;
	cout << "Enter your password: "; cin >> password;

	// Return username and password
	usernamePasswordRegister << username + " " + password;

	// Show user their username and password
	cout << endl;
	cout << "Registered info: " << usernamePasswordRegister.str().c_str() << endl;

	return usernamePasswordRegister;
}

void LogInSuccessOrFailure(bool success) {
	cout << endl;
	if (success) {
		cout << "Successfully logged in!" << endl;
	} else {
		cout << "Username and Password do not match our records. :(" << endl;
	}
}

void RegisteredSuccessOrFailure(bool existingUser) {
	cout << endl;
	if (existingUser) {
		cout << "Username already exists! Please log in." << endl;
	} else {
		cout << "Registered Successfully!" << endl;
	}

}



int main(int argc, char **argv) {

	// Prompt user to select an option from the menu
	int option = -1;

	while (option != 4) {

		option = promptMenuSelection();

		// Login existing user
		if (option == 0) {

			// Attempt to login user
			LogInSuccessOrFailure( CheckIfLoginMatchesDatabase( getLoginUsernameAndPassword() ) );

		}

		// Register existing user
		else if (option == 1) {

			// Get registered username & password
			RegisteredSuccessOrFailure (CheckIfRegisterInputMatchesDatabase ( getRegisterUsernameAndPassword() ) );
		}
	}

	cout << endl;
	cout << "-----------------------------------------" << endl;
	cout << "                 EXITING                 " << endl;
	cout << "-----------------------------------------" << endl;

	return 0;
}
