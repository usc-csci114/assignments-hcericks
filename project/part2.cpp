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

    std::ifstream ifile("Ichiro.csv"); // reading file in
	std::string line;

    if (!ifile.is_open()) 
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line); // get the header line

    //vectors to store values 
    vector<double> hit_vals;
    vector<double> gdp_vals;
    vector<double>extra_base_hits;
    vector<double>years;

    while (getline(ifile, line)) 
    {
        std::stringstream ss(line);

        string year;
        std::getline(ss, year, ',');

        string other;
        for (int i =0; i < 7; i++)
        {
            std::getline(ss, other, ',');
        }

        string hit, gdp, doub, trip, hr;

        std::getline(ss, hit, ',');
        std::getline(ss, doub, ',');
        std::getline(ss, trip, ',');
        std::getline(ss, hr, ',');

        for (int i =0; i < 11; i++)
        {
            std::getline(ss, other, ',');
        }

        std::getline(ss, gdp, ',');

        double extra_bh = (stod(doub)+stod(trip)+stod(hr)); // calculating extra base hits
        extra_base_hits.push_back(extra_bh);

       hit_vals.push_back(stod(hit));
       gdp_vals.push_back(stod(gdp));
       years.push_back(stod(year));

    }

    //omitting career end years and mid season trade 1/2 seasons
    hit_vals.erase(hit_vals.end() - 2, hit_vals.end()); 
    extra_base_hits.erase(extra_base_hits.end() - 2, extra_base_hits.end()); 
    gdp_vals.erase(gdp_vals.end() - 2, gdp_vals.end()); 
    years.erase(years.end() - 2, years.end()); 
    
    hit_vals.erase(hit_vals.begin() + 11, hit_vals.begin() + 13); 
    extra_base_hits.erase(extra_base_hits.begin() + 11, extra_base_hits.begin() + 13); 
    gdp_vals.erase(gdp_vals.begin() + 11, gdp_vals.begin() + 13); 
    years.erase(years.begin() + 11, years.begin() + 13); 
        
    //plotting
    plot(years, extra_base_hits, "-xr");
    title("Extra Base Hits vs Time");
    xlabel("Years");
    ylabel("Extra Base Hits");
    hold(on);
    plot(years, gdp_vals, "-ob")->use_y2(true);
    y2label("Grounding into Double Plays");

    show();
	save("Part2.png");
    

    return 0;

}