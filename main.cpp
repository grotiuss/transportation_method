#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <stdlib.h>

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
    int x;
    int y;
    int amount = 0;
    bool isEmpty = true;
};

struct table {
    source supply[100];
    destination demand[100];
    cell shipment[100][100];
};

int count_storage(table table_, int supp_dem = 0) {
    int result = 0;
    switch (supp_dem) {
        case 0 :
            while (!table_.supply[result].isEmpty) {
                result++;
            }
            break;
        case 1 :
            while (!table_.demand[result].isEmpty) {
                result++;
            }
            break;
    }
    return result;
}

int count_storage_capacity(table table_, int supp_dem = 0) {
    int result = 0;
    int n = count_storage(table_, supp_dem);
    switch(supp_dem) {
        case 0 :
            for (int i = 0; i <= n; i++) {
                result += table_.supply[i].capacity;
            }
            break;
        case 1 :
            for (int i = 0; i <= n; i++) {
                result += table_.demand[i].capacity;
            }
            break;
    }
    return result;
}


bool balance_checking(table table_) {
    if(count_storage_capacity(table_, 0) == count_storage_capacity(table_, 1))
        return true;
    else
        return false;
}

cell cell_arround(cell shipment_ ,table table_, int direction = 0) {
    int x = shipment_.x;
    int y = shipment_.y;

    int n_source = count_storage(table_, 0);
    int n_destination = count_storage(table_, 1);
    cell empty;

    switch (direction) {
        case 0 : // atas
            if (x == 0)
                return empty; 
            x--;
            break;
        case 1 : // bawah
            if (x == n_source)
                return empty;
            x++;
            break;
        case 2 : // kiri
            if (y == 0)
                return empty;
            y--;
            break;
        default : // kanan
            if (y == n_destination)
                return empty;
            y++;
    }
    return table_.shipment[x][y];
}

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

void title() {
    cout << "======================================================" << endl;
    cout << "======== TRANSPORTATION METHOD =======================" << endl;
    cout << "======================================================" << endl;
    cout << "                                   Created by grotiuss" << endl << endl;
}

void header (string text = "lalala") {
    title();
    cout << text.length();
}

void footer() {
    cout << endl << endl << "Created by. Grotius" << endl;
}

void show_table(table table_, string table_name = "") {
    int width = 15;
    int n_source = 0;
    int n_destination = 0;
    while (!table_.supply[n_source].isEmpty) {
        n_source++;
    }
    while (!table_.demand[n_destination].isEmpty) {
        n_destination++;
    }

    cout << table_name <<endl;
    for (int j=0; j<(n_destination + 1); j++) {
        cout << setfill('=') << left << setw(width) << "";
    }
    cout << endl;
    for (int i=0; i<n_source; i++) {
        for (int j=0; j<n_destination; j++) {
            cout  << setfill(' ') << left << setw(width) << "| " + to_string(table_.shipment[i][j].price);
        }
        cout << setfill(' ') << left << setw(width) << "|| " + to_string(table_.supply[i].capacity);
        cout << endl;
        for (int j=0; j<n_destination; j++) {
            cout << setfill(' ') << left << setw(width) << "| " + to_string(table_.shipment[i][j].amount);
        }
        cout << setfill(' ') << left << setw(width) << "|| ";
        cout << endl;
        for (int j=0; j<(n_destination + 1); j++) {
            if (n_source == (i+1)) {
                cout << setfill('=') << left << setw(width) << "";
            } else {
                cout << setfill('-') << left << setw(width) << "";
            }
        }
        cout << endl;
    }
    for (int j=0; j<n_destination; j++) {
        cout << setfill(' ') << left << setw(width) << "| " + to_string(table_.demand[j].capacity);
    }
    cout << setfill(' ') << left << setw(width) << "|| Z = " + to_string(z(table_));
    cout <<endl;

    for (int j=0; j<(n_destination); j++) {
        cout << setfill(' ') << left << setw(width) << "| ";
    }
    cout << setfill(' ') << left << setw(width) << "|| ";
    cout << endl;
    for (int j=0; j<(n_destination + 1); j++) {
        cout << setfill('=') << left << setw(width) << "";
    }
    cout << endl;
}

