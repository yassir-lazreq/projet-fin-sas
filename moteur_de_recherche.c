#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct word
{
    char mot[100];
    int occurrences;
    int longueur;
    int position[100];
};

struct word tab_words[100];
int nbrWords = 0;
int totalWords = 0;

void ajouter_texte(){
    printf("veuillez entrer un texte : ");
    char text[2000];
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    for (int i = 0 ; i < strlen(text) ; i++){
        text[i] = tolower(text[i]);
    }
    int i = 0 , j = 0;
    while (text[i] != '\0'){
        if(!ispunct(text[i])){
            text[j] = text[i];
            j++;
        }
        i++;
    }
    text[j] = '\0';
    char *word = strtok(text, " ");
    int word_pos = 1;
    printf("text traite : " );
    while (word != NULL)
    {
        printf("%s ", word);
        int found = 0;
        for (int k = 0; k < nbrWords; k++) {
            if (strcmp(tab_words[k].mot, word) == 0) {
                tab_words[k].occurrences++;
                tab_words[k].position[tab_words[k].occurrences - 1] = word_pos;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(tab_words[nbrWords].mot, word);
            tab_words[nbrWords].occurrences = 1;
            tab_words[nbrWords].position[0] = word_pos;
            tab_words[nbrWords].longueur = strlen(word);
            nbrWords++;
        }
        totalWords++;
        word_pos++;
        word = strtok (NULL, " ");
    }
    printf("\n");
}

void afficher_mots(){
    printf("les mots sont : \n");
    for (int i = 0; i < nbrWords; i++) {
        if (tab_words[i].occurrences > 0) {
            printf("mot : %s occurrences :  %d position : ", tab_words[i].mot, tab_words[i].occurrences);
            printf("(");
            for (int j = 0; j < tab_words[i].occurrences; j++) {
                printf("%d", tab_words[i].position[j]);
                if (j < tab_words[i].occurrences - 1) {
                    printf(", ");
                }
            }
            printf(")\n");
        }
    }
}

void rechercher_mot_exact(){
    printf("veuillez entrer le mot a rechercher : ");
    char mot[100];
    scanf("%s", mot);
    getchar();
    for (int i = 0; i < strlen(mot); i++)
    {
        mot[i] = tolower(mot[i]);
    }
    
    for (int i = 0; i < nbrWords; i++) {
        if (strcmp(tab_words[i].mot, mot) == 0) {
            printf("mot : %s occurrences :  %d  longueur %d position : ", tab_words[i].mot, tab_words[i].occurrences, tab_words[i].longueur);
            printf("(");
            for (int j = 0; j < tab_words[i].occurrences; j++) {
                printf("%d ", tab_words[i].position[j]);
            }
            printf(")\n");
            return;
        }
    }
    printf("mot non trouve\n");    
}

void rechercher_mot_partiel(){
    printf("veuillez entrer le mot partiel a rechercher : ");
    char mot[100];
    scanf("%s", mot);
    getchar();
    for (int i = 0; i < nbrWords; i++) {
        if (strstr(tab_words[i].mot, mot) != NULL) {
            printf("mot : %s occurrences :  %d position : ", tab_words[i].mot, tab_words[i].occurrences);
            printf("(");
            for (int j = 0; j < tab_words[i].occurrences; j++) {
                printf("%d ", tab_words[i].position[j]);
            }
            printf(")\n");
        }
    }
}

void trier_mots_alphabetique(){
    for (int i = 0; i < nbrWords - 1; i++) {
        for (int j = i + 1; j < nbrWords; j++) {
            if (strcmp(tab_words[i].mot, tab_words[j].mot) > 0) {
                struct word temp = tab_words[i];
                tab_words[i] = tab_words[j];
                tab_words[j] = temp;
            }
        }
    }
}

void trier_mots_occurrences(){
    for (int i = 0; i < nbrWords - 1; i++) {
        for (int j = i + 1; j < nbrWords; j++) {
            if (tab_words[i].occurrences < tab_words[j].occurrences) {
                struct word temp = tab_words[i];
                tab_words[i] = tab_words[j];
                tab_words[j] = temp;
            }
        }
    }
}

void trier_mots_longueur(){
    for (int i = 0; i < nbrWords - 1; i++) {
        for (int j = i + 1; j < nbrWords; j++) {
            if (tab_words[i].longueur > tab_words[j].longueur) {
                struct word temp = tab_words[i];
                tab_words[i] = tab_words[j];
                tab_words[j] = temp;
            }
        }
    }
}

void trier_mots(){
    printf("--------trier les mots--------\n");
    printf("1. par ordre alphabetique\n");
    printf("2. par nombre d'occurrences\n");
    printf("3. par longueur de mot\n");
    int choix;
    printf("entrer votre choix: ");
    scanf("%d", &choix);
    switch (choix){
        case 1:
            trier_mots_alphabetique();
            break;
        case 2:
            trier_mots_occurrences();
            break;
        case 3:
            trier_mots_longueur();
            break;
        default:
            printf("choix invalide\n");
    }
    afficher_mots();
}

void nbr_Total_Mots(){
    printf("nombre total de mots : %d\n", totalWords);
}
void nbr_Mots_Uniques(){
    int count = 0;
    for (int i = 0; i < 100; i++) {
        if (tab_words[i].occurrences == 1) {
            count++;
        }
    }
    printf("nombre de mots uniques : %d\n", count);
}

void diversite_Lexicale(){
    int unique = 0;
    for (int i = 0; i < nbrWords; i++) {
        if (tab_words[i].occurrences == 1) {
            unique++;
        }
    }
    if (nbrWords > 0) {
        float diversite = (float)unique / nbrWords;
        printf("diversite lexicale : %.2f\n", diversite);
    } else {
        printf("diversite lexicale : 0.00\n");
    }
}


void moyenne_Longueur(){
    int totalLong = 0;
    for (int i = 0; i < nbrWords; i++) {
        totalLong += tab_words[i].longueur * tab_words[i].occurrences;
    }
    if (totalWords > 0) {
        float moyenne = (float)totalLong / totalWords;
        printf("moyenne de longueur des mots : %.2f\n", moyenne);
    } else {
        printf("moyenne de longueur des mots : 0.00\n");
    }
}
void plus_Frequents(){
    printf("le mot le plus frequent : ");
    int max = 0;
    char motFreq[100];
    for (int i = 0; i < 100; i++)
    {
        if (tab_words[i].occurrences > 0 && tab_words[i].occurrences > max) {
            max = tab_words[i].occurrences;
            strcpy(motFreq, tab_words[i].mot);
        }
    }
    if (max > 0) {
        printf("mot : %s occurrences : %d\n", motFreq, max);
    } else {
        printf("aucun mot trouve\n");
    }
}

void plus_Longs(){
    printf("le mot le plus long : ");
    int max = 0;
    char motMax[100];
    for (int i = 0; i < nbrWords; i++)
    {
        if (tab_words[i].occurrences > 0 && tab_words[i].longueur > max) {
            max = tab_words[i].longueur;
            strcpy(motMax, tab_words[i].mot);
        }
    }
    if (max > 0) {
        printf("mot : %s longueur : %d\n", motMax, max);
    } else {
        printf("aucun mot trouve\n");
    }
}

void plus_Courts(){
    printf("le mot le plus court : ");
    int min = 100;
    char motMin[100];
    for (int i = 0; i < nbrWords; i++)
    {
        if (tab_words[i].occurrences > 0 && tab_words[i].longueur < min) {
            min = tab_words[i].longueur;
            strcpy(motMin, tab_words[i].mot);
        }
    }
    if (min < 100) {
        printf("mot : %s longueur : %d\n", motMin, min);
    } else {
        printf("aucun mot trouve\n");
    }
}
void statistiques_globales(){
    nbr_Total_Mots();
    nbr_Mots_Uniques();
    diversite_Lexicale();
    moyenne_Longueur();
    plus_Frequents();
    plus_Longs();
    plus_Courts();
}

void palindrome() {
    printf("les mots palindromes sont : \n");
    int found = 0;
    for (int i = 0; i < nbrWords; i++) {
        char temp[100];
        strcpy(temp, tab_words[i].mot);
        if (strcmp(tab_words[i].mot, strrev(temp)) == 0 && strlen(tab_words[i].mot) > 1) {
            printf("%s\n", tab_words[i].mot);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucun palindrome trouve\n");
    }
}

void trier_lettres(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

void anagramme() {
    int visited[100] = {0};
    int found = 0;
    for (int i = 0; i < nbrWords; i++) {
        for (int j = i + 1; j < nbrWords; j++) {
            if (strlen(tab_words[i].mot) == strlen(tab_words[j].mot)) {
                char copie1[100], copie2[100];
                strcpy(copie1, tab_words[i].mot);
                strcpy(copie2, tab_words[j].mot);
                trier_lettres(copie1);
                trier_lettres(copie2);
                if (strcmp(copie1, copie2) == 0 && !visited[j] && !visited[i]) {
                    printf("Anagramme: %s et %s\n", tab_words[i].mot, tab_words[j].mot);
                    visited[j] = 1;
                    visited[i] = 1;
                    found = 1;
                }
            }
        }
    }
    if (!found) {
        printf("Aucun anagramme trouve\n");
    }
}

void nuage_de_mots(){
    printf("nuage de mots : \n");
    for (int i = 0; i < nbrWords; i++) {
        if (tab_words[i].occurrences > 0) {
            for (int j = 0; j < tab_words[i].longueur; j++) {
                printf("*");
            }
            printf(" ");
        }
    }
    printf("\n");
}

void analyses(){
    printf("--------analyses--------\n");
    printf("1. palindrome\n");
    printf("2. anagramme\n");
    printf("3. nuage de mots\n");
    int choix;
    printf("entrer votre choix: ");
    scanf("%d", &choix);
    switch (choix){
        case 1:
            palindrome();
            break;
        case 2:
            anagramme();
            break;
        case 3:
            nuage_de_mots();
            break;
        default:
            printf("choix invalide\n");
    }
}

int main (){
    
    while (1){
        printf("--------menu--------\n");
        printf("1. Ajouter un texte\n");
        printf("2. afficher les mots\n");
        printf("3. Rechercher un mot exact\n");
        printf("4. Rechercher un mot partiel\n");
        printf("5. trier les mots \n");
        printf("6. statistiques globales\n");
        printf("7. analyses\n");
        printf("8. Quitter\n");
        int choix;
        printf("entrer votre choix: ");
        scanf("%d", &choix);
        getchar();
        switch (choix){
            case 1:
                ajouter_texte();
                break;
            case 2:
                afficher_mots();
                break;
            case 3:
                rechercher_mot_exact();
                break;
            case 4:
                rechercher_mot_partiel();
                break;
            case 5:
                trier_mots();
                break;
            case 6:
                statistiques_globales();
                break;
            case 7:
                analyses();
                break;
            case 8:
                exit(0);
            default:
                printf("choix invalide\n");
        }
    }
    return 0;
}