


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

    Evolver zurel;


    std::vector<int> shapeA = {3, 4, 1};

    //cout << "Minrae:\n";
    Membrane* minrae = zurel.produceMembrane(shapeA, 1);
    minrae->forwardPropagateMembrane();
    //minrae->displayMembrane();

    //cout << "Arkath:\n";
    Membrane* arkath = zurel.produceMembrane(shapeA, 0);
    arkath->forwardPropagateMembrane();
    //arkath->displayMembrane();

    //cout << "Lemrox:\n";
    Membrane* lemrox = zurel.produceMembrane(shapeA, 0.5);
    lemrox->forwardPropagateMembrane();
    //lemrox->displayMembrane();



    std::vector<double> imp = {0,0, 1};
    std::vector<double> desired = {0};

    std::vector<Membrane*> arkraeStrain = zurel.produceMembraneStrain(minrae, arkath);

    cout << "Testing Fitness..." << endl;

    Membrane* strongestSpecimen;
    strongestSpecimen = zurel.evolveOptimalMembrane(shapeA, minrae, arkath, imp, desired, 2, 5);

    cout << "Strongest Membrane has been found..." << endl;

    //strongestSpecimen->displayMembrane();
    cout << "Performance: " << zurel.scorePerformance(zurel.comparePerformance(desired,zurel.sampleOutputs(strongestSpecimen))) << endl;

    strongestSpecimen->silenceMembrane();
    zurel.imprintInputs(imp,strongestSpecimen);
    strongestSpecimen->forwardPropagateMembrane();
    strongestSpecimen->getMembraneVec().back()->displayLayer();;




    std::vector<double> imp2 = {0, 1, 1};
    std::vector<double> desired2 = {1};

    std::vector<double> imp3 = {1, 0, 1};
    std::vector<double> desired3 = {1};

    std::vector<double> imp4 = {1, 1, 1};
    std::vector<double> desired4 = {0};




    std::vector<std::vector<double>> inSet = {imp, imp2, imp3, imp4};
    std::vector<std::vector<double>> desiredSet = {desired, desired2, desired3, desired4};

    vector<Membrane*> population = {lemrox, minrae, arkath};
    cout << "Testing Fitness..." << endl;

    strongestSpecimen = zurel.evolveOptimalMembraneMulti(shapeA, population, inSet, desiredSet, 100, 100, 5, 0.001);
    cout << "Strongest Membrane has been found..." << endl;

    strongestSpecimen->silenceMembrane();
    zurel.imprintInputs(imp,strongestSpecimen);
    strongestSpecimen->forwardPropagateMembrane();
    strongestSpecimen->displayMembrane();

    strongestSpecimen->silenceMembrane();
    zurel.imprintInputs(imp2,strongestSpecimen);
    strongestSpecimen->forwardPropagateMembrane();
    strongestSpecimen->displayMembrane();

    strongestSpecimen->silenceMembrane();
    zurel.imprintInputs(imp3,strongestSpecimen);
    strongestSpecimen->forwardPropagateMembrane();
    strongestSpecimen->displayMembrane();

    strongestSpecimen->silenceMembrane();
    zurel.imprintInputs(imp4,strongestSpecimen);
    strongestSpecimen->forwardPropagateMembrane();
    strongestSpecimen->displayMembrane();


    //strongestSpecimen->displayMembrane();
    cout << "Total Performance: ";
    cout << zurel.multiEvaluateMembraneFitness(strongestSpecimen, inSet, desiredSet) << endl;


    string userInput;
    double in1, in2;
    while (userInput != "exit"){
        
            cout << "N1: ";
            cin >> userInput;
            if (userInput != "exit"){
                in1 = stoi(userInput);
                cout << "N2: ";
                cin >> userInput;
                if (userInput != "exit"){
                    in2 = stoi(userInput);
                }
            }
            
            if (userInput != "exit"){
                strongestSpecimen->silenceMembrane();
                zurel.imprintInputs({in1, in2, 1},strongestSpecimen);
                strongestSpecimen->forwardPropagateMembrane();
                strongestSpecimen->displayFinalLayer();
                if (zurel.sampleOutputs(strongestSpecimen)[0] >= 0.5){
                    cout << "First Neuron Activated\n";
                }else{
                    cout << "First Neuron Silent\n";
                }
            }
            
    }


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