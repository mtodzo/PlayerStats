#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Player{
  char name[64];
  float DOC;
  struct Player *next;
};




Player* sort(Player *head, int num){
  struct Player *current = head;

  for (int x=0; x<num; x++){
    head = current;
    while (head -> next != NULL){
      while (head -> next -> DOC > head -> DOC ||
        (head -> DOC == head -> next -> DOC && strcmp(head->name, head->next->name)>0)){
        char tempName[64];
        strcpy(tempName, head -> name);
        float tempDOC = head -> DOC;
        head -> DOC = head -> next -> DOC;
        strcpy(head -> name, head -> next -> name);
        head -> next -> DOC = tempDOC;
        strcpy(head -> next -> name, tempName);
      }
      head = head -> next;
    }
  }
  return current;
};

int main(int argc, char* argv[]) {
  FILE *playerFile = fopen(argv[1], "r");
  int numPlayers = 0;
  struct Player *headPlayer = NULL;
  char name[64];
  if (EOF == fscanf(playerFile, "%s", &name)){
    printf("PLAYER FILE IS EMPTY\n");
    fclose(playerFile);
    return EXIT_SUCCESS;
  };

  while (strcmp(name, "DONE")){
    numPlayers++;
    float points, assists, minutes;
    fscanf(playerFile, "%f", &points);
    fscanf(playerFile, "%f", &assists);
    fscanf(playerFile, "%f", &minutes);

    struct Player *nextPlayer;
    nextPlayer = (struct Player *) malloc(sizeof(struct Player));

    //adding to the front of linked list
    nextPlayer -> next = headPlayer;
    strcpy(nextPlayer -> name, name);
    if (minutes == 0){
      nextPlayer -> DOC = 0.0;
    }
    else{
      nextPlayer -> DOC = (points+assists)/minutes;
    }

    headPlayer = nextPlayer;

    fscanf(playerFile, "%s", &name);

  }
  struct Player *start = headPlayer;

  headPlayer = sort(headPlayer, numPlayers);

  struct Player *freePlayer = NULL;
  while (headPlayer!= NULL){
    printf("%s %f\n",headPlayer -> name, headPlayer -> DOC);
    freePlayer = headPlayer;
    headPlayer = headPlayer -> next;
    free(freePlayer);
  }

  fclose(playerFile);
  return EXIT_SUCCESS;
}
