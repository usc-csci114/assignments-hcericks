#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm> 



using namespace std;

struct Element {
	Element() :
	symbol(),name(),number(0),atomic_mass(0.0),type() {};
	
	string symbol; //e.g "H", "He"
	string name; //e.g "Hydrogen", "Helium"
	int number; //e.g 1, 2
	double atomic_mass; //e.g. 1.008, 4.0026
	string phase; //phase at room temp e.g gas, liquid, solid
	string type; //e.g. "metalliod, "transitional metals"
};

void print_elements(int num, vector<Element> elements);



//prototype 

size_t index_find(vector< pair<string, int> > index, string key);


struct compclass 
    {
        bool operator() ( pair<string, int> a, pair<string, int> b) { return (a.first < b.first);}
    } comp;
    
    //sort(symbol_index.begin(), symbol_index.end(), comp);






int main(int argc, char* argv[])
{
	vector<Element> elements(119);
    
    vector< pair<string, int> > name_index;
    vector< pair<string, int> > symbol_index;


    std::ifstream file("elements.csv");
    std::string line;

    for(int j=1;j<119;j++)
    {
        getline(file, line);
        for (int c = 0; c < line.size(); c++) 
        {
            if (line[c] == ',') 
            {
                line[c] = ' ';
            }
        }
        stringstream ss(line);
        int num;
        ss >> num;
        elements[num].number = num;
            
        ss >> elements[num].name >> elements[num].symbol >> elements[num].atomic_mass >> elements[num].phase >> elements[num].type;

        std::pair<string, int> p(elements[num].name, num);
        name_index.push_back(p);
            
        std::pair<string, int> r(elements[num].symbol, num);
        symbol_index.push_back(r);
    }
    sort(name_index.begin(), name_index.end(), comp);
    sort(symbol_index.begin(), symbol_index.end(), comp);


    while (true)
    {
        std::string user_element;
        cout << "What element are you interested in? " << endl;
        cin >> user_element;
        

        if (isdigit(user_element[0])) 
        {
            if ( (stoi(user_element) > 0) && (stoi(user_element) < 119) )
            {
                int num = stoi(user_element);
                print_elements(num, elements);
                continue;
            }
            else 
            {
                return 0;
            }
            continue;
        }
        
        if (!isdigit(user_element[0])) 
        {
            int element_size = user_element.size();

            if (element_size <= 2)
            {
                size_t num = index_find(symbol_index, user_element);
                print_elements(num, elements);
                continue;
            }
            if (user_element == "quit")
            {
                break;
            }
            
            if (element_size > 2)
            {
                size_t num = index_find(name_index, user_element);
                print_elements(num, elements);
                continue;
            }
            
            if ( element_size < 2 ) 
            {
                cout << "Not found.  " << endl;
                continue;
            }
        }
        return 0;
    }
}

 void print_elements(int num, vector<Element> elements)
    {
        cout << elements[num].name << " "
        << elements[num].symbol << " " 
        << elements[num].atomic_mass << " " 
        << elements[num].phase << " " 
        << elements[num].type << endl;
    }


    size_t index_find(vector< pair<string, int> >index, string key)
    {
        int low = 1;
        int high = index.size() - 1;

        while (high >= low)
        {
            int mid = (high + low) / 2 ; 
            
            if (key < index[mid].first) 
            {
                high = mid - 1;
            }
            else if (key == index[mid].first)
            {
                return index[mid].second;
            }
            else
            {
                low = mid + 1;
            }
        }
        return -1;
    }

   