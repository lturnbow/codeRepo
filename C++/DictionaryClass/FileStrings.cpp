/******************************************************************************/
/*!
\file   FileStrings.cpp
\author Lauren Turnbow
\brief  
  This is the implementation file for all member functions
  of the StringUtils, DictionaryInfo, and SpellChecker class. 
  Functions:
    - UpperCase
    - WordWrap
    - Tokenize
    - SpellChecker
    - GetInfo
    - SpellCheck
    - WordLengths
    - WordsStartingWith
    - AcronymToWord
    
    Hours spend on this assignment: 7

*/
/******************************************************************************/
#include <fstream>        // ifstream
#include "FileStrings.h"  // SpellChecker, StringUtils, DictionaryInfo

namespace CS170
{
//////////////////String Class/////////////////////////////////////
/******************************************************************************/
/*!
  \brief
    Returns the uppercase string

  \param string
    String to be uppercased 
    
  \return
    Returns the uppercased string

*/
/******************************************************************************/
  std::string& StringUtils::UpperCase(std::string& string)
  {
    std::string::iterator it;                  // String iterator
    // Go from beginning to end
    for (it = string.begin(); it != string.end(); ++it)
      if (*it >= 'a' && *it <= 'z')            // If lowercase
        *it = static_cast<char>(*it - SPACE);  // Make uppercase

    return string;
  }
  
/******************************************************************************/
/*!
  \brief
     Breaks a given string into lines less than or equal to the line length

  \param words
    Words that will be wrapped
    
  \param line_length
    Line length that will be used to fit lines
    
  \return
    Returns the string broken up into line lengths

*/
/******************************************************************************/
  std::vector<std::string> StringUtils::WordWrap(const std::string& words, 
                                                       size_t line_length)
  {
    // New vector of strings that will be returned
    std::vector<std::string> wordsArray;      
    
    // Taking in first word to compare to line length
    std::string firstWord;                 
    // Taking in second word to compare to line length
    std::string secondWord;          
    unsigned long i = 0;                // Loop counter
    
    // While end of string ahs not been reached
    while (words[i] != 0)
    {
      firstWord.push_back(words[i]);    // Put first word into variable 
      
      if (words[i] == SPACE)            // If end of first word is reached
      {
        // Add first word to second word to acquire next word
        secondWord.append(firstWord);   
        // Clear the first word to acquire next word
        firstWord.clear();
      }
      
      // If both words exceed the line length and there is a second word
      if (firstWord.size() + secondWord.size() > line_length && 
                                         secondWord.size() > 0)
      {
        // Resize the word to be one less
        secondWord.resize(secondWord.size() - 1);
        // Put word into vector array that will be returned 
        wordsArray.push_back(secondWord);
        // Clear the second word
        secondWord.clear();
      }
      i++;                             // Increment loop counter
    }
    
    // If the size of both words is greater than 0
    if (firstWord.size() + secondWord.size() > 0)
    {
      secondWord.append(firstWord);    // Put first and second words together
      // Add both words to vector that will be returned
      wordsArray.push_back(secondWord); 
    }
    
    return wordsArray;                 // Return vector of wrapped words
  }

/******************************************************************************/
/*!
  \brief
     Splits a string into words (no spaces)

  \param words
    String that is to be split into words
    
  \return
    Vector of strings that holds the words

*/
/******************************************************************************/
  std::vector<std::string> StringUtils::Tokenize(const std::string& words)
  {
    // New vector of strings that will be returned 
    std::vector<std::string> wordsArray;
    // String that will hold letters and words before adding to vector
    std::string buffer; 
    unsigned long i = 0;                // Loop counter
    
    while (words[i] != 0)               // While end of string is not reached
    {
      // If the element isn't a space, newline, or second to end of string
      if (words[i] != SPACE && words[i] != '\n' && words[i + 1] != 0)
        buffer.push_back(words[i]);     // Add element to buffer
      
      else
      {
        // If the element isn't a space and is the last element in string
        if (words[i] != SPACE && words[i + 1] == 0)
          buffer.push_back(words[i]);   // Add element to buffer
        
        if (buffer.size() > 0)
          wordsArray.push_back(buffer); // Add buffer to vector
        
        buffer.clear();                 // Clear the buffer
      }
      i++;                              // Increment loop counter
    }
    
    return wordsArray;                  // Return the buffer
  }
  
/////////////////////////SpellChecker Class/////////////////////////
/******************************************************************************/
/*!
  \brief
    Constructor

  \param dictionary
    File name that is supplied

*/
/******************************************************************************/
  SpellChecker::SpellChecker(const std::string &dictionary)
  {
    dictionary_ = dictionary;      // Construct dictionary using file name
  }

/******************************************************************************/
/*!
  \brief
     Returns information about the dictionary

  \param info
    Reference parameter to the dictionary
    
  \return
    Returns if the file was opened successfully or not

*/
/******************************************************************************/
  SpellChecker::SCResult SpellChecker::GetInfo(DictionaryInfo &info) const
  {
    std::ifstream infile;              // Declare ifstream object
    infile.open(dictionary_.c_str());  // Open the object
    
    if (!infile.is_open())             // If file can't be opened, return error
      return scrFILE_ERR_OPEN;  
    
    else
    {     
      // Longest word is set to 0 so it can be found
      unsigned long wordLongest = 0;    
      // Shortest word is set to a large number so it can be found
      const int LARGE_NUMBER = 20000;   
      unsigned long wordShortest = LARGE_NUMBER;              
      unsigned long wordCount = 0;     // Count of words initialized to zero    
      
      std::string word;                // String that will be input from file
     
      while (!infile.eof())
      {
        infile >> word;
        // Length of inputted word
        unsigned long length = word.length();
        
        if (infile.eof())              // If end of file has been reached
          break;
          
        // If length is shorter than current shortest word reset shortest
        if (length < wordShortest)
          wordShortest = length;
        // If the length is longer than current longest word reset longest  
        if (length > wordLongest)
          wordLongest = length;
        
        wordCount++;                  // Increment word count
        }
      
      // Initializes shortest, longest, and count variables in DictionaryInfo 
      // Class
      info.shortest = wordShortest;        
      info.longest = wordLongest;
      info.count = wordCount;
      
      // File was successfully opened, return ok 
      return scrFILE_OK;
     }
  }

/******************************************************************************/
/*!
  \brief
    Looks up words in the dictionary

  \param word
    Word that is being searched for in the dictionary
    
  \return
    Returns if the word is found or not. If not found, it is misspelled

*/
/******************************************************************************/
  SpellChecker::SCResult SpellChecker::SpellCheck(const std::string& word) const
  {
    std::ifstream infile;              // Declare ifstream object
    infile.open(dictionary_.c_str());  // Open the object
    
    if (!infile.is_open())             // If file can't be opened, return error
      return scrFILE_ERR_OPEN;  
    
    else
    {
      std::string retrievedWord;       // Word inputted from file
      std::string temp;                // Temporary string
      
      while (!infile.eof())
      {
        infile >> retrievedWord;       // Input word from file
        unsigned long i = 0;           // Loop counter
          
        temp = word;                            // Copy word into temp 
        StringUtils::UpperCase(retrievedWord);  // Uppercase word in temp
        StringUtils::UpperCase(temp);           // Uppercase buffer
                 
        // If entire word is equal to the entire word in temp
        while (retrievedWord[i] == temp[i])
        { 
          // If end of file has been reached      
          if (retrievedWord[i] == 0 && temp[i] == 0)
          {
            infile.close();
            // Word has been found, is spelled correctly
            return scrWORD_OK;
          }
            
          // If word is not equal to word in temp
          if (retrievedWord[i] != temp[i])
            break;
       
          i++;                                  // Increment counter
        }
      }
      
      infile.close();
      // Return word bad if word is not found, is not spelled correctly 
      return scrWORD_BAD;
    }
    
    // Return error message if file cannot be opened
    return scrFILE_ERR_OPEN;
  }

/******************************************************************************/
/*!
  \brief
    Counts the number of words that have length 1

  \param lengths
    Words that have length 1
    
  \param count
    Number of words that have length 1
    
  \return
    Returns if the file was opened successfully or not

*/
/******************************************************************************/
  SpellChecker::SCResult SpellChecker::WordLengths(std::vector<size_t>& lengths
                                                          , size_t count) const
  {
    std::ifstream infile;              // Declare ifstream object
    infile.open(dictionary_.c_str());  // Open the object
    
    if (!infile.is_open())             // If file can't be opened, return error
      return scrFILE_ERR_OPEN;  

    else
    {
      long unsigned string_length = 0;         // Length of string
      
      while (!infile.eof())
      {
        std::string word;                      // String that will hold input
        infile >> word;
        
        string_length = word.length();         // Length of each word

        // If length of word is less than count 
        if (string_length > 0 && string_length <= count)
        // Increment array at that index, length of string
        lengths[string_length]++;
      }
     
      infile.close();
      return scrFILE_OK;                       // Return successful     
    }
  }

/******************************************************************************/
/*!
  \brief
    Counts the number of words that start with letter

  \param letter
    Words starting with this letter are being searched for
    
  \param count
    Count of words starting with the letter
  
  \return 
    Returns if the file was opened successfully or not. Returns ok if it was
    successful

*/
/******************************************************************************/
  SpellChecker::SCResult SpellChecker::WordsStartingWith(char letter, 
                                                   int& count) const
  {
    std::ifstream infile;              // Declare ifstream object
    infile.open(dictionary_.c_str());  // Open the object
    
    if (!infile.is_open())             // If file can't be opened, return error
      return scrFILE_ERR_OPEN;
      
    else
    {
      count = 0;                       // Count of words starting with letter
      std::string word;                // Word that will be input
      std::string givenLetter;         // Given letter as a string
      
      givenLetter.push_back(letter);   // String contains given char
       
      while (!infile.eof())
      {
        infile >> word;                        // Input word from file
        StringUtils::UpperCase(givenLetter);   // Uppercase letter
        StringUtils::UpperCase(word);          // Uppercase word
        
        // If word starts with given letter 
        if (word[0] == givenLetter[0])          
          count++;                             // Increment count
        
        // If word has not been found after passing letter, break out 
        if (count > 0 && word[0] != givenLetter[0])  
          break;
      }
      
      infile.close();
      return scrFILE_OK;                      // Return successful
    }
  }

/******************************************************************************/
/*!
  \brief
     Finds word in the dictionary that has letters of the acronym in order

  \param acronym
    Acronym to be searched for
    
  \param words
    Words that contain acronym will be stored in vector
  
  \param maxlen
    Maxlength of words being searched for
  
  \return
    Returns if the file successful and could be opened

*/
/******************************************************************************/
  SpellChecker::SCResult SpellChecker::AcronymToWord(const std::string& acronym,
          std::vector<std::string>& words, size_t maxlen) const
  {
    std::ifstream infile;              // Declare ifstream object
    infile.open(dictionary_.c_str());  // Open the object
    
    if (!infile.is_open())             // If file can't be opened, return error
      return scrFILE_ERR_OPEN;
    
    else
    {
      std::string new_acronym = acronym;    // String for acronym, non const
      StringUtils::UpperCase(new_acronym);  // Uppercase acronym
      
      while (!infile.eof())
      {
        std::string word;                   // String for input word
        infile >> word;                     // Input word from file
               
        std::string newWord;                // Another string for word 
        newWord = word;                     // New word is equal to word
        // So that word can be uppercased without affecting original
        StringUtils::UpperCase(newWord);    
        
        // If size is bigger than the max length or if the word doesn't start 
        // with the same letter than the acronym does
        if ((newWord.size() > maxlen && maxlen != 0) || 
                          newWord[0] != new_acronym[0])
          continue;
        
        unsigned int numOfWords = 1;         // Loop counter
        unsigned int indexOfAcro = 1;        // Index of the letter of acronym
        
        // While end of string hasn't been reached
        while (newWord[numOfWords] != 0)    
        {
          // If letters of acronym are found, go to next letter
          if (newWord[numOfWords] == new_acronym[indexOfAcro])
            indexOfAcro++;
          
          // If all letters are found in a word
          if (indexOfAcro >= acronym.size())
          {
            // Put the word into the word array that is storing the words that 
            // contain that acronym
            words.push_back(word);
            break;
          }
          // Increment word that is being looked at            
          numOfWords++;                     
        }             
      }
    }
    return scrFILE_OK;                      // Return successful
  }
}
