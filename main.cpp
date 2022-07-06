#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<chrono>
#include<ctime>
using namespace std;

int id_cal (string username){
  int result;
  for (int i=0; i<username.size(); i++){
    char temp = username[i];
    int n = int(temp);
    result += n;
  }
  result += username.size();
  return result;
}

string encryption (string password){
  string result;
  int n = password.size();
  for (int i=0; i<password.size(); i++){
    char temp;
    if (i%2!=0) temp = password[i] - 1;
    else temp = password[i] + 1;
    result += temp;
  }
  return result;
}

string decryptor (string crypt){
  string result;
  int n = crypt.size();
  for (int i=0; i<crypt.size(); i++){
    char temp;
    if(i%2!=0) temp = crypt[i] + 1;
    else temp = crypt[i] - 1;
    result+=temp;
  }
  return result;
}

bool check_sel (char x){
  return 
    x=='R' || x=='r' ||
    x=='L' || x=='l' ||
    x=='Q' || x=='q' ;
}


string worktime (string in){
  auto timeout = chrono::system_clock::to_time_t(chrono::system_clock::now());
  string out;
  out = ctime(&timeout);
  int Hin=0;
  int Min=0;
  int Hout=0;
  int Mout=0;
  for (int i=0; i<in.size(); i++){
    if (in[i] == ':'){
      //sustracting character 0 to a char 
      //equals to -48 which translates an 
      //ascii number into its int value
      Hin += in[i-2] - '0';
      Hin += in[i-1] - '0';
      Min += in[i+1] - '0';
      Min += in[i+2] - '0';
      break;
    }
  }
  for (int i=0; i<out.size(); i++){
    if (out[i] == ':'){
      Hout += out[i-2] - '0';
      Hout += out[i-1] - '0';
      Mout += out[i+1] - '0';
      Mout += out[i+2] - '0';
      break;
    }
  }
  Min = Min + Hin * 60;
  Mout = Mout + Hout * 60;
  int T = Mout - Min;
  string result = "\n\t\tSuccessfully clocked out.\n\tYou've working for " +
  to_string(T/60) + " hours and " + to_string(T%60) + " minutes.\n" ;

  return result;
}

int main(){

  string username;
  string password;
  string confpass;
  char selection;
  string tovec;
  vector <string> database;
  
  while(true){ 
    cout << "Please, select one of the following options:\n[R]Register.\n[L]Login.\n[Q]Quit.\n";
    cin >> selection;
    cin.get();
    if (check_sel(selection)) break;
    else cout << "Error. Please Try again." << endl;
  }
  switch (selection){
    case'R':
    case'r': {//Provided registration.
      cout << "Enter your username: ";
      getline(cin, username);
      cout << "Enter your password: ";
      getline(cin, password);
      cout << "Confirm your password: ";
      getline (cin, confpass);
      if (password != confpass){
        cout << "Your passwords don't match. Quitting program..." << endl;
      }
      else{
        tovec =
        "ID" + to_string(id_cal(username)) + '\n' +
        "Username: " + username + '\n' +
        "Password (encrypted): " + encryption(password) + '\n' ;
        database.push_back(tovec);
        cout << endl << "\t\tSuccesfuly registered! Please restart the program to log in." << endl;
        cout << endl << tovec << endl;
        ofstream file;
        file.open("logdata.txt", std::ios_base::app);
        for (int i=0; i<database.size(); i++){
          file << database[i] << endl << endl;
        }
        file.close();
        database.clear();
        return 0;
      }
      break;
             }
    case 'L':// Provided Log.
    case 'l': { //Curly bracket provides local scope to avoid cross initialization
      string checkUser;
      string checkPass;
      while (true){
        cout << "Enter your Username: ";
        getline(cin, checkUser);
        cout << "Enter your password: ";
        getline(cin, checkPass);
        if (checkUser == "admin" && checkPass == "admin"){
          while (true){
            char command;
            cout << "Select option:\nA-Clear logdata\nB-Display logdata\nC-Remove User\nQ-Quit\n";
            cin >> command;
            switch (command){
              case 'Q':
              case 'q':{
                return 0;
                       }
              case 'A':
              case 'a':{
                while(true){
                  cout << "Are you sure? y/N" << endl;
                  command='\0';
                  cin >> command;
                  if(command == 'y' || command == 'Y'){
                    ofstream file ("logdata.txt");
                    file << "";
                    break;
                  }
                  else if (command == 'n' || command =='N') break;
                }
                break;
                      }
              case 'B':
              case 'b':{
                cout << endl;
                string temp;
                ifstream input;
                input.open ("logdata.txt", ios::in);
                if (input.is_open()){
                  while (getline(input, temp)){
                    database.push_back(temp);
                  }
                }
                else{
                  cout << "database error" << endl;
                  return 0;
                }
                for (string i : database){
                  cout << i << endl;
                }
                break;
                       }
              case 'C':
              case 'c':{
                string del;
                string idin;
                cout << "Please introduce user's ID:\n(0 to cancel)\n\n";
                cin >> idin;
                del = "ID" + idin;
                for (int i=0; i<database.size(); i++){
                  if (database[i]==del){
                    database.erase(database.begin()+i, database.begin()+i+5);
                    ofstream file ("logdata.txt");
                    for (int y=0; y<database.size(); y++){
                      file << database[y] << endl;
                    }
                    file.close();
                    break;
                  }
                }
                break;
                       }
            }
          }
        }
        string temp;
        ifstream input;
        input.open ("logdata.txt", ios::in);
        if (input.is_open()){
          while (getline(input, temp)){
            database.push_back(temp);
          }
        }
        else{
          cout << "database error" << endl;
          return 0;
        }
        string checker = "ID" + to_string(id_cal(checkUser));
        int idw=0;
        for (int i=0; i<database.size(); i++){
          if (database[i] == checker){
            idw++;
            string lane = database[i+2];
            string crypt;
            for (int z=0; z<lane.size(); z++){
              crypt += lane[z];
              if(crypt=="Password (encrypted): "){
                crypt = "";
              }
            }
            if (checkPass == decryptor(crypt)){
              char useropt; 
              bool clockin=false;
              string wstart;
              cout << "Successfully logged in.\n";
              while(true){
                cout << "Please select one of the following options:\nA-Clock in\nB-Clock out\nQ-Quit\n";
                cin >> useropt;
                switch (useropt){
                  case 'a':
                  case 'A':{
                    clockin=true;
                    auto timein = chrono::system_clock::to_time_t(chrono::system_clock::now());
                    cout << endl << "\tYou've clocked in at " << ctime(&timein) << endl << endl;
                    wstart = ctime(&timein);
                    break;
                           }
                  case 'b':
                  case 'B':{
                    if (wstart==""){
                      cout << "You have not clocked in!\n";
                      break;
                    }
                    else{
                      string wstop = worktime(wstart);
                      cout << wstop << endl;
                      break;
                    }
                           }
                  case 'q':
                  case 'Q':{
                    return 0;
                           }
                }
              }
            }
          }
        }
        if (idw==0) cout << "That username does not exist. Please try again." << endl;
        else if (idw==1) cout <<  "Wrong Password. Please try again." << endl;
      }
      break;
              }
    case 'Q':
    case 'q':{ // Provided Quit.
      cout << "Quitting program..." << endl;
      return 0;
      break;
             }
  }
  return 0;
}

  



