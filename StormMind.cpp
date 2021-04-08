


#include <iostream>
#include "Thunder.h"
#include <windows.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>
#include <string>

using namespace std; using namespace Thunder;


void testXORMembrane(Membrane* m){
    Evolver membraneController;
    string userInput;
    double in1, in2;
    while (userInput != "q"){
        
            cout << "N1: ";
            cin >> userInput;
            if (userInput != "q"){
                in1 = stoi(userInput);
                cout << "N2: ";
                cin >> userInput;
                if (userInput != "q"){
                    in2 = stoi(userInput);
                }
            }
            
            if (userInput != "q"){
                m->silenceMembrane();
                membraneController.imprintInputs({in1, in2, 1},m);
                m->forwardPropagateMembrane();
                m->displayFinalLayer();
                if (membraneController.sampleOutputs(m)[0] >= 0.5){
                    cout << "First Neuron Activated\n";
                }else{
                    cout << "First Neuron Silent\n";
                }
            }
            
    }
}


void displayTTTBoard(vector<vector<int>> gameBoard){
    for (int x = 0; x < gameBoard.size(); x++){
        cout << "  ";
        for (int y = 0; y < gameBoard[x].size(); y++){
            cout << gameBoard[x][y] << " ";
        }
        cout << endl;
    }
}

int gameFinished(vector<vector<int>> gameBoard){
    int playerMark = 1;
    cout << "Checking for winner...\n";

    playerMark = 1;

    // Check if player 1 wins
    if (gameBoard[0][0] == playerMark && gameBoard[1][0] == playerMark && gameBoard[2][0] == playerMark){
        cout << "Player 1 Wins!\n";
        return 1;
    }
    if (gameBoard[0][1] == playerMark && gameBoard[1][1] == playerMark && gameBoard[2][1] == playerMark){
        cout << "Player 1 Wins!\n";
        return 1;
    }
    if (gameBoard[0][2] == playerMark && gameBoard[1][2] == playerMark && gameBoard[2][2] == playerMark){
        cout << "Player 1 Wins!\n";
        return 1;
    }
    if (gameBoard[0][0] == playerMark && gameBoard[1][1] == playerMark && gameBoard[2][2] == playerMark){
        cout << "Player 1 Wins!\n";
        return 1;
    }
    if (gameBoard[2][0] == playerMark && gameBoard[1][1] == playerMark && gameBoard[0][2] == playerMark){
        cout << "Player 1 Wins!\n";
        return 1;
    }


    playerMark = 2;

    // Check if player 1 wins
    if (gameBoard[0][0] == playerMark && gameBoard[1][0] == playerMark && gameBoard[2][0] == playerMark){
        cout << "Player 2 Wins!\n";
        return 2;
    }
    if (gameBoard[0][1] == playerMark && gameBoard[1][1] == playerMark && gameBoard[2][1] == playerMark){
        cout << "Player 2 Wins!\n";
        return 2;
    }
    if (gameBoard[0][2] == playerMark && gameBoard[1][2] == playerMark && gameBoard[2][2] == playerMark){
        cout << "Player 2 Wins!\n";
        return 2;
    }
    if (gameBoard[0][0] == playerMark && gameBoard[1][1] == playerMark && gameBoard[2][2] == playerMark){
        cout << "Player 2 Wins!\n";
        return 2;
    }
    if (gameBoard[2][0] == playerMark && gameBoard[1][1] == playerMark && gameBoard[0][2] == playerMark){
        cout << "Player 2 Wins!\n";
        return 2;
    }


    return 0;
}

int playTicTacToe(){

    cout << "Beginning Game...\n";
    string userInput = "";
    bool playerTurn = 0;
    int gameover = 0, validMove = false;

    vector<int> c1 = {0, 0, 0};
    vector<int> c2 = {0, 0, 0};
    vector<int> c3 = {0, 0, 0};
    vector<vector<int>> gameBoard = {c3, c2, c1};

    int x, y;

    while (gameover == 0){
        if (playerTurn == 0 && gameover == 0 && gameover != 2){
            cout << "Player 1's Turn...\n";
            while (validMove == false){
                cout << "X: ";
                cin >> userInput;
                x = stoi(userInput) - 1;
                cout << "Y: ";
                cin >> userInput;
                y = stoi(userInput) - 1;

                if (gameBoard[y][x] == 0){
                    gameBoard[y][x] = 1;
                    validMove = true;
                    playerTurn = 1;
                }else{
                    cout << "Invalid Move...\n";
                    validMove = false;
                }
            }
        }

        displayTTTBoard(gameBoard);
        gameover = gameFinished(gameBoard);
        validMove = false;


        if (playerTurn == 1 && gameover == 0 && gameover != 1){
            cout << "Player 2's Turn...\n";
            while (validMove == false){
                cout << "X: ";
                cin >> userInput;
                x = stoi(userInput) - 1;
                cout << "Y: ";
                cin >> userInput;
                y = stoi(userInput) - 1;

                if (gameBoard[y][x] == 0){
                    gameBoard[y][x] = 2;
                    validMove = true;
                    playerTurn = 0;
                }else{
                    cout << "Invalid Move...\n";
                    validMove = false;
                }
            }
        }

        displayTTTBoard(gameBoard);
        gameover = gameFinished(gameBoard);
        validMove = false;

    }

    return gameover;

}



int main(){
    srand(time(NULL));

    cout << playTicTacToe() << endl;
    string a;
    cin >> a;

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

    strongestSpecimen = zurel.evolveOptimalMembraneMulti(shapeA, population, inSet, desiredSet, 35, 100, 5, 0.001);
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


    testXORMembrane(strongestSpecimen);


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