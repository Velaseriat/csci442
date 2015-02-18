#include "builtins.h"

using namespace std;

map<string, string> alias_map;

bool has_flag(vector<string>& tokens, string flag){
    return (find(tokens.begin(), tokens.end(), flag) != tokens.end());
}

int com_ls(vector<string>& tokens) {
  // if no directory is given, use the local directory
  if (tokens.size() < 2) {
    tokens.push_back(".");
  }

  // open the directory
  DIR* dir = opendir(tokens[1].c_str());

  // catch an errors opening the directory
  if (!dir) {
    // print the error from the last system call with the given prefix
    perror("ls error: ");

    // return error
    return 1;
  }

  // output each entry in the directory
  for (dirent* current = readdir(dir); current; current = readdir(dir)) {
    cout << current->d_name << endl;
  }

  // return success
  return 0;
}


int com_cd(vector<string>& tokens) {
    // TODO: YOUR CODE GOES HERE
    if (tokens.size() < 2){
        perror("Please specify a directory to which to change\n");
        return -1;
    }                                     
    if (access((tokens[1]).c_str(), F_OK) == -1) {
        fprintf(stderr, "cd error: %s does not exist\n", tokens[1].c_str());
        return -1;
    }
    return chdir(("./" + tokens[1]).c_str());    
}

                  
int com_pwd(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  // HINT: you should implement the actual fetching of the current directory in
  // pwd(), since this information is also used for your prompt
    cout << pwd();
    return 0;
}


int com_alias(vector<string>& tokens) {
    // TODO: YOUR CODE GOES HERE
    if (tokens.size() == 1) {
        for (map<string, string>::iterator it = alias_map.begin(); it != alias_map.end(); ++it){
            printf("%s <-> %s\n", (it->second).c_str(), (it->first).c_str());
        }                
    }                          
    else {
        for (int i = 1; i < tokens.size()-1; i=i+2){
            alias_map[tokens[i]] = tokens[i+1];
        }                   
    }
    return 0;
}

int com_unalias(vector<string>& tokens) {
    // TODO: YOUR CODE GOES HERE
    if (has_flag(tokens, "-a")){
        alias_map.clear();
    }
    else{
        if (tokens.size() < 2){
            perror("Please specify an alias or use -a to delete all");
        }
        else {
            alias_map.erase(tokens[1]);
        }
    }
  return 0;
}


int com_echo(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
    string s = "";
    for (int i = 1; i < tokens.size(); i++){
        s.append(tokens[i] + " ");
    }
    cout << s <<  endl;
  return 0;
}


int com_exit(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  exit(0);
  return 0;
}


int com_history(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  
  //HIST_ENTRY** the_list;
  //the_list = history_list();
  
  //int index = 1;
  
  //while (the_list[index] != NULL && index < 20){
  //    cout << index << ". " << the_list[index]->line << endl;
  //  index = index + 1;
 // }

  cout << "history called" << endl; // delete when implemented
  return 0;
}

string pwd() {
  // TODO: YOUR CODE GOES HERE
  return getcwd(NULL, 0);
}
