#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <windows.h>


using namespace std;

namespace Neurogen{

    double sigmoid(double x){
        double value = x, e = 2.7182818284;
        value = pow(e, -x);
        value += 1;
        value = 1/value;
        return value;
    }

    class neuron{
        public:
            string type = "sigmoid";
            double activation = 0;

            neuron(){
                // Initialize
            }
            neuron(double initialAct){
                activation = initialAct;
            }
            ~neuron(){
                // Deconstruct
            }

            void normalize(){
                if (type == "linear"){
                    if (activation > 0.5){
                        activation = (2*activation)-1;
                    }else{
                        activation = 0;
                    }
                }
                if (type == "sigmoid"){
                    activation = sigmoid(activation);
                }
            }

            void displayNeuron(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 11);
                cout << "           Neuron: " << activation << "\n";
                SetConsoleTextAttribute(hConsole, 1);
            }

    };


    class axon{
        public:
            neuron* source = nullptr;
            neuron* destination = nullptr;    
            double weight = 0;

            axon(){
                // Initialize
            }
            axon(neuron* src, neuron* dest){
                source = src;
                destination = dest;
            }
            ~axon(){
                // Deconstruct
            }

            void forwardActivation(){
                destination->activation += source->activation*weight;
            }

            void displayAxon(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout << "           Axon: " << weight << "\n";
                SetConsoleTextAttribute(hConsole, 1);
            }

    };


    class axonLayer{

        private:
            vector<axon*> axonVec;

        public:

            void addAxon(axon* d){
                axonVec.push_back(d);
            }

            // Something is wacky with this loop. It kills the output stream
            void forwardPropagate(){
                for (int i = 0; i < axonVec.size(); i++){
                    axon* currentAxon = axonVec[i]; 
                    currentAxon->forwardActivation();
                }
            }

            void displayAxons(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 10);
                cout << "       Axon Layer: \n";
                for (int i = 0; i < axonVec.size(); i++){
                    axon* currentAxon = axonVec[i]; 
                    currentAxon->displayAxon();
                }
                SetConsoleTextAttribute(hConsole, 1);
            }

    };


    class neuronLayer{

        private:
            vector<neuron*> neuronVec;

        public:

            void addNeuron(neuron* d){
                neuronVec.push_back(d);
            }

            void normalizeLayer(){
                for (int i = 0; i < neuronVec.size(); i++){
                    neuron* currentNeuron = neuronVec[i]; 
                    currentNeuron->normalize();
                }
            }

            void displayNeurons(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 10);
                cout << "       Neuron Layer: \n";
                for (int i = 0; i < neuronVec.size(); i++){
                    neuron* currentNeuron = neuronVec[i]; 
                    currentNeuron->displayNeuron();
                }
                SetConsoleTextAttribute(hConsole, 1);
            }

    };


    class membrane{

        private:
            vector<neuronLayer*> neuronLayerVec;
            vector<axonLayer*> axonLayerVec;
            
        public:

            void addNeuronLayer(neuronLayer* n){
                neuronLayerVec.push_back(n);
            }

            void addAxonLayer(axonLayer* a){
                axonLayerVec.push_back(a);
            }

            void forwardPropogateMembrane(){
                bool normalizeFirstLayer = false;

                for (int i = 0; i < neuronLayerVec.size(); i++){
                    neuronLayer* currentNeuronLayer = neuronLayerVec[i]; 

                    if (i < axonLayerVec.size()){
                        axonLayer* currentAxonLayer = axonLayerVec[i]; 
                        currentAxonLayer->forwardPropagate();
                    }

                    // Normalize unless layer is first and normalize first is false
                    if (normalizeFirstLayer == false){
                        if (i != 0){
                            currentNeuronLayer->normalizeLayer();
                        }
                    }else{
                        currentNeuronLayer->normalizeLayer();
                    }
                }
            }


            void displayMembrane(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 13);
                cout << "   Membrane: \n";
                for (int i = 0; i < neuronLayerVec.size(); i++){
                    neuronLayer* currentNeuronLayer = neuronLayerVec[i]; 
                    currentNeuronLayer->displayNeurons();
                }
                SetConsoleTextAttribute(hConsole, 1);
            }

            void createDense(vector<int> shape){
                for (int i = 0; i < shape.size(); i++){
                    neuronLayer* newNeuronLayer = new neuronLayer;
                    for (int k = 0; k < shape[i]; k++){
                        neuron* newNeuron = new neuron;
                        newNeuronLayer->addNeuron(newNeuron);
                    }
                    neuronLayerVec.push_back(newNeuronLayer);
                }
            }



    };























}