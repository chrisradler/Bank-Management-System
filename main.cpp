/******************************************************************************
Note: This program is practice project of what I have been learning,
Its basically  a very simple bank system with many assumpsutions and limited functionalities.
I'm  Practicing Parallel Vectors , So I'm not using structures or classes or any OOP.


*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<ctime>


using namespace std;


/*
--- Method id 1: loadClient---
This method is to fill the clients information from clients.txt and fill in to the 
according vectors. */
void loadClient(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    fstream fin("Clients.txt");
/*we do not want to include the first row of clients.txt so we will create a 
bool so we can check if it is the first row. */
    bool isFirstRow =true;
    
    string tempId;
    string tempPassword;
    string tempName;
    int tempBalance;
    string tempStatus;
//this loop will fill the data into the according vectors.
    while (! fin.eof()){
        if(isFirstRow == false){
            
            fin >> tempId; 
            id.push_back(tempId);
         
            fin.ignore();
            getline(fin, tempPassword, ':');
            password.push_back(tempPassword);
            
            getline(fin, tempName, '#');
            name.push_back(tempName);
            
            string tempVariable;
            getline(fin, tempVariable, ',');
            tempBalance = stoi(tempVariable);
            balance.push_back(tempBalance);
         
            getline(fin, tempStatus);
            status.push_back(tempStatus);
         
        }
//skip first row in clients.txt
        else{
            string row1;
            getline(fin ,row1);
            isFirstRow = false;
        }
    }
}
/* --- method id 2: displayClient --- 
------ this method will display clients.txt on the console.
*/
void displayClient(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    for (int x=0;x<id.size();x++){
        cout << id[x] << password[x]<< name[x] << balance[x] << status[x] << endl;
    }
}

/* --- method id 3: loadAdmin ---
------ This method will load the data in admin.txt into the according vectors.
*/
void loadAdmin(vector <string> &adminID, vector <string> &adminPassword, vector <string> &adminName){
    ifstream fin("Admin.txt");
    
    string tempID;
    string tempPassword;
    string tempName;
    bool firstRow = true;
    
    while (! fin.eof()){
        //first row of Admin.txt are titles so we want to skip that row.
        if (firstRow == false){
            
            getline(fin , tempID, ',');
            adminID.push_back(tempID);
            
            getline(fin, tempPassword, ',');
            adminPassword.push_back(tempPassword);
            
            getline(fin, tempName);
            adminName.push_back(tempName);
            
        }
        else {
            firstRow = false;
            string temp;
            getline(fin, temp);
            
        }
    }
}

/*
----- method id 4: displayAdmin -----
----- This method will display admin.txt onto the console.
*/
void displayAdmin(vector <string> &adminID, vector <string> &adminPassword, vector <string> &adminName){
    for (int x=0;x<adminID.size();x++){
        cout << adminID[x] << adminPassword[x]<< adminName[x] << endl;
    }
}