table initial_table() {
    bool isBalance = false;
    table result, result_;
    int n_source, n_destination;
    while (!isBalance) {
        system("CLS");
        title();
        result = result_;
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

        isBalance = balance_checking(result);
    }

    for(int i=0; i < n_source; i++) {
        for(int j=0; j < n_destination; j++) {
            cout << "Cell " <<"["<<i <<"]["<< j <<"]"<< "[price] : " ; cin >> result.shipment[i][j].price;
            result.shipment[i][j].x = i;
            result.shipment[i][j].y = j;
            result.shipment[i][j].isEmpty = false;
        }
    }
    return result;
}

// Initial state
int min_max (int a, int b, int param = 0) {
    if (param == 0) { // min
        if (a < b) {
            return a;
        } else {
            return b;
        }
    } else {
        if (a > b) { // max
            return a;
        } else {
            return b;
        }
    }
}

table nwc (table table_) {
    cout << endl;

    table result = table_;
    int n_source = count_storage(result, 0 );
    int n_destination = count_storage(result, 1);

    int i = 0;
    int j = 0;
    while (i < n_source && j < n_destination) {
        int input = min_max(result.supply[i].capacity, result.demand[j].capacity);
        result.shipment[i][j].amount = input;
        result.supply[i].capacity = result.supply[i].capacity - input;
        result.demand[j].capacity = result.demand[j].capacity - input;
        if (result.supply[i].capacity == 0) {
            i++;
        }
        if (result.demand[j].capacity == 0) {
            j++;
        }
    }

    show_table(result, "North West Corner");
    return result;
}

table lcm (table table_) {
    cout << endl;

    table result = table_;
    show_table(result, "Least Cost Method");
    return result;
}

//Iterations
cell stepping_stone_find_ (cell shipment_, table table_, int direction = 0, int index = 0) {
    int n_source = count_storage(table_, 0);
    int n_destination = count_storage(table_, 1);

    cell empty, branch_;
    cell branch[min_max(n_source, n_destination, 1)];
    int count = 0;
    branch_ = shipment_;
    while(!branch_.isEmpty) {
        branch_ = cell_arround(branch_, table_, direction);
        if(branch_.amount != 0 && branch_.isEmpty == false) {
            branch[count] = branch_;
            count  ++;
        }
    }
    
    if (index >= count) {
        return empty;
    } else {
        return branch[index];
    }
}

cell stepping_stone_find(cell shipment_, table table_, int direction = 0) {
    int result_i = shipment_.x;
    int result_j = shipment_.y;
    cell empty;

    switch (direction) {
        case 0: // atas
            if (result_i == 0)
                return empty;
            result_i --;
            while (table_.shipment[result_i][result_j].amount == 0 && result_i > 0) {
                result_i --;
            }
            if (table_.shipment[result_i][result_j].amount != 0) {
                return table_.shipment[result_i][result_j];
            } else {
                return empty;
            }
            break;
        case 1: // bawah
            if (result_i == count_storage(table_, 0))
                return empty;
            result_i ++;
            while (table_.shipment[result_i][result_j].amount == 0 && result_i < count_storage(table_, 0)) {
                result_i ++;
            }
            if (table_.shipment[result_i][result_j].amount != 0) {
                return table_.shipment[result_i][result_j];
            } else {
                return empty;
            }
            break;
        case 2: // kiri
            if(result_j == 0)
                return empty;
            result_j --;
            while (table_.shipment[result_i][result_j].amount == 0 && result_j > 0) {
                result_j --;
            }
            if (table_.shipment[result_i][result_j].amount != 0) {
                return table_.shipment[result_i][result_j];
            } else {
                return empty;
            }
            break;
        case 3: // kanan
            if(result_j == count_storage(table_, 1))
                return empty;
            result_j ++;
            while (table_.shipment[result_i][result_j].amount == 0 && result_j < count_storage(table_, 1)) {
                result_j ++;
            }
            if (table_.shipment[result_i][result_j].amount != 0) {
                return table_.shipment[result_i][result_j];
            } else {
                return empty;
            }
            break;
        default:
            return empty;
    }
}



