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
    std::ifstream ifile("Ichiro.csv"); //inputting data 
	std::string line;

    if (!ifile.is_open()) // checking file
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line); // get the header line

    //making vectors to hold the data
    vector<double> sac_hits;
    vector<double> sac_flies;
    vector<double> total_sac;
    vector<double> years;



    while (getline(ifile, line)) 
    {
        std::stringstream ss(line);
        
        string value, sh, sf, year;
        double sacrifices = 0.0;

        std::getline(ss, year, ',');

        for (int i = 0; i < 23; i ++)
        {
            getline(ss, value, ',');
        }

        std::getline(ss, sh, ',');
        std::getline(ss, sf, ',');

        sacrifices = stod(sh) + stod(sf); // calculating total sacrifices

        sac_hits.push_back(stod(sh));
        sac_flies.push_back(stod(sf));
        total_sac.push_back(sacrifices);
        years.push_back(stod(year));
    }

    //omitting career end years and mid season trade 1/2 seasons
    years.erase(years.end() - 2, years.end()); 
    sac_hits.erase(sac_hits.end() - 2, sac_hits.end()); 
    sac_flies.erase(sac_flies.end() - 2, sac_flies.end()); 
    total_sac.erase(total_sac.end() - 2, total_sac.end()); 
    
    years.erase(years.begin() + 11, years.begin() + 13); 
    sac_hits.erase(sac_hits.begin() + 11, sac_hits.begin() + 13); 
    sac_flies.erase(sac_flies.begin() + 11, sac_flies.begin() + 13); 
    total_sac.erase(total_sac.begin() + 11, total_sac.begin() + 13); 


    std::vector<std::vector<double>> y = {sac_hits, sac_flies};
    std::vector<std::string> labels = {"2001", "2002", "2003", "2004", "2005", "2006", 
                                    "2007", "2008", "2009","2010", "2011", "2012",
                                    "2013", "2014", "2015", "2016", "2017"};
    bar(years,y);
    xticks(years);
    xticklabels(labels);
    ylabel("Number of Sacrifices");
    xlabel("Year");
    title("Sacrificed Hits and Sacrificed Flies Overtime");
    show();
    save("Part4_bar.png");

    //can only plot one at a time
    plot (years, total_sac);
    title("Season vs Total Sacrifices");
    xlabel("Year");
    ylabel("Total Sacrifices");
    show();
    save("Part4_scattor.png");
    

    return 0;

}