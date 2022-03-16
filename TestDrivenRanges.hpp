#ifndef TEST_DRIVEN_RANGES_HPP
#define TEST_DRIVEN_RANGES_HPP

#include <vector>
#include <iostream>
#define FAILURE true
#define NO_FAILURE false
#define DANGEROUS true
#define NOT_DANGEROUS false

typedef std::vector<std::vector<float>> OutputData;

class Sensor{
private:
  std::vector<float> _input_readings;
public:
  Sensor(std::vector<float> input): _input_readings(input){};
  void input(std::vector<float> input){
    _input_readings = input;
  }
  int check_Ampere_limits(void);
  bool check_redundancy_failure(Sensor otherSensor);
  OutputData process_data(void);
  void print_data_processed_to_file(std::streambuf* streamoutput);
};



#endif
