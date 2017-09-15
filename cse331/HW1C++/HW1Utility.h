#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <time.h>
#include <thread>
#include <stdlib.h>
#include <future>
#include <exception>
#include <chrono>
#include <time.h>
#include <pthread.h>
/* for ETIMEDOUT */
#include <errno.h>
#include<sys/time.h>
using namespace std;

int clock_gettime(int /*clk_id*/, struct timespec* t) {
    struct timeval now;
    int rv = gettimeofday(&now, NULL);
    if (rv) return rv;
    t->tv_sec  = now.tv_sec;
    t->tv_nsec = now.tv_usec * 1000;
    return 0;
}

void ms2ts(struct timespec *ts, unsigned long ms)
{
    ts->tv_sec = ms / 1000;
    ts->tv_nsec = (ms % 1000) * 1000000;
}

bool cmp(const pair<int,int>& p1, const pair<int,int>& p2) {
    if(p1.second != p2.second)
        return p1.second < p2.second;
    return p1.first < p2.first;
}

bool compare(vector<vector<pair<int,int>>> our_result, vector<vector<pair<int,int>>> their_result) {
    map<vector<pair<int,int>>, int> match_map;

    //printf("Comparing vectors of size %d and %d\n",our_result.size(), their_result.size());

    if(our_result.size()!=their_result.size())
        return false;

    for(int i=0;i<(int)our_result.size();i++) {
        sort(our_result[i].begin(), our_result[i].end(), cmp);
        match_map[our_result[i]] += 1;
    }
    for(int i=0;i<(int)their_result.size();i++) {
        sort(their_result[i].begin(), their_result[i].end(), cmp);
        if(match_map.find(their_result[i]) == match_map.end()) {
            return false;
        }
    }
    return true;
}

