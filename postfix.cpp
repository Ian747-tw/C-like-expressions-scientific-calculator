#include<bits/stdc++.h> 
using namespace std;

string pow_log_process(string s){
    for(int i = 0; i < s.length(); i++){
        if((s[i] == 'l' && i + 1 < s.length() && s[i + 1] == 'o') || (s[i] == 'p' && i + 1 < s.length() && s[i + 1] == 'o')){
            int tempi = i + 4;
            int ct = 1;
            string substr0 = s.substr(0, i);
            string substr1 = "";
            while(!(ct == 1 && s[tempi] == ',')){
                substr1 += s[tempi];
                if(s[tempi] == '(')
                    ct++;
                if(s[tempi] == ')')
                    ct--;
                tempi++;
            }

            tempi++;

            ct = 0;
            string substr2 = "";
            while(!(ct == 0 && s[tempi] == ')')){
                substr2 += s[tempi];
                if(s[tempi] == '(')
                    ct++;
                if(s[tempi] == ')')
                    ct--;
                tempi++;

            }
            string substr3 = s.substr(tempi + 1);

            s = substr0 + '(' + '(' + substr1 + ')' + '(' + substr2 + ')' + ')' + s[i] + substr3;

        }
    }
    return s;
}

string func_process(string s){
    for(int i = 0; i < s.length(); i++){
        if(s[i] == 'e' && i + 1 < s.length() && s[i + 1] == 'x'){
            string substr0 = s.substr(0, i);
            int tempi = i + 3;
            string substr1 = "";
            int ct = 0;

            while(!(ct == 1 && s[tempi] == ')')){
                substr1 += s[tempi];
                if(s[tempi] == '(')
                    ct++;
                if(s[tempi] == ')')
                    ct--;
                tempi++;
            }

            substr1 += ')';

            string substr2 = s.substr(tempi + 1);

            s = substr0 + substr1 + s[i] + substr2;
        }else if(s[i] == 's' && i + 1 < s.length() && s[i + 1] == 'i'){
            string substr0 = s.substr(0, i);
            int tempi = i + 3;
            string substr1 = "";
            int ct = 0;

            while(!(ct == 1 && s[tempi] == ')')){
                substr1 += s[tempi];
                if(s[tempi] == '(')
                    ct++;
                if(s[tempi] == ')')
                    ct--;
                tempi++;
            }

            substr1 += ')';

            string substr2 = s.substr(tempi + 1);

            s = substr0 + substr1 + s[i] + substr2;
        }else if(s[i] == 'c' && i + 1 < s.length() && s[i + 1] == 'o'){
            string substr0 = s.substr(0, i);
            int tempi = i + 3;
            string substr1 = "";
            int ct = 0;

            while(!(ct == 1 && s[tempi] == ')')){
                substr1 += s[tempi];
                if(s[tempi] == '(')
                    ct++;
                if(s[tempi] == ')')
                    ct--;
                tempi++;
            }

            substr1 += ')';

            string substr2 = s.substr(tempi + 1);

            s = substr0 + substr1 + s[i] + substr2;
        }else if(s[i] == 't' && i + 1 < s.length() && s[i + 1] == 'a'){
            string substr0 = s.substr(0, i);
            int tempi = i + 3;
            string substr1 = "";
            int ct = 0;

            while(!(ct == 1 && s[tempi] == ')')){
                substr1 += s[tempi];
                if(s[tempi] == '(')
                    ct++;
                if(s[tempi] == ')')
                    ct--;
                tempi++;
            }

            substr1 += ')';

            string substr2 = s.substr(tempi + 1);

            s = substr0 + substr1 + s[i] + substr2;
        }else if(s[i] == 's' && i + 1 < s.length() && s[i + 1] == 'q'){
            string substr0 = s.substr(0, i);
            int tempi = i + 4;
            string substr1 = "";
            int ct = 0;

            while(!(ct == 1 && s[tempi] == ')')){
                substr1 += s[tempi];
                if(s[tempi] == '(')
                    ct++;
                if(s[tempi] == ')')
                    ct--;
                tempi++;
            }

            substr1 += ')';

            string substr2 = s.substr(tempi + 1);

            s = substr0 + substr1 + s[i + 1] + substr2;
        }else if(s[i] == 'f' && i + 1 < s.length() && s[i + 1] == 'a'){
            string substr0 = s.substr(0, i);
            int tempi = i + 4;
            string substr1 = "";
            int ct = 0;

            while(!(ct == 1 && s[tempi] == ')')){
                substr1 += s[tempi];
                if(s[tempi] == '(')
                    ct++;
                if(s[tempi] == ')')
                    ct--;
                tempi++;
            }

            substr1 += ')';

            string substr2 = s.substr(tempi + 1);

            s = substr0 + substr1 + s[i] + substr2;
        }
    }

    return s;
}

