#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "worder.h"

namespace CS225 {
	bool Worder::Load(const std::string& filename) {
		std::ifstream infile(filename.c_str());
		if (!infile.is_open()) return false;
		else {
			std::istream_iterator<std::string> it(infile);
			std::istream_iterator<std::string> eof;
			std::copy(it, eof, std::back_inserter(words_));
			return true;
		}
	}

	void Worder::Print(bool oneline) const {
		if (oneline)
			std::copy(words_.begin(), words_.end(), std::ostream_iterator<std::string>(std::cout, " "));
		else 
			std::copy(words_.begin(), words_.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

		std::cout << std::endl;
	}

/******************************************************CLASSES******************************************************/
	class CharCountClass {
	public:
		void operator()(std::string string) { counter += string.size(); }  // Adding the size of each string to the count
		CharCountClass() : counter(0) {}      // Initializing counter to 0
		unsigned int Counter(void) { return counter; }   
	private:
		unsigned int counter;
	};
	
	class wordsOfLength {
	public:
		wordsOfLength(unsigned int length) : Length(length), list(0) {}
		void operator()(std::string string) {
			if (string.size() == Length)    // If the current string is equal to the specified length
				list.push_back(string);     // Add that word to the list
		}
		std::list<std::string> ReturnList(void) { 
			list.sort();            // Sort the returning list of all the words of the same length
			list.unique();          // Get rid of duplicates in the list
			return list; 
		}
	private:
		unsigned Length;
		std::list<std::string> list;
	};
	
	class startsWith {
	public:
		startsWith(std::string passedPrefix) : count(0), prefix(passedPrefix) {}   // Initializing the prefix
		void operator()(std::string string) {
			if (prefix.compare(string) <= 0)      // If the words starts with the prefix
				count++;						  // Increment count of words
		}
		unsigned ReturnCount(void) { return count; }
	private:
		unsigned count;
		std::string prefix;
	};
	
	class Substring {
	public:
		Substring(std::string passedSub) : count(0), substr(passedSub) {}   // Initializing substring
		void operator()(std::string string) {
			if (string.find(substr) != std::string::npos)                   // If the substring is found
				count++;
		}
		unsigned ReturnCount(void) { return count; }
	private:
		unsigned count;
		std::string substr;
	};

	class Remove {
	public:
		Remove(std::string word) : remWord(word), newVec(0) {}    // Initializing word that is going to be removed and vector
		void operator()(std::string string) {
			if (string != remWord)                                // Push back all the words that shouldn't be removed onto the new vector
				newVec.push_back(string);
		}
		std::vector<std::string> ReturnVec(void) { return newVec; }

	private:
		std::string remWord;
		std::vector<std::string> newVec;
	};

	class UpperClass {
	public:
		void operator()(std::string & string) {
			std::transform(string.begin(), string.end(), string.begin(), toupper);  // Uppercase each letter in the string
		}
	};

	class Reverse {
	public:
		void operator() (std::string & string) {
			std::reverse(string.begin(), string.end());     // Reverse the letters
		}
	};

	class Join {
	public:
		Join(std::vector<std::string> vec, unsigned size) : newVec(vec), newList(0), i(0), size(size), vecSize(vec.size()), sizeDiff(0) {
			if (vecSize < size)         // Finding the shortest string so that we don't go past the bounds
				sizeDiff = vecSize;
			else if (vecSize > size)
				sizeDiff = size;
		}
		void operator()(std::string string) {
			if (i < sizeDiff) {         // While we are not at the end of the list by knowing if the subscript is equal to the size we are going to
				std::string temp = string + newVec[i];  // Concatenating the two words together
				newList.push_back(temp);  // Put the concatenation into the list
			}
			i++;
		}

		std::list<std::string> ReturnList(void) { return newList; }

	private:
		std::vector<std::string> newVec;
		std::list<std::string> newList;
		unsigned i;
		unsigned size;
		unsigned vecSize;
		unsigned sizeDiff;
	};
	/******************************************************FUNCTIONS******************************************************/
	Worder::Worder() : words_(0) { }

	unsigned Worder::CharCount() const
	{
		// Count the number of characters in the vector of strings
		CharCountClass countObj;
		countObj = std::for_each(words_.begin(), words_.end(), countObj);
		return countObj.Counter();
	}

	StringList Worder::WordsOfLength(unsigned length) const
	{
		// Finding all the words of specified length and adding them to a string list
		wordsOfLength obj(length);
		obj = std::for_each(words_.begin(), words_.end(), obj);
		return obj.ReturnList();
	}

	unsigned Worder::StartsWith(std::string const& prefix) const
	{
		// Counting the number of words that start with a given prefix
		std::string Prefix = prefix;
		startsWith obj(Prefix);
		obj = std::for_each(words_.begin(), words_.end(), obj);
		return obj.ReturnCount();
	}
	
	unsigned Worder::Substrings(std::string const& substring) const
	{
		// Counting the number of words that contain a substring
		std::string Substr = substring;
		Substring obj(Substr);
		obj = std::for_each(words_.begin(), words_.end(), obj);
		return obj.ReturnCount();
	}

	void Worder::RemoveAll(std::string const& word)
	{
		// Removing all of the specified words
		std::string Word = word;
		Remove obj(Word);
		obj = for_each(words_.begin(), words_.end(), obj);
		words_ = obj.ReturnVec();
	}

	void Worder::UpperCase()
	{
		// Uppercasing all strings
		UpperClass obj;
		std::for_each(words_.begin(), words_.end(), obj);
	}

	void Worder::ReverseLetters()
	{
		// Reversing the letters in all of the words
		Reverse reverseObj;
		std::for_each(words_.begin(), words_.end(), reverseObj);
	}

    StringList Worder::JoinWords( Worder const& rhs) const
    {
		// Concatenating two words and adding them to a list
	    unsigned thisSize = words_.size();
	    Join obj(rhs.words_, thisSize);
	    obj = std::for_each(words_.begin(), words_.end(), obj);
	    return obj.ReturnList();
    }

  StringList Worder::FindDuplicates() const
  {
    // Didn't do
    std::list<std::string> StringList;
    return StringList;
  }

  StringList Worder::CommonWords( Worder const& rhs) const
  {
    std::list<std::string>   StringList;
    std::string string = rhs.words_[0];
    StringList.push_back(string);
    return StringList;
  }

} // namespace CS225
