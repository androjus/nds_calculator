#include "calc_fun.h"
PrintConsole topScreen;
vector <string> action;
bool isPressed = false;
bool isCalculated = false;
string button_list[4][4]{
{
    "7", "8", "9", "*"
},
{
    "4", "5", "6", "/"
},
{
    "1", "2", "3", "-"
},
{
    "0", "DEL", "=", "+"
}
};

int button_mapping[4][4][4]={
    0,0,62,46,    65,0,127,46,    129,0,191,46,    192,0,255,46,
    0,49,62,94,   65,49,127,94,   129,49,191,94,   192,49,255,94,
    0,97,62,142,  65,97,127,142,  129,97,191,142,  192,97,255,142,
    0,145,62,191, 65,145,127,191, 129,145,191,191, 192,145,255,191
};
int VectorToInt(vector<string> x){
    vector<int> v;
    for (vector<int>::size_type i=0; i<x.size(); i++)
    {
        int num = atoi(x.at(i).c_str());
        v.push_back(num);
    }
    reverse(v.begin(), v.end());
    int decimal = 1;
    int total = 0;
    for (auto& it : v)
    {
        total += it * decimal;
        decimal *= 10;
    }
    return total;
}
void DoCalc(vector<string> eq){
    float res;
    for(vector<int>::size_type i=0; i<eq.size(); i++){
        if(eq[i]=="+" || eq[i]=="-" || eq[i]=="/" || eq[i]=="*"){
            size_t const mid = i;
            vector<string> first_s(eq.begin(), eq.begin() + mid);
            vector<string> second_s(eq.begin() + mid+1, eq.end());
            int first = VectorToInt(first_s);
            int second = VectorToInt(second_s);
            if(eq[i]=="+")
                res = first + second;
            if(eq[i]=="-")
                res = first - second;
            if(eq[i]=="*")
                res = first * second;
            if(eq[i]=="/")
                res = (float)first / (float)second;
            printf("=%0.2f", res);
            isCalculated = true;
            return;
        }
    }

}

void Clear(){
    consoleClear();
    printf("\x1b[18;1H");
    action.clear();
    isCalculated = false;
}
void onClicks(string chars){
    if(chars == "DEL"){
        Clear();
        return;
    }
    else{
        if(chars == "="){
            DoCalc(action);
        }
        else{
            action.push_back(chars);
            printf("%s", chars.c_str());
        }
    }
}

void CheckTouch()
{
	touchPosition touch;
	touchRead (&touch);
	if(touch.py == 0 && touch.px == 0){
        isPressed = false;
        return;
	}
	for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            if(touch.px>button_mapping[i][j][0] && touch.px<button_mapping[i][j][2] && touch.py>button_mapping[i][j][1] && touch.py<button_mapping[i][j][3]){
                if(isPressed == false){
                    if(isCalculated) Clear();
                    onClicks(button_list[i][j]);
                }
                isPressed = true;
                return;
        }
	}}
	return;
}
