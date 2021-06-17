#pragma once
#include <iostream>
#include "Neurogen.h"
#include "Thunder.h"
#include <windows.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>
#include <string>

using namespace std; 
using namespace Thunder;
using namespace Neurogen;



// Requires a neuron with at least 2 inputs, and 1 output neuron
// Recommended shape is 3>3>1 
void testXORMembrane(Membrane* m){

    // Code used to generate a successful membrane

    // Evolver zurel;
    // std::vector<int> shapeA = {3, 3, 1};

    // //cout << "Minrae:\n";
    // Membrane* minrae = zurel.produceMembrane(shapeA, 1);
    // //cout << "Arkath:\n";
    // Membrane* arkath = zurel.produceMembrane(shapeA, 0);
    // //cout << "Lemrox:\n";
    // Membrane* lemrox = zurel.produceMembrane(shapeA, 0.5);

    // // XOR training data
    // std::vector<double> input1 = { 0, 0, 1};
    // std::vector<double> desired1 = {0};
    // std::vector<double> input2 = { 1, 0, 1};
    // std::vector<double> desired2 = {1};
    // std::vector<double> input3 = { 0, 1, 1};
    // std::vector<double> desired3 = {1};
    // std::vector<double> input4 = { 1, 1, 1};
    // std::vector<double> desired4 = {0};

    // std::vector<std::vector<double>> inSet = {input1, input2, input3, input4};
    // std::vector<std::vector<double>> desiredSet = {desired1, desired2, desired3, desired4};

    // vector<Membrane*> population = {lemrox, minrae, arkath};
    // cout << "Evolving Membrane..." << endl;
    // Membrane* strongestSpecimen = zurel.evolveOptimalMembraneMulti(shapeA, population, inSet, desiredSet, 100, 100, 3, 0.0004);
    
    // cout << "Strongest Membrane has been found..." << endl;
    // strongestSpecimen->silenceMembrane();
    // strongestSpecimen->displayMembrane();
    // cout << "Total Performance: ";
    // cout << zurel.multiEvaluateMembraneFitness(strongestSpecimen, inSet, desiredSet) << endl;



    cout << "Testing neuron as an XOR Gate...\n";
    Evolver membraneController;
    string userInput;
    double in1, in2;
    while (userInput != "q"){  
            cout << "First Input (0 or 1): ";
            cin >> userInput;
            if (userInput == "0" || userInput == "1"){
                in1 = stoi(userInput);
                cout << "Second Input (0 or 1): ";
                cin >> userInput;
                if (userInput == "0" || userInput == "1"){
                    in2 = stoi(userInput);
                }else{
                    cout << "Ending XOR Test...\n";
                    return;
                }
            }else{
                cout << "Ending XOR Test...\n";
                return;
            }
            
            if (userInput == "0" || userInput == "1"){
                m->silenceMembrane();
                membraneController.imprintInputs({in1, in2, 1},m);
                m->forwardPropagateMembrane();
                m->displayFinalLayer();
                if (membraneController.sampleOutputs(m)[0] >= 0.5){
                    cout << "Neural XOR Output: 1\n";
                }else{
                    cout << "Neural XOR Output: 0\n";
                }
            }
    }
}

void displayTTTBoard(vector<vector<double>> gameBoard){
    for (int x = 0; x < gameBoard.size(); x++){
        cout << "  ";
        for (int y = 0; y < gameBoard[x].size(); y++){
            cout << gameBoard[x][y] << " ";
        }
        cout << endl;
    }
}

