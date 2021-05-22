
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


    vector<int> nnShape = {3, 8, 8, 4};
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

    membrane* vera = ark.evolveSupervised(&everus, imprintSet, desiredSet, 0.5, 5, 100);

    ark.computeMembrane(vera, imp1);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp2);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp3);
    vera->displayMembrane();
    ark.computeMembrane(vera, imp4);
    vera->displayMembrane();

    cout << "=========NEXT MEM========\n\n";

    membrane zyg, wer, gon, zygwer;
    zyg.createDense(nnShape);
    zyg.setAllAxonWeights(1);
    wer.createDense(nnShape);
    wer.setAllAxonWeights(0);
    gon.createDense(nnShape);
    gon.setAllAxonWeights(-1);
    zygwer.createDense(nnShape);
    zygwer.copyGeneCrossAxonWeights(&zyg, &wer);
    zygwer.copyGeneCrossAxonWeights(&zygwer, &gon);
    zygwer.mutatePartOfAxonWeights(0.1, 0.1);
    zygwer.displayMembraneAxons();


    //membrane* arev = ark.evolveSupervised(&everus, imprintSet, desiredSet, 0.5, 10, 10);

    //membrane* alpheon = ark.SEAR(&everus, imprintSet,  desiredSet, 0.9, 40, 100, 0.1, 8);

    //ark.computeMembrane(alpheon, imp1);
    //alpheon->displayMembraneFinalLayer();

    // NN seems to get caught in a local minimum quite often on XOR test.
    // genetic cross over would help with this issue!



    return 0;
}


/*  Notes

    - Adding species restarts seems to help with falling into local minima.














*/



















