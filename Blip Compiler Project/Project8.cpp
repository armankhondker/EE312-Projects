/*Arman Khondker
 *EID: aak2464
 *EE 312 - Project 8
 *
 */

#include "Project8.h"
map<String, int> vars;   //map to hold all of the variables
vector<String> blip;     //a vector to hold the expression

int operations(String operatr, int inputA, int inputB) //function for all the possible operators that will be in the expression
{
    int x = inputA;
    int y = inputB;
    if (operatr == ">"){   return (x > y);}
    else if (operatr == "<"){  return (x < y);}
    else if (operatr == ">="){ return (x >= y);}
    else if (operatr == "<="){ return (x <= y);}
    else if (operatr == "=="){ return (x == y);}
    else if (operatr == "!="){ return (x != y);}
    else if (operatr == "+"){ return (x + y);}
    else if (operatr == "-"){ return (x - y);}
    else if (operatr == "*"){ return (x * y);}
    else if (operatr == "/"){ return (x / y);}
    else if (operatr == "&&"){ return (x && y);}
    else if (operatr == "||"){ return (x || y);}
    else if (operatr == "%"){ return (x % y);}
}

void initVar()
{
    read_next_token();
    String var = String(next_token());     //set the variable
    blipGenerator();
    if (vars.find(var) != vars.end())       //check if it has been initialized  already
    {
        cout << "variable " << var.c_str() << " incorrectly re-initialized" << endl;
    }
    vars[var] = polishRecursively(blip);
    blip.clear();
}

void setVar()
{
    read_next_token();
    String var = String(next_token());
    blipGenerator();
    if (vars.find(var) == vars.end())
    {
        cout << "variable "<< var.c_str()<< " not declared" << endl;
    }

    vars[var] = polishRecursively(blip);
    blip.clear();
}

void blipGenerator()
{
    String t = String("text");
    String o = String("output");
    String v = String("var");
    String s = String("set");
    String checker = String(peek_next_token());
    for(;next_token_type != END && checker != t && checker != o && checker != v && checker != s; checker = String(peek_next_token()))
    {
        read_next_token();   //get next token
        String firstOp = String(next_token()); //create a String to store it in
        if (firstOp == "//") { skip_line(); }
        blip.push_back(firstOp);        //add it to the blip vector
    }

}

void run()
{
    String v = String("var");
    String s = String("set");
    String t = String("text");
    String o = String("output");
    for (; next_token_type != END; read_next_token())
    {
        String token = String(next_token());
        if (token == "//") { skip_line(); }
        else if (token == t)
        {
            read_next_token();
            String text1 = String(next_token());
            if (text1 == "//") { skip_line(); }
            cout << next_token();
            continue;
        }
        else if (token == v)
        {
            initVar();
            continue;
        }
        else if (token == s)
        {
            setVar();
            continue;
        }
        else if (token == o)
        {
            blipGenerator();
            cout << polishRecursively(blip);
            blip.clear();
        }
    }
    vars.clear();
}

int polishRecursively(vector<String>& blipExpres)
{
    String frontElement = blipExpres.front();   //get the first element

    if (!(vars.find(frontElement) == vars.end()))   //check to see if the first is at the end of the vector
    {
        blipExpres.erase(blipExpres.begin());
        return vars[frontElement];
    }

    else if (frontElement != ">" && frontElement != "<" && frontElement != ">=" && frontElement != "<=" && frontElement != "==" && frontElement != "!=" && frontElement != "+" && frontElement != "-" && frontElement != "*" && frontElement != "/" &&
             frontElement != "%" && frontElement != "&&" && frontElement != "||"  && frontElement != "!" && frontElement!= "~")
    {
        blipExpres.erase(blipExpres.begin());
        return atoi(frontElement.c_str());                //convert to integer value
    }
    else if (frontElement == "~" )
    {
        blipExpres.erase(blipExpres.begin());
        int blipExpreses = polishRecursively(blipExpres);
         blipExpreses *= -1;
        return blipExpreses;

    }
    else if (frontElement != "!")
    {
        blipExpres.erase(blipExpres.begin());
        int inputA = polishRecursively(blipExpres);
        int inputB = polishRecursively(blipExpres);
        return operations(frontElement, inputA, inputB);   //call the function again recursively
    }
    else if( frontElement == "!")
    {
        blipExpres.erase(blipExpres.begin());
        int blipExpreses = polishRecursively(blipExpres);
        if (blipExpreses != 0)
        {
            return false;
        }
        else if (blipExpreses == 0)
        {
            return true;    //in this case it will be zero so return true
        }
    }

}


