#include<bits/stdc++.h>
using namespace std;

int main_solve(int* index, char op, int subtotal, int num, string s);
int multiply(int* index, char op, int subtotal, int num, string s);
int column(int* index, char op, int subtotal, int num, string s);

vector<int> digit;
int dt = 0;

int main_solve(int* index, char op, int subtotal, int num, string s){
    if(*index >= s.length()){
        if(op == '+')
            subtotal += num;
        if(op == '-')
            subtotal -= num;
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
            int temp = multiply(index, s[*index - 1], num, num, s);
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
            int temp = column(index, s[*index - 1], 0, num, s);
            if(*index + 1 < s.length() && (s[*index + 1] == '*' || s[*index + 1] == '/')){
                (*index)++;
                int temp2 = multiply(index, s[*index - 1], temp, temp, s);
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
}

int multiply(int* index, char op, int subtotal, int num, string s){
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
        if(s[*index] != '*' && s[*index] != '/' && s[*index] != '('){
            if(op == '*')
                subtotal *= num;
            if(op == '/')
                subtotal /= num;
            //cout<<"test"<<endl;//test 
            return subtotal;
        }else if(s[*index] == '('){
            (*index)++;
            int temp = column(index, s[*index - 1], 0, num, s);
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
 
        }
    }   
}

int column(int* index, char op, int subtotal, int num, string s){
    if(*index >= s.length())
        return subtotal;
    if(isdigit(s[*index])){
        num = digit[dt];
        dt++;
        (*index)++;
        return column(index, op, subtotal, num, s);
    }else{
        if(s[*index] == ')'){
            if(op == ')'){
                return subtotal;
            }else if(op == '*'){
                return subtotal;
            }else if(op == '/'){
                return subtotal;
            }else if(op == '+'){
                subtotal += num;
                return subtotal;
            }else if(op == '-'){
                subtotal -= num;
                return subtotal;
            }else
                printf("column error\n");
            
        }else if(s[*index] == '*' || s[*index] == '/'){
            (*index)++;
            int temp = multiply(index, s[*index - 1], num, num, s);
            if(op == '+' || op == '(')
                subtotal += temp;
            else if(op == '-')
                subtotal -= temp;
            if(s[*index] == ')'){
                return subtotal;
            }else{
                (*index)++;
                return column(index, s[*index - 1], subtotal, num, s);
            }
        }else if(s[*index] == '('){
            (*index)++;
            int temp = column(index, s[*index - 1], 0, num, s);
            
            if(*index + 1 < s.length() && (s[*index + 1] == '*' || s[*index + 1] == '/')){
                (*index)++;
                int temp2 = multiply(index, s[*index - 1], temp, temp, s);
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
        }
    }
}

string process(string s){
    int n = s.length();
    string res;
    int t = 0;
    string temp = "";
    for(int i = 0; i < n; i++){
        if(isdigit(s[i])){
            temp += s[i];
        }else if(i && isdigit(s[i - 1])){
            digit.push_back(stoi(temp));
            temp = "";
            res += '0';
            res += s[i];
        }else{
            res += s[i];
        }
    }

    if(temp != ""){
        res += '0';
        digit.push_back(stoi(temp));
    }

    return res;

}

int main(){
    string s;
    cin>>s;
    s = process(s);
    //cout<<process(s)<<endl;
    //for(int i = 0; i < digit.size(); i++)
        //cout<<digit[i]<<" ";
    int* index = new int;
    *index = 0;
    cout<<main_solve(index, 's', 0, 0, s)<<endl;    


    return 0;
}
