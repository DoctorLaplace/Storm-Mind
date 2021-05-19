
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

    architect ark;

    membrane everus;
    everus.name = "Everus";


    vector<int> nnShape = {3, 8, 8, 1};
    vector<double> imp1 = {0, 0, 1};
    vector<double> imp2 = {1, 0, 1};
    vector<double> imp3 = {0, 1, 1};
    vector<double> imp4 = {1, 1, 1};
    vector<double> des1 = {0};
    vector<double> des2 = {1};
    vector<double> des3 = {1};
    vector<double> des4 = {0};
    vector<vector<double>> imprintSet = {imp1, imp2, imp3, imp4};
    vector<vector<double>> desiredSet = {des1, des2, des3, des4};



    everus.createDense(nnShape);

    membrane* vera = ark.evolveSupervised(&everus, imprintSet, desiredSet, 0.2, 40, 300);

    ark.computeMembrane(vera, imp1);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp2);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp3);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp4);
    vera->displayMembrane();


    cout << "=================\n\n";




    // architect nebulus;

    // membrane knight;
    // knight.name = "Knight";


    // vector<int> knightShape = {5, 3, 2};
    // vector<double> imprint = {0.2, 0.5, 1, 0.4, 0.1};
    // vector<double> output;
    // knight.createDense(knightShape);
    // nebulus.computeMembrane(&knight, imprint);
    // output = knight.returnLayerActivity(2);


    // printDVector(output);
    // knight.mutateAxonMembrane(0.5);
    // nebulus.computeMembrane(&knight, imprint);
    // output = knight.returnLayerActivity(2);
    // printDVector(output);
    // knight.displayMembrane();
    // knight.displayMembraneAxons();




    // cout << "========CLONE ZONE=========\n\n";

    // membrane* witch = knight.copyDenseMembrane(&knight);
    // witch->name = "witch";
    // witch->mutateAxonMembrane(0.3);
    // nebulus.computeMembrane(witch, imprint);
    // output = witch->returnLayerActivity(2);
    // witch->displayMembrane();
    // witch->displayMembraneAxons();


    // neuron a,b,c,d;
    // a.name = "a";
    // b.name = "b";
    // c.name = "c";
    // d.name = "d";

    // neuron* e = a.copyNeuron();
    // cout << e->name << endl;
    // a.name = "a mod";
    // cout << e->name << endl;
    // cout << a.name << endl;
    // e->name = "e";
    // cout << e->name << endl;
    // cout << a.name << endl;


    return 0;
}






