int gameFinished(vector<vector<double>> gameBoard, double &score){
    int playerMark = 1;
    cout << "Checking for winner...\n";

    playerMark = 0.3;

    // Check if player 1 wins
    if (gameBoard[0][0] == playerMark && gameBoard[1][0] == playerMark && gameBoard[2][0] == playerMark){
        cout << "Player 1 Wins!\n";
        score += -1;
        return 1;
    }
    if (gameBoard[0][1] == playerMark && gameBoard[1][1] == playerMark && gameBoard[2][1] == playerMark){
        cout << "Player 1 Wins!\n";
        score += -1;
        return 1;
    }
    if (gameBoard[0][2] == playerMark && gameBoard[1][2] == playerMark && gameBoard[2][2] == playerMark){
        cout << "Player 1 Wins!\n";
        score += -1;
        return 1;
    }
    if (gameBoard[0][0] == playerMark && gameBoard[1][1] == playerMark && gameBoard[2][2] == playerMark){
        cout << "Player 1 Wins!\n";
        score += -1;
        return 1;
    }
    if (gameBoard[2][0] == playerMark && gameBoard[1][1] == playerMark && gameBoard[0][2] == playerMark){
        cout << "Player 1 Wins!\n";
        score += -1;
        return 1;
    }


    playerMark = 0.6;

    // Check if player 1 wins
    if (gameBoard[0][0] == playerMark && gameBoard[1][0] == playerMark && gameBoard[2][0] == playerMark){
        cout << "Player 2 Wins!\n";
        score += 1;
        return 2;
    }
    if (gameBoard[0][1] == playerMark && gameBoard[1][1] == playerMark && gameBoard[2][1] == playerMark){
        cout << "Player 2 Wins!\n";
        score += 1;
        return 2;
    }
    if (gameBoard[0][2] == playerMark && gameBoard[1][2] == playerMark && gameBoard[2][2] == playerMark){
        cout << "Player 2 Wins!\n";
        score += 1;
        return 2;
    }
    if (gameBoard[0][0] == playerMark && gameBoard[1][1] == playerMark && gameBoard[2][2] == playerMark){
        cout << "Player 2 Wins!\n";
        score += 1;
        return 2;
    }
    if (gameBoard[2][0] == playerMark && gameBoard[1][1] == playerMark && gameBoard[0][2] == playerMark){
        cout << "Player 2 Wins!\n";
        score += 1;
        return 2;
    }


    return 0;
}

// Human vs AI
int playTicTacToe(Membrane* agent, double &gameScore){

    cout << "Beginning Game...\n";
    Evolver membraneController;
    double membraneScore = 0;

    string userInput = "";
    bool playerTurn = 0;
    int gameover = 0, validMove = false;

    vector<double> c1 = {0, 0, 0};
    vector<double> c2 = {0, 0, 0};
    vector<double> c3 = {0, 0, 0};
    vector<vector<double>> gameBoard = {c3, c2, c1};

    int x, y;

    while (gameover == 0){
        displayTTTBoard(gameBoard);
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
        cout << "MARK\n";

        displayTTTBoard(gameBoard);
        gameover = gameFinished(gameBoard, membraneScore);
        validMove = false;


        if (playerTurn == 1 && gameover == 0 && gameover != 1){
            cout << "Player 2's Turn...\n";
            while (validMove == false){

                std::vector<double> gameMap;
                for (int i = 0; i < gameBoard.size(); i++){
                    for (int k = 0; k < gameBoard.size(); k++){
                        gameMap.push_back(gameBoard[i][k]);
                        cout << gameBoard[i][k] << " ";
                    }
                    cout << endl;
                }

                agent->silenceMembrane();
                membraneController.imprintInputs(gameMap, agent);
                agent->forwardPropagateMembrane();
                int positionNeuron = findLargetsIndex(membraneController.sampleOutputs(agent));
                
                agent->displayFinalLayer();
                
                if (positionNeuron == 0){
                    x = 0;
                    y = 0;
                }
                if (positionNeuron == 1){
                    x = 1;
                    y = 0;
                }
                if (positionNeuron == 2){
                    x = 2;
                    y = 0;
                }
                if (positionNeuron == 3){
                    x = 1;
                    y = 0;
                }
                if (positionNeuron == 4){
                    x = 1;
                    y = 1;
                }
                if (positionNeuron == 5){
                    x = 1;
                    y = 2;
                }
                if (positionNeuron == 6){
                    x = 2;
                    y = 0;
                }
                if (positionNeuron == 7){
                    x = 2;
                    y = 1;
                }
                if (positionNeuron == 8){
                    x = 2;
                    y = 2;
                }

                // Manual Controls
                // cout << "X: ";
                // cin >> userInput;
                // x = stoi(userInput) - 1;
                // cout << "Y: ";
                // cin >> userInput;
                // y = stoi(userInput) - 1;

                if (gameBoard[x][y] == 0){
                    gameBoard[x][y] = 0.5;
                    validMove = true;
                    membraneScore += 0.25;
                    playerTurn = 0;
                }else{
                    cout << "Invalid Move...\n";
                    membraneScore += -1;
                    validMove = false;
                    cout << "Membrane Reset\n";
                    gameScore = membraneScore;
                    return -10;
                }
            }
        }

        displayTTTBoard(gameBoard);
        gameover = gameFinished(gameBoard, membraneScore);
        validMove = false;

    }

    cout << "GG: " << membraneScore << endl;
    gameScore = membraneScore;
    return gameover;

}

