#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>  
#include <ctime>   
#include <cmath> 
#include <iomanip>
#include <map>
#include <set>
#include <unordered_set>
#include <matplot/matplot.h>


using namespace std;
using namespace matplot;

//Data Point struct to hold batting features and cluster
struct DataPoint 
{
    vector<double>features; //singles, doubles, triples, homeruns
    int cluster;
};

// Mean struct to hold batting features
struct Mean 
{
    vector<double>features;
};

// Function to find the index of the minimum value 
size_t indexOfMin (vector<double> &v)
{
    size_t idx = 0;
    double min = v[0];
    for (size_t i = 1; i < v.size(); i++)
    {
        if (v[i] < min)
        {
            min = v[i];
            idx = i;
        }
    }
    return idx;
}

//distance function
double Dist (DataPoint d, Mean m)
{   
    double dist = 0;
    for (size_t i = 0; i < d.features.size(); i++)
    {
        dist += pow(d.features[i] - m.features[i], 2);
    }
    return sqrt(dist); 
}

// normalizing function
void normalize(vector<vector<double>> &data)
{
    int num_stats = data[0].size();
    int num_seasons = data.size();

    for (int i = 0; i < num_stats; i++)
    {
        double sum = 0;
        for (int j = 0; j < num_seasons; j++)
        {
            sum += data[j][i];
        }
        double mean = sum / num_seasons;

        double sq_sum_deviation = 0;
        for (int j = 0; j < num_seasons; j++)
        {
            sq_sum_deviation += pow((data[j][i] - mean),2);
        }

        double var = sq_sum_deviation / (num_seasons - 1);
        double sd = sqrt(var);
        
        for (int j = 0; j < num_seasons; j++)
        {
            data[j][i] = (data[j][i] - mean) / sd ;
        }
    }
}

void kMeans(vector<DataPoint> &dp, int k, vector<Mean> &centroids)
{
    vector<int> counts(k,0); //counts vector has k vals all intilized to 0
    srand(time(0)); //to get random #
    
    //randomly initialize centroids 
    for (int i = 0; i < k; i++)
    {
        int idx = rand() % (dp.size()); // random idx
        centroids[i].features = dp[idx].features; // set centroids features
    }

    bool changes = true; // to track if there are changes to clusters
    size_t iterations = 0; //count number of iterations for converges
    while (changes)
    {
        changes = false; // resets to false at the start of every loop

        for (int i = 0; i < dp.size(); i++)
        {   
            vector<double> distances; //dist between data point and centroid
            for (int j = 0; j < k; j++)
            {
                double dist = Dist(dp[i], centroids[j]); // compute distance
                distances.push_back(dist); // store distance
            }

            size_t cm =  indexOfMin(distances); // find min distance

            // if not min then update it 
            if (dp[i].cluster != cm)
            {
                dp[i].cluster = cm;
                changes = true; // changes were made
            }
        }
        
        //reset coutns and features for next iteration
        for (int i = 0; i < k; i++) {
            counts[i] = 0;
            centroids[i].features.assign(dp[0].features.size(), 0);
        }

        //2D vector to store all features 
        vector<vector<double>> new_centroids(k, vector<double>(dp[0].features.size(), 0)); 

        //update counts for clusters
        counts.assign(k, 0);

        //calc new centroid by averaging the features of data points in each cluster
        for (int i = 0; i < dp.size(); i++)
        {
            counts[dp[i].cluster]++;
            for (size_t j = 0; j < dp[i].features.size(); j++)
            {
                new_centroids[dp[i].cluster][j] += dp[i].features[j];
            }      
        }

        //update centroid with the new computed values
        for (int i = 0; i < k; i++)
        {
            if (counts[i] > 0)
            {
                for (size_t j = 0; j < dp[i].features.size(); j++)
                {
                    new_centroids[i][j] /= counts[i];
                }
                centroids[i].features = new_centroids[i];
            }
        }
        //increment untill iterations = 100 or no changes to indicate while loop can end
        iterations++;
        if (iterations > 100 || !changes) 
        {
            break;
        }
    }
}

void plot_kMeans(vector<DataPoint> &dp, vector<Mean> &centroids, int k)
{
    //create vectors to hold the x and y values of data points for each cluster
    vector<vector<double>> plot_x(k);
    vector<vector<double>> plot_y(k);

    //loop through data points and push back onto vector 
    for (int i = 0; i < dp.size(); i++)
    {
        plot_x[dp[i].cluster].push_back(dp[i].features[0]); // Features[0] = singles 
        plot_y[dp[i].cluster].push_back(dp[i].features[3]); // Features[1] = doubles
    }


    hold(on);
    for (int i = 0; i < k; i++) 
    {
        if (i == 0) {
            plot(plot_x[i], plot_y[i],"ro"); //red circles
        
        } else if (i == 1) {
            plot(plot_x[i], plot_y[i],"go");  // green circles
        
        } else {
            plot(plot_x[i], plot_y[i], "bo");  // blue circles
       
        }
        // plot the centroids
        plot({centroids[i].features[0]}, {centroids[i].features[1]}, "ko") -> line_width(2).marker_size(20).marker_color("b");
    }
    

    xlabel("Feature 0  (Singles)");
    ylabel("Feature 1 (Doubles)");
    title("K-means Clustering of Ichiro's Batting Data");
    grid(true);
    show();
    cla();
}

int main (int argc, char **argv) 
{
    vector<vector<double>> data; //load in data
    vector<double> years;

    std::ifstream ifile("Ichiro.csv");
	std::string line;

    if (!ifile.is_open()) //check file opens
    {
    std::cout << "Failed to open file!" << std::endl;
    return 0;
    }

    std::getline(ifile, line); // get the header line

    
    while (getline(ifile, line)) 
    {
        std::stringstream ss(line);
        
        string year, hit, doub, trip, hr;

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

        double single = 0; 
        single = stod(hit) - (stod(doub) + stod(trip)); // calculate single

        vector<double> season_data = {single, stod(doub), stod(trip), stod(hr)}; // add all the hitting stats to season_data vector
        data.push_back(season_data);
        years.push_back(stoi(year));
        
    }

    //omitting career end years and mid season trade 1/2 seasons
    data.erase(data.end() - 2, data.end()); 
    years.erase(years.end() - 2, years.end()); 

    data.erase(data.begin() + 11, data.begin() + 13); 
    years.erase(years.begin() + 11, years.begin() + 13); 

    //normalize the data(hitting stats)
    normalize(data);

    //make a vector of DataPoints and loop through to convert data into DataPoint structure
    vector<DataPoint> data_points;
    for (int i = 0; i < data.size(); i++)
    {
        DataPoint dp = {data[i], -1};
        data_points.push_back(dp);
    }


    int k = 2; // number of clusters
    vector<Mean> centroids(k, Mean{{0, 0, 0, 0}}); //inital vector of centroids set to 0
    kMeans(data_points, k, centroids); // run the kmeans with data points, k clusters, and centroids

    //plot resulting k means clustering
    plot_kMeans(data_points, centroids, k);
    
    return 0;

    
}





