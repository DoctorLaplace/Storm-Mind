


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
    a2.addConnection(&b1, 0.1);
    a2.addConnection(&b2, 0.1);
    a2.addConnection(&b3, 0.1);

    b1.addConnection(&c1, 0.1);
    b1.addConnection(&c2, 0.1);
    b2.addConnection(&c1, 0.1);
    b2.addConnection(&c2, 0.1);
    b3.addConnection(&c1, 0.1);
    b3.addConnection(&c2, 0.1);

    Layer l1, l2, l3;
    l1.addNeuronToLayer(&a1);
    l1.addNeuronToLayer(&a2);

    l2.addNeuronToLayer(&b1);
    l2.addNeuronToLayer(&b2);
    l2.addNeuronToLayer(&b3);

    l3.addNeuronToLayer(&c1);
    l3.addNeuronToLayer(&c2);

    Membrane m1;

    m1.addLayerToMembrane(&l1);
    m1.addLayerToMembrane(&l2);
    m1.addLayerToMembrane(&l3);

    m1.forwardPropagateMembrane();
    m1.displayMembrane();


    Neuron i1, i2, j1, j2, j3, k1, k2;

    i1.setActivity(1);
    i2.setActivity(1);

    i1.addConnection(&j1, 0.2);
    i1.addConnection(&j2, 0.2);
    i1.addConnection(&j3, 0.2);
    i2.addConnection(&j1, 0.2);
    i2.addConnection(&j2, 0.2);
    i2.addConnection(&j3, 0.2);

    j1.addConnection(&k1, 0.2);
    j1.addConnection(&k2, 0.2);
    j2.addConnection(&k1, 0.2);
    j2.addConnection(&k2, 0.2);
    j3.addConnection(&k1, 0.2);
    j3.addConnection(&k2, 0.2);

    Layer p1, p2, p3;
    p1.addNeuronToLayer(&i1);
    p1.addNeuronToLayer(&i2);

    p2.addNeuronToLayer(&j1);
    p2.addNeuronToLayer(&j2);
    p2.addNeuronToLayer(&j3);

    p3.addNeuronToLayer(&k1);
    p3.addNeuronToLayer(&k2);

    Membrane q1;

    q1.addLayerToMembrane(&p1);
    q1.addLayerToMembrane(&p2);
    q1.addLayerToMembrane(&p3);

    q1.forwardPropagateMembrane();
    q1.displayMembrane();


    Evolver iouna;

    cout << "Vortex:\n";

    Membrane* vortex;
    vortex = iouna.geneCrossMembranes(&m1, &q1);
    vortex->getMembraneVec()[0]->getLayerVec()[0]->setActivity(1);
    vortex->getMembraneVec()[0]->getLayerVec()[1]->setActivity(1);
    iouna.formMembraneConnections(vortex);
    vortex->forwardPropagateMembrane();
    vortex->displayMembrane();

    cout << "Lance:\n";

    Membrane* lance;
    lance = iouna.geneCrossMembranes(&m1, &q1);
    lance->getMembraneVec()[0]->getLayerVec()[0]->setActivity(1);
    lance->getMembraneVec()[0]->getLayerVec()[1]->setActivity(1);
    iouna.formMembraneConnections(lance);
    lance->forwardPropagateMembrane();
    lance->displayMembrane();
    
    cout << "Dromoskus:\n";

    Membrane* dromoskus;
    dromoskus = iouna.geneCrossMembranes(vortex, lance);
    dromoskus->getMembraneVec()[0]->getLayerVec()[0]->setActivity(1);
    dromoskus->getMembraneVec()[0]->getLayerVec()[1]->setActivity(1);
    iouna.formMembraneConnections(dromoskus);
    dromoskus->forwardPropagateMembrane();
    dromoskus->displayMembrane();
    

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


void testGeneCrossLayers(){
    /*cout << "Testing layer gene cross...\n";

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
    Manifold->displayLayer();*/

}