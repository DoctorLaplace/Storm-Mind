#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <windows.h>
#include <iomanip>

using namespace std;

namespace Neurogen{

    double sigmoid(double x){
        double value = x, e = 2.7182818284;
        value = pow(e, -x);
        value += 1;
        value = 1/value;
        return value;
    }


    double randomDouble(double min, double max, int precision = 6){
        cout << setprecision(precision);
        return min + (double)(rand()) / ((double)(RAND_MAX/(max - min)));
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

            void zeroNeuron(){
                activation = 0;
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

            void mutateAxon(double mutationRange){
                double mutationAmount = randomDouble(-mutationRange, mutationRange);
                weight += mutationAmount;
            }

            void displayAxon(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout << "               Axon " << name << ": " << weight << "\n";
                SetConsoleTextAttribute(hConsole, 6);
                cout << "                   Connects: " << source->name << " and " << destination->name << "\n";
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

            void mutateAxonSet(double mutationRange){
                for (int i = 0; i < axonVec.size(); i++){
                    axonVec[i]->mutateAxon(mutationRange);
                }
            }

            void displayAxons(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 11);
                cout << "           Axon Set: \n";
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

            void zeroNeuronLayer(){
                for (int i = 0; i < neuronVec.size(); i++){
                    neuronVec[i]->zeroNeuron();
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

            void addAxonSet(axonSet* a){
                completeLayer.push_back(a);
            }

            void forwardPropagate(){
                for (int i = 0; i < completeLayer.size(); i++){
                    completeLayer[i]->forwardPropagate();
                }
            }

            void mutateAxonLayer(double mutationRange){
                for (int i = 0; i < completeLayer.size(); i++){
                    completeLayer[i]->mutateAxonSet(mutationRange);
                }
            }

            void displayAxons(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 10);
                cout << "       Axon Layer: \n";
                for (int i = 0; i < completeLayer.size(); i++){
                    axonSet* currentAxon = completeLayer[i]; 
                    currentAxon->displayAxons();
                }
                cout << "\n";
                SetConsoleTextAttribute(hConsole, 1);
            }

    };



    class membrane{

        private:
            // Neuron layers contain neurons
            vector<neuronLayer*> neuronLayerVec;
            // Axon Layers contain axonSets
            vector<axonLayer*> axonLayerVec;
            
        public:

            void addNeuronLayer(neuronLayer* n){
                neuronLayerVec.push_back(n);
            }

            void forwardPropogateMembrane(){
                bool normalizeFirstLayer = false;

                if (normalizeFirstLayer == true){
                    neuronLayerVec[0]->normalizeLayer();
                }

                for (int i = 0; i < axonLayerVec.size(); i++){
                    axonLayerVec[i]->forwardPropagate();
                    neuronLayerVec[i+1]->normalizeLayer();
                }

            }

            void mutateAxonMembrane(double mutationRange){
                for (int i = 0; i < axonLayerVec.size(); i++){
                    axonLayerVec[i]->mutateAxonLayer(mutationRange);
                }
            }

            void zeroNeuronMembrane(){
                for (int i = 0; i < neuronLayerVec.size(); i++){
                    neuronLayerVec[i]->zeroNeuronLayer();
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
                for (int i = 0; i < axonLayerVec.size(); i++){
                    axonLayer* currentAxonLayer = axonLayerVec[i]; 
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


                    // For each neuron create a set of axons
                    for (int k = 0; k < currentLayer->neuronVec.size(); k++){
                        axonSet* newAxonSet = new axonSet;

                        // For each neuron in the next layer, create a connecting axon
                        for (int j = 0; j < nextLayer->neuronVec.size(); j++){
                            
                            axon* newAxon = new axon;
                            newAxon->source = currentLayer->neuronVec[k];
                            newAxon->destination = nextLayer->neuronVec[j];
                            //cout << "New Axon Connecting " << newAxon->source->name << " and " << newAxon->destination->name << "\n";
                            newAxonSet->addAxon(newAxon);
                        }
                        newAxonFilm->addAxonSet(newAxonSet);
                    }

                    axonLayerVec.push_back(newAxonFilm);

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
                cout << "Axon Film Size: " << axonLayerVec.size() << endl;
            }

            void setNeuronActivity(int layerIndex, int neuronIndex, double value){
                neuronLayerVec[layerIndex]->neuronVec[neuronIndex]->activation = value;
            }

    };























}