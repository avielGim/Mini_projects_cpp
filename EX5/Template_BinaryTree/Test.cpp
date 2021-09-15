#include <iostream>
#include <stdexcept>
#include <string>
#include "doctest.h"
#include "BinaryTree.hpp"

using namespace std;
using namespace ariel;

/**
 * check if there is no exeption thrown with different kind of templates
 */
TEST_CASE("kind of templates"){
    CHECK_NOTHROW(BinaryTree<int> tree_of_int);
    CHECK_NOTHROW(BinaryTree<string> tree_of_str);
    CHECK_NOTHROW(BinaryTree<double> tree_of_double);
    CHECK_NOTHROW(BinaryTree<float> tree_of_float);
}

/**
 * check the insert, replace function on BinaryTree of int.
 * also check the preorder iterator and the default (inorder).
 */
TEST_CASE("tree of INTEGER"){
    BinaryTree<int> tree_int;
    //          1 - replace with(0)                                    
    //       /      
    //     2        3 - replce with(5) than replace with(12)            
    //             /                             
    //       1    4    6                                              
    //           /
    //          7

    //  preOrder -  0 -> 2 -> 1 -> 12 -> 4 -> 7 -> 6
    //  inOrder -   2 -> 1 -> 0 -> 7 -> 4 -> 12 -> 6

    CHECK_THROWS(tree_int.add_left(1,2));       // there is no root yet
    CHECK_THROWS(tree_int.add_right(1,3));      // there is no root yet

    CHECK_NOTHROW(tree_int.add_root(1));        // 1 is the root           
    CHECK_NOTHROW(tree_int.add_left(1,2));      // 2 is left son of 1
    CHECK_NOTHROW(tree_int.add_right(1,3));     // 3 is right son of 1

    CHECK_NOTHROW(tree_int.add_left(3,4));      // 3 is left son of 3                           
    
    CHECK_THROWS(tree_int.add_right(5,1));      // 5 doesn't exist.
    CHECK_THROWS(tree_int.add_left(5,2));       // 5 doesn't exist.

    CHECK_NOTHROW(tree_int.add_right(1,5));     // replace 3 with 5
    CHECK_THROWS(tree_int.add_right(3,7));      // 3 does't exist

    CHECK_NOTHROW(tree_int.add_right(5,6));     // 6 is right son of 5 (4 is the right)
    CHECK_NOTHROW(tree_int.add_left(4,7));      // 7 is left son of 4 

    CHECK_NOTHROW(tree_int.add_root(0));        // replace the root
    CHECK_THROWS(tree_int.add_right(1,7));      // 1 is replace by 0 - 1 is not exist
    CHECK_NOTHROW(tree_int.add_right(0,12));    // 5 is replace by 12
    CHECK_NOTHROW(tree_int.add_right(2, 1));    // 1 is the right son of 2
    
    SUBCASE("preOrder: root -> left -> right"){
        //need to be: 0 -> 2 -> 12 -> 4 -> 7 -> 6
        auto pre_iter = tree_int.begin_preorder();
        for(int place = 0; place < 7; place++, pre_iter++) {
            if(pre_iter != tree_int.end_preorder()){
                if(place == 0){
                    CHECK(*pre_iter == 0);
                }
                else if(place == 1){
                    CHECK(*pre_iter == 2);
                }
                else if(place == 2){
                    CHECK(*pre_iter == 1);
                }
                else if(place == 3){
                    CHECK(*pre_iter == 12);
                }
                else if(place == 4){
                    CHECK(*pre_iter == 4);
                }
                else if(place == 5){
                    CHECK(*pre_iter == 7);
                }
                else if(place == 6){
                    CHECK(*pre_iter == 6);
                }
            }
            else{
                FAIL("pre_iter is *NOT* need to be nullptr!");
            }
        }      
        CHECK(pre_iter == tree_int.end_preorder());
    }


    SUBCASE("inorder - left -> root -> right - int"){
        // this should work like inorder
        string ans = "";
        for(int num: tree_int) {  
            ans += to_string(num) + " -> ";
        }   
        CHECK(ans ==  "2 -> 1 -> 0 -> 7 -> 4 -> 12 -> 6 -> ");
    }
}

/**
 * check the insert, replace function on BinaryTree of char.
 * also check the inorder iterator and the default (inorder) - different call to the iterator.
 */
