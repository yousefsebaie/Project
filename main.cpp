#include <iostream>
#include "Document.h"
#include "Corpus.h"
#include "Matcher.h"
#include <iomanip>
#include <chrono>
#include "BruteForceMatcher.h"
#include "RabinKarpMatcher.h"
#include "kmpMatcher.h"
#include "BoyerMooreMatcher.h"
using namespace std;

int main () {
    // Set output formatting for floating point numbers
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision (2);
    // Create a corpus object and add three documents to it
    Corpus corpus;
    Document doc;
    doc.createFromFile ("First essay.txt");
    corpus.addDocument (doc);

    doc.createFromFile ("Second essay.txt");
    corpus.addDocument (doc);

    doc.createFromFile ("Third essay.txt");
    corpus.addDocument (doc);

    doc.createFromFile ("Fourth essay.txt");
    corpus.addDocument (doc);

    // Create a test document to check for plagiarism
    Document testdoc;

    testdoc.createFromFile ("testdocpl.txt");


    // Create objects for the four matching algorithms
    BruteForceMatcher bruteForceMatcher;
    RabinKarpMatcher rabinKarpMatcher;
    kmpMatcher kmpMatcher;
    BoyerMooreMatcher boyerMooreMatcher;

    // Use each algorithm to match the test document against the corpus
    map<string , double> bfMatches = bruteForceMatcher.match (testdoc , corpus);
    map<string , double> rkMatches = rabinKarpMatcher.match (testdoc , corpus);
    map<string , double> kmpMatches = kmpMatcher.match (testdoc , corpus);
    map<string , double> bmMatches = boyerMooreMatcher.match (testdoc , corpus);

    if (bfMatches.empty ()) {
        cout << "The brute force algorithm did not detect plagarism" << endl << endl;
    }
    else
    {
        // If there are matches detected by brute force, print them out
        std::cout << "The titles of the documents that were plagarized (As detected by brute force):" << std::endl;
        for (map<string , double>::iterator itr = bfMatches.begin ();itr != bfMatches.end ();itr++)
        {
            // Print the title of the document and the percentage of plagiarism detected
            std::cout << itr->first << " was plagarised by " << itr->second << "%" << std::endl;
        }
        cout << endl << endl;
    }

    if (rkMatches.empty ()) {
        cout << "The rabin Karp algorithm did not detect plagarism" << endl << endl;
    }
    else
    {
        // If there are matches detected by Rabin-Karp, print them out
        std::cout << "The titles of the documents that were plagarized (As detected by Rabin Karp):" << std::endl;
        for (map<string , double>::iterator itr = rkMatches.begin ();itr != rkMatches.end ();itr++)
        {
            // Print the title of the document and the percentage of plagiarism detected
            std::cout << itr->first << " was plagarised by " << itr->second << "%" << std::endl;
        }
        cout << endl << endl;
    }

    if (kmpMatches.empty ()) {
        cout << "The KMP algorithm did not detect plagarism" << endl << endl;
    }

    else
    {
        // If there are matches detected by KMP, print them out
        std::cout << "The titles of the documents that were plagarized (As detected by KMP):" << std::endl;
        for (map<string , double>::iterator itr = kmpMatches.begin ();itr != kmpMatches.end ();itr++)
        {
            // Print the title of the document and the percentage of plagiarism detected
            std::cout << itr->first << "was plagarised by " << itr->second << "%" << std::endl;
        }cout << endl << endl;
    }

    if (bmMatches.empty ()) {
        cout << "The Boyer Moore algorithm did not detect plagarism" << endl << endl;
    }
    else
    {
        // If there are matches detected by Boyer-Moore, print them out
        std::cout << "The titles of the documents that were plagarized (As detected by Booyer Moore):" << std::endl;
        for (map<string , double>::iterator itr = bmMatches.begin ();itr != bmMatches.end ();itr++)
        {
            // Print the title of the document and the percentage of plagiarism detected
            std::cout << itr->first << " was plagarised by " << itr->second << "%" << std::endl;
        }
        cout << endl << endl;
    }
    // Start the timer for the brute force matching algorithm
    auto start = chrono::high_resolution_clock::now ();
    bruteForceMatcher.match (testdoc , corpus);// Use the brute force matching algorithm to find all occurrences of the test document in the corpus
    auto end = chrono::high_resolution_clock::now ();// Stop the timer for the brute force matching algorithm and compute the duration
    auto bfDuration = chrono::duration_cast<chrono::nanoseconds>(end - start).count ();
    cout << "The brute Force took :" << bfDuration << " nanoseconds" << " to excute" << endl;// Print the duration of the brute force matching algorithm
    start = chrono::high_resolution_clock::now ();// Start the timer for the Rabin-Karp matching algorithm
    rabinKarpMatcher.match (testdoc , corpus);// Use the Rabin-Karp matching algorithm to find all occurrences of the test document in the corpus
    end = chrono::high_resolution_clock::now ();// Stop the timer for the Rabin-Karp matching algorithm and compute the duration
    auto rkDuration = chrono::duration_cast<chrono::nanoseconds>(end - start).count ();
    cout << "The rabin karp took :" << rkDuration << " nanoseconds" << " to excute" << endl;// Print the duration of the Rabin-Karp matching algorithm
    start = chrono::high_resolution_clock::now ();// Start the timer for the Knuth-Morris-Pratt matching algorithm
    kmpMatcher.match (testdoc , corpus);// Use the Knuth-Morris-Pratt matching algorithm to find all occurrences of the test document in the corpus
    end = chrono::high_resolution_clock::now ();// Stop the timer for the Knuth-Morris-Pratt matching algorithm and compute the duration
    auto kmpDuration = chrono::duration_cast<chrono::nanoseconds>(end - start).count ();
    cout << "The KMP took :" << kmpDuration << " nanoseconds" << " to excute" << endl;// Print the duration of the Knuth-Morris-Pratt matching algorithm
    start = chrono::high_resolution_clock::now ();// Start the timer for the Boyer-Moore matching algorithm
    boyerMooreMatcher.match (testdoc , corpus);// Use the Boyer-Moore matching algorithm to find all occurrences of the test document in the corpus
    end = chrono::high_resolution_clock::now ();// Stop the timer for the Boyer-Moore matching algorithm and compute the duration
    auto bmDuration = chrono::duration_cast<chrono::nanoseconds>(end - start).count ();
    cout << "The Booyer Moore took :" << bmDuration << " nanoseconds" << " to excute" << endl;// Print the duration of the Boyer-Moore matching algorithm
    cout << endl;
    cout << "The brute force object ocuppies " << bruteForceMatcher.getMemoryUsage () << " bytes from memory" << endl;
    cout << "The rabin karp object ocuppies " << rabinKarpMatcher.getMemoryUsage () << " bytes from memory" << endl;
    cout << "The kmp object ocuppies " << kmpMatcher.getMemoryUsage () << " bytes from memory" << endl;
    cout << "The boyer moore object ocuppies" << boyerMooreMatcher.getMemoryUsage () << " bytes from memory" << endl;
    return 0;
}
