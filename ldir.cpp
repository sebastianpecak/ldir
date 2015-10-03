/*
    Author: Sebastian Pecak
    Date: Oct 3rd, 2015
    
    Example of use: ./ldir /pathName
*/
#include <dirent.h>
#include <stdio.h>
#include <string>

using std::string;

const char *tabularot = "---- ", *down = "|\n";
unsigned int tabNum=0, driNum=0, filesNum=0;

void listDir(const char*);
bool isHidden(const char*);

int main(int argc, char** args) {
  const char* rootPath = *(args+1);
  printf("\n.\n");
  listDir(rootPath);
  
  printf("\nCOUNTED %d FILES AND %d SUB-DIRECTORIES\n", filesNum, driNum);
}

void listDir(const char* path) {
  DIR* dir = opendir(path);
  if(dir) {
    dirent* entry=0;
    tabNum++;
    while((entry=readdir(dir))) {
      
      for (int i=0; i<tabNum-1;i++) printf("     ");
      printf("%s", down);
      
      for (int i=0; i<tabNum-1;i++) printf("     ");
      printf("%s", tabularot);
      // Sprawdz czy ukryty
      if(isHidden(entry->d_name)) printf("H ");
	printf("( %s )\n", entry->d_name);
      
      if(entry->d_type == DT_DIR) {
	
	string name(entry->d_name);
	if(name==".." || name==".") continue;
	driNum++;
	//printf("\n%s ", entry->d_name);
	string temp(path);
	if(temp.at(temp.length()-1) == '/') {
	  temp += entry->d_name;
	  listDir(temp.c_str());
	}
	else {
	  temp+='/';
	  temp+=entry->d_name;
	  listDir(temp.c_str());
	}
      }
      else filesNum++;
      
    }
    closedir(dir);
    tabNum--;
  }
  return;
}

//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

bool isHidden(const char* name)
{
  string file(name);
  if(file[0]=='.') return true;
  else return false;
}