string unary_process(string s){
    int n = s.length();
    for(int i = n - 1; i >= 0; i--){
        if((i == 0 && (s[i] == '+' || s[i] == '-' || s[i] == '!' || s[i] == '~')) || (i > 0 && (s[i] == '+' || s[i] == '-' || s[i] == '!' || s[i] == '~') && (!(isdigit(s[i-1]) || s[i-1] == '.') && !isalpha(s[i-1]) && s[i-1] != ')')  )){
            if(s[i + 1] == '('){
                int ct = 1;
                int tempi = i + 2;
                string substr0 = s.substr(0, i);
                string substr1 = "";
                
                while(!(ct == 1 && s[tempi] == ')')){
                    if(s[tempi] == '(')
                        ct++;
                    if(s[tempi] == ')')
                        ct--;
                    substr1 += s[tempi];
                    tempi++;    
                }
                
                string substr2 = "";
                string substr3 = s.substr(tempi + 1);
                if(isalpha(s[tempi + 1]) && s[tempi + 1] != 'z'){
                    substr2 += s[tempi + 1];
                    substr3 = s.substr(tempi + 2);
                }
                if(s[tempi + 1] == 'u'){
                    substr2 += s[tempi + 2];
                    substr3 = s.substr(tempi + 3);
                }
                s = substr0 + '(' + '(' + substr1 + ')' + substr2 + ')' + 'u' + s[i] + substr3;
            }else if(isdigit(s[i + 1]) || s[i + 1] == '.'){
                string substr0 = s.substr(0, i);
                string substr1 = "";
                int tempi = i + 1;
                while(isdigit(s[tempi]) || s[tempi] == '.'){
                    substr1 += s[tempi];
                    tempi++;
                }
                string substr2 = s.substr(tempi);
                s = substr0 + '(' + substr1 + ')' + 'u' + s[i] + substr2;
            }else
                printf("error10\n");
                
        }
    }

    return s;
}

