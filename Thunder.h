
#include <iostream>
#include <Vector>
#include <cmath>

namespace Thunder{


    class Neuron {
    private:
        double activity;

    public:
        void setActivity(double a);

        double getActivity();


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









