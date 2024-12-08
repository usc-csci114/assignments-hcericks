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


using namespace std;
std::map<string, map<string, int> > ds ;

void draw_row (string species, string light_type)
{
    cout << "| " << std::setw(12) << left << species << " | " << std::setw(25) << left << light_type << " |" << endl;
    cout << "--------------------------------------------" << endl;    
}

string most_attractive (string species)
{
    int max = 0;
    string most_attrac_light = "";
    std::vector<std::string> light_types = {"A", "B", "C", "LED", "CFL", "No"};

    for (size_t i = 0; i < light_types.size(); ++i) {
        if (ds[species][light_types[i]] > max)
        {
            max = ds[species][light_types[i]];
            most_attrac_light = light_types[i];
        }   
    }
    return most_attrac_light;
}

int main (int argc, char **argv) 
{   
    std::ifstream ifile("bug-attraction.csv");
	std::string line;

    if (!ifile.is_open()) 
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line);

    vector<string> order = {"Illumination", "Diptera", "Hymenoptera", "Hemiptera", "Psocoptera", "Coleoptera",
                             "Collembola", "Thysanura", "Isoptera", "Lepidoptera", "Neuroptera", "Larave", "Orthoptera",
                             "Unident", "Total", "Other_Orders"};

    while (getline(ifile, line))
    {
        std::stringstream ss(line);
        string light_type;

        std::getline(ss, light_type, ',');

        string value;
        for (int i = 0; i < 14; ++i) {
            getline(ss, value, ',');
        }

        int count;
        for (size_t i = 0; i < order.size(); ++i) {
            if (ss >> count) {
                ds[order[i]][light_type] += count;
            }
            ss.ignore(numeric_limits<streamsize>::max(), ','); // Skip to the next column
        }

        for (size_t i = 0; i < order.size(); i++)
        {
            if (ss >> count)
            {
                ds[order[i]][light_type] += count;
            }
        }
    }

    cout << "|Species       |Most Attractive Light Type |" << endl;
    cout << "--------------------------------------------" << endl; 


    for (int i = 0; i < order.size(); i++)
    {
        string light = most_attractive (order[i]);
        draw_row (order[i], light);
    }

    return 0;

}