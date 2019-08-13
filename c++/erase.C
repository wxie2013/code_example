#include <iostream>
#include <string>
using namespace std;

//Erases all characters after position ‘pos’
void eraseDemo1(string str)
{
    // Deletes all characters except first one
    str.erase(1);

    cout << "After erase(idx) : ";
    cout << str;
}

//Erases at most, len characters of *this, starting at index idx.
void eraseDemo2(string str)
{
    //string& string ::erase (size_type idx, size_type len )
    //- If len is missing, all remaining characters are removed.
    //- Throw out_of_range if idx > size().

    // Deletes 4 characters from index number 1
    str.erase(1, 4);

    cout << "After erase : ";
    cout << str;
}

//Erase the single character at iterator position pos.
void eraseDemo3(string str)
{
    //string& string ::erase (iterator pos)
    //- Return the first character after the last character removed
    //- If no such character is remaining then, returns
    //  string::end() i.e. position after the last character.

    // Deletes character at position 4
    str.erase(str.begin() + 4);

    cout << "After erase : ";
    cout << str;
}

//Erase the single character at iterator position pos
void eraseDemo(string str)
{
    //string& string ::erase (iterator beg, iterator end )
    //- Erases all characters of the range [ beg, end)
    //- Returns end i.e. the first character after the
    //  last character removed.
    //- If no such character is remaining then, returns
    //  string::end() i.e. position after the last character

        // Deletes all characters between 0th index and
    // str.end() - 6
    str.erase(str.begin() + 0, str.end() - 6);

    cout << "After erase : ";
    cout << str;
}


// Driver code
int main()
{
    string str("Hello World!");

    cout << "Before erase(idx) : ";
    cout << str << endl;
    eraseDemo1(str);
    eraseDemo2(str);

    return 0;
}


