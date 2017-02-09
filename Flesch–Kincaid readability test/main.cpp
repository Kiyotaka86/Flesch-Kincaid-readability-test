//
//  Kiyotaka Kokubun
//  UID:104669898
//
//  PIC10A  Virtanen
//  Winter 16
//
//  hw6
//
//  This program executes brief version of Flesch–Kincaid readability test.
//  It gets a phrase from the user and analyse the phrase to get the number of words, sentences, and syllables.
//  Then it calculates the score of the test based on those numbers.
//

#include <iostream>
#include <string>



//function to help get punctuation
bool is_punctuation (std::string letter)
{
    if(letter=="." || letter=="!" || letter=="?" || letter==":" || letter==";")
        return true;
    else
        return false;
}

//get the number of sentence
int sentence_count (std::string phrase)
{
    int sentence=0;
    
    for(int i=0 ; i< phrase.length(); i++)
    {
        if (is_punctuation(phrase.substr(i,1)))
            sentence++;
    }
    return sentence;
}

//get the number of spaces
bool is_space (std::string a)
{
    if (a == " ")
        return true;
    else
        return false;
}

//get the number of words
int wordcount(std::string phrase)
{
    int word=1;
    for(int i=0 ; i< phrase.length(); i++)
    {
        if (is_space(phrase.substr(i,1)))
            word++;
    }
    return word;
}

//helper function to get voels
bool is_voel (std::string a)
{
    if(a == "a" ||a == "i" ||a == "u" ||a == "e" ||a == "o" ||a == "y" ||a == "A" ||a == "I" ||a == "U" ||a == "E" ||a == "O" ||a == "Y" )
        return true;
    else
        return false;
}

//helper function to determine "e" at the end of the word
bool is_eend(std::string letter)
{
    if(letter=="e." || letter=="e!" || letter=="e?" || letter=="e:" || letter=="e;" || letter=="e "|| letter=="E." || letter=="E!" || letter=="E?" || letter=="E:" || letter=="E;" || letter=="E ")
        return true;
    else
        return false;
}

//get the number of syllables in a word given
int syllacount (std::string word)
{
    int sylla=0;
    
    for(int i=0; i < word.length(); i++)
    {
        if( (word.substr(i,1)>="a"||word.substr(i,1)>="A") && (word.substr(i,1)<="z"||word.substr(i,1)<="Z") )
        {
            
            if (is_voel(word.substr(i,1)))
            {
                if(is_voel(word.substr(i+1,1)))
                {
                    sylla++;
                    i++;
                }
                else
                    sylla++;
            }
            if (is_eend(word.substr(i,2)))
                sylla--;
        }
    }
    if(sylla<1)
        return 1;
    else
        return sylla;
}


// to catch and send a word to the syllable counting function and store the number of syllable.
int numbersylla_get(std::string phrase, int word)
{
    int syllables=0;
    
    for(int i=0 ; i < word ; i++)
    {
        size_t space;
        
        space = phrase.find(" ",0); //set a word between the beginning and space.
        
        syllables += syllacount(phrase.substr(0,space +1)); //outputs a word to the syllable finding function
        
        phrase.erase(0,space +1 ); //erase the word done analysed.
        
    }
    
    return syllables;
}


//calculate and output the score
void index (std::string phrase)
{
    int word, sylla, sentence;
    
    //use functions
    sentence = sentence_count(phrase);
    word = wordcount(phrase);
    sylla = numbersylla_get(phrase, word);
    
    //output
    std::cout<<"Your number of sentences is: " <<sentence <<"\n";
    std::cout<<"Your number of words is: " <<word <<"\n";
    std::cout<<"Your number of syllables is: " <<sylla <<"\n";
    
    double index = 206.835 - 84.6 * (double)(sylla)/word - 1.015 * word/sentence;
    std::cout<<"Your readability index is: " << index << std::endl;
    
}

int main()
{
    //get a phrase and let functions work
    
    std::string phrase;
    
    std::cout<< "Please enter a phrase in English: ";
    getline(std::cin,phrase);
    
    index(phrase);
    
    system("pause");
    return 0;
}