/*
------ Method 5: clientLogin ------
------ The method will take input for the clients id and password and then will return true or false 
      based on if the credentials are valid or not.
*/
bool clientLogin(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status,string tempUsername,string tempPassword){
    bool isFound = false;
    
    //if login was successful
    for (int x=0;x<id.size();x++){
        if (tempUsername == id[x] and tempPassword == password[x]){
            cout << "Login successful" << endl;
            cout << "------------------------------" << endl;
            isFound = true;
            return true;
            
        }
    }
    //if login was unsuccessful
    if (isFound == false){
        cout << "Login unsuccesful" << endl;
        cout <<"------------------------------" << endl;
        return false;
    }
}
/* 
------- Method 6: adminLogin ------
This method will take input for the admins ID and Password and return true or 
false based on whether the credentials are valid or not.
*/
bool adminLogin(vector <string> &adminID, vector <string> &adminPassword, vector <string> &adminName,string tempID,string tempPassword){
    bool isFound = false;
    
    for (int x=0;x < adminID.size();x++){
        if (tempID == adminID[x] && tempPassword == adminPassword[x]){
            isFound = true;
            return true;
        }
    }
    if (isFound == false){
        return false;
    }
}
/*
------- Method 7: clientFileUpdate -----
This method will update the clients.txt file when called upon.
*/
void clientFileUpdate(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    ofstream fout("Clients.txt");
    fout << "id password:name#balace,status";
    for (int x = 0;x <id.size();x++){
        fout << endl << id[x] << " " << password[x] << ":" << name[x] << "#" << balance[x] << "," << status[x];
    }
    fout.close();
}
/*
------ Method 8: usernameValidation ------
This method will validate whether the clients username is valid or not.
*/
bool usernameValidation(vector <string> &id, string tempUsername){
    // checking if the user name is repeated
    for (int x=0; x<id.size(); x++){
        if (tempUsername == id[x]){
            return false; 
        }
    }
    
    // checking if the user name has any space.
    
    for(int x =0; x<tempUsername.length();x++){
        
        if(tempUsername[x] == ' '){
            return false;
        }
    }
    
    return true;
    
}
/*
------ Method 9: nameValidation ------
This method will validate whether the clients username is valid or not.
*/
//validating whether that name is using any digit or not. Digits are not allowed.
bool nameValidation( string name){
    for (int x=0;x<name.length();x++){
        if (name[x] >= '0' && name[x] <='9'){
            return false ;
        }
    }
    return true ;
}
/*
------ Method 10: passwordValidation ------
This method will validate whether the clients username is valid or not.
*/
bool passwordValidation(string password){
        if (password.length() < 8){
            return false ;
        }
        else{
            bool isDigit = false;
            bool isAlpha = false;
            bool isSpecialChar = false;
            for (int x=0;x<password.length(); x++){
                if (password[x] >= '0' && password[x] <='9'){
                    
                    isDigit = true;
                }
                if(password[x] >= 'A' && password[x] <= 'z'){
                    isAlpha = true;
                }
                
                if(password[x] == ' '){
                    return false;
                }
                
                if(password[x] == '@' || password[x] =='#'||  password[x] == '!' || password[x] =='$' ){
                    isSpecialChar == true;
                }
                
                
            }
            
            if(isDigit == true &&isAlpha == true && isSpecialChar ==true){
                return true;
            }
            else {
                return false;
            }
        }
        
        
    }
