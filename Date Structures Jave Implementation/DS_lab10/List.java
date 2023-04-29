package com.company;

public interface List<T> {
    void insert(SNode<T> newElement);
        /*Precondition: newElement is not null.
        Postcondition: Inserts newElement into a list. If the list is not empty, then inserts newElement
        after the cursor. Otherwise, inserts newElement as the first (and only) element in the list. In
        either case, moves the cursor to newElement.*/
    void remove();
        /*Precondition: List is not empty.
        Postcondition: Removes the element marked by the cursor from a list. If the resulting list is
        not empty, then moves the cursor to the element that followed the deleted element. If the
        deleted element was at the end of the list, then moves the cursor to the beginning of the list.*/
    void replace(T newElement);
        /*Precondition: List is not empty and newElement is not null.
        Postcondition: Replaces the element marked by the cursor with newElement. The cursor
        remains at newElement.*/
    void clear();
        /*Precondition: None.
        Postcondition: Removes all the elements in a list.*/
    boolean isEmpty();
        /*Precondition: None.
        Postcondition: Returns true if a list is empty. Otherwise, returns false.*/
    boolean gotoBeginning();
        /*Precondition: None.
        Postcondition: If a list is not empty, then moves the cursor to the beginning of the list and
        returns true. Otherwise, returns false.*/
    boolean gotoEnd();
        /*Precondition: None.
        Postcondition: If a list is not empty, then moves the cursor to the end of the list and returns
        true. Otherwise, returns false.*/
    boolean gotoNext();
        /*Precondition: List is not empty.
        Postcondition: If the cursor is not at the end of a list, then moves the cursor to the next
        element in the list and returns true. Otherwise, returns false.*/
    boolean gotoPrior();
        /*Precondition: List is not empty.
        Postcondition: If the cursor is not at the beginning of a list, then moves the cursor to the
        preceding element in the list and returns true. Otherwise, returns false.*/
    T getCursor();
        /*Precondition: List is not empty.
        Postcondition: Returns the element marked by the cursor*/
}
