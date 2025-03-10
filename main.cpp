#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

enum MenuOptions {
  RUNALLEXPRESSIONS = 1,
  EXITPROGRAM = 2
};

const string IN_FILE_NAME = "C:\\Users\\hansh\\Desktop\\School Code\\CS 136\\Lab3_136_Stack\\input.txt";
const int MAX_SIZE = 60;

class Stack {
  private:
    int top;

  public:
    string storage[MAX_SIZE];

    Stack() { 
      top = -1;
    }

    const void push(string input) { 
      if(top > MAX_SIZE){
        cout << "ERROR: Max amount of characters is " << MAX_SIZE << ", please change input to fit.\n";
        system("pause");
        exit(EXIT_FAILURE);

      } else{
        storage[++top] = input; 
      } 
    }

    const string pop() { 
      if(top < 0){
        cout << "ERROR: There are already no more characters in the stack, cannot remove what isn't there.";
        system("pause");
        exit(EXIT_FAILURE);

      } else{
        string x = storage[top--]; 
        return x; 
      }
    }

    const string returnSymbolGroup(int& i){
      string result = "";

      if (isEmpty()) {
        cout << "Stack is empty\n";
      }
      
      if(storage[i] == "(" || storage[i] == ")" || 
        storage[i] == "{" || storage[i] == "}" || 
        storage[i] == "[" || storage[i] == "]" || 
        storage[i] == "\"" || storage[i] == "\'" ) {
        result += storage[i];

      } else if(storage[i] == "<" && storage[i+1] == "!" && storage[i+2] == "-" && storage[i+3] == "-"){
        result += string() + storage[i] + storage[i+1] + storage[i+2] + storage[i+3];

      } else if((storage[i] == "-" && storage[i+1] == "-" && storage[i+2] == ">")){
        result += string() + storage[i] + storage[i+1] + storage[i+2];

      } else if((storage[i] == "/" && storage[i+1] == "*") ||
                (storage[i] == "*" && storage[i+1] == "/")){
        result += string() + storage[i] + storage[i+1];

      }
      
      return result;
    }

    const string getSymbolsOnly(){
      string result = "";

      for (int i = 0; i < top; i++){
        result += returnSymbolGroup(i);
      }

      return result;
    }

    const Stack getSymbolsOnlyStack(){
      Stack symbolOnlyStack;

      for (int i = 0; i < top; i++){
        if(returnSymbolGroup(i) != ""){
          symbolOnlyStack.push(returnSymbolGroup(i));
        }
      }

      return symbolOnlyStack;
    }
  
    const bool isBalanced() {
      Stack target;
      Stack compare[MAX_SIZE];
      string opening[7] = {"(", "{", "[", "<!--", "/*", "\"", "\'"};
      string closing[7] = {")", "}", "]", "-->", "*/", "\"", "\'"};
      string lastOpeningSymbol = "";
      bool isThereComma = false, isThereQuotes = false;
      int length = 0;
      bool existingDoubleQuotes = false;
      bool existingSingleQuote = false;

      for (int i = 0; i < top; i++){
        string insert = returnSymbolGroup(i);

        auto openingIndexOfInsert = find(begin(opening), end(opening), insert);
        auto closingIndexOfinsert = find(begin(closing), end(closing), insert);
        
        if (openingIndexOfInsert != end(opening) && insert != "\"" && insert != "\'") {
            target.push(insert);

        } else if(insert == "\"" && !existingDoubleQuotes){
          existingDoubleQuotes = true;
          target.push(insert);

        } else if(insert == "\'" && !existingSingleQuote){
          existingSingleQuote = true;
          target.push(insert);

        } else if(closingIndexOfinsert != end(closing)){
          auto closingIndexOfInsert = distance(closing, find(begin(closing), end(closing), insert));

          if (insert == "\"") existingDoubleQuotes = false; 
          if (insert == "\'") existingSingleQuote = false; 
          
          if(target.peek() != opening[closingIndexOfInsert]){
            return false;
          } else {
            target.pop();
          }
        }
      }

      return true;
    };

    const void printStack() {
      if (isEmpty()) {
          cout << "Stack is empty\n";
      }

      for (int i = 0; i <= top; i++) {
        cout << storage[i];
      }
      cout << endl;
    }

    const int getTop() { return top; }

    const string peek() {  
      string x = storage[top]; 
      return x;  
    }

    const bool isEmpty() { return (top < 0); }

};

void checkFiles();
void invalidSwitchInput();
void printMenuChoices();
int validateSwitchInput(string input);
void exitProgram();
void fillStack(Stack& obj);
void switchStatement(Stack& obj);
void outputOriginal(Stack& obj);
void outputSymbolsOnly(Stack &obj);
void runAllExpressions(Stack& obj);
void isExpressionBalanced(Stack& obj);

int main(){
  class Stack dataStack;
  
  checkFiles();

  fillStack(dataStack);

  switchStatement(dataStack);
}

void switchStatement(Stack& obj){
  int userInput;

  do{
    string stringUserInput;
    
    printMenuChoices();

    getline(cin, stringUserInput);
    userInput = validateSwitchInput(stringUserInput);

    cout << "\n";

    switch(userInput){
      case (RUNALLEXPRESSIONS):
        runAllExpressions(obj);
        break;

      case (EXITPROGRAM):
        exitProgram();
        break;

      default:
        invalidSwitchInput();
        break;
    }
  } while (userInput != 3);
}

void checkFiles(){
  ifstream inFile; 
  ofstream outFile;

  inFile.open(IN_FILE_NAME); 

  if(!inFile){
    cout << "Failed reading input file. Terminating program\n";

    system("pause");
    exit(EXIT_FAILURE);
  }
  inFile.close();
}

int validateSwitchInput(string input){
  if(input.length() != 1){
    // returns 3 in order to result in default in switch statement
    return 3; 
  } else{
    return stoi(input);
  }
}

void invalidSwitchInput(){
  cout << "- Invalid input, please try again. - \n";
 
  printMenuChoices();
}

void printMenuChoices(){
  cout << setfill('-') << setw(100) << " " << "\n Here are your choices (input the number for the corresponding action): \n 1. Process all expressions at once (original, determine if well-formed, and output expression with closing & opening symbols) \n 2. Quit program"
       << endl;
}

void runAllExpressions(Stack& obj){
  outputOriginal(obj);
  isExpressionBalanced(obj);
  outputSymbolsOnly(obj);
}

void exitProgram(){
  cout << "Exiting Program";
}

void outputOriginal(Stack& obj){
  cout << "- ";
  obj.printStack();
}

void isExpressionBalanced(Stack& obj){
  if(obj.isBalanced()){
    cout << "- The given expression is balanced\n";
  } else {
    cout << "- The given expression is not balanced\n";
  }
}

void outputSymbolsOnly(Stack& obj){
  cout << "- Symbols Only: " << obj.getSymbolsOnly() << "\n"; 
}

void fillStack(Stack& obj){
  char c_fromFile;
  int charsProcessed = 0;

  ifstream inFile;
  inFile.open(IN_FILE_NAME);

  while(inFile.get(c_fromFile)){
    obj.push(string(1, c_fromFile));
    charsProcessed++;
  }
}