// AI vs AI
Membrane* playTicTacToeAI(Membrane* agent1, Membrane* agent2, double &agent1Score, double &agent2Score){

    cout << "Beginning AI Game...\n";
    Evolver membraneController;

    bool playerTurn = 2;
    int gameover = 0;

    vector<double> c1 = {0, 0, 0};
    vector<double> c2 = {0, 0, 0};
    vector<double> c3 = {0, 0, 0};
    vector<vector<double>> gameBoard = {c3, c2, c1};
    int x, y;
    std::vector<double> lastGameMap;

    while (gameover == false){
        

        if (playerTurn == 1 && gameover == false){  
            cout << "AI 1's Turn...\n";
            std::vector<double> gameMap;
            for (int i = 0; i < gameBoard.size(); i++){
                for (int k = 0; k < gameBoard.size(); k++){
                    gameMap.push_back(gameBoard[i][k]);
                    cout << gameBoard[i][k] << " ";
                }
                cout << endl;
            }

            agent1->silenceMembrane();
            membraneController.imprintInputs(gameMap, agent1);
            agent1->forwardPropagateMembrane();
            int positionNeuron = findLargetsIndex(membraneController.sampleOutputs(agent1));     
            agent1->displayFinalLayer();
            
            if (positionNeuron == 0){
                x = 0;
                y = 0;
            }
            if (positionNeuron == 1){
                x = 1;
                y = 0;
            }
            if (positionNeuron == 2){
                x = 2;
                y = 0;
            }
            if (positionNeuron == 3){
                x = 1;
                y = 0;
            }
            if (positionNeuron == 4){
                x = 1;
                y = 1;
            }
            if (positionNeuron == 5){
                x = 1;
                y = 2;
            }
            if (positionNeuron == 6){
                x = 2;
                y = 0;
            }
            if (positionNeuron == 7){
                x = 2;
                y = 1;
            }
            if (positionNeuron == 8){
                x = 2;
                y = 2;
            }
            
            
            if (gameBoard[1][1] == 0.3){
                agent1Score += 999;
                gameover = true;
            }


            if (gameBoard[x][y] == 0){
                cout << "Good Move...\n";
                gameBoard[x][y] = 0.3;
                agent1Score += 0.25;
                cout << "AI 1: " << agent1Score << endl;
                cout << "AI 2: " << agent2Score << endl << endl;
            }else{
                cout << "Invalid Move...\n";
                agent1Score += -0.125;
                cout << "AI 1: " << agent1Score << endl;
                cout << "AI 2: " << agent2Score << endl << endl;
            }
            
            



        }

        if (playerTurn == 1 && gameover == false){  
            cout << "AI 2's Turn...\n";
            std::vector<double> gameMap;
            for (int i = 0; i < gameBoard.size(); i++){
                for (int k = 0; k < gameBoard.size(); k++){
                    gameMap.push_back(gameBoard[i][k]);
                    cout << gameBoard[i][k] << " ";
                }
                cout << endl;
            }

            agent2->silenceMembrane();
            membraneController.imprintInputs(gameMap, agent2);
            agent2->forwardPropagateMembrane();
            int positionNeuron = findLargetsIndex(membraneController.sampleOutputs(agent2));     
            agent2->displayFinalLayer();
            
            if (positionNeuron == 0){
                x = 0;
                y = 0;
            }
            if (positionNeuron == 1){
                x = 1;
                y = 0;
            }
            if (positionNeuron == 2){
                x = 2;
                y = 0;
            }
            if (positionNeuron == 3){
                x = 1;
                y = 0;
            }
            if (positionNeuron == 4){
                x = 1;
                y = 1;
            }
            if (positionNeuron == 5){
                x = 1;
                y = 2;
            }
            if (positionNeuron == 6){
                x = 2;
                y = 0;
            }
            if (positionNeuron == 7){
                x = 2;
                y = 1;
            }
            if (positionNeuron == 8){
                x = 2;
                y = 2;
            }

            if (gameBoard[x][y] == 0){
                cout << "Good Move...\n";
                gameBoard[x][y] = 0.6;
                agent2Score += 0.25;
                cout << "AI 1: " << agent1Score << endl;
                cout << "AI 2: " << agent2Score << endl << endl;
            }else{
                cout << "Invalid Move...\n";
                agent2Score += -0.125;
                cout << "AI 1: " << agent1Score << endl;
                cout << "AI 2: " << agent2Score << endl << endl;
            }
            
        }
        
        if (agent1Score < 0 || agent2Score < 0){
            cout << "Failed Membrane...\n";
            gameover = true;
        }




    }

    


    cout << "AI Game Ended...\n";
    cout << "AI 1: " << agent1Score << endl;
    cout << "AI 2: " << agent2Score << endl << endl;
    if (agent1Score >= agent2Score){
        cout << "AI 1 is victorious...\n";
        return agent1;
    }else{        
        cout << "AI 2 is victorious...\n";
        return agent2;
    }
}

