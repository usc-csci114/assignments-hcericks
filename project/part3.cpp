#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath> 
#include <iomanip>
#include <map>
#include <set>
#include <unordered_set>
#include <matplot/matplot.h>



using namespace std;
using namespace matplot;

int main (int argc, char **argv) 
{

    std::ifstream ifile("Ichiro.csv"); //getting file
	std::string line;

    if (!ifile.is_open()) //checking file works
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line); // get the header line

    //making vectors to store data 
    vector<double> YEAR;
    vector<double> success_rate;


    while (getline(ifile, line)) 
    {
        std::stringstream ss(line);
        string year, sb, cs;

        std::getline(ss, year, ',');

        string other;
        for (int i =0; i < 12; i++)
        {
            std::getline(ss, other, ',');
        }

        std::getline(ss, sb, ',');
        std::getline(ss, cs, ',');

        YEAR.push_back(stod(year));

        double ratio = (stod(sb) / (stod(sb) + stod(cs))) ;  //calculating stolen base sucsess rate 
        success_rate.push_back(ratio);
        
    }

    //omitting career end years and mid season trade 1/2 seasons
    YEAR.erase(YEAR.end() - 2, YEAR.end()); 
    success_rate.erase(success_rate.end() - 2, success_rate.end());

    YEAR.erase(YEAR.begin() + 11, YEAR.begin() + 13); 
    success_rate.erase(success_rate.begin() + 11, success_rate.begin() + 13); 

    //plotting
    plot(YEAR , success_rate, "xr-");

    title("Season vs Sucsess Rate of Stolen Bases");
    xlabel("Year");
    ylabel("Percentage of Sucsessful Stolen Bases");
    show();
    save("Part3.png");
    
    return 0;

}