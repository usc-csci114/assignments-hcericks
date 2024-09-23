#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;



int main(int argc, char **argv)
{
    std::vector<double>tri_points;
    double input_value;
    double triangle_area;
    string token;

    cout << "please eneter 6 doubles" << endl;
    
    for (int i = 0; i < 6; i++)
    {
        cin >> token;

        if ((token) == "quit")
        {
            cout << "You have quit the program. Goodbye." << endl;
            return 0;
        }

        try 
        {
            input_value = stod(token);
        }
        catch (...)
        {
            cout << "Please re enter values. 6 doubles were not entered." << endl; 
            i = -1;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        tri_points.push_back(input_value);
        
    } 

    double x1 = tri_points[0];
    double x2 = tri_points[2];
    double x3 = tri_points[4];

    double y1 = tri_points[1];
    double y2 = tri_points[3];
    double y3 = tri_points[5];

    triangle_area = abs((0.5)* (x1*(y2-y3) + x2*(y3 - y1) + x3*(y1 - y2)));


//    |(1/2)*(x1(y2 − y3) + x2(y3 − y1) + x3(y1 − y2)|


    cout << triangle_area << endl;

    return 0; 
}




// do i need to throw errors
// how do i even run the code
// add in try catch statments
