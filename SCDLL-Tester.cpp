#include <iostream>
#include "SortedCircularDLL.h"
using namespace std;

int main()
{
    SortedCircularDLL<int> list1;

    cout << endl;
    cout << "- Is the list empty?\n";
    if(list1.isEmpty())
        cout << "Yes.\n";
    else
        cout << "No.\n";
    cout << endl; //=======================================

    cout << "- Adding -1, 3, 1, -10, 5, 7, 5, 10, 2, 0 sorted from smaller to bigger...\n";
    list1.add(-1);
    list1.add(3);
    list1.add(-10);
    list1.add(5);
    list1.add(7);
    list1.add(5);
    list1.add(10);
    list1.add(2);
    list1.add(0);

    cout << endl; //=======================================

    cout << "- Printing list...\n";
    cout << list1;

    cout << endl; //=======================================

    cout << "- Is the list empty?\n";
    if(list1.isEmpty())
        cout << "Yes.\n";
    else
        cout << "No.\n";
    
    cout << endl; //=======================================
    
    cout << "- Printing list in reverse...\n";
    list1.printReverse();

    cout << endl; //=======================================

    cout << "- Testing copy constructor with [list2(list1)]...\n";
    SortedCircularDLL<int> list2(list1);
    cout << list2;

    cout << endl; //=======================================

    cout << "- Removing 5...";
    if(list1.remove(5))
        cout << "removed!\n";
    else
        cout << "not removed.\n";

    cout << "- Printing list...\n";
    cout << list1;
    cout << endl; //=======================================

    cout << "- Testing operator overload '=' with [list3 = list1]...done!\n";
    SortedCircularDLL<int> list3 = list1;
    cout << "  Printing copied list...\n";
    cout << list3;

    cout << endl; //=======================================

    cout << "- First node of [list3] is " << list3.getFirst();
    cout << "\n- Last node of [list3] is " << list3.getLast();

    cout << endl; //=======================================

    cout << "\n- Number of copies of element '11': " << list1.count(11);

    cout << endl; //=======================================

    cout << "\n- First index of element '3': " << list1.firstIndex(3);
    cout << "\n- Last index of element '11': " << list1.lastIndex(11);

    cout << endl; //=======================================

    cout << "\n- Removing all copies of '11' from copied list [list3]...";
    cout << "removed " << list3.removeAll(11) << " copies.\n";
    cout << "  Printing affected list...\n";
    cout << list3;

    cout << "\n- Setting in [list3] a new element '18' at position 8...\n";
    list3.setAt(8, 18);
    cout << "  Printing list [list3]...\n";
    cout << list3;

    cout << endl; //=======================================

    cout << "- Removing at position 8 in [list3]...";
    if(!list3.removeAt(8))
        cout << "position is out of range.\n";
    else
        cout << "done!\n";

    cout << endl; //=======================================

    cout << "- Printing all three lists...";
    cout << "\n  [list1]: ";
    cout << list1;
    cout << "\n  [list2]: ";
    cout << list2;
    cout << "\n  [list3]: ";
    cout << list3;

    cout << endl; //=======================================

    cout << "\n- Printing all three lists in reverse...";
    cout << "\n  [list1]: ";
    list1.printReverse();
    cout << "\n  [list2]: ";
    list2.printReverse();
    cout << "\n  [list3]: ";
    list3.printReverse();

    cout << endl; //=======================================

    cout << "- Clearing [list1]...\n";
    list1.clear();
    cout << "  Is [list1] empty?\n";
    if(list1.isEmpty())
        cout << "  Yes.\n";
    else
        cout << "  No.\n";

    cout << endl; //=======================================

    cout << "- Adding 20, 40, 32, 10, 15, 7, 46...\n";
    list1.add(20);
    list1.add(40);
    list1.add(32);
    list1.add(10);
    list1.add(15);
    list1.add(7);
    list1.add(46);
    cout << "  Printing [list1]: ";
    cout << list1;
    cout << endl; //=======================================
    
    cout << "- Element in position 4: " << list1.getAt(4);
    cout << endl << endl;

    return 0;
}