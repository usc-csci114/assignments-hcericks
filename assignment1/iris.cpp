#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath> 
#include <iomanip>


using namespace std;

void print_chart ()
{
    cout << "								               Iris Data" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << "|        | sepal length       | sepal width        | petal length        | petal width          |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    
}

void print_rows (string flower_type, double sl_min, double sl_max, double sl_mean, double sl_std, double sw_min, double sw_max, double sw_mean, 
double sw_std, double pl_min, double pl_max, double pl_mean, double pl_std, double pw_min, double pw_max, double pw_mean, double pw_std) 
{
    cout << "| " << flower_type << " | " << setprecision(2) << sl_min << ", " << sl_max << ", " << sl_mean << ", " << sl_std << " | " 
    << sw_min << ", "<< sw_max << ", " << sw_mean << ", " << sw_std << " | " 
    << pl_min << ", " << pl_max << ", " << pl_mean << ", " << pl_std << " | " 
    << pw_min << ", " << pw_max << ", " << pw_mean << ", " << pw_std << " | " << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

}
    


double calc_min (std::vector<double> input_values) 
{
    double min = 100;
    std::vector<double> temp_min(50);
    for (int i = 0; i < 50 ; i++) 
    {
        temp_min[i] = input_values[i];
        if (temp_min[i] < min) 
        {
            min = temp_min[i];
        }
    }
    return min;
}

double calc_max (std::vector<double> input_values) {
    double max = 0;
    std::vector<double> temp_max(50);
    for (int i = 0; i < 50 ; i++) 
    {
        temp_max[i] = input_values[i];
        if (temp_max[i] > max) 
        {
            max = temp_max[i];
        }
    }
    return max;
}
    
double calc_mean (std::vector<double> input_values) 
{
    double sum = 0;

    for (int i = 0; i < 50; i++) 
    {
        sum += input_values[i];
    }

    double mean = sum / 50;
    return mean;
}

double calc_stdev (std::vector<double> input_values, double mean) 
{
    double total_sum = 0; 
    double stdev; 
     
    for (int i = 0; i < 50; i++) 
    {
        total_sum += pow((input_values[i] - mean), 2);
    }
    total_sum = total_sum / 50;
    stdev = pow(total_sum, 0.5);

    return stdev; 
}




int main (int argc, char **argv) 
{
    std::vector<string> species(3);

    std::vector<double> sl_min(3);
    std::vector<double> sl_max(3);
    std::vector<double> sl_mean(3);
    std::vector<double> sl_std(3);

    std::vector<double> sw_min(3);
    std::vector<double> sw_max(3);
    std::vector<double> sw_mean(3);
    std::vector<double> sw_std(3);

    std::vector<double> pl_min(3);
    std::vector<double> pl_max(3);
    std::vector<double> pl_mean(3);
    std::vector<double> pl_std(3);

    std::vector<double> pw_min(3);
    std::vector<double> pw_max(3);
    std::vector<double> pw_mean(3);
    std::vector<double> pw_std(3);


    std::vector<double> sl(50);
    std::vector<double> sw(50);
    std::vector<double> pl(50);
    std::vector<double> pw(50);
    std::vector<double> flower_type(50);

    
    //input data 

    std::ifstream file("iris.txt");
    std::string line;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<50;j++)
        {
            getline(file, line);
            for (int c = 0; c < line.size(); c++) 
            {
                if(line[c] == ',') 
                {
                    line[c] = ' ';
                }
            }
            stringstream ss(line);
            ss >> sl[j] >> sw[j] >> pl[j] >> pw[j] >> flower_type[j];
        }
        sl_min[i] = calc_min(sl);
        sl_max[i] = calc_max(sl);
        sl_mean[i] = calc_mean(sl);
        sl_std[i] = calc_stdev(sl,sl_mean[i]);

        sw_min[i] = calc_min(sw);
        sw_max[i] = calc_max(sw);
        sw_mean[i] = calc_mean(sw);
        sw_std[i] = calc_stdev(sw,sw_mean[i]);

        pl_min[i] = calc_min(pl);
        pl_max[i] = calc_max(pl);
        pl_mean[i] = calc_mean(pl);
        pl_std[i] = calc_stdev(pl,pl_mean[i]);

        pw_min[i] = calc_min(pw);
        pw_max[i] = calc_max(pw);
        pw_mean[i] = calc_mean(pw);
        pw_std[i] = calc_stdev(pw,pw_mean[i]);


    }

    species[0] = "Iris-setosa";
    species[1] = "Iris-versicolor";
    species[2] = "Iris-virginica";

    print_chart();

    
    print_rows (species[0], sl_min[0], sl_max[0], sl_mean[0], sl_std[0], sw_min[0], sw_max[0], sw_mean[0], sw_std[0], pl_min[0], 
    pl_max[0], pl_mean[0], pl_std[0], pw_min[0], pw_max[0], pw_mean[0], pw_std[0]);

    print_rows (species[1], sl_min[1], sl_max[1], sl_mean[1], sl_std[1], sw_min[1], sw_max[1], sw_mean[1], sw_std[1], pl_min[1], 
    pl_max[1], pl_mean[1], pl_std[1], pw_min[1], pw_max[1], pw_mean[1], pw_std[1]);
    
    print_rows (species[2], sl_min[2], sl_max[2], sl_mean[2], sl_std[2], sw_min[2], sw_max[2], sw_mean[2], sw_std[2], pl_min[2], 
    pl_max[2], pl_mean[2], pl_std[2], pw_min[0], pw_max[2], pw_mean[2], pw_std[2]);


    return 0;  
}






// extraction with the commas
// replace commas with spaces and extract using string stream


// how do i input the data
// how do i throw those vals into a math function

