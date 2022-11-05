/*
 * Binárny vyhľadávací strom — iteratívna varianta
 *
 * S využitím dátových typov zo súboru btree.h, zásobníkov zo súborov stack.h a
 * stack.c a pripravených kostier funkcií implementujte binárny vyhľadávací
 * strom bez použitia rekurzie.
 */

#include "../btree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializácia stromu.
 *
 * Užívateľ musí zaistiť, že incializácia sa nebude opakovane volať nad
 * inicializovaným stromom. V opačnom prípade môže dôjsť k úniku pamäte (memory
 * leak). Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je
 * možné toto detegovať vo funkcii.
 */
void bst_init(bst_node_t **tree) {

    
    //(*tree)->right = NULL; 
    //(*tree)->left = NULL;
    *tree = NULL;
}

/*
 * Nájdenie uzlu v strome.
 *
 * V prípade úspechu vráti funkcia hodnotu true a do premennej value zapíše
 * hodnotu daného uzlu. V opačnom prípade funckia vráti hodnotu false a premenná
 * value ostáva nezmenená.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {

//bst_node_t *findnode = NULL;
bst_node_t *nextnode = tree;

while(nextnode != NULL)
{

  if(key < nextnode->key)
    {
      nextnode = nextnode->left;
    } 
  else
    {
      if(key > nextnode->key)
      {
        nextnode = nextnode->right; 
      } else 
      {
        if(key == nextnode->key)
        {
          *value = nextnode->value;
         // printf("%d\n", *value);
          return true;
        }
       
      }
    } 
}
  return false;

}

/*
 * Vloženie uzlu do stromu.
 *
 * Pokiaľ uzol so zadaným kľúčom v strome už existuje, nahraďte jeho hodnotu.
 * Inak vložte nový listový uzol.
 *
 * Výsledný strom musí spĺňať podmienku vyhľadávacieho stromu — ľavý podstrom
 * uzlu obsahuje iba menšie kľúče, pravý väčšie.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_insert(bst_node_t **tree, char key, int value) {

bst_node_t *insertnode = NULL;
bst_node_t *nextnode = *tree;
int node_already_exists = 0;

while(nextnode != NULL)
{

  insertnode = nextnode;


  if(key < nextnode->key)
    {
      nextnode = nextnode->left;
    } 
  else
    {
      if(key > nextnode->key)
      {
        nextnode = nextnode->right; 
      } else 
      {
        node_already_exists = 1;
        break; 
      }
    } 
}

if(!node_already_exists)
{

  bst_node_t *tmp = malloc(sizeof(struct bst_node)); 
  if(tmp == NULL)
  {
    printf("malloc error");
    return;
  }  
    tmp->key = key;
    tmp->value = value;
    tmp->left = NULL;
    tmp->right = NULL;


  if(*tree == NULL)
  {
    (*tree) = tmp;
  }
  else
  {

    if(key < insertnode->key)
    {
     insertnode->left = tmp; 
    } 
    else
    {
      if(key > insertnode->key)
      {
        insertnode->right = tmp;
      }   
    }
  }
}
else
{
  insertnode->value = value;
}
 
}

/*
 * Pomocná funkcia ktorá nahradí uzol najpravejším potomkom.
 *
 * Kľúč a hodnota uzlu target budú nahradené kľúčom a hodnotou najpravejšieho
 * uzlu podstromu tree. Najpravejší potomok bude odstránený. Funkcia korektne
 * uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkcia predpokladá že hodnota tree nie je NULL.
 *
 * Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {

bst_node_t *nextnode = *tree;
bst_node_t *rightmost = NULL;
bst_node_t *father = NULL;

while(nextnode != NULL)
{

   rightmost = nextnode;

   nextnode = nextnode->right;
}

father = *tree; 
while(father->right != rightmost)
{
  father = father->right;
}

target->key = rightmost->key;
target->value = rightmost->value;


if(rightmost->left != NULL)
{
  father->right = rightmost->left;
}





father->right = NULL;
free(rightmost);
rightmost = NULL;
//free(rightmost);


}

/*
 * Odstránenie uzlu v strome.
 *
 * Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí.
 * Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla.
 * Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom
 * ľavého podstromu. Najpravejší uzol nemusí byť listom!
 * Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkciu implementujte iteratívne pomocou bst_replace_by_rightmost a bez
 * použitia vlastných pomocných funkcií.
 */
