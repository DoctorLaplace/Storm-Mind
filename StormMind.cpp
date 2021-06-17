
#include <iostream>
#include "Neurogen.h"
#include "Legacy_Code\Thunder.h"
#include "StormMindTests.cpp"
#include <windows.h>
#include <stdio.h>          // printf, scanf, puts, NULL
#include <stdlib.h>         // srand, rand
#include <time.h>           // time
#include <random>
#include <string>
#include <iomanip>
#include <future>           // std::async, std::future

using namespace Neurogen;




int main(){
    // Seed randomosity for mutations
    std::srand(std::time(nullptr));

    // Create architect controller
    architect ark;


    // Set the neural shape of the network
    vector<int> nnShape = {2, 60, 1};

    // Create training inputs and desired outputs
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


    // Shape and create the initial specimens
    // Note sometimes the specimens crossbreed with themselves, resulting in non-diverse populations that fail to learn in training
    // Better initialization methods are required. Aim for true randomosity or a starting distribution of parameters
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

    // Create the initial population
    vector<membrane*> initPop = {&zyg, &wer, &gon};
    vector<membrane*> megaspecimens;

    // Train a fit membrane against training data.
    megaspecimens = ark.GEM(initPop, imprintSet, desiredSet);
    for (int i = 0; i < 30; i++){
        cout << "Generation " << i << ": ";
        megaspecimens = ark.GEM(megaspecimens, imprintSet, desiredSet, 0.8, 0.4);
    }
       

    // Output coordinates from the membrane test
    vector<double> testIn = {0};

    for (double i = -10; i < 10; i++){
        testIn[0] = i/2;
        ark.computeMembrane(megaspecimens[0], testIn);
        
        double Y = megaspecimens[0]->neuronLayerVec[2]->neuronVec[0]->activation;
        cout << "(" << i/2 << " , " << Y << ") ";
        if (i != 9){
            cout << ",";
        }
    }

    return 0;
}


/*  Notes

    - Adding species restarts seems to help with falling into local minima. Likely from more favorable random starting conditions.

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



















