#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <sstream>
using namespace std;
const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

//function declarations
int createDictHelper(std::istream &dictfile, std::string dict[], int num);
int arrayHelper(std::string arr[]);
void wordSorter(std::string dict[], std::string arr[], std::string result[]);
void permutationsHelperL(std::string rest, int start, int end, std::string arr[], const std::string dict[], int size);
void LoopHelperL(int i, int max, int start, std::string rest, std::string arr[],std::string dict[]);
bool binarySearchHelperL(std::string target, std::string dict[], std::string result[]);

// NAME: arrayHelper
// INPUT: an array of strings
// OUTPUT: an integer
// DESCRIPTION: returns the size of the array
int arrayHelper(std::string arr[]){
     if (*arr == ""){ //if the element at the current index is blank
            return 0;
        }
        if (*arr != ""){ //if there exists a word at the current index
        return 1 + arrayHelper(arr+1); //increment by 1
        }
        if (arr == NULL){ //if the arr pointer is equal to null, there are no more elements in the array
            return 0; //return 0, as we have reached the end
        }
        return 0;
    
}


// NAME: binarySearchHelper
// INPUT: a string, an array of strings, an array of strings that hold the results
// OUTPUT: true if target found in array, false otherwise
// DESCRIPTION: searches the array to see if the target string is there
bool binarySearchHelper(std::string target, std::string arr[], std::string result[]){
     if (arrayHelper(arr) < 1){ //if we've reached the end of the array
        return false;
    }
    if (target == arr[0]){ //base case, target found in array
        return true;
    }
    if (target != arr[0]){ //target is not at array index 0
        return binarySearchHelper(target, arr+1, result); //increase the pointer to arr by 1
    }
    return false;
}

// NAME: wordSorter
// INPUT: a const array of strings, an array of strings, an array of strings that we put the target in, an integer size
// OUTPUT: None, void
// DESCRIPTION: searches for the target and sets it equal to the current element of the array
void wordSorter(const std::string dict[],std::string arr[], std::string result[], int size){
    if (size < 1){ //base case
        return;
    }
    if (dict == NULL || dict[0] == ""){ //if the current element is blank or nonexistant
        return;
    }
    std::string target = dict[0]; //set the string equal to the current element of the array

    if (binarySearchHelper(target, arr, result)){ //we found the target
        result[0] = dict[0];
        return wordSorter(dict+1, arr, result+1, size-1); //increment dict by 1, result by 1, and size by -1
    }
    return wordSorter(dict+1, arr, result, size); //return dict + 1
    
}

// NAME: LoopHelperL
// INPUT: integer i, const reference to int max, int start, string rest, array of strings, const array of strings
// OUTPUT: None, void
// DESCRIPTION: simulates a for loop, using recursion
void LoopHelperL(int i, const int &max, int start, std::string rest, std::string arr[],const std::string dict[], const int &size){
    if (i > max){ //base case
           return;
       }

    char temp1 = rest[i]; //create a temporary char that holds the character at the current index
       rest[i] = rest[start]; //swap the two characters
       rest[start] = temp1; //set the start index equal to the temp
       
       permutationsHelperL(rest, start+1, max, arr, dict, size); //call permutationshelper and increment start by 1
       
    //put the characters back in the original order
       char temp2 = rest[i];
       rest[i] = rest[start];
       rest[start] = temp2;
       
       LoopHelperL(i+1,max, start, rest, arr, dict, size); //call loop helper and increment i by 1
}

// NAME: binarySearchHelperL
// INPUT: a const reference to a string, a const array of strings, an array of strings, an integer max
// OUTPUT: true if the target is found, false otherwse
// DESCRIPTION: searches through the array for the target, returns true if found
bool binarySearchHelperL(const std::string &target, const std::string dict[], std::string result[], int max){
    if (max == 1){ //base case, target not found
        return false;
    }
    
    if (target == dict[0]){ //base case, target found in dictfile
        return true;
    }
    if (target != dict[0]){ //target is not at array index 0
        //return binarySearchHelperL(target, dict+1, result, max-1); //increase the pointer to arr by 1
        if (binarySearchHelperL(target, dict+1, result, max/2)){ //search the first half of dict
            return true;
        }
        else if (binarySearchHelperL(target, dict + max/2, result, max - max/2)){ //search the latter half of dict
            return true;
        }
        else
            return false; //nothing found so return false
    }
    return false;
}

