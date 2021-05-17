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
            string name = "";
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
                cout << "           Neuron " << name << ": " << activation << "\n";
                SetConsoleTextAttribute(hConsole, 1);
            }

    };


    class axon{
        public:
            string name = "";
            neuron* source = nullptr;
            neuron* destination = nullptr;    
            double weight = 1;

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
                // cout << "Propagating " << source->name << " --( " << weight <<" )--> " << destination->name << "\n";
                // cout << "Neuron Activity: " << destination->activation << "\n";
                destination->activation += source->activation*weight;
                // cout << "Neuron Activity Post: " << destination->activation << "\n";
            }

            void displayAxon(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout << "           Axon " << name << ": " << weight << "\n";
                cout << "           Connects: " << source->name << " and " << destination->name << "\n";
                SetConsoleTextAttribute(hConsole, 1);
            }

    };


    class axonSet{

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
                cout << "\n";
                SetConsoleTextAttribute(hConsole, 1);
            }

    };


    class neuronLayer{

        private:

        public:
            vector<neuron*> neuronVec;

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



    class axonLayer{
        private:

        public:
            vector<axonSet*> completeLayer;

            void addAxonLayer(axonSet* a){
                completeLayer.push_back(a);
            }

            void forwardPropagate(){
                for (int i = 0; i < completeLayer.size(); i++){
                    completeLayer[i]->forwardPropagate();
                }
            }

    };



    class membrane{

        private:
            vector<neuronLayer*> neuronLayerVec;
            vector<axonSet*> axonSetVec;
            vector<axonLayer*> axonLayerCompleteVec;
            
        public:

            void addNeuronLayer(neuronLayer* n){
                neuronLayerVec.push_back(n);
            }

            void addAxonLayer(axonSet* a){
                axonSetVec.push_back(a);
            }

            void forwardPropogateMembrane(){
                bool normalizeFirstLayer = false;

                if (normalizeFirstLayer == true){
                    neuronLayerVec[0]->normalizeLayer();
                }

                // cout << "Neuron Vec Size: " << neuronLayerVec.size() << endl;
                // cout << "Axon Vec Size: " << axonSetVec.size() << endl;

                for (int i = 0; i < axonLayerCompleteVec.size(); i++){
                    axonLayerCompleteVec[i]->forwardPropagate();
                    neuronLayerVec[i+1]->normalizeLayer();
                }

            }


            void displayMembrane(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 13);
                cout << "   Membrane Neurons: \n";
                for (int i = 0; i < neuronLayerVec.size(); i++){
                    neuronLayer* currentNeuronLayer = neuronLayerVec[i]; 
                    currentNeuronLayer->displayNeurons();
                }
                SetConsoleTextAttribute(hConsole, 1);
            }

            void displayMembraneAxons(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 13);
                cout << "   Membrane Axons: \n";
                for (int i = 0; i < axonSetVec.size(); i++){
                    axonSet* currentAxonLayer = axonSetVec[i]; 
                    currentAxonLayer->displayAxons();
                }
                SetConsoleTextAttribute(hConsole, 1);
            }

            // Interconnects layers in a membrane assuming a dense network architecture
            void weaveDense(){
                // Weave between each layer
                for (int i = 0; i < neuronLayerVec.size() - 1; i++){
                    neuronLayer* currentLayer = neuronLayerVec[i];
                    neuronLayer* nextLayer = neuronLayerVec[i+1];
                    int nextLayerSize = nextLayer->neuronVec.size();

                    axonLayer* newAxonFilm = new axonLayer;


                    // For each neuron in the first layer
                    for (int k = 0; k < currentLayer->neuronVec.size(); k++){
                        axonSet* newAxonLayer = new axonSet;

                        // For each neuron in the next layer
                        for (int j = 0; j < nextLayer->neuronVec.size(); j++){
                            
                            axon* newAxon = new axon;
                            newAxon->source = currentLayer->neuronVec[k];
                            newAxon->destination = nextLayer->neuronVec[j];
                            //cout << "New Axon Connecting " << newAxon->source->name << " and " << newAxon->destination->name << "\n";
                            newAxonLayer->addAxon(newAxon);
                        }
                        newAxonFilm->addAxonLayer(newAxonLayer);
                        //axonSetVec.push_back(newAxonLayer);
                    }

                    axonLayerCompleteVec.push_back(newAxonFilm);

                }
            }

            void createDense(vector<int> shape){
                for (int i = 0; i < shape.size(); i++){
                    neuronLayer* newNeuronLayer = new neuronLayer;
                    for (int k = 0; k < shape[i]; k++){
                        neuron* newNeuron = new neuron;
                        newNeuron->name = to_string(i) + "-" + to_string(k);
                        newNeuronLayer->addNeuron(newNeuron);
                    }
                    neuronLayerVec.push_back(newNeuronLayer);
                }
                weaveDense();
                cout << "Axon Film Size: " << axonLayerCompleteVec.size() << endl;
            }

            void setNeuronActivbity(int layerIndex, int neuronIndex, double value){
                neuronLayerVec[layerIndex]->neuronVec[neuronIndex]->activation = value;
            }

    };























}