void bst_delete(bst_node_t **tree, char key) {

//printf("XXXXXXXXXX\n");

bst_node_t *nextnode = *tree;
bst_node_t *foundnode = NULL;
bst_node_t *father = NULL;
bool nodeexists = false;


while(nextnode != NULL)
{
  //printf("XXXXXXXXXX\n");
  if(nextnode->right != NULL)
  {
    if(nextnode->right->key == key)
    {
      father = nextnode;
    }
  }
  
  if(nextnode->left != NULL)
  {
    if(nextnode->left->key == key)
    {
      father = nextnode;
    }
  }


  foundnode = nextnode;

  if(key < nextnode->key)
    {
      nextnode = nextnode->left;
    } 
  else
    {
      if(key > nextnode->key)
      {
        nextnode = nextnode->right; 
      } 
      else 
      {
        if(key == nextnode->key)
        {
          nodeexists = true;
          break;
        }
       
      }
    } 
}

//printf("XXXXXXXXXX\n");
  
  if(nodeexists)
  {

    if(((foundnode->left != NULL) && (foundnode->right ==NULL)) || ((foundnode->left == NULL) && (foundnode->right != NULL)))
    {
//printf("XXXXXXXXXX\n");

      if(foundnode->key < father->key)
      {
        if(foundnode->left != NULL)
        {
          father->left = foundnode->left;
        } 
        else
        {
          if(foundnode->right != NULL)
          {
            father->left = foundnode->right;
          }
        }
      }
      else
      {
        if(foundnode->key > father->key)
        {
          if(foundnode->left != NULL)
          {
            father->right = foundnode->left;
          }
          else
          if(foundnode->right != NULL)
          {
            father->right = foundnode->right;
          }
        }
       }
         free(foundnode);
         foundnode = NULL; 

      }
      else
      {

        if((foundnode->left == NULL) && (foundnode->right == NULL))
        {

          if(key > father->key)
          {
            father->right = NULL;
          } else
          {
            if(key < father->key)
            {
              father->left = NULL; 
            }
          }

          free(foundnode); 
          foundnode = NULL;
        }
        else
        {
          if((foundnode->left != NULL) && (foundnode->right != NULL))
          {
           // bst_node_t *tmp = foundnode;
             bst_replace_by_rightmost(foundnode, &foundnode->left);

          }
        }    
      } 
    }
  }









/*
 * Zrušenie celého stromu.
 *
 * Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po
 * inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených
 * uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_dispose(bst_node_t **tree) {

 /* bst_node_t *deletenode = NULL;

  while(*tree != NULL)
  {

    while()



  }*/


}

/*
 * Pomocná funkcia pre iteratívny preorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu.
 * Nad spracovanými uzlami zavola bst_print_node a uloží ich do zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit) {
}

/*
 * Preorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_preorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_preorder(bst_node_t *tree) {
}

/*
 * Pomocná funkcia pre iteratívny inorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) {
}

/*
 * Inorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_inorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_inorder(bst_node_t *tree) {
}

/*
 * Pomocná funkcia pre iteratívny postorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov. Do zásobníku bool hodnôt ukladá informáciu že uzol
 * bol navštívený prvý krát.
 *
 * Funkciu implementujte iteratívne pomocou zásobníkov uzlov a bool hodnôt a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit,
                            stack_bool_t *first_visit) {
}

/*
 * Postorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_postorder a
 * zásobníkov uzlov a bool hodnôt bez použitia vlastných pomocných funkcií.
 */
void bst_postorder(bst_node_t *tree) {
}
