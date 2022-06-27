#include <iostream>
#include <conio.h>

using namespace std;

struct storage {
    int index;
    int capacity = 0;
    bool isEmpty = true;
};
typedef storage source;
typedef storage destination;

struct cell {
    long int price = 0;
    int amount = 0;
    bool isEmpty = true;
};

struct table {
    source supply[100];
    destination demand[100];
    cell shipment[100][100];
};

long int z(table table_) {
    long int result = 0;
    int n_source = 0;
    int n_destination = 0;
    while (!table_.supply[n_source].isEmpty) {
        n_source++;
    }
    while (!table_.demand[n_destination].isEmpty) {
        n_destination++;
    }

    for(int i=0; i<n_source; i++) {
        for(int j=0; j<n_destination ; j++) {
            result += table_.shipment[i][j].amount * table_.shipment[i][j].price;
        }
    }
    return result;
}

void show_table(table table_) {
    int n_source = 0;
    int n_destination = 0;
    while (!table_.supply[n_source].isEmpty) {
        n_source++;
    }
    while (!table_.demand[n_destination].isEmpty) {
        n_destination++;
    }

    cout << "Factory : ";
    for(int i=0; i<n_source; i++) {
        cout << "\t" << table_.supply[i].capacity;
    }
    cout << endl;
    cout << "Warehouse : ";
    for(int i=0; i<n_destination; i++) {
        cout << "\t" << table_.demand[i].capacity;
    }
    cout << endl << endl;

    for(int i=0; i<n_source; i++) {
        for(int j=0; j<n_destination; j++){
            cout << "|\t" << table_.shipment[i][j].price << "\t";
        }
        cout << "||\t" << table_.supply[i].capacity;
        cout << endl;
        for(int j=0; j<n_destination; j++){
            cout << "|\t" << table_.shipment[i][j].amount << "\t";
        }
        cout << "||\t" << endl;
        for(int j=0; j<n_destination; j++){
            cout << "|\t" <<"----"<< "\t";
        }
        cout << "||\t----" << endl;
    }
    for(int j=0; j<n_destination; j++) {
        cout << "|\t\t";
    }
    cout << "||" << endl;
    for(int j=0; j<n_destination; j++) {
        cout << "|\t" << table_.demand[j].capacity << "\t";
    }
    cout << "||\tZ = " << z(table_);

}

table initial_table() {
    table result;
    int n_source, n_destination;
    cout << "n_source : "; cin >> n_source;
    cout << "n_destinantion : "; cin >> n_destination;

    for (int i = 0; i < n_source; i++) {
        cout << "Factory [" << i << "] : " ; cin >> result.supply[i].capacity;
        result.supply[i].index = i;
        result.supply[i].isEmpty = false;
    }
    for (int i = 0; i < n_destination; i++) {
        cout << "Warehouse [" << i << "] : " ; cin >> result.demand[i].capacity;
        result.demand[i].index = i;
        result.demand[i].isEmpty = false;
    }

    for(int i=0; i < n_source; i++) {
        for(int j=0; j < n_destination; j++) {
            cout << "Cell " <<"["<<i <<"]["<< j <<"]"<< "[price] : " ; cin >> result.shipment[i][j].price;
            result.shipment[i][j].isEmpty = false;
        }
    }
    show_table(result);
    return result;
}

int main()
{
    table model;
    model = initial_table();
    return 0;
}