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

double calc_A (double x_mean, double y_mean, double beta)
{
    double alpha = y_mean - (beta * x_mean);
   return alpha;
}

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
    std::vector<double> BG_Xvals;
    std::vector<double> BG_Yvals;
    std::vector<double> BG_Yvals_regression;

    std::vector<double> LK_Xvals;
    std::vector<double> LK_Yvals;
    std::vector<double> LK_Yvals_regression;


    std::vector<double> stunt_Xvals;
    std::vector<double> stunt_Yvals;
    std::vector<double> stunt_Yvals_regression;


    std::ifstream ifile("bug-attraction.csv");
	std::string line;

    if (!ifile.is_open()) 
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line);

    while (getline(ifile, line)) 
    {
        std::stringstream ss(line);
        
        std::string light_type, model_lamp, location, site, std_moon;

        std::getline(ss, light_type, ',');
        //cout << light_type << endl;
        
        std::getline(ss, model_lamp, ',');
        //cout << model_lamp << endl;
        
        std::getline(ss, location, ',');
        //cout << location << endl;
        
        std::getline(ss, site, ',');
        //cout << site << endl;
        
        std::getline(ss, std_moon, ',');
        //cout << std_moon << endl;
        double standard_moon = std::stod(std_moon);
        //cout << standard_moon << endl;

        std::string value;
        for (int i = 0; i < 26; ++i) {
            std::getline(ss, value, ',');
            //std::cout << value << endl;
        }

        std::string total;
        std::getline(ss, total, ',');
        cout << total << endl;
        
        double total_bugs = std::stod(total);
       

        if (location == "BG")
        {
            BG_Xvals.push_back(standard_moon);
            BG_Yvals.push_back(total_bugs);
        }
        
        if (location == "LK")
        {
            LK_Xvals.push_back(standard_moon);
            LK_Yvals.push_back(total_bugs);
        }
        
        if (location == "Stunt")
        {
            stunt_Xvals.push_back(standard_moon);
            stunt_Yvals.push_back(total_bugs);
        }
    }


    double BG_x_mean = calc_mean(BG_Xvals);
    double BG_y_mean = calc_mean(BG_Yvals);
    
    double beta_BG =  calc_B(BG_Xvals, BG_Yvals, BG_x_mean, BG_y_mean);
    double alpha_BG = calc_A(BG_x_mean, BG_y_mean, beta_BG);

    double lin_regression_y_BG = 0;

    for (int i = 0; i < BG_Xvals.size(); i++)
    {
        lin_regression_y_BG = alpha_BG + (beta_BG * BG_Xvals[i]);
        BG_Yvals_regression.push_back(lin_regression_y_BG);
    }


    std::vector<double> BG_fi_datapoints(101);
    for (int i = 0; i < BG_Xvals.size(); i++)
    {
        BG_fi_datapoints[i] = (alpha_BG + (beta_BG * BG_Xvals[i]));
    }

    double SS_res_BG =  calc_SS_res(BG_fi_datapoints, BG_Yvals);
    double SS_tot_BG =  calc_SS_tot(BG_Yvals, BG_y_mean);

    double R_sqaured_BG = 1 - (SS_res_BG/SS_tot_BG);

    
  
    double LK_x_mean = calc_mean(LK_Xvals);
    double LK_y_mean = calc_mean(LK_Yvals);
    
    double beta_LK =  calc_B(LK_Xvals, LK_Yvals, LK_x_mean, LK_y_mean);
    double alpha_LK = calc_A(LK_x_mean, LK_y_mean, beta_LK);

    double lin_regression_y_LK = 0;

    for (int i = 0; i < LK_Xvals.size(); i++)
    {
        lin_regression_y_LK = alpha_LK + (beta_LK * LK_Xvals[i]);
        LK_Yvals_regression.push_back(lin_regression_y_LK);
    }


    std::vector<double> LK_fi_datapoints(101);
    for (int i = 0; i < LK_Xvals.size(); i++)
    {
        LK_fi_datapoints[i] = (alpha_LK + (beta_LK * LK_Xvals[i]));
    }

    double SS_res_LK =  calc_SS_res(LK_fi_datapoints, LK_Yvals);
    double SS_tot_LK =  calc_SS_tot(LK_Yvals, LK_y_mean);

    double R_sqaured_LK = 1 - (SS_res_LK/SS_tot_LK);





    double stunt_x_mean = calc_mean(stunt_Xvals);
    double stunt_y_mean = calc_mean(stunt_Yvals);
    
    double beta_stunt =  calc_B(stunt_Xvals, stunt_Yvals, stunt_x_mean, stunt_y_mean);
    double alpha_stunt = calc_A(stunt_x_mean, stunt_y_mean, beta_stunt);

    double lin_regression_y_stunt = 0;

    for (int i = 0; i < stunt_Xvals.size(); i++)
    {
        lin_regression_y_stunt = alpha_stunt + (beta_stunt * stunt_Xvals[i]);
        stunt_Yvals_regression.push_back(lin_regression_y_stunt);
    }


    std::vector<double> stunt_fi_datapoints(101);
    for (int i = 0; i < stunt_Xvals.size(); i++)
    {
        stunt_fi_datapoints[i] = (alpha_stunt + (beta_stunt * stunt_Xvals[i]));
    }

    double SS_res_stunt =  calc_SS_res(stunt_fi_datapoints, stunt_Yvals);
    double SS_tot_stunt =  calc_SS_tot(stunt_Yvals, stunt_y_mean);

    double R_sqaured_stunt = 1 - (SS_res_stunt/SS_tot_stunt);
    
        
    /*
    must plot one at a time
    */
    
    
    plot(BG_Xvals, BG_Yvals, "-xr");
    hold(on);
    plot(BG_Xvals, BG_Yvals_regression, "-r")->use_y2(true);
    text(0.2, 200, "R^2 = " + std::to_string(R_sqaured_BG));
    text(0.2, 175, "y = " + std::to_string(alpha_BG) + "x+ " + std::to_string(beta_BG));
    title("BG Plot");
    xlabel("Standard Moon");
    ylabel("Total Bugs");
	show();
	save("BG_plot.png");
    
    
    plot(LK_Xvals, LK_Yvals, "bo-");
    hold(on);
    plot(LK_Xvals, LK_Yvals_regression, "-b")->use_y2(true);
    text(0.25, 200, "R^2 = " + std::to_string(R_sqaured_LK));
    text(0.25, 175, "y = " + std::to_string(alpha_LK) + "x+ " + std::to_string(beta_LK));
    title("LK and Stunt Plot");
    xlabel("Standard Moon");
    ylabel("Total Bugs");
	//show();
    hold(on);
	plot(stunt_Xvals,stunt_Yvals, "-rx")->use_y2(true);
    plot(stunt_Xvals, stunt_Yvals_regression, "-r")->use_y2(true);
    text(0.5, 250, "R^2 = " + std::to_string(R_sqaured_stunt));
    text(0.5, 225, "y = " + std::to_string(alpha_stunt) + "x+ " + std::to_string(beta_stunt));
	show();
	save("LK_Stunt_Plot.png");
   


    return 0;
}