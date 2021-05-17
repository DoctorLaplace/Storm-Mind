
#include <iostream>
#include "Neurogen.h"
#include "Thunder.h"
#include "StormMindTests.cpp"
#include <windows.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>
#include <string>
#include <iomanip>

using namespace Neurogen;




int main(){
    // Seed randomosity for mutations
    std::srand(std::time(nullptr));


    // neuron a, b, c,
    //         d, e, f;
    
    // axon    ab(&a, &b),
    //         ac(&a, &c),
    //         bd(&b, &d),
    //         be(&b, &e),
    //         bf(&b, &f),
    //         cd(&c, &d),
    //         ce(&c, &e),
    //         cf(&c, &f)            
    //         ;

    // axonSet axonLayer1, axonLayer2;
    // neuronLayer neuronLayer1, neuronLayer2, neuronLayer3;

    // neuronLayer1.addNeuron(&a);
    // axonLayer1.addAxon(&ab);
    // axonLayer1.addAxon(&ac);
    // neuronLayer2.addNeuron(&b);
    // neuronLayer2.addNeuron(&c);
    // axonLayer2.addAxon(&bd);
    // axonLayer2.addAxon(&be);
    // axonLayer2.addAxon(&bf);
    // axonLayer2.addAxon(&cd);
    // axonLayer2.addAxon(&ce);
    // axonLayer2.addAxon(&cf);
    // neuronLayer3.addNeuron(&d);
    // neuronLayer3.addNeuron(&e);
    // neuronLayer3.addNeuron(&f);



    // membrane drem, knight;
    // drem.addNeuronLayer(&neuronLayer1);
    // drem.addAxonLayer(&axonLayer1);
    // drem.addNeuronLayer(&neuronLayer2);
    // drem.addAxonLayer(&axonLayer2);
    // drem.addNeuronLayer(&neuronLayer3);



    // a.activation = 1;
    // ab.weight = 0.5;
    // ac.weight = 1;
    // bd.weight = 1;
    // be.weight = 1;
    // bf.weight = 1;
    // cd.weight = 0.75;
    // ce.weight = 0.5;
    // cf.weight = 0.5;


    // drem.forwardPropogateMembrane();
    // drem.displayMembrane();
    // axonLayer1.displayAxons();

    cout << "=================\n\n";

    membrane knight;

    vector<int> knightSHape = {2, 3, 2};
    knight.createDense(knightSHape);
    knight.setNeuronActivity(0,0,1);
    knight.setNeuronActivity(0,1,1);
    knight.displayMembrane();
    //knight.displayMembraneAxons();
    knight.forwardPropogateMembrane();
    knight.displayMembrane();
    knight.displayMembraneAxons();

    cout << "=================\n\n";

    knight.zeroNeuronMembrane();
    knight.setNeuronActivity(0,0,1);
    knight.setNeuronActivity(0,1,1);
    knight.mutateAxonMembrane(0.2);
    knight.forwardPropogateMembrane();
    knight.displayMembrane();
    knight.displayMembraneAxons();


    // neuron a,b,c,d;
    // a.name = "a";
    // b.name = "b";
    // c.name = "c";
    // d.name = "d";

    // axon ad(&a, &d), bd(&b, &d), cd(&c, &d);
    // axonSet nexus;
    // nexus.addAxon(&ad);
    // nexus.addAxon(&bd);
    // nexus.addAxon(&cd);
    // nexus.forwardPropagate();




    return 0;
}






















