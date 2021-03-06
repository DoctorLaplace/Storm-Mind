#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <windows.h>
#include <iomanip>
#include <algorithm>        // std::remove_if
#include <future>           // std::async, std::future
#include <iostream>

using namespace std;

namespace Neurogen{

    // Sigmoid function
    double sigmoid(double x){
        double value = x, e = 2.7182818284;
        value = pow(e, -x);
        value += 1;
        value = 1/value;
        return value;
    }

    // Sin function
    double sinFunction(double x){
        return (sin(x) + 1)/2;
    }

    // Weird function
    double weirdFunction(double x){
        return pow(x,2)/50;
    }


    // Produces a random double between a specified minimum and maximum
    double randomDouble(double min, double max, int precision = 6){
        cout << setprecision(precision);
        return min + (double)(rand()) / ((double)(RAND_MAX/(max - min)));
    }

    // Prints the contents of a vector of doubles to the terminal
    void printDVector(vector<double> v){
        for (int i = 0; i < v.size(); i++){
            cout << v[i] << endl;
        }
    }

    void printIVector(vector<int> v){
        for (int i = 0; i < v.size(); i++){
            cout << v[i] << endl;
        }
    }

    // Takes an integer vector and returns a sorted vector
    vector<int> sortIntVector(vector<int> v){
        vector<int> sortedVec;

        while (v.size() > 0){
            int indexSmallest = 0;
            for (int i = 0; i < v.size(); i++){
                if (v[i] < v[indexSmallest]){
                    indexSmallest = i;
                }
            }
            sortedVec.push_back(v[indexSmallest]);
            v.erase(v.begin() + indexSmallest);
        }

        return sortedVec;
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
                // cout << "Neuron deleted <" << name << ">\n";
            }

            void normalize(){
                if (type == "none"){
                    // raw activation
                }
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
            double bias = 0;
            string mutationMode = "percent";

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
                clone->bias = 0;
                return clone;
            }
            ~axon(){
                // Deconstruct
                // cout << "Axon: " << name << " destroyed.\n";
            }

            void forwardActivation(){
                // cout << "Propagating " << source->name << " --( " << weight <<" )--> " << destination->name << "\n";
                // cout << "Neuron Activity: " << destination->activation << "\n";
                destination->activation += (source->activation*weight) + bias;
                // cout << "Neuron Activity Post: " << destination->activation << "\n";
            }

            void mutateAxon(double mutationRange){
                double mod = 1;

                // Percent is vulnerable to getting trappped at zero. Add to mutationAmount rather than mod...
                if (mutationMode == "percent"){
                    mod = weight+0.01;
                }
                if (mutationMode == "proportional"){
                    mod = 1;
                }

                double mutationAmount = randomDouble(-mutationRange*mod, mutationRange*mod);
                weight += mutationAmount;
                double biasAmount = randomDouble(-mutationRange/10, mutationRange/10);
                bias += biasAmount;
            }

