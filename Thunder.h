
#ifndef THUNDER_H
#define THUNDER_H

#include <iostream>
#include <Vector>
#include <cmath>
#include <windows.h>

namespace Thunder{


    class Neuron {

    private:
        struct connection{
            Neuron* connectTarget = nullptr;
            double connectionWeight = 0;
        };

        double activity = 0;

        std::vector<connection*> connectionVec;


    public:
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

    };


    class Layer {

    private:
        std::vector<Neuron*> layerVec;


    public:
        
        void addNeuronToLayer(Neuron *n){
            layerVec.push_back(n);
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
        }
     
    };

    class Membrane {

    private:
        std::vector<Layer*> membraneVec;


    public:
        void addLayerToMembrane(Layer *l){
            membraneVec.push_back(l);
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
