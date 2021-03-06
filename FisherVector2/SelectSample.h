#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include "feature.h"

using namespace std;

/*
 * Select feature points from standard input
 * Append selected points to an output file
 * Used for PCA and GMM training
 */

int SelectSample(string inputfile_p, string outputfile_p, int num_p,int flag_p)
{
    string inputfile(inputfile_p);
    string outputBase(outputfile_p);
    ifstream in_f(inputfile_p.c_str());
    bool append = true;
    if (flag_p == 0)
		append = false;
    // maintain a cache of 10,000 points
    // NOTE: better use pointer
    vector<DTFeature> cache (num_p);
    // set rand seed
    srand(time(NULL));
	// read from standard input
    string line;
    int counter = 0;
    if (in_f)
    {
    while (getline(in_f, line))  {
        if (rand()/(double)RAND_MAX < 0.17) {   // put in cache
//            cout << rand()<<endl;
            DTFeature f(line);
            cache[counter] = f;
            counter++;
            if (counter > cache.size()-1)
                break;
        }
    }
    }
    // select from cache
    in_f.close();
    string outputTraj = outputBase + ".traj";
    string outputHOG = outputBase + ".hog";
    string outputHOF = outputBase + ".hof";
    string outputMBHX = outputBase + ".mbhx";
    string outputMBHY = outputBase + ".mbhy";

    ofstream fout1, fout2, fout3, fout4, fout5;
    if (!append)    {
        fout1.open(outputTraj.c_str());
        fout2.open(outputHOG.c_str());
        fout3.open(outputHOF.c_str());
        fout4.open(outputMBHX.c_str());
        fout5.open(outputMBHY.c_str());
    }   else    {
        fout1.open(outputTraj.c_str(), fstream::app);
        fout2.open(outputHOG.c_str(), fstream::app);
        fout3.open(outputHOF.c_str(), fstream::app);
        fout4.open(outputMBHX.c_str(), fstream::app);
        fout5.open(outputMBHY.c_str(), fstream::app);
    }

    if (!fout1.is_open()||!fout2.is_open()||!fout3.is_open()||!fout4.is_open()||!fout5.is_open())   {
        cout<<"Cannot save to output"<<endl;
        return 0;
    }
    int step = (int)(counter / 100.0);
    if (step < 1)
        step = 1;

    for (int i = 0; i < counter; i++)   {
 //       if (i % step == 0)  {
//            cout << i <<endl;
            DTFeature feat = cache[i];
            fout1<<feat.traj[0];
            for (int j = 1; j < TRAJ_DIM; j++)
                fout1<<" "<<feat.traj[j];
            fout1<<endl;
            fout2<<feat.hog[0];
            for (int j = 1; j < HOG_DIM; j++)
                fout2<<" "<<feat.hog[j];
            fout2<<endl;
            fout3<<feat.hof[0];
            for (int j = 1; j < HOF_DIM; j++)
                fout3<<" "<<feat.hof[j];
            fout3<<endl;
            fout4<<feat.mbhx[0];
            for (int j = 1; j < MBHX_DIM; j++)
                fout4<<" "<<feat.mbhx[j];
            fout4<<endl;
            fout5<<feat.mbhy[0];
            for (int j = 1; j < MBHY_DIM; j++)
                fout5<<" "<<feat.mbhy[j];
            fout5<<endl;
  //      }
    }

    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();
    fout5.close();

    return 0;
}

