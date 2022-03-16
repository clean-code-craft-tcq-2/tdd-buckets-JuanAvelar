#include "TestDrivenRanges.hpp"
#include <algorithm>

#define MAX_CURR_LIMIT 15
#define MAX_UNCERTAINTY 0.5

int Sensor::check_Ampere_limits(void){
  int check = NOT_DANGEROUS;
  for(auto&& IN : _input_readings){
    if(IN >= MAX_CURR_LIMIT){
      check = DANGEROUS;
    }
  }
  return check;
}

bool Sensor::check_redundancy_failure(Sensor otherSensor){
  bool check = NO_FAILURE;
  for(size_t dataindex = 0; dataindex < this->_input_readings.size(); dataindex++){
    if(this->_input_readings.at(dataindex) + MAX_UNCERTAINTY < otherSensor._input_readings.at(dataindex) ||
       this->_input_readings.at(dataindex) - MAX_UNCERTAINTY > otherSensor._input_readings.at(dataindex)){
         check = FAILURE;
       }
  }
  return check;
}

OutputData Sensor::process_data(void){
  std::vector<float> sorted_input = this->_input_readings;
  std::vector<float> buffer;
  OutputData ret;
  std::sort(sorted_input.begin(), sorted_input.end());
  for(size_t index = 1; index < sorted_input.size(); index++){
    buffer.push_back(sorted_input.at(index-1));
    if(sorted_input.at(index-1) + 1.5 <= sorted_input.at(index)){
      //then the separation between values is too much a new set will be created
      ret.push_back(buffer);
      //std::cout << "buffer next at " << index<<"\n";//uncomment this to check the position at which new set is created
      buffer.clear();
    }
  }
  buffer.push_back(sorted_input.back());
  ret.push_back(buffer);
  return ret;
}

void Sensor::print_data_processed_to_file(std::streambuf* streamoutput){
  OutputData data = this->process_data();
  std::streambuf* Original_COUT = std::cout.rdbuf(streamoutput);
  std::cout << "Range, Readings\n";
  for(auto&& OUT : data){
    std::cout << OUT.front() << "-" << OUT.back() << ", " << OUT.size() << std::endl;
  }
  //restoring STDOUT
  std::cout.rdbuf(Original_COUT);
}
