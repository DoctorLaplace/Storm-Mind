
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

        void forwardPropagate(){
            for (size_t i = 0; i < connectionVec.size(); i++){
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

        void forwardPropagateMembrane(){
            for (size_t i = 0; i < membraneVec.size(); i++){
                membraneVec[i]->forwardPropagateLayer();
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

        Neuron* geneCrossConnections(Neuron* n1, Neuron* n2){
            std::vector<Thunder::Neuron::connection*> n1_connections = n1->getConnectionVec();
            std::vector<Thunder::Neuron::connection*> n2_connections = n2->getConnectionVec();

            Neuron* hybridNeuron = new Neuron;

            for (int i = 0; i < n1_connections.size(); i++){
                Thunder::Neuron::connection*  newHybridConnection = new Thunder::Neuron::connection;

                double n1ConWeight = n1_connections[i]->connectionWeight;
                double n2ConWeight = n2_connections[i]->connectionWeight;
                Neuron* n1ConTarget = n1_connections[i]->connectTarget;
                Neuron* n2ConTarget = n2_connections[i]->connectTarget;
                
                double random_num = rand() % 100 + 1;

                // Random number between 1 and 100
                double random_weight = (rand() % 100 + 1);
                random_weight = random_weight/10000;
                random_weight = 0;

                if (random_num >= 50){
                    hybridNeuron->addConnection(n1ConTarget, n1ConWeight+random_weight);
                    std::cout << "Chosen Parent: 1" << std::endl;
                }else{
                    hybridNeuron->addConnection(n2ConTarget, n2ConWeight+random_weight);
                    std::cout << "Chosen Parent: 2" << std::endl;
                }       
            }
            // Return the created randomized neuron;
            return hybridNeuron;
        } 

        Layer* geneCrossLayers(Layer* l1, Layer* l2){
            std::vector<Neuron*> l1_neuron_vec = l1->getLayerVec();
            std::vector<Neuron*> l2_neuron_vec = l2->getLayerVec();
            std::cout << "Layer Size: " << l1->getLayerVec().size() << "\n";

            Layer* newHybridLayer = new Layer;
            for (size_t i = 0; i < l1_neuron_vec.size(); i++){
                Neuron* newHybridNeuron = new Neuron;
                newHybridNeuron = geneCrossConnections(l1_neuron_vec[i], l2_neuron_vec[i]);
                newHybridLayer->addNeuronToLayer(newHybridNeuron);
            }

            return newHybridLayer;

        } 



        void geneCrossMembranes(){
            
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