// NAME: permutationsHelperL
// INPUT: a string rest, an integer start, an integer end, a string of arrays, a const string of arrays, an integer max
// OUTPUT: None, void
// DESCRIPTION: creates permuatations of the given string
void permutationsHelperL(std::string rest, int start, int end, std::string arr[], const std::string dict[], int max){
   
   int i = start;
    if (start > end){ //base case
        //do a check here, put the target into array
        
       if (binarySearchHelperL(rest, dict, arr, max/2)){ //first half of dict
           int index = arrayHelper(arr); //create an integer index initialized to the size of the array
           arr[index] = rest; //set the element at index equal to rest
       }
        
       else if (binarySearchHelperL(rest, dict + max/2,arr, max - max/2)){ //last half of dict
        int index = arrayHelper(arr); //create an integer index initialized to the size of the array
        arr[index] = rest;//set the element at index equal to rest
       }
    }
    
    else{
        (LoopHelperL(i, end, start, rest, arr, dict, max)); //call loop helper with no incrementations
        }
    
}

// NAME: characterMixer
// INPUT: a const reference to a string, a const array of strings, a const reference to an integer, an array of strings
// OUTPUT: an integer that shows how many results were found
// DESCRIPTION: Puts all the possibilities of word which are found in dict into results. Returns the number of matched words found.
int characterMixer(const std::string &word, const std::string dict[], const int &size, std::string results[]){
    
    std::string arr[MAXDICTWORDS]; //create a temporary array with the size of global constant MAXDICTWORDS
    int strLen = word.length(); //create an integer strLen equal to word.length()
    
    permutationsHelperL(word, 0, strLen-1, arr, dict, size); //call permutationsHelper, initialize start to 0 and size to the length of the word - 1
    wordSorter(dict,arr, results, arrayHelper(arr)); //call wordSorter to input the results into the array
    return arrayHelper(results); //return the size of the new resulting array
 
    

}

// NAME: createDictHelper
// INPUT: a given text file, an array of strings, an integer num
// OUTPUT: an integer that shows the total amount of words copied
// DESCRIPTION: a helper function to help with the copying of elements in the text file into the given array
int createDictHelper(std::istream &dictfile, std::string dict[], int num){
    std::string s; //create a string s
    
    if (num == MAXDICTWORDS){ //base case
        return num;
    }
    if (getline(dictfile, s)){ //if there exists a line, put it into s
        dict[0] = s; //set dict at current index equal to s
        num++; //increment num by 1
        num = createDictHelper(dictfile, dict + 1, num); //set num equal to recursive call of createDictHelper and increment dict by 1
    }
    return num; //return the total
}

// NAME: createDict
// INPUT: a given text file, an array of strings
// OUTPUT: an integer that shows how many items were copied into the array
// DESCRIPTION: Puts each string in dictfile into the array dict. Returns the number of words read into dict. This number should not be larger than MAXDICTWORDS since that is the size of the array.
int createDict(std::istream &dictfile, std::string dict[]){
    int num = 0; //initialize num equal to 0
    num = createDictHelper(dictfile, dict, num); //set num equal to createDicthelper
    return num; //return num
}

// NAME: viewAnswers
// INPUT: a const array of strings, an integer size
// OUTPUT: None, void
// DESCRIPTION: Displays size number of strings from results.
void viewAnswers(const std::string results[], int size){
    if (size < 1){ //base case
        return;
    }

    std::cout << "Matching word " <<  results[0] << std::endl;
    viewAnswers(results + 1, size - 1); //call viewAnswers incrementing results by 1 and size by -1
}


