//Joseph Harrison 2019
//adfgvx cipher

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const char table[6][6] = {{'n', 'a', '1', 'c', '3', 'h'},
                          {'8', 't', 'b', '2', 'o', 'm'},
                          {'e', '5', 'w', 'r', 'p', 'd'},
                          {'4', 'f', '6', 'g', '7', 'i'},
                          {'9', 'j', '0', 'k', 'l', 'q'},
                          {'s', 'u', 'v', 'x', 'y', 'z'}};

const string headings = "adfgvx";

//translate a char into its equivalent digraph using table position and headings
string table_encipher(char letter)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            //check if we have found the letter
            if (table[i][j] == letter)
            {
                //use headings to create digraph
                string ret = "";
                ret.push_back(headings[i]);
                ret.push_back(headings[j]);
                return ret;
            }
        }
    }
    //'x' represents failure
    return "gx";
}

//map translate over characters in string
string table_encipher_string(string text)
{
    string ret = "";
    for (int i = 0; i < text.length(); i++)
    {
        ret.append(table_encipher(text[i]));
    }
    return ret;
}

string table_decipher_string(string text)
{
    string ret = "";
    for (int k = 1; k < text.length(); k += 2)
    {
        //position of each character in the digraph from headings
        int i = headings.find(text[k - 1]);
        int j = headings.find(text[k]);
        //get value from table
        ret.push_back(table[i][j]);
    }
    return ret;
}

string columnar_encipher(string ciphertext, string keyword)
{
    int ysize = keyword.length();
    int xsize = ciphertext.length() / keyword.length();
    
    char array[ysize][xsize];
    
    //creating array
    for (int i = 0; i < xsize; i++)
    {
        for (int j = 0; j < ysize; j++)
        {
            array[j][i] = ciphertext[i * ysize + j];
        }
    }
    
    //sort keyword
    string keywordsorted = keyword;
    sort(keywordsorted.begin(), keywordsorted.end());
    
    //reordered array
    char reordered[ysize][xsize];
    
    //compare positions of keyword and sorted keyword
    for (int i = 0; i < keyword.length(); i++)
    {
        //i position swaps to j position
        int j = keywordsorted.find(keyword[i]);
        
        //set reordered rows based on swaps made
        //to keyword
        for (int k = 0; k < xsize; k++)
        {
            reordered[j][k] = array[i][k];
        }
    }
    
    ciphertext = "";
    //copy table into ciphertext string
    for (int i = 0; i < ysize; i++)
    {
        for (int j = 0; j < xsize; j++)
        {
            ciphertext.push_back(reordered[i][j]);
        }
    }
    
    return ciphertext;
}

string columnar_decipher(string ciphertext, string keyword)
{
    int ysize = keyword.length();
    int xsize = ciphertext.length() / keyword.length();
    
    char array[ysize][xsize];
    
    //creating array
    for (int i = 0; i < ysize; i++)
    {
        for (int j = 0; j < xsize; j++)
        {
            array[i][j] = ciphertext[i * xsize + j];
        }
    }
    
    //sort keyword
    string keywordsorted = keyword;
    sort(keywordsorted.begin(), keywordsorted.end());
    
    //reordered array
    char reordered[ysize][xsize];
    
    //compare positions of keyword and sorted keyword
    for (int i = 0; i < keyword.length(); i++)
    {
        //i position swaps to j position
        int j = keyword.find(keywordsorted[i]);
        
        //set reordered rows based on swaps made
        //to keyword
        for (int k = 0; k < xsize; k++)
        {
            reordered[j][k] = array[i][k];
        }
    }
    ciphertext = "";
    //copy table into ciphertext string
    for (int i = 0; i < xsize; i++)
    {
        for (int j = 0; j < ysize; j++)
        {
            ciphertext.push_back(reordered[j][i]);
        }
    }
    return ciphertext;
}

int main(int argc, char ** argv)
{
    
    char continp;
    
    while (continp != 'y')
    {
    
        string message = "";
        
        cout << "message: ";
        cin >> message;
        
        string keyword = "";
        cout << "keyword: ";
        cin >> keyword;
        
        while (message.length() % keyword.length() != 0)
        {
            message.push_back('x');
        }

        char mode;
        cout << "encipher (e) decipher (d): ";
        cin >> mode;
        
        if (mode == 'e')
        {
        
            string ciphertext = table_encipher_string(message);
        
            ciphertext = columnar_encipher(ciphertext, keyword);
        
            cout << "ciphertext: " << ciphertext << endl;
        }
        else if (mode == 'd')
        {
            string plaintext = columnar_decipher(message, keyword);
            
            plaintext = table_decipher_string(plaintext);
            
            cout << "plaintext: " << plaintext << endl;
        }
        else
        {
            cout << "unknown input" << endl;
        }
    
        cout << "quit (y/n): ";
        cin >> continp;
        
    }
        
    return 0;
}
