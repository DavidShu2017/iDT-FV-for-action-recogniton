#ifndef SAMPLEFEA_H_INCLUDED
#define SAMPLEFEA_H_INCLUDE
#include "zlib.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fstream>
#include <ctime>
using namespace std;

#define GZ_BUF_SIZE 1048576
int SampleFea(string file_name,int s_num,string save_name)
{

    ofstream out_f (save_name.c_str(),ofstream::app);
    ifstream in_f(file_name.c_str());
    string line_fea;
    int counter = 0;
    srand((unsigned)time(NULL)); //初始化随机数种子
    if(in_f)
    {
        while(getline(in_f,line_fea))
        {
            if (rand()/(double)RAND_MAX < 0.02)
            {
                out_f << line_fea<<endl;
                counter++;
                if (counter > s_num-1)
                    break;
            }
        }
    }
    return 0;
}

int SampleFea_gz(string file_name,int s_num,string save_name)
{

    ofstream out_f (save_name.c_str(),ofstream::app);
    gzFile gzfp = gzopen(file_name.c_str(),"rb");
    if(!gzfp)
    {
        return false;
    }

    //read and add it to out
    unsigned char buf[GZ_BUF_SIZE];
    int have;
    int counter = 0;
    while( (have = gzread(gzfp,buf,GZ_BUF_SIZE)) > 0)
    {
        if (rand()/(double)RAND_MAX < 1e-2)
        {
            out_f << (const char*)buf<<endl;
            counter++;
            if (counter > s_num-1)
                break;
        }
    }
    //close .gz file
    gzclose(gzfp);
    out_f.close();
    return 0;
}
#endif // SAMPLEFEA_H_INCLUDED
