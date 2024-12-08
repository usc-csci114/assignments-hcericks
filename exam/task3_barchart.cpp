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
    std::map<string, map<string, double> > ds ;
    std::map<string, double> order_totals;

    std::ifstream ifile("bug-attraction.csv");
	std::string line;

    if (!ifile.is_open()) 
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line);

    vector<string> order = {"Diptera", "Hymenoptera", "Hemiptera", "Psocoptera", "Coleoptera",
                             "Collembola", "Thysanura", "Isoptera", "Lepidoptera", "Neuroptera", "Larave", "Orthoptera",
                             "Unident"};

    vector<double>  Diptera_sum, Hymenoptera_sum, Hemiptera_sum, Psocoptera_sum, 
                    Coleoptera_sum, Collembola_sum, Thysanura_sum, Isoptera_sum, Lepidoptera_sum, 
                    Neuroptera_sum, Larave_sum, Orthoptera_sum, Unident_sum;
    
    double top1 = -1, top2 = -1, top3 = -1, top4 = -1;
    string top1_species = "", top2_species = "", top3_species = "", top4_species = "";

    while (getline(ifile, line))
    {
        std::stringstream ss(line);
        string light_type;
        getline(ss, light_type, ',');

        string value;
        for (int i = 0; i < 17; ++i) {
            getline(ss, value, ',');
        }

        string bug_count;
        for (int i = 0; i < 13; ++i) {
            getline(ss, bug_count, ',');
            ds[light_type][order[i]] += stod(bug_count);  
            order_totals[order[i]] += stod(bug_count);
        }
    }

    for (std::map<string, double>::iterator it = order_totals.begin(); it != order_totals.end(); ++it) {

        string bug_type = it->first; 
        double sum_of_bugs = it->second;
        
        if (sum_of_bugs > top1) {
            top4 = top3;
            top3 = top2;
            top2 = top1;
            top1 = sum_of_bugs;
            top4_species = top3_species;
            top3_species = top2_species;
            top2_species = top1_species;
            top1_species = bug_type;
        } 
        else if (sum_of_bugs > top2) {
            top4 = top3;
            top3 = top2;
            top2 = sum_of_bugs;
            top4_species = top3_species;
            top3_species = top2_species;
            top2_species = bug_type;
        } 
        else if (sum_of_bugs > top3) {
            top4 = top3;
            top3 = sum_of_bugs;
            top4_species = top3_species;
            top3_species = bug_type;
        } 
        else if (sum_of_bugs > top4) {
            top4 = sum_of_bugs;
            top4_species = bug_type;
        }
    }


    std::vector<string> light_names = {"A", "B", "C", "LED", "CFL", "No"};
    std::vector<double> top1_species_vals;
    std::vector<double> top2_species_vals;
    std::vector<double> top3_species_vals;
    std::vector<double> top4_species_vals;

    top1_species_vals.push_back(ds["A"][top1_species]);
    top1_species_vals.push_back(ds["B"][top1_species]);
    top1_species_vals.push_back(ds["C"][top1_species]);
    top1_species_vals.push_back(ds["LED"][top1_species]);
    top1_species_vals.push_back(ds["CFL"][top1_species]);
    top1_species_vals.push_back(ds["No"][top1_species]);

    top2_species_vals.push_back(ds["A"][top2_species]);
    top2_species_vals.push_back(ds["B"][top2_species]);
    top2_species_vals.push_back(ds["C"][top2_species]);
    top2_species_vals.push_back(ds["LED"][top2_species]);
    top2_species_vals.push_back(ds["CFL"][top2_species]);
    top2_species_vals.push_back(ds["No"][top2_species]);

    top3_species_vals.push_back(ds["A"][top3_species]);
    top3_species_vals.push_back(ds["B"][top3_species]);
    top3_species_vals.push_back(ds["C"][top3_species]);
    top3_species_vals.push_back(ds["LED"][top3_species]);
    top3_species_vals.push_back(ds["CFL"][top3_species]);
    top3_species_vals.push_back(ds["No"][top3_species]);
    
    top4_species_vals.push_back(ds["A"][top4_species]);
    top4_species_vals.push_back(ds["B"][top4_species]);
    top4_species_vals.push_back(ds["C"][top4_species]);
    top4_species_vals.push_back(ds["LED"][top4_species]);
    top4_species_vals.push_back(ds["CFL"][top4_species]);
    top4_species_vals.push_back(ds["No"][top4_species]);


    std::vector<std::vector<double>> y = {top1_species_vals, top2_species_vals, top3_species_vals, top4_species_vals};

    auto b = bar(y);

    b->face_colors()[2] = {0.f, .2f, .6f, .5f};
    gcf()->draw();
    ylabel("Insect Count");
    title("Part 3 Bar Chart");


    show();
    save("part3.png");
    return 0;
}
