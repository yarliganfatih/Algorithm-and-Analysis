#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <ctime>
using namespace std;
# define NO_OF_CHARS 256

string sentences[10000];
string questions[1000];

int resultIndex[100];
int countResult = 0;

string WHquestions[15] = {"how does" ,"what does" ,"where" , "what time" ,"what" ,"when ","why" ,"who" ,"whose" ,"which", "how far" ,"how often", "how much" ,"how many" ,"how"};
string notImportant[18] = {"my ", "your ", "his ", "its ", "our ", "their ", "mine ", "yours ", "hers ", "ours ", "theirs ",  "the", "this ", "these ", "those ", ".", "?", " "};
string notImpBlank[7] =  {" me ", " him ", " her ", " us ", " them ", " a ", " an "};

char lowerCase(char c){
    if(c>=65 && c<=92){
        c += 32;
    }
    return c;
}

void badCharHeuristic( string str, int size, int badchar[NO_OF_CHARS]){
    for (int i = 0; i < NO_OF_CHARS; i++){
        badchar[i] = -1;
    }
    for (int i = 0; i < size; i++){
        badchar[(int) str[i]] = i;
    }
}

int search( string pat, string txt, int save=1){
    countResult = 0;
    int m = pat.size();
    int n = txt.size();
 
    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);
 
    int s = 0;
    while(s <= (n - m)){
        int j = m - 1;
        while(j >= 0 && lowerCase(pat[j]) == lowerCase(txt[s + j]))
            j--;
        if (j < 0){
            if(save){
                resultIndex[countResult] = s;
                countResult++;
            }
            s += (s + m < n)? m-badchar[txt[s + m]] : 1;
        }else{
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
    if(countResult>0){
        return resultIndex[0];
    }else{
        return -1; //Not Found
    }
}

string replaceX(string value, string text, string newval="", string ek=""){
    string eks[3] = {"es", "s", ","};
    for(auto ek:eks){
        string valueEk = value.substr(0,value.length()-1)+ek;
        int indexEk = search(valueEk,text);
        if(indexEk!=-1 && value.length()>2){
            text.replace(indexEk,value.length()+ek.length(),newval);
        }
    }

    int index = search(value,text);
    if(index!=-1){
        text.replace(index,value.length(),newval);
    }
    return text;
}

string clearNotImportant(string text){
    for(string value:notImportant){
        text = replaceX(value,text);
    }
    return text;
}

string searchAnswer(string questionText, int j, int indexFoundS){
    string answer="";

    if(search(" ",questionText)!=-1){
        int TcountResult = countResult;
        int TresultIndex[1000];
        for(int k=0;k<TcountResult;k++){
            TresultIndex[k] = resultIndex[k];
        }

        //First Word
        string kelime = questionText.substr(0,TresultIndex[0]);
        answer = replaceX(kelime+" ", sentences[j], "", "s");

        //replace Blank
        for(string value:notImpBlank){
            answer = replaceX(value,answer," ");
        }

        //Word Parsing Loop
        for(int k=0;k<TcountResult-1;k++){
            int kLength = TresultIndex[k+1]-TresultIndex[k];
            kelime = questionText.substr(TresultIndex[k]+1,kLength);
            answer = replaceX(kelime, answer, "", "s");
        }

        //Last Word
        kelime = questionText.substr(TresultIndex[TcountResult-1]+1,TresultIndex[TcountResult]-2);
        answer = replaceX(kelime+" ", answer, "", "s");
    }
    return answer;
}
 
int main(){
    clock_t baslangic = clock(), bitis;
    string x;

    ifstream inputFile;
    inputFile.open("the_truman_show_script.txt");
    int counter = 0;
    while (inputFile) {
        inputFile >> x;
        if(search(".",x)!=-1){
            sentences[counter] += x.substr(0,x.length()-1) + " ";
            counter++;
        }else{
            sentences[counter] += x + " ";
        }
    }

    ifstream questionFile;
    int counterQ = 0;
    questionFile.open("questions.txt");
    while (questionFile) {
        questionFile >> x;
        questions[counterQ] += x + " ";
        if(search("?",x)!=-1){
            counterQ++;
        }
    }

    for(int i=0;i<counterQ-1;i++){
        cout << i+1 << ") " << questions[i] << endl;
        string right = "", left = "";
        for(string whq:WHquestions){
            int indexFound = search(whq,questions[i]);
            if(indexFound!=-1){
                if(indexFound!=0){
                    left = questions[i].substr(0,indexFound-1);
                }
                int rStart = indexFound+whq.length();
                int rLength = questions[i].length()-2-rStart;
                right = questions[i].substr(rStart,rLength);
                questions[i] = questions[i].substr(0,questions[i].length()-2);

                string answer = "";
                while(answer==""){
                    for(int j=0;j<counter;j++){
                        if(left!=""){
                            int indexFoundS = search(left,sentences[j]);
                            if(indexFoundS!=-1){
                                answer = searchAnswer(questions[i],j,indexFoundS);
                                break;
                            }
                        }
                        if(right!="" && answer==""){
                            int indexFoundS = search(right,sentences[j]);
                            if(indexFoundS!=-1){
                                answer = searchAnswer(questions[i],j,indexFoundS);
                                break;
                            }
                        }
                    }

                    if(answer==""){
                        if(left!=""){
                            int firstBlank = search(" ",left);
                            left = left.substr(resultIndex[1], left.length()-resultIndex[1]);
                        }
                        if(right!=""){
                            int firstBlank = search(" ",right);
                            right = right.substr(resultIndex[1], right.length()-resultIndex[1]);
                        }
                    }

                    if((left!="" && right!="") && answer ==""){
                        answer = "Not_Found_Answer";
                        break;
                    }
                }

                answer = clearNotImportant(answer);
                cout << answer << endl;

                break;
            }
        }
    }

    bitis = clock();
    cout << endl << "Total Elapsed Time: " << (float)(bitis - baslangic) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}
  