int main(){
    vector<string> op_stack;
    vector<string> main_stack;
    string line;
    cin>>line;
    line += 'z';
    line = pow_log_process(line);
    cout<<line<<endl;
    line = func_process(line);
    cout<<line<<endl;
    line = unary_process(line);
    cout<<line<<endl;

    unordered_map<string, int> priority = {
        {"||", 1},
        {"&&", 2},
        {"|", 3},
        {"^", 4},
        {"&", 5},
        {"==", 6},
        {"!=", 6},
        {"<<", 7},
        {">>", 7},
        {"+", 8},
        {"-", 8},
        {"*", 9},
        {"/", 9},
        {"%", 9},
    };
    vector<string> s;
    string tmp = "";
    for(int i = 0; i < line.length(); i++){
        if(isdigit(line[i]) || line[i] == '.'){
            tmp += line[i];
        }else if(i && isdigit(line[i - 1])){
            s.push_back(tmp);
            tmp = "";
        }
        if(line[i] == '>' || line[i] == '<'|| line[i] == '='|| line[i] == '&'|| line[i] == '|'|| line[i] == '<'){
            if(i + 1 < line.length() && line[i + 1] == line[i]){
                if(tmp == ""){
                    tmp += line[i];
                    tmp += line[i + 1];
                    i++;
                }else
                    printf("error1\n"); //test
            }else{
                if(tmp == "")
                    tmp += line[i];
                else
                    printf("error2\n"); //test
            }
            s.push_back(tmp);
            tmp = "";
        }else if(line[i] == '!'){
            if(i + 1 < line.length() && line[i + 1] == '='){
                if(tmp == ""){
                    tmp += line[i];
                    tmp += line[i + 1];
                    i++;
                }else
                    printf("error3\n"); //test
            }else{
                printf("error4\n"); //test
            }
            s.push_back(tmp);
            tmp = "";
        }else if(line[i] == 'u'){
            if(i + 1 < line.length()){
                if(tmp == ""){
                    tmp += line[i];
                    tmp += line[i + 1];
                    i++;
                }else
                    printf("error8\n");
            }else
                printf("error9\n");
            s.push_back(tmp);
            tmp = "";
        }else if(!isdigit(line[i]) && line[i] != '.' && line[i] != 'z'){
            if(tmp == "")
                tmp += line[i];
            else
                printf("error5\n"); //test
            s.push_back(tmp);
            tmp = "";
            
        }else if(line[i] == 'z'){
            printf("processed\n"); //test
        }else if(!isdigit(line[i]) && line[i] != '.')
            printf("error6\n");
        
    }

    for(int i = 0; i < s.size(); i++){
        cout<<s[i]<<"|";

    }
    cout<<endl;

    for(int i = 0; i < s.size(); i++){
        if(isdigit(s[i][0])){
            main_stack.push_back(s[i]);
        }else if(s[i] == "("){
            op_stack.push_back(s[i]);
        }else if(s[i] == ")"){
            while(!(op_stack.empty() || op_stack.back() == "(")){
                string temp = op_stack.back();
                op_stack.pop_back();
                main_stack.push_back(temp);
            }

            if(!op_stack.empty() && op_stack.back() == "(")
                op_stack.pop_back();
            if(i + 1 < s.size() && isalpha(s[i + 1][0])){ 
                i++;
                main_stack.push_back(s[i]);   
            }
        }else if(priority.count(s[i])){
            while(!(op_stack.empty() || op_stack.back() == "(" || priority[op_stack.back()] < priority[s[i]] )){
                string temp = op_stack.back();
                op_stack.pop_back();
                main_stack.push_back(temp);
            }
            op_stack.push_back(s[i]);
        }

    }

    while(!op_stack.empty()){
        string temp = op_stack.back();
        op_stack.pop_back();
        main_stack.push_back(temp);
    }
    //print postfix expression
    for(int i = 0; i < main_stack.size(); i++){
        cout<<main_stack[i]<<" ";
    }
    cout<<endl;

    auto is_number = [](const string& t){
        if(t.empty())
            return false;
        if(isdigit(t[0]) || t[0] == '.')
            return true;
        return false;
    };

    auto to_ll = [](double v){
        return (long long)(v);
    };

    vector<double> val_stack;
    for(const string& t : main_stack){
        if(is_number(t)){
            val_stack.push_back(stod(t));
            continue;
        }

        if(t == "u+" || t == "u-" || t == "u!" || t == "u~"){
            if(val_stack.empty()){
                printf("eval error\n");
                return 0;
            }
            double a = val_stack.back();
            val_stack.pop_back();
            if(t == "u+")
                val_stack.push_back(+a);
            else if(t == "u-")
                val_stack.push_back(-a);
            else if(t == "u!")
                val_stack.push_back((a == 0) ? 1 : 0);
            else if(t == "u~")
                val_stack.push_back((double)(~to_ll(a)));
            continue;
        }

        if(t == "s" || t == "c" || t == "e" || t == "q" || t == "f"){
            if(val_stack.empty()){
                printf("eval error\n");
                return 0;
            }
            double a = val_stack.back();
            val_stack.pop_back();
            if(t == "s")
                val_stack.push_back(sin(a));
            else if(t == "c")
                val_stack.push_back(cos(a));
            else if(t == "e")
                val_stack.push_back(exp(a));
            else if(t == "q")
                val_stack.push_back(sqrt(a));
            else if(t == "f")
                val_stack.push_back(fabs(a));
            continue;
        }

        if(t == "l" || t == "p"){
            if(val_stack.size() < 2){
                printf("eval error\n");
                return 0;
            }
            double b = val_stack.back(); val_stack.pop_back();
            double a = val_stack.back(); val_stack.pop_back();
            if(t == "l")
                val_stack.push_back(log10(b) / log10(a));
            else
                val_stack.push_back(pow(a, b));
            continue;
        }

        if(val_stack.size() < 2){
            printf("eval error\n");
            return 0;
        }
        double b = val_stack.back(); val_stack.pop_back();
        double a = val_stack.back(); val_stack.pop_back();

        if(t == "+")
            val_stack.push_back(a + b);
        else if(t == "-")
            val_stack.push_back(a - b);
        else if(t == "*")
            val_stack.push_back(a * b);
        else if(t == "/")
            val_stack.push_back(a / b);
        else if(t == "%")
            val_stack.push_back((double)(to_ll(a) % to_ll(b)));
        else if(t == "<<")
            val_stack.push_back((double)(to_ll(a) << to_ll(b)));
        else if(t == ">>")
            val_stack.push_back((double)(to_ll(a) >> to_ll(b)));
        else if(t == "==")
            val_stack.push_back((a == b) ? 1 : 0);
        else if(t == "!=")
            val_stack.push_back((a != b) ? 1 : 0);
        else if(t == "&")
            val_stack.push_back((double)(to_ll(a) & to_ll(b)));
        else if(t == "^")
            val_stack.push_back((double)(to_ll(a) ^ to_ll(b)));
        else if(t == "|")
            val_stack.push_back((double)(to_ll(a) | to_ll(b)));
        else if(t == "&&")
            val_stack.push_back((a != 0 && b != 0) ? 1 : 0);
        else if(t == "||")
            val_stack.push_back((a != 0 || b != 0) ? 1 : 0);
        else{
            printf("eval error\n");
            return 0;
        }
    }

    if(val_stack.size() != 1){
        printf("eval error\n");
        return 0;
    }
    cout<<val_stack.back()<<endl;



    





    return 0;
}
