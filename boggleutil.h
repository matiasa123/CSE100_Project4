// Matias Altman <mhaltman@ieng6.ucsd.edu>, Jonathan Agustin <jagustin@ucsd.edu>
#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
#include <vector>
#include <string>
//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.

int genHash(char child);

class RadNode
{
   private:
      int radix;
      char key;
      std::vector<RadNode*> children;
      bool endFlag;

   public:
      RadNode(int size, char data, bool end);
      RadNode(int size, char data);
      ~RadNode();
      int getRadix();
      char getKey();
      void setChild(int child, RadNode*& data);
      RadNode* getChild(int child);
      std::vector<RadNode*> getChildren();
      bool getEnd();
      void setEnd(bool end);
};

void destroyNode(RadNode*& node);

class LexTree
{
   private:
   public:
      RadNode* root;
      LexTree();
      ~LexTree();
      void addWord(std::string word);
      void addChild(int child_p, char child, RadNode*& parent);
      void addChildwEnd(int child_p, char child, RadNode*& parent, bool End);
      bool Search(std::string word);
      std::vector<RadNode*> BFS();
      RadNode* getRoot();
};

class Board
{
   private:
      std::string** board;
      int col;
      int row; 
   public:
      Board();
      Board(std::string** First, int row, int col);
      ~Board();
      bool tooHigh(int _row, int _col){ return (_row >= row); }
      bool tooLow(int _row, int _col){ return (_row < 0); }
      bool tooLeft(int _row, int _col){ return (_col < 0); }
      bool tooRight(int _row, int _col){ return (_col >= col); }
      std::string** getBoard(){return board;}
      std::vector<int>  getNeighbors(int pos, std::vector<bool> visited);
      std::vector<int> Check(std::string word, std::string path, int pos, std::vector<bool> visited, std::vector<int> pathway);
      std::vector<int> contains(std::string word);
      bool matches(std::string word, std::string path);
};


#endif
