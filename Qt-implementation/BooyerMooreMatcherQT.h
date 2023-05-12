/**
 * CS2 project: 2- Simple palagarism detection utility using string matching
 */
#ifndef _BOOYERMOOREMATCHERQT_H
#define _BOOYERMOOREMATCHERQT_H

#include "MatcherQT.h"


class BooyerMooreMatcher : public Matcher {
public:

    map<string,double> match (const Document& testDoc , const Corpus& corpus);

    size_t getMemoryUsage ();
private:
    bool BoyerMooreAlgorithm (string text , string pattern) {
        int s = 0 , j;
        int m = pattern.length ();
        int n = text.length ();
        vector<int> borderPosition (m + 1) , shift (m + 1 , 0);
        preprocess_suffix (shift , borderPosition , &pattern[0] , m);
        preprocess_prefix (shift , borderPosition , &pattern[0] , m);

        while (s <= n - m) {
            j = m - 1;
            while (j >= 0 && pattern[j] == text[s + j]) {
                j--;
            }
            if (j < 0) {
                return true;
            }
            s += shift[j + 1];
        }

        return false;
    }
    void preprocess_suffix (vector<int>& shift , vector<int>& borderPosition , const string& pattern , int m) {
        int i = m , j = m + 1;
        borderPosition[i] = j;

        while (i > 0) {
            while (j <= m && pattern[i - 1] != pattern[j - 1]) {
                if (shift[j] == 0)
                    shift[j] = j - i;
                j = borderPosition[j];
            }
            i--;
            j--;
            borderPosition[i] = j;
        }
    }
    void preprocess_prefix (vector<int>& shift , vector<int>& borderPosition , const string& pattern , int m) {
        int i , j;
        j = borderPosition[0];
        for (i = 0; i <= m; i++) {
            if (shift[i] == 0)
                shift[i] = j;
            if (i == j)
                j = borderPosition[j];
        }
    }
};

#endif //_BOOYERMOOREMATCHERQT_H
