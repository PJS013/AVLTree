#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
#include "lab2.hpp"
#include "avl.hpp"

using namespace std;

Dictionary<string, int>& counter (const string& fileName) {
    static Dictionary<string, int> dic;
    int x;
    string line;
    ifstream file(fileName);
    if(file.is_open())
    {
        while(file>>line) {

            if(dic.contain(line)==0)
            dic.insertIntoDictionary(line, 1);
            else {
                dic.setInfo(line, dic.getInfo(line)+1);
            }
            }
        }
        file.close();
    return dic;
}

Ring <int, string>& listing (Dictionary <string, int>& dic){
    static Ring<int, string> ring;
    dic.pushIntoRing(ring, 1);
    char expr;
    string word;
    int occ;
    cout<<"What do you want to do?"<<endl;
    cout<<"Display ring forward (f)"<<endl;
    cout<<"Display ring backward (b)"<<endl;
    cout<<"Search for a word (s)"<<endl;
    cout<<"Search for number of occurrences (n)"<<endl;
    cin>>expr;
    switch(expr) {
    case 'f':
        ring.printRing(1);
        cout<<endl<<endl;
        break;
    case 'b':
        ring.printRing(0);
        cout<<endl<<endl;
        break;
    case 's':
        cout<<"Write the word that you're looking for"<<endl;
        cin>>word;
        ring.findInfo(word);
        break;
    case 'n':
        cout<<"Write the number of occurrences that you're looking for"<<endl;
        cin>>occ;
        ring.findKey(occ);
        break;
    }

    return ring;
}

int main() {
    Dictionary<string, int> dic;
    char again;
    int option;

    dic.insertIntoDictionary("aa", 1);
    dic.insertIntoDictionary("ab", 3);
    dic.insertIntoDictionary("cc", 5);
    dic.insertIntoDictionary("no", 7);
    dic.insertIntoDictionary("one", 9);
    dic.insertIntoDictionary("key", 11);
    dic.insertIntoDictionary("not", 13);
    dic.insertIntoDictionary("and", 15);
    dic.insertIntoDictionary("or", 17);
    dic.insertIntoDictionary("if", 19);
    dic.insertIntoDictionary("what", 21);
    dic.insertIntoDictionary("who", 23);
    dic.insertIntoDictionary("he", 25);
    dic.insertIntoDictionary("she", 27);
    dic.insertIntoDictionary("it", 29);

    dic.printGraph();
    do{
    cout<<"Which file do you want to open?"<<endl;
    cout<<"1. Academic Regulations at the Warsaw University of Technology (ANSI).txt"<<endl;
    cout<<"2. On the Origin of Species, by Charles Darwin.txt"<<endl;
    cout<<"3. The bible.txt"<<endl;
    cout<<"Enter the number standing next to corresponding text file"<<endl;
    cin>>option;
switch(option) {
    case 1:
        listing(counter("Academic Regulations at the Warsaw University of Technology (ANSI).txt"));
        break;
    case 2:
        listing(counter("On the Origin of Species, by Charles Darwin.txt"));
        break;
    case 3:
        listing(counter("The bible.txt"));
        break;
    }
    cout<<"Do you want to do it again?"<<endl;
    cout<<"y for yes, or n for no"<<endl;
    cin>>again;
    } while(again=='y');
    return 0;
}
