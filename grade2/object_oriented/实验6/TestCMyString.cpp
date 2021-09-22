#include "CMyString.h"
int main(){
    CMyString s1("BIT"), s2;
    CMyString ending('!');
    s2 = "love";
    s2[0] = 'L';
    cout << "I " + s2<< " " << s1 + ending + '\n'; // The output is:  I Love BIT

    int pos = s1.Find('T');                   // pos is 2, or -1 if  'T'  is not found.
    cout<<"find T:"<<pos<<endl;
    pos = s1.Find("IT");                  // pos is 1, or -1 if  "IT"  is not found.
    cout<<"find IT:"<<pos<<endl;

    CMyString s3("Here are some spaces in this string.");
    s1 = s3 - ' ';                            // Remove all spaces
    cout << s1 << endl;                      // The output is: Herearesomespacesinthisstring.
    CMyString pat("some");

    cout<< s1.Find(pat)<<endl;

    CMyString str_num;
    str_num = "123";
    int int_str=str_num.ToInt();
    cout<<int_str<<endl;

    str_num = "123.456";
    double double_str=str_num.ToDouble();
    cout<<double_str<<endl;

    int a = 1, b = 2;
    CMyString my = s2.Mid(a, b); // a represents starting position, b represents the length of substring. So Mid can get a substring: ov.
    cout<<my<<endl;
}