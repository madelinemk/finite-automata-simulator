// Project 1
// DFA
// Madeline Kusters
// Theory of Computing
// 9/26/2016

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>

typedef struct rule{
  std::string current;
  char input;
  std::string next;
} rule_t;

class DFA {
public:
  DFA(std::string filename);
  void process(std::string x);

private:
  std::string current_state;
  std::set<char> alphabet;
  std::set<std::string> states;
  std::string start_state;
  std::set<std::string> accept_states;
  std::vector<rule_t> transitions;
};

int main(int argc, char* argv[]) {

  // get machine description input file
  // construct DFA object based on the file
  std::string machine_spec;
  if ( argc < 3 ) {
    std::cout << "Enter the name of the file defining the FA to be simulated: ";
    std::cin >> machine_spec;
  } else {
    machine_spec = argv[1];
  }
  DFA dfa(machine_spec);

  // get file containing test strings
  std::string test_strings;
  if (argc < 3){
    std::cout << "Enter the name of the file containing test strings for the FA: ";
    std::cin >> test_strings;;
  } else {
    test_strings = argv[2];
  }
  std::ifstream ifs;
  ifs.open(test_strings);
  if (!ifs.good()) {
    std::cout << "Error - Filename invalid" << std::endl;
  }
  std::cout << test_strings << std::endl;

  // read test strings into a vector
  std::vector<std::string> strings;
  std::string x;
  while(ifs >> x) {
    strings.push_back(x);
  }
  ifs.close();

  //process each string in the dfa
  for (auto i : strings) {
    dfa.process(i);
  }
}


//Definitions of DFA class functions

DFA::DFA(std::string filename){
  std::ifstream ifs;
  ifs.open(filename);
  if (!ifs.good()) {
    std::cout << "Error - Filename invalid" << std::endl;
  } else {
    //s will hold each line of the file
    std::string s;

    //print out first line
    getline(ifs, s);
    std::cout << s << std::endl;

    //alphabet
    getline(ifs, s);
    //check for carriage return
    if (s.back() == '\r') {
      s.pop_back();
    }
    std::istringstream ss1(s);
    while (ss1) {
      std::string a;
      if (!getline(ss1, a, ',')){
        break;
      }
      alphabet.insert(a[0]);
    }

    //states
    getline(ifs, s);
    //check for carriage return
    if (s.back() == '\r') {
      s.pop_back();
    }
    std::istringstream ss2(s);
    while(ss2) {
      std::string state;
      if (!getline(ss2, state, ',')) {
        break;
      }
      states.insert(state);
    }

    //start state
    getline(ifs, s);
    //check for carriage return
    if (s.back() == '\r') {
      s.pop_back();
    }
    std::istringstream ss3(s);
    getline(ss3, start_state, '\r');
    // set current state to start state
    current_state = start_state;

    //accepting states
    getline(ifs, s);
    //check for carriage return
    if (s.back() == '\r') {
      s.pop_back();
    }
    std::istringstream ss4(s);
    while (ss4) {
      std::string state;
      if (!getline(ss4, state, ',')) {
        break;
      }
      accept_states.insert(state);
    }

    //transitions
    while (ifs) {
      if (!getline(ifs, s)) {
        break;
      } else {
        //check for carriage return
        if (s.back() == '\r') {
          s.pop_back();
        }
        std::istringstream ss5(s);
        std::string curr, in, next;
        getline(ss5, curr, ',');
        getline(ss5, in, ',');
        getline(ss5, next);
        rule_t r = {curr, in[0], next};
        transitions.push_back(r);
      }
    }
    //print rules
    for ( int i=0; i < (int)transitions.size(); i++) {
      std::cout << i << ": " << transitions[i].current << "," << transitions[i].input << "," << transitions[i].next << std::endl;
    }
    std::cout << std::endl;
  }
  ifs.close();
}



void DFA::process(std::string x) {
  //reset machine to start state
  current_state = start_state;
  //print string
  std::cout << "String: " << x << std::endl;

  for (int i = 0; i < (int)x.size(); i++) {
    //look for a matching rule
    int rule;
    bool matched = false;
    for (int j = 0; j < (int)transitions.size(); j++) {
      if (current_state == transitions[j].current) {
        if (x[i] == transitions[j].input) {
          rule = j;
          matched = true;
          break;
        }
      }
    }
    if (!matched) {
      std::cout << "Rejected" << std::endl << std::endl;
      return;
    }

    // apply rule and print out each step in the format:
    // <Step#>#<Rule_Number>: <Initial_State_Name>,<Input_Symbol>,<New_State_Name>
    std::cout << i << "#" << rule << ": " << current_state << "," << x[i] << ",";
    current_state = transitions[rule].next;
    std::cout << current_state << std::endl;
  }


  // print "Accepted" or "Rejected"
  if ( accept_states.find(current_state) != accept_states.end()) {
    std::cout << "Accepted" << std::endl << std::endl;
  } else {
    std::cout << "Rejected" << std::endl << std::endl;
  }
}