            void displayAxon(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout << "               Axon " << name << ": " << weight << "  :  " << bias << "\n";
                SetConsoleTextAttribute(hConsole, 6);
                cout << "                   Connects: " << source->name << " and " << destination->name << "\n";
                SetConsoleTextAttribute(hConsole, 1);
            }

    };


    class axonSet{

        public:
            vector<axon*> axonVec;

            ~axonSet(){
                // Deconstruct
                // cout << "Axon set deleted.\n";
                for (int i = 0; i < axonVec.size(); i++){
                    delete axonVec[i];
                }
            }

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

            ~neuronLayer(){
                // Deconstruct
                // cout << "Neuron layer deleted.\n";
                for (int i = 0; i < neuronVec.size(); i++){
                    delete neuronVec[i];
                }
            }


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


            ~axonLayer(){
                // Deconstruct
                // cout << "Axon layer deleted.\n";
                for (int i = 0; i < completeLayer.size(); i++){
                    delete completeLayer[i];
                }
            }

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


    // An artificial neural network composed of neuron and axon layers
    class membrane{

        public:
            // Neuron layers contain neurons
            vector<neuronLayer*> neuronLayerVec;
            // Axon Layers contain axonSets
            vector<axonLayer*> axonLayerVec;
            // The name of the membrane
            string name = "";
            // The fitness of the membrane
            double fitness = INFINITE;
            
        public:

            // Constructor for the membrane class
            membrane(){
                // Enpty Constructor
            }

            // Constructor for the membrane class with name assignment
            membrane(string n){
                name = n;
            }

            // Deconstructor for the membrane class
            ~membrane(){
                // Deconstruct
                // cout << "Membrane " << name << " deleted.\n";
                for (int i = 0; i < neuronLayerVec.size(); i++){
                    delete neuronLayerVec[i];
                }
                for (int i = 0; i < axonLayerVec.size(); i++){
                    delete axonLayerVec[i];
                }
            }

            // Copies the shape, neurons, and activations of a neuron membrane
            membrane* copyDeepNeuronMembrane(){
                membrane* clone = new membrane;

                for (int i = 0; i < neuronLayerVec.size(); i++){
                    neuronLayer* currentNeuronLayerClone = neuronLayerVec[i]->copyDeepNeuronLayer();
                    clone->addNeuronLayer(currentNeuronLayerClone);
                }

                return clone;
            }

            // Sets the axon weights of this membrane identical to another membrane's
            void copyAxonWeights(membrane* target){
                for(int i = 0; i < axonLayerVec.size(); i++){ 
                    for(int j = 0; j < axonLayerVec[i]->completeLayer.size(); j++){
                        for(int k = 0; k < axonLayerVec[i]->completeLayer[j]->axonVec.size(); k++){
                            axonLayerVec[i]->completeLayer[j]->axonVec[k]->weight = target->axonLayerVec[i]->completeLayer[j]->axonVec[k]->weight;
                            axonLayerVec[i]->completeLayer[j]->axonVec[k]->bias = target->axonLayerVec[i]->completeLayer[j]->axonVec[k]->bias;
                        }
                    }
                }
            }

            // Sets the axon weights of this membrane to be a random composition inherited from two parent membranes
            void copyGeneCrossAxonWeights(membrane* parent1, membrane* parent2){
                for(int i = 0; i < axonLayerVec.size(); i++){ 
                    for(int j = 0; j < axonLayerVec[i]->completeLayer.size(); j++){
                        for(int k = 0; k < axonLayerVec[i]->completeLayer[j]->axonVec.size(); k++){
                            int randomCoin = rand() % 2;
                            double inheritedWeight;
                            membrane* selectedParent;

                            if (randomCoin == 0){
                                selectedParent = parent1;
                            }else{
                                selectedParent = parent2;
                            }

                            axonLayerVec[i]->completeLayer[j]->axonVec[k]->weight = selectedParent->axonLayerVec[i]->completeLayer[j]->axonVec[k]->weight;
                            axonLayerVec[i]->completeLayer[j]->axonVec[k]->bias = selectedParent->axonLayerVec[i]->completeLayer[j]->axonVec[k]->bias;
                        }
                    }
                }
            }

            // Sets all of the axon weights within a membrane to a specific value
            void setAllAxonWeights(double value){
                for(int i = 0; i < axonLayerVec.size(); i++){ 
                    for(int j = 0; j < axonLayerVec[i]->completeLayer.size(); j++){
                        for(int k = 0; k < axonLayerVec[i]->completeLayer[j]->axonVec.size(); k++){
                            axonLayerVec[i]->completeLayer[j]->axonVec[k]->weight = value;
                        }
                    }
                }
            }

            // Mutates a percentage of the axons within a menmbrane
            void mutatePartOfAxonWeights(double mutationRange, double percentMutated = 0.1){
                // Rounds down to 2 decimal points by default
                // To gain more p[recision a new technique would need development]
                int probablityInt = percentMutated*100;
                // cout << probablityInt << endl;
                int probabiliityCheck;
                 
                for(int i = 0; i < axonLayerVec.size(); i++){ 
                    for(int j = 0; j < axonLayerVec[i]->completeLayer.size(); j++){
                        for(int k = 0; k < axonLayerVec[i]->completeLayer[j]->axonVec.size(); k++){
                            probabiliityCheck = rand() % 100;
                            if (probabiliityCheck < probablityInt){
                                axonLayerVec[i]->completeLayer[j]->axonVec[k]->mutateAxon(mutationRange);
                            }
                        }
                    }
                }
            }

            // Produces a clone of a dense network
            membrane* copyDenseMembrane(membrane* target){
                membrane* clone = target->copyDeepNeuronMembrane();
                clone->weaveDense();
                clone->copyAxonWeights(target);
                //clone->name = target->name + "-clone";
                return clone;
            }

            // Returns the shape of a membrane's neuron layout
            vector<int> getMembraneShape(){
                vector<int> shape;
                for (int i = 0; i < neuronLayerVec.size(); i++){
                    shape.push_back(neuronLayerVec[i]->neuronVec.size());
                }
                return shape;
            }

            // Adds a neuron layer to the membrane
            void addNeuronLayer(neuronLayer* n){
                neuronLayerVec.push_back(n);
            }

            // Adds an axon layer to the membrane
            void addAxonLayer(axonLayer* a){
                axonLayerVec.push_back(a);
            }

            // Forward propagates activations through the membrane
            void forwardPropogateMembrane(bool normalizeFirstLayer = false){

                if (normalizeFirstLayer == true){
                    neuronLayerVec[0]->normalizeLayer();
                }

                for (int i = 0; i < axonLayerVec.size(); i++){
                    axonLayerVec[i]->forwardPropagate();
                    neuronLayerVec[i+1]->normalizeLayer();
                }

            }

            // Mutates all of the axons in the membrane by a defined random range
            void mutateAxonMembrane(double mutationRange){
                for (int i = 0; i < axonLayerVec.size(); i++){
                    axonLayerVec[i]->mutateAxonLayer(mutationRange);
                }
            }

            // Sets all neuron activations to zero in the membrane
            void zeroNeuronMembrane(){
                for (int i = 0; i < neuronLayerVec.size(); i++){
                    neuronLayerVec[i]->zeroNeuronLayer();
                }
            }

            // Displays the neuron activations within the membrane
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

            // Displays the final neuron activations within the membrane
            void displayMembraneFinalLayer(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 13);
                cout << "   Membrane " << name << " Final Layer: \n";
                    neuronLayer* currentNeuronLayer = neuronLayerVec[neuronLayerVec.size() - 1]; 
                    currentNeuronLayer->displayNeurons();
                SetConsoleTextAttribute(hConsole, 1);
            }

            // Displays the axon weights within the membrane
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

            // Displays the fitness of the membrane
            void displayMembraneFitness(){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 13);
                cout << "   Membrane " << name << " fitness: " << fitness << "\n";
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

            // Creates a dense neural network from a given shape vector
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

            // Sets the activation of a specific neuron to a value
            void setNeuronActivity(int layerIndex, int neuronIndex, double value){
                neuronLayerVec[layerIndex]->neuronVec[neuronIndex]->activation = value;
            }

            // Sets the activations of a neuronLayer equal to an imprint
            void imprintLayer(int layerIndex, vector<double> imprint){
                for (int i = 0; i < neuronLayerVec[layerIndex]->neuronVec.size(); i++){
                    neuronLayerVec[layerIndex]->neuronVec[i]->activation = imprint[i];
                }
            }

            // Returns the activations of a particular layer as a vector of doubles
            vector<double> returnLayerActivity(int layerIndex){
                vector<double> activity;

                for (int i = 0; i < neuronLayerVec[layerIndex]->neuronVec.size(); i++){
                    activity.push_back(neuronLayerVec[layerIndex]->neuronVec[i]->activation);
                }

                return activity;
            } 


    };


    // A system that trains membranes using various algorithms
    class architect{

        public:

            vector<membrane*> deleteBucket;

            void emptyDeleteBucket(){
                for ( int i = 0; i < deleteBucket.size(); i++ ){       
                    delete deleteBucket[i];    
                }    
                deleteBucket.clear(); 
            }

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

            double supervisedSetError(membrane* m, vector<vector<double>> inputSet, vector<vector<double>> desiredOutputSet){
                double totalError = 0;

                for (int i = 0; i < inputSet.size(); i++){
                    computeMembrane(m, inputSet[i]);
                    double error  = calculateLastLayerError(m, desiredOutputSet[i]);
                    totalError += error;
                } 

                return totalError;
            }


            membrane* evolveSupervised(membrane* seedMembrane, vector<vector<double>> inputSet, vector<vector<double>> desiredOutputSet, double mutationRange = 0.1, int population = 5, int generations = 5){
                
                
                // Considers strongest membrane a clone of the seed membrane to avoid deleting it in the algorithm
                membrane* strongestSpecimen = seedMembrane->copyDenseMembrane(seedMembrane);
                vector<membrane*> genePool;
                genePool.push_back(strongestSpecimen);


                // Use seed membrane to establish score baseline
                double strongestScore = supervisedSetError(strongestSpecimen, inputSet, desiredOutputSet);
                

                for (int g = 0; g < generations; g++){

                    
                    cout << "Generation " << g << "...\n";
                    for (int i = 0; i < population; i++){
                        membrane* newMembrane = strongestSpecimen->copyDenseMembrane(strongestSpecimen);
                        newMembrane->mutateAxonMembrane(mutationRange);
                        genePool.push_back(newMembrane);
                    }

                    for (int i = 0; i < genePool.size(); i++){
                        double score  = supervisedSetError(genePool[i], inputSet, desiredOutputSet);
                        if (score < strongestScore){
                            //cout << "New strongest membrane!\n";
                            strongestSpecimen = genePool[i];
                            strongestScore = score;
                        }
                    }

                    cout << "Membrane score: " << strongestScore << "\n\n";

                    // Clean up
                    // Add current genePool to delete bucket
                    for (int k = 0; k < genePool.size(); k++){
                        if (genePool[k] != strongestSpecimen){
                            deleteBucket.push_back(genePool[k]);
                        }
                        
                    }
                    //cout << genePool.size() << endl;
                    genePool.clear();                    
                    emptyDeleteBucket();

                }

                cout << "Membrane score: " << strongestScore << "\n";
                cout << "Training has ended...\n";
                
                
                return strongestSpecimen;

            }

            // Speciated Evolutionary Algorithm Recall
            membrane* SEAR(membrane* seedMembrane, vector<vector<double>> inputSet, vector<vector<double>> desiredOutputSet, double mutationRange = 0.1, int population = 5, int generations = 5, double targetFitness = 0.1, int speciesCount = 2){

                membrane* strongestSpecimen = seedMembrane->copyDenseMembrane(seedMembrane);
                double strongestScore  = supervisedSetError(strongestSpecimen, inputSet, desiredOutputSet);

                while (strongestScore > targetFitness){
                    vector<membrane*> speciesList;

                    for (int i = 0; i < speciesCount; i++){
                        //cout << "Generating Species " << i << "\n";
                        membrane* newSpecies = evolveSupervised(strongestSpecimen, inputSet, desiredOutputSet, mutationRange, population, generations);
                        speciesList.push_back(newSpecies);
                    }
                    
                    for (int i = 0; i < speciesList.size(); i++){
                        double specimenScore = supervisedSetError(speciesList[i], inputSet, desiredOutputSet);
                        if (specimenScore < strongestScore){
                            strongestSpecimen = speciesList[i];
                            strongestScore = specimenScore;
                        }
                    }

                    // Clean up
                    for (int k = 0; k < speciesList.size(); k++){
                        if (speciesList[k] != strongestSpecimen){
                            deleteBucket.push_back(speciesList[k]);
                        }
                        
                    }
                    speciesList.clear();                    
                    emptyDeleteBucket();

                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Entering next depth....\n";
                    SetConsoleTextAttribute(hConsole, 1);
                }

                

            

                cout << "Omega specimen found.\n";
                cout << "Omega Score: " << strongestScore << endl;



                return strongestSpecimen;





            }

            // Genetic evolution method
            vector<membrane*> GEM(vector<membrane*> seedPopulation, vector<vector<double>> inputSet, vector<vector<double>> desiredOutputSet, double percentMutated = 0.5, double mutationRange = 0.5){
                
                // Cross breed the population
                // Produce a new population of descendant membranes
                // Mutate them
                // Rank fitness
                // Select a percent of them based on fitness distribution
                // Return new population

                vector<int> memShape = seedPopulation[0]->getMembraneShape();
                vector<membrane*> elitePopulation = seedPopulation;


                // Gene cross membrane Population
                vector<membrane*> geneCrossPopulation;  
                int geneCrossSize = 600;                  


                for (int i = 0; i < geneCrossSize; i++){
                    int selectedPartner1 = rand() % seedPopulation.size();
                    int selectedPartner2 = rand() % seedPopulation.size();
                    membrane* parent1 = seedPopulation[selectedPartner1];
                    membrane* parent2 = seedPopulation[selectedPartner2];

                    //cout << "Crossing " << parent1->name << " and " << parent2->name << "\n";


                    // Stray membrane cleanup needed for optimizaytion
                    membrane* newMembrane = new membrane;
                    //newMembrane->name = "" ;//parent1->name + parent2->name;
                    newMembrane->createDense(memShape);
                    newMembrane->copyGeneCrossAxonWeights(parent1, parent2);
                    geneCrossPopulation.push_back(newMembrane);
                }


                // Mutate crossbreeds
                double percentToMutated = percentMutated;
                double mutationSizeRange = mutationRange;
                for (int i = 0; i < geneCrossPopulation.size(); i++){
                    geneCrossPopulation[i]->mutatePartOfAxonWeights(mutationRange, percentMutated);
                }


                // Determine the fitness of each membrane
                for (int i = 0; i < geneCrossPopulation.size(); i++){
                    geneCrossPopulation[i]->fitness = supervisedSetError(geneCrossPopulation[i], inputSet, desiredOutputSet);
                }


                // Create sorted fitness vector, first is most fit
                vector<membrane*> fitPopulation;
                while (geneCrossPopulation.size() > 0){
                    int indexSmallest = 0;
                    for (int i = 0; i < geneCrossPopulation.size(); i++){
                        if (geneCrossPopulation[i]->fitness < geneCrossPopulation[indexSmallest]->fitness){
                            indexSmallest = i;
                        }
                    }
                    fitPopulation.push_back(geneCrossPopulation[indexSmallest]);
                    geneCrossPopulation.erase(geneCrossPopulation.begin() + indexSmallest);
                }


                // Select top specimens for new population
                double percentSelected = 0.025;
                int selectionSize = fitPopulation.size() * percentSelected;
                // New population is composed of top specimens
                vector<membrane*> selectPopulation;
                for (int i = 0; i < selectionSize; i++){
                    // Candidates are selected from the start of the vector (where fitness should be highest)
                    selectPopulation.push_back(fitPopulation[0]);
                    fitPopulation.erase(fitPopulation.begin());
                    
                }

                // Delete Remaining in fitPopulation / Memory Cleanup
                for (int i = 0; i < fitPopulation.size(); i++){
                    // Candidates are selected from the start of the vector (where fitness should be highest)
                    deleteBucket.push_back(fitPopulation[i]);
                }
                emptyDeleteBucket();


                elitePopulation = selectPopulation;

                cout << elitePopulation[0]->fitness << "\n";



                return elitePopulation;




            }

            void displayPopulationFinalMembranes(vector<membrane*> population){
                for (int i = 0; i < population.size(); i++){
                    population[i]->displayMembraneFinalLayer();
                }
            }

            void displayPopulationAxons(vector<membrane*> population){
                for (int i = 0; i < population.size(); i++){
                    population[i]->displayMembraneAxons();
                }
            }

            void displayPopulationFitnesses(vector<membrane*> population){
                for (int i = 0; i < population.size(); i++){
                    population[i]->displayMembraneFitness();
                }
            }

    };


    class dimensionalSim{

        public:
            int xp = 0;
            int yp = 0;
            double xvel = 0;
            double yvel = 0;

            double curx = 0;
            double cury = 0;

            dimensionalSim(){
                curx = randomDouble(-100, 100);
                cury = randomDouble(-100, 100);
            }

            void updatePhysics(){
                curx += xvel;
                cury += yvel;
            }

            void updateControl(){
                if (GetKeyState('A') & 0x8000){
                    xvel += -0.1;
                }
                if (GetKeyState('D') & 0x8000){
                    xvel += 0.1;
                }
            }

            void update(){
                updateControl();
                updatePhysics();
            }

            void displayCoords(){
                cout << "X: " << curx << "\nY: " << cury << "\n";
            }

    };



    class runtimeUniverse{

        private:
            int internalVal = 0; 

        public:

            void ticker(){
                int count = 0;
                while (count <= 5000){
                    cout << count << "\n";
                    count += 1;
                    internalVal = count;
                    Sleep(100);
                }
            }

            void session(){
                std::cout << "Session Started...\n";
                bool sessionActive = true;
                while (sessionActive){
                    if (GetKeyState('A') & 0x8000){
                        cout << internalVal << "\n";
                    }
                    Sleep(10);
                }
                std::cout << "Session Ended...\n";
            }

            void dimSim(){

                std::cout << "Dimensional Sim Started...\n";

                dimensionalSim sim;

                bool sessionActive = true;
                while (sessionActive){
                    cout << "Tick\n";
                    sim.update();
                    sim.displayCoords();
                    Sleep(100);
                }



                std::cout << "Dimensional Sim Ended...\n";
            }



    };

    


    








}