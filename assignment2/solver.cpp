#include <iostream>
#include <vector>
#include "system.h"

using namespace std;

int main(int argc, char* argv[])
{
    size_t n,m;
    cout << "Please enter integers for n and m " << endl;
    cin >> n >> m;
    
    vector< vector<double> > matrix(n, vector<double> (m+1));

    cout << "Please enter system matrix one row at a time: " << endl;

    for (int i = 0; i < n; i++) 
    {
        cout << "Row " << i + 1 << ": " << endl;
        for (int j = 0; j < m+1; j++) 
        {
            if (!(cin >> matrix[i][j]))
            {
                cin.clear();
                cin.ignore();
                cout << "Didnt enter m+1 values, try again" << endl;
                j = -1;
            }
        }   
    }

    
    
    System system(n, m, matrix);
    system.solve();

    int num_soln = system.getNumSolutions();
    cout << "The number of solutions is: " <<  num_soln << endl;

    if ( (num_soln == 1) || (num_soln == 2) )
    {
        vector<double> solutions = system.getSolution();
        cout << "The solution is: " << endl;
        for (int i = 0; i < solutions.size(); i++)
        {
            cout << solutions[i] << endl;
        }
    }
    
   return 0;
    
}
