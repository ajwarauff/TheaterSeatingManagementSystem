#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

int const ROWS = 15;
int const SEATS_PER_ROW = 30;

char seating[ROWS][SEATS_PER_ROW];
double rowPrices[ROWS];
double totalRevenue = 0.0;
int seatsSold = 0;

string filename = "theater_data.txt";
void loading()
{
    system("cls");
    Sleep(1000);
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                LOADING                               \t\t\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    Sleep(1000);
    system("cls");
}

void initializeSeatingChart(char seating[ROWS][SEATS_PER_ROW])
{
    ofstream Wfile;
    Wfile.open(filename);
    if (!Wfile)
    {
        cout << "Failed to open file for writing.\n";
        return;
    }
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < SEATS_PER_ROW; c++)
        {
            seating[r][c] = '#';
            Wfile << seating[r][c];
        }
        Wfile << endl;
    }
    Wfile.close();
}

void showMenu()
{
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << " \t\t\t\t                   Menu\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\n\t\t\tpress 1 to display seats chart\n";
    cout << "\t\t\tpress 2 to sell seats\n";
    cout << "\t\t\tpress 3 to check stats\n";
    cout << "\t\t\tpress 4 to see row prices\n";
    cout << "\t\t\tpress 5 to reset seats chart \n";
    cout << "\t\t\tpress 6 to update all row prices \n";
    cout << "\t\t\tpress 7 to update specific row price \n";
    cout << "\t\t\tpress 8 to exit program \n";
}

void displaySeatingChart(char seating[ROWS][SEATS_PER_ROW], string filename)
{
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                    Seating Chart\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << " \t\t     01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30\n";

    for (int r = 0; r < ROWS; r++)
    {
        if (r < 9)
        {
            cout << "\t\tRow0" << r + 1 << " ";
        }
        else
        {
            cout << "\t\tRow" << r + 1 << " ";
        }
        for (int c = 0; c < SEATS_PER_ROW; c++)
        {
            cout << seating[r][c] << "  ";
        }
        cout << endl;
    }
}

void inputRowPrices(double rowPrices[])
{
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                        ROW PRICES  \n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < ROWS; i++)
    {
        if (i < 9)
        {
            cout << "\t\tenter price for row 0" << i + 1 << " ";
        }
        else
        {
            cout << "\t\tenter price for row " << i + 1 << " ";
        }
        cin >> rowPrices[i];
        if (rowPrices[i] < 1)
        {
            while (rowPrices[i] < 1)
            {
                cout << "------------------------------------------------------------------------------------------------------------------------\n";
                cout << " \t\t\t\t                     invalid entery            \n";
                cout << "------------------------------------------------------------------------------------------------------------------------\n";
                cout << " \t\tRow Prices cannot be negative.";
                cout << "\t\t\n Re - enter price for row " << i + 1 << " ";
                cin >> rowPrices[i];
            }
        }
    }
}

void sellTickets(char seating[ROWS][SEATS_PER_ROW], double rowPrices[ROWS], double& totalRevenue, int& seatsSold)
{
    int row, seatno;
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                    Sell Tickets\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    displaySeatingChart(seating, filename);
    cout << "\t\tenter row number between 1-15 \n";
    cin >> row;
    cout << "\t\tenter seat number between 1-30 \n";
    cin >> seatno;

    while (row < 1 || row > 15)
    {
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t                    INVALID ENTRY\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\tenter row number between 1-15 \n";
        cin >> row;
    }
    while (seatno < 1 || seatno > 30)
    {
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t                    INVALID ENTRY\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\tenter seat between 1-30\n";
        cin >> seatno;
    }
    int choice;
    while (seating[row - 1][seatno - 1] == '*')
    {
        cout << "\t\tseat not available\n";
		cout << "\t\t Do you want to buy any other ticket? (1 for Yes, 0 for No): ";
        cin >> choice;
        if (choice == 0) { break; }
        else {
            cout << "\t\tenter row number between 1-15 \n";
            cin >> row;
            cout << "\t\tenter seat number between 1-30 \n";
            cin >> seatno;
        }
    }

    seating[row - 1][seatno - 1] = '*';
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\tRow number " << row << " seat number " << seatno << " sold\n";

    seatsSold++;
    totalRevenue += rowPrices[row - 1];
}