TEST_CASE("tree of CHAR"){
    BinaryTree<char> tree_char;
    //        'a' - replce with('I')   
    //      /    
    //    'b'    'c'  replce with('e') than replce with('n')      
    //          /   
    //        'O'    '!'
    //       /      /
    //     'g'    'E'   '.'  

    //  inOrder -   b -> I -> g -> O -> n -> E -> ! -> .
   

    CHECK_THROWS(tree_char.add_right('e','!'));     // there is no root yet
    CHECK_THROWS(tree_char.add_left('O','g'));      // there is no root yet

    CHECK_NOTHROW(tree_char.add_root('a'));         // 'a' is the root           
    CHECK_NOTHROW(tree_char.add_left('a','b'));     // 'b' is left son of 'a'
    CHECK_NOTHROW(tree_char.add_right('a','c'));    // 'c' is right son of 'a'
    CHECK_NOTHROW(tree_char.add_left('c','O'));     // 'c' is left son of 'O'                           

    CHECK_THROWS(tree_char.add_right('e','a'));     // 'e' doesn't exist.
    CHECK_THROWS(tree_char.add_left('e','b'));      // 'e' doesn't exist.

    CHECK_NOTHROW(tree_char.add_right('a','e'));    // replace 'c' with 'e'
    CHECK_THROWS(tree_char.add_right('c','g'));     // 'c' does't exist

    CHECK_NOTHROW(tree_char.add_right('e','!'));    // '!' is right son of 'e' ('O' is the lest)
    CHECK_NOTHROW(tree_char.add_left('O','g'));     // 'g' is left son of 'O' 

    CHECK_NOTHROW(tree_char.add_root('I'));         // replace the root
    CHECK_THROWS(tree_char.add_right('a','g'));     // 'a' is replace by 'I' - a is not exist
    CHECK_NOTHROW(tree_char.add_right('I','n'));    // replace 'e' with 'n'

    CHECK_NOTHROW(tree_char.add_right('!','.'));    // '.' is the right son of '!'
    CHECK_NOTHROW(tree_char.add_left('!','E'));     // 'E' is the left son of '!'


    SUBCASE("inOrder: left -> root -> right"){
        //need to be: b -> I -> g -> O -> n -> E -> ! -> .
        auto in_iter = tree_char.begin_inorder();
        for(int place = 0; place < 8; place++, in_iter++){
            if(in_iter != tree_char.end_inorder()){
                if(place == 0){
                    CHECK(*in_iter == 'b');
                }
                else if(place == 1){
                    CHECK(*in_iter == 'I');
                }
                else if(place == 2){
                    CHECK(*in_iter == 'g');
                }
                else if(place == 3){
                    CHECK(*in_iter == 'O');
                }
                else if(place == 4){
                    CHECK(*in_iter == 'n');
                }
                else if(place == 5){
                    CHECK(*in_iter == 'E');
                }
                else if(place == 6){
                    CHECK(*in_iter == '!');
                }
                else if(place == 7){
                    CHECK(*in_iter == '.');
                }
            }
            else{
                FAIL("pre_iter is *NOT* need to be nullptr!");
            }
        }
        CHECK(in_iter == tree_char.end_inorder());
    }

    /*SUBCASE("inorder - left -> root -> right - char"){
        // this should work like inorder
        string ans = "";
        for (char chr: tree_char) { 
            ans += chr + " -> ";
        }   
        CHECK(ans ==  "b -> I -> g -> O -> n -> E -> ! -> . -> ");
    }*/
}

/**
 * check the insert, replace function on BinaryTree of string.
 * also check the postorder iterator and the default (inorder).
 */
TEST_CASE("tree of STRING"){
    BinaryTree<string> tree_string;
    //         "one" - replce with("test")                               
    //         /         
    //     "this"   "three" - replce with("five") than replace with("best")
    //             /    
    //         "the"  "test!"
    //         /
    //      "is"

    //  postOrder - this -> is -> the -> test! -> best -> test
    //  inOrder   - this -> one -> is -> the -> best -> test! 

    CHECK_THROWS(tree_string.add_left("one","this"));      // there is no root yet
    CHECK_THROWS(tree_string.add_right("one","three"));    // there is no root yet

    CHECK_NOTHROW(tree_string.add_root("one"));             // "one" is the root           
    CHECK_NOTHROW(tree_string.add_left("one","this"));      // "this" is left son of "one"
    CHECK_NOTHROW(tree_string.add_right("one","three"));    // "three" is right son of "one"
    CHECK_NOTHROW(tree_string.add_left("three","the"));     // "three" is left son of "three"                           

    CHECK_THROWS(tree_string.add_right("five","one"));      // "five" doesn't exist.
    CHECK_THROWS(tree_string.add_left("five","this"));      // "five" doesn't exist.

    CHECK_NOTHROW(tree_string.add_right("one","five"));     // replace "three" with "five"
    CHECK_THROWS(tree_string.add_right("three","is"));      // 'c' does't exist

    CHECK_NOTHROW(tree_string.add_right("five","test!"));   // "test!" is right son of "five" ("the" is the right)
    CHECK_NOTHROW(tree_string.add_left("the","is"));        // "is" is left son of "the" 

    CHECK_NOTHROW(tree_string.add_root("test"));            //replace the root
    CHECK_THROWS(tree_string.add_right("one","is"));        //"a" is replace by "test" - 1 is not exist
    CHECK_NOTHROW(tree_string.add_right("test","best"));
    
    SUBCASE("postOrder:  left -> right -> root"){
        //need to be: this -> is -> the -> test! -> best -> test
        auto post_iter = tree_string.begin_postorder();
        for(int place = 0; place < 6; place++, post_iter++){
            if(post_iter != tree_string.end_postorder()){
                if(place == 0){
                    CHECK(*post_iter == "this");
                }
                else if(place == 1){
                    CHECK(*post_iter == "is");
                }
                else if(place == 2){
                    CHECK(*post_iter == "the");
                }
                else if(place == 3){
                    CHECK(*post_iter == "test!");
                }
                else if(place == 4){
                    CHECK(*post_iter == "best");
                }
                else if(place == 5){
                    CHECK(*post_iter == "test");
                }
            }
            else{
                FAIL("pre_iter is *NOT* need to be nullptr!");
            }
        }
        CHECK(post_iter == tree_string.end_postorder());

    }

    SUBCASE("inorder - left -> root -> right - string"){
        // this should work like inorder
        string ans = "";
        for (const string& str: tree_string) {  
            ans += str + " -> ";
        }   
        CHECK(ans ==  "this -> test -> is -> the -> best -> test! -> ");
    }
}

