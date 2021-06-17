
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
#include <future>           // std::async, std::future

using namespace Neurogen;




int main(){
    // Seed randomosity for mutations
    std::srand(std::time(nullptr));

    cout << "=================\n\n";

    architect ark;


    membrane everus;
    everus.name = "Everus";


    vector<int> nnShape = {2, 60, 1};
    vector<double>  imp1 = {-4, 1},
                    imp2 = {-3, 1},
                    imp3 = {-2, 1},
                    imp4 = {-1, 1},
                    imp5 = {0, 1},
                    imp6 = {1, 1},
                    imp7 = {2, 1},
                    imp8 = {3, 1},
                    imp9 = {4, 1},
                    imp10 = {5, 1};


                    
    vector<double>  des1 = {Neurogen::sinFunction(-4)},
                    des2 = {Neurogen::sinFunction(-3)},
                    des3 = {Neurogen::sinFunction(-2)},
                    des4 = {Neurogen::sinFunction(-1)},
                    des5 = {Neurogen::sinFunction(0)},
                    des6 = {Neurogen::sinFunction(1)},
                    des7 = {Neurogen::sinFunction(2)},
                    des8 = {Neurogen::sinFunction(3)},
                    des9 = {Neurogen::sinFunction(4)},
                    des10 = {Neurogen::sinFunction(5)};
                    



    vector<vector<double>> imprintSet = {imp1, imp2, imp3, imp4, imp5, imp6, imp7, imp8, imp9, imp10};
    vector<vector<double>> desiredSet = {des1, des2, des3, des4, des5, des6, des7, des8, des9, des10};



    everus.createDense(nnShape);

    membrane* vera = ark.evolveSupervised(&everus, imprintSet, desiredSet, 0.5, 2, 2);
    vera->name = "Vera";

    /*ark.computeMembrane(vera, imp1);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp2);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp3);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp4);
    vera->displayMembrane();*/

    cout << "=========NEXT MEM========\n\n";

    membrane zyg("zyg"), wer("wer"), gon("gon"), zygwergon("zygwergon");
    zyg.createDense(nnShape);
    zyg.setAllAxonWeights(1);
    // zyg.neuronLayerVec[4]->neuronVec[0]->type = "none";
    wer.createDense(nnShape);
    wer.setAllAxonWeights(0);
    // wer.neuronLayerVec[4]->neuronVec[0]->type = "none";
    gon.createDense(nnShape);
    gon.setAllAxonWeights(-1);
    // gon.neuronLayerVec[4]->neuronVec[0]->type = "none";
    // zygwergon.createDense(nnShape);
    // zygwergon.copyGeneCrossAxonWeights(&zyg, &wer);
    // zygwergon.copyGeneCrossAxonWeights(&zygwergon, &gon);
    // zygwergon.mutatePartOfAxonWeights(0.1, 0.1);
    // zygwergon.displayMembraneAxons();

    vector<membrane*> initPop = {&zyg, &wer, &gon};
    vector<membrane*> megaspecimens, gen2;

    //ark.displayPopulationAxons(initPop);
    megaspecimens = ark.GEM(initPop, imprintSet, desiredSet);
    gen2 = ark.GEM(megaspecimens, imprintSet, desiredSet);
    for (int i = 0; i < 30; i++){
        cout << "Generation " << i << ": ";
        double mutrate = 0.4;
        if (i > 150){
            mutrate = mutrate*0.5;
        }
        gen2 = ark.GEM(gen2, imprintSet, desiredSet, 0.8, 0.4);
    }
       

    cout << "--\n";
    //ark.displayPopulationAxons(megaspecimens);
    cout << "--\n";
    //ark.displayPopulationAxons(gen2);
    ark.displayPopulationFitnesses(gen2);
    ark.displayPopulationFinalMembranes(gen2);

    cout << "START\n";
    vector<double> testIn = {0};
    ark.computeMembrane(gen2[0], testIn);
    gen2[0]->displayMembraneFinalLayer();
    testIn[0] = -1;
    ark.computeMembrane(gen2[0], testIn);
    gen2[0]->displayMembraneFinalLayer();
    testIn[0] = 0;
    ark.computeMembrane(gen2[0], testIn);
    gen2[0]->displayMembraneFinalLayer();
    testIn[0] = 1;
    ark.computeMembrane(gen2[0], testIn);
    gen2[0]->displayMembraneFinalLayer();
    testIn[0] = 2;
    ark.computeMembrane(gen2[0], testIn);
    gen2[0]->displayMembraneFinalLayer();
    testIn[0] = 3;
    ark.computeMembrane(gen2[0], testIn);
    gen2[0]->displayMembraneFinalLayer();
    gen2[0]->displayMembraneAxons();
    testIn[0] = 4;


    for (double i = -10; i < 10; i++){
        testIn[0] = i/2;
        ark.computeMembrane(gen2[0], testIn);
        double Y = gen2[0]->neuronLayerVec[2]->neuronVec[0]->activation;

        cout << "(" << i/2 << " , " << Y << ") ,";

    }

    // Add bias to activation or normalization so translation can occur

    return 0;
}


/*  Notes

    - Adding species restarts seems to help with falling into local minima.

    - Add elitism so backwards evolution does not occur

    -   There is an important trade study within the percent of 
        survivors passed on to a new generation. Less seems to
        avoid hitting a local minima in the gene pool population.
        There is almost an evolutionary momentum, and if a population
        surivives for too long with few deaths, they become homogenized
        and thus cannot evolve quickly when they do need to evolve.

    -   Scaling the mutation rate based on the axon weight scale shows
        promise in avoiding mutations being nullified by massively 
        weighted values.








*/



