void displayStatistics(char seating[ROWS][SEATS_PER_ROW], int seatsSold, double totalRevenue)
{
    int totalavailableseats = 0;
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                              STATISTICS\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t SEATS SOLD: " << seatsSold << endl;
    cout << "\t\t REVENUE: Rs." << totalRevenue << endl;

    for (int i = 0; i < ROWS; i++)
    {
        int availableseatsR = 0;
        for (int j = 0; j < SEATS_PER_ROW; j++)
        {
            if (seating[i][j] == '#')
            {
                availableseatsR++;
                totalavailableseats++;
            }
        }
        if (i < 9)
        {
            cout << "\t\t ROW 0" << i + 1 << " available seats: " << availableseatsR << "/" << SEATS_PER_ROW << endl;
        }
        else
        {
            cout << "\t\t ROW " << i + 1 << " available seats: " << availableseatsR << "/" << SEATS_PER_ROW << endl;
        }
    }
    cout << "\t\t TOTAL SEATS " << (ROWS * SEATS_PER_ROW) << endl;
    cout << "\t\t AVAILABE SEATS " << totalavailableseats << endl;
}

void saveToFile(char seating[ROWS][SEATS_PER_ROW], double rowPrices[ROWS], double totalRevenue, int seatsSold, string filename)
{
    ofstream Sfile(filename);
    if (!Sfile)
    {
        cout << "Failed to open file for saving.\n";
        return;
    }

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < SEATS_PER_ROW; c++)
        {
            Sfile << seating[r][c];
        }
        Sfile << endl;
    }

    for (int i = 0; i < ROWS; i++)
    {
        Sfile << rowPrices[i] << endl;
    }
    Sfile << endl;
    Sfile << totalRevenue << endl;
    Sfile << seatsSold << endl;
    Sfile.close();
}
void loadfromFile()
{
    ifstream lfile(filename);
    if (!lfile)
    {
        cout << " Failed to open file.";
        return;
    }
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < SEATS_PER_ROW; c++)
        {
            lfile >> seating[r][c];
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        lfile >> rowPrices[i];
    }
    lfile >> totalRevenue;
    lfile >> seatsSold;
    lfile.close();
}
void resetSeatsChart()
{
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                      RESET SEATS CHART\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";

    initializeSeatingChart(seating);
    seatsSold = 0;
    totalRevenue = 0.0;
    saveToFile(seating, rowPrices, totalRevenue, seatsSold, filename);

    displaySeatingChart(seating, filename);
    cout << "\t\t Seats Chart Reseted.\n";
}
void updateRowPrice() {
    loading();
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                      UPDATE ROW PRICES\n  ";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    int i;
    cout << "\t\t enter Row number to edit price.\n";
    cin >> i;
    if (i <= 9)
    {
        cout << "enter price for row 0" << i << " ";
        cin >> rowPrices[i - 1];
    }
    else
    {
        cout << "enter price for row " << i << " ";
        cin >> rowPrices[i - 1];
    }
    saveToFile(seating, rowPrices, totalRevenue, seatsSold, filename);
    cout << "\t\t                      Row " << i << " Price Updated. \n";
}
void updateallrowprices() {
    loading();
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                      UPDATE ROW PRICES\n  ";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    inputRowPrices(rowPrices);
    saveToFile(seating, rowPrices, totalRevenue, seatsSold, filename);
}
void displayrowprices()
{
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t                      SHOW ROW PRICES\n  ";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < ROWS; i++)
    {
        if (i < 9)
        {
            cout << "\t\t ROW 0" << i + 1 << " price per seat Rs. " << rowPrices[i] << endl;
        }
        else
            cout << "\t\t ROW " << i + 1 << " price per seat Rs. " << rowPrices[i] << endl;
    }
}

int main()
{
    string filename = "theater_data.txt";
    ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        loadfromFile();
    }
    else
    {
        initializeSeatingChart(seating);
        inputRowPrices(rowPrices);
    }

    int choice;
    do
    {
        showMenu();
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 8)
        {
            cin.clear();
            string garbage;
            cin >> garbage;


            system("cls");
            cout << "\t\tInvalid choice. Please enter a valid number between 1 and 6.\n";
            Sleep(1000);
            system("cls");

            showMenu();
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
            loading();
            displaySeatingChart(seating, filename);
            break;
        case 2:
            system("cls");
            loading();
            sellTickets(seating, rowPrices, totalRevenue, seatsSold);
            break;
        case 3:
            system("cls");
            loading();
            displayStatistics(seating, seatsSold, totalRevenue);
            break;
        case 4:
            system("cls");
            loading();
            displayrowprices();
            break;
        case 5:
            system("cls");
            loading();
            resetSeatsChart();
            break;
        case 6:
            system("cls");
            loading();
            updateallrowprices();
            break;
        case 7:
            system("cls");
            loading();
            updateRowPrice();
            break;
        case 8:
            system("cls");
            loading();
            saveToFile(seating, rowPrices, totalRevenue, seatsSold, filename);
            cout << "\t\tData saved. Exiting program.\n";
            break;
        default:
            system("cls");
            cout << "\t\tInvalid choice. Please try again.\n";
            Sleep(1000);
            system("cls");
        }
    } while (choice != 8);

    return 0;
}