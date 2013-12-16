// Matias Altman <mhaltman@ieng6.ucsd.edu>, Jonathan Agustin <jagustin@ucsd.edu>
#include"boggleutil.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <assert.h>

//In this file, implement all of the operations your data structures support (you have declared these operations in boggleutil.h).
RadNode::RadNode(int size, char data)
{
   radix = size;
   key = data;
   children.resize(radix);
   endFlag = false;
}

//Constructor
RadNode::RadNode(int size, char data, bool end)
{
   radix = size;
   key = data;
   children.resize(radix);
   endFlag = end;
}

//Destructor
RadNode::~RadNode()
{
}

//Access Private Variable Radix
int RadNode::getRadix()
{
  return radix;
}

//Set Private Variable Child Vector 
void RadNode::setChild(int child, RadNode*& data)
{
   if(child < radix)
   {
      children[child] = data; 
   }
}

//Access Private Variable Key 
char RadNode::getKey()
{
   return key;
}

//Access Private Variable Key 
RadNode* RadNode::getChild(int child)
{
   if(child >= radix)
   {
      return nullptr; 
   }
   else
   {
      return children[child];
   }
}

//Access private Children Node 
std::vector<RadNode*> RadNode::getChildren()
{
   return children;
}

//Access End Flag
bool RadNode::getEnd()
{
   return endFlag;
}

//Set End Flag
void RadNode::setEnd(bool end)
{
   endFlag = end;
}

//Empty Tree Constructor
LexTree::LexTree()
{
   root = nullptr;
}

//Tree Destructor
LexTree::~LexTree()
{
  destroyNode(this->root); 
}

//Destructor Helper Function
void destroyNode(RadNode*& node)
{
   if(node != nullptr)
   {
      int size = node->getRadix();
      std::vector<RadNode*> children = node->getChildren();   

      for(int i = 0; i < size; i++)
      { 
        if(children[i] != nullptr)
        {
           destroyNode(children[i]);
        }
      } 
      delete node;
   }
}

//Add Children to Node
void LexTree::addChild(int child_p, char child, RadNode*& parent)
{
   RadNode* node = new RadNode(3, child);
   parent->setChild(child_p, node);
   if(parent->getChild(child_p) == nullptr)
   {
      std::cout << "Child is null" << std::endl;
   }

}

//Get Root of the Tree
RadNode* LexTree::getRoot()
{
   return root;
}

//Add Child to Node with end Flag
void LexTree::addChildwEnd(int child_p, char child, RadNode*& parent, bool End)
{

   RadNode* node = new RadNode(3, child, true);
   parent->setChild(child_p, node);
}

//Add word to our lexicon tree
void LexTree::addWord(std::string word)
{
   if((root == nullptr) && (word.size() != 0))
   {
      word[0] = std::tolower(word[0]);
      root = new RadNode(3, word[0]);
   }
   else if(word.size() == 0)
   {
      return;
   }

   RadNode* curr = root;

   for(int i = 0; i < (word.size() - 1); i++)
   {
      word[i] = std::tolower(word[i]);

      //q:this doesn't make sense, what happens when i>1

      while(curr->getKey() != word[i])
      {

         if(curr->getKey() < word[i])
         { 
            if(curr->getChild(2) != nullptr)
            {
               curr = curr->getChild(2);
            }
            else
            { 
               addChild(2, word[i], curr);
               curr = curr->getChild(2);
            }
         }
         else if(curr->getKey() > word[i])
         {
            if(curr->getChild(0) != nullptr)
            {
               curr = curr->getChild(0);
            }
            else
            { 
               addChild(0, word[i], curr);
               curr = curr->getChild(0);
            }
         }
      }

      if(i == word.size()-2)
      {
         break;
      }

      //Goto Next next level 
      //If there is no level
      if(curr->getChild(1) == nullptr)
      {
         addChild(1, std::tolower(word[i+1]), curr);
         curr = curr->getChild(1);
      }
      //otherwise traverse
      else
      {
         curr = curr->getChild(1); 
      }
   }

   if(curr->getChild(1) == nullptr)
   {
      addChildwEnd(1, std::tolower(word[word.size()-1]), curr, true); 
      curr = curr->getChild(1);
   }
   else
   {
      curr = curr->getChild(1);
      curr->setEnd(true);
   }
}

//Breadth First Search For Tree Debugging
std::vector<RadNode*> LexTree::BFS()
{
   std::vector<RadNode*> output_queue;
   std::vector<RadNode*> queue;
   queue.push_back(root);

   while(queue.size() > 0)
   {
      RadNode* front = queue.front();
      queue.erase(queue.begin());

      output_queue.push_back(front);

      std::vector<RadNode*> children = front->getChildren();
      for(int i = 0; i < front->getRadix(); i++)
      {
         if(children[i] != nullptr)
            queue.push_back(children[i]);   
      }

   } 
 
   return output_queue;
}

