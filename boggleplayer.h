// Matias Altman <mhaltman@ieng6.ucsd.edu>, Jonathan Agustin <jagustin@ucsd.edu>
#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"
#include <string>
using namespace std;

class BogglePlayer : public BaseBogglePlayer {
  public:
  void buildLexicon(const set<string>& word_list);
  
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

  void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
 

  BogglePlayer() 
  {
  };
  
  ~BogglePlayer() {
  };
    LexTree tree;

  private:
     set<std::string> word_list_internal;
     bool flagBuildLexicon;
     bool flagSetBoard;
};

#endif
