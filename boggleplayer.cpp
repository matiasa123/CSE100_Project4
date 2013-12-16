// Matias Altman <mhaltman@ieng6.ucsd.edu>, Jonathan Agustin <jagustin@ucsd.edu>
#include "boggleplayer.h"
#include "boggleutil.h"
#include <string>
#include <algorithm>

Board* boarded;

//build Tree
void BogglePlayer::buildLexicon(const set<string>& word_list)
{
   word_list_internal = word_list;
   for (std::set<std::string>::iterator it=word_list.begin(); it!=word_list.end(); ++it)
   {
      tree.addWord(*it);
   }

  this->flagBuildLexicon = true;
}

//Set Boggle Object UP
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) 
{
  this->flagSetBoard = true;
  boarded = new Board(diceArray, rows, cols); 
}

//Check boggle board representative for word
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) 
{
   if(this->flagSetBoard == false || this->flagBuildLexicon == false)
      return false;
   else
   {
      for (std::set<std::string>::iterator it=word_list_internal.begin(); it!=word_list_internal.end(); ++it)
      {
         if((*it).size() > minimum_word_length)
         {
            std::vector<int> coords = boarded->contains(*it);
            if(!coords.empty())
            {
               words->insert(*it);
            }
         }
      }
      return true;
   }
}

//Search Lexicon Tree
bool BogglePlayer::isInLexicon(const string& word_to_check) 
{
   return tree.Search(word_to_check);
}

//Check word is on the board
vector<int> BogglePlayer::isOnBoard(const string& word) 
{
   return boarded->contains(word);
}

//reset board
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) 
{
   if(this->flagSetBoard)
   {
      delete boarded;
   }
   boarded = new Board(new_board, *rows, *cols);
}

