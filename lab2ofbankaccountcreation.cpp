#include <iostream>
#include <string>
using namespace std;

class bankaccountclass {
private:
    int accountnoofuser; 
    string useridentityname;
    float moneybalanceofuser;
    bool whatistheconditionactiveorinactivehuu; 

public:
//tis is difult constructor named bankaccountclass made by student name swornimpandey kan082bct092
    bankaccountclass() {
        this->accountnoofuser = 0; 
        this->useridentityname = "NULL"; 
        this->moneybalanceofuser = 0.0f; 
        this->whatistheconditionactiveorinactivehuu = false;
    }
    //this is parameterized constructor name bankaccountclass made by student name swornimpandey kan082bct092
    bankaccountclass(int number, string name, float balance, bool status) {
        this->accountnoofuser = number; 
        this->useridentityname = name; 
        this->moneybalanceofuser = balance; 
        this->whatistheconditionactiveorinactivehuu = status;
    }
    //this is distructor of this calss which is made nonother than by swornimpandey kan082bct092
    ~bankaccountclass() {}
//this is the fun that return the account noofuser .....................................
    int getAccountNumber() { 
        return this->accountnoofuser; 
    }
// yesle user active xa ki nai return garxa tara yo pani swornim la nai banako ho so kan082bct092

    bool getStatus() { 
        return this->whatistheconditionactiveorinactivehuu; 
    }
//yo ho nonother than setting data to calss parameter accno balance name ...and yo made by swornimpandey if anyy thhis is copied from this then the other is copied and i have exclusive copywrite issue on  this lab 2 of banksworni.cpp thankyou 

    void setData(int number, string name, float balance, bool status) {
        this->accountnoofuser = number; 
        this->useridentityname = name; 
        this->moneybalanceofuser = balance; 
        this->whatistheconditionactiveorinactivehuu = status;
    }
// this display tha output of account detail of useer active and whose data is set in this program

    void display() {
        cout << "\n====================Account Details==========================================\nName           : " << this->useridentityname 
             << "\nAccount Number : " << this->accountnoofuser << "\nBalance        : Nrs" << this->moneybalanceofuser 
             << "\nStatus         : " << (this->whatistheconditionactiveorinactivehuu ? "Active" : "Inactive/Settled") << "\n-----------------------\n";
    }
//this will transfer money i mean deposit money to this account (this is done for uniqueness in this program

    void deposit(float amount) {
        if (this->whatistheconditionactiveorinactivehuu && amount > 0) {
            this->moneybalanceofuser += amount;
            cout << "Nrs" << amount << " deposited successfully.\n";
        } else {
            cout << "failed to deposit\n";
        }
    }
// my name is swornim pandey of bct b  and this function withdraws the caash on hand of this accouunt (same reason for uniqueness  in program)

    bool withdraw(float amount) {
        if (!this->whatistheconditionactiveorinactivehuu || amount <= 0 || amount > this->moneybalanceofuser) {
            cout << "Transaction failed\n";
            return false;
        }
        this->moneybalanceofuser -= amount;
        cout << "Nrs" << amount << " withdrawn success\n";
        return true;
    }
// thhis transfer money to another accouunt from this account
    void transfer(bankaccountclass &recipient, float amount) {
        if (this->whatistheconditionactiveorinactivehuu && recipient.getStatus() && this->withdraw(amount)) {
            recipient.moneybalanceofuser += amount;
            cout << "Transferred Nrs" << amount << " to Account #" << recipient.getAccountNumber() << " successfully.\n";
        } else {
            cout << "Transfer failed.\n";
        }
    }
//this return the remaning balance of user

    void settle() {
        if (!this->whatistheconditionactiveorinactivehuu) { 
            cout << "Account is already settled\n"; 
            return; 
        }
        cout << "Settling account Returning remaining balance of Nrs" << this->moneybalanceofuser << " to " << this->useridentityname << "\n";
        this->moneybalanceofuser = 0.0f; 
        this->whatistheconditionactiveorinactivehuu = false;
    }
};
// hehehaha it finds the accno in array 
int findAccount(bankaccountclass accounts[], int count, int number) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].getAccountNumber() == number) {
            return i;
        }
    }
    return -1;
}
//real program bigins in mane ................

int main() {
    bankaccountclass accounts[100];
    int total = 0, choice, number, count;
    float amount;

    cout << "Welcome to Kec-Bank\n";
    while (true) {
        cout << "\n===============================" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Transfer" << endl;
        cout << "5. Display" << endl;
        cout << "6. Settle" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 7) {
            break;
        }

        if (choice == 1) {
            if (total >= 200) { 
                cout << "Bank capacity is maximum no more account can be created!\n"; 
                continue; 
            }
            string name; 
            float balance;
            cout << "Enter name for creating account: "; 
            cin.ignore(); 
            getline(cin, name);
            cout << "Enter initial money deposit: Nrs"; 
            cin >> balance;
            accounts[total].setData(total + 1, name, balance, true);
            accounts[total++].display();
            continue;
        }

        cout << "Enter Account Number: "; 
        cin >> number;
        count = findAccount(accounts, total, number);
        if (count == -1) { 
            cout << "Account not found.\n"; 
            continue; 
        }

        switch (choice) {
            case 2: 
                cout << "Enter amount: "; 
                cin >> amount; 
                accounts[count].withdraw(amount); 
                break;
            case 3: 
                cout << "Enter amount: "; 
                cin >> amount; 
                accounts[count].deposit(amount); 
                break;
            case 4: {
                cout << "Enter Recipient Account Number: "; 
                int recipientNumber; 
                cin >> recipientNumber;
                int recipientNumberFound = findAccount(accounts, total, recipientNumber);
                if (recipientNumberFound != -1) {
                    cout << "Enter transfer amount: Nrs"; 
                    cin >> amount;
                    accounts[count].transfer(accounts[recipientNumberFound], amount);
                } else {
                    cout << "Recipient account not found.\n";
                }
                break;
            }
            case 5: 
                accounts[count].display(); 
                break;
            case 6: 
                accounts[count].settle(); 
                break;
            default: 
                cout << "Invalid numchoosed\n";
        }
    }
    return 0;
}
