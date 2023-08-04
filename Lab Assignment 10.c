#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie* createTrie();

// Trie structure
struct Trie
{	
    int isWord;
    struct Trie * next[26];
    int count;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int length = strlen(word);
    int index;

    struct Trie * pCrawl = pTrie;

    for(int i = 0; i < length; i++){
        index = word[i] - 'a';
        if(!pCrawl->next[index]){
            pCrawl->next[index] = createTrie();
        }
        pCrawl = pCrawl->next[index];
        
    }
    pCrawl->count++;
    pCrawl->isWord = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{

    int length = strlen(word);
    int count = 0;
    for(int i = 0; i < length; i++){
        if(pTrie == NULL || pTrie->next == NULL) return 0;
        pTrie = pTrie->next[word[i] - 'a'];
    }
    return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i = 0; i < 26; i++){
        if(pTrie->next[i] != NULL){
            deallocateTrie(pTrie->next[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie* createTrie()
{
    struct Trie *myTree = malloc(sizeof(struct Trie));
    myTree->isWord = 0;
    myTree->count = 0;

    for(int i = 0; i < 26; i++){
        myTree->next[i] = NULL;
    }
    return myTree;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int n = 0;
    
    FILE* ifp = fopen(filename, "r");
    fscanf(ifp, "%d", &n);
    char word[100];

    for(int i = 0; i < n; i++){
        
        pInWords[i] = malloc(sizeof(word));

        fscanf(ifp, "%s\n", word);
        strcpy(pInWords[i], word);

    }

    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}