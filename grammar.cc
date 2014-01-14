
#include "grammar.hpp"
#include <fstream>
using namespace std;
using namespace boost::regex_constants;

Token::Token(string _name, string _expr):name(_name),
    rgx(boost::regex(_expr)), expr(_expr) {};


RuleNode::RuleNode(string _value, string _separator, int _chain_type):
    value(_value), separator(_separator), chain_type(_chain_type) {};


bool Parser::ReadGrammarFile(string path)
{
    ifstream ifs(path, ios::binary|ios::in);
    string content;
    content.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());

    // remove comment
    //content = "hello world";
    //regex e("h");
    //string substitute("fuck");
    //auto tmp = regex_replace(content, e, substitute);
    //cout << content;
    //cout << tmp;

    //cout << "end";

    string s ("there is a subsequence in the string\n");
    boost::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

    //using string/c-string (3) version:
    cout << boost::regex_replace (s, e, string("sub-$2"));
    //string t1 = "hello world second";
    //regex e1("world");
    //cout << regex_replace(t1, e1, string("end"));
    //cout << content << endl;

    return true;
}