/*
------- Method 11: clientSignUp -------
This method will give the client access to sign up and create and account.
*/
void clientSignUp(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    string tempUsername;
    string tempPassword;
    string tempName;
    int tempBalance;
    //status will start at pending because client will need to be approved by admin
    //before getting access
    string tempStatus = "pending";
    
    cout << "-----Client Sign Up ------" << endl;
    do{
        cout << "What is your name? " << endl;
        cin.ignore();
        getline(cin, tempName);
    }while(nameValidation(tempName) == false);
    
    
    //validating the username 
    do{
      cout << "Please enter a username. " << endl;
      getline(cin , tempUsername);
    }while(usernameValidation(id,tempUsername) == false);
    
    do{
        cout << "Please enter a password. " << endl;
        cin >> tempPassword;
    }while(passwordValidation(tempPassword) == false);
    
    cout << "What will be your initial deposit? " << endl;
    cin >> tempBalance;
    cout << "Your current account status is " << tempStatus << endl;
    
    cout << "-------- Sign up Success --------" << endl;
    
    id.push_back(tempUsername);
    password.push_back(tempPassword);
    name.push_back(tempName);
    balance.push_back(tempBalance);
    status.push_back(tempStatus);
    //when client signs up, theyre info will move to PendingClients.txt to be 
    //approved or declined by an admin.
    ofstream fout("PendingClients.txt", ios::app);
    fout <<tempUsername<<" "<< tempPassword<<":"<< tempName <<"#" << tempBalance << "," << tempStatus << endl;
    fout.close();
    
    
}
/*
------ Method 12: history -------
the history function will log all of the transactions made by clients in the 
Log.txt file.
*/
void history(string id,int updatedBalance, int effectedAmount, string operation){
    ofstream fout ("Log.txt", ios::app);
    fout << endl << id << "," << updatedBalance << "," << effectedAmount << "," << operation ;
    fout.close();
}
/*
------ Method 13: depositMoney ------
This method will give the client power to be able to deposit money when 
they are at the clientDashboard.
*/
void depositMoney(vector <string> &id, vector <int> &balance,string loggedInUsername){
    int amount ; 
    cout << "How much do you want to deposit? " << endl;
    cin >> amount ; 
    for (int x = 0; x < id.size();x++){
        if (loggedInUsername == id[x]){
            balance[x] = amount + balance[x];
            cout << "Deposit successful. New balance is " << balance[x] << endl;
            // to log this transcation.
            history(loggedInUsername, balance[x], amount, "Deposit");
        }
    }
}
/*
------- Method 14: withdrawMoney-------
This method will allow the client to be able to withdraw money from 
their account.
*/
void withdrawMoney(vector <string> &id, vector <int> &balance,string loggedInUsername){
    int amount ; 
    cout << "How much money do you want to withdraw? " << endl;
    cin >> amount ; 
    for (int x=0;x<id.size();x++){
        if (loggedInUsername == id[x]){
            balance[x] = balance[x] - amount ;
            cout << "Withdraw successful. Your new balance is " << balance[x] << endl;
            // to log this transcation.
            history(loggedInUsername, balance[x], amount, "Withdraw");
        }
    }
}
/*
------- Method 15: checkBalance-------
This method will allow the client to check their balance.
*/
void checkBalance(vector <string> &id, vector <int> &balance,string loggedInUsername){
    for (int x=0;x<id.size(); x++){
        if (loggedInUsername == id[x]){
            cout << id[x] << " available balance is " << balance[x] << endl;
        }
    }
}
/*
------- Method 16: printStatement-------
This method will allow the client to check their recent transactions that were made.
Example: if the client have deposited or withdrew money recently, and how much.
Then it will write that statement in a new file for the client to view.
*/
void printStatement(string loggedInUsername){
    //filename will be the clients username .txt
    string fileName = loggedInUsername + ".txt";
    ofstream fout(fileName);
    vector <string> id ;
    vector <int> updatedBalance;
    vector <int> effectedAmount;
    vector <string> operation ; 
    string tempId;
    int tempBalance;
    int tempEffectedAmount;
    string tempOperation;
    
    fstream fin("Log.txt");
    //this loop will fill the data into the according vectors.
    while (! fin.eof()) {
        getline(fin, tempId, ',') ;
        id.push_back(tempId);
        
        string temp;
        getline(fin, temp, ',') ;
        tempBalance = stoi(temp);
        updatedBalance.push_back(tempBalance);
        
        string tempVar;
        getline(fin, tempVar, ',') ;
        tempEffectedAmount = stoi(tempVar);
        effectedAmount.push_back(tempEffectedAmount);
        
        getline(fin, tempOperation) ; 
        operation.push_back(tempOperation);
        
    }
    for (int x=0;x<id.size();x++){
        if (loggedInUsername == id[x]){
            //wrtie the statement on the console, and also the seperate txt file. 
            cout << id[x] << "," << updatedBalance[x] << "," << effectedAmount[x] << "," << operation[x] << endl ;  
            fout << id[x] << "," << updatedBalance[x] << "," << effectedAmount[x] << "," << operation[x] << endl ;  
        }
    }
    fout.close();
}
/*
------- Method 17: deleteAccountByClient-------
This method will allow the client to be able to delete its own account.
It will also erase the clients credentials from Clients.txt.
*/
void deleteAccountByClient(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status, string loggedInUsername){
    for (int x = 0; x <id.size(); x++){
        if (id[x] == loggedInUsername){
            id.erase(id.begin() + x);
            password.erase(password.begin() + x);
            name.erase(name.begin() + x);
            balance.erase(balance.begin() + x);
            status.erase(status.begin() + x);
        }
    }
}
/*
------- Method 18: clientUpdatePassword-------
This method will allow the client to be able to update their current password.
*/
void clientUpdatePassword(vector <string> &id, vector <string> &password){
    bool isFound = false;
    string currentPassword ;
    string newPassword;
    cout << "Please enter your current password? " << endl;
    cin >> currentPassword; 
    for (int x=0; x< id.size();x++){
        if (currentPassword == password[x]){
            cout << "Correct!" << endl;
            cout << "Please enter your new password." << endl;
            cin >> newPassword;
            password[x] = newPassword;
            cout << "Password changed successfuly! " << endl;
            isFound = true;
            
        }
    }
        if (isFound == false){
            cout << "Sorry, that is incorrect, please try again." << endl;
        }
}
/*
------- Method 19: clientDashboard-------
This method is a dashboard for when the client is logged in.
The client will be able to perform a number of actions. 
*/
void clientDashboard(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status,string loggedInUsername){
    int clientMenu ; 
    cout << "Welcome " << loggedInUsername << endl;

    while (clientMenu != 0){
        cout << "--------- Dashboard ----------" << endl;
        cout << "Press \n 1) Deposit Money \n 2) Withdrawal Money \n 3) Print Statement \n 4) Check Balance \n 5) Delete Account \n 6) Update Password \n 7) Update Account \n" << endl;
        cout << "------------------------------" << endl;
        cin >> clientMenu ; 
        if (clientMenu == 1){
            depositMoney(id, balance, loggedInUsername);
        }
        else if (clientMenu == 2){
            withdrawMoney(id, balance, loggedInUsername);
        }
        else if (clientMenu == 3){
            printStatement(loggedInUsername);
        }
        else if (clientMenu == 4){
            checkBalance(id, balance, loggedInUsername);
        }
        else if (clientMenu == 5){
            deleteAccountByClient(id, password, name, balance, status, loggedInUsername);
            clientMenu = 0;
        }
        else if (clientMenu == 6){
            clientUpdatePassword(id, password);
        }
        else if (clientMenu == 7){
            clientFileUpdate(id,password,name, balance, status);
        }
        else {
            cout << "Invalid Selection " << endl;
        }
        clientFileUpdate(id, password, name, balance, status);
    }
}
/*
------ Method 20: blockClientAccount ------
This method will give the admin power to be able to block a client account.
*/
void blockClientAccount(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    bool isFound = false ; 
    string temp ;
    cout << "Which client ID do you want to block? " << endl;
    cin >> temp;
    for (int x=0;x< id.size(); x++){
        if (temp == id[x]){
            status[x] = "blocked";
            cout << "Account blocked successfuly." << endl;
            isFound = true;
        }
    }
        if (isFound == false){
            cout << "Please try a different client ID." << endl;
        }
}
/*
------ Method 21: unblockClientAccount ------
This method will give the admin power to be able to unnlock a clients account.
*/
void unblockClientAccount(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    string temp;
    cout << "What client ID are you trying to unblock? " << endl;
    cin >> temp;
    for (int x=0;x<id.size();x++){
        if (temp == id[x]){
            //change client status from working to blocked.
            if (status[x] == "blocked"){
                status[x] = "working" ;
                cout << id[x] << "'s account is now unblocked." << endl;
            }
            else{
                cout << "The account is already working. " << endl;
            }
        }
    }
}
/*
------ Method 22: adminFileUpdate ------
This method will update the admin information.
*/
void adminFileUpdate(vector <string> &adminID, vector <string> &adminPassword, vector <string> &adminName){
    ofstream fout("Admin.txt");
    fout << "ID,Password,Name" ;
    for (int x = 0;x <adminID.size();x++){
        fout << endl << adminID[x] << "," << adminPassword[x] << "," << adminName[x] ;
    }
    fout.close();
}
/*
------ Method 23: deleteAccountByAdmin ------
This method will give the admin the power to delete a client account. and also 
remove from the Clients.txt
*/
void deleteAccountByAdmin(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    string temp ; 
    cout << "Which client ID are you trying to delete? " << endl;
    cin >> temp;
    for (int x = 0; x<id.size(); x++){
        if (id[x] == temp){
            id.erase(id.begin() + x);
            password.erase(password.begin() + x);
            name.erase(name.begin() + x);
            balance.erase(balance.begin() + x);
            status.erase(status.begin() + x);
            cout << "Client deleted successully ?" << endl;
        }
    }
}
/*
------ Method 24: bestClient ------
This method will return the client that has the most money in their balance, and
and the client that has the least money in their balance.
*/
void bestClient(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    for (int x=0;x<id.size();x++){
        for (int y=x+1;y<id.size();y++){
            if (balance[x] < balance[y]){
                // swaping balance
                int temp = balance[x];
                balance[x] = balance[y];
                balance[y] = temp;
                
                // swaping id
                string TempId = id [x];
                id[x] = id[y];
                id[y] = TempId;
                
                // swapping password 
                string tempPassword = password[x];
                password[x] = password[y];
                password[y] = tempPassword;
                
                //swapping names 
                
                string tempName = name[x];
                name[x] = name[y];
                name[y] = tempName ; 
                
                //swapping status
                string tempStatus = status[x];
                status[x] = status[y];
                status[y] = tempStatus ; 
            }
        }
    }
    //display best and worst client.
    cout << id[0] << " is the best client with a balance of " << balance[0] << endl;
    cout << id[id.size()-1] << " is the worst client with a balance of "<< balance[balance.size() -1] << endl;
}
/*
------ Method 25: average ------
This method will return the average amount of money in all of the accounts.
*/
void average(vector <int> balance){
    int add = 0;
    int result ;
    for (int x=0;x<balance.size();x++){
        add = add + balance[x];
    }
    result = add / balance.size();
    cout << "The average of all the accounts in our system is " << result << endl;
}
/*
------ Method 26: printStatement ------
This method will give the client power to be able to print their past transactions 
or their statement.
*/
void printStatementAdmin(vector <string> &id){
    
    string tempUsername ; 
    cout << "Please enter the client's ID " << endl;
    cin >> tempUsername;
    
    bool isFound = false;
    for (int x= 0 ; x<id.size();x++){
        if (tempUsername == id[x]){
            //call printStatement function from previous method.
            printStatement(tempUsername);
            isFound = true;
        }
    }
    
    if(isFound == false){
        cout <<"Inavalid ID  "<<endl;
    }
}
/*
------ Method 27: pendingRequests ------
This method will give the admin the ability to check the pending requests from 
new clients. The pending requests will be written in the PendingClients.txt
for the admin to approve or decline the request.
*/
void pendingRequests(){
    vector <string> id ;
    vector <string> tempPassword;
    vector <string> tempName;
    vector <int> tempBalance ;
    vector <string> tempStatus ; 
    string tempUsername ; 
    string password1;
    string name1;
    int balance;
    string status ;
    //read from the PendingClients.txt and store the information in according vector
    fstream fin ("PendingClients.txt");
    while (fin >> tempUsername ){
        id.push_back(tempUsername);

        fin.ignore();
        getline(fin, password1, ':');
        tempPassword.push_back(password1);
        
        getline(fin, name1, '#');
        tempName.push_back(name1);
        
        string temp;
        getline(fin, temp, ',');
        balance = stoi(temp);
        tempBalance.push_back(balance);
        
        getline(fin, status);
        tempStatus.push_back(status);
    }
    //display pending clients on the console.
    for (int x=0; x<id.size();x++){
        cout << id[x] << tempPassword[x] << tempName[x] << tempBalance[x] << tempStatus[x] << endl;
    }
}
/*
------ Method 28: approveOrDeclineRequests ------
This method will give the admin power to approve or decline the new client requests.
*/
void approveOrDeclineRequests(vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status){
    int temp ; 
    cout << "Press \n 1) Approve requests \n 2) Decline requests " << endl;
    cin >> temp ; 
    if (temp == 1){
        //load the data from PendingClients.txt and save into according variables
        //in order to write approved clients in Clients.txt.
        string tempUsername ; 
        string tempPassword;
        string tempName;
        int tempBalance;
        string tempStatus ; 
        //read from PendingClients.txt and push info back into according vectors.
        fstream fin("PendingClients.txt");
        while (fin >> tempUsername){
            id.push_back(tempUsername);

            fin.ignore();
            getline(fin, tempPassword, ':');
            password.push_back(tempPassword);
        
            getline(fin, tempName, '#');
            name.push_back(tempName);
        
            string temp;
            getline(fin, temp, ',');
            tempBalance = stoi(temp);
            balance.push_back(tempBalance);
        
            getline(fin,tempStatus) ;
            status.push_back("working");
        }
        //write the data from the variables to clients.txt because they were approved.
        ofstream fout ("Clients.txt", ios::app);
        fout << endl << tempUsername<<" "<< tempPassword<<":"<< tempName <<"#" << tempBalance << "," << tempStatus ;
        fout.close(); 
        //erase the pending clients from PendingClients.txt because they were approved.
        ofstream fout2("PendingClients.txt");
        fout2<<"";
        fout2.close();
        }
    else if (temp == 2){
        //erase the pending clients from PendingClients.txt because they were declined.
        ofstream fout("PendingClients.txt");
        fout<<"";
        fout.close();
        cout << " ---- All new requests moved to bin  -----"<<endl;
    }
    else {
        cout << "Invalid Selection" << endl;
    }
}
/*
------ Method 29: adminDashboard ------
This method will give display the actions that the admins are able to perform.
*/
void adminDashboard(vector <string> &adminID, vector <string> &adminPassword, vector <string> &adminName,vector <string> &id, vector <string> &password, vector <string> &name, vector <int> &balance, vector <string> &status, string adminLoggedInUsername){
    int adminMenu ; 
    
    while (adminMenu !=0){
        cout << "-------Admin Dashboard--------" << endl;
        cout << "Press \n 1) Block an Account \n 2) print a statement  \n 3) Unblock an Account \n 4) Delete an account"
        <<"\n 5) Find Best and Worst Clients \n 6) Find average balance \n 7) See pending requests \n 8) Approve or Decline Request \n 9) Display all present accounts" << endl;
        cout << "------------------------------" << endl;
        cin >> adminMenu;
        if (adminMenu == 1) {
            blockClientAccount(id, password, name, balance, status);
            clientFileUpdate(id, password, name, balance, status);
        }
        else if (adminMenu ==2) {
            printStatementAdmin(id);
        }
        else if (adminMenu ==3) {
            unblockClientAccount(id, password, name, balance, status);
            clientFileUpdate(id, password, name, balance, status);
        }
        else if (adminMenu == 4) {
            deleteAccountByAdmin(id, password, name, balance, status);
            clientFileUpdate(id, password, name, balance, status);
        }
        else if (adminMenu == 5) {
            bestClient(id, password, name, balance, status);
        }
        else if (adminMenu == 6){
            average(balance);
        }
        else if (adminMenu== 7){
            pendingRequests();
        }
        else if (adminMenu == 8) {
            approveOrDeclineRequests(id, password, name, balance, status);
        }
        else if (adminMenu == 9){
            displayClient(id, password, name, balance, status);
        }
        else {
            cout << "Invalid Selection" << endl;
        }
        
    }
    


}
int main()
{
// The below vectors are representing the attributes of a Client
vector <string> id;
vector <string> password;
vector <string> name;
vector <int> balance;
vector <string> status;
//the below vectors are representing the admin attributes.
vector <string> adminID;
vector <string> adminPassword;
vector <string> adminName;


int sel =-1;
loadClient(id, password, name, balance, status);
//loading data from the file into associated vectors.
loadAdmin(adminID, adminPassword, adminName);
do{
    cout << "1)Admin \n2)Client\0)exit\n select >> " << endl;
    cin >> sel;
    if(sel ==1){
        string adminLoggedInUsername;
        string tempPassword;
        cout << "-------- Admin Login ---------" << endl;
        cout << "What is your admin id? " << endl;
        cin >> adminLoggedInUsername;
        cout << "What is your password? " << endl;
        cin >> tempPassword;
        cout << "------------------------------" << endl;
        //if adminLogin is true then proceed to the adminLogin dashboard.
        if(adminLogin(adminID, adminPassword, adminName,adminLoggedInUsername,tempPassword) == true){
            cout <<"Welcome "<<adminLoggedInUsername<<endl;
            adminDashboard(adminID, adminPassword, adminName,id, password, name, balance, status, adminLoggedInUsername);
            
        }
        else{
            cout <<"Invalid selction "<<endl;
        }
        
    }
    else if(sel ==2){
        int tempLogin ;
        cout << "Press\n 1) Login \n 2) Signup ? " << endl;
        cin >> tempLogin;
        if (tempLogin == 1){
            string tempUsername;
            string tempPassword;
            cout << "------- Client Login ---------" << endl;
            cout << "What is your username? " << endl;
            cin >> tempUsername;
            cout << "what is your password? " << endl;
            cin >> tempPassword;
            //make sure the username and password credentials are correct.
            if (clientLogin(id, password, name, balance, status, tempUsername, tempPassword) == true){
               //check to make sure when the client is logging in, the account is not blocked
               bool isGood =true; 
                for (int x=0;x<id.size(); x++){
                    if (tempUsername == id[x]){
                        if (status[x] == "blocked"){
                            cout << "Your account has been blocked." << endl;
                            isGood =false;
                        }
                    }
                }
                //if credentials are correct and the account is not blocked,
                //show them the clientDashboard.
                if(isGood==true){
                   clientDashboard(id, password, name, balance, status, tempUsername);
                }
            }
        }
            else if (tempLogin == 2){
                clientSignUp(id, password, name, balance, status);
        }
            else {
                cout << "invalid selection" << endl;
            }
    
        
    }
    else{
        
        cout <<"invalid selection"<<endl;
    }
    
}while(sel != 0);


    return 0;
}