void testone(int n)
{
    string dictionary[MAXDICTWORDS];
    string results[MAXRESULTS];

    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case 1: {
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
            int numResults = createDict(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 9 && dictionary[0] == "act" && dictionary[1] == "art");
        } break; case 2: {
            // File is empty, checks that file is empty and createDict returns 0.
            istringstream iss("");
            int numResults = createDict(iss, dictionary);
            assert(numResults == 0 && dictionary[0] == "");
        } break; case 3: {
            // Dictionary has been read properly
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
            int numResults = createDict(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 9 && dictionary[0] == "act" && dictionary[numResults-1] == "tar");
        } break; case 4: {
            // Input file is larger than the dictionary size
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod\ntoo\nmany\nwords");
            int numResults = createDict(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 10 && dictionary[MAXDICTWORDS-1] == "too");
        } break; case 5: {
            // If a certain word with repeated letter is shown in results more than once - still accept.
            string dictionary[] = { "one", "oone", "ne", "e", "too" };
            int numResults = characterMixer("oto", dictionary, 5, results);
            assert((numResults == 1 || numResults == 2) && results[0] == "too");
        } break; case 6: {
            // Doesn't check numResults nor duplicates.
            string dictionary[] = { "one", "oone", "ne", "e", "too" };
            characterMixer("oto", dictionary, 5, results);
            assert(results[0] == "too");
        } break; case 7: {
            // If word wasn't found, numResults = 0 and results array is empty.
            string dictionary[] = { "one", "oone", "ne", "e" };
            int numResults = characterMixer("look", dictionary, 4, results);
            assert(numResults == 0 && results[0] == "" && results[1] == "");
        } break; case 8: {
            // No fraction of a permutation is being searched in dictionary
            string dictionary[] = { "one", "oone", "non", "oon" };
            int numResults = characterMixer("on", dictionary, 4, results);
            assert(numResults == 0 && results[0] == "" && results[1] == "");
        } break; case 9: {
            // No fraction of a permutation is being searched in dictionary
            string dictionary[] = { "one", "oone", "ne", "e", "neoo", "oneo" };
            int numResults = characterMixer("neo", dictionary, 6, results);
            assert(numResults == 1 && results[0] == "one" && results[1] == "");
        } break; case 10: {
            // Checking that no error occurs if more than MAXRESULTS are found.
            string dictionary[] = { "true",  "treu", "teru", "teur", "ture",
        "tuer", "rtue", "rteu", "retu","reut", "ruet", "rute", "utre",
        "uter", "uetr", "uert", "urte", "uret", "etru", "etur", "ertu",
        "erut", "eurt", "eutr" };
            // All 24 permutations
            int numResults = characterMixer("true", dictionary, 24, results);
            assert(numResults == MAXRESULTS);
        } break; case 11: {
            // Checking one word was found, no duplicates.
            string dictionary[] = { "ppp" };
            int numResults = characterMixer("ppp", dictionary, 1, results);
            assert(numResults == 1 && results[0] == "ppp" && results[1] == "");
        } break; case 12: {
            string dictionary[] = { "run", "dodge", "break", "urn", "defeat" };
            int numResults = characterMixer("nru", dictionary, 5, results);
            sort(results, results + numResults);
            assert(numResults == 2 && results[0] == "run" && results[1] == "urn");
        } break; case 13: {
            streambuf* oldCoutStreamBuf = cout.rdbuf();
            ostringstream strCout;
            cout.rdbuf(strCout.rdbuf());
            string results[] = { "cat", "act"};
            viewAnswers(results, 2);
            cout.rdbuf(oldCoutStreamBuf);
            string temp = strCout.str();
            bool match1 = temp.find("act") != string::npos;
            bool match2 = temp.find("cat") != string::npos;
            assert(match1 && match2);
        } break; case 14: {
            istringstream iss ("tier\nrite\nbate\ntire\nttir");
            int numWords = createDict(iss, dictionary);
            sort(dictionary, dictionary + numWords);
            assert(numWords == 5 && dictionary[0] == "bate");
            int numResults = characterMixer("tier", dictionary, numWords, results);
            assert(numResults == 3 && (results[2] == "tire" || results[2] == "tier" || results[2] == "rite"));
        } break; case 15: {
            string example[] = { "kool", "moe", "dee" };
            int numResults = characterMixer("look", example, 3, results);
            assert(numResults == 1 && results[0] == "kool");
        } break;
    }
}

int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = createDict(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = characterMixer(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        viewAnswers(results, numMatches);

    return 0;
}
/*
int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed" << endl;
}
*/
