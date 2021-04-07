
#ifndef THUNDER_H
#define THUNDER_H

#include <iostream>
#include <Vector>
#include <cmath>
#include <windows.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>


namespace Thunder{


    class Neuron {

        public:

            struct connection{
                Neuron* connectTarget = nullptr;
                double connectionWeight = 0;
            };

            void setActivity(double a){
                activity = a;
            }

            double getActivity(){
                return activity;
            }

            void addConnection(Neuron* target, double weight){
                connection* newCon = new connection;
                newCon->connectionWeight = weight;
                newCon->connectTarget = target;
                connectionVec.push_back(newCon);
            }

            void setConnectionTarget(int connectionIndex, Neuron* target){
                connectionVec[connectionIndex]->connectTarget = target;
            }

            void forwardPropagate(){
                for (size_t i = 0; i < connectionVec.size(); i++){
                    //std::cout << "Impulse " << activity*connectionVec[i]->connectionWeight << " sent to: " << connectionVec[i]->connectTarget << "\n";
                    connectionVec[i]->connectTarget->activity += activity*connectionVec[i]->connectionWeight;
                } 
            }

            void displayConnections(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 11);
                std::cout << "        Neuron: " << activity << std::endl;
                for (size_t i = 0; i < connectionVec.size(); i++){
                    SetConsoleTextAttribute(hConsole, 9);
                    std::cout << "            Connection " << i << std::endl;
                    std::cout << "                Target: " << connectionVec[i]->connectTarget << std::endl;
                    std::cout << "                Weight: " << connectionVec[i]->connectionWeight << "\n";           
                }
            }

            std::vector<connection*> getConnectionVec(){
                return connectionVec;
            }

            void replaceConnections(std::vector<connection*> newConnections){
                connectionVec = newConnections;
            }


        private:
            double activity = 0;

