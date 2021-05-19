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


    void printDVector(vector<double> v){
        for (int i = 0; i < v.size(); i++){
            cout << v[i] << endl;
        }
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
            neuron* copyDeepNeuron(){
                neuron* clone = new neuron;
                clone->name = name;
                clone->type = type;
                clone->activation = activation;
                return clone;
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
            double weight = 0;

            axon(){
                // Initialize
            }
            axon(neuron* src, neuron* dest){
                source = src;
                destination = dest;
            }
            axon* copyDeepAxon(){
                axon* clone = new axon;
                clone->name = name;
                clone->source = source;
                clone->destination = destination;
                clone->weight = weight;
                return clone;
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

        public:
            vector<axon*> axonVec;

            axonSet* copyDeepAxonSet(){
                axonSet* clone = new axonSet;

                for (int i = 0; i < axonVec.size(); i++){
                    axon* currentAxonClone = axonVec[i]->copyDeepAxon();
                    clone->addAxon(currentAxonClone);
                }

                return clone;
            }

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

            neuronLayer* copyDeepNeuronLayer(){
                neuronLayer* clone = new neuronLayer;

                for (int i = 0; i < neuronVec.size(); i++){
                    neuron* currentNeuronClone = neuronVec[i]->copyDeepNeuron();
                    clone->addNeuron(currentNeuronClone);
                    //currentNeuronClone->name = neuronVec[i]->name + "*clone*"; // Builds up massive strings, here for testing purposes
                }

                return clone;
            }

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

            axonLayer* copyDeepAxonLayer(){
                axonLayer* clone = new axonLayer;

                for (int i = 0; i < completeLayer.size(); i++){
                    axonSet* currentAxonSetClone = completeLayer[i]->copyDeepAxonSet();
                    clone->addAxonSet(currentAxonSetClone);
                }

                return clone;
            }


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

        public:
            // Neuron layers contain neurons
            vector<neuronLayer*> neuronLayerVec;
            // Axon Layers contain axonSets
            vector<axonLayer*> axonLayerVec;

            string name = "";
            
        public:

            // Copies the shape, neurons, and activations of aneuron membrane
            membrane* copyDeepNeuronMembrane(){
                membrane* clone = new membrane;

                for (int i = 0; i < neuronLayerVec.size(); i++){
                    neuronLayer* currentNeuronLayerClone = neuronLayerVec[i]->copyDeepNeuronLayer();
                    clone->addNeuronLayer(currentNeuronLayerClone);
                }

                return clone;
            }

            // Takes the membrane's existing axons and neurons, and weaves them in a dense architecture
            void copyAxonWeights(membrane* target){
                for(int i = 0; i < axonLayerVec.size(); i++){ 
                    for(int j = 0; j < axonLayerVec[i]->completeLayer.size(); j++){
                        for(int k = 0; k < axonLayerVec[i]->completeLayer[j]->axonVec.size(); k++){
                            axonLayerVec[i]->completeLayer[j]->axonVec[k]->weight = target->axonLayerVec[i]->completeLayer[j]->axonVec[k]->weight;
                        }
                    }
                }
            }

            // Produces a copy of a dense network
            membrane* copyDenseMembrane(membrane* target){
                membrane* clone = target->copyDeepNeuronMembrane();
                clone->weaveDense();
                clone->copyAxonWeights(target);
                return clone;
            }

            void addNeuronLayer(neuronLayer* n){
                neuronLayerVec.push_back(n);
            }

            void addAxonLayer(axonLayer* a){
                axonLayerVec.push_back(a);
            }

            void forwardPropogateMembrane(bool normalizeFirstLayer = false){

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
                cout << "   Membrane " << name << " Neurons: \n";
                for (int i = 0; i < neuronLayerVec.size(); i++){
                    neuronLayer* currentNeuronLayer = neuronLayerVec[i]; 
                    currentNeuronLayer->displayNeurons();
                }
                SetConsoleTextAttribute(hConsole, 1);
            }

            void displayMembraneAxons(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 13);
                cout << "   Membrane " << name << " Axons: \n";
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
                            newAxon->name = newAxon->source->name + " -> " + newAxon->destination->name;
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
                //cout << "Axon Film Size: " << axonLayerVec.size() << endl;
            }

            void setNeuronActivity(int layerIndex, int neuronIndex, double value){
                neuronLayerVec[layerIndex]->neuronVec[neuronIndex]->activation = value;
            }

            // Sets the activations of a neuronLayer equal to an imprint
            void imprintLayer(int layerIndex, vector<double> imprint){
                for (int i = 0; i < neuronLayerVec[layerIndex]->neuronVec.size(); i++){
                    neuronLayerVec[layerIndex]->neuronVec[i]->activation = imprint[i];
                }
            }

            vector<double> returnLayerActivity(int layerIndex){
                vector<double> activity;

                for (int i = 0; i < neuronLayerVec[layerIndex]->neuronVec.size(); i++){
                    activity.push_back(neuronLayerVec[layerIndex]->neuronVec[i]->activation);
                }

                return activity;
            } 


    };


    class architect{

        public:

            // Inputs data into the membrane and uses it to calculate and return output data.
            void computeMembrane(membrane* m, vector<double> input){
                m->zeroNeuronMembrane();
                m->imprintLayer(0, input);
                m->forwardPropogateMembrane();
            }

            double calculateLastLayerError(membrane* m, vector<double> desiredOutput){
                // Outputs are assumed to be the final neuron layer of a membrane
                vector<double> membraneOutputs = m->returnLayerActivity(m->neuronLayerVec.size() - 1);
                double error = 0;

                for (int i = 0; i < desiredOutput.size(); i++){
                    error += abs(membraneOutputs[i] - desiredOutput[i]);
                }

                return error;
            }

            void evolveSupervised(membrane* seedMembrane, vector<double> input, vector<double> desiredOutput, double mutationRange = 0.1, int population = 5, int generations = 5){
                
                
                vector<membrane*> genePool;
                membrane* strongestSpecimen = seedMembrane;

                // Use seed membrane to establish score baseline
                genePool.push_back(strongestSpecimen);
                computeMembrane(strongestSpecimen, input);
                double strongestScore = calculateLastLayerError(strongestSpecimen, input);;
                

                for (int g = 0; g < generations; g++){
                    cout << "Generation " << g << "...\n";
                    for (int i = 0; i < population; i++){
                        membrane* newMembrane = strongestSpecimen->copyDenseMembrane(strongestSpecimen);
                        newMembrane->mutateAxonMembrane(mutationRange);
                        genePool.push_back(newMembrane);
                    }

                    for (int i = 0; i < genePool.size(); i++){
                        computeMembrane(genePool[i], input);
                        double score  = calculateLastLayerError(genePool[i], input);
                        if (score < strongestScore){
                            //cout << "New strongest membrane!\n";
                            strongestSpecimen = genePool[i];
                            strongestScore = score;
                        }
                    }
                    cout << "Membrane score: " << strongestScore << "\n\n";

                }

                cout << "Training has ended...\n";



            }

            


    };




















}