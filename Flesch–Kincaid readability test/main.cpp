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


class Fktest
{
public:
    Fktest();
    ~Fktest();
    void input();
    void calculateindex();
    void print();
    
    
private:
    std::string* phrase;
    int n_sentence, n_word, n_sylla;
    double* index;

    bool is_punctuation(std::string);
    bool is_space (std::string);
    bool is_voel (std::string);
    bool is_eend(std::string);
    
    
    void sentence_count ();
    void wordcount();
    int syllabyword(std::string);
    void syllacount();
    
    
    
    
};


Fktest::Fktest()
{
    this->index = new double(0);
    
    std::string* newphrase = new std::string;
    
    std::cout<< "Please enter a phrase in English: ";
    getline(std::cin,*newphrase);
    phrase = newphrase;
    
}

Fktest::~Fktest()
{
    delete phrase;
    delete index;
    
    
}

void Fktest::input()
{
    delete phrase;
    
    std::string* newphrase = new std::string;
    
    std::cout<< "Please enter a phrase in English: ";
    getline(std::cin,*newphrase);
    phrase = newphrase;
    
    
    
}

void Fktest::print()
{
    
    //output
    std::cout<<"Your number of sentences is: " <<n_sentence <<"\n";
    std::cout<<"Your number of words is: " <<n_word <<"\n";
    std::cout<<"Your number of syllables is: " <<n_sylla <<"\n";
    std::cout<<"Your readability index is: " << *index << std::endl;
    
}

//function to help get punctuation
bool Fktest::is_punctuation (std::string letter)
{
    if(letter=="." || letter=="!" || letter=="?" || letter==":" || letter==";")
        return true;
    else
        return false;
}

//get the number of sentence
void Fktest::sentence_count ()
{
    int sentence=0;
    
    for(int i=0 ; i< phrase->length(); i++)
    {
        if (is_punctuation(phrase->substr(i,1)))
            sentence++;
    }
    n_sentence = sentence;
}

//get the number of spaces
bool Fktest::is_space (std::string a)
{
    if (a == " ")
        return true;
    else
        return false;
}

//get the number of words
void Fktest::wordcount()
{
 
    int word = 1;
    
    for(int i=0 ; i< phrase->length(); i++)
    {
        if (is_space(phrase->substr(i,1)))
            word++;
    }
    n_word = word;
}

//helper function to get voels
bool Fktest::is_voel (std::string a)
{
    if(a == "a" ||a == "i" ||a == "u" ||a == "e" ||a == "o" ||a == "y" ||a == "A" ||a == "I" ||a == "U" ||a == "E" ||a == "O" ||a == "Y" )
        return true;
    else
        return false;
}

//helper function to determine "e" at the end of the word
bool Fktest::is_eend(std::string letter)
{
    if(letter=="e." || letter=="e!" || letter=="e?" || letter=="e:" || letter=="e;" || letter=="e "|| letter=="E." || letter=="E!" || letter=="E?" || letter=="E:" || letter=="E;" || letter=="E ")
        return true;
    else
        return false;
}

//get the number of syllables in a word given
int Fktest::syllabyword (std::string word)
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
void Fktest::syllacount()
{
    
    for(int i=0 ; i < n_word ; i++)
    {
        size_t space;
        
        space = phrase->find(" ",0); //set a word between the beginning and space.
        
        n_sylla += syllabyword(phrase->substr(0,space +1)); //outputs a word to the syllable finding function
        
        phrase->erase(0,space +1 ); //erase the word done analysed.
        
    }
}


//calculate and output the score
void Fktest::calculateindex()
{
    sentence_count();
    wordcount();
    syllacount();
    
    double temp;
    temp = 206.835 - 84.6 * (double)(n_sylla)/n_word - 1.015 * n_word/n_sentence;
    *index = temp;
}

int main()
{
    Fktest test;
    test.calculateindex();
    test.print();
    
    
    
    
    return 0;
}
