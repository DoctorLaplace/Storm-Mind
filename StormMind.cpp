


#include <iostream>
#include "Thunder.h"
#include <windows.h>

using namespace std; using namespace Thunder;


int main(){


    Neuron a1, a2, b1, b2, b3, c1, c2;


    a1.setActivity(1);
    a2.setActivity(1);



    a1.addConnection(&b1, 0.5);
    a1.addConnection(&b2, 0.7);
    a1.addConnection(&b3, 0.9);
    a2.addConnection(&b1, 0.1);
    a2.addConnection(&b2, 0.2);
    a2.addConnection(&b3, 0.3);

    b1.addConnection(&c1, 0.1);
    b1.addConnection(&c2, 0.1);
    b2.addConnection(&c1, 0.2);
    b2.addConnection(&c2, 0.2);
    b3.addConnection(&c1, 0.3);
    b3.addConnection(&c2, 0.3);

    Layer l1;
    l1.addNeuronToLayer(&a1);
    l1.addNeuronToLayer(&a2);

    Layer l2;
    l2.addNeuronToLayer(&b1);
    l2.addNeuronToLayer(&b2);
    l2.addNeuronToLayer(&b3);

    Layer l3;
    l3.addNeuronToLayer(&c1);
    l3.addNeuronToLayer(&c2);

    Membrane m1;

    m1.addLayerToMembrane(&l1);
    m1.addLayerToMembrane(&l2);
    m1.addLayerToMembrane(&l3);

    m1.displayMembrane();
    m1.forwardPropagateMembrane();
    m1.displayMembrane();

    cout << " Hello\n";
    


    return 0;
}













