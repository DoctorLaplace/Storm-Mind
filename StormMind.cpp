
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


using namespace Neurogen;




int main(){
    neuron a, b, c,
            d, e, f;
    
    axon    ab(&a, &b),
            ac(&a, &c),
            bd(&b, &d),
            be(&b, &e),
            bf(&b, &f),
            cd(&c, &d),
            ce(&c, &e),
            cf(&c, &f)            
            ;

    axonLayer axonLayer1, axonLayer2;
    neuronLayer neuronLayer1, neuronLayer2, neuronLayer3;

    neuronLayer1.addNeuron(&a);
    axonLayer1.addAxon(&ab);
    axonLayer1.addAxon(&ac);
    neuronLayer2.addNeuron(&b);
    neuronLayer2.addNeuron(&c);
    axonLayer1.addAxon(&bd);
    axonLayer1.addAxon(&be);
    axonLayer1.addAxon(&bf);
    axonLayer1.addAxon(&cd);
    axonLayer1.addAxon(&ce);
    axonLayer1.addAxon(&cf);
    neuronLayer3.addNeuron(&d);
    neuronLayer3.addNeuron(&e);
    neuronLayer3.addNeuron(&f);



    membrane drem, knight;
    drem.addNeuronLayer(&neuronLayer1);
    drem.addAxonLayer(&axonLayer1);
    drem.addNeuronLayer(&neuronLayer2);
    drem.addAxonLayer(&axonLayer2);
    drem.addNeuronLayer(&neuronLayer3);



    a.activation = 1;
    ab.weight = 0.5;
    ac.weight = 1;
    bd.weight = 1;
    be.weight = 1;
    bf.weight = 1;
    cd.weight = 0.75;
    ce.weight = 0.5;
    cf.weight = 0.5;


    drem.forwardPropogateMembrane();
    drem.displayMembrane();

    vector<int> knightSHape = {2, 3, 4, 3};
    knight.createDense(knightSHape);
    knight.displayMembrane();





    return 0;
}






















