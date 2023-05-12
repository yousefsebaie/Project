/**
CS2 project: 2- Simple palagarism detection utility using string matching
*/

#include "RabinKarpMatcherQT.h"
#include <iostream>

map<string , double> RabinKarpMatcher::match (const Document& testDoc , const Corpus& corpus) {
    int prime = 107;
    map <string , double> matches;
    vector<string> sentences = splitIntoSentences (testDoc);
    for (const string& s : sentences) {
        for (const Document& d : corpus.getDocuments ()) {

            if (RabinKarp (d.getContent () , s , prime))
            {
                if (matches.find (d.getTitle ()) == matches.end ())
                {
                    matches.insert (pair<string , double> (d.getTitle () , s.size ()));
                }
                else {
                    matches[d.getTitle ()] += s.size ();
                }
            }
        }
        for (map<string , double>::iterator itr = matches.begin ();itr != matches.end ();itr++)
        {
            itr->second = (itr->second / testDoc.getContent ().size ()) * 100;
        }
    }
    return matches;
}
size_t RabinKarpMatcher::getMemoryUsage () {
    return sizeof (*this);
}

// int RabinKarpMatcher::calculateHash(const string& str, int start, int end, int prime) {
// int hash = 0;
//         int base = 256; // choose a base for the hash function
//         int powBase = 1; // store powers of base modulo prime
//         for (int i = start; i <= end; i++) {
//             hash = (hash + (str[i] * powBase) % prime) % prime; // add modulus operation
//             powBase = (powBase * base) % prime; // update power of base modulo prime
//         }
//         return hash;
//     }

// bool RabinKarpMatcher::isEqual(const string& str1, int start1, int end1, const string& str2, int start2, int end2) {
//     if (end1 - start1 != end2 - start2) {
//             return false;
//         }
//         for (int i = start1, j = start2; i <= end1 && j <= end2; i++, j++) {
//             if (str1[i] != str2[j]) {
//                 return false;
//             }
//         }
//         return true;
//     }