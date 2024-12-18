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

    //vectors to hold the data 
    vector<double> singles;
    vector<double> doubles;
    vector<double> triples;
    vector<double> homeruns;
    vector<double> extra_base_hits;
    vector<double> years;
       
    //inputting the file
    std::ifstream ifile("Ichiro.csv");
	std::string line;

    //checking to make sure file opens
    if (!ifile.is_open()) 
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line); // get the header line

    
    while (getline(ifile, line)) 
    {
        std::stringstream ss(line);
        
        string year, hit, sing, doub, trip, hr;

        std::getline(ss, year, ',');

        string other;
        for (int i =0; i < 7; i++)
        {
            std::getline(ss, other, ',');
        }

        std::getline(ss, hit, ',');
        std::getline(ss, doub, ',');
        std::getline(ss, trip, ',');
        std::getline(ss, hr, ',');

        //calculate singles
        int single = 0; 
        single = stod(hit) - (stod(doub) + stod(trip));

        //put the values into respective vectors
        double s_ratio = single / stod(hit);
        double d_ratio = stod(doub) / stod(hit);
        double t_ratio = stod(trip) / stod(hit);
        double hr_ratio = stod(hr) / stod(hit);
        double extra_bh = (stod(doub)+stod(trip)+stod(hr))/stod(hit);

        singles.push_back(s_ratio);
        doubles.push_back(d_ratio);
        triples.push_back(t_ratio);
        homeruns.push_back(hr_ratio);
        extra_base_hits.push_back(extra_bh);

        years.push_back(stod(year));
        
    }

    //omitting career end years and mid season trade 1/2 seasons
    singles.erase(singles.end() - 2, singles.end()); 
    doubles.erase(doubles.end() - 2, doubles.end()); 
    triples.erase(triples.end() - 2, triples.end()); 
    homeruns.erase(homeruns.end() - 2, homeruns.end()); 
    extra_base_hits.erase(extra_base_hits.end() - 2, extra_base_hits.end()); 
    years.erase(years.end() - 2, years.end()); 
    
    singles.erase(singles.begin() + 11, singles.begin() + 13); 
    doubles.erase(doubles.begin() + 11, doubles.begin() + 13); 
    triples.erase(triples.begin() + 11, triples.begin() + 13); 
    homeruns.erase(homeruns.begin() + 11, homeruns.begin() + 13); 
    extra_base_hits.erase(extra_base_hits.begin() + 11, extra_base_hits.begin() + 13); 
    years.erase(years.begin() + 11, years.begin() + 13); 
    


    vector<double> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}; // x values for bar graph spacing
    std::vector<std::vector<double>> y = {singles, doubles, triples, homeruns}; // each bar
    std::vector<std::string> labels = {"2001", "2002", "2003", "2004", "2005", "2006",  //years 
                                    "2007", "2008", "2009","2010", "2011", "2012",
                                    "2013", "2014", "2015", "2016", "2017"};

    
    //plotting, note you have to plot one at a time
    bar(x,y);

    xticks(x);
    xticklabels(labels);
    ylabel("Hit Ratio");
    xlabel("Years");
    title("Ratio of Singles, Doubles, Triples, and Home Runs to Total Hits Overtime");

	show();
	save("Part1_Ratio.png");
    
    
    bar(x,extra_base_hits);
    xticks(x);
    xticklabels(labels);
    ylabel("Hit Ratio");
    xlabel("Years");
    title("Ratio of Extra Base Hits to Total Hits Overtime");

	show();
	save("Part1_extrabasehits.png");


    // individual bar graphs of percentage of singles doubles triples overtime below

    //singles
    /*
    bar(x,singles);
    xticks(x);
    xticklabels(labels);
    ylabel("Hit Ratio");
    xlabel("Years");
    title("Ratio of Singles to Total Hits Overtime");
    
	show();
	save("Part1_singles.png");
    

    //doubles
    bar(x,doubles);
    xticks(x);
    xticklabels(labels);
    ylabel("Hit Ratio");
    xlabel("Years");
    title("Ratio of Doubles to Total Hits Overtime");

	show();
	save("Part1_doubles.png");
    

    //triples
    bar(x,triples);
    xticks(x);
    xticklabels(labels);
    ylabel("Hit Ratio");
    xlabel("Years");
    title("Ratio of Triples to Total Hits Overtime");

	show();
	save("Part1_triples.png");
    

    //homeruns
    bar(x,homeruns);
    xticks(x);
    xticklabels(labels);
    ylabel("Hit Ratio");
    xlabel("Years");
    title("Ratio of Home Runs to Total Hits Overtime");

	show();
	save("Part1_homeruns.png");
    */

    
    
    return 0;

}
