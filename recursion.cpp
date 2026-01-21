#include<bits/stdc++.h>
using namespace std;

static inline bool is_func(char c){
    return c == 's' || c == 'c' || c == 'e' || c == 'q' || c == 'f';
}

static inline double apply_func(char c, double v){
    if(c == 's')
        return sin(v);
    if(c == 'c')
        return cos(v);
    if(c == 'e')
        return exp(v);
    if(c == 'q')
        return sqrt(v);
    if(c == 'f')
        return fabs(v);
    return v;
}

string pow_log_process(string s){
    for(int i = 0; i < (int)s.length(); i++){
        if(s[i] == 'l' && i + 2 < (int)s.length() && s[i + 1] == 'o' && s[i + 2] == 'g'){
            s = s.substr(0, i) + 'l' + s.substr(i + 3);
        }else if(s[i] == 'p' && i + 2 < (int)s.length() && s[i + 1] == 'o' && s[i + 2] == 'w'){
            s = s.substr(0, i) + 'p' + s.substr(i + 3);
        }
    }
    return s;
}

string func_process(string s){
    for(int i = 0; i < (int)s.length(); i++){
        if(s[i] == 'e' && i + 1 < (int)s.length() && s[i + 1] == 'x'){
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
        }else if(s[i] == 's' && i + 1 < (int)s.length() && s[i + 1] == 'i'){
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
        }else if(s[i] == 'c' && i + 1 < (int)s.length() && s[i + 1] == 'o'){
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
        }else if(s[i] == 's' && i + 1 < (int)s.length() && s[i + 1] == 'q'){
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
        }else if(s[i] == 'f' && i + 1 < (int)s.length() && s[i + 1] == 'a'){
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

double main_solve(int* index, char op, double subtotal, double num, string s);
double multiply(int* index, char op, double subtotal, double num, string s);
double column(int* index, char op, double subtotal, double num, string s);
double pow_log(int* index, char opl, double subtotal, double num, string s);
double main_pl(int* index, char op, double subtotal, double num, string s, int border);

vector<double> digit;
int dt = 0;

double main_solve(int* index, char op, double subtotal, double num, string s){
    if(*index >= s.length()){
        if(op == '+')
            subtotal += num;
        if(op == '-')
            subtotal -= num;
        if(op == 's')
            subtotal += num;
        return subtotal;
    }

    if(isdigit(s[*index])){
        num = digit[dt];
        dt++;
        (*index)++;
        return main_solve(index, op, subtotal, num, s);
    }else{
        if(s[*index] == '+' || s[*index] == '-') {
            if(op == '+' || op == 's')
                subtotal += num;
            else if(op == '-')
                subtotal -= num;

            (*index)++;
            return main_solve(index, s[*index - 1], subtotal, num, s); 
        }else if(s[*index] == '*' || s[*index] == '/'){
            (*index)++;
            double temp = multiply(index, s[*index - 1], num, num, s);
            if(op == '+')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            else if(op == 's')
                subtotal = temp;
            else 
                printf("error\n");
            
            (*index)++;
            return main_solve(index, s[*index - 1], subtotal, num, s);
        }else if(s[*index] == '('){
            (*index)++ ;
            double temp = column(index, s[*index - 1], 0, num, s);
            if(*index + 1 < s.length() && (s[*index + 1] == '*' || s[*index + 1] == '/')){
                (*index)++;
                double temp2 = multiply(index, s[*index - 1], temp, temp, s);
                temp = temp2; 
            }
            
            if(op == '+')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            else if(op == 's')
                subtotal = temp;
            else
                printf("error\n");
            //index handling
            (*index)++; 
            return main_solve(index, s[*index - 1], subtotal, num, s);
        }else if(s[*index] == 'p' || s[*index] == 'l'){
            (*index)++;
            double temp = pow_log(index, s[*index - 1], 0, num, s);
            if(*index + 1 < s.length() && (s[*index + 1] == '*' || s[*index + 1] == '/')){
                (*index)++;
                double temp2 = multiply(index, s[*index - 1], temp, temp, s);
                temp = temp2; 
            }

            if(op == '+')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            else if(op == 's')
                subtotal = temp;
            else
                printf("error\n");
            //index handling
            (*index)++; 
            return main_solve(index, s[*index - 1], subtotal, num, s);


        } 
    }
    return subtotal;
}

double multiply(int* index, char op, double subtotal, double num, string s){
    if(*index >= s.length()){
        if(op == '*')
            subtotal *= num;
        else if(op == '/')
            subtotal /= num;
        return subtotal;
    }
    

    if(isdigit(s[*index])){
        num = digit[dt];
        dt++;
        (*index)++;
        return multiply(index, op, subtotal, num, s); 
    }else{
        if(s[*index] != '*' && s[*index] != '/' && s[*index] != '(' && s[*index] != 'l' && s[*index] != 'p'){
            if(op == '*')
                subtotal *= num;
            if(op == '/')
                subtotal /= num;
            //cout<<"test"<<endl;//test 
            return subtotal;
        }else if(s[*index] == '('){
            (*index)++;
            double temp = column(index, s[*index - 1], 0, num, s);
            if(op == '*')
                subtotal *= temp;
            else if(op == '/')
                subtotal /= temp;
            //index
            (*index)++;
            return multiply(index, s[*index - 1], subtotal, num, s);
        }else if(s[*index] == '*' || s[*index] == '/'){
            (*index)++;
            if(op == '*')
                subtotal *= num;
            else if(op == '/')
                subtotal /= num;
            return multiply(index, s[*index - 1], subtotal, num, s);
 
        }else if(s[*index] == 'l' || s[*index] == 'p'){
            (*index)++;
            double temp = pow_log(index, s[*index - 1] , 0, num, s);
            if(op == '*')
                subtotal *= temp;
            else if(op == '/')
                subtotal /= temp;
            //index
            (*index)++;
            return multiply(index, s[*index - 1], subtotal, num, s);
        }
    }   
    return subtotal;
}

double column(int* index, char op, double subtotal, double num, string s){
    if(*index >= s.length()){
        cout<<"there"<<endl;
        return subtotal;
    }
        
    if(isdigit(s[*index])){
        num = digit[dt];
        dt++;
        (*index)++;
        return column(index, op, subtotal, num, s);
    }else{
        if(s[*index] == ')'){
            if(op == ')'){
                //return subtotal;
            }else if(op == '*'){
                //return subtotal;
            }else if(op == '/'){
                //return subtotal;
            }else if(op == '+'){
                subtotal += num;
                //return subtotal;
            }else if(op == '-'){
                subtotal -= num;
                //return subtotal;
            }else if(op == '('){
                subtotal += num;
                //return subtotal;
            }else if(op == 's'){
                subtotal += num;
                //return subtotal;
            }else{
                //return subtotal;
            }
            if(*index + 1 < s.length() && is_func(s[*index + 1])){
                (*index)++;
                subtotal = apply_func(s[*index], subtotal);
            }
            return subtotal;
            
            
        }else if(s[*index] == '*' || s[*index] == '/'){
            (*index)++;
            double temp = multiply(index, s[*index - 1], num, num, s);
            if(op == '+' || op == '(')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            if(s[*index] == ')'){
                if(*index + 1 < s.length() && is_func(s[*index + 1])){
                    (*index)++;
                    subtotal = apply_func(s[*index], subtotal);
                }
                return subtotal;
            }else{
                (*index)++;
                return column(index, s[*index - 1], subtotal, num, s);
            }
        }else if(s[*index] == '('){
            (*index)++;
            double temp = column(index, s[*index - 1], 0, num, s);
            
            if(*index + 1 < s.length() && (s[*index + 1] == '*' || s[*index + 1] == '/')){
                (*index)++;
                double temp2 = multiply(index, s[*index - 1], temp, temp, s);
                temp = temp2;
            }

            if(op == '+' || op == '(')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            (*index)++;
            return column(index, s[*index - 1], subtotal, num, s);
        }else if(s[*index] == '+' || s[*index] == '-'){
            if(op == '+' || op == '(')
                subtotal += num;
            else if(op == '-')
                subtotal -= num;
            (*index)++;
            return column(index, s[*index - 1], subtotal, num, s);
        }else if(s[*index] == 'l' || s[*index] == 'p'){
            (*index)++;
            double temp = pow_log(index, s[*index - 1], 0, num, s);
            if(*index + 1 < s.length() && (s[*index + 1] == '*' || s[*index + 1] == '/')){
                (*index)++;
                double temp2 = multiply(index, s[*index - 1], temp, temp, s);
                temp = temp2;
            }

            if(op == '+' || op == '(')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            (*index)++;
            return column(index, s[*index - 1], subtotal, num, s);
        }
    }
    return subtotal;
}

double pow_log(int* index, char opl, double subtotal, double num, string s){
    int tempi = *index;
    int tc = 0;
    //cout<<s[tempi]<<endl; //test
    while(true){
        if(s[tempi] == '(')
            tc++;
        if(s[tempi] == ')')
            tc--;
        if(tempi >= s.length())
            break;
        //cout<<tc<<" "<<s[tempi]<<endl;//test
        
        if(tc == 1 && s[tempi] == ',')
            break;
        tempi++;
    }
        
    (*index)++;
    //cout<<"test"<<s[*index + 1]<<endl;//test
    //cout<<"s[tempi] = "<<s[tempi]<<endl;
    //cout<<"test2"<<endl; //test
    //cout<<"tempi"<<tempi<<endl; //test;
    double tot1 = main_pl(index, 's', 0, num, s, tempi);
    //cout<<*index<<endl;//test

    tempi = *index;
    int tk = 0;
    while(s[tempi] != ')' || tk != 0){
        
        if(s[tempi] == '(')
            tk++;
        if(s[tempi] == ')')
            tk--;
        if(tempi >= s.length())
            break;
        
        tempi++;
        
    }
    (*index)++;
    //cout<<"test"<<s[*index]<<endl;//test
    double tot2 = main_pl(index, 's', 0, num, s, tempi);
    //cout<<tot2<<endl;

    if(opl == 'l'){
        return log10(tot2) / log10(tot1);
    }else if(opl == 'p'){
        return pow(tot1, tot2);
    }
    return 0;
}

double main_pl(int* index, char op, double subtotal, double num, string s, int border){
    if(*index >= border){
        if(op == '+')
            subtotal += num;
        if(op == '-')
            subtotal -= num;
        if(op == 's')
            subtotal += num;
        
        return subtotal;
    }

    if(isdigit(s[*index])){
        num = digit[dt];
        dt++;
        (*index)++;
        //cout<<"num test: "<<num<<endl;//test
        return main_pl(index, op, subtotal, num, s, border);
    }else{
        if(s[*index] == '+' || s[*index] == '-') {
            if(op == '+' || op == 's')
                subtotal += num;
            else if(op == '-')
                subtotal -= num;
            if(*index < border)
                (*index)++;
            return main_pl(index, s[*index - 1], subtotal, num, s, border); 
        }else if(s[*index] == '*' || s[*index] == '/'){
            (*index)++;
            double temp = multiply(index, s[*index - 1], num, num, s);
            if(op == '+')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            else if(op == 's')
                subtotal = temp;
            else 
                printf("error\n");
            
            if(*index < border)
                (*index)++;
            return main_pl(index, s[*index - 1], subtotal, num, s, border);
        }else if(s[*index] == '('){
            (*index)++ ;
            double temp = column(index, s[*index - 1], 0, num, s);
            if(*index + 1 < s.length() && (s[*index + 1] == '*' || s[*index + 1] == '/')){
                (*index)++;
                double temp2 = multiply(index, s[*index - 1], temp, temp, s);
                temp = temp2; 
            }
            
            if(op == '+')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            else if(op == 's')
                subtotal = temp;
            else
                printf("error\n");
            
            
            //index handling
            //cout<<"border: "<<s[border]<<endl;
            //cout<<"s[index]: "<<s[*index]<<endl;
            if(*index < border)
                (*index)++;
            //cout<<s[*index]<<endl;
            return main_pl(index, s[*index - 1], subtotal, num, s, border);
        }else if(s[*index] == 'p' || s[*index] == 'l'){
            (*index)++;
            double temp = pow_log(index, s[*index - 1], 0, num, s);
            if(*index + 1 < s.length() && (s[*index + 1] == '*' || s[*index + 1] == '/')){
                (*index)++;
                double temp2 = multiply(index, s[*index - 1], temp, temp, s);
                temp = temp2; 
            }

            if(op == '+')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            else if(op == 's')
                subtotal = temp;
            else
                printf("error\n");
            //index handling
            if(*index < border)
                (*index)++; 
            return main_pl(index, s[*index - 1], subtotal, num, s, border);


        } 
    }
    return subtotal;
}



string process(string s){
    int n = s.length();
    string res;
    int t = 0;
    string temp = "";
    for(int i = 0; i < n; i++){
        if(isdigit(s[i]) || s[i] == '.'){
            temp += s[i];
        }else if(i && (isdigit(s[i - 1]) || s[i - 1] == '.')){
            digit.push_back(stod(temp));
            temp = "";
            res += '0';
            res += s[i];
        }else{
            res += s[i];
        }
    }

    if(temp != ""){
        res += '0';
        digit.push_back(stod(temp));
    }

    return res;

}

int main(){
    string s;
    cin>>s;
    s = pow_log_process(s);
    s = func_process(s);
    s = process(s);
    //cout<<process(s)<<endl; //test
    //for(int i = 0; i < digit.size(); i++)
        //cout<<digit[i]<<" "; //test
    //cout<<endl; //test
    
    int* index = new int;
    *index = 0;
    cout<<main_solve(index, 's', 0, 0, s)<<endl;//test
    //cout<<digit[dt]<<endl;//test

    return 0;
}