// table stepping_stone_find_cycle(cell shipment_, table table_) {
//     int n_source = count_storage(table_, 0);
//     int n_destination = count_storage(table_, 1);
//     int i_[n_source * n_destination];
//     int j_[n_source * n_destination];



//     return table_;
// }

cell stepping_stone_find_branches(cell shipment_, table table_, int prev_dir = 0, int select_branch = 0) {
    switch (prev_dir) {
        case 0 : // arah ke atas
            switch (select_branch) {
                case 0 :
                    return stepping_stone_find(shipment_, table_, 2);
                    break;
                case 1 :
                    return stepping_stone_find(shipment_, table_, 0);
                    break;
                default : //(case 2)
                    return stepping_stone_find(shipment_, table_, 3);
            }
            break;
        case 1 : // arah ke bawah
            switch (select_branch) {
                case 0 :
                    return stepping_stone_find(shipment_, table_, 3);
                    break;
                case 1 :
                    return stepping_stone_find(shipment_, table_, 1);
                    break;
                default : //(case 2)
                    return stepping_stone_find(shipment_, table_, 2);
            }
            break;
        case 2 :
            switch (select_branch) {
                case 0 :
                    return stepping_stone_find(shipment_, table_, 1);
                    break;
                case 1 :
                    return stepping_stone_find(shipment_, table_, 2);
                    break;
                default : //(case 2)
                    return stepping_stone_find(shipment_, table_, 0);
            }
            break;
        default : // (case 3)
            switch (select_branch) {
                case 0 :
                    return stepping_stone_find(shipment_, table_, 0);
                    break;
                case 1 :
                    return stepping_stone_find(shipment_, table_, 3);
                    break;
                default : //(case 2)
                    return stepping_stone_find(shipment_, table_, 1);
            }
    }
}

// bool stepping_stone_find_cycle(cell shipment_start, cell shipment_target, table table_) {
//     bool result = false;
//     if (shipment_start == shipment_target) { // awal pencarian... asekkk wkwkw 
//         for (int i = 0; i < 3; i++) {
//             if (!stepping_stone_find(shipment_start, table_, i).isEmpty) {
//                 if (stepping_stone_find(shipment_start, table_, i) == shipment_target)
//                     return true;
//                 else {
//                     for (int j = 0; j < 3; j++) {
//                         if (stepping_stone_find_branches(stepping_stone_find(shipment_start, table_, i), table_, i, j) == shipment_target) {
//                             return true
//                         } else {
//                             return stepping_stone_find_cycle(stepping_stone_find_branches(stepping_stone_find(shipment_start, table_, i), table_, i, j), shipment_target, table_);
//                         }
//                     }
//                 }
//             }
//         }
//         return false;
//     } else {
        
//     }

// }

table stepping_stone(table table_) {
    cout << endl;

    table result = table_;
    int n_source = count_storage(result, 0);
    int n_destination = count_storage(result, 1);

    //Getting all cell-indeces with zero (0) amount
    int i_[min_max(n_source, n_destination, 0)], j_[min_max(n_source, n_destination, 1)];
    int count = 0;
    for (int i = 0; i < n_source; i++) {
        for (int j = 0; j < n_destination; j++) {
            if (result.shipment[i][j].amount == 0) {
                i_[count] = i;
                j_[count] = j;
                count++;
            }
        }
    }

    cell result_;
    for (int i = 0; i < 2; i++) {
        result_ = stepping_stone_find_(table_.shipment[2][1], table_, 0, i);
        cout << result_.x << " " << result_.y << " " << result_.amount << endl;
    }

    return result;
    // show_table(result, "Stepping Stone");
    // show_table(result);
    // show_table(result);
}

int main()
{
    table model;
    model = initial_table();

    // step 1
    system("CLS");
    title();
    show_table(model, "Initial Table");
    model = nwc(model);
    table model_ = stepping_stone(model);
    // cout << endl << count_storage(model, 1);
    cout << endl;

    cout << "n_source = " << count_storage(model, 0) << endl;
    cout << "n_destinantion = " << count_storage(model, 1) << endl;
    cout << "total_source_capacity = " << count_storage_capacity(model, 0) << endl;
    cout << "total_destinantion_capacity = " << count_storage_capacity(model, 1) << endl;

    return 0;
}
