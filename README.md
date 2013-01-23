Website-Provider
================

This is a college project (2nd year, 1st semester) for the class 'Algoritmos e Estruturas de Dados' (Algorithms and Data Structures)

The whole point of this project was to further develop our skills in C++ and also to learn some new skills in programming.
The first part of the project was to implement classes, polymorphism, templates, exception handling and writing to files.
In the second part we integrated the use of binary search trees, priority queues and hash tables.

The application has the following objectives:
- Create websites (for companies and personal use) and users that are mutually associated
- Modify and delete websites and users (and update the rest of the data accordingly)
- List and search (by various criteria) websites and users
- Binary search trees are used to make a "Catalog" of website prototypes
- Priority queues house the requests of websites by users
- Hash tables store the users that were removed from the system (ex-clients)

The variables, function names, comments and documentation were all written in portuguese. (Sorry for that, next time it 
will be all in english!)

This was an interesting project because it made us learn how to implement all the things we learned during the classes.
It features a really nice menu (in terminal :p ), every object is carefully managed through pointers (for example, if
a user is deleted, the websites he manages must remove the pointer to him!), template functions are use to query the user
for the data, be it a name, number, price... The menu doesn't manage the objects, it only calls the right functions in the
"engine", which is the website provider class. 

I can say that I'm proud of some features and also should've done some parts of the code differently (polymorphism,
why have you forsaken me?). But in the end I think the project wasn't too shabby ;)

Just build, compile and run it in the terminal! The file "wsp.txt" will be created to store all the information that has been entered.
