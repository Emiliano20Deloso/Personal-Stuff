#include <iostream>
#include <fstream>
using namespace std;

 
class digital_bank {
private:
    string users[10] = {"Laura231", "RonnyCL8", "Hect0r", "R1ch4rd", "T1m", "St3v3", "W4ll4c3", "Tonny948", "Peter542", "4lonso33"};
    string password[10] = {"3451", "123", "312", "931", "Richard", "HItim", "934", "12345", "Ol56", "4ad2"};
    double money_bank[10] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
public:
void digi(string username, string passwrd) { 
bool loggedIn = false;
int u;
for (u = 0; u < 10; ++u) {
    if (username == users[u] && passwrd == password[u]) {
        cout << "SUCCESSFUL LOG IN" << endl;
        loggedIn = true;
        break;
            }
        }
            if (!loggedIn) {
                cout << "INVALID USERNAME OR PASSWORD" << endl;
                exit(0);
        }
    }
void deposit(string username){
int u;
float depo;
    for (u=0; u <10; u++){
        if(username == users [u]){
            cout<<"You have selected the deposit option"<<endl;
            cout<<"Digit the amount of money you want to deposit:"<<endl;
            cin>>depo;
            money_bank[u]= depo + money_bank[u];
            break;
            }
                if (depo<0){
                    cout<<"Invalid"<<endl;
                    exit(0);
        }

    }

}
//void transf
void txt(string username) {
int u;
for (u = 0; u < 10; ++u) {
    if (username == users[u]) {
    float I = money_bank[u];
    ofstream data_bank_user;
    data_bank_user.open("Money.txt"); 
    data_bank_user << "Hello " << username << endl;
    data_bank_user << "Thanks for choosing us as your digital bank" << endl;
    data_bank_user << "Soon we'll increment our percentage of" << endl;
    data_bank_user << "Your total money in our digital bank is an amount of " << I << endl;
    data_bank_user.close(); 
break;
    }
    }
}

void acc_bal(string username) {
int u;
    for (u = 0; u < 10; ++u) {
        if (username == users[u]) {
            float I = money_bank[u];
            cout << "Account balance is: " << I << endl;
            break;
    }
}
int bal;
    cout << "Do you want to print your account balance? (1 for yes, 0 for no)" << endl;
    cin >> bal;
    if (bal == 1) {
        txt(username);
        }
        if (bal == 0) {
            } 
                else {
                    cout << "Invalid input" << endl;
                }
    }
void transf(string username) {
    int u;
    int k;
    for (u = 0; u < 10; ++u) {
        if (username == users[u]) {
            string username2;
            cout << "Please write the account in which you want to make a transference" << endl;
            cin >> username2;
            for (k = 0; k < 10; ++k) {
                if (username2 == users[k]) {
                    float amount;
                    cout << "Digit the amount of money you want to transfer into account " << users[k] << endl;
                    cin >> amount;
                        if (amount <= money_bank[u]) {
                             money_bank[u] = money_bank[u] - amount;
                             money_bank[k] = money_bank[k] + amount;
                            cout << "SUCCESSFUL TRANSFERENCE" << endl;
                            } 
                                else {
                                    cout << "INSUFFICIENT FUNDS" << endl;
                                }
                                    if (username2 != users[k]) {
                                        cout << "NON-EXISTENT ACCOUNT" << endl;
                                        exit(0);
                                        }
         }
        }
    }
        }
}

};

class Shop {
public:
//grocerie
    string productst1[10] = {"Milk", "Eggs", "Jam", "Tomatoes", "Orange Juice", "Lettuce", "Cereal", "Rice", "Onions", "Oil"};
    float pricest1[10] = {3.00, 4.25, 4.75, 2.00, 5.75, 1.10, 6.20, 2.50, 0.85, 4.80};
    //best buy
    string productst2[10] ={};
    float pricest2[10] ={};
    //H&M
    string productst3[10] ={};
    float pricest3[10] ={};
    //car shop
    string productst4[10] ={};
    float pricest4[10] ={};
    void show1() {
        cout << "Welcome to Grosseries Shop \n";
        cout << "We have plenty of products in stock, please select the ones from your election: \n";

        for (int i = 0; i < 10; ++i) {
            cout << i + 1 << ". " << productst1[i] <<": "<<pricest1[i]<<endl;
        }
    }

    void buyProduct(int selection) {
            if (selection >= 1 && selection <= 10) {
                cout << "You have selected " << productst1[selection - 1] << endl;
                //because is an array 0 to 9 but there are 10 values
                cout << "Price: $" << pricest1[selection - 1] << endl;

            //money_bank[u]= money_bank[u]-pricest1[productss - 1]
        } else {
            cout << "You have selected an invalid product" << endl;
        }
        
    }
};


int main() {
    digital_bank digita;
    Shop shop;

    string username;
    cout << "USERNAME:" << endl;
    cin >> username;

    string paswrd;
    cout << "PASSWORD:" << endl;
    cin >> paswrd;

    digita.digi(username, paswrd);
    int selec;
do {
        cout << "1) Buy in stores" << endl;
        cout << "2) Account balance" << endl;
        cout << "3) Make a transference" << endl;
        cout << "4) Make a deposit" << endl;
        cout << "5) Log out" << endl;
        cout << "6) N/A" << endl;
        cout << "7) Quit" << endl;
        cout << "Select one option please: ";
        cin >> selec;

        switch (selec) {
            case 1:
                cout << "In which store do you want to buy" << endl;
                cout << "1) groceries shop" << endl;
                cout << "2) Best buy" << endl;
                int selec2;
                cout << "Select one store please:";
                cin >> selec2;
                switch (selec2) {
                    case 1:
                        shop.show1();

                        int selection;
                        cout << "Choose the product: ";
                        cin >> selection;

                        shop.buyProduct(selection);
                        break;
                    case 2:
                        cout << "best buy" << endl;
                        break;
                }
                break;
            case 2:
                digita.acc_bal(username);
                break;
            case 3:
            digita.transf(username);
                break;
            case 4:
                digita.deposit(username);
                break;
            case 5:
                cout << "LOGGED OUT SUCCESSFULLY" << endl;
                break;
            case 6:
            cout<<"N/A"<<endl;
            break;
            case 7:
            cout<<"Have a nice day, thank you for choosing us as your bank, see you next time."<<endl;
            exit(0);
            break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (selec != 8);


    return 0;
}


