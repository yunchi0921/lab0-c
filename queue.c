/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->qsize = 0;
    } else
        return NULL;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q != NULL) {
        list_ele_t *cur = q->head;
        list_ele_t *prev = NULL;
        while (cur) {
            prev = cur;
            cur = cur->next;
            free(prev->value);
            free(prev);
        }
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q) {
        printf("quene is NULL\n");
        return false;
    } else {
        newh = malloc(sizeof(list_ele_t));
        /* Don't forget to allocate space for the string and copy it */
        /* What if either call to malloc returns NULL? */
        if (newh) {
            // including null character
            newh->value = (char *) malloc(strlen(s) + 1);
            strcpy(newh->value, s);
            newh->next = q->head;
            q->head = newh;
            (q->qsize)++;
            /*If only one element in queue ,
            head and tail are on same element.
            */
            if (q->qsize == 1)
                q->tail = newh;
            return true;
        } else {
            return false;
        }
    }
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;
    /*If the q is NULL*/
    if (!q) {
        printf("queue is NULL\n");
        return false;
    } else {
        newh = malloc(sizeof(list_ele_t));
        if (newh) {
            newh->value = (char *) malloc(strlen(s) + 1);
            strcpy(newh->value, s);
            newh->next = NULL;
            if (q->tail != NULL)
                q->tail->next = newh;
            q->tail = newh;
            (q->qsize)++;
            /*If only one element in queue ,
              head and tail are on same element.
              */
            if (q->qsize == 1) {
                q->head = q->tail;
            }
            return true;
        } else {
            return false;
        }
    }
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    list_ele_t *prev = NULL;
    if (q->qsize != 0 && q != NULL) {
        if (sp != NULL) {
            memset(sp, '\0', bufsize);
            strncpy(sp, q->head->value, bufsize - 1);
        }
        prev = q->head;
        q->head = q->head->next;
        /*
          Free the element and the string
        */
        free(prev->value);
        free(prev);
        (q->qsize)--;
        return true;
    } else {
        return false;
    }
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q != NULL)
        return q->qsize;
    else
        return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->qsize == 0)
        return;
    else {
        q->tail = q->head;
        list_ele_t *prev = NULL;
        list_ele_t *cur = q->head;
        list_ele_t *next = NULL;
        while (cur != NULL) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        q->head = prev;
    }
}
