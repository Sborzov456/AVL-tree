# AVL Tree :deciduous_tree: 
## :pushpin: Short Description:
   This project implements the _AVL tree data structure_, namely the functions of adding a node, deleting, searching, and some others.
## :pushpin: AVL Tree:
   An AVL tree is a binary tree in which the **_heights of the left and right subtrees for each node differ by no more than one_**. This is the property of balance.
   
   It has been proven that this property provides a _logarithmic dependence_ of the tree height on the number of nodes, which increases the speed of basic operations        such as insertion, deletion and search.
   
   Here is an example of a balanced AVL tree:
   
        50
       /  \
      45  63
     /  \
    43  47
    
## :pushpin: AVL vs Binary 
   The table below compares the **_time complexity_** of running the main algorithms on an AVL tree and a binary tree.
   This table shows that the AVL tree is faster.

   |             | AVL Tree | Binary Tree |
   |-------------|----------|-------------|
   | `insertion` | O(logN)  |    O(N)     |
   | `deletion`  | O(logN)  |    O(N)     |
   | `search`    | O(logN)  |    O(N)     |
   
