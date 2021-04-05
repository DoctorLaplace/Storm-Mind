


#include <iostream>
#include "Thunder.h"
#include <windows.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>


using namespace std; using namespace Thunder;


void testGeneCross();


int main(){
    srand(time(NULL));

    Neuron a1, a2, b1, b2, b3, c1, c2;


    a1.setActivity(1);
    a2.setActivity(1);



    a1.addConnection(&b1, 0.1);
    a1.addConnection(&b2, 0.1);
    a1.addConnection(&b3, 0.1);
    a2.addConnection(&b1, 0.2);
    a2.addConnection(&b2, 0.2);
    a2.addConnection(&b3, 0.2);

    b1.addConnection(&c1, 0.1);
    b1.addConnection(&c2, 0.1);
    b2.addConnection(&c1, 0.1);
    b2.addConnection(&c2, 0.1);
    b3.addConnection(&c1, 0.1);
    b3.addConnection(&c2, 0.1);

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


    Evolver Xeno;
    Layer* Manifold;

    Neuron x1,x2,x3,y1,y2,y3,z1,z2;
    x1.addConnection(&z1,0.1);
    x2.addConnection(&z1,0.1);
    x3.addConnection(&z1,0.1);
    y1.addConnection(&z1,0.2);
    y2.addConnection(&z1,0.2);
    y3.addConnection(&z1,0.2);

    Layer film1, film2;
    film1.addNeuronToLayer(&x1);
    film1.addNeuronToLayer(&x2);
    film1.addNeuronToLayer(&x3);
    film2.addNeuronToLayer(&y1);
    film2.addNeuronToLayer(&y2);
    film2.addNeuronToLayer(&y3);

    Manifold = Xeno.geneCrossLayers(&film1, &film2);
    cout << "Hybrid Layer: \n";
    Manifold->displayLayer();



    return 0;
}










// Test functions

void testGeneCross(){
    Neuron a1, a2, b1, b2, b3;
    a1.addConnection(&b1, 0.1);
    a1.addConnection(&b2, 0.1);
    a1.addConnection(&b3, 0.1);
    a2.addConnection(&b1, 0.2);
    a2.addConnection(&b2, 0.2);
    a2.addConnection(&b3, 0.2);

    cout << "Testing neuron gene cross...\n";
    Evolver Zephyr;
    Neuron* Protius;
    Protius = Zephyr.geneCrossConnections(&a1, &a2);
    cout << "Genesis Neuron\n";
    Protius->displayConnections();
}