            std::vector<connection*> connectionVec;



    };



    class Layer {

        private:
            std::vector<Neuron*> layerVec;


        public:
            
            void addNeuronToLayer(Neuron *n){
                layerVec.push_back(n);
            }

            std::vector<Neuron*> getLayerVec(){
                return layerVec;
            }

            void forwardPropagateLayer(){
                for (size_t i = 0; i < layerVec.size(); i++){
                    layerVec[i]->forwardPropagate();
                }
            }

            void silenceLayerActivity(){
                for (size_t i = 0; i < layerVec.size(); i++){
                    layerVec[i]->setActivity(0);
                    //layerVec[i]->displayConnections();
                }
            }


            void displayLayer(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 10);
                std::cout << "    Layer: \n";
                for (size_t i = 0; i < layerVec.size(); i++){
                    layerVec[i]->displayConnections();
                }
                SetConsoleTextAttribute(hConsole, 15);

            }
        
    };



    class Membrane {
        private:

            std::vector<Layer*> membraneVec;


        public:
            void addLayerToMembrane(Layer *l){
                membraneVec.push_back(l);
            }

            std::vector<Layer*> getMembraneVec(){
                return membraneVec;
            }

            void setMembraneVec(std::vector<Layer*> newVec){
                membraneVec = newVec;
            }

            void forwardPropagateMembrane(){
                for (size_t i = 0; i < membraneVec.size(); i++){
                    membraneVec[i]->forwardPropagateLayer();
                }
            }

            void silenceMembrane(){
                for (size_t i = 0; i < membraneVec.size(); i++){
                    membraneVec[i]->silenceLayerActivity();
                }
            }


            void displayMembrane(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 13);
                std::cout << "Membrane: \n";
                for (size_t i = 0; i < membraneVec.size(); i++){
                    membraneVec[i]->displayLayer();
                }
                SetConsoleTextAttribute(hConsole, 15);
            }

    };



    class Evolver {

        private:
            Membrane* primeMembrane;
            Membrane* secondaryMembrane;


        public:

            void setPrimeMembrane(Membrane* prime){
                primeMembrane = prime;
            }

            void setSecondaryMembrane(Membrane* secondary){
                primeMembrane = secondary;
            }

            Neuron* geneCrossConnections(Neuron* n1, Neuron* n2, bool showProcess = false){
                std::vector<Thunder::Neuron::connection*> n1_connections = n1->getConnectionVec();
                std::vector<Thunder::Neuron::connection*> n2_connections = n2->getConnectionVec();
                Neuron* hybridNeuron = new Neuron;

                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                if (showProcess == true){
                    SetConsoleTextAttribute(hConsole, 11);
                    std::cout << "Performing neuron hybridization...  \n";
                    SetConsoleTextAttribute(hConsole, 15);
                }
                

                for (size_t i = 0; i < n1_connections.size(); i++){
                    Thunder::Neuron::connection*  newHybridConnection = new Thunder::Neuron::connection;

                    double n1ConWeight = n1_connections[i]->connectionWeight;
                    double n2ConWeight = n2_connections[i]->connectionWeight;
                    Neuron* n1ConTarget = nullptr; //n1_connections[i]->connectTarget;
                    Neuron* n2ConTarget = nullptr; //n2_connections[i]->connectTarget;
                    
                    // Random number between 1 and 100
                    double random_num = rand() % 100 + 1;
                    double random_weight = (rand() % 100 + 1) - 50;
                    random_weight = random_weight/100000;
                    //random_weight = 0;

                    SetConsoleTextAttribute(hConsole, 9);
                    if (random_num >= 50){
                        hybridNeuron->addConnection(n1ConTarget, n1ConWeight+random_weight);
                        if (showProcess == true){
                            std::cout << "Type-1" << std::endl;
                        }
                        
                    }else{
                        hybridNeuron->addConnection(n2ConTarget, n2ConWeight+random_weight);
                        if (showProcess == true){
                            std::cout << "Type-2" << std::endl;
                        }
                    }       
                    SetConsoleTextAttribute(hConsole, 15);
                }
                // Return the created randomized neuron;
                return hybridNeuron;
            } 

            Layer* geneCrossLayers(Layer* l1, Layer* l2, bool showProcess = false){
                std::vector<Neuron*> l1_neuron_vec = l1->getLayerVec();
                std::vector<Neuron*> l2_neuron_vec = l2->getLayerVec();
                if (showProcess == true){
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 10);
                    std::cout << "Performing layer hybridization...  Size-" << l1_neuron_vec.size() << "\n";
                    SetConsoleTextAttribute(hConsole, 15);
                }
                
                Layer* newHybridLayer = new Layer;
                for (size_t i = 0; i < l1_neuron_vec.size(); i++){
                    Neuron* newHybridNeuron = new Neuron;
                    newHybridNeuron = geneCrossConnections(l1_neuron_vec[i], l2_neuron_vec[i], showProcess);
                    newHybridLayer->addNeuronToLayer(newHybridNeuron);
                }

                return newHybridLayer;

            } 

            Membrane* geneCrossMembranes(Membrane* m1, Membrane* m2, bool showProcess = false){
                std::vector<Layer*> m1_layer_vec = m1->getMembraneVec();
                std::vector<Layer*> m2_layer_vec = m2->getMembraneVec();

                if (showProcess == true){
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 13);
                    std::cout << "Performing membrane hybridization...  Depth-" << m1_layer_vec.size() << "\n";
                    SetConsoleTextAttribute(hConsole, 15);
                }
                

                Membrane* newHybridMembrane = new Membrane;
                for (size_t i = 0; i < m1_layer_vec.size(); i++){
                    Layer* newHybridLayer = new Layer;
                    newHybridLayer = geneCrossLayers(m1_layer_vec[i], m2_layer_vec[i], showProcess);
                    newHybridMembrane->addLayerToMembrane(newHybridLayer);
                }

                return newHybridMembrane;
            }

            void formLayerToLayerConnections(Layer* l1, Layer* l2){
                for (size_t i = 0; i < l1->getLayerVec().size(); i++){
                    //std::cout << "   L-i:" << i << std::endl;
                    for (size_t k = 0; k < l2->getLayerVec().size(); k++){
                        //std::cout << "    L-k:" << k << std::endl;
                        l1->getLayerVec()[i]->setConnectionTarget(k, l2->getLayerVec()[k]);
                    }
                }
            }

            void formMembraneConnections(Membrane* m){
                std::vector<Layer*> membraneVec = m->getMembraneVec();
                //std::cout << membraneVec.size() << std::endl;
                for (size_t i = 0; i < membraneVec.size() - 1; i++){
                    //std::cout << i << std::endl;

                    formLayerToLayerConnections(membraneVec[i], membraneVec[i+1]);
                }
            }

            Membrane* produceHybrid(Membrane* m1, Membrane* m2){
                Membrane* newHybrid = new Membrane;
                newHybrid = geneCrossMembranes(m1, m2);
                formMembraneConnections(newHybrid);
                return newHybrid;
            }


            Membrane* produceMembrane(std::vector<int> membraneShape, double startingWeight){
                Membrane* newMembrane = new Membrane;

                for (int i = 0; i < membraneShape.size(); i++){
                   // std::cout << i << "Layer" << std::endl;
                    Layer* newLayer = new Layer;
                    newMembrane->addLayerToMembrane(newLayer);
                    for (int k = 0; k < membraneShape[i]; k++){
                        //std::cout << k << "Neuron" << std::endl;
                        Neuron* newNeuron = new Neuron;
                        newLayer->addNeuronToLayer(newNeuron);
                        // If not the last layer
                        if (i < membraneShape.size() - 1){
                            for (int j = 0; j < membraneShape[i+1]; j++){
                                //std::cout << j << "Connection" << std::endl;
                                newNeuron->addConnection(newNeuron, startingWeight);
                            }  
                        }
                    }
                }

                formMembraneConnections(newMembrane);

                return newMembrane;
            }

            void imprintInputs(std::vector<double> imprint, Membrane* m){
                Layer* inputLayer = m->getMembraneVec()[0];
                for (size_t i = 0; i < imprint.size(); i++){
                    double imprintActivity = imprint[i];
                    inputLayer->getLayerVec()[i]->setActivity(imprintActivity);
                }
            }

            std::vector<double> sampleOutputs(Membrane* m){
                int membraneSize = m->getMembraneVec().size();
                Layer* lastLayer = m->getMembraneVec()[membraneSize - 1];
                int layerSize = lastLayer->getLayerVec().size();
                std::vector<double> outputs;
                for (size_t i = 0; i < layerSize; i++){
                    outputs.push_back(lastLayer->getLayerVec()[i]->getActivity());
                }
                return outputs;
            }

            std::vector<double> comparePerformance(std::vector<double> desired, std::vector<double> actual){
                std::vector<double> performance;
                for (size_t i = 0; i < desired.size(); i++){
                    performance.push_back(abs(desired[i] - actual[i]));
                }
                return performance;
            }

            double scorePerformance(std::vector<double> performance){
                double score = 0;
                for (size_t i = 0; i < performance.size(); i++){
                    score += performance[i];
                }
                return score;
            }

            double evaluateMembraneFitness(Membrane* m, std::vector<double> input, std::vector<double> desiredOutput){
                m->silenceMembrane();
                imprintInputs(input, m);
                m->forwardPropagateMembrane();
                std::vector<double> membraneOutputs = sampleOutputs(m);
                std::vector<double> performance = comparePerformance(desiredOutput, membraneOutputs);
                double score = scorePerformance(performance);
                return score;
            }


            double multiEvaluateMembraneFitness(Membrane* m, std::vector<std::vector<double>> inputSet, std::vector<std::vector<double>> desiredOutputSet){
                double totalScore = 0;
                for (size_t i = 0; i < inputSet.size(); i++){
                    totalScore += evaluateMembraneFitness(m, inputSet[i], desiredOutputSet[i]);
                }
                return totalScore;
            }



            std::vector<Membrane*> produceMultiMembraneStrain(std::vector<Membrane*> geneticPopulation, int strainSize = 10){
                // Random number between 0 and geneticPopulation.size()
                double random_num1 = rand() % (geneticPopulation.size());
                double random_num2 = rand() % (geneticPopulation.size());
                std::vector<Membrane*> strain;
                for (size_t i = 0; i < strainSize; i++){
                    Membrane* newMembrane = produceHybrid(geneticPopulation[random_num1], geneticPopulation[random_num2]);
                    strain.push_back(newMembrane);
                }
                return strain;
            }



            std::vector<Membrane*> produceMembraneStrain(Membrane* m1, Membrane* m2, int strainSize = 10){
                std::vector<Membrane*> strain;
                for (size_t i = 0; i < strainSize; i++){
                    Membrane* newMembrane = produceHybrid(m1, m2);
                    strain.push_back(newMembrane);
                }
                return strain;
            }

            Membrane* selectStrongestMembrane(std::vector<Membrane*> strain, std::vector<double> input, std::vector<double> desiredOutput){
                int strongestMembraneIndex = 0;
                double strongestMembraneScore = evaluateMembraneFitness(strain[0], input, desiredOutput);
                double membraneScore = 0;
                for (size_t i = 0; i < strain.size(); i++){      
                    membraneScore = evaluateMembraneFitness(strain[i], input, desiredOutput);
                    //std::cout << membraneScore << std::endl;
                    if (membraneScore < strongestMembraneScore){
                        strongestMembraneScore = membraneScore;
                        strongestMembraneIndex = i;
                        //std::cout << "New fittest membrane..." << std::endl;
                    }
                }

                return strain[strongestMembraneIndex];
            }


            Membrane* evolveOptimalMembrane(std::vector<int> membraneShape, Membrane* m1, Membrane* m2, std::vector<double> input, std::vector<double> desiredOutput, int generationCount = 5, int strainSize = 20){
                Membrane* strongestSpecimen1 = m1;
                Membrane* strongestSpecimen2 = m2;
                
                for (size_t i = 0; i < generationCount; i++){
                    std::cout << "Generation " << i << "..." << std::endl;
                    std::vector<Membrane*> strain1 = produceMembraneStrain(strongestSpecimen1, strongestSpecimen2, strainSize);
                    
                    // double random_weight = (rand() % 100 + 1) - 50;
                    // random_weight = random_weight/100;
                    // Membrane* randomMembrane = produceMembrane(membraneShape, random_weight);

                    std::vector<Membrane*> strain2 = produceMembraneStrain(strongestSpecimen1, strongestSpecimen2, strainSize);
                    strain1.push_back(strongestSpecimen1);
                    strain2.push_back(strongestSpecimen2);

                    strongestSpecimen1 = selectStrongestMembrane(strain1, input, desiredOutput);
                    strongestSpecimen2 = selectStrongestMembrane(strain2, input, desiredOutput);
                    std::cout << "    -Performance: " << scorePerformance(comparePerformance(desiredOutput,sampleOutputs(strongestSpecimen1))) << std::endl;
                }

                return strongestSpecimen1;
            }



    };




    class Cybernetic{
        private:
            // Private
        public:
            double value = 0;


            void reduceErrorToThreshold(double threshold, double desiredValue, double dampening){
                std::cout << "Running error reducer...\n" << std::endl;
                int count = 0;
                double error = fabs(desiredValue - value);
                while (error > threshold){
                    count += 1;
                    //std::cout << error << " > " << threshold << std::endl;
                    //std::cout << desiredValue << " - " << value << " = " << desiredValue - value << std::endl;

                    value += (desiredValue - value)*dampening;
                    error = fabs(desiredValue - value);

                    std::cout << value << std::endl << std::endl;
                }
                std::cout << "Iterations to solve: " << count << "\n\n";

            }



    };




}




#endif