// Showing supervised learning
void evolveSoloTest(){


    Evolver zurel;
    std::vector<int> shapeA = {10, 12, 9};



    //cout << "Minrae:\n";
    Membrane* minrae = zurel.produceMembrane(shapeA, 1);
    //cout << "Arkath:\n";
    Membrane* arkath = zurel.produceMembrane(shapeA, 0);
    //cout << "Lemrox:\n";
    Membrane* lemrox = zurel.produceMembrane(shapeA, 0.5);

    // double performance = 0;
    // playTicTacToe(minrae, performance);
    // cout << "Performance: " << performance << endl;
    // cin >> performance;

    Membrane* strongestSpecimen, *competitorSpecimen;


    std::vector<double> imp = { 0, 0, 0,
                                0, 0, 0,
                                0, 0, 0,
                                1};
    std::vector<double> desired = { 0, 0, 0,
                                    0, 1, 0,
                                    0, 0, 0};

    std::vector<double> imp2 = { 0, 0, 0,
                                 0, 1, 0.5,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired2 = { 0, 0, 0,
                                     0, 0, 0,
                                     0, 0, 1};


    std::vector<double> imp11 = { 0, 0, 0,
                                  0, 1, 0,
                                  0, 0, 0,
                                1};
    std::vector<double> desired11 = { 0, 0, 0,
                                      0, 0, 0.5,
                                      0, 0, 0};

    std::vector<double> imp22 = { 0, 0, 0,
                                  0, 1, 0.5,
                                  0, 0, 1,
                                 1};
    std::vector<double> desired22 = { 0.5, 0, 0,
                                      0, 0, 0,
                                      0, 0, 0};



    std::vector<std::vector<double>> inSet = {imp, imp2/*, imp3, imp4, imp5, imp6, imp7, imp8, imp9*/};
    std::vector<std::vector<double>> desiredSet = {desired, desired2/*, desired3, desired4, desired5, desired6, desired7, desired8, desired9*/};
    std::vector<std::vector<double>> inSet2 = {imp11, imp22/*, imp3, imp4, imp5, imp6, imp7, imp8, imp9*/};
    std::vector<std::vector<double>> desiredSet2 = {desired11, desired22/*, desired3, desired4, desired5, desired6, desired7, desired8, desired9*/};

    vector<Membrane*> population = {lemrox, minrae, arkath};
    cout << "Evolving Membrane..." << endl;

    strongestSpecimen = zurel.evolveOptimalMembraneMulti(shapeA, population, inSet, desiredSet, 50, 4, 2, 0.0005);
    competitorSpecimen = zurel.evolveOptimalMembraneMulti(shapeA, population, inSet2, desiredSet2, 50, 4, 2, 0.0005);
    cout << "Strongest Membrane has been found..." << endl;

    //strongestSpecimen->displayMembrane();
    cout << "Total Performance: ";
    cout << zurel.multiEvaluateMembraneFitness(strongestSpecimen, inSet, desiredSet) << endl;
    
    // strongestSpecimen->silenceMembrane();
    // zurel.imprintInputs(imp, strongestSpecimen);
    // strongestSpecimen->forwardPropagateMembrane();
    // strongestSpecimen->displayFinalLayer();



}

void testAsync(){
    runtimeUniverse universe, mara;

    std::future<void> fut2 = std::async(runtimeUniverse::ticker, &mara);
    std::future<void> fut3 = std::async(runtimeUniverse::session, &mara);

    fut2.get();
    fut3.get();
}



int old_main(){
    

    srand(time(NULL));


    Evolver zurel;


    std::vector<int> shapeA = {10, 56, 9};

    //cout << "Minrae:\n";
    Membrane* minrae = zurel.produceMembrane(shapeA, 1);
    //cout << "Arkath:\n";
    Membrane* arkath = zurel.produceMembrane(shapeA, 0);
    //cout << "Lemrox:\n";
    Membrane* lemrox = zurel.produceMembrane(shapeA, 0.5);

    // double performance = 0;
    // playTicTacToe(minrae, performance);
    // cout << "Performance: " << performance << endl;
    // cin >> performance;

    Membrane* strongestSpecimen, *competitorSpecimen;


    std::vector<double> imp = { 1, 0, 0,
                                0, 0, 0,
                                0, 0, 0,
                                1};
    std::vector<double> desired = { 0, 0, 1,
                                    0, 0, 0,
                                    0, 0, 0};

    std::vector<double> imp2 = { 0, 0, 1,
                                 0, 0, 0,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired2 = { 0, 0, 0,
                                     0, 0, 0,
                                     0, 0, 1};
    std::vector<double> imp3 = { 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 1,
                                 1};
    std::vector<double> desired3 = { 0, 0, 0,
                                     0, 0, 0,
                                     1, 0, 0};
    std::vector<double> imp4 = { 0, 0, 0,
                                 0, 0, 0,
                                 1, 0, 0,
                                 1};
    std::vector<double> desired4 = { 1, 0, 0,
                                     0, 0, 0,
                                     0, 0, 0};
    std::vector<double> imp5 = { 0, 1, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired5 = { 0, 0, 0,
                                     0, 0, 1,
                                     0, 0, 0};
    std::vector<double> imp6 = { 0, 0, 0,
                                 0, 0, 1,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired6 = { 0, 0, 0,
                                     0, 0, 0,
                                     0, 1, 0};
    std::vector<double> imp7 = { 0, 0, 0,
                                 0, 0, 0,
                                 0, 1, 0,
                                 1};
    std::vector<double> desired7 = { 0, 0, 0,
                                     1, 0, 0,
                                     0, 0, 0};
    std::vector<double> imp8 = { 0, 0, 0,
                                 1, 0, 0,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired8 = { 0, 1, 0,
                                     0, 0, 0,
                                     0, 0, 0};
    std::vector<double> imp9 = { 0, 0, 0,
                                 0, 1, 0,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired9 = { 0, 0, 0,
                                     0, 1, 0,
                                     0, 0, 0};
    std::vector<double> imp10 = { 0, 1, 1,
                                 0, 0, 0,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired10 = { 0, 0, 0,
                                     0, 0, 1,
                                     0, 0, 1};
    std::vector<double> imp11 = { 0, 0, 0,
                                 0, 0, 1,
                                 0, 0, 1,
                                 1};
    std::vector<double> desired11 = { 0, 0, 0,
                                     0, 0, 0,
                                     1, 1, 0};
    std::vector<double> imp12 = { 0, 0, 0,
                                 0, 0, 0,
                                 1, 1, 0,
                                 1};
    std::vector<double> desired12 = { 1, 0, 0,
                                     1, 0, 0,
                                     0, 0, 0};
    std::vector<double> imp13 = { 1, 0, 0,
                                 1, 0, 0,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired13 = { 0, 1, 1,
                                     0, 0, 0,
                                     0, 0, 0};
    std::vector<double> imp14 = { 0, 1, 0,
                                 1, 0, 1,
                                 0, 0, 0,
                                 1};
    std::vector<double> desired14 = { 0, 1, 0,
                                      0, 0, 1,
                                      0, 1, 0};
    std::vector<double> imp15 = { 0, 1, 0,
                                  0, 0, 1,
                                  0, 0, 0,
                                  1};
    std::vector<double> imp16 = { 1, 1, 1,
                                  0, 0, 1,
                                  0, 0, 1,
                                  1};




    std::vector<std::vector<double>> inSet = {imp, imp2, imp3, imp4, imp5, imp6, imp7, imp8, imp9, imp10, imp11, imp12, imp13, imp14};
    std::vector<std::vector<double>> desiredSet = {desired, desired2, desired3, desired4, desired5, desired6, desired7, desired8, desired9, desired10, desired11, desired12, desired13, desired14};
    // std::vector<std::vector<double>> inSet2 = {imp11, imp22/*, imp3, imp4, imp5, imp6, imp7, imp8, imp9*/};
    // std::vector<std::vector<double>> desiredSet2 = {desired11, desired22/*, desired3, desired4, desired5, desired6, desired7, desired8, desired9*/};

    vector<Membrane*> population = {lemrox, minrae, arkath};
    cout << "Evolving Membrane..." << endl;

    strongestSpecimen = zurel.evolveOptimalMembraneMulti(shapeA, population, inSet, desiredSet, 200, 4, 2, 0.0005);
    // competitorSpecimen = zurel.evolveOptimalMembraneMulti(shapeA, population, inSet2, desiredSet2, 50, 4, 2, 0.0005);
    cout << "Strongest Membrane has been found..." << endl;

    //strongestSpecimen->displayMembrane();
    cout << "Total Performance: ";
    cout << zurel.multiEvaluateMembraneFitness(strongestSpecimen, inSet, desiredSet) << endl;
    
    strongestSpecimen->silenceMembrane();
    zurel.imprintInputs(imp, strongestSpecimen);
    strongestSpecimen->forwardPropagateMembrane();
    strongestSpecimen->displayFinalLayer();

    strongestSpecimen->silenceMembrane();
    zurel.imprintInputs(imp15, strongestSpecimen);
    strongestSpecimen->forwardPropagateMembrane();
    strongestSpecimen->displayFinalLayer();

    strongestSpecimen->silenceMembrane();
    zurel.imprintInputs(imp16, strongestSpecimen);
    strongestSpecimen->forwardPropagateMembrane();
    strongestSpecimen->displayFinalLayer();


    return 0;
}