//Search For Word In tree
bool LexTree::Search(std::string word)
{
   RadNode* curr = root;

   if(word.size() == 1)
   {
      while(curr != nullptr)
      {
         if(curr->getKey() > word[0])
         { 
             curr = curr->getChild(1); 
         }
         else if(curr->getKey() < word[0])
         {
            curr = curr->getChild(2);
         }
         else if(curr->getKey() == word[0])
         {
           return true;
         }
      }
      return false;
   }   

   for(int i = 0; i < word.size() - 1; i++)
   {
      word[i] = std::tolower(word[i]);

      while(curr->getKey() != word[i])
      {
         if(curr->getKey() > word[i])
         { 
            if(curr->getChild(0) != nullptr)
            {
               curr = curr->getChild(0);
            }
            else
            {
               return false; 
            }
         }
         else if(curr->getKey() < word[i])
         {
            if(curr->getChild(2) != nullptr)
            {
               curr = curr->getChild(2);
            }
            else
            {
               return false; 
            }
         }

       }

      if(curr->getChild(1) == nullptr)
      {
         return false;
      } 
      else
      {
         curr = curr->getChild(1);
      }
   }

   if(curr->getEnd() == true)
   {
      return true;
   }
   else
   {
      return false;
   }
   
}

//Empty Board Representative Constructor
Board::Board()
{
   board = nullptr;
   col = 0;
   row = 0;
   
}

//Board Representative Constructor
Board::Board(std::string** board, int row, int col)
{
   this->board = board;
   this->col = col;
   this->row = row;

}

//Board Destructor
Board::~Board()
{
   for(int i = 0; i < row; i++)
   {
      delete [] board[i];
   }
}

//Get Neighbors of position in board that have not been visited and don't overflow
std::vector<int> Board::getNeighbors(int pos, std::vector<bool> visited)
{
   std::vector<int> neigh;  

    int _row = pos/col;
    int _col = pos%col; 

   if(!tooHigh(_row + 1, _col) && !visited[pos + col]) 
   {
      neigh.push_back((((_row + 1) * col) + _col));
   }
   if(!tooHigh(_row + 1, _col + 1) && !tooRight(_row + 1, _col + 1) && !visited[pos + col + 1]) 
   {
      neigh.push_back((((_row + 1) * col) + (_col + 1)));
   }
   if(!tooHigh(_row + 1, _col - 1) && !tooLeft(_row + 1, _col - 1) && !visited[pos + col - 1]) 
   {
      neigh.push_back((((_row + 1) * col) + (_col - 1)));
   }
   if(!tooRight(_row, _col + 1) && !visited[pos + 1]) 
   {
      neigh.push_back(((_row * col) + (_col + 1)));
   }
   if(!tooLeft(_row, _col - 1) && !visited[pos - 1]) 
   {
      neigh.push_back(((_row * col) + (_col - 1)));
   }
   if(!tooLow(_row - 1, _col) && !visited[pos - col]) 
   {
      neigh.push_back((((_row - 1) * col) + _col));
   }
   if(!tooLow(_row - 1, _col + 1) && !tooRight(_row - 1, _col + 1) && !visited[pos - col + 1]) 
   {
      neigh.push_back((((_row - 1) * col) + (_col + 1)));
   }
   if(!tooLow(_row - 1, _col - 1) && !tooLeft(_row - 1, _col - 1) && !visited[pos - col - 1]) 
   {
      neigh.push_back((((_row - 1) * col) + (_col - 1)));
   }

   return neigh; 
}

//Check if word is on Boggle Board Object
std::vector<int> Board::contains(std::string word)
{
   std::vector<int> queue;   
   std::vector<int> output_queue;
   std::vector<bool> visited((row*col), 0);


   for(int i = 0; i < row; i++)
   {
      for(int j = 0; j < col; j++)
      {
         if(word.size() == 1)
            break;
         if(!board[i][j].compare(word.substr(0, board[i][j].size()))) 
         {
            queue.push_back((i*col) + row);
            visited[queue.back()] = 1;
            output_queue = Check(word, board[i][j], queue.back(), visited, queue);
   
            if(!output_queue.empty())
            {
               break;
            }
            else
            {
               queue.pop_back();
               visited.pop_back();
            }
         }     
      }
   }

   if(word.size() == 1)
   {
      word[0] = std::tolower(word[0]);
      for(int i = 0; i < row; i++)
      {
         for(int j = 0; j < col; j++)
         {
            board[i][j] = std::tolower(board[i][j][0]);
            if(!board[i][j].compare(word.substr(0, 1))) 
            {
               output_queue.push_back((i*row)+ j);
               break;
            }
         }
      }
    }
   
   return output_queue;  
}

//Check All sorounding spots to see if they continue to form the path of word
std::vector<int> Board::Check(std::string word, std::string path, int pos, std::vector<bool> visited, std::vector<int> pathway)
{
  if(!word.compare(path))
  {
     return pathway;
  } 
  else
  {
     std::vector<int> children = getNeighbors(pos, visited);
    
     
     for(int i = 0; i < children.size(); i++)
     {
        std::string met = path;
        met += board[children[i]/col][children[i]%col];

        if(matches(word, met))
        {
            std::vector<bool> recur_visited = visited;
            std::vector<int> temp_path = pathway;
            recur_visited[children[i]] = 1;
            temp_path.push_back(children[i]);
            std::vector<int> passage = Check(word, met, children[i], recur_visited, temp_path);
            if(!passage.empty())
            {
               return passage;
            } 
        }
     }
     

     std::vector<int> empty;
     return empty;

  }
}

//Compare the word we are searching for and its forming path in boggle object
bool Board::matches(std::string word, std::string path)
{
   return !path.compare(word.substr(0,path.size()));
}

