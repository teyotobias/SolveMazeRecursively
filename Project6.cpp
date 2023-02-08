// Recursion <Project6.cpp>
// EE 312 Project 6 submission by
// Teyo Turrubiates
// ttt2443
// Slip days used: 0
// Summer 2022

#include <stdio.h>
#include <stdint.h>
#include "MazeParams.h"
#include "Recursion.h"
#include <cmath> //for fabs function
#include <cfloat> //used for FLT_EPSILON

/* return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 */

/* return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * solve the problem recursively and
 * use an "n-1" type of decomposition
 */
int minRec1(int x[], int n) {
    if(n == 1){
        return x[0];
    }
    if(x[n-1] < x[n-2]){
        int temp = x[n-1];
        x[n-1] = x[n-2];
        x[n-2] = temp;
        return minRec1(x, n-1);
    }
    else {
        return minRec1(x, n-1);
    }
}

/*
 * return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * n may be either odd or even
 * solve the problem recursively and
 * use an "n / 2" type of decomposition
 */


//test case: n = 3:
/*
 * exterior frame: leftSmallest will evaluate from elements 1-1
 * rightSmallest will evaluate from elements 2-2 and compare it against last element (3) so that all #'s are accounted for
 */
int minRec2(int x[], int n) {
    if(n == 1){
        return x[n-1];
    }
    else {
        int leftSmallest = x[n-1]; //accounts for odd numbers
        if(leftSmallest < minRec2(x, n/2)){
            leftSmallest = x[n-1];
        }
        else {
            leftSmallest = minRec2(x,n/2);
        }
        int rightSmallest = x[n-1]; //accounts for odd numbers -> last number is left out in minRec2 call so must compare
        if(rightSmallest < minRec2(x + n/2,n/2)){
            rightSmallest = x[n-1];
        }
        else {
            rightSmallest = minRec2(x+n/2,n/2);
        }
        if(rightSmallest < leftSmallest){
            return rightSmallest;
        }
        else {
            return leftSmallest;
        }
    }

}
/*
int minRec2(int x[], int n){
    if(n == 1){
        return x[0];
    }
    else {
        int first_h = minRec2(x,n/2);
        int second_h = minRec2(x+n/2,n/2);
        if(first_h > second_h){
            return second_h;
        }
        else {
            return first_h;
        }
    }

}
 */



/*
 * calculate and return the square root of x.
 * The other two parameters are estimates of the square root.
 * low_guess is smaller than the actual square root, and high_guess
 * is larger than the actual square root.
 * Searching for the square root can be done much like searching
 * for a name in a phone book.
 *
 * Since you can't calculate a square root exactly, for this problem
 * you're required to calculate the answer to 15 decimal digits of
 * accuracy.
 */
double sqrtRec(double x, double low_guess, double high_guess) {
    if(low_guess == 0){low_guess++;} //needed for division
    if(x == 0 || x == 1){ return x;} //base cases

    //babylonian method for finding square root
    double next = (low_guess+x/low_guess)/2;
    if(fabs(next-low_guess) < FLT_EPSILON*x){
        return next;
    }
    else {
        return sqrtRec(x,next,high_guess);
    }
}


/*
 * using only recursion, write a string comparison function
 * return -1 if str1 is less than str2
 * return 0 if the two strings are equal
 * return +1 if str1 is greater than str2
 * when comparing strings, use the ASCII value to compare each character
 * (i.e., that means 'A' is less than 'a' since it's ASCII value is smaller)
 * The string str1 is less than str2 if either
 * str1[0] < str2[0]
 * or there exists a k such that str1[k] < str2[k] and
 *   for all j < k str1[j] == str2[j]
 *   and k is less than the length of str1 and str2
 */

//what if string1 goes beyond string2 and vice versa????
int strCompare(char* str1, char* str2) {
    if(*str1 == NULL && *str2 == NULL){
        return 0;
    }
    else if(*str1 == NULL){
        return-1;
    }
    else if(*str2 == NULL){
        return 1;
    }
    else if(*str1 > *str2){
        return 1;
    }
    else if(*str2 > *str1){
        return -1;
    }
    else {
        str1++;
        str2++;
        return strCompare(str1,str2);
    }

}


