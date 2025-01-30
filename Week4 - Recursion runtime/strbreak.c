// Find all possible ways to break a string into dictionary words
// Input: String and dictionary words

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LEN 50
#define MAX_DICT_SIZE 100

bool dictionaryContains(char *word, char dictionary[][MAX_WORD_LEN], int dictSize) {
    for(int i = 0; i < dictSize; i++)
        if(strcmp(dictionary[i], word) == 0)
            return true;
    return false;
}

void wordBreakUtil(char *str, int n, char dictionary[][MAX_WORD_LEN], int dictSize, 
                   char *result, int resultSize) {
    for(int i = 1; i <= n; i++) {
        char word[MAX_WORD_LEN] = "";
        strncpy(word, str, i);
        word[i] = '\0';
        
        if(dictionaryContains(word, dictionary, dictSize)) {
            if(i == n) {
                strcat(result, word);
                printf("%s\n", result);
                return;
            }
            int len = strlen(result);
            strcat(result, word);
            strcat(result, " ");
            wordBreakUtil(str + i, n - i, dictionary, dictSize, result, resultSize);
            result[len] = '\0';
        }
    }
}

int main() {
    char dictionary[MAX_DICT_SIZE][MAX_WORD_LEN];
    char str[1000], result[2000] = "";
    int dictSize;
    
    printf("Enter number of words in dictionary: ");
    scanf("%d", &dictSize);
    
    printf("Enter dictionary words:\n");
    for(int i = 0; i < dictSize; i++)
        scanf("%s", dictionary[i]);
        
    printf("Enter string to break: ");
    scanf("%s", str);
    
    printf("All possible word breaks:\n");
    wordBreakUtil(str, strlen(str), dictionary, dictSize, result, 0);
    
    return 0;
}

// T(n) = T(n-1) + T(n-2) + T(n-3) + ... + T(1)
// T(n-1) = T(n-2) + T(n-3) + ... + T(1)
// Time Complexity: O(2^n)
// The dictionary lookup adds another factor: O(2^n × m) where m is max word length
