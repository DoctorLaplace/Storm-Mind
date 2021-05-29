
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

    cout << "=================\n\n";

    architect ark;


    membrane everus;
    everus.name = "Everus";


    vector<int> nnShape = {5, 8, 4};
    vector<double> imp1 = {1, 0, 0, 0, 1};
    vector<double> imp2 = {0, 1, 0, 0, 1};
    vector<double> imp3 = {0, 0, 1, 0, 1};
    vector<double> imp4 = {0, 0, 0, 1, 1};
    vector<double> des1 = {0, 1, 0, 0};
    vector<double> des2 = {0, 0, 1, 0};
    vector<double> des3 = {0, 0, 0, 1};
    vector<double> des4 = {1, 0, 0, 0};
    vector<vector<double>> imprintSet = {imp1, imp2, imp3, imp4};
    vector<vector<double>> desiredSet = {des1, des2, des3, des4};



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
    wer.createDense(nnShape);
    wer.setAllAxonWeights(0);
    gon.createDense(nnShape);
    gon.setAllAxonWeights(-1);
    zygwergon.createDense(nnShape);
    zygwergon.copyGeneCrossAxonWeights(&zyg, &wer);
    zygwergon.copyGeneCrossAxonWeights(&zygwergon, &gon);
    zygwergon.mutatePartOfAxonWeights(0.1, 0.1);
    //zygwergon.displayMembraneAxons();


    vector<membrane*> initPop = {&zyg, &wer, &gon};
    vector<membrane*> megaspecimens, gen2;
    
    //ark.displayPopulationAxons(initPop);
    megaspecimens = ark.GEM(initPop, imprintSet, desiredSet);
    gen2 = ark.GEM(megaspecimens, imprintSet, desiredSet);
    for (int i = 0; i < 100; i++)
        gen2 = ark.GEM(gen2, imprintSet, desiredSet);

    cout << "--\n";
    //ark.displayPopulationAxons(megaspecimens);
    cout << "--\n";
    //ark.displayPopulationAxons(gen2);
    ark.displayPopulationFitnesses(gen2);


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










*/



