/*
 * if c is not a letter return -1
 * if c is a letter, return the position of c in the alphabet
 * where 'A' (and 'a') are position 1 and 'Z' (and 'z') are position 26
 *
 * This code is rather ugly as I'm exploiting some detailed knowledge of the ASCII table
 */
int whatLetter(char c) {
    if (c < 'A') { return -1; }
    if (c > 'z') { return -1; }
    if (c > 'Z' && c < 'a') { return -1; }
    return c & ~32 - 64;
}

/*
 * same as before, only this time
 * ignore anything that is not a letter
 * ignore the case (upper case, lower case)
 * So, strCompare2("Hello", "hello") should return 0 (they're the same)
 * strCompare2("The plane!", "theater") should return 1 since "theplane" is larger than "theater"
 * once again, you can only use recursion, no loops
 */
int strCompare2(char* str1, char* str2) {
    if(*str1 == NULL && *str2 == NULL){
        return 0;
    }
    if(*str1 == NULL && *str2 > 64){
        return -1;
    }
    if(*str2 == NULL && *str1 > 64){
        return 1;
    }
    if(*str1 < 64){
        str1++;
        if(*str1 == NULL && *str2 == NULL){
            return 0;
        }
    }
    if(*str2 < 64){
        str2++;
        if(*str1 == NULL && *str2 == NULL){
            return 0;
        }
    }
    //cases for capital letters: both, str1, str2

    if(*str1 > 64 && *str1 < 91 && *str2 > 64 && *str2 < 91){
        if(*str1+32 > *str2+32){
            return 1;
        }
        else if(*str2+32 > *str1+32){
            return -1;
        }
        else {
            str1++;
            str2++;
            return strCompare2(str1,str2);
        }

    }
    //str1 capital case

    if(*str1 > 64 && *str1 < 91){
        if(*str1+32 > *str2){
            return 1;
        }
        else if(*str2 > *str1+32){
            return -1;
        }
        else {
            str1++;
            str2++;
            return strCompare2(str1,str2);
        }
    }
    //str2 capital case

    if(*str2 > 64 && *str2 < 91){
        if(*str1 > *str2+32){
            return 1;
        }
        else if(*str2+32 > *str1){
            return -1;
        }
        else {
            str1++;
            str2++;
            return strCompare2(str1,str2);
        }
    }
    //regular case
    if(*str1 > *str2){
        return 1;
    }
    else if(*str2 > *str1){
        return -1;
    }
    else {
        str1++;
        str2++;
        return strCompare2(str1,str2);
    }
}

/*
 * the two dimensional array maze[MATRIX_SIZE][MATRIX_SIZE] contains a maze
 * Each square is (initially) either a 1 or a zero.  Each 1 represents a wall
 * (you cannot walk through walls, so you can't go into any square where the
 * value is 1).  Each 0 represents an open space.
 *
 * Write an recursive solution to find your way out of the maze
 * Your starting point is at row and col. (params to this function)
 * Your exit point is somewhere in the last row (which is: MATRIX_SIZE - 1)
 *
 * There is a relatively easy recursive solution to this problem, the trick is
 * to think of the solution in the following terms:
 *   "In which direction(s) can I go and find a way out of this maze?"
 * In some cases, you may find yourself in a spot in the maze that there's
 * no way out (at least, not without backtracking). In that case, you'd return "false"
 * since the maze has no solution. In most cases, there's one or more ways out
 * from where you are now. Your key question is simply, "what is the first step I need to take"
 *
 * If you considered going "north", and you had a function that could tell you whether
 * it was possible to get out of the maze starting at the square to the north of your
 * current position, then you could use this function to determine if you can get out by
 * going north first. Similarly, you could consider going south, east or west, and (recursively)
 * determine if the maze can be solved from any of those locations.
 *
 * With that hint, the base case should be pretty obvious.  In fact,
 * I'd suggest you consider the possibility that the base case is "Yup, I'm already at
 * the exit!"
 *
 * There is one tricky part to this decomposition.  You need to make certain
 * that the problem is getting smaller.  The "bigness" or "smallness" of this
 * problem is the number of squares that have not yet been tested.  Each time
 * you test an adjacent square (making a recursive call to decide if there is a
 * path to the exit through that square), you'll be reducing  the number of squares
 * that have not yet been tested.  Eventually, you must have tested all the
 * squares and so you'll have to have found a way to the exit.
 *
 * The easy way to deal with the tricky part is to leave "bread crumbs" behind.
 * Before you recursively check any (or all) of your neighbors to see if you
 * can find the exit from there -- drop a bread crumb in your current square.
 * Then, don't ever check to see if you can find the exit using a square
 * with a breadcrumb in it (backtracking into that square would be silly).
 *
 * If you're trying to see if you can find an exit from some square, and all
 * the adjacent squares are either walls, or have bread crumbs in them, then
 * you already know the answer -- "you can't get to the exit from here".
 * Pick up your bread crumb and return false.
 *
 * You can set the value of the current square to "2" to indicate that a bread
 * crumb has been dropped.  Set the square back to 0 when you want to pick
 * the bread crumb back up.
 * be sure not to change any of the squares that are 1 (the walls).
 *
 * for partial credit, you can leave all your bread crumbs on the floor.
 * for full credit, you must pick up all the bread crumbs EXCEPT those
 * along a path to the exit.
 */






