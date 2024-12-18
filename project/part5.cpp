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
    std::ifstream ifile("Ichiro.csv"); //inputing file
	std::string line;

    if (!ifile.is_open()) 
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line); // get the header line

    //make vectors to hold data 
    vector<string> teams;

    vector<double> BA_vals;
    vector<double> OBP_vals;
    vector<double> SLG_vals;

    //make maps to link teams to batting stats 
    map<string, double> BA;
    map<string, double> OBP;
    map<string, double> SLG;
    map<string, int> szn_count;

    while (getline(ifile, line)) 
    {
        std::stringstream ss(line);
        
        string team, ba, obp, slg, value, year;
        
        getline(ss, year, ',');
        if (stoi(year) == 2012) // omit the "TOT" year which combined the batting stats from the full year during his mid seasin trade
        {
            continue;
        }
        else if (stoi(year) == 2018) // omit the ending years that were not signifigant 
        {
            break;
        }

        getline(ss, value, ',');

        std::getline(ss, team, ',');

        for (int i = 0; i < 15; i ++)
        {
            getline(ss, value, ',');
        }

        std::getline(ss, ba, ',');
        std::getline(ss, obp, ',');
        std::getline(ss, slg, ',');

        BA[team] += (stod(ba));
        OBP[team] += (stod(obp));
        SLG[team] += (stod(slg));
        szn_count[team] ++;
    }

    for (auto b : BA) // going through all seasons
    {
        string team_name = b.first; 
        teams.push_back(team_name); // vector with the teams names

        double avg_BA = BA[team_name] / szn_count[team_name];
        double avg_OBP = OBP[team_name] / szn_count[team_name];
        double avg_SLG = SLG[team_name] / szn_count[team_name];

        //average batting stats for the team 
        BA_vals.push_back(avg_BA);
        OBP_vals.push_back(avg_OBP);
        SLG_vals.push_back(avg_SLG); 
        
    }
    
    //vector of data points 
    vector<vector<double>> data_points = {BA_vals, OBP_vals, SLG_vals};

    //plotting 
    bar(data_points);
    xticklabels(teams);
    ylabel("Average Batting Stats");
    xlabel("Teams");
    title("Batting Stats (BA, OBP, SLG) by Team");

	show();
	save("Part5.png");


    return 0;

}


