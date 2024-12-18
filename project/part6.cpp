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

// function to calculate the mean of a vector of doubles
double calc_mean (std::vector<double>& input_values) 
{
    double sum = 0;

    for (int i = 0; i < input_values.size(); i++) 
    {
        sum += input_values[i];
    }

    double mean = sum / input_values.size();
    return mean;
}

// function to calculate beta
double calc_B (std::vector<double>& x_vals, std::vector<double>& y_vals, double x_mean, double y_mean)
{
    double num_sum = 0;
    double denom_sum = 0;
    for (int i = 0; i < x_vals.size(); i++)
    {
        num_sum += ((x_vals[i] - x_mean) * (y_vals[i] - y_mean));
        denom_sum += (std::pow((x_vals[i] - x_mean),2));
    }
    double beta = (num_sum / denom_sum);
    return beta;
}

// function to calculate alpha
double calc_A (double x_mean, double y_mean, double beta)
{
    double alpha = y_mean - (beta * x_mean);
   return alpha;
}

// function to calculate SS_res
double calc_SS_res (std::vector<double> fi_datapoints, std::vector<double> y_vals)
{
    double calc = 0;
    double SS_res = 0;
    for (int i = 0; i < fi_datapoints.size(); i++)
    {
        calc = y_vals[i] - fi_datapoints[i];
        SS_res += (std::pow(calc, 2));
    }

    return SS_res;
}

// function to calculate SS_tot
double calc_SS_tot(std::vector<double> y_vals, double y_mean)
{
    double calc = 0;
    double SS_tot = 0;
    for (int i = 0; i < y_vals.size(); i++)
    {
        calc = y_vals[i] - y_mean;
        SS_tot += (std::pow(calc, 2));
    }
    return SS_tot;
}


int main (int argc, char **argv) 
{
    std::ifstream ifile("Ichiro.csv"); //open file
	std::string line;

    if (!ifile.is_open()) 
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line); // get the header line

    //vectors to store values 
    vector<double> age;
    vector<double> batting_avg;


    while (getline(ifile, line)) 
    {
        // get values from file and add to appropriate vector 
        std::stringstream ss(line);
        
        string a, ba, year, value;

        std::getline(ss, year, ',');
        std::getline(ss, a, ',');

        for (int i = 0; i < 15; i ++)
        {
            getline(ss, value, ',');
        }

        std::getline(ss, ba, ',');

        age.push_back(stod(a));
        batting_avg.push_back(stod(ba));
    }

    //omitting career end years and mid season trade 1/2 seasons
    age.erase(age.end() - 2, age.end()); 
    batting_avg.erase(batting_avg.end() - 2, batting_avg.end());

    age.erase(age.begin() + 11, age.begin() + 13); 
    batting_avg.erase(batting_avg.begin() + 11, batting_avg.begin() + 13);

    //vector for regression values
    std::vector<double> bat_avg_regression;

    //regression calcuations
    double age_mean = calc_mean(age);
    double batting_avg_mean = calc_mean(batting_avg);

    double beta =  calc_B(age, batting_avg, age_mean, batting_avg_mean);
    double alpha = calc_A(age_mean, batting_avg_mean, beta);

    double lin_regression = 0;

    for (int i = 0; i < age.size(); i++)
    {
        lin_regression = alpha + (beta * age[i]);
        bat_avg_regression.push_back(lin_regression);
    }

    // R^2 calcuations
    std::vector<double> fi_datapoints(age.size());
    for (int i = 0; i < age.size(); i++)
    {
        fi_datapoints[i] = (alpha + (beta * age[i]));
    }

    double SS_res =  calc_SS_res(fi_datapoints, batting_avg);
    double SS_tot =  calc_SS_tot(batting_avg, batting_avg_mean);

    double R_sqaured = 1 - (SS_res/SS_tot);

    //plotting
    plot(age, batting_avg, "-xr");
    hold(on);
    plot(age, bat_avg_regression, "-b")->use_y2(true);
    text(28, 0.15, "R^2 = " + std::to_string(R_sqaured));
    text(28, 0.13, "y = " + std::to_string(alpha) + "x+ " + std::to_string(beta));
    title("Batting Average vs Age Plot");
    xlabel("Age");
    ylabel("Batting Average");
	show();
	save("Part6.png");

    return 0;
}