int solveMazeRec(int row, int col) {

    if(row == MATRIX_SIZE){
        return true;
    }
    if(maze[row][col] == 1){ //there is a wall
        return false;
    }
    if(maze[row][col] == 2){ //is this needed??
        return false;
    }
    maze[row][col] = 2;
    if(solveMazeRec(row+1,col)){
        return true;
    }
    else if(solveMazeRec(row,col-1)){
        return true;
    }
    else if(solveMazeRec(row-1,col)){
        return true;
    }
    else if(solveMazeRec(row,col+1)){
        return true;
    }
    else {
        maze[row][col] = 0;
        return false;
    }
}
    /*
    bool solvable = solveMazeRec(row+1,col);
    if(solvable){
        return true;
    }
    solvable = solveMazeRec(row,col-1);
    if(solvable){
        return true;
    }
    solvable = solveMazeRec(row-1,col);
    if(solvable){
        return true;
    }
    solvable = solveMazeRec(row,col+1);
    if(solvable){
        return true;
    }
    maze[row][col] = 0;
    return false;
    /*

}





/**********************
 * adjacentCell and isOK are functions provided to help you write
 * solveMazeIt()
 */

/*
 * OK, we're currently at maze[row][col] and we're considering moving
 * in direction dir.
 * Set trow and tcol (local variables inside the calling function)
 * to the row and column that we would move to IF we moved in
 * that direction
 *
 * For example, there are two good ways to use this function.
 * 1. to actually move one step in a direction use:
 *       adjacentCell(row, col, dir, &row, &col);
 *    That will set row and col to new values.  The new values will
 *    be one square away from the old values.
 *
 * 2. to set trow and tcol to a square that is adjacent to row and col use:
 *       adjacentCell(row, col, dir, &trow, &tcol);
 *    That will not change row and col, but will change trow and tcol.
 *    This is useful if you aren't sure if you can actually move in this
 *    direction yet (e.g., maze[trow][tcol] may be a wall!).  So, you set
 *    trow and tcol, and then check to see if it's OK to move there
 */
void adjacentCell(int row, int col, int dir, int* trow, int* tcol) {
    *trow = row;
    *tcol = col;
    switch(dir) {
        case 0: // UP
            *trow = *trow - 1;
            break;
        case 1: // RIGHT
            *tcol = *tcol + 1;
            break;
        case 2: // DOWN
            *trow = *trow + 1;
            break;
        case 3: // LEFT
            *tcol = *tcol - 1;
            break;
    }
}

/*
 * return false if there is a wall in the square for row and col
 * return true if it's not a wall.
 */
/*
int isOK(int row, int col) {
    return (row > 0 && row < MATRIX_SIZE
            && col > 0 && col < MATRIX_SIZE
            && maze[row][col] != 1);
}
 */

/*
 * return the value of the direction that is one turn to the right
 */
int turnRight(int dir) {
    return (dir + 1) % 4;
}

/*
 * return the value of the direction that is one turn to the left
 */
int turnLeft(int dir) {
    return (dir + 3) % 4;
}

/*
 * the two dimensional array maze[MATRIX_SIZE][MATRIX_SIZE] contains a maze
 * Each square is (initially) either a 1 or a zero.  Each 1 represents a wall
 * (you cannot walk through walls, so you can't go into any square where the value
 * is 1).  Each 0 represents an open space.
 *
*/